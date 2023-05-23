#pragma once

class Scene;

class CUI
{
public:
	CUI();
	~CUI();

	void Init();
	void Updata();
	void Draw();

	void SetOwner(Scene* apOwner);

	/*テクスチャ*/
	void SetbackTexture(KdTexture* apTexture);
	void SetrframeTexture(KdTexture* apTexture);
	void SetlframeTexture(KdTexture* apTexture);
	void SetHPTexture(KdTexture* apTexture);
	void SetHPBarTexture(KdTexture* apTexture);
	void SetHideTexture(KdTexture* apTexture);
	void SetHideBarTexture(KdTexture* apTexture);
	void SetIconKatanaTexture(KdTexture* apTexture);
	void SetIconShurikenTexture(KdTexture* apTexture);
	void SetIconBombTexture(KdTexture* apTexture);
	void SetIconMinoTexture(KdTexture* apTexture);
	void SetStackBombTexture(KdTexture* apTexture);
	void SetStackKeyTexture(KdTexture* apTexture);

private:
	KdTexture* m_pbackTexture;
	KdTexture* m_prframeTexture;
	KdTexture* m_plframeTexture;
	KdTexture* m_pHPTexture;
	KdTexture* m_pHPbarTexture;
	KdTexture* m_pHideTexture;
	KdTexture* m_pHidebarTexture;

	KdTexture* m_prweaponTexture;
	KdTexture* m_plweaponTexture;

	KdTexture* m_pIconKatanaTexture;
	KdTexture* m_pIconShurikenTexture;
	KdTexture* m_pIconBombTexture;
	KdTexture* m_pIconMinoTexture;

	KdTexture* m_pStackBombTexture;
	KdTexture* m_pStackKeyTexture;

	Math::Matrix m_backmat;
	Math::Matrix m_rframemat;
	Math::Matrix m_lframemat;
	Math::Matrix m_hpmat;
	Math::Matrix m_hpbarmat;
	Math::Matrix m_hidemat;
	Math::Matrix m_hidebarmat;
	Math::Matrix m_stackbombIconmat;
	Math::Matrix m_stackkeyIconmat;

	Math::Color hidebarcolor;

	int m_hp;//HP取得用
	int rightweapontype; //右手武器取得用
	int leftweapontype;	//左手武器取得用
	int m_bombstacks; //爆弾の所持数取得用
	int m_keystacks;  //鍵の所持数取得用
	int m_hidecount;  //隠れ蓑の使用可能時間取得用

	Scene* m_pOwner;			//オーナー取得用
};