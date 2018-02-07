#include <SDL.h>
#include "Vec2.h"

class Bubble
{
private:
	Vec2 position;
	Vec2 velocity;
	int size;
	float speed;
	float angleRADS;

	SDL_Renderer *render;


public:

	Bubble(Vec2 position, int size, float speed, float angle, SDL_Renderer *passedRenderer);
	~Bubble();
	void Update(float deltaTs);
	void Draw();
	Vec2 GetPosition();

};