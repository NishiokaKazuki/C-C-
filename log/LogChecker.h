/* -------------------------------------------------------------------------- */
/* LogChecher.h         													  */
/* �b�k�Q�P																	  */
/* ���O�Ǘ��V�X�e���Ɋւ���w�b�_���                						  */
/* -------------------------------------------------------------------------- */
/* �ԍ�		�X�V����								���t		����		  */
/* -------------------------------------------------------------------------- */
/* 000000	�V�K�쐬								2019/05/08	����  ����	  */
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
/* typedef�錾																  */
/* -------------------------------------------------------------------------- */
typedef char           SCHR;					/* signed   char�^			  */
typedef unsigned char  UCHR;					/* unsigned char�^			  */
typedef short          SSHT;					/* signed   short�^			  */
typedef unsigned short USHT;					/* unsigned short�^			  */
typedef long           SLNG;					/* signed   long�^			  */
typedef unsigned long  ULNG;					/* unsigned long�^			  */
typedef int            SINT;					/* signed   int�^			  */
typedef unsigned int   UINT;					/* unsigned int�^			  */

/* -------------------------------------------------------------------------- */
/* define�錾																  */
/* -------------------------------------------------------------------------- */
#define LC_OK              (    0 )				/* ����I��					  */
#define LC_NG              (   -1 )				/* ���s						  */
#define LC_PARAM           (   -2 )				/* �����G���[				  */

/* �\���������Ȃ����O�̒�`���R�����g�A�E�g */
#define Windows                                 /* windows���ۂ�              */
#define NORMALLOG_DEFINE                        /* �ʏ탍�O�\����           */
#define ERRERLOG_DEFINE                         /* �G���[���O�\����         */
#define TRACELOG_DEFINE                         /* �g���[�X���O�\����       */
#define PERFORMANCELOG_DEFINE                   /* �p�t�H�[�}���X���O�\���� */

/* �\�����O�̎w�� */
#define NORMALLOG          (    0 )             /* �ʏ탍�O                   */
#define ERRERLOG           (    1 )             /* �G���[���O                 */
#define TRACELOG           (    2 )             /* �g���[�X���O               */
#define PERFORMANCELOG     (    3 )             /* �p�t�H�[�}���X���O         */

#endif /* _LOGCHECKER_ */

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾                                                          */
/* ------------------------------------------------------------------------- */
SCHR Normal    ( const char * );
SCHR Trace     ( const char * );
SCHR Perform   ( );


/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */