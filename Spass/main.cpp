#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
#include <iostream>

//to catch errors and signalize user what is wrong
void fatal_error(const std::string& error)
{
	std::cout << error << std::endl;
}

int main(int argc, char* argv[])
{
	const int width = 1280;
	const int height = 720;
	
	
	//initialization of SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//creation of my window that we can display anything
	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		fatal_error("Could not initialize window");
		return 1;
	}
	//create glContext to get use of glew --> opengl
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		fatal_error("Could not create gl Context");
		return 1;
	}

	//init glew for opengl
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatal_error("Could not initialize glew");
		return 1;
	}
	//clear color and make color pink
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	//"isRunning" to quit when user wants and not when program wants
	bool isRunning = true;
	while (isRunning)
	{
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT: isRunning = false; break;
			}
		}

		//clear everything and set our new color
		glClear(GL_COLOR_BUFFER_BIT);

		//swap to our window
		SDL_GL_SwapWindow(window);
	}

	return 0;
}