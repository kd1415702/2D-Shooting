#pragma once
#include"../Info/Info.h"

class BaseObject
{
public:



	BaseObject() {};
	virtual ~BaseObject() {};

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual void Release();

	virtual void ImGuiUpdate();

	//変数セッター=======================

	//画像セッター
	/*void SetTex(KdTexture* tex) { m_Tex = tex; }*/

	//フラグセッター
	virtual void SetFlg(bool flg) { m_Flg = flg; }

	//座標セッター
	void SetPos(Math::Vector2 pos) { m_Pos = pos; }

	//速度セッター
	void SetSpeed(float speed) { m_MovePow = speed; }

	//================================--

	//変数ゲッター===================
	//オブジェクトタイプゲッター
	ObjectType GetObjType() { return m_objType; }

	//座標ゲッター
	Math::Vector2 GetPos() { return m_Pos; }

	//移動量
	Math::Vector2 GetMove() { return m_Move; }

	//未来座標ゲッター
	Math::Vector2 GetFuturePos() { return m_Pos + m_Move; }

	//半径ゲッター
	float GetRadius() { return m_radius; }

	//最大HP
	int GetMaxHp() { return m_MaxHp; }

	//現在HPゲッター
	int GetHp() { return m_Hp; }

	//速度ゲッター
	float GetSpeed() { return m_MovePow; }

	//フラグゲッター
	bool GetFlg() { return m_Flg; }

	//=======================

	//被弾処理(受けるダメージを正の数で入れる)
	void HitDmg(int dmg);

	virtual void Hit();

protected:

	//virtual void Release();

	ObjectType	  m_objType = ObjectType::NONE;

	//画像
	KdTexture m_Tex;

	//生存フラグ
	bool m_Flg;

	//座標
	Math::Vector2 m_Pos;

	//移動量
	Math::Vector2 m_Move;

	//拡大率
	Math::Vector2 m_Scale;

	//移動速度
	float m_MovePow;

	//合成行列
	Math::Matrix m_Mat;

	//拡大行列
	Math::Matrix m_ScaleMat;
	//移動行列
	Math::Matrix m_TransMat;

	//描画フラグ
	bool m_DrawFlg;

	//切り取り範囲
	int m_Rect;

	//半径
	float m_radius;

	//最大HP
	int m_MaxHp;

	//現在Hp;
	int m_Hp;

	//アニメーションカウント
	float m_AnimCnt;

	//透明度
	float m_Alpha;

};