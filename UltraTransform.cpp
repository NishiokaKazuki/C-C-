/* ------------------------------------------------------------------------- */
/*                                                                           */
/* BMPbitカラー変換                                                          */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  番号    更新内容                                更新日      名前         */
/* ------------------------------------------------------------------------- */
/* 000000   新規作成                                2019/07/30  西岡  和輝   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル                                                           */
/* ------------------------------------------------------------------------- */

#include "system.h"
#include "UltraTransform.h"

UltraTransform:: UltraTransform() { printf("UltraTransform読み込み\n"); }
UltraTransform::~UltraTransform() { printf("UltraTransform終了\n");     }

/* ------------------------------------------------------------------------- */
/* 関数名   : BM_BmpFormatConv                                               */
/* 機能名   : BMPbitcolorの変換                                              */
/* 機能概要 : 指定された色ビット数に変換する関数の呼出                       */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : SCHR * :  sc_filename: ファイル名                              */
/* 戻り値   : SLNG   :             : ファイルサイズ                          */
/* 作成日   : 2019/07/09       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

SLNG   UltraTransform::BM_BmpFormatConv ( SLNG * sl_Errchk , BMPF * Filedata , UCHR uc_Bitcnt ) {

    /* 引数チェック -------------------------------------------------------- */
    // NULLポインタの場合
    if ( Filedata == NULL ) {
    
        * sl_Errchk = ErrerPrint ( 1 , ( SCHR * ) "BM_BmpFormatConv" );
        return 0;

    }

    // データが存在しない場合
    if ( Filedata -> sl_Height == 0 || 
         Filedata -> sl_Width  == 0 ) {
    
        * sl_Errchk = ErrerPrint ( 2 , ( SCHR * ) "aa" );
        return 0;
    
    } 

    // 32ビットじゃない時
    if ( uc_Bitcnt != BM_32 ) { 

        BM_BmpFormatConv ( sl_Errchk , Filedata , BM_32 );
        if ( * sl_Errchk == BM_NG ) { return 0; } // エラーチェック

    }

    // 変換後のビット数が変わらない場合
    if ( Filedata -> uc_Bitcnt == uc_Bitcnt ) { return 0; }

    /* 変数宣言 ------------------------------------------------------------ */
    ULNG   ul_Index    = 0;                       // 画像データの現在位置
    ULNG   ul_Datasize = 0;                       // 画像データビット数
    void * Curr_pt     = NULL;                    // 1bit現在カラーポインタ
    void * New_pt      = NULL;                    // 1bit次カラーポインタ
    void * void_pt     = Filedata -> Imagedata;   // 32bitカラーポインタ

    ul_Datasize = ( Filedata -> sl_Height ) * ( Filedata -> sl_Width ); // データサイズ取得

    Curr_pt = BM_ImageNewPointer ( sl_Errchk , uc_Bitcnt );             // 先頭ポインタ取得
    if ( * sl_Errchk == BM_NG ) { return 0; } // エラーチェック
    
    Filedata -> Imagedata = Curr_pt;

    // 全データ変換終了までループ
    for ( ul_Index = 0 ; ul_Index < ul_Datasize ; ul_Index ++ ) {

        // 指定された色ビット数に応じて分岐
        switch ( uc_Bitcnt ) {
    
            case BM_01 : BM_1BitColorConv  ( sl_Errchk , ( CL01 * )Curr_pt , ( CL32 * ) void_pt );              //  1bit
                         break;
            case BM_08 : BM_8BitColorConv  ( sl_Errchk , ( CL08 * )Curr_pt , ( CL32 * ) void_pt );              //  8bit
                         break;
            case BM_24 : BM_24BitColorConv ( sl_Errchk , ( CL24 * )Curr_pt , ( CL32 * ) void_pt );              // 24bit
                         break;
            case BM_32 : BM_32BitColorConv ( sl_Errchk , ( CL32 * )Curr_pt , void_pt , Filedata -> uc_Bitcnt ); // 24bit
                         break;
            default    : * sl_Errchk = ErrerPrint ( 3 , ( SCHR * ) "aa" );    // 異常値
                         return 0;

        }
        if ( * sl_Errchk == BM_NG ) { return 0; } // エラーチェック

        // 色ビット数で分岐 メモリ解放
        if ( uc_Bitcnt == 32 ) {
 
            switch ( Filedata -> uc_Bitcnt ) {
    
                // 1bit
                case BM_01 : {
                                 CL01 * New_pt1 = ( CL01 * ) void_pt; 
                                 if ( ( New_pt1 -> Next_pt ) == NULL ) { break; }// NULLポインタかチェック
                                 void_pt = New_pt1 -> Next_pt;
                                 free ( New_pt1 -> Prev_pt );
                             }
                             break;

                // 8bit
                case BM_08 : {
                                 CL08 * New_pt2 = ( CL08 * )void_pt;
                                 if ( ( New_pt2 -> Next_pt ) == NULL ) { break; }// NULLポインタかチェック
                                 void_pt = New_pt2 -> Next_pt;
                                 free ( New_pt2 -> Prev_pt );
                             }

                             break;

                // 24bit
                case BM_24 : {
                                 CL24 * New_pt3 = ( CL24 * )void_pt;
                                 if ( ( New_pt3 -> Next_pt ) == NULL ) { break; }// NULLポインタかチェック
                                 void_pt = New_pt3 -> Next_pt;
                                 free ( New_pt3 -> Prev_pt );
                             }

                             break;

                default    : * sl_Errchk = ErrerPrint ( 2 , ( SCHR * ) "BM_BmpFormatConv" );
                             return 0;

            }

        }
        else {
                
            CL32 * Curr_pt32 = ( CL32 * )void_pt;

            if ( ( Curr_pt32 -> Next_pt ) == NULL ) { break; }// NULLポインタかチェック
        
            void_pt = Curr_pt32 -> Next_pt;
            free ( Curr_pt32 -> Prev_pt );
        
        }

        New_pt = BM_ImageNewPointer ( sl_Errchk , uc_Bitcnt );
        if ( * sl_Errchk == BM_NG ) { return 0; } // エラーチェック
        
        BM_ImageSetPointer ( sl_Errchk , Curr_pt , New_pt , uc_Bitcnt );
        if ( * sl_Errchk == BM_NG ) { return 0; } // エラーチェック

        Curr_pt = New_pt;

    }

    free( void_pt );

    Filedata -> uc_Bitcnt = uc_Bitcnt; // 色ビット数変更

    return 0;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : BM_1BitColorConv                                               */
