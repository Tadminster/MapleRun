#include "stdafx.h"
#include "Player.h"
#include "Main.h"
#include "Map.h"


Main::Main()
{
	map = new Map();
	player = new Player();
}

Main::~Main()
{
	player->~Player();
	map->~Map();
}
void Main::Init()
{
	
}

void Main::Release()
{
}

void Main::Update()
{
	{	// DEBUG TEXT OUTPUT
		if (debug)
		{
			ImGui::Text("[ MOUSE_X ] %f\n", INPUT->GetWorldMousePos().x);
			ImGui::Text("[ MOUSE_Y ] %f\n", INPUT->GetWorldMousePos().y);
			ImGui::Text("\n");

			ImGui::Text("[ PLAYER_X ] %f\n", player->getPos().x);
			ImGui::Text("[ PLAYER_Y ] %f\n", player->getPos().y);
			ImGui::Text("[ PLAYER_G ] %f\n", player->getGravity());
		}
		else
		{
			ImGui::Text("KEYS");
			ImGui::Text("[ VK_LEFT  ] LEFT  MOVE \n");
			ImGui::Text("[ VK_RIGHT ] RIGHT MOVE \n");
		}
	}
	
	map->Update();
	map->relocate(player->getPos());
	player->Update(map);
	CAM->position.x = player->getPos().x;

}

void Main::LateUpdate()
{
}

void Main::Render()
{
	map->Render(0);
	player->Render();
	map->Render(1);
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1000.0f, 640.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}