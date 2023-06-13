#ifndef RushHour_CPP_
#define RushHour_CPP_

#endif
#include "util.h"
#include "PlayGame.h"
#include <iostream>
#include <fstream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt


Game* game = Game::getInstance();
Play* playGame = Play::getInstance();

bool isMenuDisplayed = false;
bool showedAnimation = false;
bool showSettings = false;
bool showHighScores = false;
bool showInstructions = false;
bool showPlayer1 = false;
bool showPlayer2 = false;
bool showCredits = false;
bool showControls = false;
bool showVehicle = false;
bool showSound = false;
bool player1Started = false;
bool player2Started = false;
bool isGamePaused = false;
bool isCanonPopUp = false;

void movementFunc(int key, int x, int y) {
	Person* p1 = &(playGame->getPlayer1());
	Person* p2 = &(playGame->getPlayer2());
	if (key == p1->getcontrols().getUpKey() && (player1Started || player2Started) && p1->getcontrols().getoption() == 2) {
		p1->getVehicle().moveup();
		cout << "Move Up\n";
	}
	else if (key == p1->getcontrols().getRightKey() && (player1Started || player2Started) && p1->getcontrols().getoption() == 2) {
		p1->getVehicle().moveright();
		cout << "Move Right - " << key << endl;
	}
	else if (key == p1->getcontrols().getLeftKey() && (player1Started || player2Started) && p1->getcontrols().getoption() == 2) {
		p1->getVehicle().moveleft();
		cout << "Move Left - " << key << endl;
	}
	else if (key == p1->getcontrols().getDownKey() && (player1Started || player2Started) && p1->getcontrols().getoption() == 2) {
		p1->getVehicle().movedown();
		cout << "Move Down\n";
	}

	else if (key == p2->getcontrols().getUpKey() && (player1Started || player2Started) && p2->getcontrols().getoption() == 2) {
		p2->getVehicle().moveup();
		cout << "Move Up\n";
	}
	else if (key == p2->getcontrols().getRightKey() && (player1Started || player2Started) && p2->getcontrols().getoption() == 2) {
		p2->getVehicle().moveright();
		cout << "Move Right - " << key << endl;
	}
	else if (key == p2->getcontrols().getLeftKey() && (player1Started || player2Started) && p2->getcontrols().getoption() == 2) {
		p2->getVehicle().moveleft();
		cout << "Move Left - " << key << endl;
	}
	else if (key == p2->getcontrols().getDownKey() && (player1Started || player2Started) && p2->getcontrols().getoption() == 2) {
		p2->getVehicle().movedown();
		cout << "Move Down\n";
	}
}

void GameIntro(int c) {
	glClearColor(0.07f, 0.13f, 0.7f, 1.0f); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	static int count = 0;
	if (count < 40) {
		game->showStartAnimation(count);
		count++;
		if (count == 39) { showedAnimation = true; isMenuDisplayed = true; }
	}
	glutSwapBuffers();
}

void gameMenu(){
	isMenuDisplayed = true;
	glClearColor(0.07f, 0.13f, 0.7f, 1.0f); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	game->showMenu();
	glutSwapBuffers();
	
}

void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display() {
	static int count = 0;
	glClearColor(0.07f, 0.13f, 0.7f, 1.0f); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors

	if (count <20) {
		game->showMenu();
	}
	if (count >= 20) {
		if (count == 30) {
			playGame->updateLevels();
		}
		
		//playGame->getL1()->load();

		if (playGame->getVehicle().getShortCanon().isShooted()) {
			playGame->getVehicle().getShortCanon().bounce();
		}
		if (playGame->getVehicle().getMediumCanon().isShooted()) {
			playGame->getVehicle().getMediumCanon().bounce();
		}
		if (playGame->getVehicle().getLargeCanon().isShooted()) {
			playGame->getVehicle().getLargeCanon().bounce();
		}


		static Bot* ptr = playGame->getL1()->getBot();
		if (count == 30) { ptr->AssignVehicle(); }		// Mandatory for every level to assign Vehicle
		ptr[0].getVehicle().load();
		ptr[0].moveintelligently();
	}
	
	DrawString(50, 100, to_string(count), colors[ORANGE]);
	count++;
	glutSwapBuffers();
}

//
//void NonPrintableKeys(int key, int x, int y) {
//	if (key == GLUT_KEY_LEFT) {
//		// what to do when left key is pressed...
//		Align = "Left";
//		if (xI > 0 + 30) {
//			if (!(xI >= 250 && xI <= 830 && yI >= 350-tankWidth  && yI < 370)) {
//				xI -= 10;
//			}
//		}
//
//		DrawRectangle(250, 350, 580, 20, colors[ORANGE]);
//		DrawRectangle(530, 150, 20, 420, colors[ORANGE]);
//	} else if (key == GLUT_KEY_RIGHT) {
//		Align = "Right";
//		if (xI < 1080-30) {
//			if (!(xI >= 250 - tankHeight && xI <= 830 && yI >= 350 - tankWidth && yI < 370)) {
//				xI += 10;
//			}
//		}
//	} else if (key == GLUT_KEY_UP) {
//		Align = "Up";
//		if (yI+tankHeight < 720-30) {
//			if (!(xI >= 250-tankHeight && xI <= 830 && yI >= 350 - tankWidth -20 && yI < 370)) {
//				yI += 10;
//			}
//				//yI += 10;
//			//}
//			//else {
//				
//			//}
//			
//		}
//	}
//	else if (key == GLUT_KEY_DOWN) {
//		Align = "Down";
//		if (yI > 0+30) {
//			yI -= 10;
//		}
//	}
//
//	glutPostRedisplay();*/
//}

void PrintableKeys(unsigned char Key, int x, int y) {/*
	if (key == 27) {
		exit(1); // exit the program when escape key is pressed.
	}*/
	int key = Key;
	Person* p1 = &(playGame->getPlayer1());
	Person* p2 = &(playGame->getPlayer2());
	if (key == p1->getcontrols().getUpKey() && (player1Started || player2Started) && p1->getcontrols().getoption() == 1) {
		p1->getVehicle().moveup();
	}
	else if (key == p1->getcontrols().getRightKey() && (player1Started || player2Started) && p1->getcontrols().getoption() == 1) {
		p1->getVehicle().moveright();
		cout << "Move Right - " << key << endl;
	}
	else if (key == p1->getcontrols().getLeftKey() && (player1Started || player2Started) && p1->getcontrols().getoption() == 1) {
		p1->getVehicle().moveleft();
		cout << "Move Left - " << key << endl;
	}
	else if (key == p1->getcontrols().getDownKey() && (player1Started || player2Started) && p1->getcontrols().getoption() == 1) {
		p1->getVehicle().movedown();
	}

	else if (key == p2->getcontrols().getUpKey()&& (player1Started || player2Started) && p2->getcontrols().getoption() == 1) {
		p2->getVehicle().moveup();
	}
	else if (key == p2->getcontrols().getRightKey()&& (player1Started || player2Started) && p2->getcontrols().getoption() == 1) {
		p2->getVehicle().moveright();
		cout << "Move Right - " << key << endl;
	}
	else if (key == p2->getcontrols().getLeftKey()&& (player1Started || player2Started) && p2->getcontrols().getoption() == 1) {
		p2->getVehicle().moveleft();
		cout << "Move Left - " << key << endl;
	}
	else if (key == p2->getcontrols().getDownKey()&& (player1Started || player2Started) && p2->getcontrols().getoption() == 1) {
		p2->getVehicle().movedown();
	}

	if (key == ' ' && (player1Started || player2Started)) {
		playGame->getPlayer1().getVehicle().getShortCanon().shoot(playGame->getPlayer1().getVehicle() );
	}

	if (key == 'm' && (player1Started || player2Started)) {
		playGame->getPlayer1().getVehicle().getMediumCanon().shoot(playGame->getPlayer1().getVehicle());
	}

	if (key == 'l' && (player1Started || player2Started)) {
		playGame->getPlayer1().getVehicle().getLargeCanon().shoot(playGame->getPlayer1().getVehicle());
	}

	if ((key == 'p' || key == 'P') && isCanonPopUp == true && (player1Started || player2Started)) {
		playGame->getPlayer1().pickPopUpCanon(isCanonPopUp);
	}

	if ((key == 'o' || key == 'O') && (player1Started || player2Started)) {
		playGame->getPlayer1().usePowerUps();
	}

	if (key == 'z' && (player2Started)) {
		playGame->getPlayer2().getVehicle().getShortCanon().shoot(playGame->getPlayer2().getVehicle() );
	}

	if (key == 'x' && (player2Started)) {
		playGame->getPlayer2().getVehicle().getMediumCanon().shoot(playGame->getPlayer2().getVehicle());
	}

	if (key == 'c' && (player2Started)) {
		playGame->getPlayer2().getVehicle().getLargeCanon().shoot(playGame->getPlayer2().getVehicle());
	}

	if ((key == 'q' || key == 'Q') && isCanonPopUp == true && (player2Started)) {
		playGame->getPlayer2().pickPopUpCanon(isCanonPopUp);
	}

	if ((key == 'e' || key == 'E') && (player2Started)) {
		playGame->getPlayer2().usePowerUps();
	}

	if (key == '7') {
		playGame->getPlayer1().getVehicle().setAlign("TopLeft");
	}

	if (key == '9') {
		playGame->getPlayer1().getVehicle().setAlign("TopRight");
	}
	
	if (key == '1') {
		playGame->getPlayer1().getVehicle().setAlign("BottomLeft");
	}
	
	if (key == '3') {
		playGame->getPlayer1().getVehicle().setAlign("BottomRight");
	}

/*
	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	glutPostRedisplay();*/
}

void MouseClicked(int button, int state, int x, int y) {
	static int noreclick = 0;
	if (noreclick == 0) {
		if (button == GLUT_LEFT_BUTTON) {
			cout << GLUT_DOWN << " " << GLUT_UP << endl;
			if (x >= 150 && x <= 500 && y <= 340 && y >= 260 && isMenuDisplayed) {
				cout << "HighScore Clicked\n";
				showHighScores = true;
				isMenuDisplayed = false;
			}
			else if (x >= 580 && x <= 930 && y <= 340 && y >= 260 && isMenuDisplayed) {
				cout << "Credits Button Clicked\n";
				showCredits = true;
				isMenuDisplayed = false;
			}
			else if (x >= 365 && x <= 715 && y <= 700 && y >= 620 && isMenuDisplayed) {
				cout << "Instructions Button Clicked\n";
				showInstructions = true;
				isMenuDisplayed = false;
			}
			else if (x >= 365 && x <= 715 && y <= 460 && y >= 380 && isMenuDisplayed) {
				cout << "Setting Button Clicked\n";
				showSettings = true;
				isMenuDisplayed = false;
			}
			else if (x >= 150 && x <= 500 && y <= 580 && y >= 500 && isMenuDisplayed) {
				cout << "Player 1 Button Clicked\n";
				showPlayer1 = true;
				isMenuDisplayed = false;
			}
			else if (x >= 580 && x <= 930 && y <= 580 && y >= 500 && isMenuDisplayed) {
				cout << "Player2 Button Clicked\n";
				showPlayer2 = true;
				isMenuDisplayed = false;
			}
			else if (x >= 30 && x <= 130 && y <= 70 && y >= 30 && (showCredits || showPlayer1 || showPlayer2 || showSettings || showHighScores || showInstructions)) {
				showCredits = showPlayer1 = showPlayer2 = showSettings = showHighScores = showInstructions = false;
				isMenuDisplayed = true;
				game->setCount(0);
				cout << "Back Button Clicked\n";
			}
			else if (x >= 400 && x <= 680 && y <= 295 && y >= 235 && showSettings) {
				showSound = true;
				showSettings = false;
			}

			else if (x >= 400 && x <= 680 && y <= 385 && y >= 325 && showSettings) {
				showVehicle = true;
				showSettings = false;
			}

			else if (x >= 400 && x <= 680 && y <= 475 && y >= 415 && showSettings) {
				showControls = true;
				showSettings = false;
			}

			else if (x >= 30 && x <= 130 && y <= 70 && y >= 30 && (showControls || showVehicle || showSound)) {
				showControls = showVehicle = showSound = false;
				showSettings = true;
			}

			else if (x >= 192.5 && x <= 472.5 && y <= 285 && y >= 175 && showVehicle) {
				game->getsetting().changeVehicle("Tank", 1);
			}

			else if (x >= 192.5 && x <= 472.5 && y <= 425 && y >= 315 && showVehicle) {
				game->getsetting().changeVehicle("Helicopter", 1);
			}

			else if (x >= 192.5 && x <= 472.5 && y <= 565 && y >= 455 && showVehicle) {
				game->getsetting().changeVehicle("Plane", 1);
			}

			else if (x >= 607.5 && x <= 887.5 && y <= 285 && y >= 175 && showVehicle) {
				game->getsetting().changeVehicle("Tank", 2);
			}

			else if (x >= 607.5 && x <= 887.5 && y <= 425 && y >= 315 && showVehicle) {
				game->getsetting().changeVehicle("Helicopter", 2);
			}

			else if (x >= 607.5 && x <= 887.5 && y <= 565 && y >= 455 && showVehicle) {
				game->getsetting().changeVehicle("Plane", 2);
			}

			else if (x >= 200 && x <= 465 && y <= 375 && y >= 230 && showControls) {
				game->getsetting().changeControls(1, 1);
				game->getsetting().changeControls(2, 2);
			}
			
			else if (x >= 200 && x <= 465 && y <= 570 && y >= 425 && showControls) {
				game->getsetting().changeControls(2, 1);
				game->getsetting().changeControls(1, 2);
			}

			else if (x >= 615 && x <= 880 && y <= 375 && y >= 230 && showControls) {
				game->getsetting().changeControls(1, 2);
				game->getsetting().changeControls(2, 1);
			}
			
			else if (x >= 615 && x <= 880 && y <= 570 && y >= 425 && showControls) {
				game->getsetting().changeControls(2, 2);
				game->getsetting().changeControls(1, 1);
			}

			else if (x >= 440 && x <= 640 && y <= 400 && y >= 340 && showPlayer1) {
				if (playGame->getPlayer1().getName() == "") {
					cout << "Enter Name";
				}
				else {
					cout << "Game Started\n";
					game->startGame();
					playGame->getLevel1().createBots();
					playGame->getLevel2().createBots();
					playGame->getLevel3().createBots();
					playGame->setType(1);
					playGame->getPlayer1().respawn();
					(playGame->getLevel1().getBot())[0].respawn();
					player1Started = true;
					showPlayer1 = false;

					if (game->getsetting().getMusicSound()) {
						PlaySound(TEXT("game_sound.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
					}
				}
			}
			else if (x>=975 && x<=1075 && y<=45 && y>=5 && player1Started) {
				cout << "Game Paused\n";
				isGamePaused = true;
				player1Started = false;
				PlaySound(0, 0, 0);
			}
			
			else if (x >= 325 && x <= 525 && y <= 420 && y >= 360 && isGamePaused) {
				cout << "Game Resumed\n";
				player1Started = true;
				isGamePaused = false;
				if (game->getsetting().getMusicSound()) {
					PlaySound(TEXT("game_sound.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				}
			}

			else if (x >= 555 && x <= 755 && y <= 420 && y >= 360 && isGamePaused) {
				PlaySound(0, 0, 0);
				//Store Player Progress
				ofstream progress;
				progress.open("playerProgress.dat", ios::binary|ios::app|ios::out);
				if (!progress) { cout << "Error\n"; }
				progress.write((const char*)playGame, sizeof(Play));
				progress.close();
				// storing bots info
				ofstream botsfile;
				botsfile.open("bots.dat", ios::binary|ios::app | ios::out);
				botsfile.write((const char*)&(playGame->getLevel1().getBot())[0], sizeof(Bot));
				botsfile.write((const char*)&(playGame->getLevel2().getBot())[0], sizeof(Bot));
				botsfile.write((const char*)&(playGame->getLevel2().getBot())[1], sizeof(Bot));
				botsfile.write((const char*)&(playGame->getLevel3().getBot())[0], sizeof(Bot));
				botsfile.write((const char*)&(playGame->getLevel3().getBot())[1], sizeof(Bot));
				botsfile.write((const char*)&(playGame->getLevel3().getBot())[2], sizeof(Bot));
				botsfile.close();
				
				cout << "Game Left\n";
				isMenuDisplayed = true;
				isGamePaused = false;
				player2Started = false;
				player1Started = false;
				playGame->setCount(0);
			}

			else if (x >= 365 && x <= 715 && y <= 330 && y >= 290 && showPlayer2) {
				cout << "Enter Player 01 Name: ";
				string name;
				getline(cin, name);
				playGame->getPlayer1().setName(name);
			}

			else if (x >= 365 && x <= 715 && y <= 470 && y >= 430 && showPlayer2) {
				cout << "Enter Player 02 Name: ";
				string name;
				getline(cin, name);
				playGame->getPlayer2().setName(name);
			}

			else if (x >= 440 && x <= 640 && y <= 570 && y >= 500 && showPlayer2) {
				if (playGame->getPlayer1().getName() == "" || playGame->getPlayer2().getName() == "") {
					cout << "Enter Name";
				}
				else {
					playGame->setType(2);
					game->startGame();
					playGame->getPlayer1().respawn();
					playGame->getPlayer2().respawn();
					player2Started = true;
					showPlayer2 = false;
					if (game->getsetting().getMusicSound()) {
						PlaySound(TEXT("game_sound.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
					}
				}
			}

			else if (x >= 340 && x <= 740 && y <= 550 && y >= 480 && playGame->getShowNextLvl()) {
				playGame->increaseCurrentLvl();
				playGame->setShowNextLvl(false);
				if (playGame->getLevel1().isPassed() == false) { playGame->getLevel1().setGamePassed(true); }
				else if (playGame->getLevel2().isPassed() == false) { playGame->getLevel2().setGamePassed(true); }
				else if (playGame->getLevel3().isPassed() == false) { playGame->getLevel3().setGamePassed(true); }
				if (playGame->getType() == 1) {
					Bot* ptr;
					ptr = playGame->getLevel2().getBot();
					ptr[0].respawn();
					ptr[0].increaseSpeed();
					ptr[1].respawn();
					ptr[1].increaseSpeed();
					ptr = playGame->getLevel3().getBot();
					ptr[0].increaseSpeed();
					ptr[0].respawn();
					ptr[1].increaseSpeed();
					ptr[1].respawn();
					ptr[2].increaseSpeed();
					ptr[2].respawn();
				}
			}
			
			else if (x >= 340 && x <= 740 && y <= 550 && y >= 480 && playGame->getIsShowingWinner()) {
				cout << "B\n";
				isMenuDisplayed = true;
				playGame->setIsShowingWinner(false);
				player2Started = false;
				player1Started = false;
				playGame->setCount(0);
				PlaySound(0, 0, 0);
			}
			
			else if ((x >= 340 && x <= 740 && y <= 550 && y >= 480 && playGame->getIsShowingRetry()) || (x >= 390 && x <= 690 && y <= 460 && y >= 400 && playGame->getIsShowingWinner())) {
				cout << "RETRY CLICKED\n";
				int type = playGame->getType();
				playGame->setCount(0);
				playGame->resetPlay();
				game->startGame();
				playGame->getLevel1().createBots();
				playGame->getLevel2().createBots();
				playGame->getLevel3().createBots(); 

				playGame->getLevel1().setStop(false);
				playGame->getLevel2().setStop(false);
				playGame->getLevel3().setStop(false);

				playGame->getLevel1().setGamePassed(false);
				playGame->getLevel2().setGamePassed(false);
				playGame->getLevel3().setGamePassed(false);

				playGame->getPlayer1().respawn();
				(playGame->getLevel1().getBot())[0].respawn();
				(playGame->getLevel2().getBot())[0].respawn();
				(playGame->getLevel3().getBot())[0].respawn();
				(playGame->getLevel2().getBot())[1].respawn();
				(playGame->getLevel3().getBot())[1].respawn();
				(playGame->getLevel3().getBot())[2].respawn();
				
			}
			else if (x >= 435 && x <= 505 && y <= 270 && y >= 240 && showSound) {
				game->getsetting().changeSoundCond();
			}

			else if (x>=440 && x<=640 && y<=480 && y>=420 && showPlayer1 && playGame->getGameRecordExistance()) {
				// Loading data to start game from loaded state
				cout << "Resume Button Clicked\n";
				string temp = playGame->getPlayer1().getName();
				ifstream file;
				file.open("playerProgress.dat", ios::binary | ios::in);
				bool flag = false;
				while (!file.eof()) {
					file.read((char*)playGame, sizeof(Play));
					if (playGame->getPlayer1().getName() == temp) {
						cout << "file Readed for " << playGame->getPlayer1().getName() << endl;
						break;
					}
				}
				file.close();
				//reading completed of Play Class

				// starting reading Bots class
				ifstream fileb;
				fileb.open("bots.dat", ios::binary | ios::in);
				Bot* p;
				p = playGame->getLevel1().getBot();
				p = new Bot[1];
				fileb.read((char*)&(p[0]), sizeof(Bot));
				p = playGame->getLevel2().getBot();
				p = new Bot[2];
				fileb.read((char*)&(p[0]), sizeof(Bot));
				fileb.read((char*)&(p[1]), sizeof(Bot));
				p = playGame->getLevel3().getBot();
				p = new Bot[3];
				fileb.read((char*)&(p[0]), sizeof(Bot));
				fileb.read((char*)&(p[1]), sizeof(Bot));
				fileb.read((char*)&(p[2]), sizeof(Bot));
				fileb.close();

				// Obstacles Being Created
				playGame->updateLevels();
				player1Started = true;
				showPlayer1 = false;
				playGame->setGameRecordExistance(false);
			}

			else if (x >= 365 && x <= 715 && y <= 310 && y >= 270 && showPlayer1) {
				string temp;
				cout << "Enter Player Name: ";
				getline(cin, temp);
				playGame->getPlayer1().setName(temp);

				// checking if the data of player previously exists or not
				Play* tempObj = new Play;
				ifstream file;
				file.open("playerProgress.dat", ios::binary | ios::in);
				cout << "File Opened\n";
				bool flag = false;
				while (!file.eof()) {
					file.read((char*)tempObj, sizeof(Play));
					cout << "File Readed";
					if (tempObj->getPlayer1().getName() == playGame->getPlayer1().getName()) {
						cout << "Name Matched";
						flag = true;
						playGame->setGameRecordExistance(true);
						break;
					}
				}
			}
		}

		else if (button == GLUT_RIGHT_BUTTON) {
			cout << "Right Button Pressed" << endl;

		}
		noreclick++;
	}
	else { noreclick = 0; }
	
	//glutPostRedisplay();
}

void Timer() { 
	cout << "Entered in Time FUnction\n";
	if (time(0) % 1000 == 0) {
		//cout << "Timer Func Called\n";
		static int count = 0;
		if (count < 40) {
			GameIntro(count);
			count++;
			if (count == 39) { isMenuDisplayed = true; }
		}
		else {
			//cout << "Entered\n";
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Red==Green==Blue==1 --> White Colour
			glClear(GL_COLOR_BUFFER_BIT); //Update the colors

			if (rand() % 100 == 4 && isCanonPopUp == false && (player1Started || player2Started)) { isCanonPopUp = true; }
			if (isMenuDisplayed) {
				game->showMenu();
			}
			else if (showHighScores) {
				game->showHighScores();
			}
			else if (showCredits) {
				game->ShowCredits();
			}
			else if (showPlayer1) {
				game->startPlayer1();
			}
			else if (showPlayer2) {
				game->startPlayer2();
			}
			else if (showSettings) {
				game->showSettings();
			}
			else if (showSound) {
				game->getsetting().showSoundSetting();
			}
			else if (showControls) {
				game->getsetting().showControlsSetting();
			}
			else if (showVehicle) {
				game->getsetting().showVehicleSetting();
			}
			if (player1Started) {
				playGame->begin1PlayerGame();
			}
			if (player2Started) {
				playGame->begin2PlayerGame();
			}

			if (isGamePaused) {
				playGame->showPausedScreen();
			}
			// Player 01 Only
			if (playGame->getPlayer1().getVehicle().getShortCanon().isShooted()) {
				playGame->getPlayer1().getVehicle().getShortCanon().bounce();
			}
			if (playGame->getPlayer1().getVehicle().getMediumCanon().isShooted()) {
				playGame->getPlayer1().getVehicle().getMediumCanon().bounce();
			}
			if (playGame->getPlayer1().getVehicle().getLargeCanon().isShooted()) {
				playGame->getPlayer1().getVehicle().getLargeCanon().bounce();
			}

			// Player 02 Only
			if (playGame->getPlayer2().getVehicle().getShortCanon().isShooted()) {
				playGame->getPlayer2().getVehicle().getShortCanon().bounce();
			}
			if (playGame->getPlayer2().getVehicle().getMediumCanon().isShooted()) {
				playGame->getPlayer2().getVehicle().getMediumCanon().bounce();
			}
			if (playGame->getPlayer2().getVehicle().getLargeCanon().isShooted()) {
				playGame->getPlayer2().getVehicle().getLargeCanon().bounce();
			}
			if (isCanonPopUp && (player1Started || player2Started)) {
				if (playGame->getLevel2().isPassed() == true) {
					playGame->getLevel3().popUpCanon(isCanonPopUp);
				}
				else if (playGame->getLevel1().isPassed() == true) {
					playGame->getLevel2().popUpCanon(isCanonPopUp);
				}
				else {
					playGame->getLevel1().popUpCanon(isCanonPopUp);
				}
			}

			if (showInstructions) {
				game->showInstructions();
			}

			glutSwapBuffers();
			//glutDisplayFunc(Display);
			//Display();
		}

		// implement your functionality here
		//moveCar();
		/*if (strike_Count < 3) {
			moveCanon();
		}
		else {
			shoot = false;
			click = 0;
			strike_Count = 0;
		}*/

		// once again we tell the library to call our Timer function after next 1000/FPS
		//glutPostRedisplay();
		//glutTimerFunc(100, Timer, 0);
	}
}


void Timer(int m) {
		//cout << "Timer Func Called\n";
		static int count = 0;
		if (count < 40) {
			GameIntro(count);
			count++;
			if (count == 39) { isMenuDisplayed = true; }
		}
		else {
			//cout << "Entered\n";
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Red==Green==Blue==1 --> White Colour
			glClear(GL_COLOR_BUFFER_BIT); //Update the colors

			if (rand() % 100 == 4 && isCanonPopUp == false && (player1Started || player2Started)) { isCanonPopUp = true; }
			if (isMenuDisplayed) {
				game->showMenu();
			}
			else if (showHighScores) {
				game->showHighScores();
			}
			else if (showCredits) {
				game->ShowCredits();
			}
			else if (showPlayer1) {
				game->startPlayer1();
			}
			else if (showPlayer2) {
				game->startPlayer2();
			}
			else if (showSettings) {
				game->showSettings();
			}
			else if (showSound) {
				game->getsetting().showSoundSetting();
			}
			else if (showControls) {
				game->getsetting().showControlsSetting();
			}
			else if (showVehicle) {
				game->getsetting().showVehicleSetting();
			}
			if (player1Started) {
				playGame->begin1PlayerGame();
			}
			if (player2Started) {
				playGame->begin2PlayerGame();
			}

			if (isGamePaused) {
				playGame->showPausedScreen();
			}
			// Player 01 Only
			if (playGame->getPlayer1().getVehicle().getShortCanon().isShooted()) {
				playGame->getPlayer1().getVehicle().getShortCanon().bounce();
			}
			if (playGame->getPlayer1().getVehicle().getMediumCanon().isShooted()) {
				playGame->getPlayer1().getVehicle().getMediumCanon().bounce();
			}
			if (playGame->getPlayer1().getVehicle().getLargeCanon().isShooted()) {
				playGame->getPlayer1().getVehicle().getLargeCanon().bounce();
			}

			// Player 02 Only
			if (playGame->getPlayer2().getVehicle().getShortCanon().isShooted()) {
				playGame->getPlayer2().getVehicle().getShortCanon().bounce();
			}
			if (playGame->getPlayer2().getVehicle().getMediumCanon().isShooted()) {
				playGame->getPlayer2().getVehicle().getMediumCanon().bounce();
			}
			if (playGame->getPlayer2().getVehicle().getLargeCanon().isShooted()) {
				playGame->getPlayer2().getVehicle().getLargeCanon().bounce();
			}
			if (isCanonPopUp && (player1Started || player2Started)) {
				if (playGame->getLevel2().isPassed() == true) {
					playGame->getLevel3().popUpCanon(isCanonPopUp);
				}
				else if (playGame->getLevel1().isPassed() == true) {
					playGame->getLevel2().popUpCanon(isCanonPopUp);
				}
				else {
					playGame->getLevel1().popUpCanon(isCanonPopUp);
				}
			}

			if (showInstructions) {
				game->showInstructions();
			}

			glutSwapBuffers();
			//glutDisplayFunc(Display);
			//Display();
		}

		// implement your functionality here
		//moveCar();
		/*if (strike_Count < 3) {
			moveCanon();
		}
		else {
			shoot = false;
			click = 0;
			strike_Count = 0;
		}*/

		// once again we tell the library to call our Timer function after next 1000/FPS
		//glutPostRedisplay();
		glutTimerFunc(100, Timer, 0);
}


void display()
{
	// Your rendering code goes here
	glClear(GL_COLOR_BUFFER_BIT);
	// ...

	// Swap the buffers
	glutSwapBuffers();
}

//int main(int argc, char* argv[]) {
//	int width = 1080, height = 720; // i have set my window size to be 800 x 600
//	InitRandomizer(); // seed the random number generator...
//	glutInit(&argc, argv); // initialize the graphics library...
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
//	glutInitWindowPosition(50, 50); // set the initial position of our window
//	glutInitWindowSize(width, height); // set the size of our window
//	glutCreateWindow("Attari By Basit Nazir"); // set the title of our game window
//	SetCanvasSize(width, height); // set the number of pixels...
//	srand(time(NULL));
//
//	glutSpecialFunc(movementFunc); // tell library which function to call for non-printable ASCII characters
//	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
//	//// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
//	glutTimerFunc(1000.0, Timer, 0);
//
//	//glutDisplayFunc(Timer);
//
//
//	glutMouseFunc(MouseClicked);
//	//glutPassiveMotionFunc(MouseMoved); // Mouse
//	//glutMotionFunc(MousePressedAndMoved); // Mouse
//
//
//	glutMainLoop();
//
//	
//
//
// 
//}



int main(int argc, char* argv[]) {
	int width = 1080, height = 720;
	InitRandomizer();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(width, height);
	glutCreateWindow("Attari By Basit Nazir");
	SetCanvasSize(width, height);
	srand(time(NULL));

	glutSpecialFunc(movementFunc);
	glutKeyboardFunc(PrintableKeys);
	glutDisplayFunc(Timer);
	glutTimerFunc(1000.0, Timer, 0);
	
	glutMouseFunc(MouseClicked);

	glutMainLoop();
}


