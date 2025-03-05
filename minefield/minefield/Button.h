#pragma once

#include "Text.h"

class Button : public Text
{
public:
	Button(SDL_Renderer* renderer, string fontPath, int fontSize, string text, SDL_Color color);
	bool Check(int x, int y, SDL_Event event);
private:
	//bool m_isPressed = false;
};

