#pragma once
#include"SceneBase.h"
#include"../Info/Info.h"


//前方宣言(SceneManagerで使う各シーン)
class Title;
class Game;


//各シーンの実態を管理するクラス
class SceneManager
{
public:

	SceneManager() { Init();};
	~SceneManager() {};

	void Init();
	void Update();
	void Draw();

	void ImGuiUpdate();


	//シーン切り替え関数
	void ChangeScene(SceneType type);

private:

	//現在のシーンを持たせる(SceneBaseを継承した子クラスのアドレスが入る)
	SceneBase* m_NowScene = nullptr;

	SceneType scene;

	Title* m_Title;
	Game* m_Game;
	

	//ボタンを押したかどうか
	bool ClickFlg;

public:
	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}
};

#define SceneAPP SceneManager::GetInstance()
