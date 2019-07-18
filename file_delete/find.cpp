/*----------------------------------------------------------------------------*/
/* デジタルカメラ格納 フォルダ配下ファイル検索                                */
/* デジタルカメラにフォルダに格納されるファイル名を取得します。               */
/* 本ファイルの目的はWindows系OSの_find系関数をラッピングしています。         */
/*----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "find.h"

/*----------------------------------------------------------------------------*/
/* グローバル変数                                                             */
/*----------------------------------------------------------------------------*/
static long g_FindIndex[FLD_NUM_MAX];            /* Find用識別ID              */

/*----------------------------------------------------------------------------*/
/* プロトタイプ宣言(private)                                                  */
/*----------------------------------------------------------------------------*/
void FindErr( long FindHandle, const char* name, ... );

/*----------------------------------------------------------------------------*/
/* フォルダ情報取得処理 Find_Open                                             */
/* 機能概要     ：指定フォルダ配下の識別IDを取得する。                        */
/* 引数         ：char*            ：FullPath    ：ファイル名バッファ 終端NULL*/
/*              ：unsigned short   ：PathLength  ：第一引数文字サイズ         */
/*              ：                 ：            ：最大250Byteまで            */
/* 戻り値       ：long             ：正常時      ：Find用識別ID               */
/*              ：                 ：異常時      ：FIND_NG                    */
/* 作成日       ：2007/10/17    新規作成                                      */
/*----------------------------------------------------------------------------*/
long Find_Open( char* FullPath, unsigned short PathLength )
{
	long               usPathIdx  = 0;           /* パス格納Index             */
	int                FindNextRet= 0;           /* 1回目の_findnext戻り値格納*/
	long               FindHandle = 0;           /* _findfirst受信ハンドル    */
	struct _finddata_t c_file;                   /* 指定ファイル、フォルダ情報*/
	char               cPath[256];               /* 修正後フォルダパス        */
	
	/* パラメータチェック --------------------------------------------------- */
	if(( FullPath == 0 ) || ( PathLength == 0 ) || ( PathLength > FLD_PATH_MAX )) {
		FindErr( 0, "【Find_Open】Param err.[%d]\n", (int)PathLength );
		return FIND_NG;
	}
	
	if( strlen( FullPath ) >= FLD_PATH_MAX ) {
		FindErr( 0, "【Find_Open】Path Length Over err.[%d]\n", (int)strlen( FullPath ));
		return FIND_NG;
	}
	
	/* パス空間の空き領域検索 ----------------------------------------------- */
	for( usPathIdx = 0; usPathIdx < FLD_NUM_MAX; usPathIdx ++ ) {
		if( g_FindIndex[usPathIdx] == 0 ) {
			break;
		}
	}
	
	/* エラーチェック */
	if( usPathIdx >= FLD_NUM_MAX ) {
		FindErr( 0, "【Find_Open】Path Full err.\n");
		return FIND_NG;
	}
	
	/* フォルダパスからワイルドカードに変更 --------------------------------- */
	memset( cPath, 0, sizeof( cPath ));
	strcpy( cPath, FullPath );
	strcat( cPath, "\\*" );
	
	/* "."と".."を先に検索 -------------------------------------------------- */
	FindHandle = (long)_findfirst(( const char *)cPath, &c_file );
	if( FindHandle == -1 ) {
		FindErr( 0, "【Find_Open】findfirst err.\n");
		return FIND_NG;
	}
	
	if( c_file.name[0] != '.' ) {
		FindErr( FindHandle, "【Find_Open】. Check err.\n");
		return FIND_NG;
	}
	
	/* ".."チェック */
	FindNextRet = _findnext( FindHandle, &c_file );
	if( FindNextRet != 0 ) {
		FindErr( FindHandle, "【Find_Open】findnext err.\n");
		return FIND_NG;
	}
	
	if( strncmp( "..", c_file.name, 2 ) != 0 ) {
		FindErr( FindHandle, "【Find_Open】.. Check err.\n");
		return FIND_NG;
	}
	
	/* ハンドルコピー */
	g_FindIndex[usPathIdx] = FindHandle;
	
	/* Index番号+1を返す */
	return ( usPathIdx + 1 );
	
}


