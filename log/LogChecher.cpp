/* ------------------------------------------------------------------------- */
/*                                                                           */
/* �P�O�����\�[�g                                                            */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2019/07/07  ����  �a�P   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��                                                           */
/* ------------------------------------------------------------------------- */

#include "LogChecker.h"

/* ------------------------------------------------------------------------- */
/* �萔��`	                                                                 */
/* ------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------- */
/* �\���̒�`                                                                */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* �O���[�o���ϐ�                                                            */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾                                                          */
/* ------------------------------------------------------------------------- */
SCHR LogChecker( SCHR , const char *, ... );

SCHR LogChecker( SCHR scLogType , const char * Message , ... ) {

    if ( Message == NULL ) { return LC_PARAM; }

    /* �ϐ��錾 ------------------------------------------------------------ */
    SCHR    scStr[256];							/* �ϒ�������i�[�p		 */
    va_list args;								/* �ϒ����������p			 */

    memset( scStr, 0, sizeof( scStr ));

    va_start( args, Message );					/* �ϒ����������J�n		  */
	vsprintf( scStr, Message, args );			/* �ϒ������擾			  */
	va_end( args );								/* �ϒ����������I�� 		  */

/* printf�̓��e�Ɗ֐����͓K�� */
    switch ( scLogType ) {

#ifdef _DEBUG

#ifdef NORMALLOG_DEFINE
    case NORMALLOG:
        printf( "�ʏ탂�[�h�@�@:" );
        Normal( scStr );
        break;
#endif

#ifdef TRACELOG_DEFINE
    case TRACELOG:
        printf( "�g���[�X���[�h:" );
        Trace ( scStr );
#endif

#ifdef PERFORMANCELOG_DEFINE
    case PERFORMANCELOG:
        printf( "�^�C��:" );
        Perform( );
        break;
#endif
#endif

#ifdef ERRERLOG_DEFINE
    case ERRERLOG:
        printf( "�G���[���[�h�@:" );
        Normal( scStr );
        break;
#endif

    default:
        return LC_PARAM;
    }

    return LC_OK;

}


/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */