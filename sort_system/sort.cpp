/* ------------------------------------------------------------------------- */
/* main.cpp																	 */
/* ＣＬ２１																	 */
/* １０万件ソート									 						 */
/*																			 */
/* ------------------------------------------------------------------------- */
/* 	番号	更新内容								更新日		名前		 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成								2019/04/24	西岡　和輝	 */
/* 000001	関数作成								2019/05/10	西岡　和輝	 */
/* 000002	画面作成								2019/05/12	西岡　和輝	 */
/* 000003	ファイル出力作成						2019/05/13	西岡　和輝	 */
/* 000004	昇順降順作成							2019/05/13	西岡　和輝	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル															 */
/* ------------------------------------------------------------------------- */
#include<windows.h>								/* ＯＳ機能関連				 */
#include<stdio.h>								/* 標準Ｉ／Ｏ				 */
#include<string.h>

/* ------------------------------------------------------------------------- */
/* 定数定義																	 */
/* ------------------------------------------------------------------------- */
#define AddressNumber 105000 /* アドレスデータ件数							 */


/* ------------------------------------------------------------------------- */
/* 構造体定義																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* typedef宣言																 */
/* ------------------------------------------------------------------------- */
typedef unsigned long  ULNG;
typedef unsigned short USHT;
typedef unsigned char  UCHR;
typedef signed   long  SLNG;
typedef signed   char  SCHR;

/* アドレス帳格納構造体														 */
typedef	struct Addres_Data {

	UCHR	name[15];			/* 氏名										 */
	UCHR	fname[11];			/* 苗字(カナ)								 */
	UCHR	mname[15];			/* 名前(カナ)								 */
	UCHR	sex[2];				/* 性別										 */
	UCHR	b_type[2];			/* 血液型									 */
	UCHR	birthday[11];		/* 誕生日									 */
	UCHR	phone[14];			/* 電話番号									 */
	UCHR	sphone[14];			/* 携帯番号									 */
	UCHR	maleadd[39];		/* メールアドレス							 */
	UCHR	post[9];			/* 郵便番号									 */
	UCHR	s_address[101];		/* 住所										 */
	UCHR	s_k_address[71];	/* 住所(カナ)								 */

}ADDRESS;

ADDRESS *MDp[AddressNumber];

/* ------------------------------------------------------------------------- */
/* プロトタイプ宣言															 */
/* ------------------------------------------------------------------------- */
ADDRESS Main_Data[AddressNumber];
UCHR	SS_Input			( UCHR* );
void	SS_FileOpen			( UCHR* , SCHR* );
void	SS_FileWrite		( void );
void	SS_FileRead			( UCHR* );
void	SS_QuickSort3		( ULNG , ULNG , UCHR , UCHR , UCHR );
void	SS_QuickSort2		( ULNG , ULNG , UCHR , UCHR );
void	SS_QuickSort1		( ULNG , ULNG , UCHR );
UCHR	SS_Convertion		( USHT );
void	SS_charchenge		( UCHR* , ULNG );
ULNG	SS_SortChange		( ULNG , UCHR );

/* ------------------------------------------------------------------------- */
/* 関数名	: main			 												 */
/* 機能名	: エントリーポイント											 */
/* 機能概要	: 時間計測だけします。											 */
/* 作成日	: 2019/04/24		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

SINT main( SINT argc , SCHR *argv[] )
{
	DWORD			dwStartTime		= 0;
	DWORD			dwEndTime		= 0;

	UCHR			*memp			= NULL;		/* 構造体ポインタ			 */
	UCHR			us_sortrule[3]  ;			/* ソート条件				 */
	UCHR			uc_sortnum		= 0;		/* ソート条件数				 */

	memset( Main_Data , 0 , sizeof( ADDRESS ) * AddressNumber );

    if ( argc < 2 ) { return 0; }

	/* 関数呼び出し															 */
	SS_FileOpen( memp );
	
	uc_sortnum = SS_Input( us_sortrule );


	printf("ソートを開始します...\n\n");
	/* システム起動時間を取得 */
	dwStartTime = GetTickCount();

	/* ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■  */
	/* ここに処理を記述  */
	
	/* 条件数に合わせて分岐													 */
	switch (uc_sortnum) {
	
		case 1:
			SS_QuickSort1( 0 , AddressNumber - 1 , us_sortrule[0] );
			break;

		case 2:
			SS_QuickSort2( 0 , AddressNumber - 1 , us_sortrule[0] , us_sortrule[1] );
			break;

		default:
			SS_QuickSort3( 0 , AddressNumber - 1 , us_sortrule[0] , us_sortrule[1] , us_sortrule[2] );

	}

	/* ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■  */

	/* システム起動時間を取得 */
	dwEndTime = GetTickCount();

	/* 検索前と検索後の時間を引き、処理にかかった時間を表示 */
	printf("%d秒かかりました！\n\n", (dwEndTime - dwStartTime));
	SS_FileWrite(  );
	system( "pause" );
	return 0;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_Input														 */
/* 機能名	: 入力画面														 */
/* 機能概要	: 入力インターフェースを表示し、ソート条件を保存する			 */
/* 引数		: UCHR*															 */
/* 戻り値	: UCHR															 */
/* 作成日	: 2019/05/10		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

UCHR SS_Input( UCHR* uc_sortrule ){

	USHT us_sortrule[3];
	UCHR uc_index	= 0;	/* 条件数										 */

	system("cls");  /* 画面クリア											 */

	printf( "\nアドレス帳ソートプログラムを起動しました\n\n" );

	/* 条件入力完了までループ												 */
	for ( uc_index = 0 ; uc_index < 3 ; uc_index++ ) {

		/* 条件表記															 */
		printf( "1.氏名　　　　　　2.苗字(カナ)　　　　3.名前(カナ)　　　　4.性別\n\n" );
		printf( "5.血液型　　　　　6.誕生日　　　　　　7.電話番号　　　　　8.携帯番号\n\n" );
		printf( "9.メールアドレス　10.郵便番号 　　　　11.住所　　　　　　 12.住所(カナ)\n\n\n" );
		
		/* 条件入力															 */
		printf( "第%d条件を上の中から番号で選択して下さい ( 最大3条件 ) ( 終了は13 )" , uc_index + 1 );
		scanf_s( "%hd", us_sortrule + uc_index  );
		rewind( stdin );
		*( us_sortrule + uc_index ) -= 1;

		system( "cls" ); /* 画面クリア										 */

		/* 入力エラー														 */
		if ( ( *( us_sortrule + uc_index ) < 0 ) ||
			( *( us_sortrule + uc_index ) > 12 ) ) {

			printf("\n入力エラー。再入力してください\n\n");
			uc_index--;
			continue;

		}else

		/* 終了確認															 */
		if ( * ( us_sortrule + uc_index ) == 12 ) {
			
			break;

		}else

		/* 重複確認															 */
		if ( ( ( uc_index == 1 ) &&
			( *us_sortrule == *( us_sortrule + uc_index ) ) ) ||
			( ( uc_index == 2 )  && (
			( *us_sortrule == *( us_sortrule + uc_index ) ) || 
			( *( us_sortrule + 1 ) == *( us_sortrule + uc_index) )
			) ) ) {

			printf("\n条件が重複しました。再入力してください\n\n");
			uc_index --;
			continue;

		}

		printf( "\n第%d条件受付完了\n\n" , uc_index + 1 );
	}
	/* 関数呼び出し															 */
	for ( UCHR uc_index2 = 0 ; uc_index2 < 3 ; uc_index2++ ) {

		*( uc_sortrule + uc_index2 ) = SS_Convertion( *( us_sortrule + uc_index2 ) );
	
	}

	return uc_index; /* 条件数返還											 */
}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_FileOpen													 */
/* 機能名	: ファイル読み込み												 */
/* 機能概要	: ファイルを読み込み内容を動的メモリに格納する					 */
/* 引数		: UCHR* , SCHR+*												 */
/* 戻り値	: 														         */
/* 作成日	: 2019/05/13		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

void SS_FileOpen( UCHR *memp , SCHR *sc_filename ) {

	errno_t			error			= NULL;		/* エラーチェック			 */
	FILE			*fp				= NULL;		/* ファイルポインタ			 */
	ULNG			ul_filesize		= 0;		/* ファイルサイズ			 */

	/* ファイルオープン		 												 */
	
	error = fopen_s( &fp , ( char * )sc_filename , "rb" );

	/* ファイルチェック														 */
	if ( error != NULL ) {
		printf( "エラー。ファイルが見つかりません\n" );
		printf( "プログラムを終了します\n" );
		system( "pause" );
		exit( 0 );
	}

	/* ファイルサイズチェック												 */
	fseek( fp , 0 , SEEK_END );
	ul_filesize = ftell( fp );
	fseek( fp , 0 , SEEK_SET );

	/* メモリ確保															 */
	memp = ( UCHR* )malloc( ul_filesize );


	/* ファイル読み込み														 */
	fread( memp , 1 , ul_filesize , fp );
	fclose( fp );

	SS_FileRead( memp );

}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_FileRead													 */
/* 機能名	: 構造体の内容を作成											 */
/* 機能概要	: ファイルから動的メモリに読み込んだ値を構造体に格納する		 */
/* 引数		: UCHR *														 */
/* 戻り値	: 																 */
/* 作成日	: 2019/05/10		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

void SS_FileRead( UCHR *memp ) {

	UCHR			*memp2		= NULL;			/* 構造体ポインタ保管用		 */
	ULNG			ul_index	= 0;			/*	構造体添え字			 */
	UCHR			uc_index	= 0;			/*	メンバー変数添え字		 */
	UCHR			uc_flag		= 0;			/*	メンバー変数切り替え	 */
	UCHR			uc_memindex = 0;			/*	メンバー変数サイズ		 */
	
	memp2 = memp;							/* 先頭アドレスを確保			 */
	memp += 108;							/* エクセル1行目をスキップ		 */
	printf("ファイル読み込み中...\n");

	/* 構造体のアドレスを保管												 */
	for ( ul_index = 0 ; ul_index < AddressNumber ; ul_index ++) {
		
		MDp[ul_index] = &Main_Data[ul_index];
	
	}

	ul_index = 0;

	/* 全データ構造体に格納するまでまでループ								 */
	while ( 1 ) {

		/* ',' を読み込んだら次のメンバー変数へ移動							 */
		if ( *memp == ',' ) {

			memp ++;
			uc_index = 0;
			uc_flag ++;
			continue;

		}

		/* 改行読み込み														 */
		else
		if ( *memp == 13 && *( memp + 1 ) == 10 ) {
			uc_index	  = 0;
			uc_flag		  = 0;
			ul_index ++;
			
			/* 終了判定														 */
			if ( ul_index == AddressNumber ) {
				printf( "ファイル読み込み完了\n" );
				break;
			}

			/* 先頭のメンバー変数へ移動										 */
			while ( *( memp - 1 ) != ',' ) {
				memp ++;
			}

		}
		

		/* メンバー変数を切り替え											 */
		uc_memindex = SS_Convertion ( uc_flag );

		if ( ( uc_flag == 5 ) &&
			( ( uc_index == 5 ) || ( uc_index == 8 ) ) ) {

			if ( ( *( memp + 1 ) == '/' ) ||
				 ( *( memp + 1 ) == ',' ) ) {

				*( MDp[ul_index]->name + ( uc_memindex + uc_index ) ) = '0';
				uc_index ++;

			}

		}

		/* データを１文字構造体へ格納										 */
		* ( MDp[ul_index] ->name + ( uc_memindex + uc_index ) ) = *memp;
		uc_index++;
		memp ++;
	}

	free( memp2 );

}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_FileWrite													 */
/* 機能名	: 構造体の内容を作成											 */
/* 機能概要	: ファイルから動的メモリに読み込んだ値を構造体に格納する		 */
/* 引数		:       														 */
/* 戻り値	: 																 */
/* 作成日	: 2019/05/13		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

void SS_FileWrite ( void ){

	ULNG			ul_loop			= 0;		/* ループ回数				 */
	ULNG			ul_index		= 0;		/* 構造体の添え字			 */
	errno_t			error			= NULL;		/* エラーチェック			 */
	FILE			*fp				= NULL;		/* ファイルポインタ			 */
	UCHR			uc_filename[80];			/* ファイル名格納			 */
	UCHR			uc_num[7]		=			/* 先頭の数字				 */
		  { 0 , 0 , 0 , 0 , 0 , 0 , 0 };
	UCHR			uc_index		= 0;		/* ファイル添え字			 */
	UCHR			uc_mem			= 0;		/* メモリー偏差				 */
	UCHR			uc_sort			= 0;		/* ポインタ切り替え			 */
	UCHR			uc_change		= 0;

	/* インクリメントした数字を末尾にした未作成ファイルの探索				 */
	for ( uc_index = 0 ; uc_index < 100 ; uc_index ++ ) {
		
		/* 作成済みかチェック												 */
		sprintf_s( ( char * ) uc_filename, sizeof( UCHR ) * 80 , "XXX%02d.csv" , uc_index );
		error = fopen_s( &fp , ( char * ) uc_filename , "r" );

		/* 未作成ファイル発見    											 */
		if ( error != NULL ) {
			sprintf_s( ( char * )uc_filename , sizeof( UCHR ) * 80 , "XXX%02d.csv" , uc_index );
			error = fopen_s( &fp , ( char * )uc_filename , "wb+" );
			break;
		}

	}

	printf( "昇順降順を選択して下さい（ 昇順:1 , 降順:0 )" );
	scanf_s( "%c" , &uc_change );
	rewind( stdin );

	uc_change -= 48;

	printf("\n書き込みを開始します...\n\n");

	/* エクセル１行目														 */
	fprintf( fp , "No,氏名,カナ(苗字),カナ(名前),性別,血液型,生年月日,電話番号,携帯電話,メールアドレス,〒,住所,住所（カナ）\r\n"  );
	
	/* 全データをファイルに書き込むまでループ								 */
	for ( ul_loop = 0 ; ul_loop < AddressNumber; ul_loop ++ ) {

		ul_index = SS_SortChange( ul_loop , uc_change );
		SS_charchenge( uc_num , ul_loop + 1  );

		/* 先頭の数字の格納													 */
		fputs( ( char* )uc_num , fp );
		fputc( ',' , fp );

		/* 構造体一つ分のメンバー変数を格納									 */
		for ( uc_sort = 0 ; uc_sort < 12 ; uc_sort++ ) {
			
			/* メンバー変数をずらす											 */
			uc_mem = SS_Convertion( uc_sort );

			/* メンバー変数一つを格納										 */
			fputs( ( char* ) MDp[ul_index]->name + uc_mem , fp );
			
			/* 最後のメンバー変数を格納したら改行							 */
			if ( uc_sort == 11 ) {

				fputs( "\r\n" , fp );
				break;
			
			}

			/* メンバー変数区切りの,を格納									 */
			fputc(',', fp);

		}

	}

	printf("書き込み完了\n\n");
}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_charchenge													 */
/* 機能名	: 文字変換														 */
/* 機能概要	: 数字を文字コードへ変換する									 */
/* 引数		: UCHR*  : ULNG													 */
/* 戻り値	:  																 */
/* 作成日	: 2019/05/13		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

void SS_charchenge( UCHR *uc_num , ULNG ul_index ) {
	
	UCHR uc_index = 0; /* 配列をずらす値									 */

	/* 中身をリセット														 */
	memset( uc_num , 0 , sizeof( UCHR ) * 7 );

	/* 数字の桁数でけループ													 */
	for ( uc_index = 0 ; ul_index >= 1; uc_index ++ , ul_index /= 10 ) {
		
		/* 数字を一桁ずらす													 */
		for ( UCHR uc_index2 = uc_index ; uc_index2 > 0 ; uc_index2 -- ) {
		
			*( uc_num + uc_index2 ) = *( uc_num + uc_index2 - 1 );

		}

		/* 数字を格納														 */
		*uc_num = ( ul_index % 10 ) + 48;
		
	}
}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_QuickSort3													 */
/* 機能名	: クイックソート												 */
/* 機能概要	: 構造体アドレスを3条件に合わせてソートする						 */
/* 引数		: ULNG  : ULNG : UCHR : UCHR : UCHR								 */
/* 戻り値	:  																 */
/* 作成日	: 2019/05/11		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

void SS_QuickSort3( ULNG ul_start , ULNG ul_end , UCHR uc_sort1 , UCHR uc_sort2 , UCHR uc_sort3 ) {
	
	ULNG		ul_startindex	= ul_start + 1; /* 開始時の添え字の確保		 */
	ULNG		ul_endindex		= ul_end;		/* 開始時の添え字の確保		 */
	ULNG		ul_half			= ul_start;		/* ソート基準値				 */
	ADDRESS		*ul_space		= NULL;			/* アドレス避難				 */


	/* ソート開始															 */
	while ( 1 ){

		/* 基準値以上の探索													 */
		for ( ; ul_startindex < ul_endindex ; ul_startindex ++ ) {

			/* 第一条件で比較												 */
			/* 入れ替え対象発見												 */
			if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort1 ),
				( char* ) ( MDp[ul_half]->name + uc_sort1 ) ) > 0 ) {

				break;

			}

			/* 比較一致時　第二条件に遷移									 */
			if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort1 ),
				( char* ) ( MDp[ul_half]->name + uc_sort1 ) ) == 0 ) {

				/* 第二条件で比較											 */
				if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort2 ),
					( char* ) ( MDp[ul_half]->name + uc_sort2 ) ) > 0 ) {

					break;

				}

				/* 条件不一致のためループに遷移								 */
				if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort2 ),
					( char* ) ( MDp[ul_half]->name + uc_sort2 ) ) < 0 ) {

					continue;

				}

				/* 比較一致時　第三条件に遷移								 */
				else {

					/* 第三条件で比較										 */
					if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort3 ),
						( char* ) ( MDp[ul_half]->name + uc_sort3 ) ) > 0 ) {

						break;

					}
					/* 条件不一致のためループに遷移							 */
					
				}
				
			}

		}

		/* 基準値以下の探索													 */
		for ( ; ul_startindex < ul_endindex ; ul_endindex -- ) {

			/* 第一条件で比較												 */
			/* 入れ替え対象発見												 */
			if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort1 ),
				 ( char* ) ( MDp[ul_half]->name + uc_sort1 ) ) < 0 ) {

				break;

			}

			/* 比較一致時　第二条件に遷移									 */
			if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort1 ),
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) == 0 ) {

				/* 第二条件で比較											 */
				if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort2 ),
					( char* ) ( MDp[ul_half]->name + uc_sort2 ) ) < 0 ) {

					break;

				}

				/* 条件不一致のためループに遷移								 */
				if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort2 ),
					( char* ) ( MDp[ul_half]->name + uc_sort2 ) ) > 0 ) {

					continue;

				}

				/* 比較一致時　第三条件に遷移								 */
				else {

					/* 第三条件で比較										 */
					if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort3 ),
						( char* ) ( MDp[ul_half]->name + uc_sort3 ) ) <= 0 ) {

						break;

					}
					/* 条件不一致のためループに遷移							 */

				}

			}

		}

		/* 境界線を越えた場合												 */
		if ( ul_startindex >= ul_endindex ) {

		/* 基準値が全要素を超える場合										 */
			if ( ul_endindex == ul_end ) {
				
				ul_space = MDp[ul_half];
				MDp[ul_half] = MDp[ul_endindex];
				MDp[ul_endindex] = ul_space;
				break;
			
			}
			ul_endindex --;
			ul_space = MDp[ul_half];
			MDp[ul_half] = MDp[ul_endindex];
			MDp[ul_endindex] = ul_space;
			break;

		}

		/* アドレス入れ替え													 */
		else {
		
			ul_space		   = MDp[ul_startindex];
			MDp[ul_startindex] = MDp[ul_endindex];
			MDp[ul_endindex]   = ul_space;
			ul_startindex++;
			ul_endindex--;
		}

	}

	/* ソート再帰呼び出し													 */

	if ( ( long )ul_start < ( long )ul_endindex - 1) {

		SS_QuickSort3(ul_start, ul_endindex - 1, uc_sort1, uc_sort2, uc_sort3);

	}

	if ( ( long )ul_endindex + 1 < ( long )ul_end ) {
		 
		SS_QuickSort3(ul_endindex + 1, ul_end, uc_sort1, uc_sort2, uc_sort3);
	
	}
	

}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_QuickSort2													 */
/* 機能名	: クイックソート												 */
/* 機能概要	: 構造体アドレスを2条件に合わせてソートする						 */
/* 引数		: ULNG  : ULNG : UCHR : UCHR									 */
/* 戻り値	:  																 */
/* 作成日	: 2019/05/14		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */


