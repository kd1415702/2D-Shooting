#include "Title.h"
#include "../SceneManager.h"
#include "Application/main.h"

//初期化
Title::Title()
{
	//Press Enter
	m_PETex.Load("Assets/Texture/UI/Title/Press Enter.png");
	//Press Enterの初期位置,上限、下限移動値
	PEFirst = { 0,-125 };
	PETop = PEFirst.y + 20;
	PEBottom = PEFirst.y - 20;
	//移動量
	m_PEMove = 0.3f;
	//座標
	m_PEPos = { PEFirst };

	m_PETransMat = Math::Matrix::CreateTranslation(m_PEPos.x, m_PEPos.y, 0);
	m_PEScaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_PEMat = m_PEScaleMat * m_PETransMat;



	//SelectTitle基準点
	m_SelectPos = { 0,-150 };

	//プレイ
	m_PlayTex.Load("Assets/Texture/UI/Title/Play.png");
	m_PlayPos = { m_SelectPos.x - 200,m_SelectPos.y };
	m_PlayScale = { 1.2f,1.2f };

	//ゲーム終了
	m_EndTex.Load("Assets/Texture/UI/Title/GameEnd.png");
	m_EndPos = { m_SelectPos.x + 250,m_SelectPos.y + 10 };
	m_EndScale = { 2.5f,2.5f };

	//矢印
	m_ArrowTex.Load("Assets/Texture/UI/Title/Arrow.png");
	m_ArrowPos = { m_PlayPos.x - 100,m_PlayPos.y };
	m_ArrowMove = 0.5f;


	//プレイボタン
	m_PlayTransMat = Math::Matrix::CreateTranslation(m_PlayPos.x, m_PlayPos.y, 0);
	m_PlayScaleMat = Math::Matrix::CreateScale(m_PlayScale.x, m_PlayScale.y, 0);
	m_PlayMat = m_PlayScaleMat * m_PlayTransMat;

	//ゲーム終了ボタン
	m_EndTransMat = Math::Matrix::CreateTranslation(m_EndPos.x, m_EndPos.y, 0);
	m_EndScaleMat = Math::Matrix::CreateScale(m_EndScale.x, m_EndScale.y, 0);
	m_EndMat = m_EndScaleMat * m_EndTransMat;

	//矢印
	m_ArrowTransMat = Math::Matrix::CreateTranslation(m_ArrowPos.x, m_ArrowPos.y, 0);
	m_ArrowScaleMat = Math::Matrix::CreateScale(0.5f, 0.5f, 0);
	m_ArrowMat = m_ArrowScaleMat * m_ArrowTransMat;

	//キーフラグ
	m_KeyFlg = false;

	//FirstTitleからスタート
	m_NowTitle = FirstTitle;

	//セレクト画面
	m_Select = Play;

	m_ArrowFlg = false;


}

//画像解放
Title::~Title()
{
	m_PETex.Release();
	m_PlayTex.Release();
	m_EndTex.Release();
}

void Title::Draw()
{
	DrawTitle();

	/*SHADER.m_spriteShader.DrawString(0, 0, "Title", Math::Color{ 1,1,1 });

	SHADER.m_spriteShader.DrawString(0, -100, "Enter", Math::Color{ 1,1,1 });*/
}

void Title::Update()
{
	UpdateTitle();

}

void Title::UpdateTitle()
{
	switch (m_NowTitle)
	{

	//最初の画面
	case FirstTitle:
	{

		UpdateFirstTitle();

		break;
	}
	case SelectTitle:
	{
		UpdateSelectTitle();
		break;
	}
	default:
		break;
	}
}

void Title::DrawTitle()
{
	switch (m_NowTitle)
	{
	case FirstTitle:
	{
		DrawFirstTitle();

		break;
	}
	case SelectTitle:
	{
		DrawSelectTitle();

		break;
	}
	default:
		break;
	}
}


void Title::UpdateFirstTitle()
{
	//Press Enterが上下移動する
	m_PEPos.y += m_PEMove;
	if (m_PEPos.y >= PETop || m_PEPos.y <= PEBottom)
	{
		m_PEMove *= -1;
	}

	m_PETransMat = Math::Matrix::CreateTranslation(m_PEPos.x, m_PEPos.y, 0);
	m_PEScaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_PEMat = m_PEScaleMat * m_PETransMat;


	//if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	//{
	//	if (m_KeyFlg == false)
	//	{
	//		m_KeyFlg = true;
	//		m_NowTitle = SelectTitle;
	//	}
	//}
	//else
	//{
	//	m_KeyFlg = false;
	//}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		m_NowTitle = SelectTitle;
		ArrowInit();
	}
}

