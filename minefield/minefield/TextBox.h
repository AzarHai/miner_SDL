#pragma once

#include "Button.h"

class TextBox : public Button
{
public:
	TextBox(SDL_Renderer* renderer, string fontPath, int fontSize, string text, SDL_Color color);
	void SetWidth(int width) { m_textRect.w = m_border.w = width; }
	void SetHeight(int height) { m_textRect.h = m_border.h = height; }
	void HandleEvents(SDL_Event event);
	void Render(int x, int y);
	void ReplaceText();
	int Get_Width() { return m_border.w; }
	string GetText() { return m_text; }
private:
	SDL_Rect m_border;
};

