#include "Records.h"

Records::Records(SDL_Renderer* renderer, int width, int height) : Scene(renderer, width, height)
{
	m_isReading = true;

	string fontPath = "Ysabeau-VariableFont_wght.ttf";
	SDL_Color fontColor = { 255, 255, 255, 255 };
	m_texts.push_back(new Text(renderer, fontPath, m_height / 10, "Records", fontColor));
	m_texts.push_back(new Button(renderer, fontPath, m_height / 20, "Back", fontColor));
	m_texts.push_back(new Button(renderer, fontPath, m_height / 20, "Clear", fontColor));
	m_texts.push_back(new Button(renderer, fontPath, m_height / 20, "To Print", fontColor));
}

void Records::Update()
{
	Uint32 buttons;
	buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

void Records::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 153, 204, 204, 255);
	SDL_RenderClear(m_renderer);

	m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, (m_height - m_texts[0]->Get_Height()) / 8);
	
	DrawTable(Scores::ReadFromFile());

	m_texts[1]->Render((m_width - m_texts[1]->Get_Width()) / 2, 
		14 * (m_height - m_texts[1]->Get_Height()) / 16);
	m_texts[2]->Render((m_width - m_texts[2]->Get_Width()) / 4,
		15 * (m_height - m_texts[2]->Get_Height()) / 16);
	m_texts[3]->Render(3 * (m_width - m_texts[3]->Get_Width()) / 4,
		15 * (m_height - m_texts[3]->Get_Height()) / 16);

	Scene::Render();
}

int Records::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (static_cast<Button*>(m_texts[1])->Check(m_mouseX, m_mouseY, event))
		{
			return 5;
		}
		if (static_cast<Button*>(m_texts[2])->Check(m_mouseX, m_mouseY, event))
		{
			Scores::ClearFile();
		}
		if (static_cast<Button*>(m_texts[3])->Check(m_mouseX, m_mouseY, event))
		{
			Scores::ToPrint();
			m_texts[3]->SetText("Saved in \"Records.txt\"");
		}
	}
	return Scene::HandleEvents();
}

void Records::DrawTable(vector<Score> scores)
{
	if (m_isReading)
	{
		string fontPath = "Ysabeau-VariableFont_wght.ttf";
		SDL_Color fontColor = { 255, 255, 255, 255 };
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 20, "Name", fontColor));
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 20, "Time", fontColor));
		for (auto el : scores)
		{
			m_texts.push_back(new Text(m_renderer, fontPath, m_height / 20, el.name, fontColor));
			m_texts.push_back(new Text(m_renderer, fontPath, m_height / 20, 
				to_string(el.time / 1000) + "." + to_string(el.time % 1000 / 10), fontColor));
		}
		m_isReading = false;
	}
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	for (int i = 0; i < 12; ++i)
	{
		SDL_RenderDrawLine(m_renderer, m_width / 2 - 250, m_height / 2 - 150 + i * 30, 
			m_width / 2 + 250, m_height / 2 - 150 + i * 30);
	}
	SDL_RenderDrawLine(m_renderer, m_width / 2 - 250, m_height / 2 - 150,
		m_width / 2 - 250, m_height / 2 + 180);
	SDL_RenderDrawLine(m_renderer, m_width / 2, m_height / 2 - 150,
		m_width / 2, m_height / 2 + 180);
	SDL_RenderDrawLine(m_renderer, m_width / 2 + 250, m_height / 2 - 150,
		m_width / 2 + 250, m_height / 2 + 180);

	m_texts[4]->Render((m_width - m_texts[4]->Get_Width()) / 2 - 125,
		(m_height - m_texts[4]->Get_Height()) / 2 - 135);
	m_texts[5]->Render((m_width - m_texts[5]->Get_Width()) / 2 + 125,
		(m_height - m_texts[5]->Get_Height()) / 2 - 135);
	for (int i = 6; i < m_texts.size() && scores.size(); i+=2)
	{
		m_texts[i]->Render((m_width - m_texts[i]->Get_Width()) / 2 - 125,
			(m_height - m_texts[i]->Get_Height()) / 2 - 135 + 30 * (i / 2 - 2));
		m_texts[i + 1]->Render((m_width - m_texts[i + 1]->Get_Width()) / 2 + 125,
			(m_height - m_texts[i + 1]->Get_Height()) / 2 - 135 + 30 * (i / 2 - 2));
	}
}

