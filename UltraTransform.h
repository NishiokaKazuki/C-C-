/* ------------------------------------------------------------------------- */
/*                                                                           */
/* BMPbit�J���[�ϊ�                                                          */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2019/07/30  ����  �a�P   */
/* ------------------------------------------------------------------------- */

#define RED__ 0.2126 // �ԃO���[�X�P�[��
#define GREEN 0.7152 // �O���[�X�P�[��
#define BLUE_ 0.0722 // �΃O���[�X�P�[��

/* ------------------------------------------------------------------------- */
/* �N���X��`                                                                */ 
/* ------------------------------------------------------------------------- */

class UltraTransform {

public:
    UltraTransform();                                      /* �R���X�g���N�^ */
    ~UltraTransform();                                     /* �f�X�g���N�^   */

    SLNG   BM_BmpFormatConv ( SLNG * , BMPF * , UCHR   );

private:
    void * BM_1BitColorConv  ( SLNG * , CL01 * , CL32 * );
    void * BM_8BitColorConv  ( SLNG * , CL08 * , CL32 * );
    void * BM_24BitColorConv ( SLNG * , CL24 * , CL32 * );
    void * BM_32BitColorConv ( SLNG * , CL32 * , void * , UCHR   );
    SLNG   BM_ImageSetPointer( SLNG * , void * , void * , UCHR   );
    void * BM_ImageNewPointer( SLNG * , UCHR   );

};
