/*----------------------------------------------------------------------------*/
/* デジタルカメラ格納仕様 ファイル検索管理                                    */
/* 指定フォルダ配下に存在するファイルを検索する、以下の関数をラッピングします */
/* _findfirst/_findnext/_findlast                                             */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <io.h>
#include <windows.h>
#include <stdarg.h>
#include <errno.h>


/*----------------------------------------------------------------------------*/
/* マクロ・定数定義                                                           */
/*----------------------------------------------------------------------------*/
#define FIND_OK              0                    /* Find成功                 */
#define FIND_NG             -1                    /* Find失敗                 */
#define FIND_EOF            -2                    /* ファイルが無い           */

#define FLD_NUM_MAX        999                    /* フォルダ番号最大数       */
#define FILE_NUM_MAX      9999                    /* ファイル番号最大数       */

#define FLD_PATH_MAX       250                    /* フォルダフルパス領域     */
#define FILE_NAME_MAX      256                    /* ファイル名格納領域       */

#define FLD_NAME_LEN         8                    /* フォルダ名最大数         */
#define FILE_NAME_LEN       12                    /* ファイル名最大数         */

#define FIND_FILE            0                    /* ファイル                 */
#define FIND_FLD             1                    /* フォルダ                 */

/*----------------------------------------------------------------------------*/
/* プロトタイプ宣言                                                           */
/*----------------------------------------------------------------------------*/
long Find_Open( char* FullPath, unsigned short PathLength );
long Find( long Handle, char* FileName, unsigned short FileLength, unsigned long *FileSize, char* Attr );
long Find_Close( long Handle );