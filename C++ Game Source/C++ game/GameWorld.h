#pragma once
#include <time.h>
#include <stdlib.h>
#include "Enemy.h"
#include "Player.h"
#include "GameObject.h"
#include <vector>
#include <ctime>
#include <irrKlang.h>
#include <fstream>
#include <math.h>

#define SCREENWIDTH 1042
#define SCREENHEIGHT 768
#define SCREENPOSITION_X 300
#define SCREENPOSITION_Y 100

class GameWorld
{
// Variables
public:

private:
	SpawnPosition spawnPosition; // Stores the direction an enemy is gonna spawn from.
	std::vector<Enemy*> enemies; // Pointer vector storing all instances of enemies.
	//Player* player; // A pointer storing an instance of the player.
	float oldTimeSinceStart; // Used when calculating delta time.
	float deltaTime; // Stores delta time.
	float enemySpawnInterval; // Stores the spawn frequence of the enemy.
	int rndLocationSetter; // Stores a random number betweeen 1 and 4. Used to determine the state of the spawnPosition enum.
	float rndSpawnPoint; // Stores a random number between -5 to 5. Used to find a random spawn position on the x or y axis.
	float spawnEnemyTimer; // Used to make sure we are spawn an enemy at the frequency of enemySpawnInterval variable.

// Functions
public:
	GameWorld();
	Player* player; // A pointer storing an instance of the player.
	void Keyboard(unsigned char key, int x, int y); // Runs the keyboard input of the player.
	void Progress(); // Used to find delta time, run methods, update player/enemies. Rename to Update?
	void Render(); // Handles rendering.
	void Update(); // Updates neccesarry logic.

	~GameWorld();

private:
	void SpawnLocator(int index); // Used to determine the state of the spawnPosition enum.
	void SpawnNewEnemy(float deltaTime); // Used to spawn new enemies with new logic and stores them in the enemies vector.
	void ManageVectors(); // Used to clean the enemies vector when an enemy get outside of the game window.
};