#include "SceneManager.h"
#include "Title/Title.h"

void SceneManager::Init()
{
	//メモリ確保=====
	m_Title = new Title();


		//===============


   //オーナー(SceneManager)セット
	//m_Title->SetOwner(this);


	//音関係読み込み======



	//====================



	//タイトルからスタート
	ChangeScene(TITLE);
	
}

void SceneManager::Update()
{

}

void SceneManager::Draw()
{
	m_NowScene->Draw();
}

void SceneManager::ChangeScene(SceneType type)
{
	m_NowScene = m_Title;
}
