/* ------------------------------------------------------------------------- */
/* main.cpp																	 */
/* �b�k�Q�P																	 */
/* �P�O�����\�[�g									 						 */
/*																			 */
/* ------------------------------------------------------------------------- */
/* 	�ԍ�	�X�V���e								�X�V��		���O		 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬								2019/04/24	�����@�a�P	 */
/* 000001	�֐��쐬								2019/05/10	�����@�a�P	 */
/* 000002	��ʍ쐬								2019/05/12	�����@�a�P	 */
/* 000003	�t�@�C���o�͍쐬						2019/05/13	�����@�a�P	 */
/* 000004	�����~���쐬							2019/05/13	�����@�a�P	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��															 */
/* ------------------------------------------------------------------------- */
#include<windows.h>								/* �n�r�@�\�֘A				 */
#include<stdio.h>								/* �W���h�^�n				 */
#include<string.h>

/* ------------------------------------------------------------------------- */
/* �萔��`																	 */
/* ------------------------------------------------------------------------- */
#define AddressNumber 105000 /* �A�h���X�f�[�^����							 */


/* ------------------------------------------------------------------------- */
/* �\���̒�`																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* typedef�錾																 */
/* ------------------------------------------------------------------------- */
typedef unsigned long  ULNG;
typedef unsigned short USHT;
typedef unsigned char  UCHR;
typedef signed   long  SLNG;
typedef signed   char  SCHR;

/* �A�h���X���i�[�\����														 */
typedef	struct Addres_Data {

	UCHR	name[15];			/* ����										 */
	UCHR	fname[11];			/* �c��(�J�i)								 */
	UCHR	mname[15];			/* ���O(�J�i)								 */
	UCHR	sex[2];				/* ����										 */
	UCHR	b_type[2];			/* ���t�^									 */
	UCHR	birthday[11];		/* �a����									 */
	UCHR	phone[14];			/* �d�b�ԍ�									 */
	UCHR	sphone[14];			/* �g�єԍ�									 */
	UCHR	maleadd[39];		/* ���[���A�h���X							 */
	UCHR	post[9];			/* �X�֔ԍ�									 */
	UCHR	s_address[101];		/* �Z��										 */
	UCHR	s_k_address[71];	/* �Z��(�J�i)								 */

}ADDRESS;

ADDRESS *MDp[AddressNumber];

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾															 */
/* ------------------------------------------------------------------------- */
ADDRESS Main_Data[AddressNumber];
UCHR	SS_Input			( UCHR* );
void	SS_FileOpen			( UCHR* , SCHR* );
void	SS_FileWrite		( void );
void	SS_FileRead			( UCHR* );
void	SS_QuickSort3		( ULNG , ULNG , UCHR , UCHR , UCHR );
void	SS_QuickSort2		( ULNG , ULNG , UCHR , UCHR );
void	SS_QuickSort1		( ULNG , ULNG , UCHR );
UCHR	SS_Convertion		( USHT );
void	SS_charchenge		( UCHR* , ULNG );
ULNG	SS_SortChange		( ULNG , UCHR );

/* ------------------------------------------------------------------------- */
/* �֐���	: main			 												 */
/* �@�\��	: �G���g���[�|�C���g											 */
/* �@�\�T�v	: ���Ԍv���������܂��B											 */
/* �쐬��	: 2019/04/24		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

SINT main( SINT argc , SCHR *argv[] )
{
	DWORD			dwStartTime		= 0;
	DWORD			dwEndTime		= 0;

	UCHR			*memp			= NULL;		/* �\���̃|�C���^			 */
	UCHR			us_sortrule[3]  ;			/* �\�[�g����				 */
	UCHR			uc_sortnum		= 0;		/* �\�[�g������				 */

	memset( Main_Data , 0 , sizeof( ADDRESS ) * AddressNumber );

    if ( argc < 2 ) { return 0; }

	/* �֐��Ăяo��															 */
	SS_FileOpen( memp );
	
	uc_sortnum = SS_Input( us_sortrule );


	printf("�\�[�g���J�n���܂�...\n\n");
	/* �V�X�e���N�����Ԃ��擾 */
	dwStartTime = GetTickCount();

	/* ��������������������������������������������������������������������  */
	/* �����ɏ������L�q  */
	
	/* �������ɍ��킹�ĕ���													 */
	switch (uc_sortnum) {
	
		case 1:
			SS_QuickSort1( 0 , AddressNumber - 1 , us_sortrule[0] );
			break;

		case 2:
			SS_QuickSort2( 0 , AddressNumber - 1 , us_sortrule[0] , us_sortrule[1] );
			break;

		default:
			SS_QuickSort3( 0 , AddressNumber - 1 , us_sortrule[0] , us_sortrule[1] , us_sortrule[2] );

	}

	/* ��������������������������������������������������������������������  */

	/* �V�X�e���N�����Ԃ��擾 */
	dwEndTime = GetTickCount();

	/* �����O�ƌ�����̎��Ԃ������A�����ɂ����������Ԃ�\�� */
	printf("%d�b������܂����I\n\n", (dwEndTime - dwStartTime));
	SS_FileWrite(  );
	system( "pause" );
	return 0;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_Input														 */
