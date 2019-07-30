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

#include "main.h"

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾                                                          */
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

    /* �ϐ��錾 ------------------------------------------------------------ */
    SLNG   sl_errchk = 0;



    DL_UserInterface ( &sl_errchk , ( SCHR * )"C:\\Users\\ohs80472\\Desktop\\hal\\cl21\\�ۑ�07_19_07_09\\TestData.csv" );

    system( "pause" );
    return 0;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : DL_UserInterface                                               */
/* �@�\��   : ���X�g�|�C���^�̈ړ�                                           */
/* �@�\�T�v : �ړ��l�ɉ����Ċ֐���U�蕪����                                 */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : ADDS * : ad_pt       : �ړ��O �|�C���^                         */
/*          : SLNG   : sl_movenum  : �|�C���^�ړ���                          */
/* �߂�l   : ADDS * :             : �ړ��� �|�C���^                         */
/* �쐬��   : 2019/07/09       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

ADDS * DL_UserInterface ( SLNG * sl_errchk , SCHR * sc_filename ) {

    /* �ϐ��錾 ------------------------------------------------------------ */
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

    printf ( "�@���� : %s\n" , ad_pt -> sc_name );
    printf ( "�@���� : %s\n" , ad_pt -> sc_kname );
    printf ( "�@���� : %c\n" , ad_pt -> sc_sex );
    printf ( "�@���t : %c\n" , ad_pt -> sc_blood );
    printf ( "�a���� : %s\n" , ad_pt -> sc_birthday );
    printf ( "�z��� : %c\n" , ad_pt -> sc_merry );
    printf ( "�@�N�� : %hhd\n" , ad_pt -> sc_age );
    printf ( "�@�g�� : %s\n" , ad_pt -> sc_mphone );
    printf ( "���[�� : %s\n" , ad_pt -> sc_mailadds );
    printf ( "�@�X�� : %s\n" , ad_pt -> sc_post );
    printf ( "�@�Z�� : %s\n" , ad_pt -> sc_sadds );
    printf ( "�@���� : %d\n" , ad_pt -> sl_money );

    return 0;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : DL_MemoryWrite                                                 */
/* �@�\��   : �t�@�C����ǂݍ���                                             */
/* �@�\�T�v : �ǂݍ��񂾃t�@�C�����������ɏ�������                           */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : SCHR * :  sc_filename: �t�@�C����                              */
/* �߂�l   : SLNG   :             : �t�@�C���T�C�Y                          */
/* �쐬��   : 2019/07/09       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

SCHR * DL_MemoryWrite ( SLNG * sl_errchk , SLNG * sl_filesize , SCHR * sc_filename  ) {
    
    /* �ϐ��錾 ------------------------------------------------------------ */
	FILE * fp          = NULL; // �t�@�C���|�C���^
    SCHR * sc_memp     = NULL; // �������[�|�C���^

    fp = DL_FileOpen( sl_errchk , sc_filename ); // �t�@�C���|�C���^�擾
    if ( * sl_errchk == DL_ERR ) { return 0; }  // �G���[�`�F�b�N

    * sl_filesize = DL_FileSize( sl_errchk , fp ); // �t�@�C���T�C�Y�擾

    sc_memp = ( SCHR * )calloc( ( * sl_filesize ) * 2 , sizeof( SCHR ) ); // �������[�m��

    fread( sc_memp , sizeof( SCHR ) , * sl_filesize  , fp ); // �t�@�C�����e��ǂݍ���
    fclose( fp );
   
    return sc_memp;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : DL_ListWrite                                                   */
