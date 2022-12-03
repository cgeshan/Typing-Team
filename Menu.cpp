#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "Menu.h"
#include "tutorial.h"
#include "minigame_mars.h"
#include "minigame_rockets.h"
#include "Galaga.h"
#include "Rover.h"
#include "overworld.h"

//Menu Program
GLuint texId[14];

int GetData(void)
{
	int level;
	FILE* fp = fopen("game.txt", "r");
	if (nullptr != fp)
	{
		char str[256];
		int lineNum = 1;
		while (nullptr != fgets(str, 255, fp))
		{
			str[255] = 0;
			printf(str);
			lineNum++;
		}
		fclose(fp);
		
		if (str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4')
		{
			if (str[0] == 49)
			{
				level = 1;
			}
			else if (str[0] == 50)
			{
				level = 2;
			}
			else if (str[0] == 51)
			{
				level = 3;
			}
			else if (str[0] == 52)
			{
				level = 4;
			}
			//printf("level %d", level);
		}
	}
	
	else
	{
		level = 0;
	}
	return level;
}
void ResetGame(bool&l1,bool&l2,bool&l3,bool&l4)
{
	l1 = 0;
	l2 = 0;
	l3 = 0;
	l4 = 0;

	//Overwrites the save file with value zero 
	//Modifies l1,l2,l3,l4 to be false so the option to play those levels goes away
}
void Menu::Initialize(void)
{
	x = 100, y = 550;
	tx1 = 65, tx2 = 325;
	titly1 = 150, titly2 = 235;
	move = 1, move2 = -1, bob=-1, bobv=0.3;
	dt = 0.1;
	png[0].Decode("BG.png"); //BackGround	
	png[0].Flip();
	png[1].Decode("Mars_Rover1.png"); // Rover	
	png[1].Flip();
	png[2].Decode("Alphabet_title1.png");//Title1;
	png[2].Flip();
	png[3].Decode("Astronauts_title1.png");//Title2;
	png[3].Flip();
	png[4].Decode("b1.png"); //B1	
	png[4].Flip();
	png[5].Decode("b2.png"); //B2	
	png[5].Flip();
	png[6].Decode("b3.png"); //B3
	png[6].Flip();
	png[7].Decode("b4.png"); //B4
	png[7].Flip();
	png[8].Decode("reset.png"); //Restart	
	png[8].Flip();
	png[9].Decode("overworld.png"); //OverWorld
	png[9].Flip();
	png[10].Decode("bh1.png"); //bh1	
	png[10].Flip();
	png[11].Decode("bh2.png"); //bh2
	png[11].Flip();
	png[12].Decode("bh3.png"); //bh3
	png[12].Flip();
	png[13].Decode("bh4.png"); //bh4
	png[13].Flip();
	png[14].Decode("tutorial.png"); //Tutorial Button 
	png[14].Flip();
}
void Menu::drawBackground(void)
{

	glShadeModel(GL_SMOOTH); // gradient background 
	glBegin(GL_QUADS);

	glColor3ub(255, 235, 198);
	glVertex2i(0, 0);

	glColor3ub(255, 235, 198);
	glVertex2i(800, 0);

	glColor3ub(255, 248, 235);
	glVertex2i(800, 400);

	glColor3ub(255, 248, 235);
	glVertex2i(0, 400);

	glEnd();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(0, 600 - 1);
	glDrawPixels(png[0].wid, png[0].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[0].rgba);
	glDisable(GL_BLEND);
}
void Menu::drawRover(void)
{
	if (x > 700 || x < 50)
	{
		move = move * -1;
	}
	srand(time(NULL));
	int ran = rand() % 10;
	if (y < 500 || y > 550)
	{
		move2 = move2 * -1;
	}
	y += move2 * (0.1 * ran);
	x += move;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(x, y);
	glDrawPixels(png[1].wid, png[1].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[1].rgba);
	glDisable(GL_BLEND);
}
void Menu::drawTitle()
{
	
	if (titly1 <= 140 || titly1>=160)
	{
		bob = bob * -1;
	}
	titly1 += bobv*bob;
	titly2 += bobv*bob;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(tx1, titly1);
	glDrawPixels(png[2].wid, png[2].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[2].rgba);
	glDisable(GL_BLEND);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(tx2, titly2);
	glDrawPixels(png[3].wid, png[3].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[3].rgba);
	glDisable(GL_BLEND);
}
void Menu::drawLevel1(int posx, int posy, bool include, bool hover)
{

	if (include)
	{
		if (hover)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(posx, posy);
			glDrawPixels(png[10].wid, png[10].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[10].rgba);
			glDisable(GL_BLEND);

		}

		else
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(posx, posy);
			glDrawPixels(png[4].wid, png[4].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[4].rgba);
			glDisable(GL_BLEND);

		}

	}
}
void Menu::drawLevel2(int posx, int posy, bool include, bool hover)
{

	if (include)
	{
		if (hover)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(posx, posy);
			glDrawPixels(png[11].wid, png[11].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[11].rgba);
			glDisable(GL_BLEND);

		}

		else
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(posx, posy);
			glDrawPixels(png[5].wid, png[5].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[5].rgba);
			glDisable(GL_BLEND);

		}

	}
}
void Menu::drawLevel3(int posx, int posy, bool include, bool hover)
{

	if (include)
	{
		if (hover)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(posx, posy);
			glDrawPixels(png[12].wid, png[12].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[12].rgba);
			glDisable(GL_BLEND);

		}

		else
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(posx, posy);
			glDrawPixels(png[6].wid, png[6].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[6].rgba);
			glDisable(GL_BLEND);

		}

	}
}
void Menu::drawLevel4(int posx, int posy, bool include, bool hover)
{

	if (include)
	{
		if (hover)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(posx, posy);
			glDrawPixels(png[13].wid, png[13].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[13].rgba);
			glDisable(GL_BLEND);

		}

		else
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(posx, posy);
			glDrawPixels(png[7].wid, png[7].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[7].rgba);
			glDisable(GL_BLEND);

		}

	}
}
void Menu::drawResetButton(int posx, int posy)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(posx, posy);
	glDrawPixels(png[8].wid, png[8].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[8].rgba);
	glDisable(GL_BLEND);
}
void Menu::drawTutorialButton(int posx, int posy)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(posx, posy);
	glDrawPixels(png[14].wid, png[14].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[14].rgba);
	glDisable(GL_BLEND);
}
void Menu::drawOverworldButton(int posx, int posy)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(posx, posy);
	glDrawPixels(png[9].wid, png[9].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[9].rgba);
	glDisable(GL_BLEND);
}