/*----------------------------------------------------------------------------*/
/* フォルダ情報取得処理 Find                                                  */
/* 機能概要     ：指定ID配下のファイル名を取得し、上位へ返却                  */
/* 引数         ：long             ：Handle      ：Find_Openで取得したID      */
/*              ：char*            ：FileName    ：ファイル名バッファ中身無し */
/*              ：unsigned short   ：FileLength  ：第二引数バッファサイズ     */
/*              ：                 ：            ：最大256Byteまで            */
/*              ：unsigned long    ：FileSize    ：取得ファイルサイズ         */
/*              ：char*            ：Attr        ：ファイル種別               */
/*              ：                 ：FIND_FILE   ：ファイル                   */
/*              ：                 ：FIND_FLD    ：フォルダ                   */
/* 戻り値       ：long             ：正常時      ：FIND_OK                    */
/*              ：                 ：異常時      ：FIND_NG                    */
/*              ：                 ：ファイル終端：FIND_EOF                   */
/* 作成日       ：2007/10/17    新規作成                                      */
/*----------------------------------------------------------------------------*/
long Find( long Handle, char* FileName, unsigned short FileLength, 
		   unsigned long *FileSize, char* Attr )
{
	long               FindHandle = 0;           /* _findfirst受信ハンドル    */
	int                FindNextRet= 0;           /* 1回目の_findnext戻り値格納*/
	struct _finddata_t c_file;                   /* 指定ファイル、フォルダ情報*/

	/* パラメータチェック --------------------------------------------------- */
	if(( Handle <= 0 ) || ( Handle > FLD_NUM_MAX ) || ( FileName == 0 ) ||
	   ( Attr == 0 ) || ( FileLength == 0 ) || ( FileLength > FILE_NAME_MAX ) || ( FileSize == 0 )) {
		FindErr( 0, "【Find】Param err.[%d]\n", Handle );
		return FIND_NG;
	}
	
	if( g_FindIndex[Handle - 1] == 0 ) {
		FindErr( 0, "【Find】FindIndex Not Found.[%d]\n",g_FindIndex[Handle - 1] );
		return FIND_NG;
	}
	
	/* 初期化 */
	memset( FileName, 0, FileLength );
	
	FindHandle = g_FindIndex[Handle - 1];
	
	FindNextRet = _findnext( FindHandle, &c_file );
	if( FindNextRet != 0 ) {
		/* 終端終了か否か判断する */
		if( errno == ENOENT ) {
			return FIND_EOF;
		}
		FindErr( FindHandle, "【Find】findnext err.\n");
		return FIND_NG;
	}
	
	/* ファイル名、属性、ファイルサイズ取得 --------------------------------- */
	memset( FileName, 0, FileLength );
	strcpy( FileName, c_file.name );
	
	if(( c_file.attrib & _A_SUBDIR ) == _A_SUBDIR ) {
		*Attr = FIND_FLD;
	} else {
		*Attr = FIND_FILE;
	}

	*FileSize = c_file.size;
	
	return FIND_OK;
}

/*----------------------------------------------------------------------------*/
/* フォルダ情報取得処理 Find_Close                                            */
/* 機能概要     ：指定フォルダ配下のファイル検索を終了する。                  */
/* 引数         ：long             ：Handle      ：Find_Openで取得したID      */
/* 戻り値       ：long             ：正常時      ：FIND_OK                    */
/*              ：                 ：異常時      ：FIND_NG                    */
/* 作成日       ：2007/10/17    新規作成                                      */
/*----------------------------------------------------------------------------*/
long Find_Close( long Handle )
{
	long           FindHandle = 0;           /* _findfirst受信ハンドル    */
	
	/* パラメータチェック --------------------------------------------------- */
	if(( Handle <= 0 ) || ( Handle > FLD_NUM_MAX ))  {
		FindErr( 0, "【Find】Param err.[%d]\n", Handle );
		return FIND_NG;
	}
	
	if( g_FindIndex[Handle - 1] == 0 ) {
		FindErr( 0, "【Find】FindIndex Not Found.[%d]\n",g_FindIndex[Handle - 1] );
		return FIND_NG;
	}
	
	/* Find用ハンドルをローカルにコピー、グローバル領域は削除 --------------- */
	FindHandle = g_FindIndex[Handle - 1];
	g_FindIndex[Handle - 1] = 0;
	
	/* Find終了 ------------------------------------------------------------- */
	_findclose( FindHandle );
	
	return FIND_OK;
}


/*----------------------------------------------------------------------------*/
/* フォルダ情報取得処理 FindErr                                               */
/* 機能概要     ：エラー発生時にログ出力と共に、自動でfindcloseを行う         */
/* 引数         ：long             ：FindHandle  ：_finddirstで取得したID     */
/*              ：char*            ：name...     ：可変長メッセージ           */
/* 戻り値       ：void             ：無し        ：                           */
/* 作成日       ：2007/10/17    新規作成                                      */
/*----------------------------------------------------------------------------*/
void FindErr( long FindHandle, const char* name, ... )
{
	va_list args;
	char *str = 0;
	
	/* メッセージエリア1KB確保 ---------------------------------------------- */
	str = ( char *)malloc( 1024 * 1024 );
	if( str == 0 ) {
		printf("【FindErr】malloc err.\n");
		if( FindHandle != 0 ) {
			_findclose( FindHandle );
		}
		return;
	}
	
	memset( str, 0, ( 1024 * 1024 ));
	
	/* 可変長引数変換取得 --------------------------------------------------- */
	va_start( args, name );
	vsprintf( str, name, args );
	va_end( args );
	
	/* エラーメッセージ出力 ------------------------------------------------- */
	printf("%s", str );
	
	/* find終了 ------------------------------------------------------------- */
	if( FindHandle != 0 ) {
		_findclose( FindHandle );
	}

	free( str );
	
	return;

}
