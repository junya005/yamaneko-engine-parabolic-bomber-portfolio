#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace Engine
{
	/// <remarks xml:lang="ja">
	///	デストラクタでリソース解放を行うため、
	/// ヒープ メモリに保存しないでください
	/// </remarks>
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool Initialize(SDL_Window *window);
		void Cleanup();

		void Clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
		void Present();

		void DrawTexture(SDL_Texture *texture, const SDL_Rect *src_rect, const SDL_Rect *dst_rect, bool flip_horizontal = false);
		
		SDL_Renderer* GetSDLRenderer() const { return m_renderer; }

	private:
		SDL_Renderer* m_renderer;
	};
}
