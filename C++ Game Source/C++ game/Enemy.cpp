#include "Enemy.h"

Enemy::Enemy(float _x, float _y, SpawnPosition &_spawnPosition) : GameObject()  {
	x = _x;
	y = _y;
	patternTimer = 0;
	regularSpeed = 2;
	fastSpeed = 3;
	slowSpeed = 1;
	edgeCurveValue = 3;
	sineCurveValue = 3;
	switchValue = 0.5f;
	thresholdValue = 1;
	spawnPosition = _spawnPosition;

	srand(static_cast <unsigned> (time(0)));
	rndMovementPattern = rand() % 4 + 1;

	InitializeRectangle();
	texture = SOIL_load_OGL_texture(".\\Misc/Enemy.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void Enemy::InitializeRectangle() {
	rect.left = -0.3f;
	rect.top = -0.3f;
	rect.right = 0.3f;
	rect.bottom = 0.3;
}

void Enemy::DrawRectangle(Rect rect) {
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(rect.left, rect.bottom);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(rect.right, rect.bottom);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(rect.right, rect.top);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(rect.left, rect.top);

	glEnd();
}

void Enemy::Move(float gameTime) {
	if (spawnPosition == LeftSide) {
		if (rndMovementPattern == 1) {
			LeftRegularPattern(gameTime);
		}
		if (rndMovementPattern == 2) {
			LeftEdgytWavePattern(gameTime);
		}
		if (rndMovementPattern == 3) {
			LeftSpeedPattern(gameTime);
		}
		if (rndMovementPattern == 4) {
			LeftSineWavePattern(gameTime);
		}
	}
	if (spawnPosition == RightSide) {
		if (rndMovementPattern == 1) {
			RightRegularPattern(gameTime);
		}
		if (rndMovementPattern == 2) {
			RightEdgytWavePattern(gameTime);
		}
		if (rndMovementPattern == 3) {
			RightSpeedPattern(gameTime);
		}
		if (rndMovementPattern == 4) {
			RightSineWavePattern(gameTime);
		}
	}
	if (spawnPosition == TopSide) {
		if (rndMovementPattern == 1) {
			TopRegularPattern(gameTime);
		}
		if (rndMovementPattern == 2) {
			TopEdgyWaveVerticalPattern(gameTime);
		}
		if (rndMovementPattern == 3) {
			TopSpeedPattern(gameTime);
		}
		if (rndMovementPattern == 4) {
			TopSineWavePattern(gameTime);
		}
	}
	if (spawnPosition == BottomSide) {
		if (rndMovementPattern == 1) {
			BottomRegularPattern(gameTime);
		}
		if (rndMovementPattern == 2) {
			BottomEdgyWaveVerticalPattern(gameTime);
		}
		if (rndMovementPattern == 3) {
			BottomSpeedPattern(gameTime);
		}
		if (rndMovementPattern == 4) {
			BottomSineWavePattern(gameTime);
		}
	}
}

void Enemy::Render() {
	glPushMatrix();
	glTranslatef(x, y, 0);

	glBindTexture(GL_TEXTURE_2D, texture); 
	
	DrawRectangle(rect);

	glPopMatrix(); //Makes sure only this objects uses the current matrix any manipulation of the matrix is lost.
}

void Enemy::Update(float _gameTime) {
	Move(_gameTime);
}

#pragma region MovementPatternMethods
void Enemy::LeftRegularPattern(float gameTime) {
	x += regularSpeed * gameTime;
}
void Enemy::RightRegularPattern(float gameTime) {
	x -= regularSpeed * gameTime;
}
void Enemy::TopRegularPattern(float gameTime) {
	y -= regularSpeed * gameTime;
}
void Enemy::BottomRegularPattern(float gameTime) {
	y += regularSpeed * gameTime;
}
void Enemy::LeftEdgytWavePattern(float gameTime) {
	if (patternTimer < switchValue) {
		y += edgeCurveValue * gameTime;
		patternTimer += gameTime;
	}
	else {
		y -= edgeCurveValue * gameTime;
		patternTimer += gameTime;
	}
	if (patternTimer > thresholdValue) {
		patternTimer = 0;
	}

	x += regularSpeed * gameTime;
}
void Enemy::RightEdgytWavePattern(float gameTime) {
	if (patternTimer < switchValue) {
		y += edgeCurveValue * gameTime;
		patternTimer += gameTime;
	}
	else {
		y -= edgeCurveValue * gameTime;
		patternTimer += gameTime;
	}
	if (patternTimer > thresholdValue) {
		patternTimer = 0;
	}

	x -= regularSpeed * gameTime;
}
void Enemy::TopEdgyWaveVerticalPattern(float gameTime) {
	if (patternTimer < switchValue) {
		x += edgeCurveValue * gameTime;
		patternTimer += gameTime;
	}
	else {
		x -= edgeCurveValue * gameTime;
		patternTimer += gameTime;
	}
	if (patternTimer > thresholdValue) {
		patternTimer = 0;
	}

	y -= regularSpeed * gameTime;
}
void Enemy::BottomEdgyWaveVerticalPattern(float gameTime) {
	if (patternTimer < switchValue) {
		x += edgeCurveValue * gameTime;
		patternTimer += gameTime;
	}
	else {
		x -= edgeCurveValue * gameTime;
		patternTimer += gameTime;
	}
	if (patternTimer > thresholdValue) {
		patternTimer = 0;
	}

	y += regularSpeed * gameTime;
}
void Enemy::LeftSpeedPattern(float gameTime) {
	if (patternTimer < switchValue) {
		x += fastSpeed * gameTime;
		patternTimer += gameTime;
	}
	else {
		x += slowSpeed * gameTime;
		patternTimer += gameTime;
	}
	if (patternTimer > thresholdValue) {
		patternTimer = 0;
	}
}
void Enemy::RightSpeedPattern(float gameTime) {
	if (patternTimer < switchValue) {
		x -= fastSpeed * gameTime;
		patternTimer += gameTime;
	}
	else {
		x -= slowSpeed * gameTime;
		patternTimer += gameTime;
	}
	if (patternTimer > thresholdValue) {
		patternTimer = 0;
	}
}
void Enemy::TopSpeedPattern(float gameTime) {
	if (patternTimer < switchValue) {
		y -= fastSpeed * gameTime;
		patternTimer += gameTime;
	}
	else {
		y -= slowSpeed * gameTime;
		patternTimer += gameTime;
	}
	if (patternTimer > thresholdValue) {
		patternTimer = 0;
	}
}
void Enemy::BottomSpeedPattern(float gameTime) {
	if (patternTimer < switchValue) {
		y += fastSpeed * gameTime;
		patternTimer += gameTime;
	}
	else {
		y += slowSpeed * gameTime;
		patternTimer += gameTime;
	}
	if (patternTimer > thresholdValue) {
		patternTimer = 0;
	}
}
void Enemy::LeftSineWavePattern(float gameTime) {
	y += sineCurveValue * sin(x * 3.14f / 2) * gameTime;
	x += regularSpeed * gameTime;
}
void Enemy::RightSineWavePattern(float gameTime) {
	y += sineCurveValue * sin(x * 3.14f / 2) * gameTime;
	x -= regularSpeed * gameTime;
}
void Enemy::TopSineWavePattern(float gameTime) {
	x += sineCurveValue * sin(y * 3.14 / 2) * gameTime;
	y -= regularSpeed * gameTime;
}
void Enemy::BottomSineWavePattern(float gameTime) {
	x += sineCurveValue * sin(y * 3.14 / 2) * gameTime;
	y += regularSpeed * gameTime;
}
#pragma endregion

Enemy::~Enemy() {
	glDeleteTextures(1, &texture);
}