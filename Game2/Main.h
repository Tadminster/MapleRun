﻿#pragma once
class Main : public Scene
{
private:
	ObImage* bg;
	ObImage* bg_1;
	ObImage* bg_2;
	ObImage* bg_3;
	ObImage* bg_4;
	class Player* player;
	//ObImage* player[2];

	//int playerDir;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
