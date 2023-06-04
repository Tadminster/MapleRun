﻿#pragma once
class Map
{
private:
	class Background* bg;

	ObRect* floor[5];
	ObRect* floor_side[10];
	ObRect* obstacle[5];
	vector<ObRect*> floors;
	vector<ObRect*> obstacles;

public:
	Map();
	~Map();
	
	void Init();
	void Update();
	/*
	* PARAM type == 0, BACK RENDER
	* PARAM type == 1, FRONT RENDER
	*/
	void Render(int type);


	void collision(class Player* target);
	vector<ObRect*>& getObjects() { return floors; }
	void relocate(Vector2 playerPos);

	/*
	* PARAM type == 0, LEFT PLAY
	* PARAM type == 1, RIGHT PLAY
	*/
	void play_bg(int type);
};

