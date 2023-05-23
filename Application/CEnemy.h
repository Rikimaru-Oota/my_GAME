#pragma once

#include<vector>
#include"CSamurai.h"
#include"CArcher.h"
#include"CArrow.h"
#include"CGiant.h"
#include"CBoss.h"
#include"CEnemySword.h"

//クラスの前方宣言
class Scene;

//敵の要素数
constexpr int SAMURAI_MAX = 20;
constexpr int ARCHER_MAX = 15;
constexpr int GIANT_MAX = 5;

class CEnemy
{
public:		// 外部からアクセス可
	CEnemy();		// コンストラクタ
	~CEnemy();		// デストラクタ

	void SetOwner(Scene* apOwner);		// オーナー設定取得

	void Init();			// 初期化
	void Update();			// 更新
	void Draw();			// 描画
	
	CSamurai* GetSamuraiList() { return m_samuraiList; }	// 侍リスト取得
	CArcher* GetArcherList() { return m_archerList; }		// 弓兵リスト取得
	CGiant* GetGiantList() { return m_giantList; }			// 大男リスト取得
	CBoss* GetBossList() { return &m_bossList; }			// ボスリスト取得
	int GetArrowSize() { return m_arrowList.size(); }		// 矢の配列返還
	int GetSwordSize() { return m_enemySwordList.size(); }	// 斬撃の配列返還
	int GetBossHp() { return m_bossList.GetHp(); }			// ボスのHP取得
	bool bGetEvent() { return m_bEvent; }					// イベント発生フラグ取得
	
	void SetTexture(KdTexture* apTexture);			// テクスチャ設定：侍
	void SetArcherTexture(KdTexture* apTexture);	// テクスチャ設定：弓兵
	void SetGiantTexture(KdTexture* apTexture);		// テクスチャ設定：大男
	void SetBossTexture(KdTexture* apTexture);		// テクスチャ設定：ボス
	void SetArrowTexture(KdTexture* apTexture);		// テクスチャ設定：矢
	void SetSwordTexture(KdTexture* apTexture);		// テクスチャ設定：斬撃

	void SetSamurai(int data);		// 侍配置
	void SetArcher(int data);		// 弓兵配置
	void SetGiant(int data);		// 大男配置
	void SetBoss();					// ボス配置

	void HitCheeckMap_Boss();	// ボスとマップの当たり判定

	void shot(Math::Vector2 apos, Math::Vector2 bpos);  //発射処理
	void Event();	// イベント処理

private:	// 外部からアクセス不可

	void Update_Samurai(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide);
	void Update_Archer(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide);
	void Update_Giant(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide);
	void Update_Boss(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide);
	void Update_Arrow(Math::Vector2 scrPos);
	void Update_Sword(Math::Vector2 scrPos);

	void HitCheckPlayer();	// プレイヤーとの当たり判定
	void HitCheckEnemy_And_Player(Math::Vector2 enePos, int dmg, float knockBack, float Left,float Right,float Top,float Down);	// プレイヤーと敵の当たり判定
	void HitCheckMap();		//マップとの当たり判定

	CSamurai	m_samuraiList[SAMURAI_MAX];		// 侍クラスのリスト
	const Math::Vector2 SAMURAI_SLASH_SIZE = { 1,1 };	// 侍斬撃サイズ
	CArcher		m_archerList[ARCHER_MAX];		// 弓兵クラスのリスト
	CGiant		m_giantList[GIANT_MAX];			// 大男クラスのリスト
	CBoss		m_bossList;						// ボスクラスのリスト
	const Math::Vector2 BOSS_SLASH_SIZE = { 2,2 };		// ボス斬撃サイズ

	std::vector<CEnemySword*>	m_enemySwordList;	// 敵斬撃リスト
	KdTexture* m_pSlashTex;	// テクスチャ：斬撃
	std::vector<CArrow*>	m_arrowList;	// 矢リスト
	KdTexture* m_pArrawTex;	// テクスチャ：矢		

	int         gimmickcount;                   //ギミックカウント
	bool m_bEvent;	// イベント発生処理

	Scene* m_pOwner;	// オーナー取得用
};

