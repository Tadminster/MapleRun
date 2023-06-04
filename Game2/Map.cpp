#include "stdafx.h"
#include "Player.h"
#include "Background.h"
#include "Floor.h"
#include "Map.h"

Map::Map()
{
	bg = new Background();
	floor_test = new Floor(5);

	floor_test->PushVector(this->floors, this->obstacles);
	//for (auto& objs : floor)
	//{
	//	objs = new ObRect;
	//	//objs->isFilled = false;
	//	objs->pivot = OFFSET_LB;
	//	objs->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	//	floors.emplace_back(objs);
	//}

	//for (auto& objs : floor_side)
	//{
	//	objs = new ObRect;
	//	//objs->isFilled = false;
	//	objs->pivot = OFFSET_T;
	//	objs->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	//	obstacles.emplace_back(objs);
	//}

	//for (auto& objs : obstacle)
	//{
	//	objs = new ObRect;
	//	//objs->isFilled = false;
	//	objs->pivot = OFFSET_LB;
	//	objs->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	//	obstacles.emplace_back(objs);
	//}

	Init();
}

Map::~Map()
{
	bg->~Background();
}

void Map::Init()
{
	bg->Init();
	floor_test->Init(0);
}

void Map::Update()
{
	bg->Update();
	floor_test->Update();

	for (auto& obj : this->floors)
		obj->Update();
	for (auto& obj : this->obstacles)
		obj->Update();
}

void Map::Render(int type)
{
	if (type == 0)
		bg->Render(0);
	else if (type == 1)
		bg->Render(1);

	floor_test->Render();
}

void Map::relocate(Vector2 playerPos)
{
	if (playerPos.x < 110)
	{
		this->Init();
		return;
	}

	for (auto& obj : this->floors)
		if (playerPos.x - obj->GetWorldPos().x >= 2000)
			obj->SetWorldPosX(obj->GetWorldPos().x + 3000);
	for (auto& obj : this->obstacles)
		if (playerPos.x - obj->GetWorldPos().x >= 2000)
			obj->SetWorldPosX(obj->GetWorldPos().x + 3000);
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
				target->getCollider()->MoveWorldPos(RIGHT * 400 * DELTA);
				bg->bg_right();
			}
			else
			{
				target->getCollider()->MoveWorldPos(LEFT * 400 * DELTA);
				bg->bg_left();
			}
		}
	}
}
