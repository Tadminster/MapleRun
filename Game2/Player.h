#pragma once
class Player : public ObRect
{
private:
	ObImage* player_skin[2];

	int playerDir;

public:
	Player();
	~Player() override;

	void Update() override;
	void Render() override;
	virtual void Control();
};

