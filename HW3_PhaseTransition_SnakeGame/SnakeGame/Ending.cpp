#include "Ending.h"

Ending::Ending() {
	SDL_Surface* bg_surface = IMG_Load("../../Resources/bg_ending.jpg");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source = { 0,0,600,600 };
	bg_destination = { 0, 0, bg_source.w, bg_source.h };

	SDL_Surface* start_surface = IMG_Load("../../Resources/1_restart.jpg");
	restart_texture = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	SDL_FreeSurface(start_surface);
	restart_source = { 0,0,222,59 };
	restart_destination = { bg_destination.w / 2 - 111, bg_destination.h /2 +100, restart_source.w, restart_source.h };
}

Ending::~Ending() {
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
}

void Ending::HandleEvents() {
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
				if (x >= restart_destination.x && x <= (restart_destination.x + restart_destination.w) &&
					y >= restart_destination.y && y <= restart_destination.y + restart_destination.h) {
					g_current_game_phase = PHASE_INTRO;
				}
			}
			break;

		default:
			break;
		}
	}
}

void Ending::Update() {

}

void Ending::Render() {
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
	SDL_RenderCopy(g_renderer, restart_texture, &restart_source, &restart_destination);
	SDL_RenderPresent(g_renderer);
}