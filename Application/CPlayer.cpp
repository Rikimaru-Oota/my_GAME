#include "CPlayer.h"
#include "Scene.h"
#include"Utility.h"

//コンストラクタ
CPlayer::CPlayer()
	: m_direction(Right)
	, m_LClick(eShuriken)
	, m_RClick(eSword)
	, m_status(eIdle)
	, m_pTexture(nullptr)
	, m_pos(0.0f, 0.0f)
	, m_moveVal(0.0f, 0.0f)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_size(1.0f, 1.0f)
	, m_bAlive(true)
	, m_hp(HP::PLAYER)
	, m_bHeal(false)
	, m_invincibleCnt()
	, m_alpha(1.0f)
	, m_HitFlg(false)
	, m_slashCnt(COOL_TIME::PLAYER_SLASH)
	, m_shurikenCnt(COOL_TIME::PLAYER_SHURIKEN/2)
	, m_bRClick(false)
	, m_bLClick(false)
	, m_bRChange(false)
	, m_bLChange(false)
	, m_aCnt(0)
	, m_aAttackCnt(0)
	, m_aTimer(15)
	, m_aflame(5)
	, scrRect(0,0,0,0)
	, m_BombPossession(0)
	, m_KeyPossession(0)
	, m_bMinoPossession(false)
	,m_pOwner(nullptr)
	,m_ClickPoint()
{
}

CPlayer::~CPlayer()
{
}

//初期化
void CPlayer::Init()
{
	//座標
	m_pos = { -250.0f,-1080.0f };	// 初期座標

	//移動量
	m_moveVal = { 0.0f,0.0f };
	
	//生存フラグ
	m_bAlive = true;
	
	//体力
	m_hp = HP::PLAYER;
	m_invincibleCnt = 0;

	//回復
	m_bHeal=false;

	//透明度
	m_alpha = 1.0f;

	//敵と当たったか判定
	m_HitFlg = false;

	//初期方向
	m_direction = Down;

	//初期装備
	m_LClick = eShuriken;
	m_RClick = eSword;

	//左右クリックフラグ
	m_bRClick = false;
	m_bLClick = false;

	//武器チェンジフラグ
	m_bLChange = false;
	m_bRChange = false;

	//弾の初期化
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_bulletList[i].Init();
	}
	m_shurikenCnt = COOL_TIME::PLAYER_SHURIKEN/2;

	//刀初期化
	m_swordList.Init();
	m_slashCnt = COOL_TIME::PLAYER_SLASH;

	//爆弾の初期化
	m_bombList.Init();
	m_BombPossession = 0;

	//隠れ身初期化
	m_hiddenList.Init();
	m_bMinoPossession = false;

	//鍵初期化
	m_KeyPossession = 0;

	//SE(サウンドの読み込みと実体化)
	katanaseInst = Utility::Sound_Loading(katanase, "Resource/Sound/katana.WAV");
	shurikenseInst = Utility::Sound_Loading(shurikense, "Resource/Sound/shuriken.WAV");
	hitseInst = Utility::Sound_Loading(hitse,"Resource/Sound/hit.WAV");
	healseInst = Utility::Sound_Loading(healse, "Resource/Sound/heal.WAV");
	keypuseInst = Utility::Sound_Loading(keypuse, "Resource/Sound/key.WAV");
	itempuseInst = Utility::Sound_Loading(itempuse,"Resource/Sound/itempu.WAV");
	unlockseInst = Utility::Sound_Loading(unlockse, "Resource/Sound/unlock.WAV");
	gimmickseInst = Utility::Sound_Loading(gimmickse, "Resource/Sound/gimmick.WAV");
}

// 再初期化
void CPlayer::ReInit(int mapData)
{
	switch (mapData)
	{
	//一階層
	case OneFloor:
		m_pos = { 1600,-1800 };
		m_KeyPossession = 0;
		break;
	//二階層
	case TwoFloor:
		m_pos = { -460,100 };
		m_KeyPossession = 0;
		break;
	//三階層
	case ThreeFloor:
		m_pos = { -460,-2000 };
		m_KeyPossession = 0;
		break;
	//四階層
	case FourFloor:
		m_pos = { -460,100 };
		m_KeyPossession = 0;
		break;
	//ボス
	case BossFloor:
		m_pos = { 624,-1340 };
		m_KeyPossession = 0;
		break;
	}
}

//更新
void CPlayer::Updata(POINT aMousePos)
{
	//生存時のみ処理
	if (!m_bAlive) return;
	CMap* map = m_pOwner->GetMap();		//マップクラス取得
	Math::Vector2 ScrollPos = map->GetscrollPos();		//スクロール量取得
	
	m_ClickPoint = aMousePos;	// マウス座標取得

	// プレイヤー更新
	UpDatePlayer(ScrollPos);
	
	//弾の更新
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_bulletList[i].SetScrollPos(ScrollPos);
		m_bulletList[i].Updata();
	}

	//刀攻撃更新
	m_swordList.SetScrollPos(ScrollPos);
	m_swordList.Updata(m_pos);

	//爆弾の更新
	m_bombList.SetScrollPos(ScrollPos);
	m_bombList.Updata();

	//隠れ身の更新
	m_hiddenList.Updata();
}

