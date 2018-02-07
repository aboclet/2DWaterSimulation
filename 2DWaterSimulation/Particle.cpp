#include "Particle.h"

const float PI = 3.1415926535897932384626433832795f;


Particle::Particle(Vec2 position, int size, float speed, float angle, SDL_Renderer *passedRenderer)
{
	render = passedRenderer;

	this->position = position;
	this->speed = speed;
	this->size = size;
	angleRADS = angle * PI / 180.0f;
	velocity.x = speed * cos(angleRADS);
	velocity.y = speed * sin(angleRADS);
}

Particle::~Particle()
{

}

void Particle::Update(float deltaTs)
{
	const float Gravity = 9.8f;
	velocity.y += Gravity;
	position.x += velocity.x * deltaTs;
	position.y += velocity.y * deltaTs;
}

void Particle::Draw()
{
	SDL_Rect fillRect = { position.x, position.y, size, size };
	//SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
	SDL_SetRenderDrawColor(render, 10, 105, 148, 0);
	SDL_RenderFillRect(render, &fillRect);
}

Vec2 Particle::GetPosition()
{
	return position;
}
