#pragma once
class Map
{
private:
	ObImage* bg;
	ObImage* bg_1;
	ObImage* bg_2;
	ObImage* bg_3;
	ObImage* bg_4;

	ObRect* floor[5];
	vector<ObRect*> Objects;

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


	//bool collision(GameObject* target);
	vector<ObRect*>& getObjects() { return Objects; }
	void relocate(Vector2 playerPos);
};

