#pragma once

#include"../SceneBase.h"

enum TitleType
{
	FirstTitle,  //一番最初の画面
	SelectTitle, //選択画面
};

class Title : public SceneBase
{
public:

	Title();
	~Title();

	void Draw()override;
	void Update()override;

	void ChangeNowTitle(TitleType title);

private:
	//ここから

	//背景
	KdTexture m_BackTex;
	Math::Matrix m_BackMat;

	//タイトル更新
	void UpdateTitle();
	//タイトル描画
	void DrawTitle();

	//SelectTitle更新
	void UpdateSelectTitle();

	//タイトル管理変数
	TitleType m_NowTitle;

public:
	static Title& GetInstance()
	{
		static Title Instance;
		return Instance;
	}
};

//タイトル関数アクセス
#define TitleAPP Title::GetInstance();