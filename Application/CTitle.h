#pragma once

class Scene;

class Ctitle
{
public:
	Ctitle();
	~Ctitle();

	void Init();
	void Update(POINT mouse);
	void Draw();

	int SceneTransition();		// シーン遷移関数

	bool bGetToGame() { return m_bToGame; }
	bool bGetToDescript() { return m_bToDescript; }

	void SetTexTitle(KdTexture* apTexture);	// テクスチャ設定：タイトル画面
	void SetTexLine(KdTexture* apTexture);	// テクスチャ設定：強調線

private:

	KdTexture*		m_pTex_Title;		// 画像(テクスチャ)
	KdTexture*		m_pTex_Line;		// 画像(テクスチャ)
	Math::Matrix	m_matTitle;			// 行列(タイトル)
	Math::Matrix	m_matLine;			// 行列(強調線)
	Math::Vector2	m_toGamePos;		// ゲームシーン遷移ボタン座標
	Math::Vector2	m_toDescriptPos;	// 説明シーン遷移ボタン座標
	Math::Vector2	m_LinePos;			// 強調線座標
	const float		LINE_POS_X = 10;	// 強調線のX座標固定
	bool			m_bToGame;			// ゲームシーン遷移フラグ
	bool			m_bToDescript;		// 説明シーン遷移フラグ
	const int		DRAW_MAX = 380;
	int				m_drawLineCnt;		// 強調線描画カウント

	bool bSceneButton(Math::Vector2 pos, Math::Vector2 mouse);
};
