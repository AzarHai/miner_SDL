#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Text.h"
#include "Button.h"
#include "TextBox.h"

class Scene
{
public:
	Scene(SDL_Renderer* renderer, int width, int height);
	virtual void Update();
	virtual void Render();
	virtual int HandleEvents();
protected:
	SDL_Renderer* m_renderer;
	vector<Text*> m_texts;
	int m_width, m_height;
	int m_mouseX = 0, m_mouseY = 0;
};

