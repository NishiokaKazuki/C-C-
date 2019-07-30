/* ------------------------------------------------------------------------- */
/*                                                                           */
/* �摜�����V�X�e��                                                          */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2019/07/30  ����  �a�P   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��                                                           */
/* ------------------------------------------------------------------------- */

#include "system.h"

void * BM_1BitColorConv  ( SLNG * , CL01 * , CL32 * );
void * BM_8BitColorConv  ( SLNG * , CL08 * , CL32 * );
void * BM_24BitColorConv ( SLNG * , CL24 * , CL32 * );
void * BM_32BitColorConv ( SLNG * , CL32 * , BMPF * );
SLNG   BM_ImageSetPointer( SLNG * , void * , void * , UCHR   );

int main( void ) {


    
    system( "pause" );
    return 0;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : BM_BmpFormatConv                                               */
/* �@�\��   : BMPbitcolor�̕ϊ�                                              */
/* �@�\�T�v : �w�肳�ꂽ�F�r�b�g���ɕϊ�����֐��̌ďo                       */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : SCHR * :  sc_filename: �t�@�C����                              */
/* �߂�l   : SLNG   :             : �t�@�C���T�C�Y                          */
/* �쐬��   : 2019/07/09       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

SLNG   BM_BmpFormatConv ( SLNG * sl_Errchk , BMPF * Filedata , UCHR uc_Bitcnt ) {

    /* �����`�F�b�N -------------------------------------------------------- */
    // NULL�|�C���^�̏ꍇ
    if ( Filedata == NULL ) {
    
        * sl_Errchk = ErrerPrint ( 1 , ( SCHR * ) "aa" );
        return 0;

    }

    // �f�[�^�����݂��Ȃ��ꍇ
    if ( Filedata -> sl_Height == 0 || 
         Filedata -> sl_Width  == 0 ) {
    
        * sl_Errchk = ErrerPrint ( 2 , ( SCHR * ) "aa" );
        return 0;
    
    } 

    // �ϊ���̃r�b�g�����ς��Ȃ��ꍇ
    if ( Filedata -> uc_Bitcnt == uc_Bitcnt ) { return 0; }

    /* �ϐ��錾 ------------------------------------------------------------ */
    ULNG   ul_Index    = 0;                       // �摜�f�[�^�̌��݈ʒu
    ULNG   ul_Datasize = 0;                       // �摜�f�[�^�r�b�g��
    void * Curr_pt     = NULL;                    // 1bit�J���[�|�C���^
    void * New_pt      = NULL;
    CL32 * Curr_pt32   = ( CL32 * ) Filedata -> Imagedata; // 32bit�J���[�|�C���^

    ul_Datasize = ( Filedata -> sl_Height ) * ( Filedata -> sl_Width ); // �f�[�^�T�C�Y�擾

    Curr_pt = BM_ImageNewPointer ( sl_Errchk , uc_Bitcnt );             // �擪�|�C���^�擾
    Filedata -> Imagedata = Curr_pt;    
  
    // �S�f�[�^�ϊ��I���܂Ń��[�v
    for ( ul_Index = 0 ; ul_Index < ul_Datasize ; ul_Index ++ ) {

        // �w�肳�ꂽ�F�r�b�g���ɉ����ĕ���
        switch ( uc_Bitcnt ) {
    
            case BM_01 : BM_1BitColorConv  ( sl_Errchk , ( CL01 * )Curr_pt , Curr_pt32 ); //  1bit
                         break;
            case BM_08 : BM_8BitColorConv  ( sl_Errchk , ( CL08 * )Curr_pt , Curr_pt32 ); //  8bit
                         break;
            case BM_24 : BM_24BitColorConv ( sl_Errchk , ( CL24 * )Curr_pt , Curr_pt32 ); // 24bit
                         break;
            case BM_32 : BM_32BitColorConv ( sl_Errchk , ( CL32 * )Curr_pt , Filedata  ); // 32bit
                         break;
            default    : * sl_Errchk = ErrerPrint ( 3 , ( SCHR * ) "aa" );    // �ُ�l
                         return 0;

        }

        // NULL�|�C���^���`�F�b�N
        if ( Curr_pt32 -> Next_pt == NULL ) { 
        
            break;

        }
        
        Curr_pt32 = Curr_pt32 -> Next_pt;
        free ( Curr_pt32 -> Prev_pt ); 

        New_pt = BM_ImageNewPointer ( sl_Errchk , uc_Bitcnt );
        BM_ImageSetPointer ( sl_Errchk , Curr_pt , New_pt , uc_Bitcnt );

        Curr_pt = New_pt;

    }

    free( Curr_pt32 );

    return 0;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : BM_ImageNewPointer                                             */
/* �@�\��   : �V�K���X�g�̊m��                                               */
/* �@�\�T�v : uc_Bitcnt�̒l�ɉ����ĐV�K���X�g�̊m��                          */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : UCHR   : uc_Bitcnt   : �F�r�b�g��                              */
/* �߂�l   : void * : New_pt      : �m�ۂ������X�g�̃|�C���^                */
/* �쐬��   : 2019/07/30       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

void * BM_ImageNewPointer ( SLNG * sl_Errchk , UCHR uc_Bitcnt ) {
    
    /* �ϐ��錾 ------------------------------------------------------------ */
    void * New_pt;

    // �F�r�b�g���ŕ���
    switch ( uc_Bitcnt ) {
    
        case BM_01 : New_pt = calloc ( 1 , sizeof( CL01 ) ); //  1bit
                     break;
        case BM_08 : New_pt = calloc ( 1 , sizeof( CL08 ) ); //  8bit
                     break;
        case BM_24 : New_pt = calloc ( 1 , sizeof( CL24 ) ); // 24bit
                     break;
        case BM_32 : New_pt = calloc ( 1 , sizeof( CL32 ) ); // 32bit
                     break;
        default    : * sl_Errchk = ErrerPrint ( 1, ( SCHR * ) "aa" ); // �ُ�l

    }

    return New_pt;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : BM_ImageSetPointer                                             */
/* �@�\��   : ���X�g�̕����̐ݒ�                                             */
/* �@�\�T�v : ��̃��X�g�̕����̐ݒ�                                       */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : void * : Curr_pt1    : �O���X�g                                */
/*          : void * : Curr_pt2    : �ナ�X�g                                */
/*          : UCHR   : uc_Bitcnt   : �F�r�b�g��                              */
/* �߂�l   : SLNG   :             : �K��                                    */
/* �쐬��   : 2019/07/30       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

SLNG   BM_ImageSetPointer ( SLNG * sl_Errchk , void * Curr_pt1 , void * Curr_pt2 , UCHR uc_Bitcnt ) {
    
    /* �����`�F�b�N -------------------------------------------------------- */

    // NULL�|�C���^�̏ꍇ
    if ( Curr_pt1 == NULL ||
         Curr_pt2 == NULL    ) {
    
        * sl_Errchk = ErrerPrint ( 1 , ( SCHR * ) "aa" );
        return 0;

    } 

    // �F�r�b�g���ŕ���
    switch ( uc_Bitcnt ) {
    
        // 1bit
        case BM_01 : CL01 * New_pt1 = ( CL01 * )Curr_pt1;
                     CL01 * New_pt2 = ( CL01 * )Curr_pt2;

                     New_pt1 -> Next_pt = New_pt2;
                     New_pt2 -> Prev_pt = New_pt1;

                     break;

        // 8bit
        case BM_08 : CL08 * New_pt1 = ( CL08 * )Curr_pt1;
                     CL08 * New_pt2 = ( CL08 * )Curr_pt2;

                     New_pt1 -> Next_pt = New_pt2;
                     New_pt2 -> Prev_pt = New_pt1;

                     break;

        // 24bit
        case BM_24 : CL24 * New_pt1 = ( CL24 * )Curr_pt1;
                     CL24 * New_pt2 = ( CL24 * )Curr_pt2;

                     New_pt1 -> Next_pt = New_pt2;
                     New_pt2 -> Prev_pt = New_pt1;

                     break;

        // 32bit
        case BM_32 : CL32 * New_pt1 = ( CL32 * )Curr_pt1;
                     CL32 * New_pt2 = ( CL32 * )Curr_pt2;

                     New_pt1 -> Next_pt = New_pt2;
                     New_pt2 -> Prev_pt = New_pt1;

                     break;

        default    : * sl_Errchk = ErrerPrint ( 2, ( SCHR * ) "aa" ); // �ُ�l

    }

    return 0;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : ErrerPrint                                                     */
/* �@�\��   : �G���[�o��                                                     */
/* ����	    : SLNG * : sl_Errnum   : �G���[�ԍ�                              */
/*          : SCHR * : sc_Errstr   : �G���[������                            */
/* �߂�l   : SLNG   :             : �t�@�C���T�C�Y                          */
/* �쐬��   : 2019/07/30       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

SLNG ErrerPrint ( SLNG sl_Errnum , SCHR * sc_Errstr ) {

    printf( "errernumber[%03d]\n %s\n " , sl_Errnum , sc_Errstr );
    return BM_NG;
}


/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */