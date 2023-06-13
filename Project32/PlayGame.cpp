#include "PlayGame.h"
#include <time.h>
#include "util.h"
#include <fstream>


Game* Game::instance = new Game;		// Singleton Instance of Game
Play* Play::instance = new Play;		// Singleton Instance of Play
Play* play = Play::getInstance();		// getting instance
Game* gameG = Game::getInstance();
int Level::num = 1;			// initializing static ids of Levels
// Borders of Game
Obstacle o1(1, 1050, 0, "Border - Right", ORANGE, 30, 630);		// full
Obstacle o2(2, 0, 0, "Border - Left", ORANGE, 30, 630);			// full
Obstacle o3(3, 150, 0, "Border - Down", ORANGE, 780, 30);		// half
Obstacle o4(4, 150, 600, "Border - Up", ORANGE, 780, 30);		// half
Obstacle o5(5, 0, 150, "Border - Left", ORANGE, 30, 480);		// half
Obstacle o6(6, 1050, 150, "Border - Right", ORANGE, 30, 480);	// half

// Borders of Center
Obstacle o7(7, 300, 300, "Center - Horizontal", ORANGE, 530, 30);
Obstacle o8(8, 525, 200, "Center - Vertical", ORANGE, 30, 260);
Obstacle o9(9, 500 ,225, "Center - Horicontal", ORANGE, 80, 150);
Obstacle o10(10, 440 ,255, "Center - Horicontal", ORANGE, 200, 90);
Obstacle o11(11, 380 ,285, "Center - Horicontal", ORANGE, 320, 30);

// Obstacles of Screen
Obstacle o12(12, 100, 200, "Square", ORANGE, 50, 50);
Obstacle o13(13, 930, 200, "Square", ORANGE, 50,50);
Obstacle o14(14, 100, 380, "Square", ORANGE, 50, 50);
Obstacle o15(15, 930, 380, "Square", ORANGE, 50, 50);

//Three types of Canon
Canon smallCanon(1, 5, 10000, 15);	// Size: 15, Damage: 1 points
Canon mediumCanon(2, 10, 3, 20);	// Size: 20, Damage: 2 points
Canon largeCanon(4, 15, 1, 40);		// Size: 40, Damage: 4 points

// Three Types of Vehicles And assigning them "Names" and three Canons
Vehicle tank("Tank", 5, smallCanon, mediumCanon, largeCanon);
Vehicle helicopter("Helicopter", 5, smallCanon, mediumCanon, largeCanon);
Vehicle plane("Plane", 5, smallCanon, mediumCanon, largeCanon);
// Generating array of Obstacles
Obstacle* arr[] = { &o1, &o2, &o3, &o4,&o5, &o6, &o7, &o8, &o9, &o10, &o11, &o12, &o13, &o14, &o15 };

//RGBpixmap pix[6];

Game::Game() {		// Default Constructor of Game
	players = NULL;
	settings;
	count = 0;
	ptr = NULL;
	highscores = NULL;
}

void Game::showStartAnimation(int c) {		// Function to Show Start Animation of Game
	/*pix[0].readBMPFile("Atari.bmp");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -1, 1);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	glPixelZoom(1, 1);
	glRasterPos2i(-20, 20);
	pix[0].draw();
	glutSwapBuffers();
	glFlush();*/
	//glBindTexture(GL_TEXTURE_2D, LoadTexture("Atari.bmp"));
	
	DrawString(c*30+50, 400, "ATARI GAME COMBAT", colors[MISTY_ROSE]);
	Sleep(50); // This will stop the program for some time
	if (c == 39) {	// checking to initialize game and stoping animation
		gameG->getsetting().changeVehicle("Tank", 1); // Default Player 1 Vehicle
		gameG->getsetting().changeVehicle("Tank", 2); // Default Player 2 Vehicle
		gameG->getsetting().changeControls(1, 2); // Default Player 1 Controls
		gameG->getsetting().changeControls(2, 1); // Default Player 1 Controls
	}
}

void Game::showMenu() {		// Showing Menu
	int color = ORANGE_RED;	// getting index of color ORANGE_RED
	DrawString(485, 600, "MENU", colors[color]);	// Heading
	DrawRoundRect(150, 380, 350, 80, colors[WHITE], 20.5f);	// HighScore Button
	DrawRoundRect(580, 380, 350, 80, colors[WHITE], 20.5f);	// Credits Button
	DrawRoundRect(365, 260, 350, 80, colors[WHITE], 20.5f);	// Settings Button
	DrawRoundRect(150, 140, 350, 80, colors[WHITE], 20.5f);	// 1 PLayer Button
	DrawRoundRect(580, 140, 350, 80, colors[WHITE], 20.5f);	// 2 Player Button
	DrawRoundRect(365, 20, 350, 80, colors[WHITE], 20.5f);	// Instructions Button
	// All text for the buttons created Above
	DrawString(265, 415, "High Scores", colors[color]);
	DrawString(720, 415, "Credits", colors[color]);
	DrawString(500, 295, "Settings", colors[color]);
	DrawString(260, 175, "Play 1 Player", colors[color]);
	DrawString(700, 175, "Play 2 Player", colors[color]);
	DrawString(485, 55, "Instructions", colors[color]);
}

void Game::startGame() {	// This will start the game
	cout << "Start GAme\n";
	play->updateLevels();	// this will update the levels and create bots for levels
	// Setting level member stop to show the game is stop to false
	play->getLevel1().setStop(false);
	play->getLevel2().setStop(false);
	play->getLevel3().setStop(false);
	// Setting that the game is not passed
	play->getLevel1().setGamePassed(false);
	play->getLevel2().setGamePassed(false);
	play->getLevel3().setGamePassed(false);
}

Game* Game::getInstance() { // getting instance
	return instance;
}

void Game::ShowCredits() {
	// Just Showing Credits Page
	DrawString(485, 650, "CREDITS", colors[ORANGE_RED]);	// Page title
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);	// Back Button
	DrawString(55, 660, "back", colors[ORANGE_RED]);	// Back button text
}

void Game::showInstructions() {
	// Just Showing Instructions Page
	DrawString(475, 650, "INSTRUCTIONS", colors[ORANGE_RED]);	// Page title
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);	// Back Button
	DrawString(55, 660, "back", colors[ORANGE_RED]);	// Back button text

	DrawRoundRect(240, 550, 40, 40, colors[ORANGE_RED]);
	DrawString(248, 563, "m", colors[WHITE]);
	DrawString(370, 563, "Player 1 - Shoot Medium Canon", colors[WHITE]);

	DrawRoundRect(240, 500, 40, 40, colors[ORANGE_RED]);
	DrawString(252, 513, "l", colors[WHITE]);
	DrawString(370, 513, "Player 1 - Shoot Large Canon", colors[WHITE]);

	DrawRoundRect(210, 450, 110, 40, colors[ORANGE_RED]);
	DrawString(220, 463, "spacebar", colors[WHITE]);
	DrawString(370, 463, "Player 1 - Shoot Small Canon", colors[WHITE]);

	DrawRoundRect(240, 400, 40, 40, colors[ORANGE_RED]);
	DrawString(250, 413, "o", colors[WHITE]);
	DrawString(370, 413, "Player 1 - Use Power Ups", colors[WHITE]);

	DrawRoundRect(240, 350, 40, 40, colors[ORANGE_RED]);
	DrawString(250, 363, "p", colors[WHITE]);
	DrawString(370, 363, "Player 1 - Pick Pop-Up Canon", colors[WHITE]);

	DrawRoundRect(240, 300, 40, 40, colors[ORANGE_RED]);
	DrawString(250, 313, "q", colors[WHITE]);
	DrawString(370, 313, "Player 2 - Pick Pop-Up Canon", colors[WHITE]);


	DrawRoundRect(240, 250, 40, 40, colors[ORANGE_RED]);
	DrawString(250, 263, "e", colors[WHITE]);
	DrawString(370, 263, "Player 2 - Use Power Ups", colors[WHITE]);


	DrawRoundRect(240, 200, 40, 40, colors[ORANGE_RED]);
	DrawString(250, 213, "z", colors[WHITE]);
	DrawString(370, 213, "Player 2 - Shoot Small Canon", colors[WHITE]);

	DrawRoundRect(240, 150, 40, 40, colors[ORANGE_RED]);
	DrawString(250, 163, "x", colors[WHITE]);
	DrawString(370, 163, "Player 2 - Shoot Medium Canon", colors[WHITE]);

	DrawRoundRect(240, 100, 40, 40, colors[ORANGE_RED]);
	DrawString(250, 113, "c", colors[WHITE]);
	DrawString(370, 113, "Player 2 - Shoot Large Canon", colors[WHITE]);
}

void Game::showHighScores() {
	// Showing HighScores
	DrawString(485, 650, "HIGH SCORES", colors[ORANGE_RED]); // title
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);		// back button
	DrawString(55, 660, "back", colors[ORANGE_RED]);	// back button text
	DrawString(150, 550, "Players Name", colors[ORANGE_RED]);	// column heading
	DrawString(370, 550, "Highscores", colors[ORANGE_RED]);	// scores column heading
	if (count == 0) { // checking that only one time the information of player is written
		int noOfLines = 0;	// checking how many lines exist in file
		ifstream score;	
		score.open("highscores.txt");	// opening file in read mode
		string s;	// temporary variable
		for (int i = 0; !score.eof(); i++) {
			getline(score, s);		// getting input
			noOfLines++;		// increaing number of lines
		}
		score.close();		// closing file

		cout << "No of Lines: " << noOfLines / 2 << endl;	// dividing it with two to get name and score of player as one
		noOfLines /= 2;
		score.open("highscores.txt");		// again opening to load data
		ptr = new string[noOfLines];		// creating names array for storing data
		highscores = new int[noOfLines];	// creating scores array for storing data
		for (int i = 0; i < noOfLines; i++) {
			cout << "i";
			getline(score, ptr[i]);	// getting input in names array
			getline(score, s);	// getting input number in temporary variable
			highscores[i] = stoi(s);	// converting string to int and storing in array of scores
		}
		score.close();	// closing file	
		count++;	// incrementing count to not load this action again

		int temp;
		// sorting players on basis of players scores
		for (int i = 0; i < noOfLines; i++) {
			for (int j = 0; j < noOfLines; j++) {
				if (highscores[i] > highscores[j]) {	// if true then scores along with name is swapped
					temp = highscores[i];
					highscores[i] = highscores[j];
					highscores[j] = temp;
					s = ptr[i];
					ptr[i] = ptr[j];
					ptr[j] = s;
				}
			}

		}

	}
	for (int i = 0; i < 10; i++) {		// displaying data from arrays
		DrawString(150, 550 - (i + 1) * 30, ptr[i], colors[WHITE]);	// displays the name
		DrawString(400, 550 - (i + 1) * 30, to_string(highscores[i]), colors[WHITE]);	// display the scores
	}



}

void Game::showSettings() {
	DrawString(485, 650, "SETTINGS", colors[ORANGE_RED]);	// title
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);		// button
	DrawString(55, 660, "back", colors[ORANGE_RED]);

	// Inner Rectangle
	DrawRoundRect(300, 100, 480, 500, colors[ORANGE_RED]);

	// Inner Buttons
	DrawRoundRect(400, 425, 280, 60, colors[WHITE]);
	DrawRoundRect(400, 335, 280, 60, colors[WHITE]);
	DrawRoundRect(400, 245, 280, 60, colors[WHITE]);

	// Buttons Text
	DrawString(510, 445, "Sound", colors[ORANGE_RED]);
	DrawString(502, 355, "Vehicle", colors[ORANGE_RED]);
	DrawString(495, 265, "Controls", colors[ORANGE_RED]);

}

void Game::startPlayer1() {
	//cout << "Entered in Display Mode\n";
	DrawString(485, 650, "PLAYER 01", colors[ORANGE_RED]);	// title 
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);
	DrawString(55, 660, "back", colors[ORANGE_RED]);

	DrawString(365, 470, "PLAYER 1 NAME ", colors[WHITE]);	// asking to enter players name
	DrawRectangle(365, 410, 350, 40, colors[WHITE]);
	DrawString(385, 408, play->getPlayer1().getName(), colors[BLACK]);	// displays palyers name when entered on console

	// button to start game
	DrawRoundRect(440, 320, 200, 60, colors[ORANGE_RED]);
	DrawString(465, 340, "START GAME", colors[WHITE]);

	if (play->getGameRecordExistance()) {
		DrawRoundRect(440, 240, 200, 60, colors[ORANGE_RED]);
		DrawString(460, 253, "RESUME GAME", colors[WHITE]);
	}
	cout << "Displayed\n";
}

void Game::startPlayer2() {
	DrawString(485, 650, "PLAYER 02", colors[ORANGE_RED]);		// title
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);		// button
	DrawString(55, 660, "back", colors[ORANGE_RED]);		// button text

	// inner rectangle boundary
	DrawRoundRect(200, 100, 680, 450, colors[ORANGE_RED]);

	// Asking Player 01 Name
	DrawString(365, 450, "PLAYER 1 NAME ", colors[WHITE]);
	DrawRectangle(365, 390, 350, 40, colors[WHITE]);

	// Asking Player 02 Name
	DrawString(365, 310, "PLAYER 2 NAME ", colors[WHITE]);
	DrawRectangle(365, 250, 350, 40, colors[WHITE]);

	// Displays the players Name when Entered on Console
	DrawString(385, 400, play->getPlayer1().getName(), colors[BLACK]);
	DrawString(385, 260, play->getPlayer2().getName(), colors[BLACK]);

	// Button to start game
	DrawRoundRect(440, 150, 200, 70, colors[WHITE]);
	DrawString(470, 175, "START GAME", colors[ORANGE_RED]);

	// Condition when name not entered will display error
	if (play->getPlayer1().getName() == "") {
		DrawString(385, 370, "Enter Player 01 Name", colors[RED]);
	}

	if (play->getPlayer2().getName() == "") {
		DrawString(385, 230, "Enter Player 02 Name", colors[RED]);
	}
}

Play::Play() {	// default constructor of Play Class
	score = 0;
	player1;
	player2;
	level1;
	level2;
	level3;
	type = 1;
	currentLvl = 1;
	isShowingNextLevel = false;
	isShowingRetry = false;
	isShowingWinner = false;
	gameRecordExist = false;
	p1NoOfRespawn = 3;
	p2NoOfRespawn = 3;
	count = 0;
}

void Play::begin1PlayerGame() {	// start the 1 player game with bot
	// Setting location of Player 02 to X = -50 and Y = 50 as player 2 has no role in player 1 game
	cout << "Begin 1 Player\n";
	player2.getVehicle().getLocation().setX(-50);
	player2.getVehicle().getLocation().setY(50);

	// Conditionn that which game to load
	if (level1.isPassed() == false && currentLvl == 1 && level1.getGameStoped() == false) {
		level1.load1Player();	// loads Level 1 game
	}
	else if (level2.isPassed() == false && level1.isPassed() && currentLvl == 2 && level2.getGameStoped() == false) {
		level2.load1Player();	// loads Level 2 game
	}
	else if (level3.isPassed() == false && level2.isPassed() && currentLvl == 3 && level3.getGameStoped() == false) {
		level3.load1Player();	// loads Level 3 game
	}
	// checking if player vehicle is destroyed
	if (player1.getVehicle().getlife() <= 0) {
		if (p1NoOfRespawn > 0) {
			player1.respawn();		// redisplays the vehicle
			p1NoOfRespawn--;		// decrease its lifes (hearts)
		}
		else {
			// displays the retry screen
			play->gameRetry();
			isShowingRetry = true;
			level1.setStop(true);		// stops the game
			level2.setStop(true);		// stops the game
			level3.setStop(true);		// stops the game
		}
		
	}

	// checks for level passed and shows the Next Level screen
	else if (level1.isPassed() == false && (level1.getBot())[0].getVehicle().getlife() <= 0) {
		play->showNextLevelScreen();
		setShowNextLvl(true);
		level1.setStop(true);
	}
	
	else if (level2.isPassed() == false && level1.isPassed() == true && (level2.getBot())[0].getVehicle().getlife() <= 0 && (level2.getBot())[1].getVehicle().getlife() <= 0) {
		play->showNextLevelScreen();
		setShowNextLvl(true);
		level2.setStop(true);
	}
	// Shows the Winner screen when players has complteed the three levels
	else if (level3.isPassed() == false && level2.isPassed() == true && (level3.getBot())[0].getVehicle().getlife() <= 0 && (level3.getBot())[1].getVehicle().getlife() <= 0 && (level3.getBot())[2].getVehicle().getlife() <= 0) {
		play->showWinningScreen();	// show winner screen
		setIsShowingWinner(true);	// boolean setted to true
		level3.setStop(true);	// game stopped
		if (count == 0) {		// writing the highscores in highscores text file
			ofstream score;
			score.open("highscores.txt", ios::app);
			score << player1.getName() << endl;		// writing name
			score << player1.getScore() << endl;		// writing score
			score.close();
			count++;
		}
	}
}

Play* Play::getInstance() {
	return instance;
}

Level* Play::getL1() {
	return &level1;
}

void Play::updateLevels() {	// Updates the level
	cout << "Update Levels";
	level1.createObstacles(6);	// Createssix obstacles in level
	level2.createObstacles(8);	// Creates 8 obstacles in level
	level3.createObstacles(10);// Creates 10 obstacles in level
}

void Play::showPausedScreen() { // displays Paused Screen
	DrawRoundRect(275, 200, 530, 320, colors[ORANGE_RED]);
	DrawRoundRect(325, 300, 200, 60, colors[WHITE]);
	DrawRoundRect(555, 300, 200, 60, colors[WHITE]);
	DrawString(325, 400, "What would to like to do?", colors[WHITE]);
	DrawString(395, 320, "Resume", colors[ORANGE_RED]);	// Button to resume the game
	DrawString(625, 320, "Leave", colors[ORANGE_RED]);	// Button to leave the game
}

void Play::begin2PlayerGame() {
	// Begins two player game
	if (level3.getGameStoped() == false) {
		level1.setGamePassed(true);
		level2.setGamePassed(true);
		level3.load2Player();	// loading two player game
	}
	// if one player is destroyed, will dislays the results
	if (player1.getVehicle().getlife() <= 0 || player2.getVehicle().getlife() <= 0) {
		level3.setStop(true);
		isShowingWinner = true;
		showWinningScreen();	// shows results on winner screen
	}
}

void Play::showNextLevelScreen() {
	short lvl = 1;	// checking level
	Bot* bots = level1.getBot();
	if (level1.isPassed() == true) {
		lvl = 2;
	}
	DrawRoundRect(250, 150, 580, 420, colors[ORANGE_RED]);
	DrawString(450, 500, "LEVEL 0" + to_string(lvl) + " PASSED", colors[WHITE]); // Displaying level nomber that has been passed

	DrawLine(540, 480, 540, 300, 6, colors[WHITE]);	// seperates player 1 from player 2

	DrawString(330, 440, "Player 01", colors[WHITE]);	// heading 
	DrawString(630, 440, "Player 02", colors[WHITE]);
	DrawString(260, 380, "Name : " + player1.getName(), colors[WHITE]);	// displays player 1 name
	DrawString(260, 350, "Score: " + to_string(player1.getScore()), colors[WHITE]);	// display player 1 score

	if (type == 1) {
		DrawString(550, 380, "Bots Name : Bots", colors[WHITE]);// display bots name
		DrawString(550, 350, "Score: " + to_string(bots[0].getScore()), colors[WHITE]);// display bots score
	}
	else {
		DrawString(550, 380, "Name : " + player2.getName(), colors[WHITE]);
		DrawString(550, 350, "Score: " + to_string(player2.getScore()), colors[WHITE]);
	}

	DrawRoundRect(340, 170, 400, 70, colors[WHITE]);
	DrawString(460, 192.5, "NEXT LEVEL", colors[ORANGE_RED]);// button for moving to next level
}

void Play::showWinningScreen() {
	Bot* bots = level3.getBot();

	DrawRoundRect(250, 150, 580, 420, colors[ORANGE_RED]);
	DrawString(450, 500, "GAME COMPLETED", colors[WHITE]);

	DrawLine(540, 480, 540, 300, 6, colors[WHITE]);

	DrawString(300, 440, "Player 01", colors[WHITE]);
	DrawString(640, 440, "Player 02", colors[WHITE]);

	DrawString(260, 400, "Name : " + player1.getName(), colors[WHITE]);
	DrawString(260, 370, "Score: " + to_string(player1.getScore()), colors[WHITE]);

	if (type == 1) {
		DrawString(550, 400, "Bots Name : Bots", colors[WHITE]);
		DrawString(550, 370, "Score: " + to_string(bots[0].getScore()), colors[WHITE]);

		DrawString(350, 350, "WINNER", colors[WHITE]);
	}
	else {
		DrawString(550, 400, "Name : " + player2.getName(), colors[WHITE]);
		DrawString(550, 370, "Score: " + to_string(player2.getScore()), colors[WHITE]);
		if (player1.getScore() > player2.getScore()) {
			DrawString(350, 350, "WINNER", colors[WHITE]);
		}
		else {
			DrawString(630, 350, "WINNER", colors[WHITE]);
		}
	}
	DrawRoundRect(390, 260, 300, 60, colors[WHITE]);
	DrawString(480, 278, "RE-MATCH", colors[ORANGE_RED]);
	DrawRoundRect(340, 170, 400, 70, colors[WHITE]);
	DrawString(420, 192.5, "BACK TO MAIN MENU", colors[ORANGE_RED]);
}

void Play::gameRetry() {// shows the game to retry 
	short lvl = 1;	
	Bot* bots = level1.getBot();
	if (level1.isPassed() == true) {
		lvl = 2;
	}
	if (level2.isPassed() == true) {
		lvl = 3;
	}
	DrawRoundRect(250, 150, 580, 420, colors[ORANGE_RED]);
	DrawString(450, 500, "LEVEL 0" + to_string(lvl) + " FAILED", colors[WHITE]); // drawing level faild
	// seperation line
	DrawLine(540, 480, 540, 300, 6, colors[WHITE]);
	// Displays Bots and players score
	DrawString(330, 440, "Player 01", colors[WHITE]);
	DrawString(630, 440, "Player 02", colors[WHITE]);
	DrawString(260, 380, "Name : " + player1.getName(), colors[WHITE]);
	DrawString(260, 350, "Score: " + to_string(player1.getScore()), colors[WHITE]);

	DrawString(550, 380, "Bots Name : Bots", colors[WHITE]);
	DrawString(550, 350, "Score: " + to_string(bots[0].getScore()), colors[WHITE]);

	DrawRoundRect(340, 170, 400, 70, colors[WHITE]);
	DrawString(460, 192.5, "RETRY GAME", colors[ORANGE_RED]); //  option to retry game
}

void Play::resetPlay() {
	cout << "Reset Play\n";
	score = 0;
	// reset the play class to default whe a game completes
	player1.setScore(0);
	player1.getVehicle().setlife(10);
	player1.getVehicle().getLargeCanon().setAvailableShells(1);
	player1.getVehicle().getMediumCanon().setAvailableShells(3);
	player1.getVehicle().getLocation().setX(50);
	player1.getVehicle().getLocation().setY(50);

	player2.setScore(0);
	player2.getVehicle().setlife(10);
	player2.getVehicle().getLargeCanon().setAvailableShells(1);
	player2.getVehicle().getMediumCanon().setAvailableShells(3);
	player2.getVehicle().getLocation().setX(50);
	player2.getVehicle().getLocation().setY(50);

	currentLvl = 1;
	isShowingNextLevel = false;
	isShowingRetry = false;
	isShowingWinner = false;
	p1NoOfRespawn = 3;
	p2NoOfRespawn = 3;



}


Level::Level() {
	id = num;
	obstacles = nullptr;
	numberOfObstacles = 0;
	p1vehicle = nullptr;
	p2vehicle = nullptr;
	bots = nullptr;
	noOfBots = num + 1;
	passed = false;
	num++;
	if (num == 4) {
		num = 1;
	}
	stop = false;
	count = 0;
}

