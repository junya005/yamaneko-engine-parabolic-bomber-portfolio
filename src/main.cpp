#define SDL_MAIN_HANDLED
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../engine/Window.h"
#include "../engine/Renderer.h"
#include "../engine/TextRenderer.h"
#include "../engine/AssetManager.h"
#include "../engine/Input.h"

// プロダクト名
const char PRODUCT_NAME[] = "Parabolic Bomber";

// ウィンドウサイズ
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

char* basePath = SDL_GetBasePath();

struct Bomb 
{
	int x, y;
	int width, height;
	bool is_move_right;

	Bomb(int x, int y, int width, int height, bool is_move_right) {
		this->x =x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->is_move_right = is_move_right;
	}
};

void UpdateBomb(std::vector<Bomb>& bomb_list) 
{
	for (auto it = bomb_list.begin(); it != bomb_list.end();)
	{
		if (it->is_move_right) {
			it->x++;
		}
		else
		{
			it->x--;
		}

		if (it->x >= WINDOW_WIDTH || it->x <= 0) 
		{
			it = bomb_list.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void RenderBomb(Engine::Renderer& renderer, SDL_Texture* texture, std::vector<Bomb>& bomb_list) 
{
	SDL_Rect bomb_src_rect = { 0,0,32,32 };

	for (auto& b:bomb_list) {
		SDL_Rect bomb_dst_rect = { b.x, b.y, b.width, b.height };

		renderer.DrawTexture(texture, &bomb_src_rect, &bomb_dst_rect);
	}
}

struct Explosion 
{
	int x, y;
	int w, h;
	int time;
	int max_time;

	Explosion(int x, int y, int w, int h, int max_time):x(x), y(y), w(w), h(h), time(0), max_time(max_time) {

	}
};

void UpdateExplosion(std::vector<Explosion>& explosion_list) {
	for (auto it = explosion_list.begin(); it != explosion_list.end();)
	{
		it->time++;

		if (it->time >= it->max_time)
		{
			it = explosion_list.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void RenderExplosion(Engine::Renderer& renderer, SDL_Texture* texture, std::vector<Explosion>& explosion_list) {
	SDL_Rect explosion_src_rect = { 0,0,908,696 };

	for (auto& b : explosion_list) {
		SDL_Rect explosion_dst_rect = { b.x, b.y, b.w, b.h };

		renderer.DrawTexture(texture, &explosion_src_rect, &explosion_dst_rect);
	}
}

/// <summary>
/// メイン関数
/// </summary>
int main(int argc, char* argv[]) {    

	Engine::Window window;
	if(!window.Initialize(PRODUCT_NAME, WINDOW_WIDTH, WINDOW_HEIGHT)) {
		return -1;
	}

	Engine::Renderer renderer;
	if (!renderer.Initialize(window.GetSDLWindow()))
	{
		return -1;
	}

	Engine::TextRenderer text_renderer;
	if (!text_renderer.Initialize()) {
		return -1;
	}

	Engine::AssetManager asset_manager;

	Engine::Input input;

	// フォントのロードとテクスチャ作成
	TTF_Font* font = asset_manager.LoadFont("assets/font/Galindo/Galindo-Regular.ttf", 64);

	// プレイヤーのテクスチャロード
	SDL_Texture* player_texture = asset_manager.LoadTexture(renderer, "assets/texture/player001.png");
	
	SDL_Rect playerSrcRect = { 0, 0, 1600, 1141 };

	// 爆弾のテクスチャロード
	SDL_Texture* bomb_texture = asset_manager.LoadTexture(renderer, "assets/texture/bomb001.png");		

	SDL_Rect srcRect;
	srcRect.x = 0;   // X-coordinate on the sprite sheet
	srcRect.y = 0;   // Y-coordinate on the sprite sheet
	srcRect.w = 32;  // Width of the individual frame
	srcRect.h = 32;  // Height of the individual frame

	SDL_Rect destRect;
	destRect.x = 100; // Screen X position
	destRect.y = 150; // Screen Y position
	destRect.w = 32;  // Scale width on screen
	destRect.h = 32;  // Scale height on screen

	// 爆弾爆発のテクスチャロード
	SDL_Texture* explosion_texture = asset_manager.LoadTexture(renderer, "assets/texture/Explosion.png");
	
	// 背景の草原のテクスチャロード
	SDL_Texture* grassland_texture = asset_manager.LoadTexture(renderer, "assets/texture/background001.png");

	SDL_Rect srcBGRect;
	srcBGRect.x = 0;
	srcBGRect.y = 0;
	srcBGRect.w = 1762;
	srcBGRect.h = 1250;

	SDL_Rect destBGRect;
	destBGRect.x = -100;
	destBGRect.y = -100;
	destBGRect.w = 1762;
	destBGRect.h = 1250;
	
	// プレイヤーの座標
	int x = window.GetWidthCenter() - 100 - 200, 
		y = window.GetHeightCenter();
	int x2 = window.GetWidthCenter() + 100,
		y2 = window.GetHeightCenter();

	// 爆弾の配列
	std::vector<Bomb> bomb_list = std::vector<Bomb>();	

	// 爆発の配列
	std::vector<Explosion> explosion_list = std::vector<Explosion>();

	// 勝敗判定フラグ
	bool is_match_end = false;
	bool is_winner_p1 = false;

	bool is_quit = false;
	
	while (!is_quit)
	{
		input.BeginFrame();

		SDL_Event e = {};
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				is_quit = true;
			}
			else {
				input.ProcessEvent(e);
			}
		}

		if (!is_match_end)
		{
			if (input.GetKeyDown(SDLK_e)) {
				bomb_list.emplace_back(Bomb(x + 164, y, 64, 64, true));
			}
			if (input.GetKeyDown(SDLK_RSHIFT)) {
				bomb_list.emplace_back(Bomb(x2 - 100, y2, 64, 64, false));
			}

			// プレイヤー1操作
			if (input.GetKey(SDL_SCANCODE_W)) {
				if (y >= 0)
				{
					y--;
				}
			}
			if (input.GetKey(SDL_SCANCODE_S)) {
				if (y <= WINDOW_HEIGHT - 142.625f)
				{
					y++;
				}
			}

			// プレイヤー2操作
			if (input.GetKey(SDL_SCANCODE_UP)) {
				if (y2 >= 0)
				{
					y2--;
				}
			}
			if (input.GetKey(SDL_SCANCODE_DOWN)) {
				if (y2 <= WINDOW_HEIGHT - 142.625f)
				{
					y2++;
				}
			}

			// 爆弾の処理
			UpdateBomb(bomb_list);

			// 爆発の処理
			UpdateExplosion(explosion_list);

			// 当たり判定
			for (auto it = bomb_list.begin(); it != bomb_list.end();) {
				if (x <= it->x + it->width && x + 200 >= it->x &&
					y <= it->y + it->height && y + 142.625f >= it->y &&
					!it->is_move_right)
				{
					x -= 10;

					// 削除する前に座標を保存
					int ex_x = it->x;
					int ex_y = it->y;

					it = bomb_list.erase(it);
					explosion_list.emplace_back(Explosion(ex_x-114, ex_y-87, 227, 174, 500));
				}
				else if (x2 <= it->x + it->width && x2 + 200 >= it->x &&
					y2 <= it->y + it->height && y2 + 142.625f >= it->y &&
					it->is_move_right)
				{
					x2 += 10;

					// 削除する前に座標を保存
					int ex_x = it->x;
					int ex_y = it->y;

					it = bomb_list.erase(it);
					explosion_list.emplace_back(Explosion(ex_x-114, ex_y-87, 227, 174, 500));
				}
				else
				{
					++it;
				}
			}

			// 勝敗判定
			if (x <= 0 - 200) {
				is_match_end = true;
				is_winner_p1 = false;
			}
				
			if (x2 >= WINDOW_WIDTH) {
				is_match_end = true;
				is_winner_p1 = true;
			}
		}
		
		// 画面を黒で塗りつぶす
		renderer.Clear(0,0,0,255);

		// 背景の描画
		renderer.DrawTexture(grassland_texture, &srcBGRect, &destBGRect);	
		
		SDL_Rect player1DestRect = { x,y, 200, (int)142.625f };
		SDL_Rect player2DestRect = { x2,y2, 200, (int)142.625f };
		
		renderer.DrawTexture(player_texture, &playerSrcRect, &player1DestRect, true);
		renderer.DrawTexture(player_texture, &playerSrcRect, &player2DestRect, false);	

		// 爆弾描画
		RenderBomb(renderer, bomb_texture, bomb_list);

		// 爆発描画
		RenderExplosion(renderer, explosion_texture, explosion_list);

		if (!is_match_end)
		{
			text_renderer.DrawText(renderer, font, "1P", x + 140, y - 50, { 200, 50, 50, 255 });
			text_renderer.DrawText(renderer, font, "2P", x2, y2 - 50, { 50, 50, 200, 255 });
		}

		if (is_match_end)
		{
			// 勝敗テキスト描画
			if (is_winner_p1) {
				text_renderer.DrawText(renderer, font, "Winner is 1P", window.GetWidthCenter() - 200, window.GetHeightCenter() - 50, {200, 50, 50, 255});
			}
			else {
				text_renderer.DrawText(renderer, font, "Winner is 2P", window.GetWidthCenter() - 200, window.GetHeightCenter() - 50, {50, 50, 200, 255});
			}
		}

		SDL_RenderPresent(renderer.GetSDLRenderer());
	}

	// Engine名前空間に入っている機能を使用しているのであれば、
	// リソース解放処理は必要ないです。

	return 0;
}