// プレイヤー更新処理
void CPlayer::UpDatePlayer(Math::Vector2 ScrollPos)
{
	//プレイヤーが"歩き"状態の時プレイヤーの状態を"立ち"の状態にする
	if(m_status==eWalking)
	m_status = eIdle;

	// キー操作一覧
	KeyOperation();

	//サイズ変更(画像反転用)
	switch (m_direction) {
	case 2:
		m_size = { -1.0f, 1.0f };
		break;
	case 3:
		m_size = { 1.0f, 1.0f };
		break;
	}

	//クールタイム増加
	// 斬撃カウント
	m_slashCnt++;
	if (m_slashCnt >= COOL_TIME::PLAYER_SLASH)m_slashCnt = COOL_TIME::PLAYER_SLASH;
	// 手裏剣カウント
	m_shurikenCnt++;
	if (m_shurikenCnt >= COOL_TIME::PLAYER_SHURIKEN)m_shurikenCnt = COOL_TIME::PLAYER_SHURIKEN;
	
	/* 当たり判定 */
	//敵
	HitCheckEnemy();
	//マップ
	HitCheckMap();
	//爆弾
	HitCheckBomb();
	//アイテム
	HitCheckItem();
	
	//無敵時間
	invincibleTime();

	//HP0でフラグ下げ
	if (m_hp <= 0)
	{
		m_bAlive = !m_bAlive;
		m_hp = 0;
	}
	//HP上限を設ける
	if (m_hp >= HP::PLAYER)m_hp = HP::PLAYER;

	Animation();

	//座標確定
	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;
	m_moveVal = { 0,0 };

	//行列作成
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - ScrollPos.x, m_pos.y - ScrollPos.y, 0.0f);
	m_scaleMat = DirectX::XMMatrixScaling(m_size.x, m_size.y, 0.0f);
	m_mat = m_scaleMat * m_transMat;
}

//描画
void CPlayer::Draw()
{
	if (!m_bAlive) return;

	//弾の描画
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_bulletList[i].Draw();
	}

	//斬撃の描画
	m_swordList.Draw();

	//爆弾の描画
	m_bombList.Draw();

	//プレイヤー描画
	SHADER.m_spriteShader.SetMatrix(m_mat);
	switch (m_status)
	{
	case eIdle:
		scrRect = { -20,AnimationCalc(m_aCnt,348),160,64 }; // テクスチャ座標
		break;
	case eWalking:
		scrRect = { -20,AnimationCalc(m_aCnt,1044),160,64 }; // テクスチャ座標
		break;
	case eAttack:
		scrRect = { -20,AnimationCalc(m_aCnt,0),160,64 }; // テクスチャ座標
		break;
	default:
		break;
	}
	Math::Color color = { 1,1,1, m_alpha }; // 色（RGBAの順番で　0.0～1.0）
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 160, 64, &scrRect, &color, Math::Vector2(0.5f, 0.5f));

}

//テクスチャ設定:自機
void CPlayer::SetTexture(KdTexture* apTexture)
{
	//ポインタのアドレスが正常化しらべる (nullならセットしない)
	if (apTexture == nullptr)return;
	m_pTexture = apTexture;
}
//テクスチャ設定:手裏剣
void CPlayer::SetBulletTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_bulletList[i].SetTexture(apTexture);
	}
}
//テクスチャ設定:斬撃
void CPlayer::SetSlashTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_swordList.SetTexture(apTexture);
}
//テクスチャ設定:爆弾
void CPlayer::SetBombTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_bombList.SetTexture(apTexture);
}
//テクスチャ設定：爆発
void CPlayer::SetBlastTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_bombList.SetBlastTexture(apTexture);
}

//オーナー設定
void CPlayer::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;
	m_pOwner = apOwner;
}

// 体力減少
void CPlayer::SetDamage(int dmg)
{
	// 体力減少
	m_hp -= dmg;
	//ヒット音発生
	hitseInst->Play();
	m_HitFlg = true;
	CEffect* effect = m_pOwner->GetEffect();
	effect->HitEffect(m_pos,m_moveVal,1.5);	// ヒットエフェクト発生
}

// 体力回復
void CPlayer::SetHeal(int heal)
{
	m_hp += heal;
	CEffect* effect = m_pOwner->GetEffect();
	effect->PlayerHealEffect();		// 回復エフェクト発生
	healseInst->Play();
}

// 座標セットX(現在座標に足し算)
void CPlayer::SetPosX(float x)
{
	m_pos.x = x;
}
// 座標セットY(現在座標に足し算)
void CPlayer::SetPosY(float y)
{
	m_pos.y = y;
}
// 移動量セットX(移動量を入力)
void CPlayer::SetMovevalX(float movex)
{
	m_moveVal.x = movex;
}
// 移動量セットY(移動量を入力)
void CPlayer::SetMovevalY(float movey)
{
	m_moveVal.y = movey;
}

