#include"CMap.h"
#include"Scene.h"
#include"Utility.h"

CMap::CMap()
	:m_pTexture(nullptr)	//画像(テクスチャ)
	, m_ChipData()			//マップデータ
	, m_chipX()				//座標X
	, m_chipY()				//座標Y
	, m_mat()				//行列
	, m_scroll(0, 0)		//スクロール量
	, m_mapData(OutSide)
	, m_bMapSwitch(false)	//マップ切り替えフラグ
	, m_pOwner(nullptr)
	, m_bGimmick(false)
{
}

CMap::~CMap()
{
}

// 初期化
void CMap::Init()
{
	m_mapData = OutSide;
	m_bMapSwitch = false;
	m_bGimmick = false;
	//マップ情報ロード
	LoadMapFile();

	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			m_chipX[h][w] = (64.0f * w) - 640;
			m_chipY[h][w] = (-64.0f * h) + 360;
		}
	}
}

//更新
void CMap::Update()
{
	//マップ更新
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			//スクロール処理
			Scroll();

			//画面端のリミット定義
			ScrollRemit();
		}
	}

	// ギミック処理
	const int GMAX = COOL_TIME::THORNS;
	gimmickcount++;
	if (gimmickcount > GMAX)
	{
		gimmickcount = GMAX;
	}

	if (gimmickcount >= GMAX)
	{
		m_bGimmick = !m_bGimmick;

		gimmickcount = 0;
	}
	
	if (m_mapData == TwoFloor)
	{
		int i = 0;
		int j = 0;
		if (m_bGimmick == false)
		{
			i = 95;
			j = 101;
		}
		else
		{
			i = 101;
			j = 95;
		}

		m_ChipData[21][33] = i;
		m_ChipData[22][33] = i;
		m_ChipData[21][34] = i;
		m_ChipData[22][34] = i;
		m_ChipData[21][35] = i;
		m_ChipData[22][35] = i;
		m_ChipData[21][36] = i;
		m_ChipData[22][36] = i;
		m_ChipData[21][37] = i;
		m_ChipData[22][37] = i;
		m_ChipData[21][38] = i;
		m_ChipData[22][38] = i;

		m_ChipData[25][33] = j;
		m_ChipData[26][33] = j;
		m_ChipData[25][34] = j;
		m_ChipData[26][34] = j;
		m_ChipData[25][35] = j;
		m_ChipData[26][35] = j;
		m_ChipData[25][36] = j;
		m_ChipData[26][36] = j;
		m_ChipData[25][37] = j;
		m_ChipData[26][37] = j;
		m_ChipData[25][38] = j;
		m_ChipData[26][38] = j;

		m_ChipData[30][33] = i;
		m_ChipData[29][33] = i;
		m_ChipData[30][34] = i;
		m_ChipData[29][34] = i;
		m_ChipData[30][35] = i;
		m_ChipData[29][35] = i;
		m_ChipData[30][36] = i;
		m_ChipData[29][36] = i;
		m_ChipData[30][37] = i;
		m_ChipData[29][37] = i;
		m_ChipData[30][38] = i;
		m_ChipData[29][38] = i;

		m_ChipData[32][31] = j;
		m_ChipData[32][32] = j;
		m_ChipData[33][31] = j;
		m_ChipData[33][32] = j;
		m_ChipData[34][31] = j;
		m_ChipData[34][32] = j;
		m_ChipData[35][31] = j;
		m_ChipData[35][32] = j;
		m_ChipData[36][31] = j;
		m_ChipData[36][32] = j;
		m_ChipData[37][31] = j;
		m_ChipData[37][32] = j;

		m_ChipData[32][27] = i;
		m_ChipData[32][28] = i;
		m_ChipData[33][27] = i;
		m_ChipData[33][28] = i;
		m_ChipData[34][27] = i;
		m_ChipData[34][28] = i;
		m_ChipData[35][27] = i;
		m_ChipData[35][28] = i;
		m_ChipData[36][27] = i;
		m_ChipData[36][28] = i;
		m_ChipData[37][27] = i;
		m_ChipData[37][28] = i;
	}

	//行列作成
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			m_mat[h][w] = DirectX::XMMatrixTranslation(
				m_chipX[h][w] - m_scroll.x, m_chipY[h][w] - m_scroll.y, 0.0f);
		}
	}
}

