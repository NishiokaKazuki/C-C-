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

#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* ------------------------------------------------------------------------- */
/* �萔��`	                                                                 */
/* ------------------------------------------------------------------------- */

#define BM_OK  1
#define BM_NG -1

#define BM_01  1
#define BM_08  8
#define BM_24 24
#define BM_32 32

/* ------------------------------------------------------------------------- */
/* typedef�錾                                                               */
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
/* �\���̒�`                                                                */
/* ------------------------------------------------------------------------- */

// 1bit�J���[
typedef struct color {

    UCHR          uc_Color; // �F�h�b�g
    struct color * Prev_pt; // �O�h�b�g
    struct color * Next_pt; // ���h�b�g

}CL01;

// 8bit�J���[
typedef struct color {

    UCHR          uc_Color; // �F�h�b�g
    struct color * Prev_pt; // �O�h�b�g
    struct color * Next_pt; // ���h�b�g

}CL08;


// 24bit�J���[
typedef struct color {

    UCHR      uc_Rcolor;    // ��
    UCHR      uc_Gcolor;    // ��
    UCHR      uc_Bcolor;    // ��
    struct color * Prev_pt; // �O�h�b�g
    struct color * Next_pt; // ���h�b�g

}CL24;


// 32bit�J���[
typedef struct color {

    UCHR      uc_Rcolor;    // ��
    UCHR      uc_Gcolor;    // ��
    UCHR      uc_Bcolor;    // ��
    UCHR      uc_Reserve;   // �\��̈�
    struct color * Prev_pt; // �O�h�b�g
    struct color * Next_pt; // ���h�b�g

}CL32;

// BMP���
typedef struct BMP {

    SLNG   sl_Width;    // ��
    SLNG   sl_Height;   // �c
    UCHR   uc_Bitcnt;   // �F�r�b�g��    
    void * Imagedata;   // �摜�f�[�^

}BMPF;

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾                                                          */
/* ------------------------------------------------------------------------- */

/* �֐��錾 ---------------------------------------------------------------- */
SLNG   BM_BmpFormatConv ( SLNG * , BMPF * , UCHR   );
SLNG   ErrerPrint       ( SLNG   , SCHR * );

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */