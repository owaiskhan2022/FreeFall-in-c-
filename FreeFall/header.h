#include<iostream>
using namespace::std;

class freefall
{
	private:
			int x,y,score,level,birdx,birdy,cloud1x,cloud1y,cloud2x,
				cloud2y,coin1x,coin2x,balloonx,coin1y,coin2y,balloony,planex,planey,kitex,kitey;  
	public:
		void initialize();//Constructor For Values Initialization causes problems when we play the game again after getting out		
		void mainmenu();
		void credits();
		void man(int,int);
		void bird(int,int); 
		void cloud(int,int);
		void game();
		void coin(int,int);
		void kite(int,int);
		void plane(int,int);
		void text(int,int);
		void balloon(int,int);
		bool collision(int,int,int,int,int,int*,int,int,int*,int,int*);
		void checker(int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*);
		void gameover(int);	
};