/* 機能名   : 1bitカラー変換                                                 */
/* 機能概要 : 32bitカラーを1bitカラーに変換                                  */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : CL01 * : Curr_pt01   : 1bitカラー格納                          */
/*          : CL32 * : Curr_pt32   : 32bitカラー変換元                       */
/* 戻り値   : void * : 正常値      : 0                                       */
/* 作成日   : 2019/07/30       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

void * UltraTransform::BM_1BitColorConv  ( SLNG * sl_Errchk , CL01 * Curr_pt01 , CL32 * Curr_pt32 ) {

    /* 引数チェック -------------------------------------------------------- */

    // NULLポインタの場合
    if ( Curr_pt32 == NULL ||
         Curr_pt01 == NULL ) {
    
        * sl_Errchk = ErrerPrint ( 1 , ( SCHR * ) "BM_1BitColorConv" );
        return 0;

    }

    /* 変数宣言 ------------------------------------------------------------ */

    USHT us_Addition = 0; // 32ビットカラーRGBの合算値

    us_Addition = ( Curr_pt32 -> uc_Rcolor ) + ( Curr_pt32 -> uc_Gcolor ) + ( Curr_pt32 -> uc_Bcolor );

    if ( us_Addition > 0x017E ) { Curr_pt01 -> uc_Color = 0xFF; } // 白判定
    else                        { Curr_pt01 -> uc_Color = 0x00; } // 黒判定

    return 0;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : BM_8BitColorConv                                               */
/* 機能名   : 8bitカラー変換                                                 */
/* 機能概要 : 32bitカラーを8bitカラーに変換                                  */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : CL01 * : Curr_pt08   : 8bitカラー格納                          */
/*          : CL32 * : Curr_pt32   : 32bitカラー変換元                       */
/* 戻り値   : void * : 正常値      : 0                                       */
/* 作成日   : 2019/07/31       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

void * UltraTransform::BM_8BitColorConv  ( SLNG * sl_Errchk , CL08 * Curr_pt08 , CL32 * Curr_pt32 ) {

    /* 引数チェック -------------------------------------------------------- */

    // NULLポインタの場合
    if ( Curr_pt08 == NULL ||
         Curr_pt32 == NULL ) {
    
        * sl_Errchk = ErrerPrint ( 1 , ( SCHR * ) "BM_8BitColorConv" );
        return 0;

    }

    Curr_pt08 -> uc_Color += ( Curr_pt32 -> uc_Rcolor ) * RED__; // 赤
    Curr_pt08 -> uc_Color += ( Curr_pt32 -> uc_Gcolor ) * BLUE_; // 青
    Curr_pt08 -> uc_Color += ( Curr_pt32 -> uc_Bcolor ) * GREEN; // 緑

    return 0;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : BM_24BitColorConv                                              */
