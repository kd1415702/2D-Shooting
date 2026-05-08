#include "Ui.h"
#include "../Player/Player.h"

 Ui::Ui()
{

}

 void Ui::Init()
 {
	 m_Player = std::make_shared<Player>();

	 m_LifeTex.Load("Assets/Texture/UI/Game/05.png");

	m_LifePos = { -350.0f,-300.0f };
	 
	m_LifeScale = { 1.0f,1.0f };
	m_LifeRect = 64 * 3;

	m_HpTex.Load("Assets/Texture/UI/Game/Hp.png");

	m_HpTransMat = Math::Matrix::CreateTranslation(-500.0f, -300.0f, 0);
	m_HpScaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
	m_HpMat = m_HpScaleMat * m_HpTransMat;

	m_ExpTex.Load("Assets/Texture/UI/Game/Exp_transparent.png");

	m_ExpTransMat = Math::Matrix::CreateTranslation(-100.0f, -300.0f, 0);
	m_ExpScaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
	m_ExpMat = m_ExpScaleMat * m_ExpTransMat;

	m_ExpBarTex.Load("Assets/Texture/UI/Game/ExpFrame.png");

	m_ExpBarTransMat = Math::Matrix::CreateTranslation(300.0f, -300.0f, 0);
	m_ExpBarScaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
	m_ExpBarMat = m_ExpBarScaleMat * m_ExpBarTransMat;
 }

 void Ui::Update()
 {
	
	m_LifeTransMat = Math::Matrix::CreateTranslation(m_LifePos.x, m_LifePos.y, 0);
	m_LifeScaleMat = Math::Matrix::CreateScale(m_LifeScale.x, m_LifeScale.y, 0);
	m_LifeMat = m_LifeScaleMat * m_LifeTransMat;
 }

 void Ui::Draw()
 {
	//Life
	SHADER.m_spriteShader.SetMatrix(m_LifeMat);
	SHADER.m_spriteShader.DrawTex(&m_LifeTex, Math::Rectangle{ 0,0,m_LifeRect,64 }, 1.0f);

	//体力(文字)
	SHADER.m_spriteShader.SetMatrix(m_HpMat);
	SHADER.m_spriteShader.DrawTex(&m_HpTex, Math::Rectangle{ 0,0,200,60 }, 1.0f);

	//経験値(文字)
	SHADER.m_spriteShader.SetMatrix(m_ExpMat);
	SHADER.m_spriteShader.DrawTex(&m_ExpTex, Math::Rectangle{ 0,0,200,60 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_ExpBarMat);
	SHADER.m_spriteShader.DrawTex(&m_ExpBarTex, Math::Rectangle{ 0,0,600,40 }, 1.0f);

}
