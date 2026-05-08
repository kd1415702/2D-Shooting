#pragma once

#include"../BaseObject.h"


class Game;
class Player;

class Bullet : public BaseObject
{
public:

	Bullet() {};
	~Bullet()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetPos(Math::Vector2 pos) { m_Pos = pos; }

	void SetOwner(Game* owner) { m_owner = owner; }


	void SetFlg(bool flg)override { m_Flg = flg; }

	void SetRect(int x, int y) { m_RectX = x, m_RectY = y; }
private:

	void Release();


	Game* m_owner = nullptr;

	std::shared_ptr<Player> m_Player = nullptr;
	
	//切り取り開始位置
	int m_RectX;
	int m_RectY;
	
};