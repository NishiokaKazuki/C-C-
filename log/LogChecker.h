/* -------------------------------------------------------------------------- */
/* LogChecher.h         													  */
/* ＣＬ２１																	  */
/* ログ管理システムに関するヘッダ情報                						  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴								日付		氏名		  */
/* -------------------------------------------------------------------------- */
/* 000000	新規作成								2019/05/08	桝井  隆治	  */
/* -------------------------------------------------------------------------- */
#ifndef _LOGCHECKER_
#define _LOGCHECKER_

#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>								

/* -------------------------------------------------------------------------- */
/* typedef宣言																  */
/* -------------------------------------------------------------------------- */
typedef char           SCHR;					/* signed   char型			  */
typedef unsigned char  UCHR;					/* unsigned char型			  */
typedef short          SSHT;					/* signed   short型			  */
typedef unsigned short USHT;					/* unsigned short型			  */
typedef long           SLNG;					/* signed   long型			  */
typedef unsigned long  ULNG;					/* unsigned long型			  */
typedef int            SINT;					/* signed   int型			  */
typedef unsigned int   UINT;					/* unsigned int型			  */

/* -------------------------------------------------------------------------- */
/* define宣言																  */
/* -------------------------------------------------------------------------- */
#define LC_OK              (    0 )				/* 正常終了					  */
#define LC_NG              (   -1 )				/* 失敗						  */
#define LC_PARAM           (   -2 )				/* 引数エラー				  */

/* 表示したくないログの定義をコメントアウト */
#define Windows                                 /* windowsか否か              */
#define NORMALLOG_DEFINE                        /* 通常ログ表示可否           */
#define ERRERLOG_DEFINE                         /* エラーログ表示可否         */
#define TRACELOG_DEFINE                         /* トレースログ表示可否       */
#define PERFORMANCELOG_DEFINE                   /* パフォーマンスログ表示可否 */

/* 表示ログの指定 */
#define NORMALLOG          (    0 )             /* 通常ログ                   */
#define ERRERLOG           (    1 )             /* エラーログ                 */
#define TRACELOG           (    2 )             /* トレースログ               */
#define PERFORMANCELOG     (    3 )             /* パフォーマンスログ         */

#endif /* _LOGCHECKER_ */

/* ------------------------------------------------------------------------- */
/* プロトタイプ宣言                                                          */
/* ------------------------------------------------------------------------- */
SCHR Normal    ( const char * );
SCHR Trace     ( const char * );
SCHR Perform   ( );


/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */