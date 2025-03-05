#include "Game.h"

Game::Game(SDL_Renderer* renderer, int width, int height) : Scene(renderer, width, height)
{
	m_inputName = true;
	m_pause = false;
	m_show = true;
	m_gameOver = false;

	m_startTime = 0;
	m_time = 0;
	m_pauseTime = 0;

	m_renderGame = [&]()
	{
		m_texts.clear();

		string fontPath = "Ysabeau-VariableFont_wght.ttf";
		SDL_Color fontColor = { 255, 255, 255, 255 };

		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 10, "Game", fontColor));
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 20, "Time: 0.00", fontColor));
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 30, "Hints:", fontColor));
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 30, "Use WASD or", fontColor));
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 30, "arrows to move", fontColor));
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 30, "Press ESC to pause", fontColor));
		m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "Pause", fontColor));
		m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "Back", fontColor));

		m_render = [&]()
		{
			m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, (m_height - m_texts[0]->Get_Height()) / 8);
			m_texts[1]->Render(10, 0);

			for (int i = 2; i < m_texts.size() - 2; ++i)
			{
				m_texts[i]->Render((m_width - m_texts[i]->Get_Width()) / 16, (3 + i) * (m_height - m_texts[i]->Get_Height()) / 16);
			}

			m_texts[m_texts.size() - 2]->Render((m_width - m_texts[m_texts.size() - 2]->Get_Width() - 10), 0);
			m_texts[m_texts.size() - 1]->Render((m_width - m_texts[m_texts.size() - 1]->Get_Width()) / 2,
				13 * (m_height - m_texts[m_texts.size() - 1]->Get_Height()) / 16);

			if (m_show)
			{
				m_openDesk();
			}
			else
			{
				m_closeDesk();
			}
			m_time = (SDL_GetTicks() - m_startTime) + m_pauseTime;
			m_texts[1]->SetText("Time: " + to_string(m_time / 1000) + ":" + to_string(m_time % 1000 / 10));
		};
	};
	
	m_renderPause = [&]()
	{
		m_texts.clear();

		string fontPath = "Ysabeau-VariableFont_wght.ttf";
		SDL_Color fontColor = { 255, 255, 255, 255 };

		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 10, "Pause", fontColor));
		m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "Back", fontColor));
		m_render = [&]()
		{
			m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, (m_height - m_texts[0]->Get_Height()) / 8);
			m_texts[1]->Render((m_width - m_texts[1]->Get_Width()) / 2,
				7 * (m_height - m_texts[1]->Get_Height()) / 16);
		};
	};

	m_openDesk = [&]()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				if (m_matrix[i][j] == 0)
				{
					SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
				}
				else if (m_matrix[i][j] == 1)
				{
					SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
				}
				else if (m_matrix[i][j] == 2)
				{
					SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
				}
				else if (m_matrix[i][j] == 3)
				{
					SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
				}
				else if (m_matrix[i][j] == -1)
				{
					SDL_SetRenderDrawColor(m_renderer, 128, 0, 128, 255);
				}
				SDL_RenderFillRect(m_renderer, &m_field[i][j]);
				SDL_SetRenderDrawColor(m_renderer, 140, 140, 140, 255);
				SDL_RenderDrawRect(m_renderer, &m_field[i][j]);
			}
		}
	};

	m_closeDesk = [&]()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				if (m_matrix[i][j] == 2)
				{
					SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
				}
				else
				{
					SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
				}
				SDL_RenderFillRect(m_renderer, &m_field[i][j]);
				SDL_SetRenderDrawColor(m_renderer, 140, 140, 140, 255);
				SDL_RenderDrawRect(m_renderer, &m_field[i][j]);
			}
		}
	};

	m_renderWin = [&]()
	{
		m_texts.clear();

		string fontPath = "Ysabeau-VariableFont_wght.ttf";
		SDL_Color fontColor = { 255, 255, 255, 255 };

		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 10, "You Win", fontColor));
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 20,
			"Your Time is " + to_string(m_time / 1000) + ":" + to_string(m_time % 1000 / 10), { 0, 255, 0, 255}));
		m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "New Game", fontColor));
		m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "Menu", fontColor));

		m_gameOver = true;

		m_render = [&]()
		{
			m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, (m_height - m_texts[0]->Get_Height()) / 8);
			m_texts[1]->Render((m_width - m_texts[1]->Get_Width()) / 2, 
				13 * (m_height - m_texts[2]->Get_Height()) / 16);
			m_texts[2]->Render((m_width - m_texts[2]->Get_Width()) / 2,
				14 * (m_height - m_texts[2]->Get_Height()) / 16);
			m_texts[m_texts.size() - 1]->Render((m_width - m_texts[m_texts.size() - 1]->Get_Width()) / 2,
				15 * (m_height - m_texts[m_texts.size() - 1]->Get_Height()) / 16);

			m_openDesk();
		};
		Scores::Add_Record(m_name, m_time);
	};

	m_renderGameOver = [&]()
	{
		m_texts.clear();

		string fontPath = "Ysabeau-VariableFont_wght.ttf";
		SDL_Color fontColor = { 255, 255, 255, 255 };

		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 10, "Game Over", fontColor));
		m_texts.push_back(new Text(m_renderer, fontPath, m_height / 20,
			"Your Time is " + to_string(m_time / 1000) + ":" + to_string(m_time % 1000 / 10), { 255, 0, 0, 255 }));
		m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "New Game", fontColor));
		m_texts.push_back(new Button(m_renderer, fontPath, m_height / 20, "Menu", fontColor));

		m_gameOver = true;

		m_render = [&]()
		{
			m_texts[0]->Render((m_width - m_texts[0]->Get_Width()) / 2, (m_height - m_texts[0]->Get_Height()) / 8);
			m_texts[1]->Render((m_width - m_texts[1]->Get_Width()) / 2,
				13 * (m_height - m_texts[2]->Get_Height()) / 16);
			m_texts[2]->Render((m_width - m_texts[2]->Get_Width()) / 2,
				14 * (m_height - m_texts[2]->Get_Height()) / 16);
			m_texts[m_texts.size() - 1]->Render((m_width - m_texts[m_texts.size() - 1]->Get_Width()) / 2,
				15 * (m_height - m_texts[m_texts.size() - 1]->Get_Height()) / 16);

			m_openDesk();
		};
	};

	SetupDesk();

	m_renderGame();
}

