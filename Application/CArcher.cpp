#include "CArcher.h"
#include"CArrow.h"
#include"Utility.h"

CArcher::CArcher()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_bAlive(false)
	, m_hp(HP::ARCHER)
	, m_dmg(0)
	, m_deg(0)
	, m_dist(0)
	, m_VisibilityFlg(false)
	, m_bSlashHit(false)
	, m_bBlastHit(false)
	, m_moveCnt(MOVE_CNT_MAX)
	, m_shotFlg(false)
	, m_shotCnt(0)
	, m_scrollPos(0,0)
	, m_playerPos(0,0)
	, m_bHidden(false)
{
}
CArcher::~CArcher()
{
}

//初期化
void CArcher::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_hp = HP::ARCHER;
	m_dmg = 0;
	m_VisibilityFlg = false;
	m_moveCnt = MOVE_CNT_MAX;
	m_shotFlg = false;
	m_shotCnt = 0;
	m_scrollPos = { 0,0 };
	m_playerPos = { 0,0 };
	m_bHidden = false;
}

//更新
void CArcher::Update()
{
	if (!m_bAlive) return;
	
	// ダメージ処理
	m_hp -= m_dmg;
	m_dmg = 0;

	// 死亡処理
	if (m_hp <= 0)
	{
		m_bAlive = false;
		m_shotCnt = 0;
		return;
	}


	// プレイヤーとの距離を求める
	float m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// プレイヤーとの角度を求める 
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);

	// 一定の距離に近づいたら
	if (m_dist < 350) m_VisibilityFlg = true;		// 視野フラグ上げ
	// 一定距離離れたら
	if (m_dist > 450) m_VisibilityFlg = false;		// 視野フラグ下げ

	// プレイヤーが隠れ蓑使用時、視野フラグ下げる
	if (m_bHidden)m_VisibilityFlg = false;

	if (m_VisibilityFlg)
	{
		Attack();
		// プレイヤーが近づいて来た時
		if (m_dist < 300)
		{
			// プレイヤーから逃げる
			float spd = SPEED::ARCHER;
			m_moveVal.x = -(cos(DirectX::XMConvertToRadians(m_deg)) * spd);
			m_moveVal.y = -(sin(DirectX::XMConvertToRadians(m_deg)) * spd);
		}
		else m_moveVal = { 0,0 };
	}
	else Walk();

	// 座標確定
	m_pos += m_moveVal;

	//行列
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	m_scaleMat = DirectX::XMMatrixScaling(1.0f, 1.0f, 0.0f);
	m_mat = m_scaleMat * m_transMat;	// 行列作成
}

//描画
void CArcher::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);	
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 64, 64), 1.0f);	
}

//テクスチャ設定
void CArcher::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

//弓兵設置
void CArcher::SetArchaer(Math::Vector2 pos)
{
	m_pos = pos;

	m_bAlive = true;
}

// X座標セット
void CArcher::SetPosX(float posX)
{
	m_pos.x = posX;
}

// Y座標セット
void CArcher::SetPosY(float posY)
{
	m_pos.y = posY;
}

// X移動量セット
void CArcher::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

// Y移動量セット
void CArcher::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

// 生存フラグ設定
void CArcher::SetAlive()
{
	m_bAlive = false;
}

// ダメージ処理
void CArcher::SetDamage(int dmg)
{
	m_hp -= dmg;
}

// 発射フラグ設定
void CArcher::SetShotFlg(bool flg)
{
	m_shotFlg = flg;
}

// 斬撃ヒットフラグセット
void CArcher::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

// 爆風ヒットフラグセット
void CArcher::bSetBlastHit(bool aHit)
{
	m_bBlastHit=aHit;
}

//スクロール量取得
void CArcher::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// プレイヤーの座標取得
void CArcher::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

void CArcher::bSetHidden(bool flg)
{
	m_bHidden = flg;
}

// 攻撃関数
void CArcher::Attack()
{
	// 発射された時
	if (m_shotFlg)
	{
		m_shotCnt = 0;	// カウントリセット
		m_shotFlg = false;			// 発射フラグ下げ
	}
	// 発射カウント
	if (m_shotCnt <= COOL_TIME::ARCHER_ARROW) m_shotCnt++;
}

// 見回り
void CArcher::Walk()
{
	if (m_moveCnt >= MOVE_CNT_MAX)
	{
		float moveX = float(rand() % 2 - 1);
		float moveY = float(rand() % 2 - 1);

		// ランダム移動量セット
		switch (int r = rand() % 16)
		{
		case 1:
			m_moveVal = { moveX, moveY };
			break;
		case 2:
			m_moveVal = { -moveX, -moveY };
			break;
		case 3:
			m_moveVal = { -moveX, moveY };
			break;
		case 4:
			m_moveVal = { moveX, -moveY };
			break;
		default:
			m_moveVal = { 0, 0 };
			break;
		}
		m_moveCnt = 0;
	}
	m_moveCnt++;
}

