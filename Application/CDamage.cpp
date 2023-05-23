#include"CDamage.h"

CDamage::CDamage()
	: m_pTexture(nullptr)
	 ,m_pos(0,0)
	 ,m_moveVal(0,0)
	 ,m_mat()
	 ,m_bAlive(false)
	 ,m_size(0)
	 ,m_lifeSpan(0)
	, m_dmgAnime(6)

{
}

CDamage::~CDamage()
{
}

// 初期化
void CDamage::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_size = 0;
	m_lifeSpan = 0;
	m_dmgAnime = 3;
}

// 更新
void CDamage::UpDate(Math::Vector2 scrollPos)
{
	if (!m_bAlive) return;

	//有効期間
	const float ANIMESPEED = 2;
	const int LIFESPAN_MAX = m_dmgAnime * ANIMESPEED;
	if (m_lifeSpan > LIFESPAN_MAX)
	{
		m_lifeSpan = 0;
		m_bAlive = false;
		return;
	}
	m_lifeSpan++;

	//行列作成
	Math::Matrix scaleMat, transMat;
	//拡縮行列
	scaleMat = DirectX::XMMatrixScaling(m_size,m_size,1);
	//移動行列
	transMat = DirectX::XMMatrixTranslation(m_pos.x - scrollPos.x, m_pos.y - scrollPos.y, 0);

	//行列合成
	m_mat = scaleMat * transMat;
}

// 描画
void CDamage::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle((m_lifeSpan/m_dmgAnime)*32, 0, 32, 32), 1.0f);
}

// テクスチャ設定
void CDamage::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTexture = apTexture;
}

// エフェクト発生
void CDamage::EmitDmg(Math::Vector2 pos, Math::Vector2 move, float size)
{
	m_bAlive = true;
	m_pos = pos;
	m_moveVal = move;
	m_size = size;
	m_lifeSpan = 0;
}
