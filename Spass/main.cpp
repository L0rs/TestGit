#include <SDL\SDL.h>
#include <GL\glew.h>

int main(int argc, char* argv[])
{
	const int width = 1280;
	const int height = 720;
	int error;
	
	//initialization of SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//creation of my window that we can display anything
	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	
	//create glContext to get use of glew --> opengl
	SDL_GL_CreateContext(window);

	//init glew for opengl
	glewInit();

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	bool isRunning = true;
	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	return 0;
}