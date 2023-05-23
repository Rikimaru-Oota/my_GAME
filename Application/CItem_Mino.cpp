#include"CItem_Mino.h"

CItem_Mino::CItem_Mino()
	:m_pTexture(nullptr)
	, m_mat()
	, m_pos(0, 0)
	, m_bAlive(false)
	, m_scrollPos(0,0)
{
}

CItem_Mino::~CItem_Mino()
{
}

// 初期化
void CItem_Mino::Init()
{
	m_pos = { 0,0 };
	m_bAlive = false;
}

// 更新
void CItem_Mino::Update()
{
	if (!m_bAlive)return;

	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0);
}

// 描画
void CItem_Mino::Draw()
{
	if (!m_bAlive)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { 0,0,64,64 };
	Math::Color color = { 1,1,1,1 };
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 64, 64, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
}

// テクスチャ設定
void CItem_Mino::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTexture = apTexture;
}

// 隠れ蓑配置
void CItem_Mino::SetMino(Math::Vector2 Pos)
{
	m_bAlive = true;
	m_pos = Pos;
}

// 生存フラグ
void CItem_Mino::SetAlive()
{
	m_bAlive = false;
}

// スクロール量取得
void CItem_Mino::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