void Game::Update()
{
	Uint32 buttons;
	buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 153, 204, 204, 255);
	SDL_RenderClear(m_renderer);

	m_render();

	Scene::Render();
}

int Game::HandleEvents()
{
	if (!m_pause)
	{
		if (m_show)
		{
			m_show = false;
			SDL_Delay(3000);
			m_startTime = SDL_GetTicks();
		}

		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (static_cast<Button*>(m_texts[m_texts.size() - 1])->Check(m_mouseX, m_mouseY, event))
			{
				return 5;
			}

			if (static_cast<Button*>(m_texts[m_texts.size() - 2])->Check(m_mouseX, m_mouseY, event))
			{
				if (m_gameOver)
				{
					m_gameOver = false;
					m_show = true;
					SetupDesk();
					m_pauseTime = 0;
					m_renderGame();
					return 0;
				}
				else
				{
					m_pause = true;
					m_pauseTime = m_time;
					m_renderPause();
				}
			}

			if (event.type == SDL_KEYDOWN && !m_gameOver)
			{
				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
				{
					if (m_ypos > 0)
					{
						m_matrix[m_ypos--][m_xpos] = 0;
						if (m_matrix[m_ypos][m_xpos] == 1)
						{
							m_renderGameOver();
							m_matrix[m_ypos][m_xpos] = -1;
							return 0;
						}
						m_matrix[m_ypos][m_xpos] = 2;
					}
				}
				if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
				{
					if (m_ypos < SIZE - 1)
					{
						m_matrix[m_ypos++][m_xpos] = 0;
						if (m_matrix[m_ypos][m_xpos] == 1)
						{
							m_renderGameOver();
							m_matrix[m_ypos][m_xpos] = -1;
							return 0;
						}
						m_matrix[m_ypos][m_xpos] = 2;
					}
				}
				if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
				{
					if (m_xpos < SIZE - 1)
					{
						m_matrix[m_ypos][m_xpos++] = 0;
						if (m_matrix[m_ypos][m_xpos] == 1)
						{
							m_renderGameOver();
							m_matrix[m_ypos][m_xpos] = -1;
							return 0;
						}
						m_matrix[m_ypos][m_xpos] = 2;
					}
				}
				if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
				{
					if (m_xpos > 0)
					{
						m_matrix[m_ypos][m_xpos--] = 0;
						if (m_matrix[m_ypos][m_xpos] == 1)
						{
							m_renderGameOver();
							m_matrix[m_ypos][m_xpos] = -1;
							return 0;
						}
						m_matrix[m_ypos][m_xpos] = 2;
					}
				}

				if (m_xpos == SIZE - 1 && m_ypos == SIZE - 1)
				{
					m_renderWin();
					return 0;
				}

				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					if (m_gameOver)
					{
						m_gameOver = false;
						m_show = true;
						SetupDesk();
						m_pauseTime = 0;
						m_renderGame();
						return 0;
					}
					else
					{
						m_pause = true;
						m_pauseTime = m_time;
						m_renderPause();
					}
				}
			}
			if (event.type == SDL_QUIT)
			{
				return -1;
			}
			return 0;
		}
	}
	else
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (static_cast<Button*>(m_texts[m_texts.size() - 1])->Check(m_mouseX, m_mouseY, event))
			{
				m_pause = false;
				m_startTime = SDL_GetTicks();
				m_renderGame();
				return 0;
			}
		}
	}
	return Scene::HandleEvents();
}

void Game::SetupDesk()
{
	m_xpos = 0;
	m_ypos = 0;

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			m_field[i][j] = { m_width / 2 - FSIZE * SIZE / 2 + j * FSIZE, m_height / 2 - FSIZE * SIZE / 2 + i * FSIZE, FSIZE, FSIZE };
			m_matrix[i][j] = 0;
		}
	}
	random_device dev;
	mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> cell(0, SIZE - 1);
	int x = 0, y = 0;
	for (int i = 0; i < MINES; ++i)
	{
		while (x == 0 && y == 0 || x == SIZE - 1 && y == SIZE - 1)
		{
			x = cell(rng);
			y = cell(rng);
		}
		m_matrix[cell(rng)][cell(rng)] = 1;
	}
	m_matrix[m_xpos][m_ypos] = 2;
	m_matrix[SIZE - 1][SIZE - 1] = 3;
}