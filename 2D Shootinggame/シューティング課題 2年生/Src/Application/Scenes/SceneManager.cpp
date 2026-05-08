#include "SceneManager.h"
#include "Title/Title.h"
#include "Game/Game.h"
#include"../Object/Enemy/Enemy.h"
#include"../Object/Bullet/Bullet.h"
#include"../Object/EnemyBullet/EnemyBullet.h"


void SceneManager::Init()
{


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

void SceneManager::ImGuiUpdate()
{
	m_NowScene->ImGuiUpdate();
}


void SceneManager::ChangeScene(SceneType type)
{

	switch (type)
	{
	case TITLE:
	{
		m_NowScene = std::make_shared<Title>();
		//m_NowScene->Init();
		break;
	}
	case GAME:
	{

		m_NowScene = std::make_shared<Game>();
		m_NowScene->Init();




		break;
	}
	case RESULT:
	{
		break;
	}
	case GAMEOVER:
	{
		break;
	}
	default:
		break;
	}
}
