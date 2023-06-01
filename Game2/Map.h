#pragma once
class Map
{
private:
	ObImage* bg;
	ObImage* bg_1;
	ObImage* bg_2;
	ObImage* bg_3;
	ObImage* bg_4;
public:
	Map();
	~Map();
	
	void Update();
	/*
	* PARAM type == 0, BACK RENDER
	* PARAM type == 1, FRONT RENDER
	*/
	void Render(int type);
};

