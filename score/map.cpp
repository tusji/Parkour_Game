#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <omp.h>
#include<string.h>
#include "map.h"
#include "menu.h"
#include "sync.h"
#define startx 10
#define starty 9

/*設置地圖屏障*/

 bool Map(int xpos,int ypos,const map *m){
	if(m->map[xpos][ypos]==1){
		return true;
	}
	else return false;
}

/*出生點控制*/ 

void resetxy(int xpos,int ypos,pos *p){
	p->xpose=xpos;
	p->ypose=ypos;
}

/*死亡判定*/ 
bool dead(int xpos,int ypos,const pos *p){
	if((p->xpose==xpos &&p->ypose==ypos)||(p->xpose+1==xpos &&p->ypose==ypos)||(p->xpose==xpos+1 &&p->ypose==ypos))return true;
	else return false;
}

/*游標控制*/ 
void gotoxy(int xpos, int ypos){
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

/*列印玩家*/ 
void player(const pos *p){
	csentrance(2);
	gotoxy(p->xpose,p->ypose);
	printf("★");
	csexit(2);
} 
void clear(const pos *p){
	gotoxy(p->xpose,p->ypose);
	printf(" ");
}
/*獲取二段跳*/ 

void easteregg(doublejump *dj){
	dj->eggavailable=true;
}
void equip(doublejump *dj){
	dj->doublej=true;
	dj->avail=true;
}
void cancel(doublejump *dj){
	dj->doublej=false;
	dj->avail=false;
}

/*墜落控制*/ 
int falling(bool* game ,pos *p,doublejump *dj,const map *m){
	int mode;
	while(Map(p->xpose,p->ypose+1,m)==false && Map(p->xpose+1,p->ypose+1,m)==false){
		if(*game)return 0;
		csentrance(2);
		clear(p);
		p->ypose++;
		csexit(2);
		if(kbhit()){
			mode=getch();
			if(mode==77 && Map(p->xpose+2,p->ypose,m)==false){
				csentrance(2);
				p->xpose++;
				csexit(2);
			}
			if(mode==75 && Map(p->xpose-1,p->ypose,m)==false){
				csentrance(2);
				p->xpose--;
				csexit(2);
			} 
			if(mode==32 && dj->doublej){
				dj->doublej=false;
				player(p);
				for(int i=1;i<=6;i++){
					if(*game)return 0;
					Sleep(100);				
					if(Map(p->xpose,p->ypose-1,m) || Map(p->xpose+1,p->ypose-1,m)){
						break;
					}
					csentrance(2);
					clear(p);
					p->ypose--;
					csexit(2);
					if(kbhit()){
						mode=getch();
						if(mode==77 && Map(p->xpose+2,p->ypose,m)==false){
							csentrance(2);
							p->xpose++;
							csexit(2);
						}
						if(mode==75 && Map(p->xpose-1,p->ypose,m)==false){
							csentrance(2);
							p->xpose--;
							csexit(2);
						}
						if(mode==27){
							return 1;
						}
						if(mode==115){
							return 2;
						}
					} 
					player(p);
				}
			}
			if(mode==27){
				return 1;
			}
			if(mode==115){
				return 2;
			}
		}
		player(p);
		
		Sleep(100);
	}
	if(dj->avail)dj->doublej=1;
	return 0;
}

/*移動家跳躍控制*/ 
int walk(bool*game ,pos *p,doublejump *dj,const map*m){
	int key;
	if(kbhit()){
		key=getch();
		switch(key){
			case 77:{//go righ
				if(Map(p->xpose+2,p->ypose,m)==false){
					csentrance(2);
					clear(p);
					p->xpose++;
					csexit(2);
					player(p);
					
				}	
				break;
			}
			case 75:{//go left
				if(Map(p->xpose-1,p->ypose,m)==false){
				csentrance(2);
				clear(p);
				p->xpose--;
				csexit(2);
				player(p);
				
				}
				break;
			}            
			case 32:{//jump
				DoubleJump:;
				for(int i=1;i<=6;i++){
					if(*game)return false;
					Sleep(100);				
					if(Map(p->xpose,p->ypose-1,m) || Map(p->xpose+1,p->ypose-1,m)){
						break;
					}
					csentrance(2);
					clear(p);
					p->ypose--;
					csexit(2);
					if(kbhit()){
						key=getch();
						if(key==77 && Map(p->xpose+2,p->ypose,m)==false){
							csentrance(2);
							p->xpose++;
							csexit(2);
						}
						if(key==75 && Map(p->xpose-1,p->ypose,m)==false){
							csentrance(2);
							p->xpose--;
							csexit(2);
						}
						if(key==32 && dj->doublej){
							dj->doublej=false;
							goto DoubleJump; 
						}
						if(key==27){
							return true;
						}
					}
					 
					player(p);
				}
				break;
			}
			case 113:{
				if(dj->eggavailable){
					if(!dj->avail)equip(dj);
					else if(dj->avail)cancel(dj);
				}
				break;
			}
			case 115:{
				return 2;
				break;
			}
			case 27:{
				return 1;
			}	
		}
	}
	return 0;
}

/*記錄點判定*/ 
bool stateclear(int xpos ,int ypos ,const pos *p){
	if((p->xpose==xpos && p->ypose == ypos)||(p->xpose==xpos+1 && p->ypose == ypos)||(p->xpose==xpos-1 && p->ypose == ypos))return true;
	else return false;
}
 




/*生成方塊*/ 
void block(int xpos,int ypos,int mod,map *m){
	gotoxy(xpos,ypos);
	switch(mod){
		case 0:{
			printf("#");
			m->map[xpos][ypos]=1;
			break;
		}
		case 1:{
			printf("■");
			m->map[xpos][ypos]=1;
			m->map[xpos+1][ypos]=1;
			break;
		}
		case 2:{
			printf("□");
			m->map[xpos][ypos]=1;
			m->map[xpos+1][ypos]=1;
			break;
		}
		case 3:{
			printf("△");
			break;
		}
		case 4:{
			printf(" ");
			m->map[xpos][ypos]=1;
			break;
		}
		case 5:{
			printf("◎");
			break;
		}
		case 6:{
			printf("#");
			break;
		}
	}
	
}

/*生成大方塊*/ 
void bigblock(int xpos,int ypos,int l,int h,map *m){
	for(int i=0;i<h;i++){
		for(int j=0;j<2*l;j+=2){
			block(xpos+j,ypos+i,1,m);
		}
	}
}

/*清除方塊*/ 
void clearblock(int xpos,int ypos,map *m){
	gotoxy(xpos,ypos);
	printf(" ");
	m->map[xpos][ypos]=0;
}

/*生成地圖邊界*/
void frame(map *m){
	for(int i=2;i<=69;i++){
		for(int j=2;j<=24;j++){
			if(i==2 || j==2 ||i==69|| j==24){
				block(i,j,0,m);
			}
		}
	}
}

/*生成移動方塊*/



bool moveblock(int xpos,int ypos,int len,int mod,int id,int count,map *m,const pos *p){
	if(!m->mb[id].used){
		m->mb[id].mbxy[0]=xpos;
		m->mb[id].mbxy[1]=ypos;
		csentrance(1); 
		block(xpos,ypos,1,m);
		csexit(1);
		m->mb[id].used=true;
	}
	switch(mod){////
	
		case 1:{//往上 
			if(m->mb[id].mblength<len && m->mb[id].up==0){
				csentrance(1);
				m->mb[id].mbxy[1]--;
				m->mb[id].mblength++; 
				if(dead(m->mb[id].mbxy[0],m->mb[id].mbxy[1],p)){
					csexit(1);
					return true; 
				}
				block(m->mb[id].mbxy[0],m->mb[id].mbxy[1],2,m);
				csexit(1);	
			}
			else if(m->mb[id].mblength==len && count==0){
				m->mb[id].up=1;
				csentrance(1);
				clearblock(m->mb[id].mbxy[0],m->mb[id].mbxy[1],m);
				clearblock(m->mb[id].mbxy[0]+1,m->mb[id].mbxy[1],m);
				csexit(1);
				m->mb[id].mbxy[1]++;
				m->mb[id].mblength--;
			}
			else if(m->mb[id].mblength>0 && m->mb[id].up==1 && count==0){
				csentrance(1);
				clearblock(m->mb[id].mbxy[0],m->mb[id].mbxy[1],m);
				clearblock(m->mb[id].mbxy[0]+1,m->mb[id].mbxy[1],m);
				csexit(1);
				m->mb[id].mbxy[1]++;
				m->mb[id].mblength--;
			}
			else if(m->mb[id].mblength==0){
				m->mb[id].up=0;
				csentrance(1);
				m->mb[id].mbxy[1]--;
				m->mb[id].mblength++;
				if(dead(m->mb[id].mbxy[0],m->mb[id].mbxy[1],p)){
					csexit(1);
					return true; 
				}
				block(m->mb[id].mbxy[0],m->mb[id].mbxy[1],2,m);
				csexit(1);	
			}
			break;
		}
		case 2:{//往下
			if(m->mb[id].mblength<len && m->mb[id].up==0){
				csentrance(1);
				m->mb[id].mbxy[1]++;
				m->mb[id].mblength++; 
				if(dead(m->mb[id].mbxy[0],m->mb[id].mbxy[1],p)){
					csexit(1);
					return true; 
				}
				block(m->mb[id].mbxy[0],m->mb[id].mbxy[1],2,m);
				csexit(1);	
			}
			else if(m->mb[id].mblength==len && count==0){
				m->mb[id].up=1;
				csentrance(1);
				clearblock(m->mb[id].mbxy[0],m->mb[id].mbxy[1],m);
				clearblock(m->mb[id].mbxy[0]+1,m->mb[id].mbxy[1],m);
				csexit(1);
				m->mb[id].mbxy[1]--;
				m->mb[id].mblength--;
			}
			else if(m->mb[id].mblength>0 && m->mb[id].up==1 && count==0){
				csentrance(1);
				clearblock(m->mb[id].mbxy[0],m->mb[id].mbxy[1],m);
				clearblock(m->mb[id].mbxy[0]+1,m->mb[id].mbxy[1],m);
				csexit(1);
				m->mb[id].mbxy[1]--;
				m->mb[id].mblength--;
			}
			else if(m->mb[id].mblength==0){
				m->mb[id].up=0;
				csentrance(1);
				m->mb[id].mbxy[1]++;
				m->mb[id].mblength++;
				if(dead(m->mb[id].mbxy[0],m->mb[id].mbxy[1],p)){
					csexit(1);
					return true; 
				}
				block(m->mb[id].mbxy[0],m->mb[id].mbxy[1],2,m);
				csexit(1);	
			} 
			break;
		}
		case 3:{//往左 
			if(m->mb[id].mblength<len && m->mb[id].up==0){
				csentrance(1);
				m->mb[id].mbxy[0]-=2;
				m->mb[id].mblength++; 
				if(dead(m->mb[id].mbxy[0],m->mb[id].mbxy[1],p)){
					csexit(1);
					return true; 
				}
				block(m->mb[id].mbxy[0],m->mb[id].mbxy[1],2,m);
				csexit(1);	
			}
			else if(m->mb[id].mblength==len && count==0){
				m->mb[id].up=1;
				csentrance(1);
				clearblock(m->mb[id].mbxy[0],m->mb[id].mbxy[1],m);
				clearblock(m->mb[id].mbxy[0]+1,m->mb[id].mbxy[1],m);
				csexit(1);
				m->mb[id].mbxy[0]+=2;;
				m->mb[id].mblength--;
			}
			else if(m->mb[id].mblength>0 && m->mb[id].up==1 && count==0){
				csentrance(1);
				clearblock(m->mb[id].mbxy[0],m->mb[id].mbxy[1],m);
				clearblock(m->mb[id].mbxy[0]+1,m->mb[id].mbxy[1],m);
				csexit(1);
				m->mb[id].mbxy[0]+=2;;
				m->mb[id].mblength--;
			}
			else if(m->mb[id].mblength==0){
				m->mb[id].up=0;
				csentrance(1);
				m->mb[id].mbxy[0]-=2;;
				m->mb[id].mblength++;
				if(dead(m->mb[id].mbxy[0],m->mb[id].mbxy[1],p)){
					csexit(1);
					return true; 
				}
				block(m->mb[id].mbxy[0],m->mb[id].mbxy[1],2,m);
				csexit(1);	
			}
			break;
		}
		case 4:{//往右 
			if(m->mb[id].mblength<len && m->mb[id].up==0){
				csentrance(1);
				m->mb[id].mbxy[0]+=2;
				m->mb[id].mblength++; 
				if(dead(m->mb[id].mbxy[0],m->mb[id].mbxy[1],p)){
					csexit(1);
					return true; 
				}
				block(m->mb[id].mbxy[0],m->mb[id].mbxy[1],2,m);
				csexit(1);	
			}
			else if(m->mb[id].mblength==len && count==0){
				m->mb[id].up=1;
				csentrance(1);
				clearblock(m->mb[id].mbxy[0],m->mb[id].mbxy[1],m);
				clearblock(m->mb[id].mbxy[0]+1,m->mb[id].mbxy[1],m);
				csexit(1);
				m->mb[id].mbxy[0]-=2;;
				m->mb[id].mblength--;
			}
			else if(m->mb[id].mblength>0 && m->mb[id].up==1 && count==0){
				csentrance(1);
				clearblock(m->mb[id].mbxy[0],m->mb[id].mbxy[1],m);
				clearblock(m->mb[id].mbxy[0]+1,m->mb[id].mbxy[1],m);
				csexit(1);
				m->mb[id].mbxy[0]-=2;;
				m->mb[id].mblength--;
			}
			else if(m->mb[id].mblength==0){
				m->mb[id].up=0;
				csentrance(1);
				m->mb[id].mbxy[0]+=2;;
				m->mb[id].mblength++;
				if(dead(m->mb[id].mbxy[0],m->mb[id].mbxy[1],p)){
					csexit(1);
					return true; 
				}
				block(m->mb[id].mbxy[0],m->mb[id].mbxy[1],2,m);
				csexit(1);	
			}
			break;
		}
	}
	return false;
}
void clearst(saveslot *st){
	doublejump dj;
	st->checkpoint=0;
	st->dj=dj;
	st->map=0;
	st->used=false;
}
/*輸入名字*/
void name(saveslot *st){
	map m;
	frame(&m);
	gotoxy(startx,starty);
	printf("Please enter your name(8 word at most)");
	gotoxy(startx,starty+1);
	printf("...>");
	fgets(st->name,9,stdin);
	if(strlen(st->name)==1){
		strcpy(st->name,"Untitle");
	}
	else if(st->name[strlen(st->name)-1]=='\n'){
		st->name[strlen(st->name)-1]='\0';
	}
	
	
} 
/*儲存遊戲*/
void save(saveslots *sts,const saveslot *st){
	int slot=select(6)-1;
	if(slot==5)return ;
	FILE *fp=fopen("save.txt","w");
	sts->sl[slot]=*st;
	for(int i=0;i<5;i++){
		fprintf(fp,"%s %d %d %d %d %d\n"
				,sts->sl[i].name,sts->sl[i].dj.eggavailable,sts->sl[i].map,sts->sl[i].checkpoint,sts->sl[i].score,sts->sl[i].used);	
	}
	fclose(fp);
	gotoxy(startx+2,starty+6);
	printf("儲存完成\n");
	gotoxy(startx+2,starty+7);
	system("pause");	
}

/*讀取遊戲*/
void Read(saveslots *sts){
	FILE *fp=fopen("save.txt","r");
	if(fp==0){
		return;
	}
	for(int i=0;i<5;i++){
		fscanf(fp,"%s %d %d %d %d %d"
				,sts->sl[i].name,&sts->sl[i].dj.eggavailable,&sts->sl[i].map,&sts->sl[i].checkpoint,&sts->sl[i].score,&sts->sl[i].used);
	}
}


/*遊戲存取介面*/

void lsframe(saveslots *sts){
	map m;
	int slot;
	frame(&m);
	gotoxy(startx,starty-1);
	printf("★======遊戲存取====== ★");
	for(int i=0;i<5;i++){
		gotoxy(startx+2,starty+i);
		printf("%d : ",i+1);
		if(sts->sl[i].used==1){
			printf("%8s Map%d Checkpoint:%d",sts->sl[i].name,sts->sl[i].map,sts->sl[i].checkpoint);
		}
		else{
			printf("未使用");
		}
	}
	gotoxy(startx+2,starty+5);
	printf("離開存取介面");
}

/*三張地圖*/ 

bool mapframe1(doublejump *dj, saveslots *sts,saveslot *st){
	map map1;
	pos p1;
	bool egg=false;	
	bool win=false;
	bool check=false;
	bool gameover=false;
	bool menu=false;
	bool stop=false;
	bool Save=false;
	int checkpoint=st->checkpoint;//記錄點號碼 
	int resetx,resety;//角色起始位址
	int checkx,checky;//記錄點位址
	switch(checkpoint){
		case 0:{
			resetx=3;resety=23;//角色起始位址
			checkx=3;checky=14;
			break;
		}
		case 1:{
			resetx=3;
			resety=14;
			checkx=36;
			checky=5;
			break;
		}
		case 2:{
			resetx=36;
			resety=5;
			checkx=38;
			checky=23;
			break;
		}
		case 3:{
			resetx=38;
			resety=23;
			checkx=66;
			checky=3;
			break;
		}
	}
	while(1){
		begin:;
		
		/*彩蛋*/
		for(int i=51;i<72;i++){
			block(i,0,4,&map1);
		}
		block(51,1,4,&map1);
		for(int i=0;i<=48;i++){
			block(72,i,4,&map1);
		}
		for(int i=25;i<47;i++){
			block(69,i,4,&map1);
		}
		block(68,46,4,&map1);
		block(67,47,4,&map1);
		block(68,48,4,&map1);
		block(69,48,4,&map1);
		block(70,48,4,&map1);
		block(71,48,4,&map1);
		block(68,47,5,&map1);
		
 		/*設置地圖框架*/ 
		frame(&map1);
		clearblock(52,2,&map1);
		clearblock(53,2,&map1);
		block(52,2,6,&map1);
		block(16,21,1,&map1);
		block(23,21,1,&map1);
		bigblock(30,18,3,1,&map1);
		bigblock(32,19,2,5,&map1);
		bigblock(36,6,1,18,&map1);
		bigblock(3,15,6,1,&map1);
		bigblock(12,6,12,4,&map1);
		bigblock(50,3,1,18,&map1);
		bigblock(42,10,4,1,&map1);
		bigblock(40,12,4,1,&map1);
		block(48,16,1,&map1);
		block(52,20,1,&map1);
		block(58,17,1,&map1);
		bigblock(60,9,2,1,&map1);
		block(66,4,1,&map1);
		
		again:;
		clear(&p1);
		resetxy(resetx,resety,&p1);
		player(&p1);
		block(checkx,checky,3,&map1);
		int count=1;
		#pragma omp parallel sections
		{	
			#pragma omp section
			{	
				while(!gameover && !check && !menu && !egg && !stop && !Save){
					if(moveblock(20,23,4 ,1,0,count,&map1,&p1) ||moveblock(27,22,5,1,1,count,&map1,&p1)|| 
					   moveblock(27,15,6,3,2,count,&map1,&p1)||moveblock(3,10,4,4,3,count,&map1,&p1)||
					   moveblock(10,6,3,3,4,count,&map1,&p1)||moveblock(36,9,6,4,6,count,&map1,&p1)||
					   moveblock(36,11,6,4,7,count,&map1,&p1)||moveblock(50,15,1,3,8,count,&map1,&p1)||
					   moveblock(52,12,4,4,9,count,&map1,&p1)|| moveblock(52,4,6,4,10,count,&map1,&p1)
					   ){
						gameover=true;
					}
					Sleep(50);
					count=(count+1)%10;
				}		
			}
			#pragma omp section
			{	
				while(!gameover && !check && !menu && !egg && !Save){
					int Walk=walk(&gameover,&p1,dj,&map1);
					int Fall=falling(&gameover,&p1,dj,&map1);
					if(Walk){
						switch(Walk){
							case 1:{
								menu=true;	
								break;
							}
							case 2:{
								Save=true;
								break;
							}
						}
					}
					if(Fall){
						switch(Fall){
							case 1:{
								menu=true;	
								break;
							}
							case 2:{
								Save=true;
								break;
							}
						}
					}	
					if(stateclear(checkx,checky,&p1))check=true;
					if(stateclear(68,47,&p1))egg=true;
					if(stateclear(70,1,&p1))stop=true;
					
				}	
			}	
			
		}
		for(int i=0;i<20;i++){
			map1.mb[i].used=false;
			map1.mb[i].mblength=0;
			map1.mb[i].up=0;
			map1.mb[i].mbxy[2]={};
			
		}
		if(gameover){
			system("cls");
			frame(&map1);
			gotoxy(28,12);
			printf("GameOver");
			gotoxy(28,13);
			system("pause");
			system("cls");
			gameover=false;
			goto begin;
		}
		else if(check){
			checkpoint++;
			check=false;
		}
		else if(egg){
			checkpoint=5;
			egg=false;
		}
		else if(menu){
			system("cls");
			clearst(st);
			return true;
		}
		else if(Save){
			system("cls");
			st->dj=*dj;
			st->map=1;
			st->used=true;
			st->checkpoint=checkpoint;
			lsframe(sts);
			save(sts,st);
			system("cls");
			Save=false;
			goto begin;
		}
		switch(checkpoint){
			case 1:{
				resetx=3,
				resety=14;
				checkx=36;
				checky=5;
				goto again;
			}
			case 2:{
				resetx=36,
				resety=5;
				checkx=38;
				checky=23;
				goto again;
			}
			case 3:{
				resetx=38,
				resety=23;
				checkx=66;
				checky=3;
				goto again;
			}
			case 4:{
				win=true;
				break;
			}
			case 5:{
				easteregg(dj);
				system("cls");
				frame(&map1);
				gotoxy(24,11);
				printf("double jump available");
				gotoxy(24,13);
				printf("press 'Q' to equip or cancel");
				gotoxy(24,15);
				system("pause");
				system("cls");
				win=true;
			}		
		}
		if(win){
			clearst(st);
			system("cls");
			frame(&map1);
			gotoxy(24,12);
			printf("levelClear");
			gotoxy(24,14);
			system("pause");
			system("cls");
			break;
		}
	}
	return false;	
}

bool mapframe2(doublejump *dj, saveslots *sts,saveslot *st){
	map map2;
	pos p2;
	bool win=false;
	bool check=false;
	bool gameover=false;
	bool menu=false;
	bool Save=false;
	int checkpoint=st->checkpoint;//記錄點號碼 
	int resetx,resety;//角色起始位址
	int checkx,checky;//記錄點位址
	switch(checkpoint){
		case 0:{
			resetx=3;resety=23;//角色起始位址 
			checkx=52;checky=23;
			break;
		}
		case 1:{
			resetx=52,
			resety=23;
			checkx=67;
			checky=3;
			break;
		}
	}
	while(1){
		begin:;
		/*設置地圖框架*/
		frame(&map2);
		block(7,19,1,&map2);
		block(12,15,1,&map2);
		block(7,11,1,&map2);
		bigblock(15,17,1,6,&map2);
		bigblock(50,17,1,7,&map2);
		bigblock(31,9,3,1,&map2);
		bigblock(33,13,2,1,&map2);
		bigblock(35,3,1,5,&map2);
		bigblock(55,4,2,15,&map2);
		block(61,19,1,&map2);
		bigblock(67,4,1,20,&map2);
		bigblock(61,10,2,1,&map2);
		bigblock(61,4,3,1,&map2);
		
		again:;
		clear(&p2);
		resetxy(resetx,resety,&p2);
		player(&p2);
		block(checkx,checky,3,&map2);
		int count=1;
		#pragma omp parallel sections
		{		
			#pragma omp section
			{	
				while(!gameover && !check && !menu && !Save){
					if(moveblock(24,11,5,3,0,count,&map2,&p2)||moveblock(28,7,5,3,1,count,&map2,&p2)||
					   moveblock(28,3,3,2,2,count,&map2,&p2)||moveblock(39,17,3,1,3,count,&map2,&p2)||
					   moveblock(45,17,3,1,4,count,&map2,&p2)||moveblock(59,17,3,1,5,count,&map2,&p2)||
					   moveblock(55,3,3,4,6,count,&map2,&p2)||moveblock(59,6,3,4,7,count,&map2,&p2)
					   ){
						gameover=true;
					}
					Sleep(50);
					count=(count+1)%10;
				}		
			}
			#pragma omp section
			{	
				while(!gameover && !check && !menu && !Save){
					int Walk=walk(&gameover,&p2,dj,&map2);
					int Fall=falling(&gameover,&p2,dj,&map2);
					if(Walk){
						switch(Walk){
							case 1:{
								menu=true;	
								break;
							}
							case 2:{
								Save=true;
								break;
							}
						}
					}
					if(Fall){
						switch(Fall){
							case 1:{
								menu=true;	
								break;
							}
							case 2:{
								Save=true;
								break;
							}
						}
					}		
					if(stateclear(checkx,checky,&p2))check=true;
				}	
			}
		}
		for(int i=0;i<20;i++){
			map2.mb[i].used=false;
			map2.mb[i].mblength=0;
			map2.mb[i].up=0;
			map2.mb[i].mbxy[2]={};
			
		}
		if(gameover){
			system("cls");
			frame(&map2);
			gotoxy(28,12);
			printf("GameOver");
			gotoxy(28,13);
			system("pause");
			system("cls");
			gameover=false;
			goto begin;
		}
		else if(check){
			checkpoint++;
			check=false;
		}
		else if(menu){
			clearst(st);
			system("cls");
			return true;
		}
		else if(Save){
			system("cls");
			st->dj=*dj;
			st->map=2;
			st->used=true;
			st->checkpoint=checkpoint;
			lsframe(sts);
			save(sts,st);
			system("cls");
			Save=false;
			goto begin;
		}
		switch(checkpoint){
			case 1:{
				resetx=52,
				resety=23;
				checkx=67;
				checky=3;
				goto again;
			}
			case 2:{
				win=true;
				break;
			}	
		}
		if(win){
			clearst(st);
			system("cls");
			frame(&map2);
			gotoxy(24,12);
			printf("levelClear");
			gotoxy(24,14);
			system("pause");
			system("cls");
			break;
		}
	}
	return false;	
}

bool mapframe3(doublejump *dj, saveslots *sts,saveslot *st){
	map map3;
	pos p3;
	bool win=false;
	bool check=false;
	bool gameover=false;
	bool menu=false;
	bool Save=false;
	int checkpoint=st->checkpoint;//記錄點號碼 
	int resetx,resety;//角色起始位址
	int checkx,checky;//記錄點位址
	switch(checkpoint){
		case 0:{
			resetx=3;resety=21;//角色起始位址 
		 	checkx=29;checky=16;
			break;
		}
		case 1:{
			resetx=29,
			resety=16;
			checkx=3;
			checky=16;
			break;
		}
		case 2:{
			resetx=3,
			resety=16;
			checkx=59;
			checky=6;
			break;
		}
		case 3:{
			resetx=59,
			resety=6;
			checkx=67;
			checky=23;
			break;
		}
	}
	while(1){
		begin:;
		/*設置地圖框架*/
		frame(&map3);
		bigblock(3,22,15,2,&map3);
		bigblock(3,17,15,2,&map3);
		bigblock(43,7,2,17,&map3);
		bigblock(27,12,1,5,&map3);
		bigblock(23,11,1,5,&map3);
		bigblock(25,11,1,6,&map3);
		bigblock(37,22,3,2,&map3);
		bigblock(13,7,15,2,&map3);
		bigblock(19,7,1,9,&map3);
		bigblock(15,7,1,9,&map3);
		bigblock(11,7,1,9,&map3);
		block(7,12,1,&map3);
		bigblock(65,3,2,20,&map3);
		bigblock(47,7,7,2,&map3);
		bigblock(51,15,7,2,&map3);
		bigblock(47,22,7,2,&map3);
		bigblock(59,8,1,5,&map3);
		bigblock(55,8,1,5,&map3);
		bigblock(51,8,1,4,&map3);
		block(47,11,1,&map3);
		 
		again:;
		clear(&p3);
		resetxy(resetx,resety,&p3);
		player(&p3);
		block(checkx,checky,3,&map3);
		int count=1;
		#pragma omp parallel sections
		{		
			#pragma omp section
			{	
				while(!gameover && !check && !menu && !Save){
					if(moveblock(7,18,3,2,0,count,&map3,&p3)||moveblock(9,23,4,1,1,count,&map3,&p3)||
					   moveblock(11,18,3,2,2,count,&map3,&p3)||moveblock(15,18,3,2,3,count,&map3,&p3)||
					   moveblock(17,23,4,1,4,count,&map3,&p3)||moveblock(19,18,3,2,5,count,&map3,&p3)||
					   moveblock(32,23,3,1,6,count,&map3,&p3)||moveblock(35,23,3,1,7,count,&map3,&p3)||
					   moveblock(43,17,5,3,8,count,&map3,&p3)||moveblock(21,8,8,2,9,count,&map3,&p3)||
					   moveblock(5,16,8,4,10,count,&map3,&p3)||moveblock(13,7,5,3,11,count,&map3,&p3)||
					   moveblock(45,15,2,4,12,count,&map3,&p3)||moveblock(53,16,3,3,13,count,&map3,&p3)||
					   moveblock(65,14,4,3,14,count,&map3,&p3)||moveblock(45,14,5,4,15,count,&map3,&p3)||
					   moveblock(53,16,5,2,16,count,&map3,&p3)||moveblock(57,16,5,2,17,count,&map3,&p3)||
					   moveblock(55,23,6,1,18,count,&map3,&p3)||moveblock(65,21,3,3,19,count,&map3,&p3)
					   ){
						
						gameover=true;
					}
					Sleep(50);
					count=(count+1)%10;
				}		
			}
			#pragma omp section
			{	
				while(!gameover && !check && !menu && !Save){
					int Walk=walk(&gameover,&p3,dj,&map3);
					int Fall=falling(&gameover,&p3,dj,&map3);
					if(Walk){
						switch(Walk){
							case 1:{
								menu=true;	
								break;
							}
							case 2:{
								Save=true;
								break;
							}
						}
					}
					if(Fall){
						switch(Fall){
							case 1:{
								menu=true;	
								break;
							}
							case 2:{
								Save=true;
								break;
							}
						}
					}	
					if(stateclear(checkx,checky,&p3))check=true;
				}	
			}
		}
		for(int i=0;i<20;i++){
			map3.mb[i].used=false;
			map3.mb[i].mblength=0;
			map3.mb[i].up=0;
			map3.mb[i].mbxy[2]={};
			
		}
		if(gameover){
			system("cls");
			frame(&map3);
			gotoxy(28,12);
			printf("GameOver");
			gotoxy(28,13);
			system("pause");
			system("cls");
			gameover=false;
			goto begin;
		}
		else if(check){
			checkpoint++;
			check=false;
		}
		else if(menu){
			clearst(st);
			system("cls");
			return true;
		}
		else if(Save){
			system("cls");
			st->dj=*dj;
			st->map=3;
			st->used=true;
			st->checkpoint=checkpoint;
			lsframe(sts);
			save(sts,st);
			system("cls");
			Save=false;
			goto begin;
		}
		switch(checkpoint){
			case 1:{
				resetx=29,
				resety=16;
				checkx=3;
				checky=16;
				goto again;
			}
			case 2:{
				resetx=3,
				resety=16;
				checkx=59;
				checky=6;
				goto again;
			}
			case 3:{
				resetx=59,
				resety=6;
				checkx=67;
				checky=23;
				goto again;
			}
			case 4:{
				st->checkpoint=0;
				win=true;
				break;
			}	
		}
		if(win){	
			clearst(st);
			system("cls");
			frame(&map3);
			gotoxy(24,10);
			printf("!!Congratulation!!");
			gotoxy(24,12);
			printf("!!You win the game!!");
			gotoxy(12,14);
			printf("In first map ,there is an easter egg go find it!!");
			gotoxy(24,16);
			system("pause");
			system("cls");
			break;
		}
	}
	return false;	
}










