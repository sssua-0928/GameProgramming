#include "Intro.h"

Intro::Intro() {
	SDL_Surface* bg_surface = IMG_Load("../../Resources/bg_intro.jpg");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source = { 0,0, 600,600 };
	bg_destination = { 0, 0, bg_source.w, bg_source.h };

	SDL_Surface* start_surface = IMG_Load("../../Resources/1_start.jpg");
	start_texture = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	SDL_FreeSurface(start_surface);
	start_source = { 0,0,222,59 };
	start_destination = { bg_destination.w/2-111, bg_destination.h/2+100, start_source.w, start_source.h };
}

Intro::~Intro() {
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
}

void Intro::HandleEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				int x, y;
				SDL_GetMouseState(&x, &y);

				// 버튼을 누르면 게임 시작(Ingame)
				if ( x >= start_destination.x && x<=(start_destination.x + start_destination.w) &&
					y >= start_destination.y && y <= start_destination.y + start_destination.h) {
					g_current_game_phase = PHASE_INGAME;	
				}
			}
			break;

		default:
			break;
		}
	}
}

void Intro::Update() {

}

void Intro::Render() {
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
	SDL_RenderCopy(g_renderer, start_texture, &start_source, &start_destination);
	SDL_RenderPresent(g_renderer);
}