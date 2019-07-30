/* ------------------------------------------------------------------------- */
/*                                                                           */
/* １０万件ソート                                                            */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  番号    更新内容                                更新日      名前         */
/* ------------------------------------------------------------------------- */
/* 000000   新規作成                                2019/07/07  西岡  和輝   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル                                                           */
/* ------------------------------------------------------------------------- */

#include "main.h"

/* ------------------------------------------------------------------------- */
/* プロトタイプ宣言                                                          */
/* ------------------------------------------------------------------------- */
ADDS * DL_UserInterface( SLNG * , SCHR * );
SLNG   DL_ListPrint    ( ADDS * ); 
SCHR * DL_MemoryWrite  ( SLNG * , SLNG * , SCHR * );
ADDS * DL_ListWrite    ( SLNG * , SCHR * , SLNG * );
ADDS * DL_NewPointer   ( SLNG * );
ADDS * DL_SetPointer   ( SLNG * , ADDS * , ADDS * , ADDS * );
SLNG   DL_strconv      ( SLNG * , SCHR * );
FILE * DL_FileOpen     ( SLNG * , SCHR * );
SLNG   DL_FileSize     ( SLNG * , FILE * );
SLNG   DL_PointMove    ( SLNG * , SLNG   );

SINT main( SINT argc , SCHR * argv[] ) {

    /* 変数宣言 ------------------------------------------------------------ */
    SLNG   sl_errchk = 0;



    DL_UserInterface ( &sl_errchk , ( SCHR * )"C:\\Users\\ohs80472\\Desktop\\hal\\cl21\\課題07_19_07_09\\TestData.csv" );

    system( "pause" );
    return 0;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : DL_UserInterface                                               */
/* 機能名   : リストポインタの移動                                           */
/* 機能概要 : 移動値に応じて関数を振り分ける                                 */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : ADDS * : ad_pt       : 移動前 ポインタ                         */
/*          : SLNG   : sl_movenum  : ポインタ移動数                          */
/* 戻り値   : ADDS * :             : 移動後 ポインタ                         */
/* 作成日   : 2019/07/09       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

ADDS * DL_UserInterface ( SLNG * sl_errchk , SCHR * sc_filename ) {

    /* 変数宣言 ------------------------------------------------------------ */
    SLNG   sl_filesize = 0;
    SLNG   sl_listnum  = 0;
    SCHR * sc_memp  = 0;
    ADDS * ad_pt    = 0;

    sc_memp = DL_MemoryWrite( sl_errchk , & sl_filesize , sc_filename );
    ad_pt   = DL_ListWrite  ( sl_errchk , sc_memp , & sl_listnum );

    DL_ListPrint( ad_pt );

    return 0;

}

SLNG  DL_ListPrint ( ADDS * ad_pt ) {

    printf ( "　氏名 : %s\n" , ad_pt -> sc_name );
    printf ( "　かな : %s\n" , ad_pt -> sc_kname );
    printf ( "　性別 : %c\n" , ad_pt -> sc_sex );
    printf ( "　血液 : %c\n" , ad_pt -> sc_blood );
    printf ( "誕生日 : %s\n" , ad_pt -> sc_birthday );
    printf ( "配偶者 : %c\n" , ad_pt -> sc_merry );
    printf ( "　年齢 : %hhd\n" , ad_pt -> sc_age );
    printf ( "　携帯 : %s\n" , ad_pt -> sc_mphone );
    printf ( "メール : %s\n" , ad_pt -> sc_mailadds );
    printf ( "　郵便 : %s\n" , ad_pt -> sc_post );
    printf ( "　住所 : %s\n" , ad_pt -> sc_sadds );
    printf ( "　小遣 : %d\n" , ad_pt -> sl_money );

    return 0;
}

