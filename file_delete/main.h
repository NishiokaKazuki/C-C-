/* ------------------------------------------------------------------------- */
/* main.h                                                                    */
/* ＣＬ２１	                                                                 */
/* フォルダ削除ヘッダー                                                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  番号    更新内容                                更新日      名前         */
/* ------------------------------------------------------------------------- */
/* 000000   新規作成                                2019/06/24	西岡　和輝   */

/* ------------------------------------------------------------------------- */
/* includeファイル                                                           */
/* ------------------------------------------------------------------------- */

#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE
#include "find.h"
#include <direct.h>
#include <stdarg.h>

/* ------------------------------------------------------------------------- */
/* 定数定義	                                                                 */
/* ------------------------------------------------------------------------- */

#define FOLDER_NAME_SIZE 250
#define FILE_NAME_SIZE   256
#define STRING_SIZE FILE_NAME_SIZE

#define FD_OK  0
#define FD_ERR -1

/* ------------------------------------------------------------------------- */
/* typedef宣言                                                               */
/* ------------------------------------------------------------------------- */

typedef unsigned long  ULNG;
typedef signed   long  SLNG;
typedef unsigned short USHT;
typedef signed   short SSHT;
typedef signed   char  SCHR;
typedef unsigned char  UCHR;
typedef signed   int   SINT;

/* ------------------------------------------------------------------------- */
/* プロトタイプ宣言                                                          */
/* ------------------------------------------------------------------------- */

SLNG   FD_UserInterface ( SINT , SCHR *            );
SLNG   FD_FileSearch    ( SCHR *                   );
SLNG   FD_StrUnit       ( SCHR * , SCHR * , SCHR * );
SLNG   FD_ErrerPrint    ( SLNG                     );