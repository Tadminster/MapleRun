#include "stdafx.h"
#include "Player.h"
#include "Background.h"
#include "Map.h"

Map::Map()
{
	bg = new Background();

	for (auto& objs : floor)
	{
		objs = new ObRect;
		//objs->isFilled = false;
		objs->pivot = OFFSET_LB;
		objs->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
		floors.emplace_back(objs);
	}

	for (auto& objs : floor_side)
	{
		objs = new ObRect;
		//objs->isFilled = false;
		objs->pivot = OFFSET_T;
		objs->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
		obstacles.emplace_back(objs);
	}

	for (auto& objs : obstacle)
	{
		objs = new ObRect;
		//objs->isFilled = false;
		objs->pivot = OFFSET_LB;
		objs->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
		obstacles.emplace_back(objs);
	}

	Init();
}

Map::~Map()
{
	bg->~Background();
}

void Map::Init()
{
	floor[0]->scale.x = 500.0f;
	floor[0]->scale.y = 5.f;
	floor[0]->SetWorldPos(Vector2(0.0f, -160)); // 0->500

	floor_side[0]->scale.x = 5.0f;
	floor_side[0]->scale.y = 200.f;
	floor_side[0]->SetWorldPos(Vector2(floor[0]->GetWorldPos().x, -160)); // 0->500

	floor_side[1]->scale.x = 5.0f;
	floor_side[1]->scale.y = 200.f;
	floor_side[1]->SetWorldPos(Vector2(floor[0]->GetWorldPos().x + floor[0]->scale.x, -160)); // 0->500

	floor[1]->scale.x = 400.0f;
	floor[1]->scale.y = 5.f;
	floor[1]->SetWorldPos(Vector2(600.0f, -160)); // 600->1000

	floor_side[2]->scale.x = 5.0f;
	floor_side[2]->scale.y = 200.f;
	floor_side[2]->SetWorldPos(Vector2(floor[1]->GetWorldPos().x, -160)); // 0->500

	floor_side[3]->scale.x = 5.0f;
	floor_side[3]->scale.y = 200.f;
	floor_side[3]->SetWorldPos(Vector2(floor[1]->GetWorldPos().x + floor[1]->scale.x, -160)); // 0->500

	floor[2]->scale.x = 300.0f;
	floor[2]->scale.y = 5.f;
	floor[2]->SetWorldPos(Vector2(1200.0f, -160)); // 1200->100

	floor_side[4]->scale.x = 5.0f;
	floor_side[4]->scale.y = 200.f;
	floor_side[4]->SetWorldPos(Vector2(floor[2]->GetWorldPos().x, -160)); // 0->500

	floor_side[5]->scale.x = 5.0f;
	floor_side[5]->scale.y = 200.f;
	floor_side[5]->SetWorldPos(Vector2(floor[2]->GetWorldPos().x + floor[2]->scale.x, -160)); // 0->500

	floor[3]->scale.x = 700.0f;
	floor[3]->scale.y = 5.f;
	floor[3]->SetWorldPos(Vector2(1800.0f, -160)); // 1800->2500

	floor_side[6]->scale.x = 5.0f;
	floor_side[6]->scale.y = 200.f;
	floor_side[6]->SetWorldPos(Vector2(floor[3]->GetWorldPos().x, -160)); // 0->500

	floor_side[7]->scale.x = 5.0f;
	floor_side[7]->scale.y = 200.f;
	floor_side[7]->SetWorldPos(Vector2(floor[3]->GetWorldPos().x + floor[3]->scale.x, -160)); // 0->500

	floor[4]->scale.x = 200.0f;
	floor[4]->scale.y = 5.f;
	floor[4]->SetWorldPos(Vector2(2700.0f, -160)); // 2700->3000

	floor_side[8]->scale.x = 5.0f;
	floor_side[8]->scale.y = 200.f;
	floor_side[8]->SetWorldPos(Vector2(floor[4]->GetWorldPos().x, -160)); // 0->500

	floor_side[9]->scale.x = 5.0f;
	floor_side[9]->scale.y = 200.f;
	floor_side[9]->SetWorldPos(Vector2(floor[4]->GetWorldPos().x + floor[4]->scale.x, -160)); // 0->500



	obstacle[0]->scale.x = 5;
	obstacle[0]->scale.y = 50.f;
	obstacle[0]->SetWorldPos(Vector2(300, -160)); // 2700->3000

	obstacle[1]->scale.x = 5;
	obstacle[1]->scale.y = 50.f;
	obstacle[1]->SetWorldPos(Vector2(700, -050)); // 2700->3000

	obstacle[2]->scale.x = 5;
	obstacle[2]->scale.y = 50.f;
	obstacle[2]->SetWorldPos(Vector2(1400, -160)); // 2700->3000

	obstacle[3]->scale.x = 5;
	obstacle[3]->scale.y = 75.f;
	obstacle[3]->SetWorldPos(Vector2(1850, -160)); // 2700->3000

	obstacle[4]->scale.x = 5;
	obstacle[4]->scale.y = 75.f;
	obstacle[4]->SetWorldPos(Vector2(2400, -160)); // 2700->3000
}

void Map::Update()
{
	bg->Update();

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

	for (auto& obj : this->floors)
		obj->Render();
	for (auto& obj : this->obstacles)
		obj->Render();
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