void Title::DrawFirstTitle()
{
	SHADER.m_spriteShader.SetMatrix(m_PEMat);
	SHADER.m_spriteShader.DrawTex(&m_PETex, Math::Rectangle{ 0,0,400,60 }, 1.0f);
}

void Title::UpdateSelectTitle()
{



	//プレイ状態の場合
	if (m_Select == Play)
	{
	
		ArrowInit();
		

		//右を押すと
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			//ゲーム終了に移動
			m_Select = End;
			m_ArrowFlg = false;
		}

		//ゲームシーンへ移動
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (m_KeyFlg == false)
			{
				m_KeyFlg = true;
				SceneAPP.ChangeScene(GAME);
			}

		}
		else
		{
			m_KeyFlg = false;
		}

	}
	//ゲーム終了の場合
	else if (m_Select == End)
	{
	
		ArrowInit();
		

		//左を押すと
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			//プレイに移動
			m_Select = Play;
			m_ArrowFlg = false;
		}

		//ゲーム終了
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (m_KeyFlg == false)
			{
				m_KeyFlg = true;
				APP.m_window.Release();
			}

		}
		else
		{
			m_KeyFlg = false;
		}

	}

	m_ArrowPos.x -= m_ArrowMove;
	if (m_ArrowPos.x <= ArrowLeft || m_ArrowPos.x >= ArrowRight)
	{
		m_ArrowMove *= -1;
	}




	//プレイボタン
	m_PlayTransMat = Math::Matrix::CreateTranslation(m_PlayPos.x, m_PlayPos.y, 0);
	m_PlayScaleMat = Math::Matrix::CreateScale(m_PlayScale.x, m_PlayScale.y, 0);
	m_PlayMat = m_PlayScaleMat * m_PlayTransMat;

	//ゲーム終了ボタン
	m_EndTransMat = Math::Matrix::CreateTranslation(m_EndPos.x, m_EndPos.y, 0);
	m_EndScaleMat = Math::Matrix::CreateScale(m_EndScale.x, m_EndScale.y, 0);
	m_EndMat = m_EndScaleMat * m_EndTransMat;

	//矢印
	m_ArrowTransMat = Math::Matrix::CreateTranslation(m_ArrowPos.x, m_ArrowPos.y, 0);
	m_ArrowScaleMat = Math::Matrix::CreateScale(0.5f, 0.5f, 0);
	m_ArrowMat = m_ArrowScaleMat * m_ArrowTransMat;
}

void Title::DrawSelectTitle()
{
	//プレイボタン
	SHADER.m_spriteShader.SetMatrix(m_PlayMat);
	SHADER.m_spriteShader.DrawTex(&m_PlayTex, Math::Rectangle{ 0,0,200,60 }, 1.0f);

	//ゲーム終了ボタン
	SHADER.m_spriteShader.SetMatrix(m_EndMat);
	SHADER.m_spriteShader.DrawTex(&m_EndTex, Math::Rectangle{ 0,0,192,60 }, 1.0f);

	//矢印
	SHADER.m_spriteShader.SetMatrix(m_ArrowMat);
	SHADER.m_spriteShader.DrawTex(&m_ArrowTex, Math::Rectangle{ 0,0,200,200 }, 1.0f);

	
}

//矢印初期化
void Title::ArrowInit()
{
	
	if (m_ArrowFlg == false)
	{
		m_ArrowFlg = true;
		//プレイの場合
		if (m_Select == Play)
		{
			//矢印の座標
			m_ArrowPos = { m_PlayPos.x - 150,m_PlayPos.y };
			//矢印の初期位置上限
			m_ArrowFirst = { m_PlayPos.x - 150,m_PlayPos.y };
			ArrowRight = m_ArrowFirst.x + 15;
			ArrowLeft = m_ArrowFirst.x - 15;
		}
		else if (m_Select == End)
		{
			//矢印の座標
			m_ArrowPos = { m_EndPos.x - 200,m_EndPos.y };

			//矢印の初期位置上限
			m_ArrowFirst = { m_EndPos.x - 200,m_EndPos.y };
			ArrowRight = m_ArrowFirst.x + 15;
			ArrowLeft = m_ArrowFirst.x - 15;
		}
	}
}


