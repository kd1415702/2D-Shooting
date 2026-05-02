#pragma once

#include"../BaseObject.h"


class Game;

class Bullet : public BaseObject
{
public:

	Bullet() { m_Tex.Load("Assets/Texture/Bullet/Triple_Shot_Blue.png"); }
	~Bullet()override { Release(); }

	void Init();
	void Update();
	void Draw();

	void SetPos(Math::Vector2 pos) { m_Pos = pos; }

	void SetOwner(Game* owner) { m_owner = owner; }

private:

	void Release();

	Game* m_owner = nullptr;
	
	
};