/* 機能名   : 24bitカラー変換                                                */
/* 機能概要 : 32bitカラーを24bitカラーに変換                                 */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : CL24 * : Curr_pt24   : 24bitカラー格納                         */
/*          : CL32 * : Curr_pt32   : 32bitカラー変換元                       */
/* 戻り値   : void * : 正常値      : 0                                       */
/* 作成日   : 2019/07/31       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

void * UltraTransform::BM_24BitColorConv  ( SLNG * sl_Errchk , CL24 * Curr_pt24 , CL32 * Curr_pt32 ) {

    /* 引数チェック -------------------------------------------------------- */

    // NULLポインタの場合
    if ( Curr_pt24 == NULL ||
         Curr_pt32 == NULL ) {
    
        * sl_Errchk = ErrerPrint ( 1 , ( SCHR * ) "BM_24BitColorConv" );
        return 0;

    }

    Curr_pt24 -> uc_Rcolor = Curr_pt32 -> uc_Rcolor; // 赤
    Curr_pt24 -> uc_Gcolor = Curr_pt32 -> uc_Gcolor; // 青
    Curr_pt24 -> uc_Bcolor = Curr_pt32 -> uc_Bcolor; // 緑

    return 0;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : BM_32BitColorConv                                              */
/* 機能名   : 32bitカラー変換                                                */
/* 機能概要 : 1/8/24bitカラーを32bitカラーに変換                             */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : CL32 * : Curr_pt32   : 32bitカラー格納                         */
/*          : void * : void_pt     : 1/8/24bitカラー変換元                   */
/*          : UCHR   : uc_Bitcnt   : 変換元色bit数                           */
/* 戻り値   : void * : 正常値      : 0                                       */
/* 作成日   : 2019/07/31       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

void * UltraTransform::BM_32BitColorConv  ( SLNG * sl_Errchk , CL32 * Curr_pt32 , void * void_pt , UCHR uc_Bitcnt ) {

    /* 引数チェック -------------------------------------------------------- */

    // NULLポインタの場合
    if ( Curr_pt32 == NULL ||
         void_pt   == NULL ) {
    
        * sl_Errchk = ErrerPrint ( 1 , ( SCHR * ) "BM_32BitColorConv" );
        return 0;

    }

       // 色ビット数で分岐
    switch ( uc_Bitcnt ) {
    
        // 1bit
        case BM_01 : {
                         CL01 * Curr_pt01 = ( CL01 * )void_pt;
                         if ( Curr_pt01 -> uc_Color == 0xFF ) { Curr_pt32 -> uc_Rcolor = Curr_pt32 -> uc_Gcolor = Curr_pt32 -> uc_Bcolor = 0xFF; }
                         else                                 { Curr_pt32 -> uc_Rcolor = Curr_pt32 -> uc_Gcolor = Curr_pt32 -> uc_Bcolor = 0x00; }
                     }
                     break;

        // 8bit
        case BM_08 : {
                         CL08 * Curr_pt08 = ( CL08 * )void_pt;
                         Curr_pt32 -> uc_Rcolor = Curr_pt08 -> uc_Color / RED__;
                         Curr_pt32 -> uc_Gcolor = Curr_pt08 -> uc_Color / BLUE_;
                         Curr_pt32 -> uc_Bcolor = Curr_pt08 -> uc_Color / GREEN;
                     }
                     break;

        // 24bit
        case BM_24 : {
                         CL24 * Curr_pt24 = ( CL24 * )void_pt;
                     
                         Curr_pt32 -> uc_Rcolor = Curr_pt24 -> uc_Rcolor;
                         Curr_pt32 -> uc_Gcolor = Curr_pt24 -> uc_Gcolor;
                         Curr_pt32 -> uc_Bcolor = Curr_pt24 -> uc_Bcolor;
                     }

                     break;

        default    : * sl_Errchk = ErrerPrint ( 2, ( SCHR * ) "aa" ); // 異常値

    }

    return 0;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : BM_ImageNewPointer                                             */