/* �@�\��   : �t�@�C���̐擪�|�C���^                                         */
/* �@�\�T�v : �ړ��l�ɉ����Ċ֐���U�蕪����                                 */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : SCHR * : sc_filename : �t�@�C����                              */
/*          : SLNG   : sl_filesize : �t�@�C���̃r�b�g��                      */
/* �߂�l   : ADDS * :             : �������̐擪�|�C���^                    */
/* �쐬��   : 2019/07/28       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

ADDS * DL_ListWrite ( SLNG * sl_errchk , SCHR * sc_startmemp  , SLNG * sl_listnum ) {

    /* �ϐ��錾 ------------------------------------------------------------ */
    SLNG   sl_ptindex = 0;    
    SCHR   sc_ptflg   = 0;
    SCHR   sc_age  [__AGE_SIZE];
    SCHR   sc_money[MONEY_SIZE];
    ADDS * ad_pt;
    ADDS * new_pt;
    SCHR * sc_memp = sc_startmemp;
    SCHR i = 0;

    memset ( sc_age   , 0 , sizeof( SCHR ) * __AGE_SIZE ); // ������
    memset ( sc_money , 0 , sizeof( SCHR ) * MONEY_SIZE ); // ������

    ad_pt = ( ADDS * )calloc( 1 , sizeof( ADDS ) );

    for ( ; * ( sc_memp - 1 ) != '\n' ;  sc_memp ++ ){} // ��s�ڂ��X�L�b�v

    // �������ɏ�������
    while ( 1 ) {
     
       // if ( * sc_memp == EOF ) { break; } // �I������

        // �����o�[�ϐ��؂�ւ�
        if ( * sc_memp == ',' ) {
        
            if ( sc_ptflg == 6 ) { 
            
                ad_pt -> sc_age = DL_strconv ( sl_errchk , sc_age );  // ���l�ϊ�
                memset ( sc_age , 0 , sizeof( SCHR ) * __AGE_SIZE ); // ������
            
            }

            sc_memp   ++; // �������l�؂�ւ�
            sc_ptflg  ++; // �����o�[�ϐ��ݒ�
            sl_ptindex = DL_PointMove( sl_errchk , sc_ptflg ); // �����o�[�ϐ��ύX
            continue; 
        
        }
        
        // ���s�ǂݍ���
        if ( * sc_memp  == '\n' ) {
            
            sc_ptflg   = 0; // �����o�[�ϐ��ݒ�
            sc_memp     ++; // ���s�X�L�b�v
            ( * sl_listnum  ) ++; // �A�h���X���J�E���g

            sl_ptindex = DL_PointMove( sl_errchk , sc_ptflg );        // �����o�[�ϐ��ύX
            ad_pt -> sl_money = DL_strconv ( sl_errchk , sc_money );  // ���l�ϊ�            
            memset ( sc_money , 0 , sizeof( SCHR ) * MONEY_SIZE ); // ������

            i++;
            if (i == 10) { break; }
            if ( * sc_memp == EOF ) { break; } // �I������

            new_pt = DL_NewPointer( sl_errchk ); // �i�[�ꏊ�擾
            ad_pt  = DL_SetPointer( sl_errchk , NULL , ad_pt , new_pt ); // ���|�C���^�ݒ�

        }

        if ( ( sc_ptflg != 11 ) && ( sc_ptflg != 6 ) ) {          * ( ad_pt -> sc_name + sl_ptindex ) = * sc_memp; } // ���������ȊO 
        if (   sc_ptflg == 11 )       { sc_money[ sl_ptindex - DL_PointMove( sl_errchk , sc_ptflg ) ] = * sc_memp; } // ���������̏ꍇ
        if (   sc_ptflg == 6  )       { sc_age  [ sl_ptindex - DL_PointMove( sl_errchk , sc_ptflg ) ] = * sc_memp; } // �N��̏ꍇ
        
        sc_memp ++;    // �������l�؂�ւ�
        sl_ptindex ++; // �ϐ����|�C���^�ړ�
        
    }

    free( sc_startmemp );

    ad_pt = DL_ListMove ( sl_errchk , ad_pt , 1 - ( * sl_listnum ) ); // �擪�|�C���^�Ɉړ�

    return ad_pt;

}
 
/* ------------------------------------------------------------------------- */
/* �֐���   : DL_NewPointer                                                  */
/* �@�\��   : ���X�g�̌���                                                   */
/* �@�\�T�v : �O�̃��X�g���ԂɌ���������Ԍ�̃��X�g��ԋp                 */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : ADDS * : ad_pt1      : �擪�|�C���^                            */
/*          : ADDS * : ad_pt2      : ���S�|�C���^                            */
/*          : ADDS * : ad_pt3      : �����|�C���^                            */
/* �߂�l   : ADDS * :             : ��Ԍ�̃��X�g�̃|�C���^                */
/* �쐬��   : 2019/07/27       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
 
ADDS * DL_SetPointer ( SLNG * sl_errchk , ADDS * ad_pt1 , ADDS * ad_pt2 , ADDS * ad_pt3 ) { 

    /* �����`�F�b�N -------------------------------------------------------- */

    if ( ad_pt2 == NULL ) { 
        
        * sl_errchk = DL_ERR;
        return 0; 
    
    }

    // �O���X�g������ꍇ
    if ( ad_pt1 != NULL ) { 

        ad_pt1 -> next_pt   = ad_pt2;
        ad_pt2 -> before_pt = ad_pt1;

    }

    // ��냊�X�g������ꍇ
    if ( ad_pt3 != NULL ) {

        ad_pt2 -> next_pt   = ad_pt3;
        ad_pt3 -> before_pt = ad_pt2;

    }

    return ad_pt3;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : DL_NewPointer                                                  */
/* �@�\��   : �V�K���X�g�̍쐬                                               */
/* �@�\�T�v : �V�������������m�ۂ����̃|�C���^��Ԃ�                         */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/* �߂�l   : ADDS * :             : �V�K���X�g�̃|�C���^                    */
/* �쐬��   : 2019/07/11       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

ADDS * DL_NewPointer ( SLNG * sl_errchk ) {

    // �������m��
    ADDS * new_pt;
    new_pt = ( ADDS * )calloc( 1 , sizeof( ADDS ) );
    return new_pt;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : DL_strconv                                                     */
/* �@�\��   : ������𐔒l�ɕϊ�                                             */
/* �@�\�T�v : �����̕�����𐔒l�ɕϊ�                                       */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : SCHR * : sc_string   : �����̕�����                            */
/* �߂�l   : SLNG   :             : �ϊ��㐔�l                              */
/* �쐬��   : 2019/07/09       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

SLNG   DL_strconv ( SLNG * sl_errchk , SCHR * sc_string ) {

    /* �����`�F�b�N ---------------------------------------------------------*/

    if ( sc_string == NULL ) { 
        
        * sl_errchk =  ErrerPrint( 001 , ( SCHR * )"DL_strconv" );
        return 0;

    }

    /* �ϐ��錾 ------------------------------------------------------------ */
    SLNG sl_num    = 0; // return�l
    SLNG sl_index  = 0; // ������Y����
    SLNG sl_tencnt = 1; // ���̏d��

    // ���̏d�ݐݒ�
    for ( sl_index = 1 ; sl_index < strlen ( ( char * ) sc_string ) ; sl_index ++ ) { sl_tencnt = sl_tencnt * 10; }

    // ������𐔒l�ɕϊ�
    for ( sl_index = 0 ; sl_index < strlen ( ( char * ) sc_string ) ; sl_index ++ ) {
        
        sl_num += ( ( * ( sc_string + sl_index ) ) - 0x30 ) * sl_tencnt;
        sl_tencnt = sl_tencnt / 10;

    }

    return sl_num;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : DL_FileOpen                                                    */
