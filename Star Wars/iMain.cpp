#include"iGraphics.h"
#include<math.h>
#include<stdio.h>
#include<string.h>

#define SCREENWIDTH  1300
#define SCREENHEIGHT  700
#define MOVEMENTSPEED 20
#define BACKGROUNDSPEED 1

void Level1AllCollisionChecker();
void ValueResetter();
bool IsColliding(int x1, int y1, int dx1, int dy1, int x2, int y2, int dx2, int dy2);

//first level 100 ships ,second level 150 +small boss ,final level 200 +boss 
int enemyshipcounter = 0;
int mposx, mposy;

//menu structure
struct menu{
	bool showmenu = true;
	bool avatar = false;

	bool avatar1select = false;
	int avatar1_x = 85, avatar1_y = 75;
	bool avatar2select = false;
	int avatar2_x = 525, avatar2_y = 75;
	bool avatar3select = false;
	int avatar3_x = 965, avatar3_y = 75;

	bool namefield = false; bool namefieldactive = false;
	int namefield_x = 477, namefield_y = 514;

	bool play = false; int play_x = 548, play_y = 400;

	bool option = false; int option_x = 517, option_y = 286;

	int turnon_x = 500, turnon_y = 390;
	int turnoff_x = 500, turnoff_y = 260;
	int back_x = 457, back_y = 107;

	bool gameover = false;
	int gameoverquit_x = 525, gameoverquit_y = 15;
	int gameoverback_x = 439, gameoverback_y = 102;

	bool top = false;
	int top_x = 457, top_y = 190;
	int top_dx = 361, top_dy = 45;
	int top_back_x = 540, top_back_y = 23;
	int top_back_dx = 162, top_back_dy = 46;

	bool credits = false;

	bool exit = false; int exit_x = 555, exit_y = 24;
};

struct menu gamemenu;

//Game board health bar

struct health{
	int health_x = SCREENWIDTH - 200 + 20;
	int health_y = 205;
	int health_xsize = 160;
	int health_ysize = 40;
	int health_red = 0;
	int health_green = 255;
	int health_blue = 0;
	int const healthsize = 160;

};
struct health healthboard;

//Scoreboard counter and others
struct score{
	double gamescore = 0;
	int score_x = SCREENWIDTH - 200 + 57;
	int score_y = 587;
	char scorestring[10];
};
struct score score;

//TOP SCORES
struct player{

	char name[100];
	int score;
	int nameindex = 0;
};

struct player playerinfo;
//level structure
bool level1 = true;
bool level2 = false;
bool level3 = false;


//Bacground Redering 
char level1backimg[8][100] = { "image\\b_render\\render1.bmp", "image\\b_render\\render1.bmp",
"image\\b_render\\render2.bmp", "image\\b_render\\render3.bmp", "image\\b_render\\render4.bmp",
"image\\b_render\\render5.bmp", "image\\b_render\\render6.bmp", "image\\b_render\\render7.bmp" };

struct background{
	int x;
	int y;
};
struct background backgroundlevel1render[7];

//Initializes Background at the starting
void BackgroundLevel1Init(){
	int top_y = SCREENHEIGHT;
	for (int i = 0; i < 8; i++){
		backgroundlevel1render[i].y = top_y;
		top_y -= 100;
	}
}

void ShowBackgroundLevel1(){
	for (int i = 0; i < 7; i++){
		iShowBMP(0, backgroundlevel1render[i].y, level1backimg[i]);
	}
}

//GAME MUSIC
bool gamesound = true;
char selecttrack[25] = "sound\\menu_select.wav";
char toppilottrack[30] = "sound\\toppilot.wav";

//Plays track on demands!!!
void Playtrack(bool isplay){
	if (isplay == true && gamemenu.top == true)
		PlaySound(toppilottrack, NULL, SND_ASYNC);
}


// All playership structures and variables starts from here

//playership file name
char playership[3][35] = { "image\\playership\\ship1.bmp", "image\\playership\\ship2.bmp",
"image\\playership\\ship3.bmp" };

//player ship structure
struct playership{
	int x = SCREENWIDTH / 2 - 150;
	int y = 0;
	int shiphealth;
	int dx = 80; int dy = 80;

};
//level 1 ship 1
struct playership playership1;

//laser structure for ship 1 level 1
struct laser
{
	bool shot = false;
	int l_x = playership1.x + 28; int dx = 7;
	int r_x = playership1.x + 43; int dy = 25;
	int  y = playership1.y + 60;
};

//Laser Variables
char bluelaserimg[31] = "image\\playership\\bluelaser.bmp";
struct laser bluelaser[100];
int laserindex = 0;


//All Enemeyship structure starts from here

//Enemy ship realted func , variable all starts from here

char greenhornimg[30] = "image\\enemy\\greenhorn.bmp";
int green_random_x[5] = { 196, 396, 596, 796, 996 };
int green_random_y[5] = { 800, 1300, 2100, 1700, 2500 };
int const greenhornL1size = 6;
struct greenhorn{
	int x;
	int y;
	int dx = 96;
	int dy = 73;
	int ball_x;
	int ball_y;
	double lifevalue = 20;
	int counter = 0;
	bool life = true;

};

int greehorncounter = 0;
struct greenhorn greenhornL1[greenhornL1size];

char droneimg[30] = "image\\enemy\\drone.bmp";
int drone_random_x[5] = { -1700, -1300, -100,- 400, -700 };
int drone_random_y[5] = { 70,180 , 250 ,350 ,450 };
int const droneL1size = 2;
struct drone{
	double x; 
	double y;
	int dx = 63;
	int dy = 59;
	double sinx = 0;
	int lifevalue = 15;
	bool life = true;
};

struct drone droneL1[droneL1size];
//First Time randomly initializes enemey ships positions
void Level1EnemyInit(){

	for (int i = 0; i < greenhornL1size; i++){
		greenhornL1[i].x = green_random_x[rand() % 5];
		greenhornL1[i].y = green_random_y[rand() % 5];
	
	}

	//Initializes Level 1 Drones
	for (int i = 0; i < droneL1size; i++){
		droneL1[i].x = drone_random_x[rand() % 5];
		droneL1[i].y = drone_random_y[rand() % 5];
	}
}

//All enemy drawing function starts here
//Displays Greenhorn enemyship // Called by Idraw functions
void ShowLevel1AllEnemy(){

	//Shows Greenhorn on the screen
	for (int i = 0; i < greenhornL1size; i++){
		if (greenhornL1[i].life == true){
			iShowBMP2(greenhornL1[i].x, greenhornL1[i].y, greenhornimg, 0);
			
		}
	}

	//Shows level1 drones
	for (int i = 0; i < droneL1size; i++){
		if (droneL1[i].life == true){
			iShowBMP2(droneL1[i].x, droneL1[i].y, droneimg, 0);
		}
	}
	
}

//All functions for drawing starts from here

//ship draw func
void ShowScore(){
	_itoa_s(score.gamescore, score.scorestring, 10);
	iSetColor(0, 255, 255);
	iText2(score.score_x, score.score_y, score.scorestring, GLUT_BITMAP_TIMES_ROMAN_24);
}

//Draws a health rectangle
void ShowHealth(){

	if (healthboard.health_xsize > 0){
		if (healthboard.health_xsize >= healthboard.healthsize / 2)
		{
			healthboard.health_blue = 0; healthboard.health_green = 255, healthboard.health_red = 0;
		}
		else if (healthboard.health_xsize < healthboard.healthsize / 2 &&
			healthboard.health_xsize >= healthboard.healthsize / 4){
			healthboard.health_blue = 17; healthboard.health_green = 255, healthboard.health_red = 251;
		}
		else{
			healthboard.health_blue = 0; healthboard.health_green = 0, healthboard.health_red = 255;
		}

		iSetColor(healthboard.health_red, healthboard.health_green, healthboard.health_blue);
		iFilledRectangle(healthboard.health_x, healthboard.health_y, healthboard.health_xsize,
			healthboard.health_ysize);
	}
}

//displays playership 1
void ShowPlayerShip1(){

	iShowBMP2(playership1.x, playership1.y, playership[0], 0);
	for (int i = 0; i < 100; i++){
		if (bluelaser[i].shot == true){
			iShowBMP2(bluelaser[i].l_x, bluelaser[i].y, bluelaserimg, 0);
			iShowBMP2(bluelaser[i].r_x, bluelaser[i].y, bluelaserimg, 0);
		}
	}
	for (int i = 0; i<100; i++){
		if (bluelaser[i].y> SCREENHEIGHT){
			bluelaser[i].shot = false;
			bluelaser[i].l_x = playership1.x + 28, bluelaser[i].r_x = playership1.x + 43,
				bluelaser[i].y = playership1.y + 60;
		}
	}
}

// Playership 1 , level 1 ,Blue laser position initializer function
void Ship1LaserXInecrease(){
	for (int i = 0; i < 100; i++){
		if (bluelaser[i].r_x < 1050 && bluelaser[i].shot == false){
			bluelaser[i].l_x += MOVEMENTSPEED;
			bluelaser[i].r_x += MOVEMENTSPEED;
		}
	}
}

void Ship1LaserXdecrease(){
	for (size_t i = 0; i < 100; i++)
	{
		if (bluelaser[i].l_x >28 && bluelaser[i].shot == false){
			bluelaser[i].l_x -= MOVEMENTSPEED;
			bluelaser[i].r_x -= MOVEMENTSPEED;
		}
	}
}

void Ship1LaserYincrease(){
	for (size_t i = 0; i <100; i++)
	{
		bluelaser[i].y += MOVEMENTSPEED;
	}

}
void Ship1LaserYdecrease(){
	for (size_t i = 0; i < 100; i++)
	{
		if (bluelaser[i].y>80 && bluelaser[i].shot == false)
			bluelaser[i].y -= MOVEMENTSPEED;
	}

}
// palyer ship 1 level lasaer position initializer ends here


void iDraw()
{
	iClear();

	Level1AllCollisionChecker();

	if (gamemenu.showmenu == true){
		iShowBMP(0, 0, "image\\gamemenu\\completemenu.bmp");
	}

	if (gamemenu.avatar == true){
		iShowBMP(0, 0, "image\\gamemenu\\charactermenu.bmp");
	}
	if (gamemenu.top == true){
		iShowBMP(0, 0, "image\\gamemenu\\toppilots.bmp");
	}
	if (gamemenu.option == true){
		iShowBMP(0, 0, "image\\gamemenu\\option.bmp");
	}

	if (gamemenu.namefield == true){
		iShowBMP(0, 0, "image\\gamemenu\\namefield.bmp");
		iSetColor(0, 197, 255);
		iText(543, 530, playerinfo.name, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (gamemenu.play == true && level1==true){
		ShowBackgroundLevel1();
	}
	if (gamemenu.play == true && gamemenu.avatar1select == true){
		iShowBMP(SCREENWIDTH - 200, 0, "image\\gamemenu\\avatar1select.bmp");
		ShowScore();
		ShowHealth();
	}
	else if (gamemenu.play == true && gamemenu.avatar2select == true){

		iShowBMP(SCREENWIDTH - 200, 0, "image\\gamemenu\\avatar2select.bmp");
		ShowScore();
		ShowHealth();

	}
	else if (gamemenu.play == true && gamemenu.avatar3select == true){
		iShowBMP(SCREENWIDTH - 200, 0, "image\\gamemenu\\avatar3select.bmp");
		ShowScore();
		ShowHealth();

	}

	//player spaceships // ship 1 level 1 // and ammos
	if (gamemenu.play == true){
		ShowPlayerShip1();
	}

	if (gamemenu.play == true && level1==true){
		ShowLevel1AllEnemy();
	}

	if (gamemenu.gameover == true){
		iShowBMP(0, 0, "image\\gamemenu\\gameover3.bmp");
	}


}

void iMouseMove(int mx, int my)
{



}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){


		if (gamemenu.showmenu == true && ((mx >= gamemenu.play_x && mx <= gamemenu.play_x + 170) &&
			(my >= gamemenu.play_y && my <= gamemenu.play_y + 46))){
			if (gamesound == true)
				PlaySound(selecttrack, NULL, SND_ASYNC);

			gamemenu.showmenu = false;
			gamemenu.avatar = true;
		}

		else if (gamemenu.showmenu == true && ((mx >= gamemenu.option_x && mx <= gamemenu.option_x + 240)
			&& (my >= gamemenu.option_y && my <= gamemenu.option_y + 52))){
			if (gamesound == true)
				PlaySound(selecttrack, NULL, SND_ASYNC);

			gamemenu.showmenu = false;
			gamemenu.option = true;
		}

		else if (gamemenu.option == true && (mx >= gamemenu.turnon_x && mx <= gamemenu.turnon_x + 240)
			&& (my >= gamemenu.turnon_y && my <= gamemenu.turnon_y + 52)){
			if (gamesound == true)
				PlaySound(selecttrack, NULL, SND_ASYNC);

			gamesound = true;
		}

		else  if (gamemenu.option == true && (mx >= gamemenu.turnoff_x && mx <= gamemenu.turnoff_x + 240)
			&& (my >= gamemenu.turnoff_y && my <= gamemenu.turnoff_y + 52)){
			if (gamesound == true)
				PlaySound(selecttrack, NULL, SND_ASYNC);

			gamesound = false;
		}

		else  if (gamemenu.option == true && (mx >= gamemenu.back_x && mx <= gamemenu.back_x + 334)
			&& (my >= gamemenu.back_y && my <= gamemenu.back_y + 66)){
			if (gamesound == true)
				PlaySound(selecttrack, NULL, SND_ASYNC);

			gamemenu.option = false;
			gamemenu.showmenu = true;
		}

		else if (gamemenu.showmenu == true && ((mx >= gamemenu.exit_x && mx <= gamemenu.exit_x + 165)
			&& (my >= gamemenu.exit_y && my <= gamemenu.exit_y + 73))){

			exit(0);
		}

		else if (gamemenu.avatar == true && (mx >= gamemenu.avatar1_x && mx <= gamemenu.avatar1_x + 265)
			&& (my >= gamemenu.avatar1_y && my <= gamemenu.avatar1_y + 555)){
			if (gamesound == true)
				PlaySound("sound\\menu_select.wav", NULL, SND_ASYNC);

			gamemenu.avatar = false;
			gamemenu.namefield = true;
			gamemenu.avatar1select = true;
		}

		else if
			(gamemenu.avatar == true && (mx >= gamemenu.avatar2_x && mx <= gamemenu.avatar2_x + 265)
			&& (my >= gamemenu.avatar2_y && my <= gamemenu.avatar2_y + 555)){

			if (gamesound == true)
				PlaySound("sound\\menu_select.wav", NULL, SND_ASYNC);

			gamemenu.avatar = false;
			gamemenu.namefield = true;
			gamemenu.avatar2select = true;
		}

		else  if
			(gamemenu.avatar == true && (mx >= gamemenu.avatar3_x && mx <= gamemenu.avatar3_x + 265)
			&& (my >= gamemenu.avatar3_y && my <= gamemenu.avatar3_y + 555)){
			if (gamesound == true){
				PlaySound("sound\\menu_select.wav", NULL, SND_ASYNC);
			}
			gamemenu.avatar = false;
			gamemenu.namefield = true;
			gamemenu.avatar3select = true;
		}

		else if (gamemenu.namefield == true && ((mx >= gamemenu.namefield_x && mx <= gamemenu.namefield_x + 263))
			&& ((my >= gamemenu.namefield_y && my <= gamemenu.namefield_y + 52))){
			gamemenu.namefieldactive = true;

		}

		else if (gamemenu.gameover == true && ((mx >= gamemenu.gameoverquit_x && mx <= gamemenu.gameoverquit_x + 175))
			&& ((my >= gamemenu.gameoverquit_y  && my <= gamemenu.gameoverquit_y + 45))){
			exit(0);
		}

		else if (gamemenu.gameover == true && ((mx >= gamemenu.gameoverback_x && mx <= gamemenu.gameoverback_x + 382))
			&& ((my >= gamemenu.gameoverback_y  && my <= gamemenu.gameoverback_y + 50))){

			if (gamesound == true)
				PlaySound(selecttrack, NULL, SND_ASYNC);

			gamemenu.gameover = false;
			gamemenu.showmenu = true;
			ValueResetter();
		}

		else if (gamemenu.showmenu == true &&
			((mx >= gamemenu.top_x && mx <= gamemenu.top_x + gamemenu.top_dx) &&
			(my >= gamemenu.top_y && my <= gamemenu.top_y + gamemenu.top_dy))){

			gamemenu.showmenu = false;
			gamemenu.top = true;

			if (gamesound == true){
				PlaySound(selecttrack, NULL, SND_ASYNC);
				Playtrack(true);

			}


		}

		else if (gamemenu.top == true &&
			((mx >= gamemenu.top_back_x && mx <= gamemenu.top_back_x + gamemenu.top_back_dx) &&
			(my >= gamemenu.top_back_y && my <= gamemenu.top_back_y + gamemenu.top_back_dy))){
			gamemenu.top = false;
			gamemenu.showmenu = true;
			Playtrack(false);
			if (gamesound == true)
				PlaySound(selecttrack, NULL, SND_ASYNC);
		}
	}
}


