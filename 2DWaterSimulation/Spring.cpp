#include "Spring.h"

const Vec2 gravity = { 0.0f, -9.8f };

Spring::Spring(Vec2 position, SDL_Renderer *passedRenderer)
{
	render = passedRenderer;
	speed = 0;
	this->position.x = position.x + 5;
	this->position.y = position.y + 5;
	targetHeight = position;

}

Spring::~Spring()
{

}

void Spring::Update(float dampening, float tension, float deltaTs)
{
	float x = targetHeight.y - position.y;
	speed += (tension * x) - (speed * dampening);
	position.y += speed;

}

void Spring::Draw()
{
	SDL_Rect fillRect = { position.x, position.y, 10, 780 - position.y };
	SDL_SetRenderDrawColor(render, 10, 105, 148, 0);
	SDL_RenderFillRect(render, &fillRect);
}

Vec2 Spring::GetPosition()
{
	return position;
}

float Spring::GetSpeed()
{
	return speed; 
}

void Spring::UpdatePosition(float value)
{
	position.y += value;
}

void Spring::UpdateSpeed(float value)
{
	speed += value;
}

