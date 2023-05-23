#include"CGiant.h"
#include"Utility.h"

CGiant::CGiant()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_bAlive(false)
	, m_hp(HP::GIANT)
	, m_dmg(0)
	, m_deg(0)
	, m_VisibilityFlg(false)
	, m_bSlashHit(false)
	, m_bBlastHit(false)
	, m_bDrop(false)
	, m_moveCnt(MOVE_CNT_MAX)
	, m_rushCnt(0)
	, m_bRush(false)
	, m_bAtk(false)
	, m_atkCnt(0)
	, m_atkRnd(0)
	, m_scrollPos(0,0)
	, m_playerPos(0,0)
	, m_bHidden(false)
{
}

CGiant::~CGiant()
{
}

// 初期化
void CGiant::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_hp = HP::GIANT;
	m_dmg = 0;
	m_VisibilityFlg = false;
	m_bSlashHit = false;
	m_bBlastHit = false;
	m_bDrop = false;
	m_rushCnt = 0;
	m_bRush = false;
	m_bAtk = false;
	m_atkCnt = 0;
	m_atkRnd = 0;
	m_scrollPos = { 0,0 };
	m_playerPos = { 0,0 };
	m_bHidden = false;
}

// 更新
void CGiant::Update(int mapData)
{
	if (!m_bAlive) return;

	// ダメージ処理
	m_hp -= m_dmg;
	m_dmg = 0;
	// 死亡処理
	if (m_hp <= 0)
	{
		m_bAlive = false;
		if (mapData == 3) m_bDrop = true;
		return;
	}

	// プレイヤーとの距離を求める
	float m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// プレイヤーとの角度を求める 
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);

	// 一定の距離に近づいたら
	if (m_dist < 400 ) m_VisibilityFlg = true;		// 視野フラグ上げ
	// 一定の距離に離れたら
	if (m_dist > 500)	m_VisibilityFlg = false;	// 視野フラグ下げ

	// プレイヤーが隠れ蓑使用時
	if (m_bHidden) m_VisibilityFlg = false;	// 視野フラグ下げる

	// 視界内の時
	if (m_VisibilityFlg) Attack();	//攻撃態勢
	// 視野外
	else Walk();	//散歩

	// 座標確定
	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;

	//行列
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	m_scaleMat = DirectX::XMMatrixScaling(1.0f, 1.0f, 0.0f);
	m_mat = m_scaleMat * m_transMat;	// 行列作成
}

// 描画
void CGiant::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 70, 80), 1.0f);
}

// 配置関数
void CGiant::SetGiant(Math::Vector2 pos)
{
	m_pos = pos;
	m_bAlive = true;
}

// テクスチャ設定
void CGiant::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pTexture = apTexture;
}

// X座標セット
void CGiant::SetPosX(float posX)
{
	m_pos.x = posX;
}

// Y座標セット
void CGiant::SetPosY(float posY)
{
	m_pos.y = posY;
}

// X移動量セット
void CGiant::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

//  Y移動量セット
void CGiant::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

//  生存フラグ設定
void CGiant::SetAlive()
{
	m_bAlive = false;
}

// ダメージ処理
void CGiant::SetDamage(int dmg)
{
	m_dmg += dmg;
}

// 斬撃ヒットフラグセット
void CGiant::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

// 爆風ヒットフラグセット
void CGiant::bSetBlastHit(bool aHit)
{
	m_bBlastHit = aHit;
}

// ドロップフラグセット
void CGiant::bSetDrop()
{
	m_bDrop = false;
}

// スクロール量取得用
void CGiant::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// プレイヤーの座標取得
void CGiant::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

// 隠れ身状態取得
void CGiant::bSetHidden(bool flg)
{
	m_bHidden = flg;
}

// 攻撃関数
void CGiant::Attack()
{
	// ランダム行動
	switch (m_atkRnd)
	{
	case 1:
		m_bAtk = true;
		Rush();	// 突進
		break;
	default:
		Homing(SPEED::GIANT_NORMAL);	// ゆっくり近づく
		break;
	}

	// 行動変化カウント
	if (m_atkRnd == 1)return;
	if (m_atkCnt >= COOL_TIME::GIANT_ATK)
	{
		m_atkCnt = COOL_TIME::GIANT_ATK;
		// 攻撃してないとき
		if (!m_bAtk)
		{
			m_atkRnd = 1;
			m_atkCnt = 0;
		}
	}
	m_atkCnt++;
}

// ホーミング処理
void CGiant::Homing(float sp)
{
	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * sp;
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * sp;
}

// 突進
void CGiant::Rush()
{
	if (m_rushCnt >= RUSH_CNT_MAX)
	{
		m_rushCnt = 0;
		m_atkRnd = 0;
		m_bAtk = false;
	}
	else if (m_rushCnt >= RUSH_CNT_MAX / 1.2)
	{
		m_moveVal = { 0,0 };
		m_bRush = false;
	}
	else if (m_rushCnt >= RUSH_CNT_MAX / 2.5)
	{
		if (!m_bRush) Homing(SPEED::GIANT_RUSH);
		m_bRush = true;
	}
	else if (m_rushCnt >= 0)
	{
		const float sp = SPEED::GIANT_NORMAL;
		m_moveVal.x = -cos(DirectX::XMConvertToRadians(m_deg)) * sp;
		m_moveVal.y = -sin(DirectX::XMConvertToRadians(m_deg)) * sp;
	}
	m_rushCnt++;
}

// 徘徊処理
void CGiant::Walk()
{
	if (m_moveCnt >= MOVE_CNT_MAX)
	{
		const int rnd = 2;	// ランダム幅
		float moveX = (rand() % rnd - rnd/2);
		float moveY = (rand() % rnd - rnd/2);

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