void iPassiveMouseMove(int mx, int my)
{
	mposx = mx;
	mposy = my;
	if (mx == 2){}
	else if (my == 2){}

}


void iKeyboard(unsigned char key)
{

	if (gamemenu.play == true && key == ' '){
		if (laserindex == 40)
			laserindex = 0;
		if (gamesound == true)
			PlaySound("sound\\lasershot.wav", NULL, SND_ASYNC);
		bluelaser[laserindex++].shot = true;
	}
	else if (gamemenu.namefieldactive == true && playerinfo.nameindex <= 9){
		if (key != '\b'){
			playerinfo.name[playerinfo.nameindex] = key;
			playerinfo.name[playerinfo.nameindex + 1] = '\0';
			playerinfo.nameindex++;
		}
		else{
			playerinfo.name[playerinfo.nameindex] = '\0';
			playerinfo.nameindex--;
			if (playerinfo.nameindex < 0)
				playerinfo.nameindex = 0;
		}
	}
	if (gamemenu.namefieldactive == true && key == '\r'){
		if (gamesound == true)
			PlaySound(selecttrack, NULL, SND_ASYNC);
		gamemenu.namefieldactive = false; gamemenu.namefield = false;
		gamemenu.play = true;
	}


}


void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_END && gamemenu.namefield == true){
		gamemenu.namefield = false;
		gamemenu.play = true;
	}
	//player spaceship position
	if (key == GLUT_KEY_UP)
	{
		if (playership1.y<SCREENHEIGHT - 80)
			playership1.y += MOVEMENTSPEED;
	}
	if (key == GLUT_KEY_DOWN){
		if (playership1.y > 0)
			playership1.y -= MOVEMENTSPEED;
	}
	if (key == GLUT_KEY_RIGHT){
		if (playership1.x < SCREENWIDTH - 290){
			playership1.x += MOVEMENTSPEED;
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (playership1.x> 10)
			playership1.x -= MOVEMENTSPEED;
	}


	//laser shot initial position decider
	if (key == GLUT_KEY_RIGHT){

		Ship1LaserXInecrease();
	}
	if (key == GLUT_KEY_LEFT){
		Ship1LaserXdecrease();
	}
	if (key == GLUT_KEY_UP){
		Ship1LaserYincrease();
	}
	if (key == GLUT_KEY_DOWN){
		Ship1LaserYdecrease();
	}
}

