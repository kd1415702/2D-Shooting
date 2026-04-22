#pragma once
#include"SceneBase.h"
#include"../Info/Info.h"


//前方宣言
class Title;


//各シーンの実態を管理するクラス
class SceneManager
{
public:

	SceneManager() {};
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
	

	//ボタンを押したかどうか
	bool ClickFlg;

};