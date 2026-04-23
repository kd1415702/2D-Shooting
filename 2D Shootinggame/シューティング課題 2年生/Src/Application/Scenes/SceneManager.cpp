#include "SceneManager.h"
#include "Title/Title.h"
#include "Game/Game.h"

void SceneManager::Init()
{
	//メモリ確保=====
	m_Title = new Title();
	m_Game = new Game();

		//===============


   //オーナー(SceneManager)セット
	m_Title->SetOwner(this);
	m_Game->SetOwner(this);


	//音関係読み込み======



	//====================



	//タイトルからスタート
	ChangeScene(TITLE);
	
}

void SceneManager::Update()
{
	m_NowScene->Update();
}

void SceneManager::Draw()
{
	m_NowScene->Draw();
}

void SceneManager::ChangeScene(SceneType type)
{
	switch (type)
	{
	case TITLE:
		m_NowScene = m_Title;
		break;
	case GAME:
		m_NowScene = m_Game;
		break;
	case RESULT:
		break;
	case GAMEOVER:
		break;
	default:
		break;
	}
}
