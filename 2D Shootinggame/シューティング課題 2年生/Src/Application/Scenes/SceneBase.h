#pragma once

//前方宣言
class SceneManager;

//各シーンの親クラス
class SceneBase
{
public:

	SceneBase() {};
	~SceneBase() {};

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void ImGuiUpdate();


	void SetOwner(SceneManager* manager) { m_owner = manager; }


protected:

	SceneManager* m_owner = nullptr;

};