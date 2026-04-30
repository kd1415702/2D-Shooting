#include "main.h"
#include "Scene.h"
#include "Scenes/SceneManager.h"
#include"Player/Player.h"

void Scene::Draw2D()
{

	SceneManager::GetInstance().Draw();
}

void Scene::Update()
{
	
	SceneManager::GetInstance().Update();
}

void Scene::Init()
{

	SceneManager::GetInstance().Init();

	m_Player = std::make_shared<Player>();
	
}

void Scene::Release()
{
	SceneManager::GetInstance().~SceneManager();
}

void Scene::ImGuiUpdate()
{

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);

		SceneManager::GetInstance().ImGuiUpdate();
	}
	ImGui::End();
}