//All functions that need to be called by iSettimer starts here
//palyer "change fucntions" starts here
//Background Render change functions
void BackgroundChange(){
	for (int i = 0; i < 8; i++){
		backgroundlevel1render[i].y -= 1;
		if (backgroundlevel1render[i].y + 100 == 0)
			backgroundlevel1render[i].y = SCREENHEIGHT;
	}
}
//Player ship 1, blue laser changer
void laserchange(){
	for (size_t i = 0; i < 100; i++)
	{
		if (bluelaser[i].shot == true)
			bluelaser[i].y += MOVEMENTSPEED;
	}

}
// player "change functions" finishes here

//Enemy ship change func starts hee
void GreenhornChange(){
	if (gamemenu.play == true && level1==true){
		for (int i = 0; i < greenhornL1size; i++){
			if (greenhornL1[i].y <= 0 || greenhornL1[i].life == false){
				greenhornL1[i].y = green_random_y[rand() % 5];
				greenhornL1[i].x = green_random_x[rand() % 5];
				greenhornL1[i].lifevalue = 20;
				greenhornL1[i].life = true;
			}
			greenhornL1[i].y--;
		}
	}
}

void DroneChange(){
	if (gamemenu.play == true && level1 ==true){
		for (int i = 0; i < droneL1size; i++){
			if (droneL1[i].life == false || droneL1[i].x>=SCREENWIDTH-263){
				droneL1[i].x = drone_random_x[rand() % 5];
				droneL1[i].y = drone_random_y[rand() % 5];
				droneL1[i].life = true;
				droneL1[i].lifevalue = 15;
			}
			droneL1[i].y = 80 * sin(droneL1[i].sinx) + 400;
			droneL1[i].sinx += 0.05; 
			droneL1[i].x += 2;
		}
	}
}

//All enemy change functions ends here


//All collision fucntions starts here
//Wholla...Collision check function // Just Pass your value to it.. 
bool IsColliding(int x1, int y1, int dx1, int dy1, int x2, int y2, int dx2, int dy2){

	if ((x1 + dx1 > x2 && x2 + dx2 > x1) && (y1 + dy1 >y2 && y2 + dy2 > y1))
		return true;
	else
		return false;
}

//Checks all collsions on level 1

void Level1AllCollisionChecker(){

	//Greenhorn and ship 1 collision
	if (gamemenu.play == true && level1==true){
		for (int i = 0; i < greenhornL1size; i++){
			if (IsColliding(greenhornL1[i].x, greenhornL1[i].y, greenhornL1[i].dx, greenhornL1[i].dy,
				playership1.x, playership1.y, playership1.dx, playership1.dy)){

				greenhornL1[i].lifevalue -= 10;
				score.gamescore += 5;
				if (greenhornL1[i].lifevalue <= 0){
					greehorncounter += 1;
					greenhornL1[i].life = false;
				}
				
				healthboard.health_xsize -= 15;

				if (healthboard.health_xsize <= 0){
					gamemenu.gameover = true;
					gamemenu.play = false;
				}

			}
		}
	}
	//BLuelaser and Greenhorn Collision
	if (gamemenu.play == true && level1 ==true){
		for (int i = 0; i < 100; i++){
			for (int j = 0; j < greenhornL1size; j++){
				if (greenhornL1[j].life == true && bluelaser[i].shot == true){
					if (IsColliding(greenhornL1[j].x, greenhornL1[j].y, greenhornL1[j].dx, greenhornL1[j].dy,
						bluelaser[i].l_x, bluelaser[i].y - 8, bluelaser[i].dx, bluelaser[i].dy - 8)){
						bluelaser[i].shot = false;
						bluelaser[i].l_x = playership1.x + 28;
						bluelaser[i].r_x = playership1.x + 43;
						bluelaser[i].y = playership1.y + 60;
						greenhornL1[j].lifevalue -= 0.50;
						score.gamescore += 0.50;
						if (greenhornL1[j].lifevalue <= 0)
							greenhornL1[j].life = false;
					}
				}
			}
		}
	}

	//Drone and Ship 1 collsions
	if (gamemenu.play == true && level1 == true){
		for (int i = 0; i < droneL1size; i++){
			if (IsColliding(droneL1[i].x, droneL1[i].y, droneL1[i].dx, droneL1[i].dy,
				playership1.x, playership1.y, playership1.dx, playership1.dy)){
				
				droneL1[i].lifevalue -= 5;
				if (droneL1[i].lifevalue <= 0){
					droneL1[i].life = false;
				}
				healthboard.health_xsize -= 5;
				if (healthboard.health_xsize <= 0){
					gamemenu.gameover = true;
					gamemenu.play = false;
				}
			}
		}
	}

	//Drone and blue laser Collsion
	if (gamemenu.play == true && level1 == true){
		for (int i = 0; i < 100; i++){
			for (int j = 0; j < droneL1size; j++){
				if (droneL1[j].life == true && bluelaser[i].shot == true){
					if (IsColliding(droneL1[j].x, droneL1[j].y, droneL1[j].dx, droneL1[j].dy,
						bluelaser[i].l_x, bluelaser[i].y - 8, bluelaser[i].dx, bluelaser[i].dy - 8)){
						
						bluelaser[i].shot = false;
						bluelaser[i].l_x = playership1.x + 28;
						bluelaser[i].r_x = playership1.x + 43;
						bluelaser[i].y = playership1.y + 60;
						droneL1[j].lifevalue -= 5;
						score.gamescore += 1;
						if (droneL1[j].lifevalue <= 0)
							droneL1[j].life = false;
					}
				}
			}
		}
	}
}



//Value Resetter after game Restart
void ValueResetter(){
	//Enemy Variables level 1
	enemyshipcounter = 0;
	Level1EnemyInit();

	//Playership variables level 1
	int  y = playership1.y + 80;
	playership1.x = SCREENWIDTH / 2 - 150;
	playership1.y = 0;

	//blue laser resetting
	for (int i = 0; i < 100; i++){
		bluelaser[i].l_x = playership1.x + 25;
		bluelaser[i].r_x = playership1.x + 35;
		bluelaser[i].y = playership1.y + 80;
	}
	score.gamescore = 0;
	healthboard.health_xsize = healthboard.healthsize;

}

int main()
{
	BackgroundLevel1Init();
	Level1EnemyInit();
	iSetTimer(3, DroneChange);
	//iSetTimer(50, BackgroundChange);
	iSetTimer(8, GreenhornChange);
	iSetTimer(18, laserchange);
	iInitialize(SCREENWIDTH, SCREENHEIGHT, "SPACE WAR");

	return 0;
}