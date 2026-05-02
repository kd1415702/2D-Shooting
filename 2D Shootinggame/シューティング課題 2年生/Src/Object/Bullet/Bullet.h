#pragma once

class Bullet
{
public:

	Bullet() { m_Tex.Load("Assets/Texture/Bullet/Triple_Shot_Blue.png"); }
	~Bullet() {	Release();}

	void Init();
	void Update();
	void Draw();

	void SetPos(Math::Vector2 pos) { m_Pos = pos; }

private:
	
	void Release();

	KdTexture m_Tex;

	Math::Vector2 m_Pos;

	Math::Vector2 m_Scale;

	Math::Matrix m_TransMat;
	Math::Matrix m_ScaleMat;
	Math::Matrix m_Mat;

	float m_Move;

	bool m_Flg;

	int m_Rect;
};