#include "Ui.h"
#include "../Player/Player.h"

 Ui::Ui()
{

}

 void Ui::Init()
 {
	 //プレイヤーインスタンス生成
	 m_Player = std::make_shared<Player>();

	 //ライフ=========================
	 m_LifeTex.Load("Assets/Texture/UI/Game/05.png");

	 m_LifePos = { -380.0f,-300.0f };

	 m_LifeScale = { 1.0f,1.0f };
	 m_LifeRect = 64 * 3;

	 m_LifeTransMat = Math::Matrix::CreateTranslation(m_LifePos.x, m_LifePos.y, 0);
	 m_LifeScaleMat = Math::Matrix::CreateScale(0, 0, 0);
	 m_LifeMat = m_LifeScaleMat * m_LifeTransMat;
	 //=================================

	 //体力(文字)=========================
	 m_HpTex.Load("Assets/Texture/UI/Game/Hp.png");

	 m_HpTransMat = Math::Matrix::CreateTranslation(-550.0f, -300.0f, 0);
	 m_HpScaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
	 m_HpMat = m_HpScaleMat * m_HpTransMat;
	 //=================================

	 //レベル(文字)=========================
	 m_ExpTex.Load("Assets/Texture/UI/Game/Level_transparent.png");

	 m_ExpTransMat = Math::Matrix::CreateTranslation(-180.0f, -300.0f, 0);
	 m_ExpScaleMat = Math::Matrix::CreateScale(1.3f, 1.3f, 0);
	 m_ExpMat = m_ExpScaleMat * m_ExpTransMat;

	 //=================================

	 //レベル(数字)=========================
	 m_LvNumTex.Load("Assets/Texture/UI/Game/Number.png");

	 m_Lv = 1;
	 //=================================

	 //経験値(フレーム)=========================
	 m_ExpFrameTex.Load("Assets/Texture/UI/Game/ExpFrame.png");

	 m_ExpFrameTransMat = Math::Matrix::CreateTranslation(300.0f, -300.0f, 0);
	 m_ExpFrameScaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
	 m_ExpFrameMat = m_ExpFrameScaleMat * m_ExpFrameTransMat;

	 //=================================

	 //経験値(バー)=========================
	 m_ExpBarTex.Load("Assets/Texture/UI/Game/Bar.png");

	 m_ExpBarPos = 300.0f;

	 m_ExpBarTransMat = Math::Matrix::CreateTranslation(m_ExpBarPos, -300.0f, 0);
	 m_ExpBarScaleMat = Math::Matrix::CreateScale(0.9f, 0.9f, 0);
	 m_ExpBarMat = m_ExpBarScaleMat * m_ExpBarTransMat;

	 m_ExpBarRect = 0;
	 m_Exp = 0;
	 //=================================

	 m_BlackTex.Load("Assets/Texture/UI/Game/Black.png");
	 m_BlackTransMat = Math::Matrix::CreateTranslation(0.0f, 0.0f, 0);
 }
	

 void Ui::Update()
 {

	 //現在経験値に応じて経験値バーの長さと位置を変える
	 switch (m_Exp)
	 {
	 case 10:
		 m_ExpBarRect = 600 * 0.1f;
		 m_ExpBarPos = 300.0f - 270.0f;
		 break;

	 case 20:
		 m_ExpBarRect = 600 * 0.2f;
		 m_ExpBarPos = 300.0f - 245.0f;
		 break;

	 case 30:
		 m_ExpBarRect = 600 * 0.3f;
		 m_ExpBarPos = 300.0f - 220.0f;
		 break;

	 case 40:
		 m_ExpBarRect = 600 * 0.4f;
		 m_ExpBarPos = 300.0f - 190.0f;
		 break;

	 case 50:
		 m_ExpBarRect = 600 * 0.5f;
		 m_ExpBarPos = 300.0f - 163.0f;
		 break;

	 case 60:
		 m_ExpBarRect = 600 * 0.6f;
		 m_ExpBarPos = 300.0f - 135.0f;
		 break;

	 case 70:
		 m_ExpBarRect = 600 * 0.7f;
		 m_ExpBarPos = 300.0f - 110.0f;
		 break;

	 case 80:
		 m_ExpBarRect = 600 * 0.8f;
		 m_ExpBarPos = 300.0f - 80.0f;
		 break;
	 
	 case 90:
		 m_ExpBarRect = 600 * 0.99f;
		 m_ExpBarPos = 300.0f - 30.0f;
		 break;

	 default:
		 m_ExpBarRect = 0;
		 m_ExpBarPos = 300.0f;
		 break;
	 }


	 m_LvNumTransMat = Math::Matrix::CreateTranslation(-80.0f, -300.0f, 0);
	 m_LvNumScaleMat = Math::Matrix::CreateScale(1.5f, 1.5f, 0);
	 m_LvNumMat = m_LvNumScaleMat * m_LvNumTransMat;


	 m_ExpBarTransMat = Math::Matrix::CreateTranslation(m_ExpBarPos, -300.0f, 0);
	 m_ExpBarScaleMat = Math::Matrix::CreateScale(0.9f, 0.9f, 0);
	 m_ExpBarMat = m_ExpBarScaleMat * m_ExpBarTransMat;


	m_LifeTransMat = Math::Matrix::CreateTranslation(m_LifePos.x, m_LifePos.y, 0);
	m_LifeScaleMat = Math::Matrix::CreateScale(m_LifeScale.x, m_LifeScale.y, 0);
	m_LifeMat = m_LifeScaleMat * m_LifeTransMat;
 }

 void Ui::Draw()
 {
	//Life
	SHADER.m_spriteShader.SetMatrix(m_LifeMat);
	SHADER.m_spriteShader.DrawTex(&m_LifeTex, Math::Rectangle{ 0,0,m_LifeRect,64 }, 1.0f);

	//体力(文字)
	SHADER.m_spriteShader.SetMatrix(m_HpMat);
	SHADER.m_spriteShader.DrawTex(&m_HpTex, Math::Rectangle{ 0,0,200,60 }, 1.0f);

	//レベル(文字)
	SHADER.m_spriteShader.SetMatrix(m_ExpMat);
	SHADER.m_spriteShader.DrawTex(&m_ExpTex, Math::Rectangle{ 0,0,100,60 }, 1.0f);

	//現在レベル(数字)
	NumDraw(m_Lv);

	//経験値(フレーム)
	SHADER.m_spriteShader.SetMatrix(m_ExpFrameMat);
	SHADER.m_spriteShader.DrawTex(&m_ExpFrameTex, Math::Rectangle{ 0,0,600,40 }, 1.0f);

	//経験値(バー)
	SHADER.m_spriteShader.SetMatrix(m_ExpBarMat);
	SHADER.m_spriteShader.DrawTex(&m_ExpBarTex, Math::Rectangle{ 0,0,m_ExpBarRect,40 }, 1.0f);

}

 void Ui::NumDraw(int _num)
 {
	 //現在レベル

	 //10以上なら桁数を求める
	 if (_num >= 10)
	 {
		 //桁数を入れるワークスペース
		 long w = 0;

		 for (long long i = 1; i <= _num; i *= 10)
		 {
			 w++;
		 }

		 //分解した1桁数を入れる
		 std::vector<int> w_num;

		 for (int i = 0; i < w; i++)
		 {
			 int a = 1;
			 for (int j = i; j < w - 1; j++)
			 {
				 a *= 10;
			 }

			 w_num.push_back((_num / a) % 10);
			 _num %= a;


		 }

		 for (int i = 0; i < w_num.size(); i++)
		 {
			 //横切り取り範囲
			 int recX = 30;

			 //縦切り取り範囲
			 int recY = 40;

			 
			 SHADER.m_spriteShader.SetMatrix(m_LvNumMat);
			 SHADER.m_spriteShader.DrawTex(&m_LvNumTex, Math::Rectangle{ w_num[i] * 30,0,30,40 }, 1.0f);
			 m_LvNumMat *= Math::Matrix::CreateTranslation(30.0f, 0.0f, 0);
				 //次の数字を描画するために、描画後に行列を移動させる
				 //（今回は左に移動させる）
				 //（右に移動させる場合は、CreateTranslationの引数を正の値にする）
				 //（上や下に移動させる場合は、CreateTranslationの引数のyを変更する）
				 //（斜めに移動させる場合は、CreateTranslationの引数のxとyを両方変更する）
				 //（数字以外のものを描画する場合も同様）
				 //（例えば、レベルアップの文字を描画したい場合は、CreateTranslationの引数を適切な値にして、レベルアップのテクスチャを用意して描画する）
				 //（このように、行列を移動させることで、複数のものを順番に描画することができる）
				 //（また、行列を回転させたり拡大縮小させたりすることもできるので、様々な表現が可能になる）
				 //（例えば、レベルアップの文字を回転させて描画したい場合は、CreateRotationZなどの関数を使って行列を回転させてから描画する）

		 }
	 }
	 else
	 {
		 int recX = 30;
		 int recY = 40;

		 SHADER.m_spriteShader.SetMatrix(m_LvNumMat);
		 SHADER.m_spriteShader.DrawTex(&m_LvNumTex, Math::Rectangle{ _num * 30,0,30,40 }, 1.0f);
	 }
 }
