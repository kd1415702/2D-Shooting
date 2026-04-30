#include "Hit.h"
#include"../Player/Player.h"
#include"../Enemy/Enemy.h"


void Hit::Init()
{
	m_Flg = false;
	m_Cooltime = 0;
	m_Player = std::make_shared<Player>();
	m_Enemy = std::make_shared<Enemy>();
}

//自機と敵の当たり判定(斜辺)
void Hit::EnemyPlayerHit()
{
	if (m_Enemy == nullptr) { return; }

	if (m_Enemy->GetFlg())
	{
		const float x = m_Enemy->GetPos().x - m_Player->GetPos().x;
		const float y = m_Enemy->GetPos().y - m_Player->GetPos().y;
		const float z = sqrt(x * x + y * y);



		//半径＋半径
		const float sum = m_Enemy->GetRadius() + m_Player->GetRadius();

		if (z < sum)
		{

			m_Player->HitDmg();

			return;
		}
	}
}




