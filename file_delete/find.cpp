/*----------------------------------------------------------------------------*/
/* �f�W�^���J�����i�[ �t�H���_�z���t�@�C������                                */
/* �f�W�^���J�����Ƀt�H���_�Ɋi�[�����t�@�C�������擾���܂��B               */
/* �{�t�@�C���̖ړI��Windows�nOS��_find�n�֐������b�s���O���Ă��܂��B         */
/*----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "find.h"

/*----------------------------------------------------------------------------*/
/* �O���[�o���ϐ�                                                             */
/*----------------------------------------------------------------------------*/
static long g_FindIndex[FLD_NUM_MAX];            /* Find�p����ID              */

/*----------------------------------------------------------------------------*/
/* �v���g�^�C�v�錾(private)                                                  */
/*----------------------------------------------------------------------------*/
void FindErr( long FindHandle, const char* name, ... );

/*----------------------------------------------------------------------------*/
/* �t�H���_���擾���� Find_Open                                             */
/* �@�\�T�v     �F�w��t�H���_�z���̎���ID���擾����B                        */
/* ����         �Fchar*            �FFullPath    �F�t�@�C�����o�b�t�@ �I�[NULL*/
/*              �Funsigned short   �FPathLength  �F�����������T�C�Y         */
/*              �F                 �F            �F�ő�250Byte�܂�            */
/* �߂�l       �Flong             �F���펞      �FFind�p����ID               */
/*              �F                 �F�ُ펞      �FFIND_NG                    */
/* �쐬��       �F2007/10/17    �V�K�쐬                                      */
/*----------------------------------------------------------------------------*/
long Find_Open( char* FullPath, unsigned short PathLength )
{
	long               usPathIdx  = 0;           /* �p�X�i�[Index             */
	int                FindNextRet= 0;           /* 1��ڂ�_findnext�߂�l�i�[*/
	long               FindHandle = 0;           /* _findfirst��M�n���h��    */
	struct _finddata_t c_file;                   /* �w��t�@�C���A�t�H���_���*/
	char               cPath[256];               /* �C����t�H���_�p�X        */
	
	/* �p�����[�^�`�F�b�N --------------------------------------------------- */
	if(( FullPath == 0 ) || ( PathLength == 0 ) || ( PathLength > FLD_PATH_MAX )) {
		FindErr( 0, "�yFind_Open�zParam err.[%d]\n", (int)PathLength );
		return FIND_NG;
	}
	
	if( strlen( FullPath ) >= FLD_PATH_MAX ) {
		FindErr( 0, "�yFind_Open�zPath Length Over err.[%d]\n", (int)strlen( FullPath ));
		return FIND_NG;
	}
	
	/* �p�X��Ԃ̋󂫗̈挟�� ----------------------------------------------- */
	for( usPathIdx = 0; usPathIdx < FLD_NUM_MAX; usPathIdx ++ ) {
		if( g_FindIndex[usPathIdx] == 0 ) {
			break;
		}
	}
	
	/* �G���[�`�F�b�N */
	if( usPathIdx >= FLD_NUM_MAX ) {
		FindErr( 0, "�yFind_Open�zPath Full err.\n");
		return FIND_NG;
	}
	
	/* �t�H���_�p�X���烏�C���h�J�[�h�ɕύX --------------------------------- */
	memset( cPath, 0, sizeof( cPath ));
	strcpy( cPath, FullPath );
	strcat( cPath, "\\*" );
	
	/* "."��".."���Ɍ��� -------------------------------------------------- */
	FindHandle = (long)_findfirst(( const char *)cPath, &c_file );
	if( FindHandle == -1 ) {
		FindErr( 0, "�yFind_Open�zfindfirst err.\n");
		return FIND_NG;
	}
	
	if( c_file.name[0] != '.' ) {
		FindErr( FindHandle, "�yFind_Open�z. Check err.\n");
		return FIND_NG;
	}
	
	/* ".."�`�F�b�N */
	FindNextRet = _findnext( FindHandle, &c_file );
	if( FindNextRet != 0 ) {
		FindErr( FindHandle, "�yFind_Open�zfindnext err.\n");
		return FIND_NG;
	}
	
	if( strncmp( "..", c_file.name, 2 ) != 0 ) {
		FindErr( FindHandle, "�yFind_Open�z.. Check err.\n");
		return FIND_NG;
	}
	
	/* �n���h���R�s�[ */
	g_FindIndex[usPathIdx] = FindHandle;
	
	/* Index�ԍ�+1��Ԃ� */
	return ( usPathIdx + 1 );
	
}


