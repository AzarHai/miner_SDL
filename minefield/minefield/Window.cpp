#include "Window.h"

Window::Window(string name, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Ошибка при инициализации SDL" << endl;
	}
	if (TTF_Init() < 0)
	{
		cout << "Ошибка при инициализации TTF" << endl;
	}
	m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		cout << "Ошибка при создании окна" << endl;
	}
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	if (!m_renderer)
	{
		cout << "Ошибка при создании рендерера" << endl;
	}

	m_opened = true;
}

Window::~Window()
{
	SDL_DestroyWindow(m_window);
	TTF_Quit();
	SDL_Quit();
}
