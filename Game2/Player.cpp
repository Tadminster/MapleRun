#include "stdafx.h"
#include "Player.h"
#include "Map.h"


Player::Player()
{
	collider = new ObRect();
	skin_idle[0] = new ObImage(L"player_idle_left.png");
	skin_idle[1] = new ObImage(L"player_idle_right.png");
	skin_run[0] = new ObImage(L"player_run_left.png");
	skin_run[1] = new ObImage(L"player_run_right.png");
	skin_jump[0] = new ObImage(L"player_jump_left.png");
	skin_jump[1] = new ObImage(L"player_jump_right.png");

	// PLAYER COLLISION
	collider->pivot = OFFSET_B;
	collider->scale.x = 30.0f;
	collider->scale.y = 60.0f;
	collider->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	collider->isFilled = false;
	collider->hasAxis = false;

	this->Init();

	// SKIN
	{
		// IDLE
		for (auto& idle : skin_idle)
		{
			idle->SetParentRT(*this->collider);
			idle->scale.x = idle->imageSize.x;
			idle->scale.y = idle->imageSize.y;
			idle->SetLocalPosY(34);
		}
		//skin_idle[0]->SetLocalPosX(-10);
		//skin_idle[1]->SetLocalPosX(10);
		
		// JUMP
		for (auto& jump : skin_jump)
		{
			jump->SetParentRT(*this->collider);
			jump->scale.x = jump->imageSize.x;
			jump->scale.y = jump->imageSize.y;
			jump->SetLocalPosY(34);
		}

		// RUN
		for (auto& run : skin_run)
		{
			run->SetParentRT(*this->collider);
			run->scale.x = run->imageSize.x / 4.0f;
			run->scale.y = run->imageSize.y;
			run->uv.z = 1.0f / 4.0f;
			run->SetLocalPosY(34);
		}
		skin_run[0]->SetLocalPosX(-10);
		skin_run[1]->SetLocalPosX(10);
	}
}

Player::~Player()
{
	for (auto& idle : skin_idle)
		delete idle;
	TEXTURE->DeleteTexture(L"player_idel_left.png");
	TEXTURE->DeleteTexture(L"player_idel_right.png");

	for (auto& jump : skin_jump)
		delete jump;
	TEXTURE->DeleteTexture(L"player_idel_left.png");
	TEXTURE->DeleteTexture(L"player_idel_right.png");

	for (auto& run : skin_run)
		delete run;
	TEXTURE->DeleteTexture(L"player_run_left.png");
	TEXTURE->DeleteTexture(L"player_run_right.png");

	delete collider;
}

bool Player::collision(Map* map)
{
	for (auto& obj : map->getObjects())
	{
		//obj->color = Color(1, 1, 1, 1);
		if (this->collider->Intersect(obj))
		{
			//obj->color = Color(1, 0, 0, 1);
			return true;
		}

	}
	return false;
}

void Player::Init()
{
	collider->SetWorldPos(Vector2(100, -150));
	state = PlayerState::IDLE;
	dir = PlayerDir::R;
}

