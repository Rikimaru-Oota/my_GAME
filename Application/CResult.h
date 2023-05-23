#pragma once

class CResult
{
public:
	CResult();
	~CResult();

	void Init();
	void Update(POINT mouse);
	void Draw();

	bool SceneTransition();		// シーン遷移関数

	void SetTexResult(KdTexture* apTexture);	// テクスチャ設定
	void SetTexLine(KdTexture* apTexture);		// テクスチャ設定：強調線

private:
	KdTexture*		m_pTex_Result;		// テクスチャ(リザルト)
	KdTexture*		m_pTex_Line;		// テクスチャ（強調線）
	Math::Matrix	m_matResult;		// 行列(リザルト)
	Math::Matrix	m_matLine;			// 行列(強調線)
	Math::Vector2	m_LinePos;			// 強調線座標
	bool			m_bDrawLine;		// 強調線表示フラグ
	int				m_drawLineCnt;		// 強調線描画カウント
	const int		DRAW_MAX = 380;

	bool bSceneButton(Math::Vector2 pos, Math::Vector2 mouse);
};
