#pragma once
class Map
{
private:
	/*ObImage* bg_0;
	ObImage* bg_1;
	ObImage* bg_2;
	ObImage* bg_3;
	ObImage* bg_5;*/
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

	void play_bg(int type);
	//void bg_left();
	//void bg_right();
};

