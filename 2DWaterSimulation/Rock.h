#include <SDL.h>
#include "Vec2.h"


class Rock
{
private:

	Vec2 position;
	Vec2 velocity;

	float angleRADS;

	SDL_Renderer *renderer;


public:

	Rock(SDL_Renderer *renderer);
	~Rock();
	void Update(float deltaTs);
	void Draw();
	Vec2 GetPosition();
	void SetPosition(Vec2 position);
	void SetVelocity(Vec2 velocity);
};