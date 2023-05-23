#include "main.h"
#include "Scene.h"
#include"Utility.h"

void Scene::Draw2D()
{
	switch (sceneType)
	{
	case eSceneTitle:
		//タイトル
		TitleDraw();
		break;
	case eSceneGame:
		//ゲーム本編
		GameDraw();
		break;
	case eSceneDescription:
		//説明
		DescriptDraw();
		break;
	case eSceneResult:
		//リザルト
		ResultDraw();
		break;
	}

	// マウスカーソル
	MousePointDraw();
}

void Scene::Update()
{
	switch (sceneType)
	{
	case eSceneTitle:
		//タイトル
		TitleUpdate();
		break;
	case eSceneGame:
		//ゲーム本編
		GameUpdate();
		break;
	case eSceneDescription:
		//説明
		DescriptUpdate();
		break;
	case eSceneResult:
		//リザルト
		ResultUpdate();
		break;
	}
}

void Scene::Init()
{
	srand(timeGetTime());

	Reset();
}

void Scene::Release()
{
	// プレイヤー
	m_playerTex.Release();
	m_bulletTex.Release();
	m_bombTex.Release();

	// 敵
	m_samuraiTex.Release();
	m_archerTex.Release();
	m_arrowTex.Release();
	m_GiantTex.Release();
	m_bossTex.Release();

	// マップ
	m_mapTex.Release();

	// アイテム
	m_ItemBombTex_t.Release();
	m_ItemBombTex_f.Release();
	m_ItemKeyTex.Release();
	m_ItemHealthTex.Release();
	m_ItemMinoTex.Release();

	// UI
	m_backTex.Release();
	m_rframeTex.Release();
	m_lframeTex.Release();
	m_HPTex.Release();
	m_HPbarTex.Release();
	m_HideTex.Release();
	m_HidebarTex.Release();
	m_katanaTex.Release();
	m_shurikenTex.Release();
	m_iconBombTex.Release();
	m_iconMinoTex.Release();
	m_stackBombTex.Release();
	m_stackKeyTex.Release();

	// エフェクト
	m_pSlashTex.Release();
	m_eSlashTex.Release();
	m_dmgTex.Release();
	m_HealTex.Release();

	// メッセージ
	m_msgTex.Release();

	// その他
	m_titleTex.Release();
	m_lineTex.Release();
	
	m_descriptTex.Release();
	m_resultTex.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_Once);

	CBoss* BossList = m_enemy.GetBossList();
	bool a = m_title.bGetToGame();
	bool b = m_title.bGetToDescript();

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		ImGui::Text("playerX : %.2f", m_player.GetPos().x);
		ImGui::Text("playerY : %.2f", m_player.GetPos().y);
		ImGui::Text("HP : %d", m_player.GetHp());
		ImGui::Text("R_Click : %d", m_player.GetR());
		ImGui::Text("L_Click : %d", m_player.GetL());
		ImGui::Text("Item_BombNum : %d", m_player.GetBombPossession());
		ImGui::Text("Item_KeyNum : %d", m_player.GetKeyPossession());
		ImGui::Text("BossHp : %d", BossList->GetHp());
		ImGui::Text("Activate : %f", m_player.GetHideCnt());
		
		ImGui::Checkbox("gameF", &a);
		ImGui::Checkbox("descF", &b);

	}
	ImGui::End();
}

//初期化リセット
void Scene::Reset()
{
	/*テクスチャ*/
	// タイトル画面
	m_titleTex.Load("Resource/Texture/Title/Op.png");
	m_lineTex.Load("Resource/Texture/Title/Line.png");

	// 説明画面
	m_descriptTex.Load("Resource/Texture/Description/descript.png");

	// プレイヤー
	m_playerTex.Load("Resource/Texture/Player/player.png");
	m_bulletTex.Load("Resource/Texture/Player/shuriken.png");
	m_bombTex.Load("Resource/Texture/Player/bomb.png");
	m_blastTex.Load("Resource/Texture/Player/blast.png");

	// 敵
	m_samuraiTex.Load("Resource/Texture/Enemy/samurai.png");
	m_archerTex.Load("Resource/Texture/Enemy/Archer.png");
	m_arrowTex.Load("Resource/Texture/Enemy/arrow.png");
	m_GiantTex.Load("Resource/Texture/Enemy/giant.png");
	m_bossTex.Load("Resource/Texture/Enemy/idle_0.png");	// ボス

	// マップ
	m_mapTex.Load("Resource/Texture/Map/Map1.png");
	
	// アイテム
	m_ItemBombTex_t.Load("Resource/Texture/Item/BombStorage_true.png");		// 爆弾_有
	m_ItemBombTex_f.Load("Resource/Texture/Item/BombStorage_false.png");		// 爆弾_無
	m_ItemKeyTex.Load("Resource/Texture/Item/Key.png");						// 鍵
	m_ItemHealthTex.Load("Resource/Texture/Item/onigirio.png");				// 回復
	m_ItemMinoTex.Load("Resource/Texture/Item/hidemino.png");					// 隠れ蓑

	// UI
	m_backTex.Load("Resource/Texture/UI/back.png");
	m_rframeTex.Load("Resource/Texture/UI/frameR.png");
	m_lframeTex.Load("Resource/Texture/UI/frameL.png");
	m_HPTex.Load("Resource/Texture/UI/HP.png");
	m_HPbarTex.Load("Resource/Texture/UI/HPbar.png");
	m_HideTex.Load("Resource/Texture/UI/Hide.png");
	m_HidebarTex.Load("Resource/Texture/UI/Hidebar.png");
	m_katanaTex.Load("Resource/Texture/UI/Katana.png");
	m_shurikenTex.Load("Resource/Texture/UI/Shuriken.png");
	m_iconBombTex.Load("Resource/Texture/UI/Bomb.png");
	m_iconMinoTex.Load("Resource/Texture/UI/Hidemino.png");
	m_stackBombTex.Load("Resource/Texture/UI/bomb_icon.png");
	m_stackKeyTex.Load("Resource/Texture/UI/key.png");

	// エフェクト
	m_pSlashTex.Load("Resource/Texture/Effect/p_slash.png");
	m_eSlashTex.Load("Resource/Texture/Effect/e_slash.png");
	m_dmgTex.Load("Resource/Texture/Effect/dmg.png");
	m_darkenTex.Load("Resource/Texture/Effect/Dark.gif");
	m_HealTex.Load("Resource/Texture/Effect/heal.png");
	m_BlackTex.Load("Resource/Texture/Effect/black.png");

	// メッセージ
	m_msgTex.Load("Resource/Texture/Message/AOMessage.png");

	// リザルト
	m_resultTex.Load("Resource/Texture/Result/clear.png");

	// マウスカーソル
	m_mousePointTex.Load("Resource/Texture/Player/mousepoint.png");

	/*クラスごとの初期化*/
	// タイトル
	m_title.Init();
	m_title.SetTexTitle(&m_titleTex);
	m_title.SetTexLine(&m_lineTex);

	// ゲーム説明
	m_descript.Init();
	m_descript.SetTexDescript(&m_descriptTex);
	m_descript.SetTexLine(&m_lineTex);

	//マップ
	m_map.SetOwner(this);
	m_map.Init();
	m_map.SetTexture(&m_mapTex);

	//プレイヤー
	m_player.SetOwner(this);
	m_player.Init();
	m_player.SetTexture(&m_playerTex);
	m_player.SetBulletTexture(&m_bulletTex);
	m_player.SetSlashTexture(&m_pSlashTex);
	m_player.SetBombTexture(&m_bombTex);
	m_player.SetBlastTexture(&m_blastTex);

	//敵
	m_enemy.SetOwner(this);
	m_enemy.GetBossList()->SetOwner(this);
	m_enemy.Init();					// 敵：初期化
	m_enemy.SetTexture(&m_samuraiTex);		// 侍
	m_enemy.SetArcherTexture(&m_archerTex);	// 弓兵
	m_enemy.SetArrowTexture(&m_arrowTex);	// 矢
	m_enemy.SetGiantTexture(&m_GiantTex);	// 大男
	m_enemy.SetBossTexture(&m_bossTex);		// ボス
	m_enemy.SetSwordTexture(&m_eSlashTex);// 敵斬撃

	//アイテム
	m_item.SetOwner(this);
	m_item.Init();
	m_item.SetTexBomb_t(&m_ItemBombTex_t);
	m_item.SetTexBomb_f(&m_ItemBombTex_f);
	m_item.SetTexKey(&m_ItemKeyTex);
	m_item.SetTexHealth(&m_ItemHealthTex);
	m_item.SetTexMino(&m_ItemMinoTex);

	//UI
	m_ui.SetOwner(this);
	m_ui.Init();
	m_ui.SetbackTexture(&m_backTex);
	m_ui.SetrframeTexture(&m_rframeTex);
	m_ui.SetlframeTexture(&m_lframeTex);
	m_ui.SetHPTexture(&m_HPTex);
	m_ui.SetHPBarTexture(&m_HPbarTex);
	m_ui.SetHideTexture(&m_HideTex);
	m_ui.SetHideBarTexture(&m_HidebarTex);
	m_ui.SetIconKatanaTexture(&m_katanaTex);
	m_ui.SetIconShurikenTexture(&m_shurikenTex);
	m_ui.SetIconBombTexture(&m_iconBombTex);
	m_ui.SetIconMinoTexture(&m_iconMinoTex);
	m_ui.SetStackBombTexture(&m_stackBombTex);
	m_ui.SetStackKeyTexture(&m_stackKeyTex);

	// エフェクト
	m_effect.SetOwner(this);
	m_effect.Init();
	m_effect.SetDmgTexture(&m_dmgTex);
	m_effect.SetDarkTexture(&m_darkenTex);
	m_effect.SetHealTexture(&m_HealTex);
	m_effect.SetBlackTexture(&m_BlackTex);

	// メッセージ
	m_message.Init();
	m_message.SetTexture(&m_msgTex);

	// リザルト
	m_result.Init();
	m_result.SetTexResult(&m_resultTex);
	m_result.SetTexLine(&m_lineTex);

	//初期シーン　タイトル
	sceneType = eSceneTitle;

	blackcnt = 0;

	bgmflg = true;
	bossbgmflg = false;
	blackflg = true;

	bgmInst = Utility::Sound_Loading(bgm, "Resource/Sound/BGM.WAV");
	bgmInst->SetVolume(0.3);
	bgmInst->Play(true);

	bossbgmInst = Utility::Sound_Loading(bossbgm, "Resource/Sound/bossBGM.WAV");
	bossbgmInst->Play(true);
	bossbgmInst->Pause();
	gameoverseInst = Utility::Sound_Loading(gameoverse, "Resource/Sound/gameover.WAV");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												タイトル画面
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//タイトル:更新
void Scene::TitleUpdate()
{
	GetMousePos({ 0,0 });

	// 更新処理
	m_title.Update(m_mouse.cur);

	int trans = m_title.SceneTransition();
	switch (trans)
	{
	case 1: sceneType = eSceneGame;
		break;
	case 2:sceneType = eSceneDescription;
		break;
	default:
		break;
	}
}
//タイトル:描画
void Scene::TitleDraw()
{
	m_title.Draw();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												ゲーム画面
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ゲーム:更新
void Scene::GameUpdate()
{
	GetMousePos(m_map.GetscrollPos());

	//マップ切り替え時の処理
	if (m_map.GetMapSwitchFlg())
	{
		CDarken* darkenList = m_effect.GetDarkenList();
		darkenList->EmitDark();		// 暗転エフェクト

		//マップ情報の切り替え
		m_map.SetMapData();
		m_map.LoadMapFile();

		//チップ画像切り替え
		switch (m_map.GetMapData())
		{
		//城外
		case OutSide:
			m_mapTex.Load("Resource/Texture/Map/Map1.png");
			break;
		//一階層
		case OneFloor:
			m_mapTex.Load("Resource/Texture/Map/Map2.png");
			break;
		//二階層
		case TwoFloor:
			m_mapTex.Load("Resource/Texture/Map/Map3.png");
			break;
		//三階層
		case ThreeFloor:
			m_mapTex.Load("Resource/Texture/Map/Map4.png");
			break;
		//四階層
		case FourFloor:
			m_mapTex.Load("Resource/Texture/Map/Map5.png");
			break;
		//ボス階層
		case BossFloor:
			m_mapTex.Load("Resource/Texture/Map/Boss.png");
			break;
		}

		// プレイヤー再初期化
		m_player.ReInit(m_map.GetMapData());

		//アイテム再初期化
		m_item.Init();

		//敵クラス再初期化
		m_enemy.Init();

		m_map.SetMapSwitchFlg(false);	//切り替えフラグ下げ
	}

	m_map.Update();		//マップ
	m_enemy.Update();	//敵
	m_player.Updata(m_mouse.cur);	//プレイヤー
	m_item.Update();	//アイテム
	m_ui.Updata();		//UI
	m_effect.UpDate();	// エフェクト
	
	// メッセージ
	switch (m_message.GetMsgNum())	
	{
	case 0: m_msgTex.Load("Resource/Texture/Message/Attack description.png");
		break;
	case 1: m_msgTex.Load("Resource/Texture/Message/Weapon change description.png");
		break; 
	case 2: m_msgTex.Load("Resource/Texture/Message/Weapon description.png");
		break; 
	case 3: m_msgTex.Load("Resource/Texture/Message/Door description.png");
		break; 
	case 4: m_msgTex.Load("Resource/Texture/Message/minoMassage.png");
		break;
	case 5: m_msgTex.Load("Resource/Texture/Message/BombMassage.png");
		break;
	case 6: m_msgTex.Load("Resource/Texture/Message/lightbasketMessage.png");
		break;
	}
	m_message.SetScrollPos(m_map.GetscrollPos());
	m_message.Update();

	// リザルト移行
	if (m_player.GetHp() <= 0)
	{
		m_resultTex.Load("Resource/Texture/Result/GameOver.png");

		CBlack* blackList = m_effect.GetBlackList();
		blackList->EmitBlack();		//暗転エフェクト

		blackcnt++;
		if (blackcnt >= 60)
		{
			bgmInst->Stop();
			bossbgmInst->Stop();
			gameoverseInst->Play();
			sceneType = eSceneResult;
		}
	}
	else if (m_enemy.GetBossHp() <= 0)
	{
		sceneType = eSceneResult;
	}

	if (!bgmflg)
	{
		bgmInst->Stop();
		bgmflg = true;
	}
	if(bossbgmflg)
		bossbgmInst->Resume();
}

//ゲーム:描画
void Scene::GameDraw()
{
	//マップ
	m_map.Draw();

	//アイテム
	m_item.Draw();

	//敵
	m_enemy.Draw();
	
	//プレイヤー
	m_player.Draw();

	//UI
	m_ui.Draw();

	// エフェクト
	m_effect.Draw();

	// メッセージ
	m_message.Draw();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												操作説明画面
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//説明:更新
void Scene::DescriptUpdate()
{
	GetMousePos({ 0,0 });
	m_descript.Update(m_mouse.cur);
	// シーン遷移処理
	if (m_descript.SceneTransition())
	{
		sceneType = eSceneTitle;
	}
}
//説明:描画
void Scene::DescriptDraw()
{
	m_descript.Draw();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												リザルト画面
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// リザルト：更新
void Scene::ResultUpdate()
{
	GetMousePos({ 0,0 });
	m_result.Update(m_mouse.cur);
	// シーン遷移処理
	if (m_result.SceneTransition())
	{
		Reset();
		return;
	}
	bossbgmInst->Pause();
}

// リザルト：描画
void Scene::ResultDraw()
{
	m_result.Draw();
}

//マウス座標取得関数
void Scene::GetMousePos(Math::Vector2 scrPos)
{
	GetCursorPos(&m_mouse.cur);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mouse.cur);

	m_mouse.cur.x -= Screen::HalfWidth - scrPos.x;
	m_mouse.cur.y -= Screen::HalfHeight + scrPos.y;
	m_mouse.cur.y *= -1;
}

// マウスポイント描画
void Scene::MousePointDraw()
{
	GetMousePos({ 0,0 });
	Math::Matrix mat;
	int r = 32;
	mat = DirectX::XMMatrixTranslation(m_mouse.cur.x+ r/2, m_mouse.cur.y- r/2, 0);
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_mousePointTex, Math::Rectangle(0,0, r, r),1.0f);
}

void Scene::SetBGMFlg()
{
	bgmflg = false;
}

void Scene::SetbossBGMFlg()
{
	bossbgmflg = true;
}