/* ------------------------------------------------------------------------- */
/* 関数名   : DL_MemoryWrite                                                 */
/* 機能名   : ファイルを読み込み                                             */
/* 機能概要 : 読み込んだファイルをメモリに書き込み                           */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : SCHR * :  sc_filename: ファイル名                              */
/* 戻り値   : SLNG   :             : ファイルサイズ                          */
/* 作成日   : 2019/07/09       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

SCHR * DL_MemoryWrite ( SLNG * sl_errchk , SLNG * sl_filesize , SCHR * sc_filename  ) {
    
    /* 変数宣言 ------------------------------------------------------------ */
	FILE * fp          = NULL; // ファイルポインタ
    SCHR * sc_memp     = NULL; // メモリーポインタ

    fp = DL_FileOpen( sl_errchk , sc_filename ); // ファイルポインタ取得
    if ( * sl_errchk == DL_ERR ) { return 0; }  // エラーチェック

    * sl_filesize = DL_FileSize( sl_errchk , fp ); // ファイルサイズ取得

    sc_memp = ( SCHR * )calloc( ( * sl_filesize ) * 2 , sizeof( SCHR ) ); // メモリー確保

    fread( sc_memp , sizeof( SCHR ) , * sl_filesize  , fp ); // ファイル内容を読み込み
    fclose( fp );
   
    return sc_memp;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : DL_ListWrite                                                   */
/* 機能名   : ファイルの先頭ポインタ                                         */
/* 機能概要 : 移動値に応じて関数を振り分ける                                 */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : SCHR * : sc_filename : ファイル名                              */
/*          : SLNG   : sl_filesize : ファイルのビット数                      */
/* 戻り値   : ADDS * :             : メモリの先頭ポインタ                    */
/* 作成日   : 2019/07/28       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

ADDS * DL_ListWrite ( SLNG * sl_errchk , SCHR * sc_startmemp  , SLNG * sl_listnum ) {

    /* 変数宣言 ------------------------------------------------------------ */
    SLNG   sl_ptindex = 0;    
    SCHR   sc_ptflg   = 0;
    SCHR   sc_age  [__AGE_SIZE];
    SCHR   sc_money[MONEY_SIZE];
    ADDS * ad_pt;
    ADDS * new_pt;
    SCHR * sc_memp = sc_startmemp;
    SCHR i = 0;

    memset ( sc_age   , 0 , sizeof( SCHR ) * __AGE_SIZE ); // 初期化
    memset ( sc_money , 0 , sizeof( SCHR ) * MONEY_SIZE ); // 初期化

    ad_pt = ( ADDS * )calloc( 1 , sizeof( ADDS ) );

    for ( ; * ( sc_memp - 1 ) != '\n' ;  sc_memp ++ ){} // 一行目をスキップ

    // メモリに書き込み
    while ( 1 ) {
     
       // if ( * sc_memp == EOF ) { break; } // 終了判定

        // メンバー変数切り替え
        if ( * sc_memp == ',' ) {
        
            if ( sc_ptflg == 6 ) { 
            
                ad_pt -> sc_age = DL_strconv ( sl_errchk , sc_age );  // 数値変換
                memset ( sc_age , 0 , sizeof( SCHR ) * __AGE_SIZE ); // 初期化
            
            }

            sc_memp   ++; // メモリ値切り替え
            sc_ptflg  ++; // メンバー変数設定
            sl_ptindex = DL_PointMove( sl_errchk , sc_ptflg ); // メンバー変数変更
            continue; 
        
        }
        
        // 改行読み込み
        if ( * sc_memp  == '\n' ) {
            
            sc_ptflg   = 0; // メンバー変数設定
            sc_memp     ++; // 改行スキップ
            ( * sl_listnum  ) ++; // アドレス数カウント

            sl_ptindex = DL_PointMove( sl_errchk , sc_ptflg );        // メンバー変数変更
            ad_pt -> sl_money = DL_strconv ( sl_errchk , sc_money );  // 数値変換            
            memset ( sc_money , 0 , sizeof( SCHR ) * MONEY_SIZE ); // 初期化

            i++;
            if (i == 10) { break; }
            if ( * sc_memp == EOF ) { break; } // 終了判定

            new_pt = DL_NewPointer( sl_errchk ); // 格納場所取得
            ad_pt  = DL_SetPointer( sl_errchk , NULL , ad_pt , new_pt ); // 次ポインタ設定

        }

        if ( ( sc_ptflg != 11 ) && ( sc_ptflg != 6 ) ) {          * ( ad_pt -> sc_name + sl_ptindex ) = * sc_memp; } // お小遣い以外 
        if (   sc_ptflg == 11 )       { sc_money[ sl_ptindex - DL_PointMove( sl_errchk , sc_ptflg ) ] = * sc_memp; } // お小遣いの場合
        if (   sc_ptflg == 6  )       { sc_age  [ sl_ptindex - DL_PointMove( sl_errchk , sc_ptflg ) ] = * sc_memp; } // 年齢の場合
        
        sc_memp ++;    // メモリ値切り替え
        sl_ptindex ++; // 変数内ポインタ移動
        
    }

    free( sc_startmemp );

    ad_pt = DL_ListMove ( sl_errchk , ad_pt , 1 - ( * sl_listnum ) ); // 先頭ポインタに移動

    return ad_pt;

}
 
