#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "menu.h"

int main(){
	int o,menu,level;
	doublejump dj;
	saveslots sts;
	saveslot st;
	Read(&sts);
	do{
		mainmenu:;
		system("cls");
		level=1;
		menuframe();
		menu=select(4);
		switch(menu){
			case 1:{
				system("cls");
				clearst(&st);
				dj=st.dj;
				name(&st);
				game:;
				system("cls");
				switch(level){
					case 1:{
						if(mapframe1(&dj,&sts,&st))goto mainmenu;
					}
					case 2:{
						if(mapframe2(&dj,&sts,&st))goto mainmenu;	
					}
					case 3:{
						if(mapframe3(&dj,&sts,&st))goto mainmenu;
						
					}
					case 4:{
						goto mainmenu;
					}
				}
				
			}
			case 2:{
				Read(&sts);
				while(1){
					system("cls");
					lsframe(&sts);
					int slot=select(6)-1;
					if(sts.sl[slot].used){
						level=sts.sl[slot].map;
						dj=sts.sl[slot].dj;
						st=sts.sl[slot];
						break;
					}
					else if(slot==5){
						goto mainmenu;
					}
				}
				goto game;
				break;
			}
			case 3:{
				system("cls");
				gamerule();
				break;
			}
		}	
	}while(menu!=4);
	system("cls");
	return 0;	
}

