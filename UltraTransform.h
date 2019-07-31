/* ------------------------------------------------------------------------- */
/*                                                                           */
/* BMPbitカラー変換                                                          */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  番号    更新内容                                更新日      名前         */
/* ------------------------------------------------------------------------- */
/* 000000   新規作成                                2019/07/30  西岡  和輝   */
/* ------------------------------------------------------------------------- */

#define RED__ 0.2126 // 赤グレースケール
#define GREEN 0.7152 // 青グレースケール
#define BLUE_ 0.0722 // 緑グレースケール

/* ------------------------------------------------------------------------- */
/* クラス定義                                                                */ 
/* ------------------------------------------------------------------------- */

class UltraTransform {

public:
    UltraTransform();                                      /* コンストラクタ */
    ~UltraTransform();                                     /* デストラクタ   */

    SLNG   BM_BmpFormatConv ( SLNG * , BMPF * , UCHR   );

private:
    void * BM_1BitColorConv  ( SLNG * , CL01 * , CL32 * );
    void * BM_8BitColorConv  ( SLNG * , CL08 * , CL32 * );
    void * BM_24BitColorConv ( SLNG * , CL24 * , CL32 * );
    void * BM_32BitColorConv ( SLNG * , CL32 * , void * , UCHR   );
    SLNG   BM_ImageSetPointer( SLNG * , void * , void * , UCHR   );
    void * BM_ImageNewPointer( SLNG * , UCHR   );

};
