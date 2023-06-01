#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	this->scale.x = 60.0f;
	this->scale.y = 120.0f;
	this->SetWorldPos(Vector2(0.0f, -95.0f));
	this->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	this->isFilled = false;
	this->hasAxis = false;

	playerDir = 1;
	
	player_skin[0] = new ObImage(L"player_left.png");
	player_skin[1] = new ObImage(L"player_right.png");

	for (auto& player : this->player_skin)
	{
		player->SetParentRT(*this);
		player->scale.x = player->imageSize.x * 2.0f / 4.0f;
		player->scale.y = player->imageSize.y * 2.0f;
		player->uv.z = 1.0f / 4.0f;
	}
	player_skin[0]->SetLocalPosX(-10);
	player_skin[1]->SetLocalPosX(10);
}

Player::~Player()
{
	for (auto& playerSkin : this->player_skin)
		delete playerSkin;
	TEXTURE->DeleteTexture(L"player_left.png");
	TEXTURE->DeleteTexture(L"player_right.png");
}

void Player::Update()
{
	ObRect::Update();


	static float tickCount = 0.0f;
	if (TIMER->GetTick(tickCount, 0.1f))
	{
		if (INPUT->KeyPress(VK_LEFT))
		{
			this->playerDir = 0;
			for (auto& playerSkin : this->player_skin)
			{
				playerSkin->uv.z -= 1.0f / 4.0f;
				playerSkin->uv.x -= 1.0f / 4.0f;
			}
		}
		if (INPUT->KeyPress(VK_RIGHT))
		{
			this->playerDir = 1;
			for (auto& playerSkin : this->player_skin)
			{
				playerSkin->uv.z += 1.0f / 4.0f;
				playerSkin->uv.x += 1.0f / 4.0f;
			}
		}
	}

	for (auto& player : this->player_skin)
		player->Update();
}

void Player::Render()
{
	//ObRect::Render();

	if (playerDir == 0)
		player_skin[0]->Render();
	else if (playerDir == 1)
		player_skin[1]->Render();
}

void Player::Control()
{

	
}
