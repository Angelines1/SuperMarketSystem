#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
using namespace std;

void init_SDL_ALL()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer³õÊ¼»¯Ê§°Ü: %s\n", Mix_GetError());
		return ;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cerr << "SDL³õÊ¼»¯Ê§°Ü: " << SDL_GetError() << std::endl;
		return ;
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags)) 
	{
		std::cerr << "SDL_image³õÊ¼»¯Ê§°Ü: " << IMG_GetError() << std::endl;
		SDL_Quit();
		return ;
	}

}

//¼ÓÔØÍ¼Æ¬

//¼ÓÔØÒôÀÖ