/* ------------------------------------------------------------------------- */
/*                                                                           */
/* 画像装飾システム                                                          */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  番号    更新内容                                更新日      名前         */
/* ------------------------------------------------------------------------- */
/* 000000   新規作成                                2019/07/30  西岡  和輝   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル                                                           */
/* ------------------------------------------------------------------------- */

#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* ------------------------------------------------------------------------- */
/* 定数定義	                                                                 */
/* ------------------------------------------------------------------------- */

#define BM_OK  1
#define BM_NG -1

#define BM_01  1
#define BM_08  8
#define BM_24 24
#define BM_32 32

/* ------------------------------------------------------------------------- */
/* typedef宣言                                                               */
/* ------------------------------------------------------------------------- */

typedef signed   int   SINT;
typedef unsigned int   UINT;
typedef signed   long  SLNG;
typedef unsigned long  ULNG;
typedef signed   short SSHT;
typedef unsigned short USHT;
typedef signed   char  SCHR;
typedef unsigned char  UCHR;

/* ------------------------------------------------------------------------- */
/* 構造体定義                                                                */
/* ------------------------------------------------------------------------- */

// 1bitカラー
typedef struct color {

    UCHR          uc_Color; // 色ドット
    struct color * Prev_pt; // 前ドット
    struct color * Next_pt; // 次ドット

}CL01;

// 8bitカラー
typedef struct color {

    UCHR          uc_Color; // 色ドット
    struct color * Prev_pt; // 前ドット
    struct color * Next_pt; // 次ドット

}CL08;


// 24bitカラー
typedef struct color {

    UCHR      uc_Rcolor;    // 赤
    UCHR      uc_Gcolor;    // 緑
    UCHR      uc_Bcolor;    // 青
    struct color * Prev_pt; // 前ドット
    struct color * Next_pt; // 次ドット

}CL24;


// 32bitカラー
typedef struct color {

    UCHR      uc_Rcolor;    // 赤
    UCHR      uc_Gcolor;    // 緑
    UCHR      uc_Bcolor;    // 青
    UCHR      uc_Reserve;   // 予約領域
    struct color * Prev_pt; // 前ドット
    struct color * Next_pt; // 次ドット

}CL32;

// BMP情報
typedef struct BMP {

    SLNG   sl_Width;    // 横
    SLNG   sl_Height;   // 縦
    UCHR   uc_Bitcnt;   // 色ビット数    
    void * Imagedata;   // 画像データ

}BMPF;

/* ------------------------------------------------------------------------- */
/* プロトタイプ宣言                                                          */
/* ------------------------------------------------------------------------- */

/* 関数宣言 ---------------------------------------------------------------- */
SLNG   BM_BmpFormatConv ( SLNG * , BMPF * , UCHR   );
SLNG   ErrerPrint       ( SLNG   , SCHR * );

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */