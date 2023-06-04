#include "stdafx.h"
#include "Player.h"
#include "Background.h"
#include "Floor.h"
#include "Map.h"

Map::Map()
{
	bg = new Background();
	statPoint = new Floor(5);

	block = new Floor*[maxBlock];
	for (int i = 0; i < maxBlock; i++)
	{
		int rand = RANDOM->Int(0, 8);
		block[i] = new Floor(rand);
		blockCnt[i] = rand + 2;
	}

	statPoint->PushVector(this->floors, this->obstacles);
	for (int i = 0; i < maxBlock; i++)
		block[i]->PushVector(this->floors, this->obstacles);

	// 첫 블록 시작위치
	/*accumulatedDistance = 800;*/

	Init();
}

Map::~Map()
{
	bg->~Background();
}

void Map::Init()
{
	accumulatedDistance = 900;
	bg->Init();
	statPoint->Init(0);

	for (int i = 0; i < maxBlock; i++)
	{
		block[i]->Init(accumulatedDistance);
		accumulatedDistance += (blockCnt[i] * 100 + RANDOM->Int(100, 400));
	}

}

void Map::Update()
{
	bg->Update();
	statPoint->Update();

	for (auto& obj : this->floors)
		obj->Update();
	for (auto& obj : this->obstacles)
		obj->Update();
	for (int i = 0; i < maxBlock; i++)
		block[i]->Update();

	ImGui::Text("[accumulatedDistance] %d\n", accumulatedDistance);
}

void Map::Render(int type)
{
	if (type == 0)
		bg->Render(0);
	else if (type == 1)
		bg->Render(1);

	statPoint->Render();
	for (int i = 0; i < maxBlock; i++)
		block[i]->Render();
}

void Map::relocate(Vector2 playerPos)
{
	if (playerPos.x < 110)
	{
		//accumulatedDistance = 800;
		this->Init();
		return;
	}

	for (auto& obj : this->floors)
		if (playerPos.x - obj->GetWorldPos().x >= accumulatedDistance - 1000)
			obj->SetWorldPosX(obj->GetWorldPos().x + accumulatedDistance);
	/*
	for (auto& obj : this->obstacles)
		if (playerPos.x - obj->GetWorldPos().x >= 2000)
			obj->SetWorldPosX(obj->GetWorldPos().x + 3000);*/
}

void Map::play_bg(int type)
{
	if (type == 0)
		bg->bg_left();
	else if (type == 1)
		bg->bg_right();
}

void Map::collision(Player* target)
{
	// when collsion for floor
	for (auto& obj : this->floors)
	{
		obj->color = Color(1, 1, 1, 1);
		if (obj->Intersect(target->getCollider()))
		{
			obj->color = Color(1, 0, 0, 1);
		}
	}

	// when collision for obstacle
	for (auto& obj : this->obstacles)
	{
		obj->color = Color(1, 1, 1, 1);
		if (obj->Intersect(target->getCollider()))
		{
			obj->color = Color(1, 0, 0, 1);
			if (target->getDir() == PlayerDir::L)
			{
				target->getCollider()->MoveWorldPos(RIGHT * 1200 * DELTA);
				bg->bg_right();
			}
			else
			{
				target->getCollider()->MoveWorldPos(LEFT * 1200 * DELTA);
				bg->bg_left();
			}
		}
	}
}
