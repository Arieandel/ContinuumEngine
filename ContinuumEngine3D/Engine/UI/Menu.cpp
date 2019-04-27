#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
	SDL_FreeSurface(menus[0]);
	SDL_FreeSurface(menus[1]);
}



int Menu::showmenu(SDL_Surface* screen, TTF_Font* font)
{
	Uint32 time;
	int x, y;
	labels[0] =  "Continue";
	labels[1] = "Exit";

	SDL_Color color[2] = { {255,255,255},{255,0,0} };

	//menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	//menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
	SDL_Rect pos[2]; //NUMMENU
	pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[1].y = screen->clip_rect.h / 2 + menus[0]->clip_rect.h;

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				SDL_FreeSurface(menus[0]);
				SDL_FreeSurface(menus[1]);
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < NUMMENU; i += 1) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = 1;
							SDL_FreeSurface(menus[i]);
						//	menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
						}
					}
					else
					{
						if (selected[i])
						{
							selected[i] = 0;
							SDL_FreeSurface(menus[i]);
						//	menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < NUMMENU; i += 1) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						SDL_FreeSurface(menus[0]);
						SDL_FreeSurface(menus[1]);
						return i;
					}
				}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
					return 0;
				}
			}
		}
		for (int i = 0; i < NUMMENU; i += 1) {
			SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
		}

		//SDL_Flip(screen);
		if (1000 / 30 > (SDL_GetTicks() - time))
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
	}
}