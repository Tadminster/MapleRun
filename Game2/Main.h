#pragma once
class Main : public Scene
{
private:
	ObImage* bg;
	ObImage* bg_1;
	ObImage* bg_2;
	ObImage* bg_3;
	ObImage* bg_4;
	ObImage* player[2];

	int playerDir;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
