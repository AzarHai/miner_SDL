#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class Window
{
public:
	Window(string name, int width, int height);
	~Window();

	SDL_Renderer* GetRenderer() { return m_renderer; }
	bool IsOpened() { return m_opened; }
	void SetOpened(bool opened) { m_opened = opened; }

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool m_opened;
};

