#pragma once
#include <string>;
#include <Windows.h>
#include <MMSystem.h>
using namespace std;

class Bot;	

class Point {	// stores coordinates of a point
	float x;	
	float y;
public:
	// setters
	void setX(float);	
	void setY(float);
	// getters
	float getX();
	float getY();
};

class Obstacle {
	int id;		
	Point location;
	int color;
	string type;
	int width;	// width of obstacle
	int height;
public:
	Obstacle();	// default constructor
	Obstacle(int id, float x, float y, string type, int color, int Width, int Height = 0);
	void setLocation(float, float);	// sets x, y loaction of obstacle
	void load();			// Loads the obstacle in Level
	bool checkOverlaping(int x, int y, int w, int h);		// checks if the parameters entered overlaps the obstacle
	// getters
	Point& getLocation() { return location; }	
	int& getWidth() { return width; }
	int& getHeight() { return height; }
};

class MovementControls {
	int upKey;
	int downKey;
	int leftKey;
	int rightKey;
	int option;
public:
	MovementControls();	// default constructor
	// Getters
	int getUpKey() { return upKey; }
	int getDownKey() { return downKey; }
	int getLeftKey() { return leftKey; }
	int getRightKey() { return rightKey; }
	int getoption() { return option; }
	// Setters
	void setUpKey(int key) { upKey = key; }
	void setDownKey(int key) { downKey = key; }
	void setLeftKey(int key) { leftKey = key; }
	void setRightKey(int key) { rightKey = key; }
	void setOption(int opt) { option = opt; }
	//MovementControls(int, int, int, int);

	//void configureControls();
};

class Vehicle;
class Canon {
	int damage;
	int size;
	int noOfShellAvailable;
	int speed;
	Point location;
	bool shooted;
	string direction;
	int strike;
	Vehicle* vehicle;
public:
	Canon();	// default constructor
	Canon(int, int, int, int);		// initialize with damage, size, shells and speed of Canon 
	void shoot(Vehicle&);	// shoots shell from the vehicle
	void bounce();	// shell bounces
	//void increaseCanonLevel();
	bool isShooted() { return shooted; }	// checking if it is shootes
	int getAvailableShells() { return noOfShellAvailable; }	
	// setters
	void setAvailableShells(int num) { noOfShellAvailable = num; }
	void setVehicle(Vehicle* v) { vehicle = v; }
};

class Vehicle {
	string type;
	int movementSpeed;
	Canon smallCanon;
	Canon mediumCanon;
	Canon largeCanon;
	Point location;
	string Align;
	string player;
	int life;
	int limit;
public:
	Vehicle();
	Vehicle(string, int, Canon&, Canon&, Canon&);
	Vehicle(Vehicle&);	// copy constructor
	void initialize();	// initializes the vehicle
	void moveup();		// moves the vehicle upwards
	void movedown();	// moves the vehicle downwards
	void moveleft();	// moves the vehocle leftwards
	void moveright();	// moves the vehicle rightwards
	void load();	// loads the vehicle on screen
	void decreaseLife(int damage) { life -= damage; }	// decrease lifeafter getting shooted
	void increaseTemporarySpeed();	// activates the booster

	// getters
	string getAlign() { return Align; }
	Point& getLocation() { return location; }
	Canon& getShortCanon() { return smallCanon; }
	Canon& getLargeCanon() { return largeCanon; }
	Canon& getMediumCanon() { return mediumCanon; }
	int getMovementSpeed() { return movementSpeed; }
	string getType() { return type; }
	int getlife() { return life; }
	int getHeight() {
		if (type == "Tank") { return 100; }
		if (type == "Helicopter") { return 85; }
		if (type == "Plane") { return 79; }
	}

	int getWidth() {
		if (type == "Tank") { return 55; }
		if (type == "Helicopter") { return 90; }
		if (type == "Plane") { return 60; }
	}
	// setters
	void setMovementSpeed(int s) { movementSpeed = s; }
	void setSmallCanon(Canon& canon) { smallCanon = canon; }
	void setMediumCanon(Canon& canon) { mediumCanon = canon; }
	void setLargeCanon(Canon& canon) { largeCanon = canon; }
	void setPlayer(string a) { player = a; }
	void setlife(int x) { life = x; }
	void setAlign(string temp) { Align = temp; }

};

/*class Tank : public Vehicle {
	int width;
	int height;
	int radius;
	bool isSelected;
public:
	void setTank(int, int, int, int, Canon&, Canon&, Canon&);
	void setxy(int, int);
	void load();
};

class Helicopter : public Vehicle {
	int radius;
	bool isSelected;
	static Helicopter* instance;
public:
	void setHelicopter(int, int, Canon&, Canon&, Canon&, int);
	void setxy(int, int);
	void moveup();
	void movedown();
	void moveleft();
	void moveright();
	void load();
	Helicopter* getInstance() { return instance; }
};


class Plane : public Vehicle {
	int width;
	bool isSelected;
	static Plane* instance;
public:
	void setPlane(int, int, int, int, Canon&, Canon&, Canon&, int);
	void setxy(int, int);
	void moveup();
	void movedown();
	void moveleft();
	void moveright();
	void load();
	Plane* getInstance() { return instance; }
};*/


class Player {
protected:
	Vehicle playerVehicle;
	MovementControls playerControls;
	string name;
	int score;
public:
	Player() {
		playerVehicle;
		score = 0;
		name = "";
	}
	Player(Vehicle& vehicle) {
		playerVehicle = vehicle;
		name = "";
		score = 0;
	}
	void respawn();
	Vehicle& getVehicle() { return playerVehicle; }
	MovementControls& getcontrols() { return playerControls; }
	void setScore(int n) { score = n; }
	int getScore() { return score; }
	string getName() { return name; }
	void setName(string n) { name = n; }
};

class Person : public Player {
	int id;
	int highscore;
	int noOfPowerUps;
public:
	Person() {
		id = 0;
		highscore = 0;
		noOfPowerUps = 1;
	}
	void pickPopUpCanon(bool&);
	void usePowerUps();
	void setnoOfPowerUps(int num) { noOfPowerUps = num; }
	int getnoOfPowerUps() { return noOfPowerUps; }
};

class Bot : public Player {
	int intelligence;
	Point* path;
public:
	Bot();
	void AssignVehicle();
	void AlignCanon();
	void moveintelligently();
	void findpath();
	void setIntelligence(short intl) { intelligence = intl; }
	int getIntelligence() { return intelligence; }
	void increaseSpeed() { playerVehicle.setMovementSpeed(playerVehicle.getMovementSpeed() + 5); }
};

class Level {
	int id;
	Obstacle* obstacles;
	static int num;
	int numberOfObstacles;
	Vehicle* p1vehicle;
	Vehicle* p2vehicle;
	Point popUpLocation;
	int noOfBots;
	Bot* bots;
	bool passed;
	bool stop;
	short count;
public:
	Level();
	void createObstacles(int);		// int noOfObstacles to Create
	void popUpCanon(bool&);	// pop u canon during game play
	void load1Player();	// loads player1 vehicle
	void load2Player();	// loads player2 vehicle
	void operator=(Level&);	// overloaded deep copy
	void createBots();	// creates bots as per level
	// getters
	Vehicle& getVehicle() { return *p1vehicle; }
	Obstacle* getobstacles() { return obstacles; }
	Bot* getBot() { return bots; }
	int getNoOfBots() { return noOfBots; }
	bool getGameStoped() { return stop; }
	bool isPassed() { return passed; }
	Vehicle& getPlayer1Vehicle() { return *p1vehicle; }
	Vehicle& getPlayer2Vehicle() { return *p2vehicle; }
	Point& getPopUpLocation() { return popUpLocation; }

	// setters
	void setStop(bool p) { stop = p; }
	void setGamePassed(bool p) { passed = p; }
	void setcount(int num) { count = num; }
	
	// destructor
	~Level();
};

class Play {
	int score;
	Person player1;
	Person player2;
	Level level1;
	Level level2;
	Level level3;
	static Play* instance;
	short type;
	int currentLvl;
	bool isShowingNextLevel;
	bool isShowingRetry;
	bool isShowingWinner;
	bool gameRecordExist;
	short p1NoOfRespawn;
	short p2NoOfRespawn;
	int count;
public:
	Play(); // default constructor
	static Play* getInstance();	// returns singleton instance
	void updateLevels();	// upadtes levels by creating obstacles
	void begin1PlayerGame();	// starts loading 1 player game
	void begin2PlayerGame();	// starts loading 2 player game
	void showPausedScreen();	// shows the screen the game is paused
	void showWinningScreen();	// shows thw screen when the game is won
	void showNextLevelScreen();	// show screen when a level is cleared
	void gameRetry();	// retry from start 
	void resetPlay();	// resets play object to default state
	void increaseCurrentLvl() { currentLvl++; }	// increase level
	// setters
	void setCount(int num) { count = num; }
	void setType(short t) { type = t; }	// Set game type i.e. 1 for  Player 1 or 2 for Player 2 
	void setShowNextLvl(bool flag) { isShowingNextLevel = flag; }
	void setIsShowingWinner(bool flag) { isShowingWinner = flag; }
	void setIsShowingRetry(bool flag) { isShowingRetry = flag; }
	void setGameRecordExistance(bool flag) { gameRecordExist = flag; }
	// getters
	Level* getL1();
	Vehicle& getVehicle() { return level1.getVehicle(); }    // Eliminate this
	short getP1NoOfRespawn() { return p1NoOfRespawn; }
	short getP2NoOfRespawn() { return p2NoOfRespawn; }
	Person& getPlayer1() { return player1; }
	Person& getPlayer2() { return player2; }
	short getType() { return type; }
	Level& getLevel1() { return level1; }
	Level& getLevel2() { return level2; }
	Level& getLevel3() { return level3; }
	bool getShowNextLvl() { return isShowingNextLevel; }
	bool getIsShowingWinner() { return isShowingWinner; }
	bool getIsShowingRetry() { return isShowingRetry; }
	bool getGameRecordExistance() { return gameRecordExist; }
};

class Animation {
	int id;
	string type;
	// Animation :: Video
public:
	//void playAnimation();
};

class Setting {
	bool gameSoundOn;
	bool gameMusicOn;
public:
	Setting();// default constructor
	void changeVehicle(string, int);	// changes vehicle from list for player 1 and player 2
	void changeControls(int, int);	// changes controls from list of player 1 and player 2
	void showSoundSetting();	// shows sound settings
	void showVehicleSetting();	// shows vehicle settings page/ screen
	void showControlsSetting();	// shows controls settings screen
	void changeSoundCond() {// changes condition for game sound(stop or on)
		if (gameSoundOn) {
			gameSoundOn = false;
		}
		else {
			gameSoundOn = true;
		}
	}
	// getters
	bool getGameSound() { return gameSoundOn; }
	bool getMusicSound() { return gameSoundOn; }
};

class Game {
private:
	Player* players;
	Setting settings;
	static Game* instance;
	int count;
	string* ptr;
	int* highscores;
public:
	Game();		// Constructor
	static Game* getInstance();
	void showStartAnimation(int);    // Displays the Starting Animation of Game
	void showMenu();			// Displays the Menu to Select Select Options
	void showHighScores();	// shows highscores from text file
	void showInstructions();	// shows highscores from text file
	void showSettings();	// shows settings 
	void ShowCredits();	// show credits page
	void startPlayer1();	// starts player 1 game
	void startPlayer2();	// starts player2 game
	void startGame();	// updates the game
	// setters
	void setCount(int num) { count = num; }
	//getters
	int getCount() { return count; }
	Setting& getsetting() { return settings; }
};