// キー操作一覧
void CPlayer::KeyOperation()
{
	/* 移動 */
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_moveVal.y += SPEED::PLAYER;
		m_direction = Up;
		if(m_status==eIdle) //プレイヤーが"立ち"状態の時に"歩き"状態に変える
		m_status = eWalking;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_moveVal.y -= SPEED::PLAYER;
		m_direction = Down;
		if (m_status == eIdle) //プレイヤーが"立ち"状態の時に"歩き"状態に変える
			m_status = eWalking;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_moveVal.x -= SPEED::PLAYER;
		m_direction = Left;
		if (m_status == eIdle) //プレイヤーが"立ち"状態の時に"歩き"状態に変える
			m_status = eWalking;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_moveVal.x += SPEED::PLAYER;
		m_direction = Right;
		if (m_status == eIdle) //プレイヤーが"立ち"状態の時に"歩き"状態に変える
			m_status = eWalking;
	}

	/* 攻撃 */
	//左クリック攻撃
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		Attack(m_bLClick, m_LClick);
		m_bLClick = true;
	}
	else m_bLClick = false;
	//右クリック攻撃
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		Attack(m_bRClick, m_RClick);
		m_bRClick = true;
	}
	else m_bRClick = false;

	/* 武器チェンジ */
	//左クリック武器
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (!m_bLChange)
		{
			m_LClick = ChangeItem(m_LClick);
			if (m_LClick == m_RClick)m_LClick = ChangeItem(m_LClick);
			m_bLChange = true;
		}
	}
	else m_bLChange = false;
	//右クリック武器
	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (!m_bRChange)
		{
			m_RClick = ChangeItem(m_RClick);
			if (m_RClick == m_LClick)m_RClick = ChangeItem(m_RClick);
			m_bRChange = true;
		}
	}
	else m_bRChange = false;
}

