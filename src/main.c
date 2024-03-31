#define _CRT_SECURE_NO_WARNINGS

#include "SDL.h"
#ifndef SDL_h_
#include <SDL2/SDL.h>
#endif /* ifndef _SDL_h */

#include <stdio.h>

// Коды ошибок
enum Errors { NOERR, SDLERR, NOPIC };

// Параметры окна
#define TITLE "Жигунов СН"
#define HSIZE 700
#define VSIZE 800
#define BG_COLOUR 0xFF, 0xC0, 0x00
#define KEY_COLOUR 0xFF, 0xFF, 0xFF

int CreateWindow(SDL_Window **window, SDL_Surface **surface, const char *name, int x, int y, int w, int h,
				 Uint32 flags);

int main(void)
{
	SDL_Window *win = NULL;
	SDL_Surface *surf = NULL;

	// Ввод названия файла
	char fname[32];
	printf("Введите название изображения: ");
	scanf("%31s", fname);
	// Проверка, существует ли файл
	FILE *f = fopen(fname, "rb");
	if (!f)
	{
		puts("Такого изображения нет!");
		return NOPIC;
	}
	fclose(f);

	// Запуск SDL, создание окна и поверхности
	if (CreateWindow(&win, &surf, TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HSIZE, VSIZE,
					 SDL_WINDOW_SHOWN))
	{
		printf("Ошибка SDL: %s. Завершение работы", SDL_GetError());
		return SDLERR;
	}

	// Заливка окна жёлтым
	SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, BG_COLOUR));
	SDL_UpdateWindowSurface(win);
	SDL_Delay(1000);

	// Вставка картинки
	SDL_Surface *image = NULL;
	SDL_Rect pic;
	// Открытие картинки, проверка этого
	if (!(image = SDL_LoadBMP(fname)))
	{
		// Если не удалось открыть изображение, осуществляется прекращение работы
		printf("Не удалось открыть изображение! Завершение работы!\n");

		SDL_DestroyWindow(win);
		SDL_Quit();
		return NOPIC;
	}
	// Задаём расположение картинки
	pic.x = 160, pic.y = 160;

	//"Вырезаем" фон
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, KEY_COLOUR));
	SDL_BlitSurface(image, NULL, surf, &pic); // Вставка картинки
	SDL_UpdateWindowSurface(win);			  // Обновление окна
	SDL_Delay(1000);						  // Задержка окна

	// Штатное завершение работы
	SDL_DestroyWindow(win);
	SDL_Quit();
	return NOERR;
}

/*Вызываем SDL, создаём окно window с названием name, координатами x и y,
размерами w и h, некоторым набором флагов и поверхность surface в нём */
int CreateWindow(SDL_Window **window, SDL_Surface **surface, const char *name, int x, int y, int w, int h, Uint32 flags)
{
	if (SDL_Init(SDL_INIT_VIDEO) || !(*window = SDL_CreateWindow(name, x, y, w, h, flags)) ||
		!(*surface = SDL_GetWindowSurface(*window)))
	{
		return SDLERR;
	}
	/*else*/ return NOERR;
}
