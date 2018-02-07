#include <SDL.h>
#include "Vec2.h"

class Spring
{
private:
	Vec2 position;
	Vec2 targetHeight;
	float speed;
	SDL_Renderer *render;

public:

	Spring(Vec2 position, SDL_Renderer *passedRenderer);
	~Spring();
	void Update(float dampening, float tension, float deltaTs);
	void Draw();
	Vec2 GetPosition();
	float GetSpeed();
	void UpdateSpeed(float value);
	void UpdatePosition(float value);
};