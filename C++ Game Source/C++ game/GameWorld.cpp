#include "GameWorld.h"

GameWorld::GameWorld() {
	srand(static_cast<unsigned>(time(0)));
	spawnPosition = NoSide;
	enemySpawnInterval = 0.5f;
	rndSpawnPoint = rand() % 10 - 5;
	oldTimeSinceStart = 0;
	spawnEnemyTimer = 0;
	glEnable(GL_TEXTURE_2D); //Enable texture mapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Specify how textures should be interpolized over surfaces 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	player = new Player(0, 0, &enemies);
}

void GameWorld::Keyboard(unsigned char key, int x, int y) {
	player->KeyboardInput(key);
}

void GameWorld::SpawnLocator(int index) {
	switch (index) {
	case 1:
		spawnPosition = LeftSide;
		break;
	case 2:
		spawnPosition = RightSide;
		break;
	case 3:
		spawnPosition = TopSide;
		break;
	case 4:
		spawnPosition = BottomSide;
		break;
	default:
		break;
	}
}

void GameWorld::SpawnNewEnemy(float deltaTime) {
	rndSpawnPoint = rand() % 10 - 5;
	float positiveAxis = 5.5f;
	float negativeAxis = -5.5f;

	if (spawnEnemyTimer < enemySpawnInterval) {
		spawnEnemyTimer += deltaTime;
	}
	else {
		spawnEnemyTimer = 0;

		if (spawnPosition == LeftSide) {
			enemies.push_back(new Enemy(negativeAxis, rndSpawnPoint, spawnPosition));
		}
		if (spawnPosition == RightSide) {
			enemies.push_back(new Enemy(positiveAxis, rndSpawnPoint, spawnPosition));
		}
		if (spawnPosition == TopSide) {
			enemies.push_back(new Enemy(rndSpawnPoint, positiveAxis, spawnPosition));
		}
		if (spawnPosition == BottomSide) {
			enemies.push_back(new Enemy(rndSpawnPoint, negativeAxis, spawnPosition));
		}
	}
}

void GameWorld::ManageVectors() {
	int enemyDeletionBorder = 7;

	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->x > enemyDeletionBorder || enemies[i]->x < -enemyDeletionBorder || enemies[i]->y > enemyDeletionBorder || enemies[i]->y < -enemyDeletionBorder) {
			delete enemies[i];
			enemies[i] = 0;
			enemies.erase(enemies.begin() + i);
			std::cout << "Enemy pointer destroyed." << std::endl;
		}
	}
}

void GameWorld::Progress() {
	rndLocationSetter = rand() % 4 + 1;
	SpawnLocator(rndLocationSetter);

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float time = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	deltaTime = time / 1000;

	player->Update(deltaTime);
	SpawnNewEnemy(deltaTime);

	for (Enemy *nme : enemies) {
		nme->Update(deltaTime);
	}

	ManageVectors();
}

void GameWorld::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); //loads the identity matrix on the matrix stack - essentially resetting any other matrixes
	glTranslatef(0.0f, 0.0f, -12.0f);

	for (Enemy *nme : enemies) {
		nme->Render();
	}

	player->Render();

	glutSwapBuffers();
	glFinish();
	glFlush();
	glutPostRedisplay();
}

void GameWorld::Update() {
	Progress();
	Render();
}

GameWorld::~GameWorld() {
	for (Enemy *nme : enemies) {
		delete nme;
		nme = 0;
	}

	enemies.clear();
	delete player;
	player = 0;
}
