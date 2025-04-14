#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include"item.hpp"
#include"SDL.hpp"
#include<windows.h>
using namespace std;

//�����б� 

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
	
	// ��ʼ��SDL������չ��
	init_SDL_ALL();
	//------------------
	
	//����һ������
	SDL_Window* window = SDL_CreateWindow
	(
		"SuperMarketSystem",          // ���ڱ���
		SDL_WINDOWPOS_CENTERED,		  // ��ʼxλ��
		SDL_WINDOWPOS_CENTERED,       // ��ʼyλ��
		1200,                         // ���
		843,                          // �߶�
		SDL_WINDOW_SHOWN              // ���ڱ�־
	);
	if (!window) 
	{
		std::cerr << "�޷���������: " << SDL_GetError() << std::endl;
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	// 4. Ϊ���ڴ�����Ⱦ��
	SDL_Renderer* renderer = SDL_CreateRenderer
	(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!renderer) 
	{
		std::cerr << "�޷�������Ⱦ��: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	//IMGUI��ʼ��
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	// 5. ����ͼƬ
	SDL_Surface* surface = IMG_Load("Image/First.jpg");
	if (!surface) 
	{
		std::cerr << "�޷�����ͼƬ: " << IMG_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	// 6. ��surface��������
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); // �ͷ�surface��������Ҫ
	if (!texture) 
	{
		std::cerr << "�޷���������: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return -1;
	}
	
	// ���������ļ�
	Mix_Music* music1 = Mix_LoadMUS("Music/Aoharu_Band_Arrange.mp3"); // ֧��MP3, OGG, WAV�ȸ�ʽ
	
	//���ֻص�����
	Mix_HookMusicFinished(musicFinished);

	// 7. ��ѭ��
	bool quit = false;
	SDL_Event event;

	Mix_PlayMusic(music1, 0);


	while (!quit) 
	{
		// �����¼�
		while (SDL_PollEvent(&event)) 
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT) 
			{
				quit = true;
			}
		}
		//ѭ��������������
		
		// ��ʼ�µ�ImGui֡
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		
		// �����Ļ������Ϊ��ɫ������
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

//SDL��Ⱦ��

		// ��ȡ����ߴ�
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

		// ����Ŀ����Σ�������ʾ��
		SDL_Rect dstRect;
		dstRect.x = (1200 - texW) / 2;
		dstRect.y = (843 - texH) / 2;
		dstRect.w = texW;
		dstRect.h = texH;

		// ����������Ⱦ��
		SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	
//IMGUi ����
		// ��ȷд��������ͼƬ�е������ռ�Ͳ�������
		ImGui::Begin("Control Panel", nullptr, ImGuiWindowFlags_NoCollapse);
		{
			// ���ô���λ�úʹ�С��������Begin/End֮�䣩
			ImGui::SetWindowPos(ImVec2(100, 50), ImGuiCond_FirstUseEver);
			ImGui::SetWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

			// �ؼ���λ������ͼƬ�еĴ���ð�ţ�
			ImGui::SetCursorPos(ImVec2(20, 40));  // ��Դ��ڵ�����
			if (ImGui::Button("Click Me"))
			{
				Mix_PauseMusic();
			}
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),renderer);

		// ������Ļ
		SDL_RenderPresent(renderer);

		// ���С�ӳټ���CPUռ��
		SDL_Delay(10);
	}

	// 8. ������Դ
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