/* �@�\��   : �t�@�C���̐擪�|�C���^                                         */
/* �@�\�T�v : �ړ��l�ɉ����Ċ֐���U�蕪����                                 */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : SCHR * : asc_filename: �t�@�C����                              */
/* �߂�l   : FILE * :             : �t�@�C���|�C���^                        */
/* �쐬��   : 2019/07/09       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

FILE * DL_FileOpen ( SLNG * sl_errchk , SCHR * sc_filename ) {
    
    /* �����`�F�b�N ---------------------------------------------------------*/

    if ( sc_filename == NULL ) {
    
        * sl_errchk = ErrerPrint( 001 , ( SCHR * )"DL_FileOpen" );
        return 0;
    
    } 

    /* �ϐ��錾 ------------------------------------------------------------ */
    errno_t	  error	= NULL;     // �G���[�`�F�b�N
	FILE    * fp    = NULL;     // �t�@�C���|�C���^

    error = fopen_s( &fp , ( char * ) sc_filename , "r" ); // �t�@�C���I�[�v��
    if ( error != NULL ) { * sl_errchk = ErrerPrint( 002 , ( SCHR * )"DL_FileOpen" ); } // �G���[�`�F�b�N

    return fp;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : DL_FileSize                                                    */
/* �@�\��   : �t�@�C���̃T�C�Y�𒲂ׂ�                                       */
/* ����     : FILE * : fp          : �����Ώۃt�@�C���̃|�C���^              */
/* �߂�l   : SLNG   :             : �t�@�C���̃T�C�Y                        */
/* �쐬��   : 2019/07/09       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

SLNG   DL_FileSize ( SLNG * sl_errchk , FILE * fp ) {

    SLNG sl_filesize;

    // fp��NULL�|�C���^�̎�
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
/* �֐���   : DL_PointMove                                                   */
/* �@�\��   : ���X�g�|�C���^�̈ړ�                                           */
/* �@�\�T�v : �ړ��l�ɉ����Ċ֐���U�蕪����                                 */
/* ����	    : SLNG * : sl_errchk   : �G���[�m�F                              */
/*          : ADDS * : ad_pt       : �ړ��O �|�C���^                         */
/*          : SLNG   : sl_movenum  : �|�C���^�ړ���                          */
/* �߂�l   : ADDS * :             : �ړ��� �|�C���^                         */
/* �쐬��   : 2019/07/09       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

SLNG   DL_PointMove ( SLNG * sl_errchk , SLNG sl_listmember ) {

    SLNG sl_ptindex = 0; // �����o�[�ϐ��ւ̃A�N�Z�X
    
    // �|�C���^�̒l�擾
    switch ( sl_listmember ) {
    
        case 11 : sl_ptindex += SADDS_SIZE;     // ��������
        case 10 : sl_ptindex += _POST_SIZE;     // �Z��
        case  9 : sl_ptindex += MADDS_SIZE;     // �X�֔ԍ�
        case  8 : sl_ptindex += PHONE_SIZE;     // ���[���A�h���X
        case  7 : sl_ptindex += sizeof( char ); // �g�ѓd�b�ԍ�
        case  6 : sl_ptindex += sizeof( char ); // �N��
        case  5 : sl_ptindex += _BDAY_SIZE;     // �z���
        case  4 : sl_ptindex += sizeof( char ); // �a����
        case  3 : sl_ptindex += sizeof( char ); // ���t�^
        case  2 : sl_ptindex += KNAME_SIZE;     // ����
        case  1 : sl_ptindex += _NAME_SIZE;     // ����
        case  0 : break;                        // ����

        default : * sl_errchk = ErrerPrint( 002 , ( SCHR * )"DL_PointMove" );
                  return 0;
    
    }

    return sl_ptindex;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : ErrerPrint                                                     */
/* �@�\��   : �G���[�ԍ��̏o��                                               */
/* ����	    : SLNG   : sl_errnum   : �G���[�ԍ�                              */
/* �߂�l   : SLNG   : �ُ�l      : DL_ERR                                  */
/* �쐬��   : 2019/07/28       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */

SLNG   ErrerPrint ( SLNG sl_errnum , SCHR * sc_errstr ) {

    printf( "errernumber[%03d]\n%s\n" , sl_errnum , sc_errstr ); // �G���[�o��
    return DL_ERR;

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */