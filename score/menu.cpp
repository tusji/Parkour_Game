#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "map.h"
#define startx 10
#define starty 9

/*�D���ج[*/ 
void menuframe(){
	map m;
	frame(&m);
	gotoxy(startx,starty-1);
	printf("��======�]�ŹC��====== ��");
	gotoxy(startx+2,starty);
	printf("�s�C��");
	gotoxy(startx+2,starty+1);
	printf("��ܦs��");
	gotoxy(startx+2,starty+2);
	printf("�C������");
	gotoxy(startx+2,starty+3);
	printf("Exit");
	gotoxy(startx+2,starty+10);
	printf("�H�W�U�䱱��D���");
}

/*����ܤ�����*/ 
int select(int num){
	int o,s=1,count=0;
	gotoxy(startx,starty);
	printf("=>");
	while(o!=13){
		if(kbhit ){
			o=getch();
			switch(o){
				case 80:{//���U 
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
				case 72:{//���W 
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

/*�C������*/ 
void gamerule(){
	system("cls");
	map m;
	frame(&m);
	gotoxy(startx,starty-5);
	printf("��=================�C������================= ��");
	gotoxy(startx+2,starty-3);
	printf("1.���a�i�ޱ����k��ӱ���Ⲿ��,�ť���ӱ�����D");
	gotoxy(startx+2,starty-1);
	printf("2.#���a�����,���a�L�k�W�X���");
	gotoxy(startx+2,starty+1);
	printf("3.������ߤ��,���a�L�k��z�����,���i�H���ߦb�W��");
	gotoxy(startx+2,starty+3);
	printf("4.�������Y���,��������X�ü��W���a�ɹC������");
	gotoxy(startx+2,starty+5);
	printf("5.����checkpoint,���a�Y�������,�h�|�O�����a���Ҧb��l");
	gotoxy(startx+2,starty+7);
	printf("  �Y���̫�@��checkpoint����o�C���ӧQ");
	gotoxy(startx+2,starty+9);
	printf("6.�`�N�C���ɽбN��J�k�令�^��p�g��J�k");
	gotoxy(startx+2,starty+11);
	printf("7.�C���ɥi�H��s���x�s�ɮ�");
	gotoxy(startx+2,starty+13);
	printf("8.�C���ɩMŪ���C��������,�i��ESC��^��D���");
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

/*���d���*/ 
void levelframe(){
	map m;
	frame(&m);
	gotoxy(startx,starty-1);
	printf("��======���d���====== ��");
	gotoxy(startx+2,starty);
	printf("�Ĥ@��");
	gotoxy(startx+2,starty+1);
	printf("�ĤG��");
	gotoxy(startx+2,starty+2);
	printf("�ĤT��");
	gotoxy(startx+2,starty+3);
	printf("�D���");
	gotoxy(startx+2,starty+10);
	printf("�H�W�U�䱱����");
}

 







