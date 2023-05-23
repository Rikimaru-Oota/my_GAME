#include"Scene.h"
#include"CItem.h"


CItem::CItem()
	:m_pOwner(nullptr)
{
}

CItem::~CItem()
{
}

//初期化
void CItem::Init()
{
	// アイテム：爆弾
	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].Init();
	}
	SetBomb();	//爆弾設置
	
	// アイテム：鍵
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		m_keyList[i].Init();
	}
	SetKey();	//鍵設置

	// アイテム：回復
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		m_healthList[i].Init();
	}

	// アイテム：隠れ蓑
	m_minoList.Init();
	SetMino();	// 隠れ蓑配置
}

//更新
void CItem::Update()
{
	//マップクラス取得
	CMap* map = m_pOwner->GetMap();
	
	//スクロール量取得
	Math::Vector2 ScrollPos = map->GetscrollPos();
	
	//爆弾
	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].SetScrollPos(ScrollPos);		//スクロール量取得
		m_bombList[i].Update();		//更新
	}
	//鍵
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		m_keyList[i].SetScrollPos(ScrollPos);		//スクロール量取得
		m_keyList[i].Update();		//更新
	}
	// 回復
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		m_healthList[i].SetScrollPos(ScrollPos);
		m_healthList[i].Update();
	}
	// 隠れ蓑
	m_minoList.SetScrollPos(ScrollPos);
	m_minoList.Update();
}

//描画
void CItem::Draw()
{
	//爆弾
	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].Draw();
	}
	//鍵
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		m_keyList[i].Draw();
	}
	// 回復
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		m_healthList[i].Draw();
	}
	// 隠れ蓑
	m_minoList.Draw();
}

//オーナー設定取得
void CItem::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

//爆弾設置
void CItem::SetBomb()
{
	CMap* map = m_pOwner->GetMap();
	int mapData = map->GetMapData();	//マップデータ取得

	//データごとの配置設定
	switch (mapData)
	{
	//城外
	case OutSide:
		m_bombList[0].SetBomb({ 260.0f,-920.0f });
		break;
	//一階層
	case OneFloor:
		m_bombList[0].SetBomb({ 464,-744 });
		break;
	//二階層
	case TwoFloor:
		m_bombList[0].SetBomb({ 300,200 });
		break;
	//三階層
	case ThreeFloor:
		break;
	//ボス階層
	case BossFloor:
		m_bombList[0].SetBomb({ 730,-1000 });
		break;
	default:
		break;
	}
}

//鍵設置
void CItem::SetKey()
{
	CMap* map = m_pOwner->GetMap();
	int mapData = map->GetMapData();	//マップデータ取得

	//データごとの配置設定
	switch (mapData)
	{
	//一階層
	case OneFloor:
		m_keyList[0].SetKey({ 1450, 100 });
		m_keyList[1].SetKey({ -500, -1950 });
	//二階層
	case TwoFloor:
		break;
	//三階層
	case ThreeFloor:
		break;
	//四階層
	case FourFloor:
		break;
	}
}

//隠れ蓑設置
void CItem::SetMino()
{
	CMap* map = m_pOwner->GetMap();
	int mapData = map->GetMapData();	//マップデータ取得
	
	if (mapData == TwoFloor) m_minoList.SetMino({ 1700,200 });
}

//テクスチャ設定：爆弾true
void CItem::SetTexBomb_t(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].SetTexture_t(apTexture);
	}
}

//テクスチャ設定：爆弾false
void CItem::SetTexBomb_f(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].SetTexture_f(apTexture);
	}
}

//テクスチャ設定：鍵
void CItem::SetTexKey(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < KEY_SETMAX; i++)
	{
		m_keyList[i].SetTexture(apTexture);
	}
}

// テクスチャ設定：回復
void CItem::SetTexHealth(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		m_healthList[i].SetTexture(apTexture);
	}
}

// テクスチャ設定：隠れ蓑
void CItem::SetTexMino(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_minoList.SetTexture(apTexture);
}

// 回復ドロップ処理(true：ドロップ)
bool CItem::DropHealth(bool bDrop, Math::Vector2 pos)
{
	if (!bDrop) return false;

	if (int r = rand() % 2 > 0) return true;
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		if (m_healthList[i].GetAlive())continue;	// キーフラグチェック
		m_healthList[i].SetHealth(pos);		// 回復ドロップ
		return true;
	}
	return false;
}

// 鍵ドロップ処理(true：ドロップ)
bool CItem::DropKey(bool bDrop, Math::Vector2 pos)
{
	if (!bDrop) return false;
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		if (m_keyList[i].GetAlive())continue;	// キーフラグチェック
		m_keyList[i].SetKey(pos);		// 鍵ドロップ
		return true;
	}
	return false;
}

