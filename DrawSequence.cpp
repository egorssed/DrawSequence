#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <math.h>
#include <stdbool.h>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;




void GetPoint(double *x, double *r)
{
	*x = (*x)*exp((*r)*(1 - (*x)));
}

void Draw(SDL_Renderer * ren, int x1, int y1, int R, int G, int B)
{
	double a, l = 0.5;
	for (a = -l; a <= l; a++)
	{
		SDL_SetRenderDrawColor(ren, R, G, B, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(ren, x1 - (int)(sqrt(l*l - a * a)), y1 + (int)(a), x1 + (int)(sqrt(l*l - a * a)), y1 + (int)(a));
	}
}








int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

	//Создание окна
	SDL_Window *win = SDL_CreateWindow("deviation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return 1;
	}


	//Получаем поверхность
	SDL_Surface *surface = SDL_GetWindowSurface(win);

	//Заполняем ее белым цветом
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 250, 240));

	//Обновляем поверхность
	SDL_UpdateWindowSurface(win);

	SDL_SetRenderDrawColor(ren, 255, 250, 240, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);

	//Начальные условия
	double x = 0.2;
	double r = 0.2;
	int N = 0;
	int p;
	//Рисование Сетки

	{
		for (p = 50; p <= SCREEN_HEIGHT - 50; p = p + 10)
		{
			SDL_SetRenderDrawColor(ren, 255, 165, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(ren, 0 + 50, p, SCREEN_WIDTH - 50, p);
		}
		for (p = 50; p <= SCREEN_HEIGHT - 50; p = p + 100)
		{
			SDL_SetRenderDrawColor(ren, 205, 102, 29, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(ren, 0 + 50, p, SCREEN_WIDTH - 50, p);
		}
		for (p = 50; p <= SCREEN_WIDTH - 50; p = p + 10)
		{
			SDL_SetRenderDrawColor(ren, 255, 165, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(ren, p, 50, p, SCREEN_HEIGHT - 50);
		}
		for (p = 50; p <= SCREEN_WIDTH - 50; p = p + 100)
		{
			SDL_SetRenderDrawColor(ren, 205, 102, 29, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(ren, p, 50, p, SCREEN_HEIGHT - 50);
		}
	}
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ren, 45, 350, SCREEN_WIDTH - 30, 350);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ren, 50, 0, 50, SCREEN_HEIGHT - 50);
	SDL_RenderPresent(ren);


	//периодичность

	x = 0.2;
	for (r = 0; r <= 10; r += 0.001) {
		//r = 0.9 - (0.17 / i);
		x = 0.2;
		for (int j = 0; j < 1000; j++) {
			GetPoint(&x, &r);
		}
		for (N = 0; N <= 512; N++)
		{
			Draw(ren, (int)(r * 200) + 50, 350 - (int)(x * 100), 0, 0, 255);
			GetPoint(&x, &r);
		}

	}

	

	SDL_RenderPresent(ren);
	SDL_Event event;

	bool run = true;

	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				run = false;
				break;
			}
		}
	}


	SDL_DestroyRenderer(ren);
	//И удаляем из памяти окно
	SDL_DestroyWindow(win);
	//Выход из SDL
	SDL_Quit();

	return 0;

}