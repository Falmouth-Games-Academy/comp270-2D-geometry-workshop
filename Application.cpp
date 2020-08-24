#include "stdafx.h"
#include "Application.h"
#include "Vector2h.h"

// Constructor -- initialise application-specific data here
Application::Application()
{
}

// Destructor -- delete any pointers/allocated memory
Application::~Application()
{
}

// Run the application
// Return true if the application finishes successfully, or false if an error occurs
bool Application::run()
{
	// Initialisation
	if (!initSDL())
		return false;

	// Initialise the drawing class
	m_draw.init(c_max_x, c_max_y, c_windowWidth, c_windowHeight, m_renderer);

	// Set up the scene (including creating shapes)
	m_scene.setup(c_max_x, c_max_y);

	// Main loop
	m_quit = false;
	while (!m_quit)
	{
		// Process events
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			processEvent(ev);
		}

		// Update objects
		update();

		// Render
		render();
		SDL_RenderPresent(m_renderer);
	}

	// Shutdown
	shutdownSDL();
	return true;
}

// Initialise the required parts of the SDL library
// Return true if initialisation is successful, or false if initialisation fails
bool Application::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_window = SDL_CreateWindow("COMP270", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, c_windowWidth, c_windowHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

// Shutdown the SDL library
void Application::shutdownSDL()
{
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}

	SDL_Quit();
}

// Process a single event
void Application::processEvent(const SDL_Event &ev)
{
	switch (ev.type)
	{
	case SDL_QUIT:
		m_quit = true;
		break;

	case SDL_KEYDOWN:
		if (ev.key.keysym.sym == SDLK_ESCAPE)
		{
			m_quit = true;
		}

		break;
	}
}

// Called every time the main application loop runs
void Application::update()
{
	// TO DO: Add any time-varying updates to objects here
}

// Render the scene
void Application::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	m_draw.drawAxes();
	m_draw.drawObjects(m_scene.getObjects());
}

// Application entry point
int main(int, char**)
{
	Application application;
	if (application.run())
		return 0;
	else
		return 1;
}
