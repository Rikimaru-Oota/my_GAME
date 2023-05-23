#include"CEffect.h"
#include"Scene.h"

CEffect::CEffect()
	:m_pOwner(nullptr)
{
}

CEffect::~CEffect()
{
}

// 初期化
void CEffect::Init()
{
	// ダメージエフェクト初期化
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_dmgList[i].Init();
	}
	// 暗転エフェクト初期化
	m_darkenList.Init();

	// 暗転エフェクト初期化
	m_blackList.Init();

	// 回復エフェクト
	for (int i = 0; i < HEAL_MAX; i++)
	{
		m_healList[i].Init();
	}
}

// 更新
void CEffect::UpDate()
{
	CMap* map = m_pOwner->GetMap();
	Math::Vector2 scrollPos = map->GetscrollPos();

	// ダメージエフェクト
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_dmgList[i].UpDate(scrollPos);
	}
	// 暗転エフェクト
	m_darkenList.Update();

	// 暗転エフェクト
	m_blackList.Update();

	// 回復エフェクト
	for (int i = 0; i < HEAL_MAX; i++)
	{
		m_healList[i].UpDate(scrollPos);
	}
}

// 描画
void CEffect::Draw()
{
	// ダメージエフェクト
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_dmgList[i].Draw();
	}
	// 暗転エフェクト
	m_darkenList.Draw();
	
	// 暗転エフェクト
	m_blackList.Draw();

	// 回復エフェクト
	for (int i = 0; i < HEAL_MAX; i++)
	{
		m_healList[i].Draw();
	}
}

// テクスチャ設定：ダメージ
void CEffect::SetDmgTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_dmgList[i].SetTexture(apTexture);
	}
}

// テクスチャ設定：暗転
void CEffect::SetDarkTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_darkenList.SetTexture(apTexture);
}

// テクスチャ：回復エフェクト
void CEffect::SetHealTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	for (int i = 0; i < HEAL_MAX; i++)
	{
		m_healList[i].SetTexture(apTexture);
	}
}

//テクスチャ:暗転
void CEffect::SetBlackTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_blackList.SetTexture(apTexture);
}

// プレイヤーのヒットエフェクト発生
void CEffect::HitEffect(Math::Vector2 pos, Math::Vector2 move, float size)
{
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		if (m_dmgList[i].GetbAlive())continue;
		m_dmgList[i].EmitDmg(pos, move, size);
		return;
	}
}

// プレイヤーの回復エフェクト発生
void CEffect::PlayerHealEffect()
{
	CPlayer* player = m_pOwner->GetPlayer();
	for (int i = 0; i < HEAL_MAX; i++)
	{
		if (m_healList[i].GetbAlive())continue;
		m_healList[i].EmitHeal(player->GetPos(), player->GetMove());
	}
}

// オーナー設定取得
void CEffect::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr)return;
	m_pOwner = apOwner;
}
