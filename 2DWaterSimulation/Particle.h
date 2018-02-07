#include <SDL.h>
#include "Vec2.h"

class Particle
{
private:
	Vec2 position;
	Vec2 velocity;
	int size;
	float speed;
	float angleRADS;

	SDL_Renderer *render;


public:

	Particle(Vec2 position, int size, float speed, float angle, SDL_Renderer *passedRenderer);
	~Particle();
	void Update(float deltaTs);
	void Draw();
	Vec2 GetPosition();
	void SetDifference(float diff);
	int GetSpringID();
};