#include <SDL.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "Particle.h"
#include "Spring.h"
#include "Rock.h"
#include "Bubble.h"

void Splash(std::vector<Spring>&springs, std::vector<Particle>&particles, std::vector<Rock>&rocks, int target, float speed, SDL_Renderer *renderer);
void Collision(std::vector<Spring>&springs, std::vector<Particle>&particles, Rock *rock, bool &bHasRockHitWater, SDL_Renderer *renderer);
void CreateBubbles(std::vector<Bubble>&bubbles, Rock *rock, SDL_Renderer *renderer);

int count = 0;

int main(int argc, char *argv[])
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}

	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 1024;
	int winHeight = 780;
	SDL_Window *window = SDL_CreateWindow("Water",
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	unsigned int lastTime = SDL_GetTicks();
	float deltaTs = 0.0f;

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	std::vector<Particle>particles;
	std::vector<Spring>springs;
	std::vector<Bubble>bubbles;
	
	Rock *rock = nullptr;


	float tension = 0.025f;
	float dampening = 0.025f;
	float spread = 0.25f;

	float mouseX;
	float mouseY;
	Vec2 position;

	bool bIsRockAlive = false;
	bool bHasRockHitWater = false;

	srand(time(0));

	for (int x = -10; x < 1030; x += 10)
	{
		
		Vec2 position = {x, 500};
		springs.push_back(Spring(position, renderer));
	}

	

	bool go = true;
	while (go)
	{

		unsigned int current = SDL_GetTicks();

		deltaTs = (float)(current - lastTime) / 1000.0f;
		
		lastTime = current;

		SDL_Event incomingEvent;

		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{
				case SDL_QUIT:

				go = false;
				break;


				case SDL_MOUSEMOTION:
				{
					mouseX = incomingEvent.motion.x;
					mouseY = incomingEvent.motion.y;
				}
				break;

				case SDL_MOUSEBUTTONDOWN:
				{
					switch (incomingEvent.button.button)
					{

						case SDL_BUTTON_LEFT:
						{
							if (bIsRockAlive == false)
							{
								rock = new Rock(renderer);
								position = { mouseX, mouseY };								
								rock->SetPosition(position);
								rock->SetVelocity({ 0.0f, 0.0f });
								count = 0;
								bIsRockAlive = true;
								bHasRockHitWater = false;
							}												
						}
						break;

					}
				}
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 135, 206, 235, 0);
		SDL_RenderClear(renderer);



		for (unsigned int i = 0; i < springs.size(); i++)
		{
			springs[i].Update(dampening, tension, deltaTs);
			springs[i].Draw();
		}

		for (unsigned int i = 0; i < particles.size(); i++)
		{
			particles[i].Update(deltaTs);
			particles[i].Draw();
			if (particles[i].GetPosition().y > 800)
			{
				particles.erase(particles.begin() + i);
			}
		}

		for (unsigned int i = 0; i < bubbles.size(); i++)
		{
			bubbles[i].Update(deltaTs);
			bubbles[i].Draw();
			if (bubbles[i].GetPosition().y < 500)
			{
				bubbles.erase(bubbles.begin() + i);
			}
		}


		if (bIsRockAlive == true)
		{
			rock->Update(deltaTs);
			rock->Draw();
			if (rock->GetPosition().y > 500)
			{
				Collision(springs, particles, rock, bHasRockHitWater, renderer);
				CreateBubbles(bubbles, rock, renderer);
			}
			if (rock->GetPosition().y >= 800)
			{
				bIsRockAlive = false;
			}
		}
		else if (bIsRockAlive == false)
		{
			rock = nullptr;
		}
		


		
		

		SDL_Rect sun = { 800, 20, 100, 100 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &sun);

		float left[104];
		float right[104];

		for (int i = 0; i < 8; i++)
		{
			for (unsigned int j = 0; j < springs.size(); j++)
			{
				if (j > 0)
				{
					left[j] = spread * (springs[j].GetPosition().y - springs[j - 1].GetPosition().y);
					springs[j - 1].UpdateSpeed(left[j]);
				}
				if (j < springs.size() - 1)
				{
					right[j] = spread * (springs[j].GetPosition().y - springs[j + 1].GetPosition().y);
					springs[j + 1].UpdateSpeed(right[j]);
				}
			}

			for (unsigned int j = 0; j < springs.size(); j++)
			{
				if (j > 0)
				{
					springs[j - 1].UpdatePosition(left[j]);
				}
				if (j < springs.size() - 1)
				{
					springs[j + 1].UpdatePosition(right[j]);
				}
			}
		}

		SDL_RenderPresent(renderer);

		if (deltaTs < (1.0f / 50.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void Splash(std::vector<Spring>&springs, std::vector<Particle>&particles, int target, float speed, SDL_Renderer *renderer)
{
	srand(time(0));
	springs[target].UpdateSpeed(speed);
	for (int i = 0; i < 20; i++)
	{
		particles.push_back(Particle(springs[target].GetPosition(), (rand() % 10) + 10, (rand() % 300) + 200, rand() % (325 + 1 - 225) + 225, renderer));
	}
}

void Collision(std::vector<Spring>&springs, std::vector<Particle>&particles, Rock *rock, bool &bHasRockHitWater, SDL_Renderer *renderer)
{
	for (unsigned int i = 0; i < springs.size(); i++)
	{
		for (int x = springs[i].GetPosition().x; x < springs[i].GetPosition().x + 10; x++)
		{
			if (rock->GetPosition().x == x && bHasRockHitWater == false)
			{
				Splash(springs, particles, i + 2, 300.0f, renderer);
				bHasRockHitWater = true;
			}
		}
	}
}

void CreateBubbles(std::vector<Bubble>&bubbles, Rock *rock, SDL_Renderer *renderer)
{
		bubbles.push_back(Bubble(rock->GetPosition(), (rand() % 10) + 10, 50, rand() % (325 + 1 - 225) + 225, renderer));
}
