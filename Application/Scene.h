#pragma once
#include "CPlayer.h"
#include "CEnemy.h"
#include "CMap.h"
#include"CItem.h"
#include"UI.h"
#include"CEffect.h"
#include"CMessage.h"
#include"CTitle.h"
#include"CResult.h"
#include"CDescription.h"

//シーンの種類
enum eSceneType
{
	eSceneTitle,		//0	Title
	eSceneGame,			//1	ゲーム
	eSceneDescription,	//2	説明
	eSceneResult		//3リザルト
};

//マウスの構造体
struct t_Mouse
{
	POINT cur;			//マウスカーソル座標
	POINT clickPoint;	//クリックした座標
	bool clickFlg;		//clickフラグ
};

class Scene
{
private:

	/* タイトル */
	Ctitle m_title;
	
	/* 説明シーン */
	CDescription m_descript;

	/* ゲームメイン */
	CPlayer m_player;	//プレイヤー
	CMap m_map;			//マップ
	CEnemy m_enemy;		//敵
	CItem m_item;		//アイテム
	CUI m_ui;			//UI
	CEffect m_effect;	//エフェクト
	CMessage m_message;	//メッセージ

	/* リザルト */
	CResult m_result;

	//テクスチャ関連
	//プレイヤー
	KdTexture m_playerTex;
	KdTexture m_bulletTex;
	KdTexture m_bombTex;
	KdTexture m_blastTex;

	//敵	
	KdTexture m_samuraiTex;
	KdTexture m_archerTex;
	KdTexture m_arrowTex;
	KdTexture m_GiantTex;
	KdTexture m_bossTex;
	
	//マップ
	KdTexture m_mapTex;

	//アイテム
	KdTexture m_ItemBombTex_t;
	KdTexture m_ItemBombTex_f;
	KdTexture m_ItemKeyTex;
	KdTexture m_ItemHealthTex;
	KdTexture m_ItemMinoTex;

	//UI
	KdTexture m_backTex;
	KdTexture m_rframeTex;
	KdTexture m_lframeTex;
	KdTexture m_HPTex;
	KdTexture m_HPbarTex;
	KdTexture m_HideTex;
	KdTexture m_HidebarTex;
	KdTexture m_katanaTex;
	KdTexture m_shurikenTex;
	KdTexture m_iconBombTex;
	KdTexture m_iconMinoTex;
	KdTexture m_stackBombTex;
	KdTexture m_stackKeyTex;


	// エフェクト
	KdTexture m_pSlashTex;
	KdTexture m_eSlashTex;
	KdTexture m_dmgTex;
	KdTexture m_darkenTex;
	KdTexture m_HealTex;
	KdTexture m_BlackTex;

	// メッセージ
	KdTexture m_msgTex;

	// タイトル
	KdTexture m_titleTex;
	KdTexture m_lineTex;
	
	// 説明
	KdTexture m_descriptTex;

	// リザルト
	KdTexture m_resultTex;


	eSceneType sceneType;	//0:タイトル　1:ゲーム本編

	//マウス
	KdTexture m_mousePointTex;
	t_Mouse m_mouse;

	Math::Color color;

	std::shared_ptr<KdSoundEffect> bgm;
	std::shared_ptr<KdSoundInstance> bgmInst;

	std::shared_ptr<KdSoundEffect> bossbgm;
	std::shared_ptr<KdSoundInstance> bossbgmInst;

	std::shared_ptr<KdSoundEffect> gameoverse;
	std::shared_ptr<KdSoundInstance> gameoverseInst;

	bool bgmflg;
	bool bossbgmflg;

	int blackcnt; // 暗転のカウント
	bool blackflg; //暗転しているか

public:

	// 初期設定
	void Init();
	// 解放
	void Release();

	// 更新処理
	void Update();
	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	//初期化リセット
	void Reset();

	//敵クラス取得
	CEnemy* GetEnemy(){ return &m_enemy; }

	//マップクラス取得
	CMap* GetMap(){ return &m_map; }
	
	//プレイヤークラス取得
	CPlayer* GetPlayer(){ return &m_player; }
	
	//アイテムクラス取得
	CItem* GetItem() { return &m_item; }

	// エフェクト
	CEffect* GetEffect() { return &m_effect; }

	// メッセージ
	CMessage* GetMsg() { return &m_message; }

	//タイトル
	void TitleUpdate();//更新
	void TitleDraw();//描画

	//ゲーム　
	void GameUpdate(); //更新
	void GameDraw();//描画

	//説明　
	void DescriptUpdate(); //更新
	void DescriptDraw(); //描画

	//リザルト
	void ResultUpdate();
	void ResultDraw();

	//マウス座標取得
	void GetMousePos(Math::Vector2 scrPos);
	void MousePointDraw();

	//セッター
	void SetBGMFlg();
	void SetbossBGMFlg();

private:
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;

	Scene() {}
public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()

// 点とOBBとの最近接点を求める
inline void PointToBox(const Math::Vector2& point, const Math::Vector2& obbCenterPos, const Math::Vector2& obbHalfSize, const Math::Matrix& obbMat, Math::Vector2& outNearestPos)
{
	// ※参考:[書籍]「ゲームプログラミングのためのリアルタイム衝突判定」
	Math::Vector2 d = point - obbCenterPos;
	// ボックスの中心における結果から開始、そのから段階的に進める。
	outNearestPos = obbCenterPos;
	// 各OBBの軸に対して
	for (int i = 0; i < 2; i++)
	{
		// dをその軸に投影して
		// ボックスの中心からdの軸に沿った距離を得る
		float dist = d.Dot((Math::Vector2&)obbMat.m[i]);
		// ボックスの範囲よりも距離が大きい場合、ボックスまでクランプ
		if (dist > (&obbHalfSize.x)[i]) dist = (&obbHalfSize.x)[i];
		if (dist < -(&obbHalfSize.x)[i]) dist = -(&obbHalfSize.x)[i];
		// ワールド座標を得るためにその距離だけ軸に沿って進める
		outNearestPos += dist * (Math::Vector2&)obbMat.m[i];
	}

}


//========================
// オブジェクト基本クラス
//========================
class ObjectBase
{
public:
	virtual ~ObjectBase() {}

	virtual void Update() {}
	virtual void Draw() {}

	virtual bool HitTest_Circle(const Math::Vector2& pos, float radius, Math::Vector2* hitPos) { return false; }

	virtual void DebugDraw() {}

	// 座標
	Math::Vector2	m_pos;
	float			m_z = 0;
};

//========================
// キャラ
//========================
class Chara : public ObjectBase
{
public:

	void Init(KdTexture* tex, float x, float y)
	{
		m_pTex = tex;
		m_pos.x = x;
		m_pos.y = y;
	}

	// 更新処理
	virtual void Update() override
	{
		// キー移動
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_pos.x -= 5.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_pos.x += 5.0f;

		}

	}

	// 描画処理
	virtual void Draw() override
	{
		Math::Matrix m;
		// キャラの行列
		m = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);

		// 行列セット
		SHADER.m_spriteShader.SetMatrix(m);
		// 描画
		SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, 48, 48, &Math::Rectangle(0, 0, 48, 48), &Math::Color(1,1,1,1), Math::Vector2(0.5f, 0.5f));
	}

private:
	KdTexture*	m_pTex = nullptr;
};
