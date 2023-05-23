#include"CItem_Health.h"

CItem_Health::CItem_Health()
	:m_pTexture(nullptr)
	, m_mat()
	, m_pos(0, 0)
	, m_bAlive(false)
	, m_scrollPos(0,0)
{
}

CItem_Health::~CItem_Health()
{
}

// 初期化
void CItem_Health::Init()
{
	m_pos = { 0,0 };
	m_bAlive = false;
}

// 更新
void CItem_Health::Update()
{
	if (!m_bAlive)return;

	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0);

}

// 描画
void CItem_Health::Draw()
{
	if (!m_bAlive)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { 0,0,32,32 };	// テクスチャ座標
	Math::Color color = { 1,1,1,1 };			// 色（RGBAの順番で　0.0～1.0）
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 32, 32, &scrRect, &color, Math::Vector2(0.5f, 0.5f));

}

// テクスチャ設定
void CItem_Health::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTexture = apTexture;
}

// アイテムセット
void CItem_Health::SetHealth(Math::Vector2 Pos)
{
	m_pos = Pos;
	m_bAlive = true;
}

// フラグセット
void CItem_Health::SetAlive()
{
	m_bAlive = false;
}

// スクロール量取得
void CItem_Health::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
