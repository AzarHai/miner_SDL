#include "Scene.h"

Scene::Scene(SDL_Renderer* renderer, int width, int height)
{
	m_renderer = renderer;
	m_width = width;
	m_height = height;
}

void Scene::Update()
{
}

void Scene::Render()
{
	SDL_RenderPresent(m_renderer);
}

int Scene::HandleEvents()
{	
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	{
		return -1;
	}
	return 0;
}
