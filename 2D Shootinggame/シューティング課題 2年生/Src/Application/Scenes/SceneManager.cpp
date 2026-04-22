#include "SceneManager.h"
#include "Title/Title.h"

void SceneManager::Init()
{
	//メモリ確保=====
	m_Title = new Title();


	//===============





	//音関係読み込み======



	//====================



	//タイトルからスタート
	ChangeScene(TITLE);
	
}

void SceneManager::Update()
{}

void SceneManager::Draw()
{}

void SceneManager::ChangeScene(SceneType type)
{
	m_NowScene = m_Title;
}
