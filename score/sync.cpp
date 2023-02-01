/*處里程式的同步問題,採用bakery Algo*/
#include <stdio.h> 
#define pnum 5 
int idn[pnum],choose[pnum]={},number[pnum]={};
int max(){
	int n=0;
	for(int i=0;i<pnum;i++){
		if(number[i]>n){
			n=number[i];
		}	
	}
	return n; 
}
/*臨界區間之出入口設計*/ 
void csentrance(int id){
	idn[id]=id;
	choose[id]=1;
	number[id]=max()+1;
	choose[id]=0;
	for(int i=0;i<pnum;i++){
		while(choose[i]==1);
		while((number[i]>0) && ((number[i]<number[id])||((number[id]==number[i]) && idn[i]<idn[id])));	
	}
}
void csexit(int id){
	number[id]=0;
}

