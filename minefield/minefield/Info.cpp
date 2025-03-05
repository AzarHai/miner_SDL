#include "Info.h"

Info::Info(SDL_Renderer* renderer, int width, int height) : Scene(renderer, width, height)
{
	string fontPath = "Ysabeau-VariableFont_wght.ttf";
	SDL_Color fontColor = { 255, 255, 255, 255 };
	m_texts.push_back(new Text(renderer, fontPath, m_height / 10, "Information", fontColor));

	m_texts.push_back(new Text(renderer, fontPath, m_height / 20, 
		"You are the blue square (in the upper left corner).", fontColor));
	m_texts.push_back(new Text(renderer, fontPath, m_height / 20,
		"At the beginning of the game, a field with mines", fontColor));
	m_texts.push_back(new Text(renderer, fontPath, m_height / 20,
		"(red squares) is shown for 2 seconds. You need", fontColor));
	m_texts.push_back(new Text(renderer, fontPath, m_height / 20,
		"to remember their location and use the WASD keys", fontColor));
	m_texts.push_back(new Text(renderer, fontPath, m_height / 20,
		"or arrows to get to the lower right edge", fontColor));
	m_texts.push_back(new Text(renderer, fontPath, m_height / 20,
		"(green square) without touching the mines.", fontColor));
	m_texts.push_back(new Text(renderer, fontPath, m_height / 20,
		"The faster you pass, the better. Good luck!", fontColor));

	m_texts.push_back(new Button(renderer, fontPath, m_height / 20, "Back", fontColor));
}

void Info::Update()
{
	Uint32 buttons;
	buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

void Info::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 153, 204, 204, 255);
	SDL_RenderClear(m_renderer);

	m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, (m_height - m_texts[0]->Get_Height()) / 8);

	for (int i = 1; i < m_texts.size() - 1; ++i)
		m_texts[i]->Render((m_width - m_texts[i]->Get_Width()) / 2, 
			(4 + i) * (m_height - m_texts[i]->Get_Height()) / 16);

	m_texts[m_texts.size() - 1]->Render((m_width - m_texts[m_texts.size() - 1]->Get_Width()) / 2,
		13 * (m_height - m_texts[m_texts.size() - 1]->Get_Height()) / 16);
	
	Scene::Render();
}

int Info::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (static_cast<Button*>(m_texts[m_texts.size() - 1])->Check(m_mouseX, m_mouseY, event))
		{
			return 5;
		}
	}
	return Scene::HandleEvents();
}
