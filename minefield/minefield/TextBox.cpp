#include "TextBox.h"

#include <iostream>

TextBox::TextBox(SDL_Renderer* renderer, string fontPath, int fontSize, string text, SDL_Color color) : Button(renderer, fontPath, fontSize, text, color)
{
}

void TextBox::HandleEvents(SDL_Event event)
{
	SDL_StartTextInput();
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_BACKSPACE)
		{
			if (!m_text.empty()) m_text.pop_back();
			this->ReplaceText();
		}
		else if (39 <= event.key.keysym.sym && event.key.keysym.sym <= 122 && m_text.size() < 8)
		{
			m_text += event.key.keysym.mod ? (char)event.key.keysym.sym - 32 : (char)event.key.keysym.sym;
			this->ReplaceText();
		}
	}
	SDL_StopTextInput();
}

void TextBox::Render(int x, int y)
{
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_textRect);
}

void TextBox::ReplaceText()
{
	SDL_DestroyTexture(m_texture);
	m_texture = LoadFont(m_fontPath, m_fontSize, m_text, m_color);
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);
}
