#pragma once
//親クラスのインクルード
#include"EnemyBase.h"

class Enemy :public EnemyBase
{
public:

	Enemy() {};
	~Enemy()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	void ImGuiUpdate()override;

private:

	void Release()override;




};