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



#define CLEAR_NUM 2048				//目標値

/*色定義*/
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
#define COL_INTENSITY	0x08		//高輝度マスク
#define COL_RED_MASK	0x04
#define COL_GREEN_MASK	0x02
#define COL_BLUE_MASK	0x01

/*共通関数定義*/
int i, j;							//配列の添え字
int x, y;							//2のポップ位置の座標
int cnt;							//カウンタ変数
int sec;							//プレイ秒数
int score;							//スコア

/*関数プロトタイプ*/
void set_color(int, int);					//色指定関数
void menu();								//メニュー表示用関数
void init_board(int board[4][4]);			//ボード初期化用関数
void print_board(int board[4][4]);	//ボード出力用関数
void move(int, int board[4][4]);	//移動処理用関数



void main(){

	int flg = 0;					//終了フラグ
	char inp;						//文字入力用変数
	int board[4][4];				//ボード用配列
	time_t t1, t2;

	/*メニュー*/
	do{
		system("cls");						//画面クリア
		set_color(COL_GREEN, COL_BLACK);
		menu();								//メニュー表示
		inp = getch();
		Beep(330,200);						//セレクト音
		switch(inp){
			/*スタート*/
			case '1':
				break;
			/*終了*/
			case '3':
				system("cls");				//画面クリア
				printf("Exit...\n");
				exit(1);
			/*エラーメッセージ*/
			default :
				system("cls");
				set_color(COL_RED, COL_BLACK);
				printf("Please input 1 or 2 or 3.\n");
				Beep(180,600);			//警告音
				Sleep(300);
				set_color(COL_GREEN, COL_BLACK);
				break;
		}
	}while(inp != '1');

	/*ゲーム開始*/
	time(&t1);						//開始時間をt1に格納
	srand((unsigned) time(NULL));	//乱数系列の変更
	init_board(board);				//ボード初期化
	while(flg == 0){
		system("cls");				//画面クリア
		time(&t2);					//現在時刻をt2に格納
		sec = difftime(t2, t1);		//かかった秒数を計算
		print_board(board);	//ボード表示

		inp = getch();				//入力
		Beep(400,200);				//入力音

		/*W, A, S, D の入力がそれぞれ↑, ←, ↓, → に対応*/
		switch(inp){
			//↑上移動
			case 'w':
				move(0, board);
				break;
			//←左移動
			case 'a':
				move(1, board);
				break;
			//↓下移動
			case 's':
				move(2, board);
				break;
			//→右移動
			case 'd':
				move(3, board);
				break;
			//中断,断念
			case '0':
				flg = 2;
				break;
			default :
				break;
		}
		/*目標値に達していればクリアフラグを立て,スコア+5000*/
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
	if(flg == 1){		//クリアフラグが立っていれば
		printf("Clear!\n");
		printf("Bonus >> 5000pt\n");
		printf("Score >> %dpt\n", score);
	}if(flg == 2){		//中断フラグが立っていれば
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
	/*タイトルをアスキーアートで表示*/
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
	/*ボードを0で初期化*/
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			board[i][j] = 0;
		}
	}
	/*ボードにランダムで2を2つ配置*/
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
	for(i = 0; i < 13; i++){	//13行
		set_color(COL_BLACK, COL_DARK_GREEN);
		if(i % 3 == 0)				//3行ごとに枠を表示
			printf("                          \n");		//ボード枠
		else{
			for(j = 0; j < 4; j++){	//列
				printf("  ");
				/*ブロックの色設定*/
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
				/*ブロックの表示*/
				if(i % 3 == 1 || i % 3 == 2)
					printf("    ");
				set_color(COL_BLACK, COL_DARK_GREEN);
			}
			set_color(COL_BLACK, COL_DARK_GREEN);
			printf("  \n");
		}
	}
	set_color(COL_GREEN, COL_BLACK);

	/*操作方法表示*/
	printf("W : ↑\n");
	printf("A : ←\n");
	printf("S : ↓\n");
	printf("D : →\n");
	printf("0 : quit\n");
}

///////////////////////////////////////////////////////////////////////////////

void move(int direction, int board[4][4]){

	int a, b;							//移動元セルの座標
	int s, t;							//移動先セルの座標
	/*最高3回移動が必要*/
	cnt = 0;
	while(cnt < 3){
		/*移動方向に応じて移動先セルの始行と終行を決定*/
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
			/*移動方向に応じて移動先セルの始列と終列を決定*/
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
				/*移動方向に応じて移動元セルを決定*/
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
				if(board[a][b] != 0){			//移動元セルが0でない場合
					if(board[i][j] == board[a][b]){//移動元セルと移動先セルが同じ数の場合,足し合わせる
						score += board[i][j];	//足し合わせる数字をスコアに加算
						board[i][j] *= 2;
						board[a][b] = 0;
						Beep(600,200);			//200ミリ秒鳴らす
					}
					if(board[i][j] == 0){		//移動先セルが0の場合
						board[i][j] = board[a][b];
						board[a][b] = 0;
					}
				}
				/*左移動のときのみ列の添え字jをデクリメント*/
				if(direction == 3){
					j--;
				}else{
					j++;
				}
			}
			/*下移動のときのみ行の添え字iをデクリメント*/
			if(direction == 2){
				i--;
			}else{
				i++;
			}
		}
		/*1行移動ごとに表示*/
		system("cls");
		print_board(board);
		Sleep(50);
		cnt++;
	}
	/*移動方向の逆端に2をポップ*/
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
