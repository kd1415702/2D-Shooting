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
	PreUpdate();
	m_NowScene->Update();
}

void SceneManager::Draw()
{
	m_NowScene->Draw();


}

void SceneManager::PreUpdate()
{
	// イテレータ作成 auto版
	auto it = m_ObjList.begin();

	while (it != m_ObjList.end())	// end() は 最後の要素の1個後ろを返す
	{
		// オブジェクトの有効チェック
		if ((*it)->GetFlg() == false)
		{
			// 無効なオブジェクトをリストから削除
			it = m_ObjList.erase(it);
		}
		else
		{
			it++;	// 次の要素へイテレータを進める
		}
	}
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
		m_ObjList.clear();
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