void Level::operator=(Level& lev) {
	id = lev.id;
	obstacles = new Obstacle[lev.numberOfObstacles];
	for (int i = 0; i < lev.numberOfObstacles; i++) {
		obstacles[i] = lev.obstacles[i];
	}
	numberOfObstacles = lev.numberOfObstacles;
}

void Level::createObstacles(int noOfObstacles) {
	srand(time(NULL));
	numberOfObstacles = noOfObstacles;
	if (obstacles == nullptr) {
		obstacles = new Obstacle[noOfObstacles];
	}
	int x = (rand() % 2) + 1;
	if (x == 1) {x = 0; }
	// Assigning Borders
	for (int i = 0; i < 4; i++) {
		if (noOfObstacles > 0) {
			obstacles[i] = *arr[i + x];
			noOfObstacles--;
		}
	}
	// Assigning Center
	x = (rand() % 2) + 1;
	int y;
	if (x == 1) { y = 2; x--; }
	else { y = 3; }
	for (int i = 0; i < y; i++) {
		if (noOfObstacles > 0) {
			obstacles[i + 4] = *arr[6 + x + i];
			noOfObstacles--;
		}
	}
	// Assigning Random Obstacles
	x = (rand() % 3 ) + 0;

	for (int i = 0; i <= x; i++) {
		if (noOfObstacles > 0) {
			obstacles[i + 4 + y] = *arr[11 + i];
			noOfObstacles--;
		}
	}
	p1vehicle = &(play->getPlayer1().getVehicle());
	p2vehicle = &(play->getPlayer2().getVehicle());
}

void Level::load1Player() {
	cout << "Load 1 Player\n";
	/*glClearColor(0.07f, 0.13f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);*/

	// show Hearts (Lifes)
	for (int i = 0; i < play->getP1NoOfRespawn(); i++) {
		DrawTriangle(20*(i+1) + i*10, 690, 20 * (i + 1) + i * 10 + 30, 690, 20 * (i + 1) + i * 10 + 15, 670, colors[RED]);
		DrawCircle(20 * (i + 1) + i * 10 + 7.5, 693, 7.5, colors[RED]);
		DrawCircle(20 * (i + 1) + i * 10 + 22.5, 693, 7.5, colors[RED]);
	}

	DrawRoundRect(10, 635, 120, 30, colors[ORANGE_RED]);
	DrawString(12, 640, "PowerUp " + to_string(play->getPlayer1().getnoOfPowerUps()), colors[WHITE]);

	DrawRoundRect(975, 675, 100, 40, colors[ORANGE_RED]);
	DrawString(992, 685, "Pause", colors[WHITE]);
	string temp = "LEVEL 0" + to_string(id);
	DrawString(485, 675, temp, colors[ORANGE_RED]);
	DrawString(235, 685, to_string(play->getPlayer1().getScore()), colors[ORANGE_RED]);
	DrawString(780, 685, to_string(bots[0].getScore()), colors[ORANGE_RED]);

	
	DrawRectangle(700, 657, 172, 20, colors[ORANGE_RED]);
	for (int i = 0; i < 10; i++) {
		if (i + 1 <= bots[0].getVehicle().getlife()) {
			DrawRectangle(702 + 15 * i + i * 2, 659, 15, 16, colors[WHITE]);
		}
	}
	if (id >= 2) {
		DrawRectangle(700, 635, 172, 20, colors[ORANGE_RED]);
		for (int i = 0; i < 10; i++) {
			if (i + 1 <= bots[1].getVehicle().getlife()) {
				DrawRectangle(702 + 15 * i + i * 2, 637, 15, 16, colors[WHITE]);
			}
		}
	}
	if (id == 3){
		DrawRectangle(880, 635, 172, 20, colors[ORANGE_RED]);
		for (int i = 0; i < 10; i++) {
			if (i + 1 <= bots[2].getVehicle().getlife()) {
				DrawRectangle(702 + 15 * i + i * 2, 637, 15, 16, colors[WHITE]);
			}
		}
	}

	DrawRectangle(159, 650, 172, 20, colors[ORANGE_RED]);
	for (int i = 0; i < 10; i++) {
		if (i + 1 <= play->getPlayer1().getVehicle().getlife() ) {
			DrawRectangle(161 + 15*i + i*2, 652, 15, 16, colors[WHITE]);
		}
	}
	
	// Drawing Information of Available Canons of Player 01
	DrawRoundRect(351,636,151,34,colors[DARK_GRAY]);
	for (int i = 0; i < 3; i++) {
		DrawRoundRect(351 + 45*i +(i + 1) * 4, 640, 45, 26, colors[ORANGE_RED]);
	}
	DrawString(351 + 4 + 2, 643, "S: ul", colors[WHITE]);
	DrawString(351 + 8 + 45 + 2, 643, "M: " + to_string(p1vehicle->getMediumCanon().getAvailableShells()), colors[WHITE]);
	DrawString(351 + 12 + 90 + 2, 643, "L: " + to_string(p1vehicle->getLargeCanon().getAvailableShells()), colors[WHITE]);
	
	// Collecting Information of Bots
	
	int medShells = 0, lrgShells = 0;
	if (id >= 1) { 
		medShells += bots[0].getVehicle().getMediumCanon().getAvailableShells(); 
		lrgShells += bots[0].getVehicle().getLargeCanon().getAvailableShells();
	}
	else if (id >= 2) { 
		medShells += bots[1].getVehicle().getMediumCanon().getAvailableShells();
		lrgShells+= bots[1].getVehicle().getLargeCanon().getAvailableShells();
	}
	else if (id >= 3) { 
		medShells += bots[2].getVehicle().getMediumCanon().getAvailableShells(); 
		lrgShells += bots[2].getVehicle().getLargeCanon().getAvailableShells();
	}
	// Drawing Information of Available Canons of Bots
	DrawRoundRect(535, 636, 151, 34, colors[DARK_GRAY]);
	for (int i = 0; i < 3; i++) {
		DrawRoundRect(535 + 45 * i + (i + 1) * 4, 640, 45, 26, colors[ORANGE_RED]);
	}
	DrawString(535 + 4 + 2, 643, "S: ul", colors[WHITE]);
	DrawString(535 + 8 + 45 + 2, 643, "M: " + to_string(medShells), colors[WHITE]);
	DrawString(535 + 12 + 90 + 2, 643, "L: " + to_string(lrgShells), colors[WHITE]);
	
	for (int i = 0; i < numberOfObstacles; i++) {
		obstacles[i].load();
	}
	/*glutSwapBuffers();*/
	//vehicle = tank;
	p1vehicle->load();
	if (id >= 1 && bots[0].getVehicle().getlife() > 0) {
		bots[0].getVehicle().load();
		bots[0].moveintelligently();
	}
	if (id >= 2 && bots[1].getVehicle().getlife() > 0) {
		bots[1].getVehicle().load();
		bots[1].moveintelligently();
	}
	if (id >= 3 && bots[2].getVehicle().getlife() > 0) {
		bots[2].getVehicle().load();
		bots[2].moveintelligently();
	}
	if (id >= 1 && bots[0].getVehicle().getlife() <= 0) {
		bots[0].getVehicle().getLocation().setX(-50);
		bots[0].getVehicle().getLocation().setY(50);
	}
	if (id >= 2 && bots[1].getVehicle().getlife() <= 0) {
		bots[1].getVehicle().getLocation().setX(-50);
		bots[1].getVehicle().getLocation().setY(50);
	}
	if (id >= 3 && bots[2].getVehicle().getlife() <= 0) {
		bots[2].getVehicle().getLocation().setX(-50);
		bots[2].getVehicle().getLocation().setY(50);
	}
}

Obstacle::Obstacle() {
	id = 0;
	location;
	type = "N/A";
	color = WHITE;
}

Obstacle::Obstacle(int id, float x, float y, string type, int color, int Width, int Height) {
	this->id = id;
	location.setX(x);
	location.setY(y);
	this->type = type;
	this->color = color;
	width = Width;
	height = Height;
}

void Obstacle::setLocation(float x, float y) {
	cout << "Set Location\n";
	location.setX(x);
	location.setY(y);
}

void Obstacle::load() {
	cout << "OBS LOad\n";
	DrawRectangle(location.getX(), location.getY(), width, height, colors[color]);
}

bool Obstacle::checkOverlaping(int x, int y, int w, int h) {
	/*int vehiclex = 0, vehicley = 0;
	if (play->getVehicle().getAlign() == "Up") {
		vehiclex = x;
		vehicley = y + h + 30;
	}
	if (play->getVehicle().getAlign() == "Down") {
		vehiclex = x;
		vehicley = y - 30;
	}

	if (play->getVehicle().getAlign() == "Left") {
		vehiclex = x - 30;
		vehicley = y;
	}

	if (play->getVehicle().getAlign() == "Right") {
		vehiclex = x + h + 30;
		vehicley = y;
	}

	if (!(vehiclex >= location.getX() && vehiclex <= location.getX() + width && vehicley >= location.getY() && vehicley <= location.getY() + height)) {
		return true;
	}
	return false;*/

	if ((x >= location.getX() && x <= location.getX() + getWidth() && y >= location.getY() && y <= location.getY() + getHeight()) || (x + w >= location.getX() && x + w <= location.getX() + getWidth() && y + h >= location.getY() && y + h <= location.getY() + getHeight())) {
		return false;
	}
	return true;

}

void Point::setX(float a) {
	x = a;
}

void Point::setY(float a) {
	y = a;
}

float Point::getX() { return x; }
float Point::getY() { return y; }

Vehicle::Vehicle() { // Default Constructor
	Canon c;
	type = "Null";
	movementSpeed = 0;
	smallCanon;
	mediumCanon;
	largeCanon;
	location.setX(35);
	location.setY(35);
	Align = "Up";
	player = "Player";
	smallCanon.setVehicle(this);
	mediumCanon.setVehicle(this);
	largeCanon.setVehicle(this);
	life = 10;
	limit = 0;
}

Vehicle::Vehicle(string Type, int speed, Canon& c1, Canon& c2, Canon& c3) {
	type = Type;
	movementSpeed = speed;
	smallCanon = c1;
	mediumCanon = c2;
	largeCanon = c3;
	location.setX(35);
	location.setY(35);
	Align = "Up";
	player = "Player";
	smallCanon.setVehicle(this);
	mediumCanon.setVehicle(this);
	largeCanon.setVehicle(this);
	life = 10;
	limit = 0;
}