/*----------------------------------------------------------------------------*/
/* �t�H���_���擾���� Find                                                  */
/* �@�\�T�v     �F�w��ID�z���̃t�@�C�������擾���A��ʂ֕ԋp                  */
/* ����         �Flong             �FHandle      �FFind_Open�Ŏ擾����ID      */
/*              �Fchar*            �FFileName    �F�t�@�C�����o�b�t�@���g���� */
/*              �Funsigned short   �FFileLength  �F�������o�b�t�@�T�C�Y     */
/*              �F                 �F            �F�ő�256Byte�܂�            */
/*              �Funsigned long    �FFileSize    �F�擾�t�@�C���T�C�Y         */
/*              �Fchar*            �FAttr        �F�t�@�C�����               */
/*              �F                 �FFIND_FILE   �F�t�@�C��                   */
/*              �F                 �FFIND_FLD    �F�t�H���_                   */
/* �߂�l       �Flong             �F���펞      �FFIND_OK                    */
/*              �F                 �F�ُ펞      �FFIND_NG                    */
/*              �F                 �F�t�@�C���I�[�FFIND_EOF                   */
/* �쐬��       �F2007/10/17    �V�K�쐬                                      */
/*----------------------------------------------------------------------------*/
long Find( long Handle, char* FileName, unsigned short FileLength, 
		   unsigned long *FileSize, char* Attr )
{
	long               FindHandle = 0;           /* _findfirst��M�n���h��    */
	int                FindNextRet= 0;           /* 1��ڂ�_findnext�߂�l�i�[*/
	struct _finddata_t c_file;                   /* �w��t�@�C���A�t�H���_���*/

	/* �p�����[�^�`�F�b�N --------------------------------------------------- */
	if(( Handle <= 0 ) || ( Handle > FLD_NUM_MAX ) || ( FileName == 0 ) ||
	   ( Attr == 0 ) || ( FileLength == 0 ) || ( FileLength > FILE_NAME_MAX ) || ( FileSize == 0 )) {
		FindErr( 0, "�yFind�zParam err.[%d]\n", Handle );
		return FIND_NG;
	}
	
	if( g_FindIndex[Handle - 1] == 0 ) {
		FindErr( 0, "�yFind�zFindIndex Not Found.[%d]\n",g_FindIndex[Handle - 1] );
		return FIND_NG;
	}
	
	/* ������ */
	memset( FileName, 0, FileLength );
	
	FindHandle = g_FindIndex[Handle - 1];
	
	FindNextRet = _findnext( FindHandle, &c_file );
	if( FindNextRet != 0 ) {
		/* �I�[�I�����ۂ����f���� */
		if( errno == ENOENT ) {
			return FIND_EOF;
		}
		FindErr( FindHandle, "�yFind�zfindnext err.\n");
		return FIND_NG;
	}
	
	/* �t�@�C�����A�����A�t�@�C���T�C�Y�擾 --------------------------------- */
	memset( FileName, 0, FileLength );
	strcpy( FileName, c_file.name );
	
	if(( c_file.attrib & _A_SUBDIR ) == _A_SUBDIR ) {
		*Attr = FIND_FLD;
	} else {
		*Attr = FIND_FILE;
	}

	*FileSize = c_file.size;
	
	return FIND_OK;
}

/*----------------------------------------------------------------------------*/
/* �t�H���_���擾���� Find_Close                                            */
/* �@�\�T�v     �F�w��t�H���_�z���̃t�@�C���������I������B                  */
/* ����         �Flong             �FHandle      �FFind_Open�Ŏ擾����ID      */
/* �߂�l       �Flong             �F���펞      �FFIND_OK                    */
/*              �F                 �F�ُ펞      �FFIND_NG                    */
/* �쐬��       �F2007/10/17    �V�K�쐬                                      */
/*----------------------------------------------------------------------------*/
long Find_Close( long Handle )
{
	long           FindHandle = 0;           /* _findfirst��M�n���h��    */
	
	/* �p�����[�^�`�F�b�N --------------------------------------------------- */
	if(( Handle <= 0 ) || ( Handle > FLD_NUM_MAX ))  {
		FindErr( 0, "�yFind�zParam err.[%d]\n", Handle );
		return FIND_NG;
	}
	
	if( g_FindIndex[Handle - 1] == 0 ) {
		FindErr( 0, "�yFind�zFindIndex Not Found.[%d]\n",g_FindIndex[Handle - 1] );
		return FIND_NG;
	}
	
	/* Find�p�n���h�������[�J���ɃR�s�[�A�O���[�o���̈�͍폜 --------------- */
	FindHandle = g_FindIndex[Handle - 1];
	g_FindIndex[Handle - 1] = 0;
	
	/* Find�I�� ------------------------------------------------------------- */
	_findclose( FindHandle );
	
	return FIND_OK;
}


/*----------------------------------------------------------------------------*/
/* �t�H���_���擾���� FindErr                                               */
/* �@�\�T�v     �F�G���[�������Ƀ��O�o�͂Ƌ��ɁA������findclose���s��         */
/* ����         �Flong             �FFindHandle  �F_finddirst�Ŏ擾����ID     */
/*              �Fchar*            �Fname...     �F�ϒ����b�Z�[�W           */
/* �߂�l       �Fvoid             �F����        �F                           */
/* �쐬��       �F2007/10/17    �V�K�쐬                                      */
/*----------------------------------------------------------------------------*/
void FindErr( long FindHandle, const char* name, ... )
{
	va_list args;
	char *str = 0;
	
	/* ���b�Z�[�W�G���A1KB�m�� ---------------------------------------------- */
	str = ( char *)malloc( 1024 * 1024 );
	if( str == 0 ) {
		printf("�yFindErr�zmalloc err.\n");
		if( FindHandle != 0 ) {
			_findclose( FindHandle );
		}
		return;
	}
	
	memset( str, 0, ( 1024 * 1024 ));
	
	/* �ϒ������ϊ��擾 --------------------------------------------------- */
	va_start( args, name );
	vsprintf( str, name, args );
	va_end( args );
	
	/* �G���[���b�Z�[�W�o�� ------------------------------------------------- */
	printf("%s", str );
	
	/* find�I�� ------------------------------------------------------------- */
	if( FindHandle != 0 ) {
		_findclose( FindHandle );
	}

	free( str );
	
	return;

}
