#include"CSamurai.h"
#include"Utility.h"
#include"Scene.h"

CSamurai::CSamurai()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_size(1.0f,1.0f)
	, m_bAlive(false)
	, m_hp(HP::SAMURAI)
	, m_dmg(0)
	, m_deg(0)
	, m_dist(0)
	, m_VisibilityFlg(false)
	, m_bSlashHit(false)
	, m_bBlastHit(false)
	, m_bDrop(false)
	, m_moveCnt(MOVE_CNT_MAX)
	, m_bSlash(false)
	, m_atkRnd(0)
	, m_bAtk(false)
	, m_atkCnt(COOL_TIME::SAMURAI_SLASH/2)
	, m_scrollPos(0,0)
	, m_playerPos(0,0)
	, m_bHidden(false)
{
}

CSamurai::~CSamurai()
{
}

//初期化
void CSamurai::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_hp = HP::SAMURAI;
	m_dmg = 0;
	m_VisibilityFlg = false;
	m_bSlashHit = false;
	m_bBlastHit = false;
	m_bDrop = false;
	m_moveCnt = MOVE_CNT_MAX;
	m_bSlash = false;
	m_bAtk = false;
	m_atkCnt = 0;
	m_scrollPos = { 0,0 };
	m_playerPos = { 0,0 };
	m_bHidden = false;
}

//更新
void CSamurai::Update()
{
	if (!m_bAlive) return;

	// ダメージ処理
	m_hp -= m_dmg;
	m_dmg = 0;

	// 死亡処理
	if (m_hp <= 0)
	{
		m_bAlive = false;
		m_bDrop = true;
		return;
	}

	if(m_moveVal.x>0)
		m_size = { -1.0f, 1.0f };
	else if (m_moveVal.x < 0)
		m_size = { 1.0f, 1.0f };


	// プレイヤーとの距離を求める
	m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// プレイヤーとの角度を求める 
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);

	// 一定の距離に近づいたら
	if (m_dist < 300) m_VisibilityFlg = true;		// 視野フラグ上げ
	// 一定の距離に離れたら
	else if (m_dist > 400)	m_VisibilityFlg = false;	// 視野フラグ下げ
	
	// プレイヤーが隠れ蓑使用時、視野フラグ下げる
	if (m_bHidden)m_VisibilityFlg = false;

	// 視界内の時
	if (m_VisibilityFlg)
	{
		Attack();
	}
	// 視野外
	else Walk(); // 徘徊

	// 座標確定
	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;

	//行列
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	m_scaleMat = DirectX::XMMatrixScaling(m_size.x, m_size.y, 0.0f);
	m_mat = m_scaleMat * m_transMat;	// 行列作成
}

//描画
void CSamurai::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 62, 62), 1.0f);
}

//テクスチャ設定
void CSamurai::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

//侍の設置
void CSamurai::SetSamurai(Math::Vector2 pos)
{
	m_pos = pos;

	m_bAlive = true;
}

// X座標セット
void CSamurai::SetPosX(float posX)
{
	m_pos.x = posX;
}

// Y座標セット
void CSamurai::SetPosY(float posY)
{
	m_pos.y = posY;
}

// X移動量セット
void CSamurai::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

// Y移動量セット
void CSamurai::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

//生存フラグ設定
void CSamurai::SetAlive()
{
	m_bAlive = false;
}

// ダメージ処理
void CSamurai::SetDamage(int dmg)
{
	m_dmg += dmg;
}

// 斬撃攻撃フラグセット
void CSamurai::bSetSlash(bool flg)
{
	m_bSlash = flg;
}

// 攻撃フラグセット
void CSamurai::bSetAtk()
{
	m_bAtk = false;
}

// 斬撃ヒットフラグセット
void CSamurai::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

// 爆風ヒットフラグセット
void CSamurai::bSetBlastHit(bool aHit)
{
	m_bBlastHit = aHit;
}

// ドロップフラグセット
void CSamurai::bSetDrop()
{
	m_bDrop = false;
}

//スクロール量取得
void CSamurai::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// プレイヤーの座標取得
void CSamurai::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

// プレイヤーの隠れ蓑使用フラグ取得
void CSamurai::bSetHidden(bool flg)
{
	m_bHidden = flg;
}

// 攻撃関数
void CSamurai::Attack()
{
	const int stop = 90;
	if (m_dist <=150)
	{
		if(m_dist <= stop) m_moveVal = { 0,0 };
		// 斬撃攻撃
		if (m_atkCnt >= COOL_TIME::SAMURAI_SLASH)
		{
			bSetSlash(true);
			m_atkCnt = 0;
		}
		m_atkCnt+=2;
	}
	else
	{
		Homing(SPEED::SAMURAI);		// プレイヤーを追跡
		m_atkCnt++;
		if(m_atkCnt >= COOL_TIME::SAMURAI_SLASH - 50)
			m_atkCnt = COOL_TIME::SAMURAI_SLASH - 50;
	}
	
}

void CSamurai::Homing(float sp)
{
	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * sp;	// cos
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * sp;	// sin
}

// 見回り関数
void CSamurai::Walk()
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