/* �@�\��	: ���͉��														 */
/* �@�\�T�v	: ���̓C���^�[�t�F�[�X��\�����A�\�[�g������ۑ�����			 */
/* ����		: UCHR*															 */
/* �߂�l	: UCHR															 */
/* �쐬��	: 2019/05/10		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

UCHR SS_Input( UCHR* uc_sortrule ){

	USHT us_sortrule[3];
	UCHR uc_index	= 0;	/* ������										 */

	system("cls");  /* ��ʃN���A											 */

	printf( "\n�A�h���X���\�[�g�v���O�������N�����܂���\n\n" );

	/* �������͊����܂Ń��[�v												 */
	for ( uc_index = 0 ; uc_index < 3 ; uc_index++ ) {

		/* �����\�L															 */
		printf( "1.�����@�@�@�@�@�@2.�c��(�J�i)�@�@�@�@3.���O(�J�i)�@�@�@�@4.����\n\n" );
		printf( "5.���t�^�@�@�@�@�@6.�a�����@�@�@�@�@�@7.�d�b�ԍ��@�@�@�@�@8.�g�єԍ�\n\n" );
		printf( "9.���[���A�h���X�@10.�X�֔ԍ� �@�@�@�@11.�Z���@�@�@�@�@�@ 12.�Z��(�J�i)\n\n\n" );
		
		/* ��������															 */
		printf( "��%d��������̒�����ԍ��őI�����ĉ����� ( �ő�3���� ) ( �I����13 )" , uc_index + 1 );
		scanf_s( "%hd", us_sortrule + uc_index  );
		rewind( stdin );
		*( us_sortrule + uc_index ) -= 1;

		system( "cls" ); /* ��ʃN���A										 */

		/* ���̓G���[														 */
		if ( ( *( us_sortrule + uc_index ) < 0 ) ||
			( *( us_sortrule + uc_index ) > 12 ) ) {

			printf("\n���̓G���[�B�ē��͂��Ă�������\n\n");
			uc_index--;
			continue;

		}else

		/* �I���m�F															 */
		if ( * ( us_sortrule + uc_index ) == 12 ) {
			
			break;

		}else

		/* �d���m�F															 */
		if ( ( ( uc_index == 1 ) &&
			( *us_sortrule == *( us_sortrule + uc_index ) ) ) ||
			( ( uc_index == 2 )  && (
			( *us_sortrule == *( us_sortrule + uc_index ) ) || 
			( *( us_sortrule + 1 ) == *( us_sortrule + uc_index) )
			) ) ) {

			printf("\n�������d�����܂����B�ē��͂��Ă�������\n\n");
			uc_index --;
			continue;

		}

		printf( "\n��%d������t����\n\n" , uc_index + 1 );
	}
	/* �֐��Ăяo��															 */
	for ( UCHR uc_index2 = 0 ; uc_index2 < 3 ; uc_index2++ ) {

		*( uc_sortrule + uc_index2 ) = SS_Convertion( *( us_sortrule + uc_index2 ) );
	
	}

	return uc_index; /* �������Ԋ�											 */
}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_FileOpen													 */
/* �@�\��	: �t�@�C���ǂݍ���												 */
/* �@�\�T�v	: �t�@�C����ǂݍ��ݓ��e�𓮓I�������Ɋi�[����					 */
/* ����		: UCHR* , SCHR+*												 */
/* �߂�l	: 														         */
/* �쐬��	: 2019/05/13		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

void SS_FileOpen( UCHR *memp , SCHR *sc_filename ) {

	errno_t			error			= NULL;		/* �G���[�`�F�b�N			 */
	FILE			*fp				= NULL;		/* �t�@�C���|�C���^			 */
	ULNG			ul_filesize		= 0;		/* �t�@�C���T�C�Y			 */

	/* �t�@�C���I�[�v��		 												 */
	
	error = fopen_s( &fp , ( char * )sc_filename , "rb" );

	/* �t�@�C���`�F�b�N														 */
	if ( error != NULL ) {
		printf( "�G���[�B�t�@�C����������܂���\n" );
		printf( "�v���O�������I�����܂�\n" );
		system( "pause" );
		exit( 0 );
	}

	/* �t�@�C���T�C�Y�`�F�b�N												 */
	fseek( fp , 0 , SEEK_END );
	ul_filesize = ftell( fp );
	fseek( fp , 0 , SEEK_SET );

	/* �������m��															 */
	memp = ( UCHR* )malloc( ul_filesize );


	/* �t�@�C���ǂݍ���														 */
	fread( memp , 1 , ul_filesize , fp );
	fclose( fp );

	SS_FileRead( memp );

}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_FileRead													 */
/* �@�\��	: �\���̂̓��e���쐬											 */
/* �@�\�T�v	: �t�@�C�����瓮�I�������ɓǂݍ��񂾒l���\���̂Ɋi�[����		 */
/* ����		: UCHR *														 */
/* �߂�l	: 																 */
/* �쐬��	: 2019/05/10		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

void SS_FileRead( UCHR *memp ) {

	UCHR			*memp2		= NULL;			/* �\���̃|�C���^�ۊǗp		 */
	ULNG			ul_index	= 0;			/*	�\���̓Y����			 */
	UCHR			uc_index	= 0;			/*	�����o�[�ϐ��Y����		 */
	UCHR			uc_flag		= 0;			/*	�����o�[�ϐ��؂�ւ�	 */
	UCHR			uc_memindex = 0;			/*	�����o�[�ϐ��T�C�Y		 */
	
	memp2 = memp;							/* �擪�A�h���X���m��			 */
	memp += 108;							/* �G�N�Z��1�s�ڂ��X�L�b�v		 */
	printf("�t�@�C���ǂݍ��ݒ�...\n");

	/* �\���̂̃A�h���X��ۊ�												 */
	for ( ul_index = 0 ; ul_index < AddressNumber ; ul_index ++) {
		
		MDp[ul_index] = &Main_Data[ul_index];
	
	}

	ul_index = 0;

	/* �S�f�[�^�\���̂Ɋi�[����܂ł܂Ń��[�v								 */
	while ( 1 ) {

		/* ',' ��ǂݍ��񂾂玟�̃����o�[�ϐ��ֈړ�							 */
		if ( *memp == ',' ) {

			memp ++;
			uc_index = 0;
			uc_flag ++;
			continue;

		}

		/* ���s�ǂݍ���														 */
		else
		if ( *memp == 13 && *( memp + 1 ) == 10 ) {
			uc_index	  = 0;
			uc_flag		  = 0;
			ul_index ++;
			
			/* �I������														 */
			if ( ul_index == AddressNumber ) {
				printf( "�t�@�C���ǂݍ��݊���\n" );
				break;
			}

			/* �擪�̃����o�[�ϐ��ֈړ�										 */
			while ( *( memp - 1 ) != ',' ) {
				memp ++;
			}

		}
		

		/* �����o�[�ϐ���؂�ւ�											 */
		uc_memindex = SS_Convertion ( uc_flag );

		if ( ( uc_flag == 5 ) &&
			( ( uc_index == 5 ) || ( uc_index == 8 ) ) ) {

			if ( ( *( memp + 1 ) == '/' ) ||
				 ( *( memp + 1 ) == ',' ) ) {

				*( MDp[ul_index]->name + ( uc_memindex + uc_index ) ) = '0';
				uc_index ++;

			}

		}

		/* �f�[�^���P�����\���̂֊i�[										 */
		* ( MDp[ul_index] ->name + ( uc_memindex + uc_index ) ) = *memp;
		uc_index++;
		memp ++;
	}

	free( memp2 );

}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_FileWrite													 */
/* �@�\��	: �\���̂̓��e���쐬											 */
/* �@�\�T�v	: �t�@�C�����瓮�I�������ɓǂݍ��񂾒l���\���̂Ɋi�[����		 */
/* ����		:       														 */
/* �߂�l	: 																 */
/* �쐬��	: 2019/05/13		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

void SS_FileWrite ( void ){

	ULNG			ul_loop			= 0;		/* ���[�v��				 */
	ULNG			ul_index		= 0;		/* �\���̂̓Y����			 */
	errno_t			error			= NULL;		/* �G���[�`�F�b�N			 */
	FILE			*fp				= NULL;		/* �t�@�C���|�C���^			 */
	UCHR			uc_filename[80];			/* �t�@�C�����i�[			 */
	UCHR			uc_num[7]		=			/* �擪�̐���				 */
		  { 0 , 0 , 0 , 0 , 0 , 0 , 0 };
	UCHR			uc_index		= 0;		/* �t�@�C���Y����			 */
	UCHR			uc_mem			= 0;		/* �������[�΍�				 */
	UCHR			uc_sort			= 0;		/* �|�C���^�؂�ւ�			 */
	UCHR			uc_change		= 0;

	/* �C���N�������g���������𖖔��ɂ������쐬�t�@�C���̒T��				 */
	for ( uc_index = 0 ; uc_index < 100 ; uc_index ++ ) {
		
		/* �쐬�ς݂��`�F�b�N												 */
		sprintf_s( ( char * ) uc_filename, sizeof( UCHR ) * 80 , "XXX%02d.csv" , uc_index );
		error = fopen_s( &fp , ( char * ) uc_filename , "r" );

		/* ���쐬�t�@�C������    											 */
		if ( error != NULL ) {
			sprintf_s( ( char * )uc_filename , sizeof( UCHR ) * 80 , "XXX%02d.csv" , uc_index );
			error = fopen_s( &fp , ( char * )uc_filename , "wb+" );
			break;
		}

	}

	printf( "�����~����I�����ĉ������i ����:1 , �~��:0 )" );
	scanf_s( "%c" , &uc_change );
	rewind( stdin );

	uc_change -= 48;

	printf("\n�������݂��J�n���܂�...\n\n");

	/* �G�N�Z���P�s��														 */
	fprintf( fp , "No,����,�J�i(�c��),�J�i(���O),����,���t�^,���N����,�d�b�ԍ�,�g�ѓd�b,���[���A�h���X,��,�Z��,�Z���i�J�i�j\r\n"  );
	
	/* �S�f�[�^���t�@�C���ɏ������ނ܂Ń��[�v								 */
	for ( ul_loop = 0 ; ul_loop < AddressNumber; ul_loop ++ ) {

		ul_index = SS_SortChange( ul_loop , uc_change );
		SS_charchenge( uc_num , ul_loop + 1  );

		/* �擪�̐����̊i�[													 */
		fputs( ( char* )uc_num , fp );
		fputc( ',' , fp );

		/* �\���̈���̃����o�[�ϐ����i�[									 */
		for ( uc_sort = 0 ; uc_sort < 12 ; uc_sort++ ) {
			
			/* �����o�[�ϐ������炷											 */
			uc_mem = SS_Convertion( uc_sort );

			/* �����o�[�ϐ�����i�[										 */
			fputs( ( char* ) MDp[ul_index]->name + uc_mem , fp );
			
			/* �Ō�̃����o�[�ϐ����i�[��������s							 */
			if ( uc_sort == 11 ) {

				fputs( "\r\n" , fp );
				break;
			
			}

			/* �����o�[�ϐ���؂��,���i�[									 */
			fputc(',', fp);

		}

	}

	printf("�������݊���\n\n");
}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_charchenge													 */
/* �@�\��	: �����ϊ�														 */
/* �@�\�T�v	: �����𕶎��R�[�h�֕ϊ�����									 */
/* ����		: UCHR*  : ULNG													 */
/* �߂�l	:  																 */
/* �쐬��	: 2019/05/13		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

void SS_charchenge( UCHR *uc_num , ULNG ul_index ) {
	
	UCHR uc_index = 0; /* �z������炷�l									 */

	/* ���g�����Z�b�g														 */
	memset( uc_num , 0 , sizeof( UCHR ) * 7 );

	/* �����̌����ł����[�v													 */
	for ( uc_index = 0 ; ul_index >= 1; uc_index ++ , ul_index /= 10 ) {
		
		/* �������ꌅ���炷													 */
		for ( UCHR uc_index2 = uc_index ; uc_index2 > 0 ; uc_index2 -- ) {
		
			*( uc_num + uc_index2 ) = *( uc_num + uc_index2 - 1 );

		}

		/* �������i�[														 */
		*uc_num = ( ul_index % 10 ) + 48;
		
	}
}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_QuickSort3													 */
/* �@�\��	: �N�C�b�N�\�[�g												 */
/* �@�\�T�v	: �\���̃A�h���X��3�����ɍ��킹�ă\�[�g����						 */
/* ����		: ULNG  : ULNG : UCHR : UCHR : UCHR								 */
/* �߂�l	:  																 */
/* �쐬��	: 2019/05/11		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

void SS_QuickSort3( ULNG ul_start , ULNG ul_end , UCHR uc_sort1 , UCHR uc_sort2 , UCHR uc_sort3 ) {
	
	ULNG		ul_startindex	= ul_start + 1; /* �J�n���̓Y�����̊m��		 */
	ULNG		ul_endindex		= ul_end;		/* �J�n���̓Y�����̊m��		 */
	ULNG		ul_half			= ul_start;		/* �\�[�g��l				 */
	ADDRESS		*ul_space		= NULL;			/* �A�h���X���				 */


	/* �\�[�g�J�n															 */
	while ( 1 ){

		/* ��l�ȏ�̒T��													 */
		for ( ; ul_startindex < ul_endindex ; ul_startindex ++ ) {

			/* �������Ŕ�r												 */
			/* ����ւ��Ώ۔���												 */
			if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort1 ),
				( char* ) ( MDp[ul_half]->name + uc_sort1 ) ) > 0 ) {

				break;

			}

			/* ��r��v���@�������ɑJ��									 */
			if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort1 ),
				( char* ) ( MDp[ul_half]->name + uc_sort1 ) ) == 0 ) {

				/* �������Ŕ�r											 */
				if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort2 ),
					( char* ) ( MDp[ul_half]->name + uc_sort2 ) ) > 0 ) {

					break;

				}

				/* �����s��v�̂��߃��[�v�ɑJ��								 */
				if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort2 ),
					( char* ) ( MDp[ul_half]->name + uc_sort2 ) ) < 0 ) {

					continue;

				}

				/* ��r��v���@��O�����ɑJ��								 */
				else {

					/* ��O�����Ŕ�r										 */
					if ( strcmp ( ( char* ) ( MDp[ul_startindex]->name + uc_sort3 ),
						( char* ) ( MDp[ul_half]->name + uc_sort3 ) ) > 0 ) {

						break;

					}
					/* �����s��v�̂��߃��[�v�ɑJ��							 */
					
				}
				
			}

		}

		/* ��l�ȉ��̒T��													 */
		for ( ; ul_startindex < ul_endindex ; ul_endindex -- ) {

			/* �������Ŕ�r												 */
			/* ����ւ��Ώ۔���												 */
			if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort1 ),
				 ( char* ) ( MDp[ul_half]->name + uc_sort1 ) ) < 0 ) {

				break;

			}

			/* ��r��v���@�������ɑJ��									 */
			if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort1 ),
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) == 0 ) {

				/* �������Ŕ�r											 */
				if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort2 ),
					( char* ) ( MDp[ul_half]->name + uc_sort2 ) ) < 0 ) {

					break;

				}

				/* �����s��v�̂��߃��[�v�ɑJ��								 */
				if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort2 ),
					( char* ) ( MDp[ul_half]->name + uc_sort2 ) ) > 0 ) {

					continue;

				}

				/* ��r��v���@��O�����ɑJ��								 */
				else {

					/* ��O�����Ŕ�r										 */
					if ( strcmp ( ( char* ) ( MDp[ul_endindex]->name + uc_sort3 ),
						( char* ) ( MDp[ul_half]->name + uc_sort3 ) ) <= 0 ) {

						break;

					}
					/* �����s��v�̂��߃��[�v�ɑJ��							 */

				}

			}

		}

		/* ���E�����z�����ꍇ												 */
		if ( ul_startindex >= ul_endindex ) {

		/* ��l���S�v�f�𒴂���ꍇ										 */
			if ( ul_endindex == ul_end ) {
				
				ul_space = MDp[ul_half];
				MDp[ul_half] = MDp[ul_endindex];
				MDp[ul_endindex] = ul_space;
				break;
			
			}
			ul_endindex --;
			ul_space = MDp[ul_half];
			MDp[ul_half] = MDp[ul_endindex];
			MDp[ul_endindex] = ul_space;
			break;

		}

		/* �A�h���X����ւ�													 */
		else {
		
			ul_space		   = MDp[ul_startindex];
			MDp[ul_startindex] = MDp[ul_endindex];
			MDp[ul_endindex]   = ul_space;
			ul_startindex++;
			ul_endindex--;
		}

	}

	/* �\�[�g�ċA�Ăяo��													 */

	if ( ( long )ul_start < ( long )ul_endindex - 1) {

		SS_QuickSort3(ul_start, ul_endindex - 1, uc_sort1, uc_sort2, uc_sort3);

	}

	if ( ( long )ul_endindex + 1 < ( long )ul_end ) {
		 
		SS_QuickSort3(ul_endindex + 1, ul_end, uc_sort1, uc_sort2, uc_sort3);
	
	}
	

}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_QuickSort2													 */
/* �@�\��	: �N�C�b�N�\�[�g												 */
/* �@�\�T�v	: �\���̃A�h���X��2�����ɍ��킹�ă\�[�g����						 */
/* ����		: ULNG  : ULNG : UCHR : UCHR									 */
/* �߂�l	:  																 */
/* �쐬��	: 2019/05/14		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */


void SS_QuickSort2( ULNG ul_start , ULNG ul_end , UCHR uc_sort1 , UCHR uc_sort2 ) {

	ULNG		ul_startindex = ul_start + 1;	/* �J�n���̓Y�����̊m��		 */
	ULNG		ul_endindex	  = ul_end;			/* �J�n���̓Y�����̊m��		 */
	ULNG		ul_half		  = ul_start;		/* �\�[�g��l				 */
	ADDRESS		*ul_space	  = NULL;			/* �A�h���X���				 */


	/* �\�[�g�J�n															 */
	while ( 1 ) {

		/* ��l�ȏ�̒T��													 */
		for ( ; ul_startindex < ul_endindex ; ul_startindex++ ) {

			/* �������Ŕ�r												 */
			/* ����ւ��Ώ۔���												 */
			if ( strcmp ( ( char* )( MDp[ul_startindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) > 0 ) {

				break;

			}

			/* ��r��v���@�������ɑJ��									 */
			if ( strcmp ( ( char* )( MDp[ul_startindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) == 0 ) {

				/* �������Ŕ�r											 */
				if ( strcmp ( ( char* )( MDp[ul_startindex]->name + uc_sort2 ),
					( char* )( MDp[ul_half]->name + uc_sort2 ) ) > 0 ) {

					break;

				}

				/* �����s��v�̂��߃��[�v�ɑJ��								 */

			}

		}

		/* ��l�ȉ��̒T��													 */
		for ( ; ul_startindex < ul_endindex ; ul_endindex -- ) {

			/* �������Ŕ�r												 */
			/* ����ւ��Ώ۔���												 */
			if ( strcmp ( ( char* )( MDp[ul_endindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) < 0) {

				break;

			}

			/* ��r��v���@�������ɑJ��									 */
			if ( strcmp ( ( char* )( MDp[ul_endindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) == 0 ) {

				/* �������Ŕ�r											 */
				if ( strcmp ( ( char* )( MDp[ul_endindex]->name + uc_sort2 ) ,
					( char* )( MDp[ul_half]->name + uc_sort2 ) ) <= 0 ) {

					break;

				}


				/* �����s��v�̂��߃��[�v�ɑJ��									 */

			}

		}


		/* ���E�����z�����ꍇ												 */
		if ( ul_startindex >= ul_endindex ) {

			/* ��l���S�v�f�𒴂���ꍇ										 */
			if ( ul_endindex == ul_end ) {

				ul_space		 = MDp[ul_half];
				MDp[ul_half]     = MDp[ul_endindex];
				MDp[ul_endindex] = ul_space;
				break;

			}
			ul_endindex --;
			ul_space		 = MDp[ul_half];
			MDp[ul_half]	 = MDp[ul_endindex];
			MDp[ul_endindex] = ul_space;
			break;

		}

		/* �A�h���X����ւ�													 */
		else {

			ul_space		    = MDp[ul_startindex];
			MDp[ul_startindex] = MDp[ul_endindex];
			MDp[ul_endindex]   = ul_space;
			ul_startindex ++;
			ul_endindex   --;
		}

	}

	/* �\�[�g�ċA�Ăяo��													 */

	if ( ( long )ul_start < ( long )ul_endindex - 1 ) {

		SS_QuickSort2( ul_start , ul_endindex - 1 , uc_sort1 , uc_sort2 );

	}

	if ( ( long )ul_endindex + 1 < ( long )ul_end ) {

		SS_QuickSort2( ul_endindex + 1 , ul_end, uc_sort1 , uc_sort2 );

	}


}
/* ------------------------------------------------------------------------- */
/* �֐���	: SS_QuickSort1													 */
/* �@�\��	: �N�C�b�N�\�[�g												 */
/* �@�\�T�v	: �\���̃A�h���X��1�����ɍ��킹�ă\�[�g����						 */
/* ����		: ULNG  : ULNG : UCHR											 */
/* �߂�l	:  																 */
/* �쐬��	: 2019/05/14		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

void SS_QuickSort1( ULNG ul_start , ULNG ul_end , UCHR uc_sort1 ) {

	ULNG		ul_startindex = ul_start + 1;   /* �J�n���̓Y�����̊m��		 */
	ULNG		ul_endindex   = ul_end;			/* �J�n���̓Y�����̊m��		 */
	ULNG		ul_half		  = ul_start;		/* �\�[�g��l				 */
	ADDRESS		*ul_space	  = NULL;			/* �A�h���X���				 */


	/* �\�[�g�J�n															 */
	while (1) {

		/* ��l�ȏ�̒T��													 */
		for ( ; ul_startindex < ul_endindex ; ul_startindex ++ ) {

			/* �������Ŕ�r												 */
			/* ����ւ��Ώ۔���												 */
			if ( strcmp ( ( char* )( MDp[ul_startindex]->name + uc_sort1 ) ,
				( char* )( MDp[ul_half]->name + uc_sort1 ) )  > 0 ) {

				break;

			}


		}

		/* ��l�ȉ��̒T��													 */
		for ( ; ul_startindex < ul_endindex ; ul_endindex -- ) {

			/* �������Ŕ�r												 */
			/* ����ւ��Ώ۔���												 */
			if ( strcmp ( ( char* )( MDp[ul_endindex]->name + uc_sort1 ),
				( char* )( MDp[ul_half]->name + uc_sort1 ) ) <= 0 ) {

				break;

			}

			

		}

		/* ���E�����z�����ꍇ												 */
		if ( ul_startindex >= ul_endindex ) {

			/* ��l���S�v�f�𒴂���ꍇ										 */
			if ( ul_endindex == ul_end ) {

				ul_space = MDp[ul_half];
				MDp[ul_half] = MDp[ul_endindex];
				MDp[ul_endindex] = ul_space;
				break;

			}
			ul_endindex--;
			ul_space = MDp[ul_half];
			MDp[ul_half] = MDp[ul_endindex];
			MDp[ul_endindex] = ul_space;
			break;

		}

		/* �A�h���X����ւ�													 */
		else {

			ul_space = MDp[ul_startindex];
			MDp[ul_startindex] = MDp[ul_endindex];
			MDp[ul_endindex] = ul_space;
			ul_startindex++;
			ul_endindex--;
		}

	}

	/* �\�[�g�ċA�Ăяo��													 */
	/* ���ʂ̏ꍇ���ŏI��													 */
	if ( ( uc_sort1 != 41 ) ) {	

		/* �v�f���P��葽��													 */
		if ( ( long )ul_start < ( long )ul_endindex - 1 ) {
		
			SS_QuickSort1( ul_start , ul_endindex - 1 , uc_sort1 );

		}

		/* �v�f���P��葽��													 */
		if ( ( long )ul_endindex + 1 < ( long )ul_end ) {

			SS_QuickSort1( ul_endindex + 1 , ul_end , uc_sort1 );

		}
	}

}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_Convertion													 */
/* �@�\��	: �\�[�g�����̕ϊ�												 */
/* �@�\�T�v	: �\�[�g�����ɍ��킹�ă������̒l�����炷�ϐ��̍쐬				 */
/* ����		: UCHR															 */
/* �߂�l	: UCHR 															 */
/* �쐬��	: 2019/05/10		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

UCHR SS_Convertion( USHT ul_origin ) {

	switch ( ul_origin ) {
	case 0:			//name[15]
		return 0;

	case 1:			//fname[11]
		return 15;

	case 2:			//mname[15]
		return 26;

	case 3:			//sex[2]
		return 41;

	case 4:			//b_type[2]
		return 43;

	case 5:			//birthday[11]
		return 45;

	case 6:			//phone[14]
		return 56;

	case 7:			//sphone[14]
		return 70;

	case 8:			//maleadd[39]
		return 84;

	case 9:			//post[9]
		return 123;

	case 10:		//s_address[101]
		return 132;

	case 11:		//s_k_address[71]
		return 233;

	default:		//���������̏ꍇ
		return 255;
	}
}

/* ------------------------------------------------------------------------- */
/* �֐���	: SS_SortChange													 */
/* �@�\��	: �\�[�g�����̕ϊ�												 */
/* �@�\�T�v	: �\�[�g�����ɍ��킹�ă������̒l�����炷�ϐ��̍쐬				 */
/* ����		: UCHR															 */
/* �߂�l	: UCHR 															 */
/* �쐬��	: 2019/05/10		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

ULNG SS_SortChange( ULNG ul_index , UCHR uc_change ) {

	switch ( uc_change ) {
	
	case 0: return ( AddressNumber - ul_index - 1 );

	default: return ul_index;

	}

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */