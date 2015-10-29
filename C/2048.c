/*2048.c*/
/*

***** ***** *  *  *****
    * *   * *  *  *   *
***** *   * ***** *****
*     *   *    *  *   *
***** *****    *  *****

*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>



#define CLEAR_NUM 2048				//�ڕW�l

/*�F��`*/
#define COL_BLACK		0x00
#define COL_DARK_BLUE	0x01
#define COL_DARK_GREEN	0x02
#define COL_DARK_CYAN	0x03
#define COL_DARK_RED	0x04
#define COL_DARK_VIOLET	0x05
#define COL_DARK_YELLOW	0x06
#define COL_GRAY		0x07
#define COL_LIGHT_GRAY	0x08
#define COL_BLUE 		0x09
#define COL_GREEN		0x0a
#define COL_CYAN		0x0b
#define COL_RED			0x0c
#define COL_VIOLET		0x0d
#define COL_YELLOW		0x0e
#define COL_WHITE		0x0f
#define COL_INTENSITY	0x08		//���P�x�}�X�N
#define COL_RED_MASK	0x04
#define COL_GREEN_MASK	0x02
#define COL_BLUE_MASK	0x01

/*���ʊ֐���`*/
int i, j;							//�z��̓Y����
int x, y;							//2�̃|�b�v�ʒu�̍��W
int cnt;							//�J�E���^�ϐ�
int sec;							//�v���C�b��
int score;							//�X�R�A

/*�֐��v���g�^�C�v*/
void set_color(int, int);					//�F�w��֐�
void menu();								//���j���[�\���p�֐�
void init_board(int board[4][4]);			//�{�[�h�������p�֐�
void print_board(int board[4][4]);	//�{�[�h�o�͗p�֐�
void move(int, int board[4][4]);	//�ړ������p�֐�



void main(){

	int flg = 0;					//�I���t���O
	char inp;						//�������͗p�ϐ�
	int board[4][4];				//�{�[�h�p�z��
	time_t t1, t2;

	/*���j���[*/
	do{
		system("cls");						//��ʃN���A
		set_color(COL_GREEN, COL_BLACK);
		menu();								//���j���[�\��
		inp = getch();
		Beep(330,200);						//�Z���N�g��
		switch(inp){
			/*�X�^�[�g*/
			case '1':
				break;
			/*�I��*/
			case '3':
				system("cls");				//��ʃN���A
				printf("Exit...\n");
				exit(1);
			/*�G���[���b�Z�[�W*/
			default :
				system("cls");
				set_color(COL_RED, COL_BLACK);
				printf("Please input 1 or 2 or 3.\n");
				Beep(180,600);			//�x����
				Sleep(300);
				set_color(COL_GREEN, COL_BLACK);
				break;
		}
	}while(inp != '1');

	/*�Q�[���J�n*/
	time(&t1);						//�J�n���Ԃ�t1�Ɋi�[
	srand((unsigned) time(NULL));	//�����n��̕ύX
	init_board(board);				//�{�[�h������
	while(flg == 0){
		system("cls");				//��ʃN���A
		time(&t2);					//���ݎ�����t2�Ɋi�[
		sec = difftime(t2, t1);		//���������b�����v�Z
		print_board(board);	//�{�[�h�\��

		inp = getch();				//����
		Beep(400,200);				//���͉�

		/*W, A, S, D �̓��͂����ꂼ�ꁪ, ��, ��, �� �ɑΉ�*/
		switch(inp){
			//����ړ�
			case 'w':
				move(0, board);
				break;
			//�����ړ�
			case 'a':
				move(1, board);
				break;
			//�����ړ�
			case 's':
				move(2, board);
				break;
			//���E�ړ�
			case 'd':
				move(3, board);
				break;
			//���f,�f�O
			case '0':
				flg = 2;
				break;
			default :
				break;
		}
		/*�ڕW�l�ɒB���Ă���΃N���A�t���O�𗧂�,�X�R�A+5000*/
		for(i = 0; i < 4; i++){
			for(j = 0; j < 4; j++){
				if(board[i][j] == CLEAR_NUM){
					flg = 1;
					score += 5000;
				}
			}
		}
	}
	set_color(COL_GREEN, COL_BLACK);
	if(flg == 1){		//�N���A�t���O�������Ă����
		printf("Clear!\n");
		printf("Bonus >> 5000pt\n");
		printf("Score >> %dpt\n", score);
	}if(flg == 2){		//���f�t���O�������Ă����
		printf("Failed...\n");
		printf("Score >> %dpt\n", score);
	}
}

//////////////////////////////////////////////////////////////////////////////////////

void set_color(int fg, int bg)
{
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attr = 0;
	if(fg & COL_INTENSITY)
		attr |= FOREGROUND_INTENSITY;
	if(fg & COL_RED_MASK)
		attr |= FOREGROUND_RED;
	if(fg & COL_GREEN_MASK)
		attr |= FOREGROUND_GREEN;
	if(fg & COL_BLUE_MASK)
		attr |= FOREGROUND_BLUE;

	if(bg & COL_INTENSITY)
		attr |= BACKGROUND_INTENSITY;
	if(bg & COL_RED_MASK)
		attr |= BACKGROUND_RED;
	if(bg & COL_GREEN_MASK)
		attr |= BACKGROUND_GREEN;
	if(bg & COL_BLUE_MASK)
		attr |= BACKGROUND_BLUE;
	SetConsoleTextAttribute(hCons, attr);
}

///////////////////////////////////////////////////////////////////////////////

void menu(){
	/*�^�C�g�����A�X�L�[�A�[�g�ŕ\��*/
	printf("***** ***** *  *  *****\n");
	printf("    * *   * *  *  *   *\n");
	printf("***** *   * ***** *****\n");
	printf("*     *   *    *  *   *\n");
	printf("***** *****    *  *****\n\n");
	printf("1:Start.\n");
	printf("3:Exit.\n");
}

///////////////////////////////////////////////////////////////////////////////

void init_board(int board[4][4]){
	/*�{�[�h��0�ŏ�����*/
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			board[i][j] = 0;
		}
	}
	/*�{�[�h�Ƀ����_����2��2�z�u*/
	cnt = 0;
	while(cnt < 2){
		for(i = 0; i < 100; i++){
			x = (int)(rand() % 4);
		}
		for(i = 0; i < 100; i++){
			y = (int)(rand() % 4);
		}
		if(board[x][y] == 0){
			board[x][y] = 2;
			cnt++;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void print_board(int board[4][4]){

	printf("TIME:%d\tSCORE:%d\n", sec, score);
	for(i = 0; i < 13; i++){	//13�s
		set_color(COL_BLACK, COL_DARK_GREEN);
		if(i % 3 == 0)				//3�s���Ƃɘg��\��
			printf("                          \n");		//�{�[�h�g
		else{
			for(j = 0; j < 4; j++){	//��
				printf("  ");
				/*�u���b�N�̐F�ݒ�*/
				switch(board[i / 3][j]){
					case 2:
						set_color(COL_BLACK, COL_WHITE);
						break;
					case 4:
						set_color(COL_BLACK, COL_GRAY);
						break;
					case 8:
						set_color(COL_BLACK, COL_LIGHT_GRAY);
						break;
					case 16:
						set_color(COL_BLACK, COL_YELLOW);
						break;
					case 32:
						set_color(COL_WHITE, COL_DARK_YELLOW);
						break;
					case 64:
						set_color(COL_BLACK, COL_RED);
						break;
					case 128:
						set_color(COL_WHITE, COL_DARK_RED);
						break;
					case 256:
						set_color(COL_BLACK, COL_VIOLET);
						break;
					case 512:
						set_color(COL_WHITE, COL_DARK_VIOLET);
						break;
					case 1024:
						set_color(COL_BLACK, COL_CYAN);
						break;
					case 2048:
						set_color(COL_WHITE, COL_BLUE);
						break;
					default:
						set_color(COL_BLACK, COL_GREEN);
						break;
				}
				/*�u���b�N�̕\��*/
				if(i % 3 == 1 || i % 3 == 2)
					printf("    ");
				set_color(COL_BLACK, COL_DARK_GREEN);
			}
			set_color(COL_BLACK, COL_DARK_GREEN);
			printf("  \n");
		}
	}
	set_color(COL_GREEN, COL_BLACK);

	/*������@�\��*/
	printf("W : ��\n");
	printf("A : ��\n");
	printf("S : ��\n");
	printf("D : ��\n");
	printf("0 : quit\n");
}

///////////////////////////////////////////////////////////////////////////////

void move(int direction, int board[4][4]){

	int a, b;							//�ړ����Z���̍��W
	int s, t;							//�ړ���Z���̍��W
	/*�ō�3��ړ����K�v*/
	cnt = 0;
	while(cnt < 3){
		/*�ړ������ɉ����Ĉړ���Z���̎n�s�ƏI�s������*/
		if(direction == 2){
			i = 3;
			s = 0;
		}else{
			i = 0;
			if(direction == 0){
				s = 3;
			}else{
				s = 4;
			}
		}

		while(i != s){
			/*�ړ������ɉ����Ĉړ���Z���̎n��ƏI�������*/
			if(direction == 3){
				j = 3;
				t = 0;
			}else{
				j = 0;
				if(direction == 1){
					t = 3;
				}else{
					t = 4;
				}
			}

			while(j != t){
				/*�ړ������ɉ����Ĉړ����Z��������*/
				if(direction == 0){
					a = i + 1;
					b = j;
				}
				if(direction == 1){
					a = i;
					b = j + 1;
				}
				if(direction == 2){
					a = i - 1;
					b = j;
				}
				if(direction == 3){
					a = i;
					b = j - 1;
				}
				if(board[a][b] != 0){			//�ړ����Z����0�łȂ��ꍇ
					if(board[i][j] == board[a][b]){//�ړ����Z���ƈړ���Z�����������̏ꍇ,�������킹��
						score += board[i][j];	//�������킹�鐔�����X�R�A�ɉ��Z
						board[i][j] *= 2;
						board[a][b] = 0;
						Beep(600,200);			//200�~���b�炷
					}
					if(board[i][j] == 0){		//�ړ���Z����0�̏ꍇ
						board[i][j] = board[a][b];
						board[a][b] = 0;
					}
				}
				/*���ړ��̂Ƃ��̂ݗ�̓Y����j���f�N�������g*/
				if(direction == 3){
					j--;
				}else{
					j++;
				}
			}
			/*���ړ��̂Ƃ��̂ݍs�̓Y����i���f�N�������g*/
			if(direction == 2){
				i--;
			}else{
				i++;
			}
		}
		/*1�s�ړ����Ƃɕ\��*/
		system("cls");
		print_board(board);
		Sleep(50);
		cnt++;
	}
	/*�ړ������̋t�[��2���|�b�v*/
	if(direction == 0){
		x = 3;
		y = (int)(rand() % 4);
	}if(direction == 1){
		x = (int)(rand() % 4);
		y = 3;
	}if(direction == 2){
		x = 0;
		y = (int)(rand() % 4);
	}if(direction == 3){
		x = (int)(rand() % 4);
		y = 0;
	}
	if(board[x][y] == 0)
		board[x][y] = 2;
}
