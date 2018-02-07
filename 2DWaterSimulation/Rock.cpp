#include "Rock.h"

const float gravity = 9.8f;

Rock::Rock(SDL_Renderer *renderer)
{
	this->renderer = renderer;
	velocity = { 0.0f, 0.0f };
	
}

Rock::~Rock()
{

}

void Rock::Update(float deltaTs)
{
	if (position.y > 500)
	{
		velocity.y *= 0.84f;
	}

	velocity.y += gravity;
	position.y += velocity.y * deltaTs;
}

Vec2 Rock::GetPosition()
{
	return position;
}

void Rock::SetPosition(Vec2 position)
{
	this->position = position;
}

void Rock::SetVelocity(Vec2 velocity)
{
	this->velocity = velocity;
}

void Rock::Draw()
{
	SDL_Rect fillRect = { position.x, position.y, 50, 50};
	SDL_SetRenderDrawColor(renderer, 160, 160, 160, 0);
	SDL_RenderFillRect(renderer, &fillRect);
}