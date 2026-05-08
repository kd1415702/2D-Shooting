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

	void SetColor(Color _color) { m_Color = _color; }


private:

	



	void Release();
};