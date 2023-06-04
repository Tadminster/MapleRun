#pragma once
class Background
{
private:
	ObImage* bg_0;
	ObImage* bg_1;
	ObImage* bg_2;
	ObImage* bg_3;
	ObImage* bg_5;

public:
	Background();
	~Background();

	void Init();
	void Update();
	void Render(int type);

	void bg_left();
	void bg_right();
};