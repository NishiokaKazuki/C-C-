/*----------------------------------------------------------------------------*/
/* �f�W�^���J�����i�[�d�l �t�@�C�������Ǘ�                                    */
/* �w��t�H���_�z���ɑ��݂���t�@�C������������A�ȉ��̊֐������b�s���O���܂� */
/* _findfirst/_findnext/_findlast                                             */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <io.h>
#include <windows.h>
#include <stdarg.h>
#include <errno.h>


/*----------------------------------------------------------------------------*/
/* �}�N���E�萔��`                                                           */
/*----------------------------------------------------------------------------*/
#define FIND_OK              0                    /* Find����                 */
#define FIND_NG             -1                    /* Find���s                 */
#define FIND_EOF            -2                    /* �t�@�C��������           */

#define FLD_NUM_MAX        999                    /* �t�H���_�ԍ��ő吔       */
#define FILE_NUM_MAX      9999                    /* �t�@�C���ԍ��ő吔       */

#define FLD_PATH_MAX       250                    /* �t�H���_�t���p�X�̈�     */
#define FILE_NAME_MAX      256                    /* �t�@�C�����i�[�̈�       */

#define FLD_NAME_LEN         8                    /* �t�H���_���ő吔         */
#define FILE_NAME_LEN       12                    /* �t�@�C�����ő吔         */

#define FIND_FILE            0                    /* �t�@�C��                 */
#define FIND_FLD             1                    /* �t�H���_                 */

/*----------------------------------------------------------------------------*/
/* �v���g�^�C�v�錾                                                           */
/*----------------------------------------------------------------------------*/
long Find_Open( char* FullPath, unsigned short PathLength );
long Find( long Handle, char* FileName, unsigned short FileLength, unsigned long *FileSize, char* Attr );
long Find_Close( long Handle );