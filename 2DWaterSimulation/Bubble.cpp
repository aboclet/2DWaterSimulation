#include "Bubble.h"

const float PI = 3.1415926535897932384626433832795f;


Bubble::Bubble(Vec2 position, int size, float speed, float angle, SDL_Renderer *passedRenderer)
{
	render = passedRenderer;

	this->position = position;
	this->position.x = position.x + 20;
	this->speed = speed;
	this->size = size;
	angleRADS = angle * PI / 180.0f;
	velocity.x = speed * cos(angleRADS);
	velocity.y = speed * sin(angleRADS);
}

Bubble::~Bubble()
{

}

void Bubble::Update(float deltaTs)
{
	position.x += velocity.x * deltaTs;
	position.y += velocity.y * deltaTs;
}

void Bubble::Draw()
{
	
	SDL_Rect fillRect = { position.x, position.y, size, size };
	SDL_SetRenderDrawColor(render, 198, 252, 255, 0);
	SDL_RenderFillRect(render, &fillRect);
}

Vec2 Bubble::GetPosition()
{
	return position;
}
