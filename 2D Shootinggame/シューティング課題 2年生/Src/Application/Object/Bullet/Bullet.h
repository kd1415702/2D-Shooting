#pragma once

#include"../BaseObject.h"


class Game;

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


private:

	void Release();

	Game* m_owner = nullptr;


	
	
};