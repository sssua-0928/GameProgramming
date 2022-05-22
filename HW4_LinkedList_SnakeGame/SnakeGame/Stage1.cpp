#include "Stage1.h"

Stage1::Stage1() {
	//Background
	SDL_Surface* bg_surface = IMG_Load("../../Resources/bg_stage1.jpg");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source = { 0,0,600,600 };
	bg_destination = { 0, 0, bg_source.w, bg_source.h };

	//Snake
	SDL_Surface* snake_surface = IMG_Load("../../Resources/snake.png");
	snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_surface);
	SDL_FreeSurface(snake_surface);
	snake_source = { 0,0,SIZE,SIZE };
	snake.push_front({ 0,0,SIZE,SIZE });

	//Item
	SDL_Surface* item_surface = IMG_Load("../../Resources/item.png");
	item_texture = SDL_CreateTextureFromSurface(g_renderer, item_surface);
	SDL_FreeSurface(item_surface);
	item_source = { 0,0,SIZE,SIZE };
	item_status = false;

	//Font
	font = TTF_OpenFont("../../Resources/arose.ttf", 50);
	yellow = { 255, 200, 0, 0 };

	//Text_gameover
	SDL_Surface* game_over_surface = TTF_RenderText_Blended( font, "--GAME OVER--", yellow );
	game_over_texture = SDL_CreateTextureFromSurface( g_renderer, game_over_surface );
	SDL_FreeSurface(game_over_surface);
	game_over_text = { 0, 0, 500 ,100 };
	game_over_destination = { bg_destination.w/2 - game_over_text.w/2, bg_destination.h/2 - game_over_text.h/2, game_over_text.w, game_over_text.h };

	direction = DIE;
	srand(time(NULL));
	game_over = false;
	game_over_click = false;
}

Stage1::~Stage1() {
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(snake_texture);
	SDL_DestroyTexture(item_texture);
}

void Stage1::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;
	
		//KEY DOWN
		case SDL_KEYDOWN:
			// snake 이동
			if (event.key.keysym.sym == SDLK_LEFT) {
				if (direction != RIGHT)
					direction = LEFT;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				if (direction != LEFT)
					direction = RIGHT;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				if (direction != DOWN)
					direction = UP;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				if (direction != UP)
					direction = DOWN;
			}
			break;
		
		//MOUSE DOWN
		case SDL_MOUSEBUTTONDOWN:
			// 왼쪽 마우스 클릭시 Ending화면으로 이동
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (game_over) {
					g_current_game_phase = PHASE_ENDING;
					game_over_click = true;
				}
			}

		}
	}
}

void Stage1::Update() {
	//게임 재시작
	if (game_over) return;

	//아이템 랜덤배치 (10단위로 배치)
	randomX = ( (rand() % 600) / 10 ) * 10;
	randomY = ( (rand() % 600) / 10 ) * 10;
	if (item_status == false) {
		for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
			if ((*iter).x == randomX && (*iter).y == randomY) {
				randomX = ( (rand() % 600) / 10 ) * 10;
				randomY = ( (rand() %600) / 10 ) * 10;
			}
			else
				continue;
		}
		item_destination = { randomX, randomY, SIZE, SIZE };
		item_status = true;
	}

	//Snake
	int tempX = 0;
	int tempY = 0;

	switch (direction) {
	case LEFT:
		tempX = -10;
		tempY = 0;
		break;
	case RIGHT:
		tempX = 10;
		tempY = 0;
		break;
	case UP:
		tempX = 0;
		tempY = -10;
		break;
	case DOWN:
		tempX = 0;
		tempY = 10;
		break;
	default:
		break;
	}
	snake.push_front({ snake.front().x + tempX , snake.front().y + tempY, 25, 25 });  //head에 추가
	snake.pop_back();

	//Item에 닿으면 상태변경(item_status)
	if ((snake.front().x == item_destination.x) && (snake.front().y == item_destination.y)) {
		snake.push_front({ snake.front().x + tempX, snake.front().y + tempY, 25, 25 });
		snake.push_front({ snake.front().x + tempX, snake.front().y + tempY, 25, 25 });
		item_status = false;
		printf("아이템 획득!");
	}

	//Snake 위치상태
	if ((snake.front().x < 0) || (snake.front().x >= 575) || (snake.front().y < 0) || (snake.front().y >= 575)) {
		game_over = true;
		direction = DIE;
		snake.front().x = tempX;
		snake.front().y = tempY;
		printf("[Game Over] 벽에 닿음");
	}

	int frontX = snake.front().x;
	int frontY = snake.front().y;
	for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
		if ((*iter).x == frontX && (*iter).y == frontY) {
			game_over = true;
			direction = DIE;
			snake.front().x = tempX;
			snake.front().y = tempY;
			printf("[Game Over] 몸통에 닿음");
		}
	}

}


void Stage1::Render() {
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
	SDL_RenderCopy(g_renderer, item_texture, &item_source, &item_destination);

	if(!game_over){	//게임이 끝나면 더이상 그려지지 않게
		for (auto iter = snake.begin(); iter != snake.end(); iter++) {
			//printf("%d, %d \n", (*iter).x, (*iter).y );
			SDL_RenderCopy(g_renderer, snake_texture, &snake_source, &(*iter));
		}		
	}
	if (game_over) 
		SDL_RenderCopy(g_renderer, game_over_texture, &game_over_text, &game_over_destination);
	if (game_over_click) {
		snake.clear();
		snake.push_front({ 0,0,SIZE,SIZE });
		direction = DIE;
		game_over = false;
		game_over_click = false;
		SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
		SDL_RenderCopy(g_renderer, item_texture, &item_source, &item_destination);
		SDL_RenderCopy(g_renderer, snake_texture, &snake_source, &(snake.front()));
	}
	SDL_RenderPresent(g_renderer);
}
