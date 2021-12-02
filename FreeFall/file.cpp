#include<iostream>
#include<Windows.h>
#include"mmsystem.h"
#include<graphics.h>
#include"header.h"
using namespace::std;
void freefall::game()
{
	char key;
	bool hit=0;
{
	//PlaySound("alto.wav",NULL,SND_ASYNC);
	initialize();
	setbkcolor(3);
	do		// this loop is executed once and when a key is hit the control comes to this loop and performs defined actions
	{
		do 		//as long as a key isnt hit the inner loop will continue executing
		{	
			plane(planex,planey);			//spanwns these shapes at their respective positions according to the variables 
			cloud(cloud1x,cloud1y);
			cloud(cloud2x,cloud2y);
			coin(coin1x,coin1y);
			coin(coin2x,coin2y);
			bird(birdx,birdy);
						 
			if(x<0)  //limits the man and stops him from getting out of screen
				x=0;
			if(x>1060)
			x=1060;
			
			man(x,y);
			text(level,score);
			kite(kitex,kitey);			
			balloon(balloonx,balloony);
/***Collision function detects which object is hitting the character if it is coin it increases the score and if something else we get "hit" flag***/										
			hit=collision(x,y,birdx,birdy,coin1x,&coin1y,kitex,kitey, &score,coin2x,&coin2y); //coins Y axis and score's addresses are passed as argument so that we could make change in them from inside the function 
			if(hit==1)
				{
				 PlaySound("game_over.wav",NULL,SND_ASYNC);
				 break;
			    }
 /***Checker checks the y axis of different things and once they get out of screen it makes them reappear at bottom of the screen***/
				checker(&birdx,&birdy,&cloud1x,&cloud1y,&cloud2x,&cloud2y,&balloonx,&balloony,&coin1x,&coin1y,&coin2x,&coin2y,&kitex,&kitey);
			
			if ((50-(level*2))>10)	delay(50-(level*2));
			else delay(10);					  
		cleardevice();
		}while(!kbhit()); 	
				if(hit==1)			//TO check if the character was hit by some obstacle
				{	
					setbkcolor(0);
					gameover(score);
					break;
				}
		key=getch();							
		if(key=='d')			// left
			x+=20;
	    else if(key=='a')	//right
			x-=20;
		
	}while(key!='E' && key !='e');  //if E or e is hit the loop terminates
}
setbkcolor(0);	// To change the colour back to default black to solve some issues in mainmenu 
}
void  freefall::mainmenu()
{
	char choice; 
	int gm,gd= DETECT;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	 
	cleardevice();
	setbkcolor(0);
	setcolor(14);
	rectangle(500,151,780,265);
	rectangle(500,265,780,380);
	rectangle(500,380,780,503);
		
	setfillstyle(8,2);
	floodfill(10,50,14);
	
	//PlaySound("mainmenu.wav",NULL,SND_ASYNC);
	setbkcolor(0);
	setcolor(5);
	settextstyle(1,0,6);
	outtextxy(340,50,"ToXiC Softwares");
	settextstyle(8,0,4);
	setcolor(14);
	outtextxy(550,200,"[P]LAY");
	outtextxy(550,300,"[C]REDITS");
	outtextxy(550,420,"[E]XIT");
	
	outtextxy(200,600,"HINT: Collect Coins , Avoid Objects & A D To Move");
	while(1)   //always true so that mainmenu could be used again & agin in one execution
	{
		   choice=getch();
		if(choice == 'C' || choice == 'c')
			{
		  		setfillstyle(1,14); floodfill(501,266,14);delay(900);	//custom effects	
				credits();				/*displays credits*/
			} 
		if(choice=='P' || choice=='p')								
			{
				setfillstyle(1,14); floodfill(501,151,14); delay(900); //custom effects
				game();
			}			
		if(choice=='E' || choice=='e')
			{
				setfillstyle(1,14); floodfill(501,381,14); delay(900); break; //custom effects
			}
		if(choice == 'C' || choice == 'c' || choice =='P' || choice =='p')// program wont do anything if any other key is pressed except P,C,E
			{
				mainmenu();								//mainmenu is called again after showing credits or after game ends
				break;       // to break the while loop
			}
	}
}
void freefall::credits()
{
	int x=350,y=1000;
	cleardevice();	
	while(y>-900)
		{		
			setcolor(14);
			outtextxy(x+280,y-450,"FREE FALL®");           setcolor(1);
			outtextxy(x-340,y-250,"WARNING! The Contents Of This Game Are Purely Fictional Any Resemblence");
			outtextxy(x-320,y-200,"To Any Real Life Person Is Purely Coincidence And The Contents Do Not");	
			outtextxy(x-320,y-150,"            Intend To Harm Any One's Personal Character");
			setcolor(15);
			outtextxy(x+300,y-100,"CREDITS");
			outtextxy(x,y-50, "Man Falling Down :P        Zubair Arshad");
			outtextxy(x,y    ,"Game Designer              Hamdoon Shafieen");	
			outtextxy(x,y+80 ,"Game Director              Zubair Arshad");
			outtextxy(x,y+160,"Programming                Hamdoon Shafieen");
			outtextxy(x,y+240,"Animation                  Zubair Arshad");
			outtextxy(x,y+320,"Sound Effects              Hamdoon Shafieen");
			outtextxy(x,y+400,"Artist & Development       Hamdoon Shafieen");
			outtextxy(x,y+480,"Project Management		  Zubair Arshad");
			outtextxy(x,y+580,"		©2017 Built By ToXiC Softwares");
			outtextxy(x,y+710,"For More Information Visit Our Website");
			setcolor(5);
			outtextxy(x,y+750,"      www.thereisnowebsite.com");
			y--;		
			setfillstyle(7,3);
			floodfill(10,50,14);	
		}
}
void freefall::man(int x,int y)
{						/***Parachute***/
		setlinestyle(0,0,1);
		setcolor(0);			//once done it should  be 15 white
		line(x+10,y-7,x+70,y-7);//baseline for parachute
		arc(x+40,y,15,165,30);	//Upper
					/***ColourFillings***/
		setfillstyle(1,15);
		floodfill(x+40,y-8,0);
					/***Structure Of Parachute***/
		arc(x+30,y+10,25,80,40);	//R
		arc(x+50,y+10,100,155,40);	//L
		arc(x+13,y,10,50,40);		//R
		arc(x+67,y,132,170,40);		//L			
		line(x+10,y-6,x+19,y+40);
		line(x+68,y-6,x+59,y+40);
		line(x+27,y-6,x+19,y+40);
		line(x+52,y-6,x+59,y+40);
							/***Man***/	
		setcolor(0);
	  	circle(x+40,y+40,10);		              		//Head
      	circle(x+37,y+36,2);circle(x+42,y+36,2);  		//Eyes
		arc (x+40,y+40,160 ,10,5);  			  		//Mouth
		line(x+32,y+50,x+48,y+50);			      		//Hands
		line(x+48,y+50,x+56,y+40);circle(x+56,y+40,4);	//R
		line(x+32,y+50,x+24,y+40);circle(x+24,y+40,4);	//L
		line(x+40,y+50,x+40,y+60); 		    	  		//Neck
		line(x+40,y+60,x+30,y+70); 			 		    //Feet
		line(x+40,y+60,x+50,y+70);			 	  		//Feet	   
}
void freefall::bird(int x,int y)
{	
	setlinestyle(0,0,3);
	setcolor(0);
	arc(x+40,y+40,10,170,10);     					// left wing
	arc(x+59,y+40,10,170,10);	  					// right wing
}
void freefall::kite(int x,int y)
{	
	setlinestyle(0,0,0);
	setcolor(14);
	line(x,y,x+30,y);			//horizontal
	line(x+15,y-15,x+15,y+30);	//vertical
	setcolor(14);
	line(x,y,x+15,y-15);		//top-right
	line(x+30,y,x+15,y-15);		//top-left
	line(x,y,x+15,y+30);		//bot-right
	line(x+15,y+30,x+30,y);		//bot-left
	setcolor(14);
	line(x+15,y+30,x+17,y+50);	//tail
	setcolor(4);
	line(x+15,y+30,x+13,y+50);	//tail
	setcolor(6);
	line(x+15,y+30,x+15,y+50);	//tail
	setcolor(4);setlinestyle(3,0,0);
							/***Thread***/
	arc(x+415,y-10,186,230,400);line(x+157,y+296,x+500,y+570);	
							/***ColourFillings***/
	setfillstyle(1,4);
	floodfill(x+14,y+14,14);
	floodfill(x+16,y-2,14);
	setfillstyle(1,14);
	floodfill(x+14,y-2,14);
	floodfill(x+16,y+2,14);
}
void freefall::cloud(int x,int y)
{	setcolor(15);
	setlinestyle(0,0,1);
	arc(x+50,y+41,10,170,10);	//clouds bump left
	arc(x+110,y+41,10,170,10);  //clouds bump right
	arc(x+79,y+37,10,170,30);   //clouds bump mid
	line(x+39,y+40,x+120,y+40); //clouds base line
	setfillstyle(1,15);
	floodfill(x+50,y+35,15);
	floodfill(x+79,y+35,15);
	floodfill(x+110,y+35,15);
}
void freefall::balloon(int x,int y)
{
	setcolor(4);
	setfillstyle(1,4);
	fillellipse(x,y,15,20);
	fillellipse(x,y+20,3,2);	
	arc(x+2,y+26,90,270,5);
	arc(x-1,y+35,90,290,5);
}
void freefall::coin(int x,int y)
{	
	setlinestyle(0,0,1);
	setcolor(14);
	circle(x,y,10);
	setfillstyle(1,14);
	floodfill(x,y,14);
}
void freefall::text(int level,int score)
{
	char coincounter[128],scorecounter[128];
	settextstyle(8,0,4);
	setcolor(15);									
	sprintf(scorecounter, " %d", score);			//Character array i.e string takes value stored in integer variable
	outtextxy(1250,70, scorecounter);
	sprintf(coincounter, " %d", level);
	outtextxy(1250,150,coincounter);
	setcolor(0);
	outtextxy(1150,70,"SCORE");							//prints on desired locations
	outtextxy(1150,150,"LEVEL");
	setcolor(15);
	setlinestyle(0,0,3);
	line(1140,2,1140,700);
	line(1140,2,2,2);
	line(2,2,2,700);
	line(2,700,1140,700);
}
void freefall::plane(int x,int y)
{
		setlinestyle(0,0,0);
	setcolor(7);
			line(x,y,x,y+40);	//tail
			line(x,y,x-20,y);
			line(x-20,y,x-30,y+20);	
			line(x-30,y+20,x-141,y+20);		// upper part
	
			line(x-70,y+20,x-90,y+10);		
			line(x-90,y+10,x-110,y+10);		
			line(x-110,y+10,x-130,y+20);	
			line(x-111,y+10,x-111,y+20);	
			line(x-70,y+20,x-131,y+20);			
			line(x-90,y+10,x-90,y+20);		
	
			arc(x-140,y+30,90,270,10);		
			line(x-141,y+40,x-88,y+42);		//lower left part
			line(x-100,y+30,x-60,y+70);		//bottom wing
			line(x-60,y+70,x-40,y+70);		
			line(x-40,y+70,x-70,y+30);
			line(x-61,y+42,x,y+40);			//lower right part
			line(x-65,y+20,x-40,y);			//top wing right part
			line(x-40,y,x-65,y);		//top wing upper part
			line(x-65,y,x-85,y+13);		//top wing left part
						/*************Colour Fillings*************/
	setfillstyle(1,7);
	floodfill(x-61,y+40,7);
	floodfill(x-80,y+13,7);
}
bool freefall::collision(int x,int y,int birdx,int birdy,int coin1x,int *coin1y,int kitex,int kitey,int *ptr,int coin2x,int *coin2y)
{	
	bool hit=0;
										/***Bird***/
	if((x+30 >= birdx+30 && x+30 <= birdx+70) || (x+50 >= birdx+30 && x+50 <= birdx+70))
			{
				if(y+70>=birdy+28 && y+70<= birdy+40)
				 hit=1;				
			}
	if((x+10 >= birdx+30 && x+10 <= birdx+70) || (x+70 >= birdx+30 && x+70 <= birdx+70))
			{
				if(y-7 >= birdy+28 && y-7 <= birdy+40)
				 hit=1;
			}
										/***coin1***/
	if((x+30 >= coin1x-15 && x+30 <= coin1x+15) || (x+50 >= coin1x-15 && x+50 <= coin1x+15))//Collision detection on x axis
			{
				if(y+70 >= *coin1y-15 && y+70<= *coin1y+15) //collision detection on y axis
				{
					*ptr = *ptr + 150;				
					*coin1y = -100;
				}			
			}
	if((x+10 >= coin1x-15 && x+10 <= coin1x+15) || (x+70 >= coin1x-15 && x+70 <= coin1x+15) ||(x+45 >= coin1x-15 && x+45 <= coin1x+15))  //collision detection on X axis
			{
				if(y-7 >= *coin1y-15 && y-7 <= *coin1y+15) //collision detection on y axis
				 {
				 	*ptr = *ptr + 150;
					 *coin1y = -100;
				 }
			}
	if(x+45 >= coin1x-15 && x+45 <= coin1x+15)//The coin is too small and it used to get by the character without activating the collision points so we had to put an extra collision point to get the coin
	{
			if(y+40 >= *coin1y-15 && y+40 <= *coin1y+15) //collision detection on y axis
				 {
				 	*ptr = *ptr + 150;
					 *coin1y = -100;
				 }
	}	
								/***coin2***/
	if((x+30 >= coin2x-15 && x+30 <= coin2x+15) || (x+50 >= coin2x-15 && x+50 <= coin2x+15)) //collision detection on X axis
			{
				if(y+70 >= *coin2y-15 && y+70<= *coin2y+15) //collision detection on y axis
				{
					*ptr = *ptr + 150;				
					*coin2y = -100;
				}			
			}
	if((x+10 >= coin2x-15 && x+10 <= coin2x+15) || (x+70 >= coin2x-15 && x+70 <= coin2x+15)||(x+45 >= coin2x-15 && x+45 <= coin2x+15)) //collision detection on X axis
			{
				if(y-7 >= *coin2y-15 && y-7 <= *coin2y+15) //collision detection on y axis
				 {
				 	*ptr = *ptr + 150;
					 *coin2y = -100;
				 }
			}
	if(x+45 >= coin2x-15 && x+45 <= coin2x+15)
	{
			if(y+40 >= *coin2y-15 && y+40 <= *coin2y+15) //collision detection on y axis
				 {
				 	*ptr = *ptr + 150;
				 	*coin2y = -100;
				 }
	}		
								/***kite***/
	if((x+30 >= kitex && x+30 <= kitex+30) || (x+50 >= kitex && x+50 <= kitex+30))
			{
				if(y+70>=kitey-15 && y+70<= kitey+30)
				 hit=1;
			}
	if((x+10 >= kitex && x+10 <= kitex+30) || (x+70 >= kitex && x+70 <= kitex+30))
			{
				if(y-7 >= kitey-15 && y-7 <= kitey+30)
				 hit=1;
			}		
							  /***Balloon***/
	if((x+30 >= balloonx-15 && x+30 <= balloonx+15) || (x+50 >= balloonx-15 && x+50 <= balloonx+15))
			{
				if(y+70>=balloony-20 && y+70<= balloony+20)
				 hit=1;				
			}
	if((x+10 >= balloonx-15 && x+10 <= balloonx+15) || (x+70 >= balloonx-15 && x+70 <= balloonx+15))
			{ 
				if(y-7 >= balloony-20 && y-7 <= balloony+20)
				 hit=1;
			}								
	level=score/1500; //after every 1500 score the level increases and after every level increase the speed of game increases	  
	if(level%2==0)
	{
		setbkcolor(3);		
	}
	else if(level%3==0)
	{
		setbkcolor(1);	
	}
	else
	{
		setbkcolor(2);		
	}
  return hit;	
}
void freefall::gameover(int score)
{
		char totalscore[128];
		cleardevice();
		settextstyle(8,0,4);
		setlinestyle(0,0,8);
		setcolor(14);
		setfillstyle(8,2);
		floodfill(10,50,14);
		sprintf(totalscore, "%d", score);
		outtextxy(400,250,"Your Score");
		outtextxy(620,250,totalscore);
		outtextxy(400,330,"Press Any Key.....");
		delay(3500);
		getch();
}
void freefall::checker(int *birdx,int *birdy,int *cloud1x,int *cloud1y,int *cloud2x,int *cloud2y,int *balloonx,int *balloony,int *coin1x,int *coin1y,int *coin2x,int *coin2y,int *kitex,int *kitey)
{
	if(*birdy<=-30)		//when the bird reaches upper side												//max y should be 460
			{
				*birdy=680;
				*birdx=(rand()%900+100);				
												//this is for the speed and difficulty of the game
			}
			if((*kitey)<=-350)		//when the bird reaches upper side												//max y should be 460
			{
				*kitey=1500;
				*kitex=(rand()%900+100); //needs to be %1080
			}
			if(*cloud1y<=-100)		//when the cloud exits left side												//max y should be 460
			{
				*cloud1y=1100;
				*cloud1x=(rand()%900+100);
			}
			if(*cloud2y<=-100)		//when the cloud exits left side												//max y should be 460
			{
				*cloud2y=1100;
				*cloud2x=(rand()%900+100);
			}
			if(*balloony<=-150)
			{
				*balloony=1000;
				*balloonx=(rand()%1000);
			}
			if(*coin1y <= -100)
			{
				*coin1y=800;
				*coin1x=(rand()%900);
			}
			if(*coin2y<=-150)
			{
				*coin2y=1000;
				*coin2x=(rand()%900);
			}			
		*cloud1y-=1;*cloud2y-=2;*birdy-=6;*kitey-=10;planex--;*coin1y-=8;*coin2y-=7;*balloony-=10;
}
					/***Function Intialization  Values***/  //constructor aroused problems
void freefall::initialize()
		{
		 x=250;y=80;score=0;
		 birdx=50;birdy=400;cloud1x=350;cloud1y=230;cloud2x=620;cloud2y=100;coin1x=500;coin2x=870;balloonx;
		 coin1y=-100;coin2y=-100;balloony=-100;planex=1000;planey=200;kitex=350;kitey=1500;
		}		
// colors  0_Black, 1_Blue, 2_Green, 3_lightblue, 4_Brown, 5_Magenta, 6_Red, 7_Grey, 14_Yellow, 15_White,
