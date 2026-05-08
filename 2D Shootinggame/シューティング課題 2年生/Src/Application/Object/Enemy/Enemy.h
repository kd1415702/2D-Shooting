#pragma once
//親クラスのインクルード
#include"../BaseObject.h"


class Enemy :public BaseObject
{
public:

	Enemy() {};
	~Enemy()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	void ImGuiUpdate()override;

	void Hit()override;



private:


	//クールタイム(次に打てるまでの時間)
	int m_BulletCT;

	//クールタイムカウンター
	int m_BulletCnt;

	void Release()override;



};