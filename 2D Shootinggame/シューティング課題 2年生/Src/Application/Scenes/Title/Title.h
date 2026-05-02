#pragma once

#include"../SceneBase.h"

//タイトルの種類
enum TitleType
{
	//一番最初の画面
	FirstTitle,  
	//選択画面
	SelectTitle, 
};

//SelectTitleで何を選んでいるか
enum SelectType
{
	Play,	//プレイ
	End		//ゲーム終了
};

class Title : public SceneBase
{
public:

	Title();
	~Title()override;

	void Draw()override;
	void Update()override;

	void ChangeNowTitle(TitleType title);


private:
	
	//背景
	KdTexture m_BackTex;
	Math::Matrix m_BackMat;

	//キーを押しているかどうか
	bool m_KeyFlg;

	//タイトル更新
	void UpdateTitle();
	//タイトル描画
	void DrawTitle();

	

	//タイトル管理変数
	TitleType m_NowTitle;

	//FirstTitle========================
	//FirstTitle更新処理
	void UpdateFirstTitle();
	//描画
	void DrawFirstTitle();

	//Press Enter用変数
	KdTexture m_PETex;
	Math::Vector2 m_PEPos;
	Math::Matrix m_PETransMat;
	Math::Matrix m_PEScaleMat;
	Math::Matrix m_PEMat;

	//Press Enterの初期位置,上限、下限移動値
	Math::Vector2 m_PEFirst;
	float m_PETop;
	float m_PEBottom;
	//移動量
	float m_PEMove;

	//FirstTitleかどうか(TrueならFirstTitle)
	bool m_FirstFlg;

	//========================================


	//SelectTitle========================-
	//SelectTitle更新
	void UpdateSelectTitle();
	//描画
	void DrawSelectTitle();

	SelectType m_Select;
	//基準点
	Math::Vector2 m_SelectPos;

	//プレイボタン用変数
	KdTexture m_PlayTex;
	Math::Vector2 m_PlayPos;
	Math::Vector2 m_PlayScale;
	Math::Matrix m_PlayTransMat;
	Math::Matrix m_PlayScaleMat;
	Math::Matrix m_PlayMat;


	//ゲーム終了ボタン用変数
	KdTexture m_EndTex;
	Math::Vector2 m_EndPos;
	Math::Vector2 m_EndScale;
	Math::Matrix m_EndTransMat;
	Math::Matrix m_EndScaleMat;
	Math::Matrix m_EndMat;

	//矢印初期化
	void ArrowInit();

	//矢印
	KdTexture m_ArrowTex;
	Math::Vector2 m_ArrowPos;
	Math::Matrix m_ArrowTransMat;
	Math::Matrix m_ArrowScaleMat;
	Math::Matrix m_ArrowMat;
	//矢印の初期位置,左右移動値上限
	Math::Vector2 m_ArrowFirst;
	float ArrowRight;
	float ArrowLeft;
	//移動量
	float m_ArrowMove;

	//移動フラグ
	bool m_ArrowFlg;


	//FirstTitleが出るのは一回のみ
	//bool m_FirstFlg;

	//ゲーム終了処理
	//APP.m_window.Release();

public:
	static Title& GetInstance()
	{
		static Title GInstance;
		return GInstance;
	}
};

//タイトル関数アクセス
#define TitleAPP Title::GetInstance();