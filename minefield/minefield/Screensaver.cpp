#include "Screensaver.h"

Screensaver::Screensaver(SDL_Renderer* renderer, int width, int height) : Scene(renderer, width, height)
{
	string fontPath = "Ysabeau-VariableFont_wght.ttf";
	SDL_Color fontColor = { 255, 255, 255, 255 };
	m_texts.push_back(new Text(renderer, fontPath, m_height / 10, "Minefield", fontColor));

	m_texts.push_back(new Text(renderer, fontPath, m_height / 20, "Artur Groshev O729B", fontColor));
}

void Screensaver::Update()
{
	Uint32 buttons;
	buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

void Screensaver::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 153, 204, 204, 255);
	SDL_RenderClear(m_renderer);

	m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, 1 * (m_height - m_texts[0]->Get_Height()) / 3);

	m_texts[1]->Render((m_width - m_texts[1]->Get_Width()) / 2, 2 * (m_height - m_texts[1]->Get_Height()) / 3);

	Scene::Render();
}

int Screensaver::HandleEvents()
{
	return Scene::HandleEvents();
}
