#include"CItem_Key.h"

CItem_Key::CItem_Key()
	:m_pTexture(nullptr)
	, m_mat()
	, m_pos(0, 0)
	, m_bAlive(false)
	, m_scrollPos(0, 0)
{
}

CItem_Key::~CItem_Key()
{
}

//初期化
void CItem_Key::Init()
{
	m_pos = { 0,0 };
	m_bAlive = false;
}

//更新
void CItem_Key::Update()
{
	if (!m_bAlive)return;

	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0);
}

//描画
void CItem_Key::Draw()
{
	if (!m_bAlive)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { 0,0,32,32 };	// テクスチャ座標
	Math::Color color = { 1,1,1,1 };			// 色（RGBAの順番で　0.0～1.0）
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 32, 32, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
}

//テクスチャ設定
void CItem_Key::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

//座標セット、フラグ立てる
void CItem_Key::SetKey(Math::Vector2 Pos)
{
	m_bAlive = true;

	m_pos = Pos;
}

//フラグ変更
void CItem_Key::SetAlive()
{
	m_bAlive = false;
}

void CItem_Key::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
