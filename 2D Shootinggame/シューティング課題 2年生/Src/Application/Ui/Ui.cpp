#include "Ui.h"
#include "../Player/Player.h"

 Ui::Ui()
{

}

 void Ui::Init()
 {
	 m_Player = std::make_shared<Player>();

	 m_LifeTex.Load("Assets/Texture/UI/Game/05.png");


	m_LifePos = { -500,-300 };
	 
	m_LifeScale = { 1.0f,1.0f };
	m_LifeRect = 64 * 3;
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

 }