void Vehicle::load() {
	// load the Vehicle as per alignment
	if (type == "Tank") {// for tank
		int tankWidth = 55, tankHeight = 100;
		if (Align == "Up") {// draw tank aligned upwards
			DrawRectangle(location.getX(), location.getY(), tankWidth, tankHeight - 30, colors[GREEN]);
			DrawCircle(location.getX() + tankWidth / 2, location.getY() + tankHeight - 50, 10, colors[DARK_GREEN]);
			DrawLine(location.getX() + tankWidth / 2, location.getY() + tankHeight - 43, location.getX() + tankWidth / 2, location.getY() + tankHeight, 5, colors[GREEN]);
		}

		else if (Align == "Down") {// draw tank aligned downwards
			DrawRectangle(location.getX(), location.getY() + 30, tankWidth, tankHeight - 30, colors[GREEN]);
			DrawCircle(location.getX() + tankWidth / 2, location.getY() + 50, 10, colors[DARK_GREEN]);
			DrawLine(location.getX() + tankWidth / 2, location.getY(), location.getX() + tankWidth / 2, location.getY() + 43, 5, colors[GREEN]);
		}

		else if (Align == "Left") {// draw tank aligned leftwards
			DrawRectangle(location.getX() + 30, location.getY(), tankHeight - 30, tankWidth, colors[GREEN]);
			DrawCircle(location.getX() + 50, location.getY() + tankWidth / 2, 10, colors[DARK_GREEN]);
			DrawLine(location.getX(), location.getY() + tankWidth / 2, location.getX() + 43, location.getY() + tankWidth / 2, 5, colors[GREEN]);
		}

		else if (Align == "Right") {// draw tank aligned rightwards
			DrawRectangle(location.getX(), location.getY(), tankHeight - 30, tankWidth, colors[GREEN]);
			DrawCircle(location.getX() + 50, location.getY() + tankWidth / 2, 10, colors[DARK_GREEN]);
			DrawLine(location.getX() + 57, location.getY() + tankWidth / 2, location.getX() + tankHeight, location.getY() + tankWidth / 2, 5, colors[GREEN]);
		}

		else if (Align == "TopRight") {
			DrawRectangle(location.getX(), location.getY(), tankWidth, tankHeight - 30, colors[GREEN]);
			DrawCircle(location.getX() + tankWidth / 2, location.getY() + tankHeight - 50, 10, colors[DARK_GREEN]);
			DrawLine(location.getX() + tankWidth / 2, location.getY() + tankHeight - 43, location.getX() + tankWidth, location.getY() + tankHeight, 5, colors[DARK_GREEN]);
		}

		else if (Align == "TopLeft") {
			DrawRectangle(location.getX(), location.getY(), tankWidth, tankHeight - 30, colors[GREEN]);
			DrawCircle(location.getX() + tankWidth / 2, location.getY() + tankHeight - 50, 10, colors[DARK_GREEN]);
			DrawLine(location.getX() + tankWidth / 2, location.getY() + tankHeight - 43, location.getX(), location.getY() + tankHeight, 5, colors[DARK_GREEN]);
		}

		else if (Align == "BottomLeft") {
			DrawRectangle(location.getX(), location.getY() + 30, tankWidth, tankHeight - 30, colors[GREEN]);
			DrawCircle(location.getX() + tankWidth / 2, location.getY() + 50, 10, colors[DARK_GREEN]);
			DrawLine(location.getX(), location.getY(), location.getX() + tankWidth / 2, location.getY() + 43, 5, colors[GREEN]);
		}

		else if (Align == "BottomRight") {
			DrawRectangle(location.getX(), location.getY() + 30, tankWidth, tankHeight - 30, colors[GREEN]);
			DrawCircle(location.getX() + tankWidth / 2, location.getY() + 50, 10, colors[DARK_GREEN]);
			DrawLine(location.getX()+tankWidth, location.getY(), location.getX() + tankWidth / 2, location.getY() + 43, 5, colors[GREEN]);
		}
	}
	else if (type == "Helicopter") {	// draws helicopter
		//int xI = 235, yI = 380, 
		int r = 15;
		if (Align == "Up" || Align == "TopLeft" || Align == "TopRight") {// draw helicopter aligned upwards
			DrawCircle(location.getX() + 30, location.getY() + 50 + r, r, colors[GREEN]);
			DrawRectangle(location.getX() + 30 - r, location.getY() + 25 + r, 2 * r, 30, colors[GREEN]);
			DrawTriangle(location.getX() + 30 - r, location.getY() + 25 + r, location.getX() + 30 + r, location.getY() + 25 + r, location.getX() + 30, location.getY() + 25, colors[GREEN]);
			DrawLine(location.getX() + 30, location.getY() + 25, location.getX() + 30, location.getY(), 5, colors[GREEN]);
			DrawLine(location.getX() + 20, location.getY() + 4, location.getX() + 40, location.getY() + 4, 4, colors[GREEN]);

			DrawLine(location.getX() + 30, location.getY() + 40 + r, location.getX() + 55, location.getY() + 40 + r, 4, colors[DARK_GREEN]);
			DrawLine(location.getX() + 30, location.getY() + 40 + r, location.getX() + 15, location.getY() + 66 + r, 4, colors[DARK_GREEN]);
			DrawLine(location.getX() + 30, location.getY() + 40 + r, location.getX() + 15, location.getY() + 14 + r, 4, colors[DARK_GREEN]);
		}
		else if (Align == "Down" || Align == "BottomLeft" || Align == "BottomRight") {// draw helicopter aligned downwards
			DrawCircle(location.getX() + 30, location.getY() + r, r, colors[GREEN]);
			DrawRectangle(location.getX() + 30 - r, location.getY() + r, 2 * r, 31, colors[GREEN]);
			DrawTriangle(location.getX() + 30 - r, location.getY() + 30 + r, location.getX() + 30 + r, location.getY() + 30 + r, location.getX() + 30, location.getY() + 30 + 2 * r, colors[GREEN]);
			DrawLine(location.getX() + 30, location.getY() + 30 + 2 * r, location.getX() + 30, location.getY() + 55 + 2 * r, 5, colors[GREEN]);
			DrawLine(location.getX() + 20, location.getY() + 51 + 2 * r, location.getX() + 40, location.getY() + 51 + 2 * r, 4, colors[GREEN]);

			DrawLine(location.getX() + 30, location.getY() + 15 + r, location.getX() + 55, location.getY() + 15 + r, 4, colors[DARK_GREEN]);
			DrawLine(location.getX() + 30, location.getY() + 15 + r, location.getX() + 15, location.getY() + 41 + r, 4, colors[DARK_GREEN]);
			DrawLine(location.getX() + 30, location.getY() + 15 + r, location.getX() + 15, location.getY() - 11 + r, 4, colors[DARK_GREEN]);
		}

		else if (Align == "Left") {// draw helicopter aligned leftwards
			DrawCircle(location.getX() + r, location.getY() + 30, r, colors[GREEN]);
			DrawRectangle(location.getX() + r, location.getY() + 30 - r, 31, 2 * r, colors[GREEN]);
			DrawTriangle(location.getX() + r + 30, location.getY() + 30 - r, location.getX() + r + 30, location.getY() + 30 + r, location.getX() + 30 + 2 * r, location.getY() + 30, colors[GREEN]);
			DrawLine(location.getX() + 30 + 2 * r, location.getY() + 30, location.getX() + 55 + 2 * r, location.getY() + 30, 5, colors[GREEN]);
			DrawLine(location.getX() + 51 + 2 * r, location.getY() + 20, location.getX() + 51 + 2 * r, location.getY() + 40, 4, colors[GREEN]);

			DrawLine(location.getX() + 15 + r, location.getY() + 30, location.getX() + 15 + r, location.getY() + 55, 4, colors[DARK_GREEN]);
			DrawLine(location.getX() + 15 + r, location.getY() + 30, location.getX() + 41 + r, location.getY() + 15, 4, colors[DARK_GREEN]);
			DrawLine(location.getX() + 15 + r, location.getY() + 30, location.getX() - 11 + r, location.getY() + 15, 4, colors[DARK_GREEN]);
		}

		else if (Align == "Right") {// draw helicopter aligned rightwards
			DrawCircle(location.getX() + 55 + r, location.getY() + 30, r, colors[GREEN]);
			DrawRectangle(location.getX() + 25 + r, location.getY() + 30 - r, 31, 2 * r, colors[GREEN]);
			DrawTriangle(location.getX() + r + 25, location.getY() + 30 - r, location.getX() + r + 25, location.getY() + 30 + r, location.getX() + 25, location.getY() + 30, colors[GREEN]);
			DrawLine(location.getX() + 25, location.getY() + 30, location.getX(), location.getY() + 30, 5, colors[GREEN]);
			DrawLine(location.getX() + 4, location.getY() + 20, location.getX() + 4, location.getY() + 40, 4, colors[GREEN]);

			DrawLine(location.getX() + 40 + r, location.getY() + 30, location.getX() + 40 + r, location.getY() + 55, 4, colors[DARK_GREEN]);
			DrawLine(location.getX() + 40 + r, location.getY() + 30, location.getX() + 66 + r, location.getY() + 15, 4, colors[DARK_GREEN]);
			DrawLine(location.getX() + 40 + r, location.getY() + 30, location.getX() + 14 + r, location.getY() + 15, 4, colors[DARK_GREEN]);

		}

	}

	else if (type == "Plane") {

		static int width = 12;
		if (Align == "Up" || Align=="TopLeft" || Align=="TopRight") {
			DrawTriangle(location.getX() + 2.5 * width, location.getY(), location.getX() + 2 * width, location.getY() + width, location.getX() + width * 3, location.getY() + width, colors[GREEN]);
			DrawRectangle(location.getX() + 2 * width, location.getY() + width, width, 56, colors[GREEN]);
			DrawTriangle(location.getX() + 2 * width, location.getY() + 55 + width, location.getX() + 3 * width, location.getY() + 55 + width, location.getX() + 2.5 * width, location.getY() + 55 + 2 * width, colors[GREEN]);
			DrawTriangle(location.getX(), location.getY() + 30 + width, location.getX() + width * 2, location.getY() + 30 + width, location.getX() + width * 2, location.getY() + 37 + width, colors[GREEN]);
			DrawTriangle(location.getX() + 3 * width, location.getY() + 30 + width, location.getX() + width * 5, location.getY() + 30 + width, location.getX() + width * 3, location.getY() + 37 + width, colors[GREEN]);
			DrawTriangle(location.getX() + 3 * width, location.getY() + width, location.getX() + 3.5 * width, location.getY() + width, location.getX() + 3 * width, location.getY() + 5 + width, colors[GREEN]);
			DrawTriangle(location.getX() + 1.5 * width, location.getY() + width, location.getX() + 2 * width, location.getY() + width, location.getX() + 2 * width, location.getY() + 5 + width, colors[GREEN]);
		}

		else if (Align == "Down" || Align == "BottomLeft" || Align == "BottomRight") {
			DrawTriangle(location.getX() + 2.5 * width, location.getY(), location.getX() + 2 * width, location.getY() + width, location.getX() + width * 3, location.getY() + width, colors[GREEN]);
			DrawRectangle(location.getX() + 2 * width, location.getY() + width, width, 56, colors[GREEN]);
			DrawTriangle(location.getX() + 2 * width, location.getY() + 55 + width, location.getX() + 3 * width, location.getY() + 55 + width, location.getX() + 2.5 * width, location.getY() + 55 + 2 * width, colors[GREEN]);
			DrawTriangle(location.getX(), location.getY() + 25 + width, location.getX() + width * 2, location.getY() + 25 + width, location.getX() + width * 2, location.getY() + 18 + width, colors[GREEN]);
			DrawTriangle(location.getX() + 3 * width, location.getY() + 25 + width, location.getX() + width * 5, location.getY() + 25 + width, location.getX() + width * 3, location.getY() + 18 + width, colors[GREEN]);
			DrawTriangle(location.getX() + 3 * width, location.getY() + 55 + width, location.getX() + 3.5 * width, location.getY() + 55 + width, location.getX() + 3 * width, location.getY() + 50 + width, colors[GREEN]);
			DrawTriangle(location.getX() + 1.5 * width, location.getY() + 55 + width, location.getX() + 2 * width, location.getY() + 55 + width, location.getX() + 2 * width, location.getY() + 50 + width, colors[GREEN]);
		}

		else if (Align == "Left") {
			DrawTriangle(location.getX(), location.getY() + 2.5 * width, location.getX() + width, location.getY() + 2 * width, location.getX() + width, location.getY() + 3 * width, colors[GREEN]);
			DrawRectangle(location.getX() + width, location.getY() + 2 * width, 56, width, colors[GREEN]);
			DrawTriangle(location.getX() + 55 + width, location.getY() + 2 * width, location.getX() + width + 55, location.getY() + 3 * width, location.getX() + 2 * width + 55, location.getY() + 2.5 * width, colors[GREEN]);
			DrawTriangle(location.getX() + width + 18, location.getY() + 2 * width, location.getX() + width + 25, location.getY() + 2 * width, location.getX() + width + 25, location.getY(), colors[GREEN]);
			DrawTriangle(location.getX() + width + 18, location.getY() + 3 * width, location.getX() + width + 25, location.getY() + 3 * width, location.getX() + width + 25, location.getY() + 5 * width, colors[GREEN]);
			DrawTriangle(location.getX() + width + 55, location.getY() + 2 * width, location.getX() + 51 + width, location.getY() + 2 * width, location.getX() + 55 + width, location.getY() + 1.5 * width, colors[GREEN]);
			DrawTriangle(location.getX() + width + 55, location.getY() + 3 * width, location.getX() + 51 + width, location.getY() + 3 * width, location.getX() + 55 + width, location.getY() + 3.5 * width, colors[GREEN]);

		}

		else if (Align == "Right") {
			DrawTriangle(location.getX(), location.getY() + 2.5 * width, location.getX() + width, location.getY() + 2 * width, location.getX() + width, location.getY() + 3 * width, colors[GREEN]);
			DrawRectangle(location.getX() + width, location.getY() + 2 * width, 56, width, colors[GREEN]);
			DrawTriangle(location.getX() + 55 + width, location.getY() + 2 * width, location.getX() + width + 55, location.getY() + 3 * width, location.getX() + 2 * width + 55, location.getY() + 2.5 * width, colors[GREEN]);

			DrawTriangle(location.getX() + width + 37, location.getY() + 2 * width, location.getX() + width + 30, location.getY() + 2 * width, location.getX() + width + 30, location.getY(), colors[GREEN]);
			DrawTriangle(location.getX() + width + 37, location.getY() + 3 * width, location.getX() + width + 30, location.getY() + 3 * width, location.getX() + width + 30, location.getY() + 5 * width, colors[GREEN]);
			DrawTriangle(location.getX() + width, location.getY() + 2 * width, location.getX() + 4 + width, location.getY() + 2 * width, location.getX() + width, location.getY() + 1.5 * width, colors[GREEN]);
			DrawTriangle(location.getX() + width, location.getY() + 3 * width, location.getX() + 4 + width, location.getY() + 3 * width, location.getX() + width, location.getY() + 3.5 * width, colors[GREEN]);

		}
	}
	if (limit > 0) {	// when booster deactivate decrease speed
		limit--;
		if (limit == 0) { movementSpeed /= 2; } // decrease speed which was doubled by booster
	}
	glutPostRedisplay();
}

void Vehicle::moveup() {
	Obstacle* ptr;
	int num = 6;
	if (play->getLevel1().isPassed() == false) {
		ptr = play->getLevel1().getobstacles();
		num = 6;
	}
	else if (play->getLevel1().isPassed() == true && play->getLevel2().isPassed() == false) {
		ptr = play->getLevel2().getobstacles();
		num = 8;
	}
	else {
		ptr = play->getLevel3().getobstacles();
		num = 10;
	}

	//int w = 55, h = 70;
	bool flag = true;
	/*int x = location.getX();
	int y = location.getY();*/
	//cout << "X : " << x << " Y: " << y << endl;
	//if (type == "Tank") { w = 5; h = 70; }		// only Tank
	int count = 1;
	for (int i = 0; i < num; i++) {
	recheck:
		if (ptr[i].checkOverlaping(location.getX(), location.getY(), getWidth(), getHeight()) == false) {

			//if Vehicles is Stuck at one place then do something
			if (Align == "Left") { location.setX(location.getX() + 5); }
			if (Align == "Right") { location.setX(location.getX() - 5); }
			if (Align == "Down" || Align == "BottomLeft" || Align == "BottomRight") { location.setY(location.getY() + 5); }
			if (count > 0) {
				count--;
				goto recheck;
			}
			flag = false;
			break;
		}
	}
	if (flag) {
		if (Align == "Up" && location.getY() + getHeight() > 630) {
			location.setY(location.getY() + movementSpeed - 630);
		}
		else {
			location.setY(location.getY() + movementSpeed);
		}
		Align = "Up";
	}
	if (flag == false && player == "Bot") {
		if (play->getPlayer1().getVehicle().getLocation().getX() > location.getX()) {
			location.setX(location.getX() - movementSpeed);
			Align = "Left";
		}
		if (play->getPlayer1().getVehicle().getLocation().getX() < location.getX()) {
			location.setX(location.getX() + movementSpeed);
			Align = "Right";
		}
	}
	//cout << "X : " << x << " Y: " << y << endl;
}

void Vehicle::movedown() {
	Obstacle* ptr;
	int num;
	if (play->getLevel1().isPassed() == false) {
		ptr = play->getLevel1().getobstacles();
		num = 6;
	}
	else if (play->getLevel1().isPassed() == true && play->getLevel2().isPassed() == false) {
		ptr = play->getLevel2().getobstacles();
		num = 8;
	}
	else {
		ptr = play->getLevel3().getobstacles();
		num = 10;
	}
	bool flag = true;
	/*int x = location.getX();
	int y = location.getY();*/
	//cout << "X : " << x << " Y: " << y << endl;
	//if (type == "Tank") { w = 55; h = 70; }		// only Tank
	int count = 1;
	for (int i = 0; i < num; i++) {
	recheck:
		if (ptr[i].checkOverlaping(location.getX(), location.getY(), getWidth(), getHeight()) == false) {
			if (Align == "Left") { location.setX(location.getX() + 5); }
			if (Align == "Right") { location.setX(location.getX() - 5); }
			if (Align == "Up" || Align == "TopLeft" || Align == "TopRight") { location.setY(location.getY() - 5); }
			if (count > 0) {
				count--;
				goto recheck;
			}
			flag = false;
			break;
		}
	}
	if (flag) {
		cout << "Not Entered\n";
		if (Align == "Down" && location.getY() + getHeight() < 0) {
			location.setY(location.getY() - movementSpeed + 560);
		}
		else {
			location.setY(location.getY() - movementSpeed);
		}
		Align = "Down";
	}
	if (flag == false && player == "Bot") {
		cout << "Entered\n";
		if (play->getVehicle().getLocation().getX() > location.getX()) {
			location.setX(location.getX() - movementSpeed);
			Align = "Left";
		}
		if (play->getVehicle().getLocation().getX() < location.getX()) {
			location.setX(location.getX() + movementSpeed);
			Align = "Right";
		}
	}
	//cout << "X : " << x << " Y: " << y << endl;
}

void Vehicle::moveleft() {
	Obstacle* ptr;
	int num;
	if (play->getLevel1().isPassed() == false) {
		ptr = play->getLevel1().getobstacles();
		num = 6;
	}
	else if (play->getLevel1().isPassed() == true && play->getLevel2().isPassed() == false) {
		ptr = play->getLevel2().getobstacles();
		num = 8;
	}
	else {
		ptr = play->getLevel3().getobstacles();
		num = 10;
	}
	/*
	int w = 70, h = 55;*/
	bool flag = true;
	//int x = location.getX();
	//int y = location.getY();
	//cout << "X : " << x << " Y: " << y << endl;
	//if (type == "Tank") { w = 70; h = 55; }		// only Tank
	int count = 1;
	for (int i = 0; i < num; i++) {
	recheck:
		if (ptr[i].checkOverlaping(location.getX(), location.getY(), getHeight(), getWidth()) == false) {
			if (Align == "Down" || Align == "BottomLeft" || Align == "BottomRight") { location.setY(location.getY() + 5); }
			if (Align == "Up" || Align == "TopLeft" || Align == "TopRight") { location.setY(location.getY() - 5); }
			if (Align == "Right") { location.setX(location.getX() - 5); }
			if (count > 0) {
				count--;
				goto recheck;
			}
			flag = false;
			break;
		}
	}
	if (flag) {
		if (Align == "Left" && location.getX() < 0) {
			location.setX(location.getX() - movementSpeed + 1080);
		}
		else {
			location.setX(location.getX() - movementSpeed);
		}
		Align = "Left";
	}
	if (flag == false && player == "Bot") {
		if (play->getVehicle().getLocation().getY() < location.getY()) {
			location.setY(location.getY() + movementSpeed);
			Align = "Up";
		}
		if (play->getVehicle().getLocation().getY() > location.getY()) {
			location.setY(location.getY() - movementSpeed);
			Align = "Down";
		}
	}
	//cout << "X : " << x << " Y: " << y << endl;
}

void Vehicle::moveright() {
	Obstacle* ptr;
	int num;
	if (play->getLevel1().isPassed() == false) {
		ptr = play->getLevel1().getobstacles();
		num = 6;
	}
	else if (play->getLevel1().isPassed() == true && play->getLevel2().isPassed() == false) {
		ptr = play->getLevel2().getobstacles();
		num = 8;
	}
	else {
		ptr = play->getLevel3().getobstacles();
		num = 10;
	}
	/*int w = 70, h = 55;*/
	bool flag = true;
	//int x = location.getX();
	//int y = location.getY();
	//cout << "X : " << x << " Y: " << y << endl;
	//if (type == "Tank") { w = 70; h = 55; }		// only Tank
	int count = 1;
	for (int i = 0; i < num; i++) {
	recheck:
		if (ptr[i].checkOverlaping(location.getX(), location.getY(), getHeight(), getWidth()) == false) {
			if (Align == "Left") { location.setX(location.getX() + 5); }
			if (Align == "Down" || Align == "BottomLeft" || Align == "BottomRight") { location.setY(location.getY() + 5); }
			if (Align == "Up" || Align == "TopLeft" || Align == "TopRight") { location.setY(location.getY() - 5); }
			if (count > 0) {
				count--;
				goto recheck;
			}
			flag = false;
			break;
		}
	}
	if (flag) {
		if (Align == "Right" && location.getX() + getWidth() > 1080) {
			location.setX(location.getX() + movementSpeed - 1080);
		}
		else {
			location.setX(location.getX() + movementSpeed);
		}
		Align = "Right";
	}
	if (flag == false && player == "Bot") {
		if (play->getVehicle().getLocation().getY() < location.getY()) {
			location.setY(location.getY() + movementSpeed);
			Align = "Up";
		}
		if (play->getVehicle().getLocation().getY() > location.getY()) {
			location.setY(location.getY() - movementSpeed);
			Align = "Down";
		}
	}
	//cout << "X : " << x << " Y: " << y << endl;
}

Vehicle::Vehicle(Vehicle& v) {
	type = v.type;
	movementSpeed = v.movementSpeed;
	smallCanon = v.smallCanon;
	mediumCanon = v.mediumCanon;
	largeCanon = v.largeCanon;
	location.setX(v.location.getX());
	location.setY(v.location.getY());
	Align = "Up";
	player = v.player;
	life = v.life;
}

void Vehicle::initialize() {
	smallCanon.setVehicle(this);
	mediumCanon.setVehicle(this);
	largeCanon.setVehicle(this);
}

void Vehicle::increaseTemporarySpeed() {
	movementSpeed *= 2;
	limit += 400;
}

Canon::Canon() {
	damage = 0;
	size = 0;
	noOfShellAvailable = 0;
	speed = 0;
	location.setX(0);
	location.setY(0);
	shooted = false;
	direction = "Up";
	strike = 0;
	vehicle;
}

Canon::Canon(int dam, int Size, int shells, int Speed) {
	damage = dam;
	size = Size;
	noOfShellAvailable = shells;
	speed = Speed;
	location.setX(0);
	location.setY(0);
	shooted = false;
	direction = "Up";
	strike = 0;
	vehicle;
}

void Canon::shoot(Vehicle& v) {
	if (noOfShellAvailable > 0 && !shooted) {
		if (gameG->getsetting().getGameSound()) {
			//mciSendString(TEXT("Fire.wav"), NULL, 0, NULL);
			//PlaySound(TEXT("Fire.wav"), NULL, SND_ASYNC);
		}
		int x = v.getLocation().getX();
		int y = v.getLocation().getY();
		if (v.getAlign() == "Up") {
			x = x + v.getWidth() / 2;
			y = y + v.getHeight();
			location.setX(x);
			location.setY(y);
			direction = "Up";
			shooted = true;
			noOfShellAvailable--;
		}

		if (v.getAlign() == "Down") {
			x = x + v.getWidth() / 2;
			y = y;
			location.setX(x);
			location.setY(y);
			direction = "Down";
			shooted = true;
			noOfShellAvailable--;
		}

		if (v.getAlign() == "Left") {
			x = x;
			y = y + v.getWidth() / 2;
			location.setX(x);
			location.setY(y);
			direction = "Left";
			shooted = true;
			noOfShellAvailable--;
		}

		if (v.getAlign() == "Right") {
			x = x + v.getHeight();
			y = y + v.getWidth() / 2;
			location.setX(x);
			location.setY(y);
			direction = "Right";
			shooted = true;
			noOfShellAvailable--;
		}

		if (v.getAlign() == "TopLeft") {
			x = x;
			y = y + v.getHeight();
			location.setX(x);
			location.setY(y);
			direction = "TopLeft";
			shooted = true;
			noOfShellAvailable--;
		}

		if (v.getAlign() == "TopRight") {
			x = x + v.getWidth();
			y = y + v.getHeight();
			location.setX(x);
			location.setY(y);
			direction = "TopRight";
			shooted = true;
			noOfShellAvailable--;
		}

		if (v.getAlign() == "BottomLeft") {
			x = x;
			y = y;
			location.setX(x);
			location.setY(y);
			direction = "BottomLeft";
			shooted = true;
			noOfShellAvailable--;
		}

		if (v.getAlign() == "BottomRight") {
			x = x + v.getWidth();
			y = y;
			location.setX(x);
			location.setY(y);
			direction = "BottomRight";
			shooted = true;
			noOfShellAvailable--;
		}
	}


	/*cout << "The Vehicle X : " << vehicle->getLocation().getX();
	cout << " and Y: " << vehicle->getLocation().getY() << endl;*/
}

void Canon::bounce() {
	DrawCircle(location.getX(), location.getY(), size, colors[WHITE]);
	if (strike == 3) {
		strike = 0;
		shooted = false;
		return;
	}
	if (direction == "Up") { location.setY(location.getY() + speed); }
	if (direction == "Down") { location.setY(location.getY() - speed); }
	if (direction == "Left") { location.setX(location.getX() - speed); }
	if (direction == "Right") { location.setX(location.getX() + speed); }
	if (direction == "TopLeft") { 
		location.setX(location.getX() - cos(Deg2Rad(45))*speed);
		location.setY(location.getY() + sin(Deg2Rad(45))*speed);

	}
	if (direction == "TopRight") { 
		location.setX(location.getX() + cos(Deg2Rad(45))*speed);
		location.setY(location.getY() + sin(Deg2Rad(45)) * speed);
	}
	if (direction == "BottomLeft") { 
		location.setX(location.getX() - cos(Deg2Rad(45))*speed);
		location.setY(location.getY() - sin(Deg2Rad(45)) * speed);
	}
	if (direction == "BottomRight") { 
		location.setX(location.getX() + cos(Deg2Rad(45))*speed); 
		location.setY(location.getY() - sin(Deg2Rad(45)) * speed);
	}

	static Obstacle* obs;
	static Level* lvl;
	static int size = 0;
	if (play->getLevel1().isPassed() == false) {
		obs = play->getLevel1().getobstacles();
		lvl = &(play->getLevel1());
		size = 6;
	}

	else if (play->getLevel2().isPassed() == false && play->getLevel1().isPassed() == true) {
		obs = play->getLevel2().getobstacles();
		lvl = &(play->getLevel2());
		size = 8;
	}

	else if (play->getLevel3().isPassed() == false && play->getLevel2().isPassed() == true) {
		obs = play->getLevel3().getobstacles();
		lvl = &(play->getLevel3());
		size = 10;
	}

	Bot* bots = nullptr;
	int numBots;
	if (play->getType() == 1 && play->getLevel1().isPassed() == false) { bots = play->getLevel1().getBot(); numBots = 1; }
	else if (play->getType() == 1 && play->getLevel1().isPassed() == true && play->getLevel2().isPassed() == false) { bots = play->getLevel2().getBot(); numBots = 2; }
	else if (play->getType() == 1 && play->getLevel2().isPassed() == true && play->getLevel3().isPassed() == false) { bots = play->getLevel3().getBot(); numBots = 3; }

	if (location.getX() >= 1050 && (direction=="TopRight"||direction=="BottomRight")) { 
		if (direction == "TopRight") {
			direction = "TopLeft"; 
		}
		else {
			direction = "BottomLeft";
		}
		strike++;
	}
	else if (location.getX() <= 30 && (direction == "TopLeft" || direction == "BottomLeft")) {
		if (direction == "TopLeft") {
			direction = "TopRight"; 
		}
		else {
			direction = "BottomRight";
		}
		strike++;
	}
	else if (location.getY() >= 600 && (direction == "TopLeft" || direction == "TopRight")) {
		if (direction == "TopLeft") {
			direction = "BottomLeft"; 
		}
		else {
			direction = "BottomRight";
		}
		strike++;
	}
	else if (location.getY() <= 30 && (direction == "BottomLeft" || direction == "BottomRight")) {
		if (direction == "BottomLeft") {
			direction = "TopLeft"; 
		}
		else {
			direction = "TopRight";
		}
		strike++;
	}

	else if (location.getX() >= 1050) { direction = "Left"; strike++; }
	else if (location.getX() <= 30) { direction = "Right"; strike++; }
	else if (location.getY() >= 600) { direction = "Down"; strike++; }
	else if (location.getY() <= 30) { direction = "Up"; strike++; }
	else if (location.getX() >= lvl->getPlayer1Vehicle().getLocation().getX() && location.getX() <= lvl->getPlayer1Vehicle().getLocation().getX() + lvl->getPlayer1Vehicle().getWidth() && location.getY() >= lvl->getPlayer1Vehicle().getLocation().getY() && location.getY() <= lvl->getPlayer1Vehicle().getLocation().getY() + lvl->getPlayer1Vehicle().getHeight()) {
		strike = 3;
		lvl->getPlayer1Vehicle().decreaseLife(damage);
		if (play->getType() == 2) {
			play->getPlayer2().setScore(play->getPlayer2().getScore() + damage);
		}
		else {
			bots[0].setScore(bots[0].getScore() + damage);
		}
	}

	else if (location.getX() >= lvl->getPlayer2Vehicle().getLocation().getX() && location.getX() <= lvl->getPlayer2Vehicle().getLocation().getX() + lvl->getPlayer2Vehicle().getWidth() && location.getY() >= lvl->getPlayer2Vehicle().getLocation().getY() && location.getY() <= lvl->getPlayer2Vehicle().getLocation().getY() + lvl->getPlayer2Vehicle().getHeight()) {
		strike = 3;
		lvl->getPlayer2Vehicle().decreaseLife(damage);
		if (play->getType() == 2) {
			play->getPlayer1().setScore(play->getPlayer1().getScore() + damage);
		}
	}

	else if (play->getType() == 1 && location.getX() >= bots[0].getVehicle().getLocation().getX() && location.getX() <= bots[0].getVehicle().getLocation().getX() + bots[0].getVehicle().getWidth() && location.getY() >= bots[0].getVehicle().getLocation().getY() && location.getY() <= bots[0].getVehicle().getLocation().getY() + bots[0].getVehicle().getHeight()) {
		strike = 3;
		bots[0].getVehicle().decreaseLife(damage);
		play->getPlayer1().setScore(play->getPlayer1().getScore() + damage);
	}

	else if (play->getType() == 1 && play->getLevel1().isPassed() == true && location.getX() >= bots[1].getVehicle().getLocation().getX() && location.getX() <= bots[1].getVehicle().getLocation().getX() + bots[1].getVehicle().getWidth() && location.getY() >= bots[1].getVehicle().getLocation().getY() && location.getY() <= bots[1].getVehicle().getLocation().getY() + bots[1].getVehicle().getHeight()) {
		strike = 3;
		bots[1].getVehicle().decreaseLife(damage);
		play->getPlayer1().setScore(play->getPlayer1().getScore() + damage);
	}

	else if (play->getType() == 1 && play->getLevel2().isPassed() == true && location.getX() >= bots[2].getVehicle().getLocation().getX() && location.getX() <= bots[2].getVehicle().getLocation().getX() + bots[2].getVehicle().getWidth() && location.getY() >= bots[2].getVehicle().getLocation().getY() && location.getY() <= bots[2].getVehicle().getLocation().getY() + bots[2].getVehicle().getHeight()) {
		strike = 3;
		bots[2].getVehicle().decreaseLife(damage);
		play->getPlayer1().setScore(play->getPlayer1().getScore() + damage);
	}

	else {
		static int x, y, h, w;
		for (int i = 0; i < size; i++) {
			x = obs[i].getLocation().getX();
			y = obs[i].getLocation().getY();
			h = obs[i].getHeight();
			w = obs[i].getWidth();
			if (location.getX() >= x && location.getX() <= x + w && location.getY() >= y && location.getY() <= y + h) {
				
				if (direction == "TopRight" && location.getY() >= y) { direction = "BottomRight"; strike++; }
				else if (direction == "TopLeft" && location.getY() >= y) { direction = "BottomLeft"; strike++; }
				else if (direction == "BottomRight" && location.getY() <= y+w) { direction = "TopRight"; strike++; }
				else if (direction == "BottomLeft" && location.getY() <= y+w) { direction = "TopLeft"; strike++; }
				else if (direction == "TopRight") { direction = "TopLeft"; strike++; }
				else if (direction == "TopLeft") { direction = "TopRight"; strike++; }
				else if (direction == "BottomLeft") { direction = "BottomRight"; strike++; }
				else if (direction == "BottomRight") { direction = "BottomLeft"; strike++; }
				
				
				else if (direction == "Right") { direction = "Left"; strike++; }
				else if (direction == "Left") { direction = "Right"; strike++; }
				else if (direction == "Up") { direction = "Down"; strike++; }
				else if (direction == "Down") { direction = "Up"; strike++; }
			}
		}
	}
}

Bot::Bot():Player(tank) {
	intelligence = 0;
	path = nullptr;
}

void Bot::findpath() {
	int playerx = play->getVehicle().getLocation().getX();
	int playery = play->getVehicle().getLocation().getY();

}

void Bot::moveintelligently() {
	cout << "Move Intelligently\n";
	static short count = 0;
	int playerx = play->getPlayer1().getVehicle().getLocation().getX();
	int playery = play->getPlayer1().getVehicle().getLocation().getY();
	
	if ((playerVehicle.getLocation().getX() == playerx || playerVehicle.getLocation().getY() == playery) && ((intelligence == 1 && count == 0) || (intelligence == 2 && count % 2 == 0) || (intelligence == 3))) {
		if (playerVehicle.getShortCanon().isShooted() == false ) {
			AlignCanon();
			playerVehicle.getShortCanon().shoot(playerVehicle);
		}
		else if (playerVehicle.getMediumCanon().isShooted() == false && playerVehicle.getMediumCanon().getAvailableShells() > 0) {
			AlignCanon();
			playerVehicle.getMediumCanon().shoot(playerVehicle);
		}
		else if (playerVehicle.getLargeCanon().isShooted() == false && playerVehicle.getLargeCanon().getAvailableShells() > 0) {
			AlignCanon();
			playerVehicle.getLargeCanon().shoot(playerVehicle);
		}
		count++;
	}
	else if (playerVehicle.getLocation().getX() == playerx || playerVehicle.getLocation().getY() == playery) {
		AlignCanon();
		//playerVehicle.setAlign(play->getPlayer1().getVehicle().getAlign());
		/*layerVehicle.setAlign("Right");
		playerVehicle.setAlign("Left");
		playerVehicle.setAlign("Up");
		playerVehicle.setAlign("Down");*/
		count++;
	}
	
	else {
		if (playerVehicle.getLocation().getX() < playerx) {
			playerVehicle.moveright();
		}
		if (playerVehicle.getLocation().getX() > playerx) {
			playerVehicle.moveleft();
		}
		if (playerVehicle.getLocation().getY() < playery) {
			playerVehicle.moveup();
		}
		if (playerVehicle.getLocation().getY() > playery) {
			playerVehicle.movedown();
		}
	}
	if (playerVehicle.getShortCanon().isShooted() == true) {
		playerVehicle.getShortCanon().bounce();
	}
	if (playerVehicle.getMediumCanon().isShooted() == true) {
		playerVehicle.getMediumCanon().bounce();
	}
	if (playerVehicle.getLargeCanon().isShooted() == true) {
		playerVehicle.getLargeCanon().bounce();
	}
	if (count == 4) {
		count = 0;
	}
}

void Bot::AlignCanon() {
	cout << "Align Canon\n";
	int playerx = play->getPlayer1().getVehicle().getLocation().getX();
	int playery = play->getPlayer1().getVehicle().getLocation().getY();
	/*if (playerVehicle.getType() == "Helicopter") {
		playerVehicle.getLocation().setY(playerVehicle.getLocation().getY() + 5);
	}*/


	if (playerVehicle.getLocation().getX() < playerx) {
		playerVehicle.moveright();
		//playerVehicle.setAlign("Right");
	}
	else if (playerVehicle.getLocation().getX() > playerx) {
		playerVehicle.moveleft();
		//playerVehicle.setAlign("Left");
	}
	else if (playerVehicle.getLocation().getY() < playery) {
		playerVehicle.moveup();
		//playerVehicle.setAlign("Up");
	}
	else if (playerVehicle.getLocation().getY() > playery) {
		playerVehicle.movedown();	
		//playerVehicle.setAlign("Down");
	}
}

void Bot::AssignVehicle() {
	cout << "Assign Vehicle\n";
	playerVehicle = tank;
	playerVehicle.getLocation().setX(720);
	playerVehicle.getLocation().setY(500);
	playerVehicle.setPlayer("Bot");
}

void Setting::showVehicleSetting() {
	DrawString(450, 670, "VEHICLE SETTINGS", colors[ORANGE_RED]);
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);
	DrawString(55, 660, "back", colors[ORANGE_RED]);

	// Inner Rectangle
	DrawRoundRect(100, 50, 880, 600, colors[ORANGE_RED]);

	// Player 1 Rectangle
	DrawRoundRect(150, 100, 365, 500, colors[WHITE]);
	DrawString(275, 550, "PLAYER 01", colors[ORANGE_RED]);
	// Player 2 Rectangle
	DrawRoundRect(565, 100, 365, 500, colors[WHITE]);
	DrawString(690, 550, "PLAYER 02", colors[ORANGE_RED]);

	// Inner Buttons
	if (play->getPlayer1().getVehicle().getType() == "Tank") {
		DrawRoundRect(192.5, 435, 280, 110, colors[DARK_GRAY]);
		DrawRoundRect(192.5, 295, 280, 110, colors[ORANGE_RED]);
		DrawRoundRect(192.5, 155, 280, 110, colors[ORANGE_RED]);
	}
	if (play->getPlayer1().getVehicle().getType() == "Helicopter") {
		DrawRoundRect(192.5, 295, 280, 110, colors[DARK_GRAY]);
		DrawRoundRect(192.5, 435, 280, 110, colors[ORANGE_RED]);
		DrawRoundRect(192.5, 155, 280, 110, colors[ORANGE_RED]);
	}
	if (play->getPlayer1().getVehicle().getType() == "Plane") {
		DrawRoundRect(192.5, 435, 280, 110, colors[ORANGE_RED]);
		DrawRoundRect(192.5, 155, 280, 110, colors[DARK_GRAY]);
		DrawRoundRect(192.5, 295, 280, 110, colors[ORANGE_RED]);
	}
	
	if (play->getPlayer2().getVehicle().getType() == "Tank") {
		DrawRoundRect(607.5, 435, 280, 110, colors[DARK_GRAY]);
		DrawRoundRect(607.5, 295, 280, 110, colors[ORANGE_RED]);
		DrawRoundRect(607.5, 155, 280, 110, colors[ORANGE_RED]);
	}
	if (play->getPlayer2().getVehicle().getType() == "Helicopter") {
		DrawRoundRect(607.5, 435, 280, 110, colors[ORANGE_RED]);
		DrawRoundRect(607.5, 295, 280, 110, colors[DARK_GRAY]);
		DrawRoundRect(607.5, 155, 280, 110, colors[ORANGE_RED]);
	}
	if (play->getPlayer2().getVehicle().getType() == "Plane") {
		DrawRoundRect(607.5, 155, 280, 110, colors[DARK_GRAY]);
		DrawRoundRect(607.5, 435, 280, 110, colors[ORANGE_RED]);
		DrawRoundRect(607.5, 295, 280, 110, colors[ORANGE_RED]);
	}

	// Draw Tank
	int xI = 205, yI = 440, width = 55, height = 70, r = 10;

	for (int i = 0; i < 2; i++) {
		DrawRectangle(xI, yI, width, height, colors[GREEN]);
		DrawCircle(xI + width / 2, yI + height - 20, r, colors[DARK_GREEN]);
		DrawLine(xI + width / 2, yI + height - 13, xI + width / 2, yI + height + 30, 5, colors[GREEN]);
		xI = 620;
	}
	
	// Draw Helicopter
	xI = 235, yI = 380, r = 15;
	for (int i = 0; i < 2; i++) {
		DrawCircle(xI, yI, r, colors[GREEN]);
		DrawRectangle(xI - r, yI - 30, 30, 30, colors[GREEN]);
		DrawTriangle(xI - r, yI - 30, xI + r, yI - 30, xI, yI - 30 - r, colors[GREEN]);
		DrawLine(xI, yI - r - 30, xI, yI - r - 65, 5, colors[GREEN]);
		DrawLine(xI - 10, yI - r - 61, xI + 10, yI - r - 61, 4, colors[GREEN]);

		DrawLine(xI, yI - r, xI + 40, yI - r, 4, colors[DARK_GREEN]);
		DrawLine(xI, yI - r, xI - 20, yI + 26 - r, 4, colors[DARK_GREEN]);
		DrawLine(xI, yI - r, xI - 20, yI - 26 - r, 4, colors[DARK_GREEN]);
		xI = 650;
	}
	
	// Draw Plane
	xI = 235; yI = 160; width = 12;
	for (int i = 0; i < 2; ++i) {
		DrawTriangle(xI, yI + 85, xI + width, yI + 85, xI + width / 2, yI + 100, colors[GREEN]);
		DrawRectangle(xI, yI + 15, width, 71, colors[GREEN]);
		DrawTriangle(xI, yI + 60, xI - width * 2, yI + 60, xI, yI + 70, colors[GREEN]);
		DrawTriangle(xI + width, yI + 60, xI + width * 3, yI + 60, xI + width, yI + 70, colors[GREEN]);
		DrawTriangle(xI, yI + 15, xI - width / 2 - 2, yI + 15, xI, yI + 20, colors[GREEN]);
		DrawTriangle(xI + width, yI + 15, xI + width + width / 2 + 2, yI + 15, xI + width, yI + 20, colors[GREEN]);
		DrawTriangle(xI, yI + 15, xI + width, yI + 15, xI + width / 2, yI, colors[GREEN]);
		xI = 650;
	}
	
	// Buttons Text
	DrawString(330, 475, "TANK", colors[WHITE]);
	DrawString(730, 475, "TANK", colors[WHITE]);
	DrawString(300, 335, "HELICOPTER", colors[WHITE]);
	DrawString(705, 335, "HELICOPTER", colors[WHITE]);
	DrawString(325, 195, "PLANE", colors[WHITE]);
	DrawString(720, 195, "PLANE", colors[WHITE]);

	//DrawRoundRect(400, 435, 280, 110, colors[WHITE]);
	//DrawRoundRect(400, 295, 280, 110, colors[WHITE]);
	//DrawRoundRect(400, 155, 280, 110, colors[WHITE]);
}

void Setting::showSoundSetting() {
	DrawString(470, 650, "SOUND SETTINGS", colors[ORANGE_RED]);
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);
	DrawString(55, 660, "back", colors[ORANGE_RED]);
	DrawRoundRect(350, 200, 380, 350, colors[ORANGE_RED]);

	if (gameSoundOn == true) {
		DrawString(380, 500, "Game Sound: On", colors[WHITE]);
		DrawRoundRect(450, 450, 40, 30, colors[BLUE]);
		DrawCircle(450, 465, 15, colors[BLUE]);
		DrawCircle(490, 465, 15, colors[BLUE]);
		DrawCircle(490, 465, 13, colors[WHITE]);
	}
	else {
		DrawString(380, 500, "Game Sound: Off", colors[WHITE]);
		DrawRoundRect(450, 450, 40, 30, colors[DARK_GRAY]);
		DrawCircle(450, 465, 15, colors[DARK_GRAY]);
		DrawCircle(490, 465, 15, colors[DARK_GRAY]);
		DrawCircle(450, 465, 13, colors[WHITE]);
	}
	
}

string ctos(char c) {
	string s = " ";
	s[0] = c;
	return s;
}

void Setting::showControlsSetting() {

	DrawString(450, 670, "CONTROLS SETTINGS", colors[ORANGE_RED]);
	DrawRoundRect(30, 650, 100, 40, colors[WHITE], 20);
	DrawString(55, 660, "back", colors[ORANGE_RED]);

	// Inner Rectangle
	DrawRoundRect(100, 50, 880, 600, colors[ORANGE_RED]);

	// Player 1 Rectangle
	DrawRoundRect(150, 100, 365, 500, colors[WHITE]);
	DrawString(275, 550, "PLAYER 01", colors[ORANGE_RED]);
	// Player 2 Rectangle
	DrawRoundRect(565, 100, 365, 500, colors[WHITE]);
	DrawString(690, 550, "PLAYER 02", colors[ORANGE_RED]);

	// Drawing Options
	if (play->getPlayer1().getcontrols().getUpKey() == 119) {
		DrawRoundRect(200, 345, 265, 145, colors[DARK_GRAY]);
		DrawRoundRect(200, 150, 265, 145, colors[ORANGE_RED]);
		DrawRoundRect(615, 345, 265, 145, colors[ORANGE_RED]);
		DrawRoundRect(615, 150, 265, 145, colors[DARK_GRAY]);
	}
	else if (play->getPlayer1().getcontrols().getUpKey() == GLUT_KEY_UP) {
		DrawRoundRect(200, 345, 265, 145, colors[ORANGE_RED]);
		DrawRoundRect(200, 150, 265, 145, colors[DARK_GRAY]);
		DrawRoundRect(615, 345, 265, 145, colors[DARK_GRAY]);
		DrawRoundRect(615, 150, 265, 145, colors[ORANGE_RED]);
	}

	else if (play->getPlayer2().getcontrols().getUpKey() == 119) {
		DrawRoundRect(200, 345, 265, 145, colors[ORANGE_RED]);
		DrawRoundRect(200, 150, 265, 145, colors[DARK_GRAY]);
		DrawRoundRect(615, 345, 265, 145, colors[DARK_GRAY]);
		DrawRoundRect(615, 150, 265, 145, colors[ORANGE_RED]);
	}
	else if (play->getPlayer1().getcontrols().getUpKey() == GLUT_KEY_UP) {
		DrawRoundRect(200, 345, 265, 145, colors[DARK_GRAY]);
		DrawRoundRect(200, 150, 265, 145, colors[ORANGE_RED]);
		DrawRoundRect(615, 345, 265, 145, colors[ORANGE_RED]);
		DrawRoundRect(615, 150, 265, 145, colors[DARK_GRAY]);
	}
	int x = 0, y = 0;
	char a = 'W', b = 'A', c = 'S', d = 'D';
	for (int i = 0; i < 4; i++) {
		DrawRoundRect(305 + x, 425 - y, 55, 50, colors[WHITE]);
		DrawRoundRect(240 + x, 365 - y, 55, 50, colors[WHITE]);
		DrawRoundRect(305 + x, 365 - y, 55, 50, colors[WHITE]);
		DrawRoundRect(370 + x, 365 - y, 55, 50, colors[WHITE]);
		DrawString(305 + 22 + x, 425 + 15 - y, ctos(a), colors[ORANGE_RED]);
		DrawString(240 + 22 + x, 365 + 15 - y, ctos(b), colors[ORANGE_RED]);
		DrawString(305 + 22 + x, 365 + 15 - y, ctos(c), colors[ORANGE_RED]);
		DrawString(370 + 22 + x, 365 + 15 - y, ctos(d), colors[ORANGE_RED]);

		if (i == 0) { x = 415; }
		if (i == 1) { x = 0; y = 195; a = '^'; b = '<'; c = 'v'; d = '>'; }
		if (i == 2) { x = 415; y = 195; }
	}
	
}

//void Tank::setTank(int w, int h, int r, int speed, Canon& c1, Canon& c2, Canon& c3) {
//	width = w;
//	height = h;
//	radius = r;
//	isSelected = false;
//	setMovementSpeed(speed);
//	setSmallCanon(c1);
//	setMediumCanon(c2);
//	setLargeCanon(c3);
//}
//
//void Tank::setxy(int x, int y) {
//	getLocation().setX(x);
//	getLocation().setY(y);
//}
//
//void Tank::load() {
//	if (getAlign() == "Up") {
//		DrawRectangle(getLocation().getX(), getLocation().getY(), width, height, colors[GREEN]);
//		DrawCircle(getLocation().getX() + width / 2, getLocation().getY() + height - 20, 10, colors[DARK_GREEN]);
//		DrawLine(getLocation().getX() + width / 2, getLocation().getY() + height - 13, getLocation().getX() + width / 2, getLocation().getY() + height + 30, 5, colors[GREEN]);
//	}
//
//	if (getAlign() == "Down") {
//		DrawRectangle(getLocation().getX(), getLocation().getY(), width, height, colors[GREEN]);
//		DrawCircle(getLocation().getX() + width / 2, getLocation().getY() + 20, 10, colors[DARK_GREEN]);
//		DrawLine(getLocation().getX() + width / 2, getLocation().getY() + 13, getLocation().getX() + width / 2, getLocation().getY() - height + 30, 5, colors[GREEN]);
//	}
//
//	if (getAlign() == "Left") {
//		DrawRectangle(getLocation().getX(), getLocation().getY(), height, width, colors[GREEN]);
//		DrawCircle(getLocation().getX() + 20, getLocation().getY() + width / 2, 10, colors[DARK_GREEN]);
//		DrawLine(getLocation().getX() + 13, getLocation().getY() + width / 2, getLocation().getX() - height + 30, getLocation().getY() + width / 2, 5, colors[GREEN]);
//	}
//
//	if (getAlign() == "Right") {
//		DrawRectangle(getLocation().getX(), getLocation().getY(), height, width, colors[GREEN]);
//		DrawCircle(getLocation().getX() + height - 20, getLocation().getY() + width / 2, 10, colors[DARK_GREEN]);
//		DrawLine(getLocation().getX() + height - 13, getLocation().getY() + width / 2, getLocation().getX() + height + 30, getLocation().getY() + width / 2, 5, colors[GREEN]);
//	}
//}

void Setting::changeVehicle(string type, int id) {
	cout << "Change Vehicle";
	Vehicle *vehicle;
	if (id == 1) { vehicle = &(play->getPlayer1().getVehicle()); }
	else { vehicle = &(play->getPlayer2().getVehicle()); }
	if (type == "Tank") { *vehicle = tank; }
	else if (type == "Helicopter") { *vehicle = helicopter; }
	else if (type == "Plane") { *vehicle = plane; }
}

void Setting::changeControls(int option, int id) {
	cout << "Change Controls\n";
	MovementControls* ptr;
	if (id == 1) { ptr = &(play->getPlayer1().getcontrols()); }
	else { ptr = &(play->getPlayer2().getcontrols()); }
	ptr->setOption(option);
	if (option == 1) {
		ptr->setUpKey(119);
		ptr->setDownKey(115);
		ptr->setLeftKey(97);
		ptr->setRightKey(100);
	}
	else if (option == 2) {
		ptr->setUpKey(GLUT_KEY_UP);
		ptr->setDownKey(GLUT_KEY_DOWN);
		ptr->setLeftKey(GLUT_KEY_LEFT);
		ptr->setRightKey(GLUT_KEY_RIGHT);
	}
}

Setting::Setting() {
	gameSoundOn = true;
	gameMusicOn = true;
}

MovementControls::MovementControls() {
	upKey = downKey = leftKey = rightKey = option =0;
}

void Level::createBots() {
	cout << "Create Bots\n";
	bots = new Bot[id];
	if (id >= 1) {
		if (id >= 1) {
			bots[0].getVehicle() = tank;
			bots[0].setName("Bot 1");
			bots[0].setScore(0);
			bots[0].setIntelligence(1);
		}
		if (id >= 2) {
			bots[1].getVehicle() = helicopter;
			bots[1].setName("Bot 2");
			bots[1].setScore(0);
			bots[1].setIntelligence(2);
		}
		if (id >= 3) {
			bots[2].getVehicle() = plane;
			bots[2].setName("Bot 3");
			bots[2].setScore(0);
			bots[2].setIntelligence(3);
		}
	}
}

void Level::load2Player() {
	DrawRoundRect(975, 675, 100, 40, colors[ORANGE_RED]);
	DrawString(992, 685, "Pause", colors[WHITE]);
	string temp = "2 PLAYER GAME";
	DrawString(440, 685, temp, colors[ORANGE_RED]);
	DrawString(235, 685, to_string(play->getPlayer1().getScore()), colors[ORANGE_RED]);
	DrawString(780, 685, to_string(play->getPlayer2().getScore()), colors[ORANGE_RED]);

	// Drawing Players Name
	DrawString(10, 685, play->getPlayer1().getName(), colors[WHITE]);
	DrawString(820, 685, play->getPlayer2().getName(), colors[WHITE]);

	DrawRectangle(159, 650, 172, 20, colors[ORANGE_RED]);
	for (int i = 0; i < 10; i++) {
		if (i + 1 <= play->getPlayer1().getVehicle().getlife()) {
			DrawRectangle(161 + 15 * i + i * 2, 652, 15, 16, colors[WHITE]);
		}
	}

	// Drawing PowerUps
	DrawRoundRect(10, 635, 120, 30, colors[ORANGE_RED]);
	DrawString(12, 640, "PowerUp " + to_string(play->getPlayer1().getnoOfPowerUps()), colors[WHITE]);
	DrawRoundRect(950, 635, 120, 30, colors[ORANGE_RED]);
	DrawString(940, 640, "PowerUp " + to_string(play->getPlayer2().getnoOfPowerUps()), colors[WHITE]);


	// Drawing Player 1 Canon
	DrawRoundRect(351, 636, 151, 34, colors[DARK_GRAY]);
	for (int i = 0; i < 3; i++) {
		DrawRoundRect(351 + 45 * i + (i + 1) * 4, 640, 45, 26, colors[ORANGE_RED]);
	}
	DrawString(351 + 4 + 2, 643, "S: ul", colors[WHITE]);
	DrawString(351 + 8 + 45 + 2, 643, "M: " + to_string(p1vehicle->getMediumCanon().getAvailableShells()), colors[WHITE]);
	DrawString(351 + 12 + 90 + 2, 643, "L: " + to_string(p1vehicle->getLargeCanon().getAvailableShells()), colors[WHITE]);
	// Drawing Player 2 Canon
	DrawRoundRect(535, 636, 151, 34, colors[DARK_GRAY]);
	for (int i = 0; i < 3; i++) {
		DrawRoundRect(535 + 45 * i + (i + 1) * 4, 640, 45, 26, colors[ORANGE_RED]);
	}
	DrawString(535 + 4 + 2, 643, "S: ul", colors[WHITE]);
	DrawString(535 + 8 + 45 + 2, 643, "M: " + to_string(p2vehicle->getMediumCanon().getAvailableShells()), colors[WHITE]);
	DrawString(535 + 12 + 90 + 2, 643, "L: " + to_string(p2vehicle->getLargeCanon().getAvailableShells()), colors[WHITE]);


	DrawRectangle(700, 650, 172, 20, colors[ORANGE_RED]);
	for (int i = 0; i < 10; i++) {
		if (i + 1 <= play->getPlayer2().getVehicle().getlife()) {
			DrawRectangle(702 + 15 * i + i * 2, 652, 15, 16, colors[WHITE]);
		}
	}

	for (int i = 0; i < numberOfObstacles; i++) {
		obstacles[i].load();
	}
	/*glutSwapBuffers();*/
	//vehicle = tank;
	p1vehicle->load();
	p2vehicle->load();
}

void Level::popUpCanon(bool& showing) {
	if (count == 0) {
		popUpLocation.setX(rand() % 1040 + 40);
		popUpLocation.setY(rand() % 600 + 40);
	}
	DrawCircle(popUpLocation.getX(), popUpLocation.getY(), 15, colors[BROWN]);
	count++;
	if (count == 100) {
		count = 0;
		showing = false;
	}
}

Level::~Level() {
	delete obstacles;
	delete bots;
}

void Player::respawn() {
	cout << "Respawn\n";
	if (name == "Bot") {
		if (play->getLevel1().isPassed() == false) {
			(play->getLevel1().getBot())[0].getVehicle().getLocation().setX(50);
			(play->getLevel1().getBot())[0].getVehicle().getLocation().setY(50);

		}

		else if (play->getLevel2().isPassed() == false) {
			(play->getLevel2().getBot())[0].getVehicle().getLocation().setX(50);
			(play->getLevel2().getBot())[0].getVehicle().getLocation().setY(50);
			(play->getLevel2().getBot())[1].getVehicle().getLocation().setX(950);
			(play->getLevel2().getBot())[1].getVehicle().getLocation().setY(50);

		}
		else if (play->getLevel2().isPassed() == true) {
			(play->getLevel3().getBot())[0].getVehicle().getLocation().setX(50);
			(play->getLevel3().getBot())[0].getVehicle().getLocation().setY(50);
			(play->getLevel3().getBot())[1].getVehicle().getLocation().setX(950);
			(play->getLevel3().getBot())[1].getVehicle().getLocation().setY(50);
			(play->getLevel3().getBot())[2].getVehicle().getLocation().setX(50);
			(play->getLevel3().getBot())[2].getVehicle().getLocation().setY(500);

		}
	}
	else {
		int temp = rand() % 1000 + 50;
		playerVehicle.getLocation().setX(temp - temp % 5);
		temp = rand() % 520 + 40;
		playerVehicle.getLocation().setY(temp - temp % 5);
		playerVehicle.setlife(10);
	}
	
}

void Person::pickPopUpCanon(bool& canon) {
	int Xloc = 0, Yloc = 0;
	Xloc = playerVehicle.getLocation().getX() + playerVehicle.getWidth() / 2;
	Yloc = playerVehicle.getLocation().getY() + playerVehicle.getHeight() / 2;

	if (play->getLevel2().isPassed() == true) {
		if (play->getLevel3().getPopUpLocation().getX() <= Xloc + 150 && play->getLevel3().getPopUpLocation().getX() >= Xloc - 150 && play->getLevel3().getPopUpLocation().getY() <= Yloc + 150 && play->getLevel3().getPopUpLocation().getX() >= Yloc - 150) {
			play->getLevel3().setcount(0);
			canon = false;
			playerVehicle.getLargeCanon().setAvailableShells(playerVehicle.getLargeCanon().getAvailableShells() + 1);
		}
	}
	else if (play->getLevel1().isPassed() == true) {
		if (play->getLevel2().getPopUpLocation().getX() <= Xloc + 150 && play->getLevel2().getPopUpLocation().getX() >= Xloc - 150 && play->getLevel2().getPopUpLocation().getY() <= Yloc + 150 && play->getLevel2().getPopUpLocation().getX() >= Yloc - 150) {
			play->getLevel2().setcount(0);
			canon = false;
			playerVehicle.getLargeCanon().setAvailableShells(playerVehicle.getLargeCanon().getAvailableShells() + 1);
		}
	}

	else {
		if (play->getLevel1().getPopUpLocation().getX() <= Xloc + 150 && play->getLevel1().getPopUpLocation().getX() >= Xloc - 150 && play->getLevel1().getPopUpLocation().getY() <= Yloc + 150 && play->getLevel1().getPopUpLocation().getX() >= Yloc - 150) {
			play->getLevel1().setcount(0);
			canon = false;
			playerVehicle.getLargeCanon().setAvailableShells(playerVehicle.getLargeCanon().getAvailableShells() + 1);
		}
	}
}

void Person::usePowerUps() {
	if (noOfPowerUps > 0) {
		playerVehicle.increaseTemporarySpeed();
		noOfPowerUps--;
	}
	else {
		cout << "No Power Ups\n";
	}
}
