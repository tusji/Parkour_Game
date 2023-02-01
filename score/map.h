#ifndef MAP
#define MAP


struct movebox{
	int mblength=0;
	int up=0;
	int mbxy[2]={};
	bool used=false;
};
struct map{
	int map[100][100]={{},{}}; 
	movebox mb[20]={};
};

struct pos{
	int xpose=0;
	int ypose=0; 
};
struct doublejump{
	bool doublej=false;//改true獲得二段跳 
	bool avail=false;//改true獲得二段跳
	bool eggavailable=false;
};
struct saveslot{
	char name[30]={};
	int map=0;
	int checkpoint=0;
	doublejump dj;
	int score=0;
	bool used=false;
};
struct saveslots{
	saveslot sl[5]={};
	int size=0;
};

bool Map(int,int,const map *);
void resetxy(int,int,pos *);
bool dead(int ,int ,const pos *);
void gotoxy(int , int );
void player(const pos *);
void clear(const pos *);
void easteregg(doublejump *);
void equip(doublejump *);
void cancel(doublejump *);
int falling(bool *,pos *,doublejump *,const map *);
int walk(bool * ,pos * ,doublejump *,const map *);
bool stateclear(int,int,const pos *);
void block(int,int,int,map *);
void bigblock(int,int,int,int,map *);
void clearblock(int,int,map *);
void frame(map *);
void clearst(saveslot *st);
void name(saveslot *);
void save(saveslots *sts,const saveslot *st);
void Read(saveslots *sts);
bool load(const saveslots *sts);
void lsframe(saveslots *sts);
bool moveblock(int ,int,int ,int,int,map *,const pos *p);
bool mapframe1(doublejump *,saveslots *,saveslot *);
bool mapframe2(doublejump *,saveslots *,saveslot *);
bool mapframe3(doublejump *,saveslots *,saveslot *);
#endif




