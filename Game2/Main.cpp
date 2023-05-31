#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	bg = new ObImage(L"bg_background.png");
	bg_1 = new ObImage(L"bg_ground_flower.png");
	bg_2 = new ObImage(L"bg_ground_extend.png");
	bg_3 = new ObImage(L"bg_ground_weeds.png");
	bg_4 = new ObImage(L"bg_ground_trees.png");

	player[0] = new ObImage(L"player_left.png");
	player[1] = new ObImage(L"player_right.png");
	for (auto& player : this->player)
	{
		player->scale.x = player->imageSize.x * 2.0f / 4.0f;
		player->scale.y = player->imageSize.y * 2.0f;
		player->uv.z = 1.0f / 4.0f;
		player->SetWorldPosY(-(app.GetHeight() - 450.f) / 2.0f);
	}
	playerDir = 1; // 기본 방향은 오른쪽


	bg->scale.x = app.GetWidth();
	bg->scale.y = app.GetHeight();
	bg_1->scale.x = app.GetWidth();
	bg_1->scale.y = app.GetHeight();
	bg_2->scale.x = app.GetWidth();
	bg_2->scale.y = app.GetHeight();
	bg_3->scale.x = app.GetWidth();
	bg_3->scale.y = app.GetHeight();
	bg_4->scale.x = app.GetWidth();
	bg_4->scale.y = app.GetHeight();

	//bg->imageSize.x *= 2.0f;
	//bg->imageSize.y *= 2.0f;
	bg_1->imageSize.x *= 2.0f;
	bg_1->imageSize.y *= 2.0f;
	bg_2->imageSize.x *= 2.0f;
	bg_2->imageSize.y *= 2.0f;
	bg_3->imageSize.x *= 2.0f;
	bg_3->imageSize.y *= 2.0f;
	bg_4->imageSize.x *= 2.0f;
	bg_4->imageSize.y *= 2.0f;

	bg->uv.z = app.GetWidth() / bg->imageSize.x;
	bg_1->uv.z = app.GetWidth() / bg->imageSize.x;
	bg_2->uv.z = app.GetWidth() / bg_2->imageSize.x;
	bg_3->uv.z = app.GetWidth() / bg_3->imageSize.x;
	bg_4->uv.z = app.GetWidth() / bg_4->imageSize.x;

	bg->space = SPACE::SCREEN;
	bg_1->space = SPACE::SCREEN;
	bg_2->space = SPACE::SCREEN;
	bg_3->space = SPACE::SCREEN;
	bg_4->space = SPACE::SCREEN;
}

Main::~Main()
{
	delete bg;
	delete bg_2;
	delete bg_3;
	TEXTURE->DeleteTexture(L"Oven1.png");
	TEXTURE->DeleteTexture(L"bg_ground_extend.png");
	TEXTURE->DeleteTexture(L"bg_ground_weeds.png");
}
void Main::Init()
{
	
}

void Main::Release()
{
}

void Main::Update()
{
	static float tickCount = 0.0f;

	if (INPUT->KeyPress(VK_LEFT))
	{
		playerDir = 0;

		//초당 한장 지나가는속도 -> 초당 1픽셀 속도 * 300

		bg->uv.x -= DELTA * 10.0f / bg->imageSize.x;
		bg->uv.z -= DELTA * 10.0f / bg->imageSize.x;

		bg_1->uv.x -= DELTA * 260.0f / bg_1->imageSize.x;
		bg_1->uv.z -= DELTA * 260.0f / bg_1->imageSize.x;

		bg_2->uv.x -= DELTA * 350.0f / bg_2->imageSize.x;
		bg_2->uv.z -= DELTA * 350.0f / bg_2->imageSize.x;

		bg_3->uv.x -= DELTA * 200.0f / bg_3->imageSize.x;
		bg_3->uv.z -= DELTA * 200.0f / bg_3->imageSize.x;

		bg_4->uv.x -= DELTA * 100.0f / bg_4->imageSize.x;
		bg_4->uv.z -= DELTA * 100.0f / bg_4->imageSize.x;

		if (TIMER->GetTick(tickCount, 0.1f))
		{
			for (auto& player : this->player)
			{
				player->uv.z -= 1.0f / 4.0f;
				player->uv.x -= 1.0f / 4.0f;
			}
		}
	}

	if (INPUT->KeyPress(VK_RIGHT))
	{
		playerDir = 1;
		
		//초당 한장 지나가는속도 -> 초당 1픽셀 속도 * 300

		bg->uv.x += DELTA * 10.0f / bg->imageSize.x;
		bg->uv.z += DELTA * 10.0f / bg->imageSize.x;

		bg_1->uv.x += DELTA * 260.0f / bg_1->imageSize.x;
		bg_1->uv.z += DELTA * 260.0f / bg_1->imageSize.x;

		bg_2->uv.x += DELTA * 350.0f / bg_2->imageSize.x;
		bg_2->uv.z += DELTA * 350.0f / bg_2->imageSize.x;

		bg_3->uv.x += DELTA * 200.0f / bg_3->imageSize.x;
		bg_3->uv.z += DELTA * 200.0f / bg_3->imageSize.x;

		bg_4->uv.x += DELTA * 100.0f / bg_4->imageSize.x;
		bg_4->uv.z += DELTA * 100.0f / bg_4->imageSize.x;

		if (TIMER->GetTick(tickCount, 0.1f))
		{
			for (auto& player : this->player)
			{
				player->uv.z += 1.0f / 4.0f;
				player->uv.x += 1.0f / 4.0f;
			}
		}
	}
		
	bg->Update();
	bg_1->Update();
	bg_2->Update();
	bg_3->Update();
	bg_4->Update();
	for (auto& player : this->player)
		player->Update();

}

void Main::LateUpdate()
{
}

void Main::Render()
{
	bg->Render();
	bg_4->Render();
	bg_3->Render();
	bg_2->Render();
	if (playerDir == 0)
		player[0]->Render();
	else if (playerDir == 1)
		player[1]->Render();
	bg_1->Render();
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