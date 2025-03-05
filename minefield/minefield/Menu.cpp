#include "Menu.h"

Menu::Menu(SDL_Renderer* renderer, int width, int height) : Scene(renderer, width, height)
{
	string fontPath = "Ysabeau-VariableFont_wght.ttf";
	SDL_Color fontColor = { 255, 255, 255, 255 };
	m_texts.push_back(new Text(renderer, fontPath, m_height / 10, "Minefield", fontColor));
	vector<string> texts = { "Play", "Input name", "Records", "Info", "Exit" };
	for (int i = 0; i < texts.size(); ++i)
	{
		m_texts.push_back(new Button(renderer, fontPath, m_height / 20, texts[i], fontColor));
	}
	m_texts.push_back(new Text(renderer, fontPath, m_height / 20, "Artur Groshev O729B", fontColor));
}

void Menu::Update()
{
	Uint32 buttons;
	buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

void Menu::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 153, 204, 204, 255);
	SDL_RenderClear(m_renderer);
	m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, (m_height - m_texts[0]->Get_Height()) / 8);
	for (int i = 1; i < m_texts.size() - 1; ++i)
	{
		m_texts[i]->Render((m_width - m_texts[i]->Get_Width()) / 2, (m_height - m_texts[i]->Get_Height()) / 3 + (i - 1) * 13 * m_height / 96);
	}
	m_texts[6]->Render(m_width - m_texts[6]->Get_Width() - 20, m_height - m_texts[6]->Get_Height());
	Scene::Render();
}

int Menu::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		for (int i = 1; i < m_texts.size() - 1; ++i)
		{
			if (static_cast<Button*>(m_texts[i])->Check(m_mouseX, m_mouseY, event))
			{
				if (i == 5) return -1;
				else return i;
			}
		}
	}
	return Scene::HandleEvents();
}
