#include "Button.h"

Button::Button(SDL_Renderer* renderer, string fontPath, int fontSize, string text, SDL_Color color) : Text(renderer, fontPath, fontSize, text, color)
{
}

bool Button::Check(int x, int y, SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (x >= m_textRect.x && x <= m_textRect.x + m_textRect.w && y >= m_textRect.y && y <= m_textRect.y + m_textRect.h)
			{
				return true;
			}
			else return false;
		}
	}
	return false;
}
