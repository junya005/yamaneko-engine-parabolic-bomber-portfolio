# pragma once

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <string>

namespace Engine
{
	/// <summary xml:lang="ja">
	/// ウィンドウの管理を行うクラス
	/// </summary>
	/// <remarks xml:lang="ja">
	///	デストラクタでリソース解放を行うため、
	/// ヒープ メモリに保存しないでください
	/// </remarks>
	/// <summary xml:lang="en">
	/// Class of Window Management.
	/// </summary>
	class Window {
	public:
		// コンストラクタ及びデストラクタ
		Window();
		~Window();

		/// <summary>
		/// ウィンドウの初期化を行います
		/// </summary>
		/// <param name="title">ウィンドウの名前</param>
		/// <param name="width">ウィンドウの横幅(px)</param>
		/// <param name="height">ウィンドウの縦幅(px)</param>
		/// <returns>ウィンドウの初期化に成功したか</returns>
		bool Initialize(const std::string& title, int width, int height);

		void Cleanup();

		SDL_Window* GetSDLWindow() const { return m_window; }

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		int GetWidthCenter() const { return m_width / 2; }
		int GetHeightCenter() const { return m_height / 2; }

	private:
		SDL_Window* m_window;
		int m_width;
		int m_height;
	};
}

