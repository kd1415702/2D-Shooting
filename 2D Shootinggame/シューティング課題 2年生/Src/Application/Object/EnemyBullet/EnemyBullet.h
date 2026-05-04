#pragma once

//親クラスのインクルード
#include"../BaseObject.h"

//前方宣言
class Game;

class EnemyBullet : public  BaseObject
{
public:
	

	EnemyBullet() {};
	~EnemyBullet()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetOwner(Game* owner) { m_Owner = owner; }


private:

	Game* m_Owner = nullptr;



	void Release();
};