#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "map.h"
#define startx 10
#define starty 9

/*主選單框架*/ 
void menuframe(){
	map m;
	frame(&m);
	gotoxy(startx,starty-1);
	printf("★======跑酷遊戲====== ★");
	gotoxy(startx+2,starty);
	printf("新遊戲");
	gotoxy(startx+2,starty+1);
	printf("選擇存檔");
	gotoxy(startx+2,starty+2);
	printf("遊戲說明");
	gotoxy(startx+2,starty+3);
	printf("Exit");
	gotoxy(startx+2,starty+10);
	printf("以上下鍵控制主選單");
}

/*選單選擇之控制*/ 
int select(int num){
	int o,s=1,count=0;
	gotoxy(startx,starty);
	printf("=>");
	while(o!=13){
		if(kbhit ){
			o=getch();
			switch(o){
				case 80:{//往下 
					if(count+1<=num-1){
						gotoxy(startx,starty+count);
						printf("  ");
						count++;
						gotoxy(startx,starty+count);
						printf("=>");
						s++;
					}
					
					break;
				}
				case 72:{//往上 
					if(count-1>=0){
						gotoxy(startx,starty+count);
						printf("  ");
						count--;
						gotoxy(startx,starty+count);
						printf("=>");
						s--;
					}
					
					break;
				}
			
			}
		}
	}
	return s;	
}

/*遊戲說明*/ 
void gamerule(){
	system("cls");
	map m;
	frame(&m);
	gotoxy(startx,starty-5);
	printf("★=================遊戲說明================= ★");
	gotoxy(startx+2,starty-3);
	printf("1.玩家可操控左右鍵來控制角色移動,空白鍵來控制跳躍");
	gotoxy(startx+2,starty-1);
	printf("2.#為地圖邊界,玩家無法超出邊界");
	gotoxy(startx+2,starty+1);
	printf("3.■為實心方塊,玩家無法穿透此方塊,但可以站立在上面");
	gotoxy(startx+2,starty+3);
	printf("4.□為伸縮方塊,當此方塊伸出並撞上玩家時遊戲結束");
	gotoxy(startx+2,starty+5);
	printf("5.△為checkpoint,當玩家吃掉此方塊,則會記錄玩家的所在位子");
	gotoxy(startx+2,starty+7);
	printf("  吃掉最後一個checkpoint後取得遊戲勝利");
	gotoxy(startx+2,starty+9);
	printf("6.注意遊玩時請將輸入法改成英文小寫輸入法");
	gotoxy(startx+2,starty+11);
	printf("7.遊玩時可以按s來儲存檔案");
	gotoxy(startx+2,starty+13);
	printf("8.遊玩時和讀完遊戲說明後,可按ESC鍵回到主選單");
	while(1){
		if(kbhit()){
			if(getch()==27){
				break;
			}
		}
	}
	system("cls");
	return;
}

/*關卡選擇*/ 
void levelframe(){
	map m;
	frame(&m);
	gotoxy(startx,starty-1);
	printf("★======關卡選擇====== ★");
	gotoxy(startx+2,starty);
	printf("第一關");
	gotoxy(startx+2,starty+1);
	printf("第二關");
	gotoxy(startx+2,starty+2);
	printf("第三關");
	gotoxy(startx+2,starty+3);
	printf("主選單");
	gotoxy(startx+2,starty+10);
	printf("以上下鍵控制選單");
}

 







