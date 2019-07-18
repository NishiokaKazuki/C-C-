/* ------------------------------------------------------------------------- */
/*                                                                           */
/* �N�C�b�N�\�[�g                                                            */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2019/07/10  ����  �a�P   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��                                                           */
/* ------------------------------------------------------------------------- */

#include "quicksort.h"

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾                                                          */
/* ------------------------------------------------------------------------- */

int Swap(int *, int *);

int quicksort ( int * sortarray , int arraynum ) {
    
    /* �ϐ��錾 ------------------------------------------------------------ */
    int si_pivot  = 0;            // ��l
    int si_index1 = 0;            // ��l��菬�������̔z��
    int si_index2 = arraynum - 1; // ��l���傫�����̔z��

    // ��l����
    si_pivot = rand() % arraynum;
    si_pivot = * ( sortarray + si_pivot );

    // ��l�����ɕ��ёւ�
    while ( 1 ) {

        // ��l�ȏ㔭���܂Ń��[�v
        for ( ; si_index1 < si_index2 ; si_index1 ++ ) {
    
            if ( * ( sortarray + si_index1 ) >= si_pivot ) { break; }
    
        }

        // ��l�ȉ������܂Ń��[�v
        for ( ; si_index2 > si_index1 ; si_index2 -- ) {
    
            if ( * ( sortarray + si_index2 ) <  si_pivot ) { break; }
    
        }

        if ( si_index1 == si_index2 ) { break; }

        Swap ( ( sortarray + si_index1 ) , ( sortarray + si_index2 ) );

    }

    // ��l�����̔z��Ń\�[�g
    if ( si_index1 != 0            ) { quicksort( sortarray                 , si_index1             ); }
    // ��l�ȏ�̔z��Ń\�[�g
    if ( si_index2 != arraynum - 1 ) { quicksort( ( sortarray + si_index2 ) , arraynum  - si_index1 ); }

    return 0;

}

// ����ւ�
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