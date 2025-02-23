#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "constant.h"
struct GameState; //forward declaration

enum EntityType
{
	UNDEFINED,
	PLAYER,
	BULLET,
	ENEMY
};

class Entity
{
public:
	Entity() {};
	~Entity() {};

	EntityType getType() { return mType; }
	bool isAlive() { return mIsAlive; }
	SDL_FPoint getCenter() { return { mTexRect.x + mTexRect.w / 2, mTexRect.y + mTexRect.h / 2 }; }
	SDL_FRect getHitbox() { return mHitboxRect; }
	SDL_FRect getTexRect() { return mTexRect; }
	float getRadianAngle() { return mAngleRad; }
	int getAngle() { return mAngle; }
	void isCollisionWith(Entity* other) {
		SDL_FRect otherHitbox = other->getHitbox();
		if (SDL_HasIntersectionF(&mHitboxRect, &otherHitbox))
		{
			onCollision(other->getType());
			other->onCollision(mType);
		}
	}

	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void onCollision(EntityType type) = 0;
protected:
	void checkOutsideScreen() {
		if (mTexRect.x < 0 || mTexRect.x + mTexRect.w > SCREEN_WIDTH || mTexRect.y < 0 || mTexRect.y + mTexRect.h > SCREEN_HEIGHT)
			mIsAlive = false;
	}

	EntityType mType = EntityType::UNDEFINED;

	GameState* mGameState;

	SDL_Texture* mTexture;
	SDL_FRect mHitboxRect;
	SDL_FRect mTexRect;
	float mAngleRad;
	int mAngle;
	bool mIsAlive = true;

	const float mSpeed = 0.0;
	const float mHitboxSize = 50.0;
	const float mTexSize = 50.0;
	const char* mTexturePath;
};

#include "game.h"