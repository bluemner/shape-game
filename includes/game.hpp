#ifndef __BETACORE_GAME_HPP__
#define __BETACORE_GAME_HPP__

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#include <Windows.h>
#include <GLU.h>
#include <GL/gl.h>
#elif linux
#include <GL/glu.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#define PI 3.14159265359
namespace betacore
{
enum SHAPE{
	NONE,
	TRIANGLE,
	CIRCLE,
	SQUARE,
	PENTAGON
};
class Game
{
private:
	SDL_Window *WINDOW = NULL;
	SDL_GLContext glContext;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const char *TITLE = "Lesson 01";
	bool KEEP_ALIVE = true;
	bool SHOW_GRID = false;
	SHAPE USER_CURRENT = TRIANGLE;

public:
	Game();
	~Game();
	int init();
	int initGL();
	void box();
	void close();
	void grid();
	void paint();
	void events( SDL_Event &event );
	void key_down(SDL_Keycode key_code);
	void resize ( int width, int height );
	void triangle();
	void square();
	void circle();
	void pentagon();
	
	void on_key_up_arrow();
	void on_key_down_arrow();
	void on_key_left_arrow();
	void on_key_right_arrow();
	void on_key_space();
	void on_key_enter();
	void top_screen();
	void user_screen();
	void guest_screen();
};
} // namespace betacore
#endif