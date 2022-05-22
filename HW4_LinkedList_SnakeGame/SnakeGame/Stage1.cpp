#include "Stage1.h"

Stage1::Stage1() {
	SDL_Surface* bg_surface = IMG_Load("../../Resources/bg_stage1.jpg");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source = { 0,0,600,600 };
	bg_destination = { 0, 0, bg_source.w, bg_source.h };
}

Stage1::~Stage1() {
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
}

void Stage1::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE) {
				g_current_game_phase = PHASE_ENDING;
			}
			break;
		}
	}
}

void Stage1::Update() {

}

void Stage1::Render() {
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
	SDL_RenderPresent(g_renderer);
}