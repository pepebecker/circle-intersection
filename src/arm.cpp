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

struct Point
{
	float x;
	float y;
};

struct CircleIntersection
{
	Point a;
	Point b;
	bool success;
};

CircleIntersection getIntersection(float x0, float y0, float r0, float x1, float y1, float r1) {
	float a, dx, dy, d, h, rx, ry;
	float x2, y2;

	// dx and dy are the vertical and horizontal distances between
	// the circle centers.
	dx = x1 - x0;
	dy = y1 - y0;

	// Determine the straight-line distance between the centers.
	d = sqrt((dy*dy) + (dx*dx));

	// Check for solvability.
	if (d > (r0 + r1)) {
		// no solution. circles do not intersect.
		return {0, 0, false};
	}
	if (d < fabs(r0 - r1)) {
		// no solution. one circle is contained in the other
		return {0, 0, false};
	}

	// 'point 2' is the point where the line through the circle
	// intersection points crosses the line between the circle
	// centers.  
	 

	// Determine the distance from point 0 to point 2.
	a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

	// Determine the coordinates of point 2.
	x2 = x0 + (dx * a/d);
	y2 = y0 + (dy * a/d);

	// Determine the distance from point 2 to either of the
	// intersection points.
	h = sqrt((r0*r0) - (a*a));

	// Now determine the offsets of the intersection points from
	// point 2.
	rx = -dy * (h/d);
	ry = dx * (h/d);

	// Determine the absolute intersection points.
	float xi = x2 + rx;
	float xi_prime = x2 - rx;
	float yi = y2 + ry;
	float yi_prime = y2 - ry;

	return {{xi, yi}, {xi_prime, yi_prime}, true};
}

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
	window = SDL_CreateWindow("Inverse Kinematics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	SDL_ShowCursor(SDL_DISABLE);

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
		handY = mouseY;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		DrawCircle(shoulderX, shoulderY, shoulderR, 1);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		DrawCircle(handX, handY, handR, 1);

		CircleIntersection intersection = getIntersection(shoulderX, shoulderY, shoulderR, handX, handY, handR);

		if (intersection.success)
		{
			if (true)
			// if (intersection.a.y > intersection.b.y)
			{
				elbowX = intersection.a.x;
				elbowY = intersection.a.y;
			} else {
				elbowX = intersection.b.x;
				elbowY = intersection.b.y;
			}

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
