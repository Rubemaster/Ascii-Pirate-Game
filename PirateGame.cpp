#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
using namespace std;
int main(){
	srand(time(0));
	int height=200;
	int width=200;
	int runThroughCount=0;
	char map[width][height];
	char pirateBoat[8][5]={
		'X','X','X','X','X',
		'X','X','X','X','X',
		'+','=','=','=','+',
		'X','=','=','=','X',
		'+','-','O','-','+',
		' ','X','=','X',' ',
		' ','X','X','X',' ',
		' ',' ','X',' ',' '
	};char pirateBoat2[5][8]={
		'X','X','+','X','+','X',' ',' ',
		'X','X','=','=','|','X','X',' ',
		'X','X','=','=','O','=','X','X',
		'X','X','=','=','|','X','X',' ',
		'X','X','+','X','+','X',' ',' '
	};
	int direction=0;
	system("pause");
	int plots[200][3];
	int plotCount=-1;
		int lLocX=0;
		int lLocY=0;
		int locX=0;
		int locY=0;
		
		int lShiftX=100,lShiftY=100;
		int shiftX=100,shiftY=100;
		
		int plotSide=40;
	while(true){
		for(int i=0;i<width*height;i++){
			map[i%width][i-(i%width)*width]=' ';
		}
		for(int xLocSh=0;xLocSh<2;xLocSh++){
			for(int yLocSh=0;yLocSh<2;yLocSh++){
				int foundAt=-1;
				for(int i=0;i<plotCount&&foundAt==-1;i++){
					if(plots[i][0]==locX+xLocSh&&plots[i][1]==locY+yLocSh)foundAt=i;
				}
				if(foundAt==-1){
					plotCount++;
					plots[plotCount][0]=locX+xLocSh;
					plots[plotCount][1]=locY+yLocSh;
					plots[plotCount][2]=rand();
					foundAt=plotCount;
				}
				srand(plots[foundAt][2]);
				int islandCount=rand()%5;
				int islands[islandCount][2];
				for(int i=0;i<islandCount;i++){
					islands[i][0]=rand()%plotSide;
					islands[i][1]=rand()%plotSide;
				}
				int sizeEmUp=1;
				int spreadSize=1000*sizeEmUp;
				int units=20*sizeEmUp;
				int input=0;
				shiftX-=xLocSh*200;
				shiftY-=yLocSh*200;
				for(int i2=0;i2<islandCount;i2++){
					int x=islands[i2][0],y=islands[i2][1];
					for(int i=0;i<spreadSize*units;i++){
						input=rand()%4;
						if(input==0)x++;
						if(input==1)x--;
						if(input==2)y++;
						if(input==3)y--;
						if(x>shiftX&&x<width+shiftX&&y>shiftY&&y<height+shiftY){
							if(map[x-shiftX][y-shiftY]==' '){
								map[x-shiftX][y-shiftY]=0;
							}else if(map[x-shiftX][y-shiftY]<58)map[x-shiftX][y-shiftY]++;
						}
						if(i%spreadSize==0)x=islands[i2][0],y=islands[i2][1];
					}
				}
				shiftX+=xLocSh*200;
				shiftY+=yLocSh*200;
			}
		}
		for(int x=0;x<width;x++){
			for(int y=0;y<height;y++){
				if(map[x][y]!=' '){
					if(map[x][y]<2){
						map[x][y]=176;
					}else if(map[x][y]<5){
						map[x][y]=177;
					}else if(map[x][y]<19){
						map[x][y]=178;
					}else{
						map[x][y]=219;
					}
				}
			}
		}
		
		if(map[60][60]!=' ')shiftX=lShiftX,shiftY=lShiftY,locX=lLocX,locY=lLocY;
		if(direction==0){
			for(int x2=60;x2<68;x2++){
				for(int y2=60;y2<65;y2++){
					char boatPart=pirateBoat2[y2-60][7-(x2-60)];
					if(boatPart!=' ')map[x2][y2-4]=boatPart;
				}
			}
		}
		if(direction==1){
			for(int x2=60;x2<68;x2++){
				for(int y2=60;y2<65;y2++){
					char boatPart=pirateBoat2[y2-60][x2-60];
					if(boatPart!=' ')map[x2][y2-4]=boatPart;
				}
			}
		}
		if(direction==2){
			for(int x2=60;x2<65;x2++){
				for(int y2=60;y2<68;y2++){
					char boatPart=pirateBoat[y2-60][x2-60];
					if(boatPart!=' ')map[x2][y2-4]=boatPart;
				}
			}
		}
		if(direction==3){
			for(int x2=60;x2<65;x2++){
				for(int y2=60;y2<68;y2++){
					char boatPart=pirateBoat[7-(y2-60)][x2-60];
					if(boatPart!=' ')map[x2][y2-4]=boatPart;
				}
			}
		}
		map[60][60]=1;
		system("cls");
			string out2="";
			for(int y=0;y<height&&y<110;y++){	
				out2+="\n";
				for(int x=0;x<width;x++){
					out2+=map[x][y];
				}
			}
		cout<<"Arrr, a tale of the sea arr"<<endl<<out2;
		lShiftX=shiftX;
		lShiftY=shiftY;
		lLocX=locX;
		lLocY=locY;
		while(lShiftX==shiftX&&lShiftY==shiftY){
			if(GetAsyncKeyState(VK_LEFT)){direction=0;shiftX--;}
			if(GetAsyncKeyState(VK_RIGHT)){direction=1;shiftX++;}
			if(GetAsyncKeyState(VK_DOWN)){direction=2;shiftY++;}
			if(GetAsyncKeyState(VK_UP)){direction=3;shiftY--;}
		}
		if(shiftX==200)shiftX=0,locX++;
		if(shiftX==-1)shiftX=199,locX--;
		if(shiftY==200)shiftY=0,locY++;
		if(shiftY==-1)shiftY=199,locY--;
		cout<<endl<<"Shift X:"<<shiftX;
		cout<<endl<<"Shift Y:"<<shiftY;
		cout<<endl<<"Loc X:"<<locX;
		cout<<endl<<"Loc Y:"<<locY;
		
	}
}
