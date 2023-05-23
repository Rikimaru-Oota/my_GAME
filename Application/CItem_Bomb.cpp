#include "Pch.h"
#include "CItem_Bomb.h"

CItem_Bomb::CItem_Bomb()
	:m_pTexture_t(nullptr)
	,m_pTexture_f(nullptr)
	,m_mat()
	,m_pos(0,0)
	,m_bAlive(false)
	,m_bBombHit(false)
	,m_scrollPos(0,0)
{
}

CItem_Bomb::~CItem_Bomb()
{
}

//初期化
void CItem_Bomb::Init()
{
	m_pos = { 0,0 };
	m_bAlive = false;
	m_bBombHit = false;
}

//更新
void CItem_Bomb::Update()
{
	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0);
}

//描画
void CItem_Bomb::Draw()
{
	if (m_bAlive)
	{
		// 爆弾置き場：有
		SHADER.m_spriteShader.SetMatrix(m_mat);
		Math::Rectangle scrRect = { 0,0,96,96 }; // テクスチャ座標
		Math::Color color = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
		SHADER.m_spriteShader.DrawTex(m_pTexture_t, 0, 0, 96, 96, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
	}
	else
	{
		if (!m_bBombHit) return;

		// 爆弾置き場：空
		SHADER.m_spriteShader.SetMatrix(m_mat);
		Math::Rectangle scrRect = { 0,0,96,96 }; // テクスチャ座標
		Math::Color color = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
		SHADER.m_spriteShader.DrawTex(m_pTexture_f, 0, 0, 96, 96, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
	}
}

//テクスチャ設定：true時
void CItem_Bomb::SetTexture_t(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture_t = apTexture;
}

// テクスチャ設定：false
void CItem_Bomb::SetTexture_f(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture_f = apTexture;
}

// 座標セット、フラグ立てる
void CItem_Bomb::SetBomb(Math::Vector2 Pos)
{
	m_bAlive = true;
	m_pos = Pos;
}

void CItem_Bomb::SetAlive()
{
	m_bAlive = false;
}

//爆弾アイテムヒットフラグセット
void CItem_Bomb::bSetbombHit()
{
	m_bBombHit = true;
}

void CItem_Bomb::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