void SS_QuickSort2( ULNG ul_start , ULNG ul_end , UCHR uc_sort1 , UCHR uc_sort2 ) {

	ULNG		ul_startindex = ul_start + 1;	/* 開始時の添え字の確保		 */
	ULNG		ul_endindex	  = ul_end;			/* 開始時の添え字の確保		 */
	ULNG		ul_half		  = ul_start;		/* ソート基準値				 */
	ADDRESS		*ul_space	  = NULL;			/* アドレス避難				 */


	/* ソート開始															 */
	while ( 1 ) {

		/* 基準値以上の探索													 */
		for ( ; ul_startindex < ul_endindex ; ul_startindex++ ) {

			/* 第一条件で比較												 */
			/* 入れ替え対象発見												 */
			if ( strcmp ( ( char* )( MDp[ul_startindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) > 0 ) {

				break;

			}

			/* 比較一致時　第二条件に遷移									 */
			if ( strcmp ( ( char* )( MDp[ul_startindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) == 0 ) {

				/* 第二条件で比較											 */
				if ( strcmp ( ( char* )( MDp[ul_startindex]->name + uc_sort2 ),
					( char* )( MDp[ul_half]->name + uc_sort2 ) ) > 0 ) {

					break;

				}

				/* 条件不一致のためループに遷移								 */

			}

		}

		/* 基準値以下の探索													 */
		for ( ; ul_startindex < ul_endindex ; ul_endindex -- ) {

			/* 第一条件で比較												 */
			/* 入れ替え対象発見												 */
			if ( strcmp ( ( char* )( MDp[ul_endindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) < 0) {

				break;

			}

			/* 比較一致時　第二条件に遷移									 */
			if ( strcmp ( ( char* )( MDp[ul_endindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) == 0 ) {

				/* 第二条件で比較											 */
				if ( strcmp ( ( char* )( MDp[ul_endindex]->name + uc_sort2 ) ,
					( char* )( MDp[ul_half]->name + uc_sort2 ) ) <= 0 ) {

					break;

				}


				/* 条件不一致のためループに遷移									 */

			}

		}


		/* 境界線を越えた場合												 */
		if ( ul_startindex >= ul_endindex ) {

			/* 基準値が全要素を超える場合										 */
			if ( ul_endindex == ul_end ) {

				ul_space		 = MDp[ul_half];
				MDp[ul_half]     = MDp[ul_endindex];
				MDp[ul_endindex] = ul_space;
				break;

			}
			ul_endindex --;
			ul_space		 = MDp[ul_half];
			MDp[ul_half]	 = MDp[ul_endindex];
			MDp[ul_endindex] = ul_space;
			break;

		}

		/* アドレス入れ替え													 */
		else {

			ul_space		    = MDp[ul_startindex];
			MDp[ul_startindex] = MDp[ul_endindex];
			MDp[ul_endindex]   = ul_space;
			ul_startindex ++;
			ul_endindex   --;
		}

	}

	/* ソート再帰呼び出し													 */

	if ( ( long )ul_start < ( long )ul_endindex - 1 ) {

		SS_QuickSort2( ul_start , ul_endindex - 1 , uc_sort1 , uc_sort2 );

	}

	if ( ( long )ul_endindex + 1 < ( long )ul_end ) {

		SS_QuickSort2( ul_endindex + 1 , ul_end, uc_sort1 , uc_sort2 );

	}


}
/* ------------------------------------------------------------------------- */
/* 関数名	: SS_QuickSort1													 */
/* 機能名	: クイックソート												 */
/* 機能概要	: 構造体アドレスを1条件に合わせてソートする						 */
/* 引数		: ULNG  : ULNG : UCHR											 */
/* 戻り値	:  																 */
/* 作成日	: 2019/05/14		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

void SS_QuickSort1( ULNG ul_start , ULNG ul_end , UCHR uc_sort1 ) {

	ULNG		ul_startindex = ul_start + 1;   /* 開始時の添え字の確保		 */
	ULNG		ul_endindex   = ul_end;			/* 開始時の添え字の確保		 */
	ULNG		ul_half		  = ul_start;		/* ソート基準値				 */
	ADDRESS		*ul_space	  = NULL;			/* アドレス避難				 */


	/* ソート開始															 */
	while (1) {

		/* 基準値以上の探索													 */
		for ( ; ul_startindex < ul_endindex ; ul_startindex ++ ) {

			/* 第一条件で比較												 */
			/* 入れ替え対象発見												 */
			if ( strcmp ( ( char* )( MDp[ul_startindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) )  > 0 ) {

				break;

			}


		}

		/* 基準値以下の探索													 */
		for ( ; ul_startindex < ul_endindex ; ul_endindex -- ) {

			/* 第一条件で比較												 */
			/* 入れ替え対象発見												 */
			if ( strcmp ( ( char* )( MDp[ul_endindex]->name + uc_sort1 ),
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) <= 0 ) {

				break;

			}

			

		}

		/* 境界線を越えた場合												 */
		if ( ul_startindex >= ul_endindex ) {

			/* 基準値が全要素を超える場合										 */
			if ( ul_endindex == ul_end ) {

				ul_space = MDp[ul_half];
				MDp[ul_half] = MDp[ul_endindex];
				MDp[ul_endindex] = ul_space;
				break;

			}
			ul_endindex--;
			ul_space = MDp[ul_half];
			MDp[ul_half] = MDp[ul_endindex];
			MDp[ul_endindex] = ul_space;
			break;

		}

		/* アドレス入れ替え													 */
		else {

			ul_space = MDp[ul_startindex];
			MDp[ul_startindex] = MDp[ul_endindex];
			MDp[ul_endindex] = ul_space;
			ul_startindex++;
			ul_endindex--;
		}

	}

	/* ソート再帰呼び出し													 */
	/* 性別の場合一回で終了													 */
	if ( ( uc_sort1 != 41 ) ) {	

		/* 要素が１より多い													 */
		if ( ( long )ul_start < ( long )ul_endindex - 1 ) {
		
			SS_QuickSort1( ul_start , ul_endindex - 1 , uc_sort1 );

		}

		/* 要素が１より多い													 */
		if ( ( long )ul_endindex + 1 < ( long )ul_end ) {

			SS_QuickSort1( ul_endindex + 1 , ul_end , uc_sort1 );

		}
	}

}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_Convertion													 */
/* 機能名	: ソート条件の変換												 */
/* 機能概要	: ソート条件に合わせてメモリの値をずらす変数の作成				 */
/* 引数		: UCHR															 */
/* 戻り値	: UCHR 															 */
/* 作成日	: 2019/05/10		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

UCHR SS_Convertion( USHT ul_origin ) {

	switch ( ul_origin ) {
	case 0:			//name[15]
		return 0;

	case 1:			//fname[11]
		return 15;

	case 2:			//mname[15]
		return 26;

	case 3:			//sex[2]
		return 41;

	case 4:			//b_type[2]
		return 43;

	case 5:			//birthday[11]
		return 45;

	case 6:			//phone[14]
		return 56;

	case 7:			//sphone[14]
		return 70;

	case 8:			//maleadd[39]
		return 84;

	case 9:			//post[9]
		return 123;

	case 10:		//s_address[101]
		return 132;

	case 11:		//s_k_address[71]
		return 233;

	default:		//条件無しの場合
		return 255;
	}
}

/* ------------------------------------------------------------------------- */
/* 関数名	: SS_SortChange													 */
/* 機能名	: ソート条件の変換												 */
/* 機能概要	: ソート条件に合わせてメモリの値をずらす変数の作成				 */
/* 引数		: UCHR															 */
/* 戻り値	: UCHR 															 */
/* 作成日	: 2019/05/10		西岡　和輝		新規作成					 */
/* ------------------------------------------------------------------------- */

ULNG SS_SortChange( ULNG ul_index , UCHR uc_change ) {

	switch ( uc_change ) {
	
	case 0: return ( AddressNumber - ul_index - 1 );

	default: return ul_index;

	}

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */