#pragma once

//マップシーン
enum eMapData
{
	OutSide,	//城外
	OneFloor,	//1階層
	TwoFloor,	//2階層
	ThreeFloor,	//3階層
	FourFloor,	//4階層
	BossFloor	//ボス部屋
};

class Scene;

constexpr int MAP_CHIP_H = 40;					//縦サイズ
constexpr int MAP_CHIP_W = 40;					//横サイズ

class CMap
{
public:
	CMap();
	~CMap();

	void Init();
	void Update();
	void Draw();
	void SetTexture(KdTexture* apTexture);
	float (*GetPosX())[MAP_CHIP_W];		//X座標取得
	float (*GetPosY())[MAP_CHIP_W];		//Y座標取得
	int (*GetChipData())[MAP_CHIP_W];	//マップデータ取得
	Math::Vector2 GetscrollPos();		//スクロール量取得
	int GetMapData() { return m_mapData; }	//マップの場面情報取得
	bool GetMapSwitchFlg() { return m_bMapSwitch; }	//マップ切り替えフラグ取得
		
	void SetOwner(Scene* apOwner);		//オーナー設定
	void SetMapData();					//マップデータの変更
	void SetMapSwitchFlg(bool flg);		//マップ切り替えフラグ反転
	void SetUnlock();					//鍵開け
	void SetLock();						//カギ閉め

	void LoadMapFile();		//マップファイル読み込み

private:

	KdTexture*			m_pTexture;								//画像(テクスチャ)
	int					m_ChipData[MAP_CHIP_H][MAP_CHIP_W];		//マップデータ
	float				m_chipX[MAP_CHIP_H][MAP_CHIP_W];		//座標
	float				m_chipY[MAP_CHIP_H][MAP_CHIP_W];		//座標
	Math::Matrix		m_mat[MAP_CHIP_H][MAP_CHIP_W];			//行列
	Math::Vector2		m_scroll;								//スクロール量

	eMapData			m_mapData;			//マップ
	bool				m_bMapSwitch;		//マップ切り替えフラグ
	int gimmickcount;
	Scene* m_pOwner;		//オーナー取得用
	bool			    m_bGimmick;         //ギミックflg

	void Scroll();			//スクロール処理
	void ScrollRemit();		//画面端リミット
};