//描画
void CMap::Draw()
{
	Math::Rectangle chipRect;

	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			if (m_ChipData[h][w] == 0)
			{
				chipRect = { 0,0,64,64 };
			}
			else if (m_ChipData[h][w] == 1)
			{
				chipRect = { 64,0,64,64 };
			}
			else if (m_ChipData[h][w] == 2)
			{
				chipRect = { 128,0,64,64 };
			}
			else if (m_ChipData[h][w] == 3)
			{
				chipRect = { 192,0,64,64 };
			}
			else if (m_ChipData[h][w] == 4)
			{
				chipRect = { 256,0,64,64 };
			}
			else if (m_ChipData[h][w] == 5)
			{
				chipRect = { 320,0,64,64 };
			}
			else if (m_ChipData[h][w] == 7)
			{
				chipRect = { 384,0,64,64 };
			}
			else if (m_ChipData[h][w] == 6)
			{
				chipRect = { 448 ,0,64,64 };
			}
			else if (m_ChipData[h][w] == 9)
			{
				chipRect = { 512 ,0,64,64 };
			}
			else if (m_ChipData[h][w] == 8)
			{
				chipRect = { 576,0,64,64 };
			}
			else if (m_ChipData[h][w] == 10)
			{
				chipRect = { 0 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 11)
			{
				chipRect = { 64,64,64,64 };
			}
			else if (m_ChipData[h][w] == 12)
			{
				chipRect = { 128,64,64,64 };
			}
			else if (m_ChipData[h][w] == 13)
			{
				chipRect = { 192,64,64,64 };
			}
			else if (m_ChipData[h][w] == 14)
			{
				chipRect = { 256,64,64,64 };
			}
			else if (m_ChipData[h][w] == 15)
			{
				chipRect = { 320,64,64,64 };
			}
			else if (m_ChipData[h][w] == 16)
			{
				chipRect = { 384,64,64,64 };
			}
			else if (m_ChipData[h][w] == 17)
			{
				chipRect = { 448 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 18)
			{
				chipRect = { 512 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 19)
			{
				chipRect = { 576,64,64,64 };
			}
			else if (m_ChipData[h][w] == 20)
			{
				chipRect = { 640 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 21)
			{
				chipRect = { 0 ,128,64,64 };
			}
			else if (m_ChipData[h][w] == 22)
			{
				chipRect = { 64,128,64,64 };
			}
			else if (m_ChipData[h][w] == 23)
			{
				chipRect = { 128,128,64,64 };
			}
			else if (m_ChipData[h][w] == 24)
			{
				chipRect = { 192,128,64,64 };
			}
			else if (m_ChipData[h][w] == 25)
			{
				chipRect = { 256,128,64,64 };
			}
			else if (m_ChipData[h][w] == 26)
			{
				chipRect = { 320,128,64,64 };
			}
			else if (m_ChipData[h][w] == 27)
			{
				chipRect = { 384,128,64,64 };
			}
			else if (m_ChipData[h][w] == 28)
			{
				chipRect = { 448 ,128,64,64 };
			}
			else if (m_ChipData[h][w] == 29)
			{
				chipRect = { 512 ,128,64,64 };
			}
			else if (m_ChipData[h][w] == 30)
			{
				chipRect = { 576,128,64,64 };
			}
			else if (m_ChipData[h][w] == 31)
			{
				chipRect = { 0 ,192,64,64 };
			}
			else if (m_ChipData[h][w] == 32)
			{
				chipRect = { 64,192,64,64 };
			}
			else if (m_ChipData[h][w] == 33)
			{
				chipRect = { 128,192,64,64 };
			}
			else if (m_ChipData[h][w] == 34)
			{
				chipRect = { 192,192,64,64 };
			}
			else if (m_ChipData[h][w] == 35)
			{
				chipRect = { 256,192,64,64 };
			}
			else if (m_ChipData[h][w] == 36)
			{
				chipRect = { 320,192,64,64 };
			}
			else if (m_ChipData[h][w] == 37)
			{
				chipRect = { 384,192,64,64 };
			}
			else if (m_ChipData[h][w] == 38)
			{
				chipRect = { 448 ,192,64,64 };
			}
			else if (m_ChipData[h][w] == 39)
			{
				chipRect = { 512 ,192,64,64 };
			}
			else if (m_ChipData[h][w] == 40)
			{
				chipRect = { 576,192,64,64 };
			}
			else if (m_ChipData[h][w] == 41)
			{
				chipRect = { 0 ,256,64,64 };
			}
			else if (m_ChipData[h][w] == 42)
			{
				chipRect = { 64,256,64,64 };
			}
			else if (m_ChipData[h][w] == 43)
			{
				chipRect = { 128,256,64,64 };
			}
			else if (m_ChipData[h][w] == 44)
			{
				chipRect = { 192,256,64,64 };
			}
			else if (m_ChipData[h][w] == 45)
			{
				chipRect = { 256,256,64,64 };
			}
			else if (m_ChipData[h][w] == 46)
			{
				chipRect = { 320,256,64,64 };
			}
			else if (m_ChipData[h][w] == 47)
			{
				chipRect = { 384,256,64,64 };
			}
			else if (m_ChipData[h][w] == 48)
			{
				chipRect = { 448 ,256,64,64 };
			}
			else if (m_ChipData[h][w] == 49)
			{
				chipRect = { 128,0,64,64 };
			}
			else if (m_ChipData[h][w] == 51)
			{
				chipRect = { 448 ,0,64,64 };
			}
			else if (m_ChipData[h][w] == 52)
			{
				chipRect = { 384,0,64,64 };
			}
			else if (m_ChipData[h][w] == 53)
			{
				chipRect = { 320,0,64,64 };
			}
			else if (m_ChipData[h][w] == 54)
			{
				chipRect = { 256,0,64,64 };
			}
			else if (m_ChipData[h][w] == 55)
			{
				chipRect = { 576,0,64,64 };
			}
			else if (m_ChipData[h][w] == 56)
			{
				chipRect = { 512 ,0,64,64 };
			}
			else if (m_ChipData[h][w] == 57)
			{
				chipRect = { 512 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 58)
			{
				chipRect = { 576,64,64,64 };
			}
			else if (m_ChipData[h][w] == 60)
			{
				chipRect = { 0 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 61)
			{
				chipRect = { 0 ,256,64,64 };
			}
			else if (m_ChipData[h][w] == 62)
			{
				chipRect = { 128,256,64,64 };
			}
			else if (m_ChipData[h][w] == 63)
			{
			    chipRect = { 64,256,64,64 };
			}
			else if (m_ChipData[h][w] == 64)
			{
			    chipRect = { 576,128,64,64 };
			}
			else if (m_ChipData[h][w] == 65)
			{
				chipRect = { 512 ,128,64,64 };
			}
			else if (m_ChipData[h][w] == 66)
			{
			    chipRect = { 512 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 70)
			{
				chipRect = { 64,64,64,64 };
			}
			else if (m_ChipData[h][w] == 78)
			{
				if (m_mapData == BossFloor)
				{
					chipRect = { 192,64,64,64 };
				}
				else chipRect = { 256,64,64,64 };
			}
			else if (m_ChipData[h][w] == 79)
			{
				if (m_mapData == BossFloor)
				{
					chipRect = { 256,64,64,64 };
				}
				else chipRect = { 320,64,64,64 };
			}
			else if (m_ChipData[h][w] >= 80 && m_ChipData[h][w] <= 83)
			{
				chipRect = { 0 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 91)
			{
				chipRect = { 0,128,64,64 };
			}
			else if (m_ChipData[h][w] == 90)
			{
				chipRect = { 64,128,64,64 };
			}
			else if (m_ChipData[h][w] == 95)
			{
			    chipRect = { 128,128,64,64 };
			}
			else if (m_ChipData[h][w] == 96)
			{
			    chipRect = { 320,128,64,64 };
			}
			else if (m_ChipData[h][w] == 97)
			{
			    chipRect = { 384,128,64,64 };
			}
			else if (m_ChipData[h][w] == 101)
			{
			    chipRect = { 192,128,64,64 };
			}
			else if (m_ChipData[h][w] == 111)
			{
			    chipRect = { 256,64,64,64 };
			}
			else if (m_ChipData[h][w] == 112)
			{
			    chipRect = { 320,64,64,64 };
			}
			else if (m_ChipData[h][w] == 113)
			{
			    chipRect = { 384,64,64,64 };
			}
			else if (m_ChipData[h][w] == 114)
			{
			    chipRect = { 448 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 115)
			{
			    chipRect = { 64,128,64,64 };
			}
			else if (m_ChipData[h][w] == 116)
			{
			    chipRect = { 256,192,64,64 };
			}
			else if (m_ChipData[h][w] == 117)
			{
			    chipRect = { 320,192,64,64 };
			}
			else if (m_ChipData[h][w] == 118)
			{
			    chipRect = { 320,256,64,64 };
			}
			else if (m_ChipData[h][w] == 119)
			{
			    chipRect = { 128,192,64,64 };
			}

			SHADER.m_spriteShader.SetMatrix(m_mat[h][w]);
			SHADER.m_spriteShader.DrawTex(m_pTexture, chipRect, 1.0f);

		}
	}
}

//テクスチャ設定
void CMap::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pTexture = apTexture;
}

//マップX座標取得
float(*CMap::GetPosX())[MAP_CHIP_W]
{
	return m_chipX;
}

//マップY座標取得
float(*CMap::GetPosY())[MAP_CHIP_W]
{
	return m_chipY;
}

//マップデータ取得
int(*CMap::GetChipData())[MAP_CHIP_W]
{
	return m_ChipData;
}

//スクロール量取得
Math::Vector2 CMap::GetscrollPos()
{
	return m_scroll;
}

//オーナー設定
void CMap::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

//マップデータの変更
void CMap::SetMapData()
{
	switch (m_mapData)
	{
	case OutSide:
		m_mapData = OneFloor;
		break;
	case OneFloor:
		m_mapData = TwoFloor;
		break;
	case TwoFloor:
		m_mapData = ThreeFloor;
		break;
	case ThreeFloor:
		m_mapData = FourFloor;
		break;
	case FourFloor:
		m_mapData = BossFloor;
		break;
	}

}

//マップ切り替えフラグ反転
void CMap::SetMapSwitchFlg(bool flg)
{
	m_bMapSwitch = flg;
}

//鍵開け処理
void CMap::SetUnlock()
{
	const int ch = 10;
	switch (m_mapData)
	{
	case OneFloor:
		m_ChipData[19][21] = ch;
		m_ChipData[19][22] = ch;
		m_ChipData[20][21] = ch;
		m_ChipData[20][22] = ch;
		m_ChipData[5][1] = ch;
		m_ChipData[5][2] = ch;
		m_ChipData[6][1] = ch;
		m_ChipData[6][2] = ch;
		break;
	case TwoFloor:
		m_ChipData[34][1] = 19;
		m_ChipData[34][2] = 19;
		m_ChipData[35][1] = 19;
		m_ChipData[35][2] = 19;
		break;
	case ThreeFloor:
		m_ChipData[11][3] = ch;
		m_ChipData[12][3] = ch;
		m_ChipData[11][4] = ch;
		m_ChipData[12][4] = ch;
		break;
	}
}

// カギ閉め処理
void CMap::SetLock()
{
	const int ch = 49;
	switch (m_mapData)
	{
	case OutSide:
		break;
	case OneFloor:
		m_ChipData[19][21] = 51;
		m_ChipData[19][22] = 52;
		m_ChipData[20][21] = 53;
		m_ChipData[20][22] = 54;
		m_ChipData[5][1] = 51;
		m_ChipData[5][2] = 52;
		m_ChipData[6][1] = 53;
		m_ChipData[6][2] = 54;
		break;
	case TwoFloor:
		m_ChipData[11][3] = 55;
		m_ChipData[12][3] = 51;
		m_ChipData[11][4] = 56;
		m_ChipData[12][4] = 52;
		break;
	case BossFloor:
		m_ChipData[13][18] = 18;
		m_ChipData[14][18] = 16;
		m_ChipData[13][19] = 19;
		m_ChipData[14][19] = 17;
		m_ChipData[13][20] = 18;
		m_ChipData[14][20] = 16;
		m_ChipData[13][21] = 19;
		m_ChipData[14][21] = 17;

		break;
	default:
		break;
	}
}

//スクロール処理
void CMap::Scroll()
{
	//プレイヤー座標取得
	CPlayer* player = m_pOwner->GetPlayer();
	Math::Vector2 playerPos = player->GetPos();

	//スクロール座標
	m_scroll = playerPos;
}

//画面端リミット定義
void CMap::ScrollRemit()
{
	if (m_mapData == BossFloor)
	{
		static const float SCR_X_MIN = m_chipX[1][6] + Screen::HalfWidth;
		static const float SCR_X_MAX = m_chipX[1][32] - Screen::HalfWidth;
		static const float SCR_Y_MIN = m_chipY[31][1] + Screen::HalfHeight;
		static const float SCR_Y_MAX = m_chipY[1][1] - Screen::HalfHeight;

		//左端判定
		if (m_scroll.x < SCR_X_MIN)	 m_scroll.x = SCR_X_MIN;  //端に到達時固定
		//右端判定
		else if (m_scroll.x > SCR_X_MAX)	m_scroll.x = SCR_X_MAX; //端に到達時固定
		//下端判定
		if (m_scroll.y < SCR_Y_MIN)		m_scroll.y = SCR_Y_MIN; //端に到達時固定
		//上端判定
		else if (m_scroll.y > SCR_Y_MAX)	m_scroll.y = SCR_Y_MAX; //端に到達時固定
	}
	else
	{
		static const float SCR_X_MIN = m_chipX[0][0] + Screen::HalfWidth;
		static const float SCR_X_MAX = m_chipX[0][MAP_CHIP_W - 1] - Screen::HalfWidth;
		static const float SCR_Y_MIN = m_chipY[MAP_CHIP_H - 1][0] + Screen::HalfHeight;
		static const float SCR_Y_MAX = m_chipY[0][0] - Screen::HalfHeight;

		//左端判定
		if (m_scroll.x < SCR_X_MIN)	 m_scroll.x = SCR_X_MIN;  //端に到達時固定
		//右端判定
		else if (m_scroll.x > SCR_X_MAX)	m_scroll.x = SCR_X_MAX; //端に到達時固定
		//下端判定
		if (m_scroll.y < SCR_Y_MIN)		m_scroll.y = SCR_Y_MIN; //端に到達時固定
		//上端判定
		else if (m_scroll.y > SCR_Y_MAX)	m_scroll.y = SCR_Y_MAX; //端に到達時固定
	}
}

//マップ読み込み
void CMap::LoadMapFile()
{
	FILE* fp; // ファイルの情報を格納する構造体

	// ファイル読み込み
	switch (m_mapData)
	{
	case OutSide:
		fp = fopen("Resource/MapData/Map1.csv", "r");
		break;
	case OneFloor:
		fp = fopen("Resource/MapData/Map2.csv", "r");
		break;
	case TwoFloor:
		fp = fopen("Resource/MapData/Map3.csv", "r");
		break;
	case ThreeFloor:
		fp = fopen("Resource/MapData/Map4.csv", "r");
		break;
	case FourFloor:
		fp = fopen("Resource/MapData/Map5.csv", "r");
		break;
	case BossFloor:
		fp = fopen("Resource/MapData/Boss.csv", "r");
		break;
	default:
		break;
	}

	if (fp != nullptr)
	{
		for (int h = 0; h < MAP_CHIP_H; h++)
		{
			for (int w = 0; w < MAP_CHIP_W; w++)
			{
				fscanf(fp, "%d,", &m_ChipData[h][w]);
			}
		}
		fclose(fp);
	}
}
