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
#include "common.hpp"
#include "client.hpp"

namespace betacore
{

class Game
{
private:
	SDL_Window *WINDOW = NULL;
	SDL_GLContext glContext;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	int MONITOR_WIDTH=1920;
	int MONITOR_HEIGHT=1080;
	const char *TITLE ;
	bool KEEP_ALIVE = true;
	bool SHOW_GRID = false;
	SHAPE USER_CURRENT = TRIANGLE;
	SHAPE GUST_CURRENT = 	UNKOWN;
	MODE ME;
	bool KEY_UP_ARROW_ACTIVE = false;
	bool KEY_DOWN_ARROW_ACTIVE = false;
	bool KEY_LEFT_ARROW_ACTIVE = false;
	bool KEY_RIGHT_ARROW_ACTIVE = false;
	bool KEY_SPACE_ACTIVE = false;
	bool KEY_RETURN_ACTIVE = false;
	bool FULL_SCREEN = false;
	Client* client = nullptr;
public:
	Game(MODE mode,
	  int port, 
		std::string url);
	~Game();
	int init();
	int initGL();
	void box();
	void close();
	void grid();
	void paint();
	void events( SDL_Event &event );
	void key_down(SDL_Keycode key_code);
	void key_up(SDL_Keycode key_code);
	void resize ( int width, int height );
	void triangle();
	void triangle(bool filled);
	void square();
	void square(bool filled);
	void circle();
	void circle(bool filled);
	void pentagon();
	void pentagon(bool filled);
	void rectangle();
	void cross(bool filled);
	void compass();
	
	void on_key_up_arrow();
	void on_key_down_arrow();
	void on_key_left_arrow();
	void on_key_right_arrow();
	void on_key_space();
	void on_key_enter();

	void top_screen();
	void user_screen();
	void guest_screen();

	void update(SHAPE &s,MODE &m);
};
} // namespace betacore
#endif