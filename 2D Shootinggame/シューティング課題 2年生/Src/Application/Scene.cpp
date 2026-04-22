#include "main.h"
#include "Scene.h"
#include "Scenes/SceneManager.h"

void Scene::Draw2D()
{
	m_SceneManager.Draw();
}

void Scene::Update()
{
	m_SceneManager.Update();
}

void Scene::Init()
{
	/*if (m_SceneManager == nullptr)
	{
		m_SceneManager = new SceneManager();
	}*/

	//if (m_SceneManager != nullptr)
	//{
		m_SceneManager.Init();
	
}

void Scene::Release()
{
	m_SceneManager.~SceneManager();
}

void Scene::ImGuiUpdate()
{

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