//マップとの当たり判定
void CPlayer::HitCheckMap()
{
	CEnemy* enemy = m_pOwner->GetEnemy();
	CBoss* boss = enemy->GetBossList();
	CMap* map = m_pOwner->GetMap();

	float(*chipX)[MAP_CHIP_W] = map->GetPosX();
	float(*chipY)[MAP_CHIP_W] = map->GetPosY();
	int(*chipData)[MAP_CHIP_W] = map->GetChipData();
	int mapData = map->GetMapData();	//マップデータ取得

	//マップデータを使って
	int hit = 0;
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			if (chipData[h][w] >= 78 && chipData[h][w] <= 79)	//データ：ギミック
			{
				if (mapData == OneFloor)
				{
					hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
					if (hit == 1)
					{
						if (enemy->bGetEvent())map->SetLock();	// カギ閉め
						enemy->Event();		// イベント発生
					}
				}
				else if (mapData == BossFloor)
				{
					// イベント発生処理
					hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
					if (hit == 1) 
					{
						map->SetLock();		// カギ閉め
						enemy->SetBoss();
						enemy->SetSamurai(mapData);
						enemy->SetArcher(mapData);
						enemy->SetGiant(mapData);
						boss->bSetButtleStart();	// 戦闘開始フラグtrue
						m_pOwner->SetbossBGMFlg(); //ボスBGMフラグをtrueにする
					}
					m_pOwner->SetBGMFlg();
				}
			}
			else if (chipData[h][w] >= 91 && chipData[h][w] <= 94)	//データ：扉
			{
				// 通常の壁判定
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);
				HitChkMapAndBullet({ chipX[h][w],chipY[h][w] }, chipX[0][0]);
			}
			else if (chipData[h][w] >= 90 && chipData[h][w] <= 94)	//データ：回復ポイント
			{
				if (m_bHeal) continue;
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
				{
					SetHeal(HP::PLAYER);
					m_bHeal = true;
				}
			}
			else if (chipData[h][w] == 95)	// ギミック：トゲ
			{
				if (m_HitFlg) continue;
				bool hit = bMapHitFunction({ chipX[h][w],chipY[h][w] });
				if (hit) SetDamage(POWER::THORNS);
			}
			else if (chipData[h][w] == 96)	// データ：灯籠
			{
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				if (hit == 2 || hit == 4) { map->SetUnlock(); gimmickseInst->Play(); }
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);
			}
			else if (chipData[h][w] >= 111 && chipData[h][w] <= 119)	//	Map5の階層判定
			{
				// 通常の壁判定
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);
			}
			else if (chipData[h][w] == 80)	//データ：ギミック
			{
				// 矢の発射
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
				{
					int y = rand() % 4 + 18;
					int x = 37;
					enemy->shot({ chipX[y][x], chipY[y][x] }, m_pos);
				}
			}
			else if (chipData[h][w] == 70)	//データ：看板表示
			{
				if (mapData != OutSide)continue;
				CMessage* msgList = m_pOwner->GetMsg();
				//看板前判定
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
				{
					int msgNum = 0;
					if (w == 5)msgNum = 0;
					else if (w == 8)msgNum = 1;
					else if (w == 11)msgNum = 2;
					if (w == 16)msgNum = 5;

					// メッセージ表示
					msgList->SetMessage({ chipX[h][w],chipY[h][w] + 100 }, msgNum);
					return;
				}
				else msgList->SetAlive();
			}
			else if (chipData[h][w] >= 60 && chipData[h][w] <= 69)	//データ：マップチェンジ
			{
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
				{
					map->SetMapSwitchFlg(true);		//マップ切り替えフラグ
				}
			}
			else if (chipData[h][w] >= 49 && chipData[h][w] <= 59)	//データ：扉
			{
				////////////////////////////////////////////////////////////////
				//		プレイヤーのヒットチェック								
				////////////////////////////////////////////////////////////////
				// 通常の壁判定
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);

				// 鍵を制限数持ってる状態で鍵付き壁に触れると
				if ((m_KeyPossession >= 2) && (bMapHitFunction({ chipX[h][w],chipY[h][w] })))
				{
					map->SetUnlock();	// 鍵開け処理
					unlockseInst->Play();
				}
				////////////////////////////////////////////////////////////////
				//		弾のヒットチェック								
				////////////////////////////////////////////////////////////////
				HitChkMapAndBullet({ chipX[h][w],chipY[h][w] }, chipX[0][0]);
			}
			else if (chipData[h][w] == 21)		// データ：メッセージ
			{
				if (mapData != OneFloor && mapData != TwoFloor)continue;
				CMessage* msgList = m_pOwner->GetMsg();
				//看板前判定
				if (bMapHitFunction({chipX[h][w],chipY[h][w]}))
				{
					int msgNum = 0;
					if (w == 23)msgNum = 3;
					if (w == 24)msgNum = 6;
					if (w == 34)msgNum = 4;
					
					// メッセージ表示
					msgList->SetMessage({ chipX[h][w],chipY[h][w] + 100 }, msgNum);
					return;
				}
				else msgList->SetAlive();
			}
			else if (chipData[h][w] <= 19 && chipData[h][w] >= 18)	// データ：ふすま
			{
				if (mapData == BossFloor)
				{
					hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
					HitMapCase({ chipX[h][w],chipY[h][w] }, hit);
					HitChkMapAndBullet({ chipX[h][w],chipY[h][w] }, chipX[0][0]);
				}
			}
			else if (chipData[h][w] >= 10)	continue; //データ：床
			else	//データ：壁
			{
				////////////////////////////////////////////////////////////////
				//		プレイヤーのヒットチェック								
				////////////////////////////////////////////////////////////////
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);
				////////////////////////////////////////////////////////////////
				//		弾のヒットチェック								
				////////////////////////////////////////////////////////////////
				HitChkMapAndBullet({ chipX[h][w],chipY[h][w] }, chipX[0][0]);
			}
		}
	}
}

// マップとプレイヤーの判定関数(bool判定)
bool CPlayer::bMapHitFunction(Math::Vector2 chipPos)
{
	if (!Utility::bHitCheck(m_pos, m_moveVal,chipPos,
		PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
		Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
	{
		return true;
	}
	return false;
}
// マップとプレイヤーの判定関数(int判定)
int CPlayer::iMapHitFunction(Math::Vector2 chipPos)
{
	return Utility::iHitCheck(m_pos, m_moveVal, chipPos.x, chipPos.y,
		PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
		Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32);
}
// マップと弾の当たり判定
void CPlayer::HitChkMapAndBullet(Math::Vector2 chipPos, float chipX)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!m_bulletList[i].IsAlive())continue;
		//ヒット時
		if (!Utility::bHitCheck(m_bulletList[i].GetPos(), m_bulletList[i].GetMove(), { chipPos.x,chipPos.y },
			SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
			Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
		{
			m_bulletList[i].SetAlive();	//弾のフラグ下げ
			break;
		}
		if (m_bulletList[i].GetPos().x < chipX - SHURIKEN_SIZE::LEFT) m_bulletList[i].SetAlive();
	}
}
// 四辺の当たり判定関数
void CPlayer::HitMapCase(Math::Vector2 chipPos, int HitCase)
{
	//マップの現在座標の四辺
	const float MAP_LEFT = chipPos.x - Infor::RADIUS_32;		//左辺
	const float MAP_RIGHT = chipPos.x + Infor::RADIUS_32;		//右辺
	const float MAP_TOP = chipPos.y + Infor::RADIUS_32;		//上辺
	const float MAP_BOTTOM = chipPos.y - Infor::RADIUS_32;	//下辺
	switch (HitCase)
	{
	case 1:m_pos.y = MAP_TOP + PLAYER_SIZE::TOP;
		m_moveVal.y = 0;
		break;
	case 2:
		m_pos.y = MAP_BOTTOM - PLAYER_SIZE::DOWN;
		m_moveVal.y = 0;
		break;
	case 3:m_pos.x = MAP_LEFT - PLAYER_SIZE::LEFT;
		m_moveVal.x = 0;
		break;
	case 4:
		m_pos.x = MAP_RIGHT + PLAYER_SIZE::RIGHT;
		m_moveVal.x = 0;
	break; 
	default:
		break;
	}
}

//敵との当たり判定
void CPlayer::HitCheckEnemy()
{
	CEnemy* enemy = m_pOwner->GetEnemy();		// 敵クラス取得
	CEffect* effect = m_pOwner->GetEffect();	// エフェクトクラス取得
	const float EffectSize = 1.6;	// ヒットエフェクトサイズ

	////////////////////////////////////////////////////////////////
	//		侍との当たり判定								
	////////////////////////////////////////////////////////////////
	CSamurai* samuraiList = enemy->GetSamuraiList();	//敵クラス：侍リスト取得
	for (int e = 0; e < SAMURAI_MAX; e++)
	{
		Math::Vector2 enePos = samuraiList[e].GetPos();		//座標取得
		Math::Vector2 eneMove = samuraiList[e].GetMove();	//移動量取得

		if (!samuraiList[e].IsAlive()) continue;	// 生存時の敵のみ

		/* 弾のヒットチェック */
		if (HitCheckEnemy_And_Bullet(enePos, SAMURAI_SIZE::LEFT, SAMURAI_SIZE::RIGHT, SAMURAI_SIZE::TOP, SAMURAI_SIZE::DOWN))
		{
			samuraiList[e].SetDamage(POWER::PLAYER_SHURIKEN);	// 敵にダメージ
			effect->HitEffect(enePos, eneMove, EffectSize);		// ダメージエフェクト発生
		}
		/* 斬撃のヒットチェック */
		if (m_swordList.bGetSlash()) // 斬撃を出している間
		{
			if(HitCheckEnemy_And_Slash(enePos, samuraiList[e].bGetSlashHit(), SAMURAI_SIZE::LEFT))
			{
				samuraiList[e].SetDamage(POWER::PLAYER_SLASH);	// 敵にダメージ
				samuraiList[e].bSetSlashHit(true);				// 多段ヒット防止
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else samuraiList[e].bSetSlashHit(false);
		/* 爆発のヒットチェック */
		if (m_bombList.GetBlastAlive()) // 爆発している時
		{
			if (HitCheckEnemy_And_Blast(enePos, samuraiList[e].bGetBlastHit(), SAMURAI_SIZE::LEFT, SAMURAI_SIZE::RIGHT, SAMURAI_SIZE::TOP, SAMURAI_SIZE::DOWN))
			{
				samuraiList[e].SetDamage(POWER::PLAYER_BLAST);	//敵にダメージ
				samuraiList[e].bSetBlastHit(true);				// 多段ヒット防止
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else samuraiList[e].bSetBlastHit(false);
	}
	////////////////////////////////////////////////////////////////
	//		弓兵との当たり判定								
	////////////////////////////////////////////////////////////////
	CArcher* archerList = enemy->GetArcherList();	//敵クラス：弓兵リスト取得
	for (int e = 0; e < ARCHER_MAX; e++)
	{
		Math::Vector2 enePos = archerList[e].GetPos();		//座標取得
		Math::Vector2 eneMove = archerList[e].GetMove();	//移動量取得

		if (!archerList[e].IsAlive()) continue;	// 生存時の敵のみ

		/* 弾のヒットチェック */
		if (HitCheckEnemy_And_Bullet(enePos, ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN))
		{
			archerList[e].SetDamage(POWER::PLAYER_SHURIKEN);	// 敵にダメージ
			effect->HitEffect(enePos, eneMove, EffectSize);		// ダメージエフェクト発生
		}
		/* 斬撃のヒットチェック */
		if (m_swordList.bGetSlash()) // 斬撃を出している間
		{
			if (HitCheckEnemy_And_Slash(enePos, archerList[e].bGetSlashHit(), ARCHER_SIZE::LEFT))
			{
				archerList[e].SetDamage(POWER::PLAYER_SLASH);	// 敵にダメージ
				archerList[e].bSetSlashHit(true);				// 多段ヒット防止
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else archerList[e].bSetSlashHit(false);
		/* 爆発のヒットチェック */
		if (m_bombList.GetBlastAlive()) // 爆発している時
		{
			if (HitCheckEnemy_And_Blast(enePos, archerList[e].bGetBlastHit(), ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN))
			{
				archerList[e].SetDamage(POWER::PLAYER_BLAST);	//敵にダメージ
				archerList[e].bSetBlastHit(true);				// 多段ヒット防止
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else archerList[e].bSetBlastHit(false);
	}
	////////////////////////////////////////////////////////////////
	//		大男との当たり判定								
	////////////////////////////////////////////////////////////////
	CGiant* giantList = enemy->GetGiantList();	//敵クラス：大男リスト取得
	for (int e = 0; e < GIANT_MAX; e++)
	{
		Math::Vector2 enePos = giantList[e].GetPos();		//座標取得
		Math::Vector2 eneMove = giantList[e].GetMove();		//移動量取得

		if (!giantList[e].IsAlive()) continue;	// 生存時の敵のみ

		/* 弾のヒットチェック */
		if (HitCheckEnemy_And_Bullet(enePos, GIANT_SIZE::LEFT, GIANT_SIZE::RIGHT, GIANT_SIZE::TOP, GIANT_SIZE::DOWN))
		{
			giantList[e].SetDamage(POWER::PLAYER_SHURIKEN);		//敵にダメージ
			effect->HitEffect(enePos, eneMove, EffectSize);		//ダメージエフェクト発生
		}
		/* 斬撃のヒットチェック */
		if (m_swordList.bGetSlash()) // 斬撃を出している間
		{
			if (HitCheckEnemy_And_Slash(enePos, giantList[e].bGetSlashHit(), GIANT_SIZE::LEFT))
			{
				giantList[e].SetDamage(POWER::PLAYER_SLASH);	//敵にダメージ
				giantList[e].bSetSlashHit(true);				// 多段ヒット防止
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else giantList[e].bSetSlashHit(false);
		/* 爆発のヒットチェック */
		if (m_bombList.GetBlastAlive()) // 爆発している時
		{
			if (HitCheckEnemy_And_Blast(enePos, giantList[e].bGetBlastHit(), GIANT_SIZE::LEFT, GIANT_SIZE::RIGHT, GIANT_SIZE::TOP, GIANT_SIZE::DOWN))
			{
				giantList[e].SetDamage(POWER::PLAYER_BLAST);	//敵にダメージ
				giantList[e].bSetBlastHit(true);				// 多段ヒット防止
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else giantList[e].bSetBlastHit(false);
	}
	////////////////////////////////////////////////////////////////
	//		ボスとの当たり判定								
	////////////////////////////////////////////////////////////////
	CBoss* bossList = enemy->GetBossList();				//敵クラス：ボスリスト取得
	Math::Vector2 enePos = bossList->GetPos();			//座標取得
	Math::Vector2 eneMove = bossList->GetMove();		//移動量取得

	if (!bossList->IsAlive()) return;	// 生存時の敵のみ

	/* 弾のヒットチェック */
	if (HitCheckEnemy_And_Bullet(enePos,BOSS_SIZE::LEFT, BOSS_SIZE::RIGHT, BOSS_SIZE::TOP, BOSS_SIZE::DOWN))
	{
		bossList->SetDamage(POWER::PLAYER_SHURIKEN);		//敵にダメージ
		effect->HitEffect(enePos, eneMove, EffectSize);		//ダメージエフェクト発生
	}
	/* 斬撃のヒットチェック */
	if (m_swordList.bGetSlash()) // 斬撃を出している間
	{
		if (HitCheckEnemy_And_Slash(enePos, bossList->bGetSlashHit(), BOSS_SIZE::LEFT))
		{
			bossList->SetDamage(POWER::PLAYER_SLASH);	//敵にダメージ
			bossList->bSetSlashHit(true);				// 多段ヒット防止
			effect->HitEffect(enePos, eneMove, EffectSize);
		}
	}
	else bossList->bSetSlashHit(false);
	/* 爆発のヒットチェック */
	if (m_bombList.GetBlastAlive()) // 爆発している時
	{
		if (HitCheckEnemy_And_Blast(enePos, bossList->bGetBlastHit(), BOSS_SIZE::LEFT, BOSS_SIZE::RIGHT, BOSS_SIZE::TOP, BOSS_SIZE::DOWN))
		{
			bossList->SetDamage(POWER::PLAYER_BLAST);	//敵にダメージ
			bossList->bSetBlastHit(true);				// 多段ヒット防止
			effect->HitEffect(enePos, eneMove, EffectSize);
		}
	}
	else bossList->bSetBlastHit(false);
}

// 敵と手裏剣当たり判定関数
bool CPlayer::HitCheckEnemy_And_Bullet(Math::Vector2 enePos, float left, float right, float top, float down)
{
	for (int b = 0; b < BULLET_MAX; b++)
	{
		if (m_bulletList[b].IsAlive()) // 発射中のみ
		{
			//ヒット時
			if (!Utility::bHitCheck(m_bulletList[b].GetPos(), m_bulletList[b].GetMove(), enePos,
				SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
				left,right,top,down))
			{
				m_bulletList[b].SetAlive();	//弾のフラグ下げ
				return true;
			}
		}
	}
	return false;
}
// 敵と斬撃当たり判定関数
bool CPlayer::HitCheckEnemy_And_Slash(Math::Vector2 enePos, bool bSlashHit, float size)
{
	if (!bSlashHit)	// 多段ヒット防止フラグ
	{
		// 敵と斬撃の距離
		const float checkDist = Utility::GetDistance(enePos, m_swordList.GetPos());
		// ヒット判定の距離
		const float hitDist = SLASH_SIZE::LEFT + size;
		// ヒット判定よりも距離が近いとき
		if (checkDist <= hitDist) return true;
	}
	return false;
}
// 敵と爆風当たり判定関数
bool CPlayer::HitCheckEnemy_And_Blast(Math::Vector2 enePos, bool bBlastHit, float left, float right, float top, float down)
{
	if (!bBlastHit)
	{
		if (!Utility::bHitCheck(m_bombList.GetBlastPos(), { 0,0 }, enePos,
			BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN,
			left,right,top,down)) return true;
	}
	return false;
}

// 爆風との当たり判定
void CPlayer::HitCheckBomb()
{
	if (m_HitFlg) return;

	CEffect* effect = m_pOwner->GetEffect();
	CDamage* dmgList = effect->GetDmgList();
	//爆発している時
	if (m_bombList.GetBlastAlive())
	{
		//ヒット時
		if (!Utility::bHitCheck(m_pos, m_moveVal, m_bombList.GetBlastPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN))
		{
			SetDamage(POWER::PLAYER_BLAST);
		}
	}
}

//アイテムとの当たり判定
void CPlayer::HitCheckItem()
{
	CItem* item = m_pOwner->GetItem();
	
	////////////////////////////////////////////////////////////////
	//		アイテム：爆弾								
	////////////////////////////////////////////////////////////////
	CItem_Bomb* ItemBomb = item->GetBombItem();	//爆弾リスト取得
	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		// 爆弾所持数最大なら入手しない
		if (m_BombPossession >= BOMB_MAX) break;

		if (!ItemBomb[i].GetAlive())continue;
		
		//ヒット時
		if (!Utility::bHitCheck(m_pos, m_moveVal, ItemBomb[i].GetPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			ITEM_BOMB_SIZE::LEFT,ITEM_BOMB_SIZE::RIGHT,ITEM_BOMB_SIZE::TOP,ITEM_BOMB_SIZE::DOWN))
		{
			ItemBomb[i].bSetbombHit();	//拾った判定入手
			ItemBomb[i].SetAlive();		//爆弾のフラグ下げ
			m_BombPossession = BOMB_MAX;	//アイテム入手
			itempuseInst->Play();
		}
	}
	////////////////////////////////////////////////////////////////
	//		アイテム：鍵								
	////////////////////////////////////////////////////////////////
	//鍵リスト取得
	CItem_Key* ItemKey = item->GetKeyItem();
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		if (!ItemKey[i].GetAlive()) continue;

		//ヒット時
		if (!Utility::bHitCheck(m_pos, m_moveVal, ItemKey[i].GetPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			ITEM_KEY_SIZE::LEFT,ITEM_KEY_SIZE::RIGHT,ITEM_KEY_SIZE::TOP,ITEM_KEY_SIZE::DOWN))
		{
			ItemKey[i].SetAlive();		//鍵のフラグ下げ
			keypuseInst->Play();
			m_KeyPossession++;		//鍵入手
		}
	}
	////////////////////////////////////////////////////////////////
	//		アイテム：回復								
	////////////////////////////////////////////////////////////////
	//回復リスト取得
	CItem_Health* ItemHealth = item->GetHealthItem();
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		if (!ItemHealth[i].GetAlive())continue;
		
		//ヒット時
		if (!Utility::bHitCheck(m_pos, m_moveVal, ItemHealth[i].GetPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			ITEM_HELSE_SIZE::LEFT,ITEM_HELSE_SIZE::RIGHT,ITEM_HELSE_SIZE::TOP,ITEM_HELSE_SIZE::DOWN))
		{
			ItemHealth[i].SetAlive();		// 回復のフラグ下げ
			SetHeal(5);		// 回復
		}
	}
	////////////////////////////////////////////////////////////////
	//		アイテム：隠れ蓑								
	////////////////////////////////////////////////////////////////
	//隠れ蓑リスト取得
	CItem_Mino* ItemMino = item->GetMinoItem();
	if (!ItemMino->GetAlive())return;
	//ヒット時
	if (!Utility::bHitCheck(m_pos, m_moveVal, ItemMino->GetPos(),
		PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
		ITEM_HIDE_SIZE::LEFT,ITEM_HIDE_SIZE::RIGHT,ITEM_HIDE_SIZE::TOP,ITEM_HIDE_SIZE::DOWN))
	{
		ItemMino->SetAlive();			// フラグ下げ
		m_bMinoPossession = true;		// 隠れ蓑入手
		itempuseInst->Play();
	}
}

//武器切り替え関数
eClick CPlayer::ChangeItem(eClick click)
{
	switch (click)
	{
	case eShuriken:
		return eSword;
	case eSword:
		if (m_BombPossession > 0)return eBomb;
	case eBomb:
		if (m_bMinoPossession) return eHidden;	// 隠れ蓑所持時使用可能
		else return eShuriken;
	case eHidden:
		return eShuriken;
	}
}

// 攻撃関数
void CPlayer::Attack(bool flg, eClick click)
{
	if (flg) return;
	switch (click)
	{
	case eSword:	//刀
		SetSword();
		break;
	case eShuriken:	//手裏剣
		SetShuriken();
		break;
	case eBomb:		//爆弾
		SetBomb();
		break;
	case eHidden:	//隠れ身
		SetHidden();
		break;
	}
}

//攻撃：手裏剣
void CPlayer::SetShuriken()
{
	if (m_shurikenCnt < COOL_TIME::PLAYER_SHURIKEN) return;
	
	m_hiddenList.bSetHidden();	// 攻撃時隠れ身解除

	// 弾発射
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!m_bulletList[i].IsAlive())
		{
			Inversion();	// プレイヤー左右反転関数
			// 発射角度を求める
			float deg = Utility::GetAngleDeg(m_pos, { (float)m_ClickPoint.x, (float)m_ClickPoint.y });
			// 発射
			m_bulletList[i].Shot(m_pos, deg);
			m_shurikenCnt = 0;
			shurikenseInst->Play();
			break;
		}
	}
}

//攻撃：刀
void CPlayer::SetSword()
{
	if (m_slashCnt < COOL_TIME::PLAYER_SLASH) return;	// 斬撃カウント制限
	
	m_status = eAttack; //プレイヤーの状態を"攻撃"にする
	m_hiddenList.bSetHidden();	// 攻撃時隠れ身解除

	// 斬撃発動
	if (!m_swordList.bGetSlash())
	{
		Inversion();	// プレイヤー左右反転関数
		// 発射角度を求める
		float deg = Utility::GetAngleDeg(m_pos, { (float)m_ClickPoint.x, (float)m_ClickPoint.y });
		// 斬撃発生
		m_swordList.Slash(m_pos, deg);
		m_slashCnt = 0;
		katanaseInst->Play();
	}
}

//攻撃：爆弾
void CPlayer::SetBomb()
{
	if (m_BombPossession <= 0) return;

	m_hiddenList.bSetHidden();	// 攻撃時隠れ身解除

	// 爆弾発動
	if (!m_bombList.IsAlive())
	{
		m_bombList.InstBomb(m_pos);
		m_BombPossession--;		// 個数減少
	}
}

//隠れ身
void CPlayer::SetHidden()
{
	m_hiddenList.Hidden();	// 隠れ身
	if (m_hiddenList.bGetHidden())
	{
		m_alpha = 0.2f;
		m_HitFlg = false;
	}
}

//無敵時間
void CPlayer::invincibleTime()
{
	if (m_HitFlg)	//プレイヤーが当たったら
	{
		m_hiddenList.bSetHidden();		// 隠れ身解除

		const int CNT_MAX = 120;	//無敵時間
		if (m_invincibleCnt >= CNT_MAX)
		{
			m_alpha = 1.0f;
			m_invincibleCnt = 0;
			m_HitFlg = false;
			return;
		}
		m_invincibleCnt++;

		//点滅
		if (m_invincibleCnt % 10 == 0)
		{
			if (m_alpha < 1)m_alpha = 1;
			else m_alpha = 0.5;
		}
	}
	else
	{
		m_invincibleCnt = 0;
		if (!m_hiddenList.bGetHidden()) m_alpha = 1.0f;
	}
}

// 向き反転関数
void CPlayer::Inversion()
{
	// プレイヤーの方向と逆方向にカーソルがある場合左右反転
	if (m_pos.x < (float)m_ClickPoint.x && m_direction != Right) m_direction = Right;
	else if (m_pos.x > (float)m_ClickPoint.x && m_direction != Left) m_direction = Left;
}

void CPlayer::Animation()
{
	switch (m_status)
	{
	case eIdle:
		m_aTimer = 15;
		m_aflame = 6;
		break;
	case eWalking:
		m_aTimer = 10;
		m_aflame = 6;
		break;
	case eAttack:
		m_aTimer = 5;
		m_aflame = 3;
		break;
	default:
		break;
	}

	const int CNT_MAX = m_aTimer * m_aflame;
	if (m_aCnt >= CNT_MAX - 1)
	{
		m_aCnt = 0;
	}
	m_aCnt++;

	//攻撃アニメーションの計算
	if (m_status == eAttack)
	{
		const int CNT_MAX = m_aTimer * m_aflame;
		if (m_aCnt >= CNT_MAX - 1)
		{
			m_aAttackCnt = 0;
			m_status = eIdle;
		}
		m_aAttackCnt++;
	}

}

// アニメーション
int CPlayer::AnimationCalc(int cnt, const int xtex)
{
	return cnt / m_aTimer * 116 + 38 + xtex;
}
