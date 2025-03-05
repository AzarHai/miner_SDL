#include "InputName.h"

InputName::InputName(SDL_Renderer* renderer, int width, int height, bool f) : Scene(renderer, width, height)
{
	m_f = f;
	string fontPath = "Ysabeau-VariableFont_wght.ttf";
	SDL_Color fontColor = { 255, 255, 255, 255 };

	m_texts.push_back(new Text(m_renderer, fontPath, m_height / 10, "Input name", fontColor));

	m_texts.push_back(new TextBox(m_renderer, fontPath, m_height / 20, " ", fontColor));

	m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "Accept", fontColor));

	if (f) m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "Back", fontColor));
}

void InputName::Update()
{
	Uint32 buttons;
	buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

void InputName::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 153, 204, 204, 255);
	SDL_RenderClear(m_renderer);

	m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, (m_height - m_texts[0]->Get_Height()) / 8);

	m_texts[1]->Render((m_width - m_texts[1]->Get_Width()) / 2, (m_height - m_texts[1]->Get_Height()) / 3);

	for (int i = 2; i < m_texts.size(); ++i)
	{
		m_texts[i]->Render((m_width - m_texts[i]->Get_Width()) / 2,
			(m_height - m_texts[i]->Get_Height()) / 3 + (i - 1) * 13 * m_height / 72);
	}
	Scene::Render();
}

int InputName::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (static_cast<Button*>(m_texts[2])->Check(m_mouseX, m_mouseY, event))
		{
			if (static_cast<TextBox*>(m_texts[1])->GetText() != "")
			{
				m_name = static_cast<TextBox*>(m_texts[1])->GetText();
				return 5;
			}
		}

		if (static_cast<Button*>(m_texts[m_texts.size() - 1])->Check(m_mouseX, m_mouseY, event) && m_f)
		{
			return 5;
		}

		static_cast<TextBox*>(m_texts[1])->HandleEvents(event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
		{
			if (static_cast<TextBox*>(m_texts[1])->GetText() != "")
			{
				m_name = static_cast<TextBox*>(m_texts[1])->GetText();
				return 5;
			}
		}
		if (event.type == SDL_QUIT)
		{
			return -1;
		}
	}
	return Scene::HandleEvents();
}

