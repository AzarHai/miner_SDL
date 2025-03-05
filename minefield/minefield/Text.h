#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class Text
{
public:
	Text(SDL_Renderer* renderer, string fontPath, int fontSize, string text, SDL_Color color);
	void Render(int x, int y);
	SDL_Texture* LoadFont(const string& fontPath, int fontSize, string& text, SDL_Color color);
	int Get_X() { return m_textRect.x; }
	int Get_Y() { return m_textRect.y; }
	int Get_Width() { return m_textRect.w; }
	int Get_Height() { return m_textRect.h; }
	void SetText(string str);

protected:
	SDL_Texture* m_texture = nullptr;
	SDL_Rect m_textRect;
	TTF_Font* m_font = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	string m_text;
	SDL_Color m_color;
	string m_fontPath;
	int m_fontSize;
};

