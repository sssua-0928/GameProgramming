#pragma once
#include "main.h"
#include <list>
#include <stdlib.h>
#include <time.h>
#include <atlstr.h>

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
	//Background
	SDL_Texture* bg_texture;
	SDL_Rect bg_source;
	SDL_Rect bg_destination;

	//Snake
	SDL_Texture* snake_texture;
	SDL_Rect snake_source;
	SDL_Rect snake_destination;

	//Item
	SDL_Texture* item_texture;
	SDL_Rect item_source;
	SDL_Rect item_destination;
	boolean item_status;  //�������� ���� ȭ�鿡 ��Ÿ���ִ���
	int randomX, randomY;	//���� ������ġ


	//Font
	TTF_Font* font;
	SDL_Color yellow;

	//Text_gameover
	SDL_Texture* game_over_texture;
	SDL_Rect game_over_text;
	SDL_Rect game_over_destination;

	enum dt { LEFT, RIGHT, UP, DOWN, DIE };
	
	int direction;	//snake �̵�����

	list<SDL_Rect> snake;
	/*
	std::list<int> L;
	std::cout << "size of L : " << L.size << std:endl;
	L.front() / L.back()

	*/
	const int SIZE = 25;  //��, �������� ���μ��� ������� ��� 25
	boolean game_over;  //������ ��������
	boolean game_over_click;  //'Game Over'�� ��������
};