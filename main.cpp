#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include"item.hpp"
#include"SDL.hpp"
#include<windows.h>
using namespace std;

//音乐列表 

const char* Music_list[] = 
{
	"Music/Aoharu_Band_Arrange.mp3",
	"Music/Water_Drop.mp3"
};

bool isPlaying = false;
int Playtimes = 0;

void musicFinished()
{
	static Mix_Music* lastMusic = nullptr;

	if (lastMusic != nullptr) 
	{
		Mix_FreeMusic(lastMusic);
	}

	Playtimes = (Playtimes + 1) % 2;
	lastMusic = Mix_LoadMUS(Music_list[Playtimes]);
	Mix_PlayMusic(lastMusic, 0);
}


int main(int argc,char* argv[])
{
	
	// 初始化SDL及其扩展库
	init_SDL_ALL();
	//------------------
	
	//创造一个窗口
	SDL_Window* window = SDL_CreateWindow
	(
		"SuperMarketSystem",          // 窗口标题
		SDL_WINDOWPOS_CENTERED,		  // 初始x位置
		SDL_WINDOWPOS_CENTERED,       // 初始y位置
		1200,                         // 宽度
		843,                          // 高度
		SDL_WINDOW_SHOWN              // 窗口标志
	);
	if (!window) 
	{
		std::cerr << "无法创建窗口: " << SDL_GetError() << std::endl;
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	// 4. 为窗口创建渲染器
	SDL_Renderer* renderer = SDL_CreateRenderer
	(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!renderer) 
	{
		std::cerr << "无法创建渲染器: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	//IMGUI初始化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	// 5. 加载图片
	SDL_Surface* surface = IMG_Load("Image/First.jpg");
	if (!surface) 
	{
		std::cerr << "无法加载图片: " << IMG_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	// 6. 从surface创建纹理
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); // 释放surface，不再需要
	if (!texture) 
	{
		std::cerr << "无法创建纹理: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}
	
	// 加载音乐文件
	Mix_Music* music1 = Mix_LoadMUS("Music/Aoharu_Band_Arrange.mp3"); // 支持MP3, OGG, WAV等格式
	
	//音乐回调函数
	Mix_HookMusicFinished(musicFinished);

	// 7. 主循环
	bool quit = false;
	SDL_Event event;

	Mix_PlayMusic(music1, 0);


	while (!quit) 
	{
		// 处理事件
		while (SDL_PollEvent(&event)) 
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT) 
			{
				quit = true;
			}
		}
		//循环播放两首音乐
		
		// 开始新的ImGui帧
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		
		// 清除屏幕（设置为白色背景）
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

//SDL渲染器

		// 获取纹理尺寸
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

		// 设置目标矩形（居中显示）
		SDL_Rect dstRect;
		dstRect.x = (1200 - texW) / 2;
		dstRect.y = (843 - texH) / 2;
		dstRect.w = texW;
		dstRect.h = texH;

		// 复制纹理到渲染器
		SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	
//IMGUi 内容
		// 正确写法（修正图片中的命名空间和参数错误）
		ImGui::Begin("Control Panel", nullptr, ImGuiWindowFlags_NoCollapse);
		{
			// 设置窗口位置和大小（必须在Begin/End之间）
			ImGui::SetWindowPos(ImVec2(100, 50), ImGuiCond_FirstUseEver);
			ImGui::SetWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

			// 控件定位（修正图片中的错误冒号）
			ImGui::SetCursorPos(ImVec2(20, 40));  // 相对窗口的坐标
			if (ImGui::Button("Click Me"))
			{
				Mix_PauseMusic();
			}
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),renderer);

		// 更新屏幕
		SDL_RenderPresent(renderer);

		// 添加小延迟减少CPU占用
		SDL_Delay(10);
	}

	// 8. 清理资源
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	Mix_FreeMusic(music1);
	Mix_CloseAudio();

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return 0;
}
