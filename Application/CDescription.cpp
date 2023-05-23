#include"CDescription.h"

CDescription::CDescription()
	:m_pTex_Descript(nullptr)
	, m_pTex_Line(nullptr)
	, m_matDescript()
	, m_matLine()
	, m_LinePos(0, 0)
	, m_bDrawLine(false)
	, m_drawLineCnt(0)
{
}

CDescription::~CDescription()
{
}

// 初期化
void CDescription::Init()
{
	m_LinePos = { 460,-225 };
	m_bDrawLine = false;
	m_drawLineCnt = 0;
}

// 更新処理
void CDescription::Update(POINT mouse)
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

	// ゲーム説明行列作成
	m_matDescript = DirectX::XMMatrixTranslation(0, 0, 0);
	// 強調線行列作成
	m_matLine = DirectX::XMMatrixTranslation(DRAW_MAX*2.5 - ((DRAW_MAX / 2 - m_drawLineCnt) / 2), m_LinePos.y - 50, 0);
}

// 描画
void CDescription::Draw()
{
	// ゲーム説明画面
	SHADER.m_spriteShader.SetMatrix(m_matDescript);
	SHADER.m_spriteShader.DrawTex(m_pTex_Descript, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	if (!m_bDrawLine) return;
	SHADER.m_spriteShader.SetMatrix(m_matLine);
	SHADER.m_spriteShader.DrawTex(m_pTex_Line, Math::Rectangle(0, 0, m_drawLineCnt, 15), 1.0f);

}

// シーン遷移関数
bool CDescription::SceneTransition()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bDrawLine)return true;
		else return false;
	}
}

// テクスチャ設定：ゲーム説明
void CDescription::SetTexDescript(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Descript = apTexture;
}

// テクスチャ設定：強調線
void CDescription::SetTexLine(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Line = apTexture;
}

bool CDescription::bSceneButton(Math::Vector2 pos, Math::Vector2 mouse)
{
	const float Left = pos.x - 80;
	const float Right = pos.x + 80;
	const float Top = pos.y + 55;
	const float Bottom = pos.y - 55;
	
	if (mouse.x > Left && mouse.x < Right &&
		mouse.y > Bottom && mouse.y < Top)
	{
		return true;	//枠を表示
	}
	else return false;
}
