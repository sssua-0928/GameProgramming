#pragma once
#include "main.h"

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;

class Stage1 : public PhaseInterface {
public:
	Stage1();
	~Stage1();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	SDL_Texture* bg_texture;
	SDL_Rect bg_source;
	SDL_Rect bg_destination;
};