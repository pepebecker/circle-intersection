#include <math.h>
#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer* renderer;

int mouseX = 0, mouseY = 0;
float shoulderX = 320;
float shoulderY = 240;
float elbowX;
float elbowY;
float handX;
float handY;
float shoulderR = 75;
float handR = 100;

bool running = true;

void DrawCircle(int h, int k, float r, bool point = false) {
  for (float x = -r; x < r; x+= 0.01)
  {
    int y = sqrt(r * r - x * x);
    SDL_RenderDrawPoint(renderer, h + x, k + y);
    SDL_RenderDrawPoint(renderer, h + x, k - y);
  }

  if (point)
  {
    for (int y = -1; y <= 1; y++)
    {
      SDL_RenderDrawPoint(renderer, h-1, k+y);
      SDL_RenderDrawPoint(renderer, h  , k+y);
      SDL_RenderDrawPoint(renderer, h+1, k+y);
    }
  }
}

int main(int argc, char const *argv[])
{
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			if (event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mouseX, &mouseY);
            }
		}

		handX = mouseX;
		handY = shoulderY;

		if (handX > shoulderX + shoulderR + handR)
			handX = shoulderX + shoulderR + handR;

		if (handX < shoulderX - shoulderR - handR)
			handX = shoulderX - shoulderR - handR;

		float distanceX = handX - shoulderX;

		elbowX = handX - (pow(distanceX, 2) - pow(shoulderR, 2) + pow(handR, 2)) / (2 * distanceX);

		elbowY = handY - -abs(sqrt( (-distanceX + shoulderR - handR) * (-distanceX - shoulderR + handR) * (-distanceX + shoulderR + handR) * (distanceX + shoulderR + handR) ) / (distanceX * 2));

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		DrawCircle(shoulderX, shoulderY, shoulderR, 1);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		DrawCircle(handX, handY, handR, 1);

		if (abs(handX - shoulderX) >= abs(shoulderR - handR)) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			DrawCircle(elbowX, elbowY, 1, 1);
			SDL_RenderDrawLine(renderer, shoulderX, shoulderY, elbowX, elbowY);
			SDL_RenderDrawLine(renderer, handX, handY, elbowX, elbowY);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
