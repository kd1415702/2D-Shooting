#include "SceneManager.h"
#include "Title/Title.h"
#include "Game/Game.h"

void SceneManager::Init()
{
	//メモリ確保=====
	

	//===============

	//音関係読み込み======



	//====================



	//タイトルからスタート
	ChangeScene(GAME);
	
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

		m_NowScene = std::make_shared<Title>();
		break;
	case GAME:
		m_NowScene = std::make_shared<Game>();
		break;
	case RESULT:
		break;
	case GAMEOVER:
		break;
	default:
		break;
	}
}
