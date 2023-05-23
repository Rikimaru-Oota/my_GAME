#pragma once

class CDescription
{
public:
	CDescription();
	~CDescription();

	void Init();
	void Update(POINT mouse);
	void Draw();

	bool SceneTransition();		// シーン遷移関数

	void SetTexDescript(KdTexture* apTexture);	// テクスチャ設定：説明画面
	void SetTexLine(KdTexture* apTexture);		// テクスチャ設定：強調線

private:
	KdTexture*		m_pTex_Descript;		// テクスチャ(説明)
	KdTexture*		m_pTex_Line;			// テクスチャ(強調線)
	Math::Matrix	m_matDescript;			// 行列(説明)
	Math::Matrix	m_matLine;				// 行列(強調線)
	Math::Vector2	m_LinePos;				// 強調線座標
	bool			m_bDrawLine;			// 強調線表示フラグ
	int				m_drawLineCnt;			// 強調線描画カウント
	const int		DRAW_MAX = 170;

	bool bSceneButton(Math::Vector2 pos, Math::Vector2 mouse);
};

