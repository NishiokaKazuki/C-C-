/* ------------------------------------------------------------------------- */
/*                                                                           */
/*  �}�[�W�\�[�g                                                             */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2019/07/07  ����  �a�P   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��                                                           */
/* ------------------------------------------------------------------------- */

#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>


int Merge( int * , int   );
int Swap ( int * , int * );

int Merge ( int * si_data , int   si_data_num  ) {

    /* �ϐ��錾 ------------------------------------------------------------ */
    int   si_pivot1 = 0; // ���񕔕��̐擪�ւ̊�l
    int   si_pivot2 = 0; // ��r�Ώۂ��\�[�g�I���̎����̊�l�Ɉڂ�
    int   si_index1 = 0; // ��r�Ώ�1
    int   si_index2 = 0; // ��r�Ώ�2

    // �\�[�g�I���܂Ń��[�v
    for ( si_pivot1 = 1 ; si_pivot1 < si_data_num ; si_pivot1 *= 2 ) {
     
        // ��l�T�C�Y�ł̔z����\�[�g�I���܂Ń��[�v
        for ( si_pivot2 = si_pivot1 ; si_pivot2 < si_data_num ; si_pivot2 += ( si_pivot1 * 2 ) ) {
            
            si_index1 = si_pivot2 - si_pivot1;
            si_index2 = si_pivot2;

            while ( 1 ) {            

                // �\�[�g�Ώۂ̏ꍇ
                if ( si_data[si_index1] > si_data[si_index2] ) {
                
                    Swap( ( si_data + si_index1 ) , ( si_data + si_index2 ) );
                    si_index1 ++;
                    si_index2 ++;
                
                }
                else { si_index1 ++ ; }
            
                // �I������ 
                if ( si_index1 ==   si_pivot2             )   { break; }
                if ( si_index2 == ( si_pivot1 + si_pivot2 ) ) { break; }

                // ��l�̃T�C�Y�ɖ����Ȃ��z�񔭌���
                if ( si_index2 ==   si_data_num           )   { 
                
                    while ( 1 ) {

                        Swap( ( si_data + si_index1 ++ ) , ( si_data + si_pivot2 ) );
                        if  ( si_index1 ==   si_pivot2 )   { break; }
                        Swap( ( si_data + si_index1 ++ ) , ( si_data + si_pivot2 + 1 ) );
                        if  ( si_index1 ==   si_pivot2 )   { break; }

                    }

                    break;
                }

            }
        
        }
    
    }

    return 0;

}

// �������Ƒ���������ւ�
int Swap ( int * si_data1 , int * si_data2 ) {

    int si_sub = 0;
    
    si_sub     = * si_data1;
    * si_data1 = * si_data2;
    * si_data2 = si_sub;
    
    return 0;

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */