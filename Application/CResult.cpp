#include"CResult.h"

CResult::CResult()
	:m_pTex_Result(nullptr)
	,m_pTex_Line(nullptr)
	,m_matResult()
	,m_matLine()
	,m_LinePos(0,0)
	,m_bDrawLine(false)
	,m_drawLineCnt(0)
{
}

CResult::~CResult()
{
}

// 初期化
void CResult::Init()
{
	m_LinePos = { -425,-205 };
	m_bDrawLine = false;
	m_drawLineCnt = 0;
}

// 更新
void CResult::Update(POINT mouse)
{
	// マウス座標取得
	Math::Vector2 mousePos = { (float)mouse.x,(float)mouse.y };

	// カーソルがシーン遷移ボタン内でフラグ変更
	m_bDrawLine = bSceneButton(m_LinePos, mousePos);

	// 強調線アニメーション
	if (m_bDrawLine)
	{
		m_drawLineCnt += 30;
		if (m_drawLineCnt >= DRAW_MAX)m_drawLineCnt = DRAW_MAX;
	}
	else m_drawLineCnt = 0;

	// リザルト行列作成
	m_matResult = DirectX::XMMatrixTranslation(0, 0, 0);
	// 強調線行列作成
	m_matLine = DirectX::XMMatrixTranslation(-DRAW_MAX*1.25 - ((DRAW_MAX / 2 - m_drawLineCnt) / 2), m_LinePos.y - 30, 0);
}

// 描画
void CResult::Draw()
{
	// タイトル画面
	SHADER.m_spriteShader.SetMatrix(m_matResult);
	SHADER.m_spriteShader.DrawTex(m_pTex_Result, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	
	if (!m_bDrawLine) return;
	SHADER.m_spriteShader.SetMatrix(m_matLine);
	SHADER.m_spriteShader.DrawTex(m_pTex_Line, Math::Rectangle(0, 0, m_drawLineCnt, 15), 1.0f);

}

// シーン遷移関数
bool CResult::SceneTransition()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bDrawLine)return true;
		else return false;
	}
}

// テクスチャ設定：リザルト
void CResult::SetTexResult(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Result = apTexture;
}

// テクスチャ設定：強調線
void CResult::SetTexLine(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Line = apTexture;
}

// シーン遷移ボタン判定関数
bool CResult::bSceneButton(Math::Vector2 pos, Math::Vector2 mouse)
{
	const float Left = pos.x - 125;
	const float Right = pos.x + 125;
	const float Top = pos.y + 25;
	const float Bottom = pos.y - 25;
	if (mouse.x > Left && mouse.x < Right &&
		mouse.y > Bottom && mouse.y < Top)
	{
		return true;	//枠を表示
	}
	else return false;
}

