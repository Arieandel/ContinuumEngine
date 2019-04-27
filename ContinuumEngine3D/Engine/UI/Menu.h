#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


class Menu
{
public:

	Menu(const Menu&) = delete;
	Menu(Menu&&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu& operator=(Menu&&) = delete;

	int showmenu(SDL_Surface* screen, TTF_Font* font);

private:
	Menu();
	~Menu();


	const int NUMMENU = 2;
	const char* labels[2]; //NUMMENU
	SDL_Surface* menus[2];//NUMMENU
	bool selected[2] = { 0,0 }; //NUMMENU




};

#endif