/* ------------------------------------------------------------------------- */
/* 関数名   : DL_NewPointer                                                  */
/* 機能名   : リストの結合                                                   */
/* 機能概要 : 三つのリスト順番に結合すし一番後のリストを返却                 */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : ADDS * : ad_pt1      : 先頭ポインタ                            */
/*          : ADDS * : ad_pt2      : 中心ポインタ                            */
/*          : ADDS * : ad_pt3      : 末尾ポインタ                            */
/* 戻り値   : ADDS * :             : 一番後のリストのポインタ                */
/* 作成日   : 2019/07/27       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */
 
ADDS * DL_SetPointer ( SLNG * sl_errchk , ADDS * ad_pt1 , ADDS * ad_pt2 , ADDS * ad_pt3 ) { 

    /* 引数チェック -------------------------------------------------------- */

    if ( ad_pt2 == NULL ) { 
        
        * sl_errchk = DL_ERR;
        return 0; 
    
    }

    // 前リストがある場合
    if ( ad_pt1 != NULL ) { 

        ad_pt1 -> next_pt   = ad_pt2;
        ad_pt2 -> before_pt = ad_pt1;

    }

    // 後ろリストがある場合
    if ( ad_pt3 != NULL ) {

        ad_pt2 -> next_pt   = ad_pt3;
        ad_pt3 -> before_pt = ad_pt2;

    }

    return ad_pt3;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : DL_NewPointer                                                  */
/* 機能名   : 新規リストの作成                                               */
/* 機能概要 : 新しくメモリを確保しそのポインタを返す                         */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/* 戻り値   : ADDS * :             : 新規リストのポインタ                    */
/* 作成日   : 2019/07/11       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

ADDS * DL_NewPointer ( SLNG * sl_errchk ) {

    // メモリ確保
    ADDS * new_pt;
    new_pt = ( ADDS * )calloc( 1 , sizeof( ADDS ) );
    return new_pt;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : DL_strconv                                                     */
/* 機能名   : 文字列を数値に変換                                             */
/* 機能概要 : 数字の文字列を数値に変換                                       */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : SCHR * : sc_string   : 数字の文字列                            */
/* 戻り値   : SLNG   :             : 変換後数値                              */
/* 作成日   : 2019/07/09       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

SLNG   DL_strconv ( SLNG * sl_errchk , SCHR * sc_string ) {

    /* 引数チェック ---------------------------------------------------------*/

    if ( sc_string == NULL ) { 
        
        * sl_errchk =  ErrerPrint( 001 , ( SCHR * )"DL_strconv" );
        return 0;

    }

    /* 変数宣言 ------------------------------------------------------------ */
    SLNG sl_num    = 0; // return値
    SLNG sl_index  = 0; // 文字列添え字
    SLNG sl_tencnt = 1; // 桁の重み

    // 桁の重み設定
    for ( sl_index = 1 ; sl_index < strlen ( ( char * ) sc_string ) ; sl_index ++ ) { sl_tencnt = sl_tencnt * 10; }

    // 文字列を数値に変換
    for ( sl_index = 0 ; sl_index < strlen ( ( char * ) sc_string ) ; sl_index ++ ) {
        
        sl_num += ( ( * ( sc_string + sl_index ) ) - 0x30 ) * sl_tencnt;
        sl_tencnt = sl_tencnt / 10;

    }

    return sl_num;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : DL_FileOpen                                                    */
/* 機能名   : ファイルの先頭ポインタ                                         */
/* 機能概要 : 移動値に応じて関数を振り分ける                                 */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : SCHR * : asc_filename: ファイル名                              */
/* 戻り値   : FILE * :             : ファイルポインタ                        */
/* 作成日   : 2019/07/09       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

FILE * DL_FileOpen ( SLNG * sl_errchk , SCHR * sc_filename ) {
    
    /* 引数チェック ---------------------------------------------------------*/

    if ( sc_filename == NULL ) {
    
        * sl_errchk = ErrerPrint( 001 , ( SCHR * )"DL_FileOpen" );
        return 0;
    
    } 

    /* 変数宣言 ------------------------------------------------------------ */
    errno_t	  error	= NULL;     // エラーチェック
	FILE    * fp    = NULL;     // ファイルポインタ

    error = fopen_s( &fp , ( char * ) sc_filename , "r" ); // ファイルオープン
    if ( error != NULL ) { * sl_errchk = ErrerPrint( 002 , ( SCHR * )"DL_FileOpen" ); } // エラーチェック

    return fp;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : DL_FileSize                                                    */
/* 機能名   : ファイルのサイズを調べる                                       */
/* 引数     : FILE * : fp          : 調査対象ファイルのポインタ              */
/* 戻り値   : SLNG   :             : ファイルのサイズ                        */
/* 作成日   : 2019/07/09       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

SLNG   DL_FileSize ( SLNG * sl_errchk , FILE * fp ) {

    SLNG sl_filesize;

    // fpがNULLポインタの時
    if ( fp == NULL ){ 
         
        * sl_errchk = ErrerPrint( 002 , ( SCHR * )"DL_FileSize" );
        return 0;

    }

    fseek  ( fp , 0 , SEEK_END );
    sl_filesize = ftell( fp );
    fseek  ( fp , 0 , SEEK_SET );

    return sl_filesize;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : DL_PointMove                                                   */
/* 機能名   : リストポインタの移動                                           */
/* 機能概要 : 移動値に応じて関数を振り分ける                                 */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : ADDS * : ad_pt       : 移動前 ポインタ                         */
/*          : SLNG   : sl_movenum  : ポインタ移動数                          */
/* 戻り値   : ADDS * :             : 移動後 ポインタ                         */
/* 作成日   : 2019/07/09       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

SLNG   DL_PointMove ( SLNG * sl_errchk , SLNG sl_listmember ) {

    SLNG sl_ptindex = 0; // メンバー変数へのアクセス
    
    // ポインタの値取得
    switch ( sl_listmember ) {
    
        case 11 : sl_ptindex += SADDS_SIZE;     // お小遣い
        case 10 : sl_ptindex += _POST_SIZE;     // 住所
        case  9 : sl_ptindex += MADDS_SIZE;     // 郵便番号
        case  8 : sl_ptindex += PHONE_SIZE;     // メールアドレス
        case  7 : sl_ptindex += sizeof( char ); // 携帯電話番号
        case  6 : sl_ptindex += sizeof( char ); // 年齢
        case  5 : sl_ptindex += _BDAY_SIZE;     // 配偶者
        case  4 : sl_ptindex += sizeof( char ); // 誕生日
        case  3 : sl_ptindex += sizeof( char ); // 血液型
        case  2 : sl_ptindex += KNAME_SIZE;     // 性別
        case  1 : sl_ptindex += _NAME_SIZE;     // かな
        case  0 : break;                        // 氏名

        default : * sl_errchk = ErrerPrint( 002 , ( SCHR * )"DL_PointMove" );
                  return 0;
    
    }

    return sl_ptindex;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : ErrerPrint                                                     */
/* 機能名   : エラー番号の出力                                               */
/* 引数	    : SLNG   : sl_errnum   : エラー番号                              */
/* 戻り値   : SLNG   : 異常値      : DL_ERR                                  */
/* 作成日   : 2019/07/28       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

SLNG   ErrerPrint ( SLNG sl_errnum , SCHR * sc_errstr ) {

    printf( "errernumber[%03d]\n%s\n" , sl_errnum , sc_errstr ); // エラー出力
    return DL_ERR;

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */