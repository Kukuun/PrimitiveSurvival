#include "Player.h"

Player::Player(float _x, float _y, std::vector<Enemy*>* _enemies) : GameObject() {
	x = _x;
	y = _y;
	enemies = _enemies;
	direction = None;
	InitializeRectangle();
	texture = SOIL_load_OGL_texture(".\\Misc/Player.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void Player::InitializeRectangle() {
	rect.left = -0.2f;
	rect.top = -0.2f;
	rect.right = 0.2f;
	rect.bottom = 0.2f;
}

void Player::DrawRectangle(Rect rect) {
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(rect.left, rect.bottom);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(rect.right, rect.bottom);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(rect.right, rect.top);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(rect.left, rect.top);

	glEnd();
}

void Player::KeyboardInput(unsigned char key) {
	switch (key) {
	case 'w': case 'W':
		direction = Up;
		break;
	case 's': case 'S':
		direction = Down;
		break;
	case 'a': case 'A':
		direction = Left;
		break;
	case 'd': case 'D':
		direction = Right;
		break;
	default:
		break;
	}
}

void Player::Move(float _gameTime) {
	float positiveWindowBoundary = 4.8f; // X/Y positive boundaries with glut is 5. 4.8 fits with the size of the texture.
	float negativeWindowBoundary = -4.8f; // X/Y negative boundaries with glut is 5. 4.8 fits with the size of the texture.
	float movementSpeed = 5.0f;

	switch (direction) {
	case Up:
		if (y < positiveWindowBoundary) { 
			y += movementSpeed * _gameTime;
		}
		break;
	case Down:
		if (y > negativeWindowBoundary) { 
			y -= movementSpeed * _gameTime;
		}
		break;
	case Left:
		if (x > negativeWindowBoundary) {
			x -= movementSpeed * _gameTime;
		}
		break;
	case Right:
		if (x < positiveWindowBoundary) {
			x += movementSpeed * _gameTime;
		}
		break;
	default:
		break;
	}
}

void Player::Render() {
	glPushMatrix(); 
	glTranslatef(x, y, 0);

	glBindTexture(GL_TEXTURE_2D, texture); 

	DrawRectangle(rect);

	glPopMatrix(); 
}

void Player::OnCollision() {
	for (Enemy *nme : *enemies) {
		if ((rect.left + x) < (nme->rect.right + nme->x) && (rect.right + x) > (nme->rect.left + nme->x) && (rect.top + y) < (nme->rect.bottom + nme->y) && (rect.bottom + y) > (nme->rect.top + nme->y)) {
			SaveLatestRoundTimeToFile();
			exit(0);
		}
	}
}

void Player::DisplayTimeToConsole(float gameTime) {
	int aMinute = 60;
	survivedInSeconds += 1.0f * gameTime;

	if (survivedInSeconds > aMinute) {
		survivedInSeconds = 0;
		survivedInMinutes += 1;
	}
}

void Player::SaveLatestRoundTimeToFile() {
	writeTimeToFile.open("_RoundTime.txt");
	writeTimeToFile << "In the latest try you survived for: " << std::endl;
	std::cout << std::endl;
	writeTimeToFile << survivedInMinutes << " minute(s) and " << round(survivedInSeconds) << " second(s)." << std::endl;
	writeTimeToFile.close();
}

void Player::Update(float _gameTime) {
	Move(_gameTime);
	DisplayTimeToConsole(_gameTime);
	OnCollision();
}

Player::~Player() {
	delete enemies;
	glDeleteTextures(1, &texture);
}