void Menu::LoadingGame(int level){

	std::string loadingStr;
	
	if (level == 1)
	{
		loadingStr = "Loading into Mars mini-game";
	}
	else if (level == 2)
	{
		loadingStr = "Loading into Galaga mini-game";
	}
	else if (level == 3)
	{
		loadingStr = "Loading into Rockets mini-game";
	}
	else if (level == 4)
	{
		loadingStr = "Loading into Rover mini-game";
	}

	char loadingChar[256];
	strcpy(loadingChar, loadingStr.c_str()); 
	for(int i = 0; i < 75; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		drawBackground();
		
		glColor3f(1, 1, 1);
		glRasterPos2i(82, 112);
		YsGlDrawFontBitmap16x24(loadingChar);

		FsSwapBuffers();
		FsSleep(20);
	}
}
int main(void)
{
	FsChangeToProgramDir();
	
	Menu menu;
	menu.Initialize();
	
	FsOpenWindow(0, 0, 800, 600, 1);
	
	int level = 0;
	bool l1 = 0, l2 = 0, l3 = 0, l4 = 0;
	bool h1 = 0, h2 = 0, h3 = 0, h4 = 0;
	int px1, px2, px3, px4, px5, px6, px7;
	int py1, py2, py3, py4, py5, py6, py7;
	
	px1 = 170,px2 = 430,px3 = 195,px4 = 456, px5=695,px6=20, px7= 645;
	py1 = 320,py2 = 345,py3 = 425,py4 = 445, py5=595,py6=525, py7= 55;
	
	level = GetData();
	if (level == 1)
	{
		l1 = 1;
	}
	else if (level == 2)
	{
		l1 = 1;
		l2 = 1;
	}
	else if (level == 3)
	{
		l1 = 1;
		l2 = 1;
		l3 = 1;
	}
	else if (level == 4)
	{
		l1 = 1;
		l2 = 1;
		l3 = 1;
		l4 = 1;
	}
	for (;;)
	{
		FsPollDevice();
		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{ 
			break;
		}
		int lb, mb, rb, mx, my;
		if (FSMOUSEEVENT_MOVE == FsGetMouseEvent(lb, mb, rb, mx, my))
		{
		}
		if (mx >= px1 && mx <= px1 + 163 && my >= py1-75 && my <= py1 && l1)
		{
			h1 = 1;
			if (lb)
			{
				//Go to overworld first
				GameData overworld;
				overworld.Initialize();
				
				for(;;){
					
					overworld.Run();
					
					if(true == overworld.terminate){
						break;
					}
					// FsSleep(10);
				}
				
				//Mini Game 1
				printf("Mars Mini Game");
				Mars mars;
				mars.Initialize();
				
				for(;;){
					
					mars.RunOneStep();
					
					if(true == mars.term){
						break;
					}
					FsSleep(20);
				}
				
			}
		}
		else if (mx >= px2 && mx <= px2 + 163 && my >=py2-75 && my <= py2 && l2)
		{
			h2 = 1;
			if (lb)
			{
				// //Go to overworld first
				GameData overworld;
				overworld.Initialize();
				
				for(;;){
					
					overworld.Run();
					
					if(true == overworld.terminate){
						break;
					}
					// FsSleep(10);
				}
				
				//Mini Game 2
				printf("Galaga Mini Game");
				Galaga galaga;
				galaga.Initialize();
				
				for(;;){
					
					galaga.Run();
					
					if(true == galaga.terminate){
						break;
					}
					FsSleep(20);
				}
			}
		}
		else if (mx >= px3 && mx <= px3 + 163 && my >= py3-75 && my <= py3 && l3)
		{
			h3 = 1;
			if (lb)
			{
				// //Go to overworld first
				GameData overworld;
				overworld.Initialize();
				
				for(;;){
					
					overworld.Run();
					
					if(true == overworld.terminate){
						break;
		
					}
					// FsSleep(10);
				}
				
				//Mini Game 3
				printf("Rockets Mini Game");
				Rockets rocket;
				rocket.Initialize();
				
				for(;;){
					
					rocket.RunOneStep();
					
					if(true == rocket.terminate){
						break;
					}
					FsSleep(20);
				}
			}
		}
		else if (mx >= px4 && mx <= px4 + 163 && my >= py4-75 && my <= py4 && l4)
		{
			h4 = 1;
			if (lb)
			{
				// //Go to overworld first
				GameData overworld;
				overworld.Initialize();
				
				for(;;){
					
					overworld.Run();
					
					if(true == overworld.terminate){
						break;
					}
					// FsSleep(10);
				}
				
				//Mini Game 4
				printf("Rover Mini Game");
				Rover rover;
				rover.Initialize();
				
				for(;;){
					
					rover.Run();
					
					if(true == rover.terminate){
						break;
					}
					FsSleep(20);
				}
			}
		}
		else if (mx >= px6 && mx <= px6 + 125 && my >= py6 - 144 && my <= py6)
		{
			if (lb)
			{
				//Overworld
				printf("Overworld");
				GameData overworld;
				overworld.Initialize();
				
				for(;;){
					
					overworld.Run();
					
					if(true == overworld.terminate){
						break;
					}
				}
				menu.LoadingGame(level);
				//Go to whatever highest available game is. Pick up where you left off
					if (level == 1)
					{
						Mars mars;
						mars.Initialize();
						
						for(;;){
							
							mars.RunOneStep();
							
							if(true == mars.term){
								break;
							}
							FsSleep(20);
						}
					}
					else if (level == 2)
					{
						Galaga galaga;
						galaga.Initialize();
						
						for(;;){
							
							galaga.Run();
							
							if(true == galaga.terminate){
								break;
							}
							FsSleep(20);
						}
					}
					else if (level == 3)
					{
						Rockets rockets;
						rockets.Initialize();
						
						for(;;){
							
							rockets.RunOneStep();
							
							if(true == rockets.terminate){
								break;
							}
							FsSleep(20);
						}
					}
					else if (level == 4)
					{
						Rover rover;
						rover.Initialize();
						
						for(;;){
							
							rover.Run();
							
							if(true == rover.terminate){
								break;
							}
							FsSleep(20);
						}
					}

			}
		}
		else if (mx >= px5 && mx <= px5 + 100 && my >= py5 - 100 && my <= py5)
		{
			if (lb)
			{
				//reset
				printf("Reset");
				ResetGame(l1, l2, l3, l4);
			}
		}
		else if (mx >= px7 && mx <= px7 + 150 && my >= py7 - 40 && my <= py7)
		{
			if (lb)
			{
				//Launch Tutorial
				printf("Tutorial");
				Tutorial tut;
				tut.Initialize();
				
				for(;;){
					tut.Draw();
					tut.RunOneStep();
					
					if(true == tut.terminate){
						break;
					}
					FsSleep(20);
				}
			}
		}
		else
		{
			h1 = 0, h2 = 0, h3 = 0, h4 = 0;
		}
		
		// Draw OverWorld Continue Button	 
		// Draw Restart Button 
		menu.drawBackground();
		menu.drawTitle();
		menu.drawLevel1(px1, py1, l1, h1);
		menu.drawLevel2(px2, py2, l2, h2);
		menu.drawLevel3(px3, py3, l3, h3);
		menu.drawLevel4(px4, py4, l4, h4);
		menu.drawResetButton(px5, py5);
		menu.drawOverworldButton(px6,py6);
		menu.drawTutorialButton(px7,py7);
		menu.drawRover();
		FsSwapBuffers();
		FsSleep(20);
	}
	
	return 0;
}
