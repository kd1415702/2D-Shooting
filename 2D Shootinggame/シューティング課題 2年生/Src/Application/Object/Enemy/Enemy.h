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

	void Release()override;





};