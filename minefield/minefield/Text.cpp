#include "Text.h"

#include <iostream>

using namespace std;

Text::Text(SDL_Renderer* renderer, string fontPath, int fontSize, string text, SDL_Color color)
{
	m_fontPath = fontPath;
	m_fontSize = fontSize;
	m_color = color;
	m_renderer = renderer;
	m_texture = LoadFont(fontPath, fontSize, text, color);
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);
}

void Text::Render(int x, int y)
{
	m_textRect.x = x;
	m_textRect.y = y;
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_textRect);
}

SDL_Texture* Text::LoadFont(const string& fontPath, int fontSize, string& text, SDL_Color color)
{
	m_font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!m_font)
	{
		cout << "Ошибка при открытии шрифта" << endl;
	}
	auto textSurface = TTF_RenderText_Solid(m_font, text.c_str(), color);
	if (!textSurface)
	{
		// cout << "Ошибка при создании text surface" << endl;
	}
	auto textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	if (!textTexture)
	{
		// cout << "Ошибка при создании text texture" << endl;
	}
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(m_font);
	return textTexture;
}

void Text::SetText(string str)
{
	SDL_DestroyTexture(m_texture);
	m_texture = LoadFont(m_fontPath, m_fontSize, str, m_color);
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);
}