void Player::Update(Map* map)
{
	this->Control();
	this->collider->Update();

	if (collider->GetWorldPos().y <= -500) this->Init();

	if (state != PlayerState::IDLE)
	{
		map->bg_right();
		this->collider->MoveWorldPos(RIGHT * 400 * DELTA);
	}
	if (state == PlayerState::JUMP)
	{
		this->gravity += 400.f * DELTA;
		this->collider->MoveWorldPos(DOWN * gravity * DELTA);
		if (this->collider->GetWorldPos().y < -155 && this->collision(map))
		{
			this->collider->SetWorldPosY(-155);
			this->state = PlayerState::RUN;
			gravity = 0;
		}
	}
	else if (state == PlayerState::RUN)
	{
		if (!this->collision(map))
		{
			this->gravity += 400.f * DELTA;
			this->collider->MoveWorldPos(DOWN * gravity * DELTA);
		}
		else if (this->collision(map) && collider->GetWorldPos().y > -155)
			gravity = 0;

		static float tickCount = 0.0f;
		if (TIMER->GetTick(tickCount, 0.1f))
			for (auto& playerSkin : this->skin_run)
			{
				playerSkin->uv.z += 1.0f / 4.0f;
				playerSkin->uv.x += 1.0f / 4.0f;
			}
	}



	//static float tickCount = 0.0f;
	//if (TIMER->GetTick(tickCount, 0.1f))
	//{
	//	if (INPUT->KeyPress(VK_LEFT))
	//	{
	//		
	//		for (auto& playerSkin : this->skin_run)
	//		{
	//			playerSkin->uv.z -= 1.0f / 4.0f;
	//			playerSkin->uv.x -= 1.0f / 4.0f;
	//		}
	//	}
	//	if (INPUT->KeyPress(VK_RIGHT))
	//	{
	//		for (auto& playerSkin : this->skin_run)
	//		{
	//			playerSkin->uv.z += 1.0f / 4.0f;
	//			playerSkin->uv.x += 1.0f / 4.0f;
	//		}
	//	}

	//}

	for (auto& idle : this->skin_idle)
		idle->Update();
	for (auto& jump : this->skin_jump)
		jump->Update();
	for (auto& run : this->skin_run)
		run->Update();
}

void Player::Render()
{
	this->collider->Render();

	if (state == PlayerState::IDLE && dir == PlayerDir::L)
		skin_idle[0]->Render();
	else if (state == PlayerState::IDLE && dir == PlayerDir::R)
		skin_idle[1]->Render();

	else if (state == PlayerState::JUMP && dir == PlayerDir::L)
		skin_jump[0]->Render();
	else if (state == PlayerState::JUMP && dir == PlayerDir::R)
		skin_jump[1]->Render();

	else if (state == PlayerState::RUN && dir == PlayerDir::L)
		skin_run[0]->Render();
	else if (state == PlayerState::RUN && dir == PlayerDir::R)
		skin_run[1]->Render();


}

void Player::Control()
{	
	if (DEBUG_MODE)
	{ 
		// When IDEL, RUN
		if (state == PlayerState::IDLE || state == PlayerState::RUN)
			// can JUMP
			if (INPUT->KeyDown(VK_UP))
			{
				this->collider->SetWorldPosY(collider->GetWorldPos().y + 5);
				state = PlayerState::JUMP;
				gravity = -250.0f;
			}
		// When DEBUG, can DOWN
		if (INPUT->KeyDown(VK_DOWN))
		{
			this->collider->MoveWorldPos(DOWN * 500.0f * DELTA);
		}

		// When NOT JUMP, can change state
		// Direction always changes
		if (INPUT->KeyDown(VK_LEFT))
		{
			dir = PlayerDir::L;

			if (state != PlayerState::JUMP)
				state = PlayerState::RUN;
		}
		if (INPUT->KeyDown(VK_RIGHT))
		{
			dir = PlayerDir::R;

			if (state != PlayerState::JUMP)
				state = PlayerState::RUN;
		}

		// KeyUP while Running, change state to IDLE
		if (state == PlayerState::RUN && (INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp(VK_RIGHT)))
		{
			state = PlayerState::IDLE;
		}

		// can always Move
		if (INPUT->KeyPress(VK_LEFT))
		{
			this->collider->MoveWorldPos(LEFT * 500.0f * DELTA);
		}
		if (INPUT->KeyPress(VK_RIGHT))
		{
			this->collider->MoveWorldPos(RIGHT * 500.0f * DELTA);
		}
	}
	else
	{
		if (state == PlayerState::IDLE)
			if (INPUT->KeyDown(VK_SPACE))
			{
				state = PlayerState::RUN;
			}

		// When IDEL, RUN
		if (state == PlayerState::RUN)
		// can JUMP
			if (INPUT->KeyDown(VK_UP))
			{
				this->collider->SetWorldPosY(collider->GetWorldPos().y + 5);
				state = PlayerState::JUMP;
				gravity = -250.0f;
			}
	}

}