/* 機能名   : 新規リストの確保                                               */
/* 機能概要 : uc_Bitcntの値に応じて新規リストの確保                          */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : UCHR   : uc_Bitcnt   : 色ビット数                              */
/* 戻り値   : void * : New_pt      : 確保したリストのポインタ                */
/* 作成日   : 2019/07/30       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

void * UltraTransform::BM_ImageNewPointer ( SLNG * sl_Errchk , UCHR uc_Bitcnt ) {
    
    /* 変数宣言 ------------------------------------------------------------ */
    void * New_pt;

    // 色ビット数で分岐
    switch ( uc_Bitcnt ) {
    
        case BM_01 : New_pt = calloc ( 1 , sizeof( CL01 ) ); //  1bit
                     break;
        case BM_08 : New_pt = calloc ( 1 , sizeof( CL08 ) ); //  8bit
                     break;
        case BM_24 : New_pt = calloc ( 1 , sizeof( CL24 ) ); // 24bit
                     break;
        case BM_32 : New_pt = calloc ( 1 , sizeof( CL32 ) ); // 32bit
                     break;
        default    : * sl_Errchk = ErrerPrint ( 1, ( SCHR * ) "aa" ); // 異常値
                     return 0;

    }

    return New_pt;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : BM_ImageSetPointer                                             */
/* 機能名   : リストの方向の設定                                             */
/* 機能概要 : 二つのリストの方向の設定                                       */
/* 引数	    : SLNG * : sl_errchk   : エラー確認                              */
/*          : void * : Curr_pt1    : 前リスト                                */
/*          : void * : Curr_pt2    : 後リスト                                */
/*          : UCHR   : uc_Bitcnt   : 色ビット数                              */
/* 戻り値   : SLNG   :             : 適当                                    */
/* 作成日   : 2019/07/30       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

SLNG   UltraTransform::BM_ImageSetPointer ( SLNG * sl_Errchk , void * Curr_pt1 , void * Curr_pt2 , UCHR uc_Bitcnt ) {
    
    /* 引数チェック -------------------------------------------------------- */

    // NULLポインタの場合
    if ( Curr_pt1 == NULL ||
         Curr_pt2 == NULL    ) {
    
        * sl_Errchk = ErrerPrint ( 1 , ( SCHR * ) "BM_ImageSetPointer" );
        return 0;

    } 

    // 色ビット数で分岐
    switch ( uc_Bitcnt ) {
    
        // 1bit
        case BM_01 : {
                         CL01 * New_pt1 = ( CL01 * )Curr_pt1;
                         CL01 * New_pt2 = ( CL01 * )Curr_pt2;

                         New_pt1 -> Next_pt = New_pt2;
                         New_pt2 -> Prev_pt = New_pt1;
                     }
                     break;

        // 8bit
        case BM_08 : {
                         CL08 * New_pt3 = ( CL08 * )Curr_pt1;
                         CL08 * New_pt4 = ( CL08 * )Curr_pt2;

                         New_pt3 -> Next_pt = New_pt4;
                         New_pt4 -> Prev_pt = New_pt3;
                     }
                     break;

        // 24bit
        case BM_24 : {
                         CL24 * New_pt5 = ( CL24 * )Curr_pt1;
                         CL24 * New_pt6 = ( CL24 * )Curr_pt2;

                         New_pt5 -> Next_pt = New_pt6;
                         New_pt6 -> Prev_pt = New_pt5;
                     }

                     break;

        // 32bit
        case BM_32 : {
                         CL32 * New_pt7 = ( CL32 * )Curr_pt1;
                         CL32 * New_pt8 = ( CL32 * )Curr_pt2;

                         New_pt7 -> Next_pt = New_pt8;
                         New_pt8 -> Prev_pt = New_pt7;
                     }

                     break;

        default    : * sl_Errchk = ErrerPrint ( 2, ( SCHR * ) "aa" ); // 異常値

    }

    return 0;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : ErrerPrint                                                     */
/* 機能名   : エラー出力                                                     */
/* 引数	    : SLNG * : sl_Errnum   : エラー番号                              */
/*          : SCHR * : sc_Errstr   : エラー文字列                            */
/* 戻り値   : SLNG   :             : ファイルサイズ                          */
/* 作成日   : 2019/07/30       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */

SLNG ErrerPrint ( SLNG sl_Errnum , SCHR * sc_Errstr ) {

    printf( "errernumber[%03d]\n %s\n " , sl_Errnum , sc_Errstr );
    return BM_NG;
}


/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */