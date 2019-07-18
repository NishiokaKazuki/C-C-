/* ------------------------------------------------------------------------- */
/* main.h                                                                    */
/* �b�k�Q�P	                                                                 */
/* �t�H���_�폜�w�b�_�[                                                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2019/06/24	�����@�a�P   */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��                                                           */
/* ------------------------------------------------------------------------- */

#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE
#include "find.h"
#include <direct.h>
#include <stdarg.h>

/* ------------------------------------------------------------------------- */
/* �萔��`	                                                                 */
/* ------------------------------------------------------------------------- */

#define FOLDER_NAME_SIZE 250
#define FILE_NAME_SIZE   256
#define STRING_SIZE FILE_NAME_SIZE

#define FD_OK  0
#define FD_ERR -1

/* ------------------------------------------------------------------------- */
/* typedef�錾                                                               */
/* ------------------------------------------------------------------------- */

typedef unsigned long  ULNG;
typedef signed   long  SLNG;
typedef unsigned short USHT;
typedef signed   short SSHT;
typedef signed   char  SCHR;
typedef unsigned char  UCHR;
typedef signed   int   SINT;

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾                                                          */
/* ------------------------------------------------------------------------- */

SLNG   FD_UserInterface ( SINT , SCHR *            );
SLNG   FD_FileSearch    ( SCHR *                   );
SLNG   FD_StrUnit       ( SCHR * , SCHR * , SCHR * );
SLNG   FD_ErrerPrint    ( SLNG                     );