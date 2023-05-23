#pragma once

//画面情報
namespace Screen
{
	const int Width = 1280;				//画面幅
	const int Height = 720;				//画面高
	const int HalfWidth = Width / 2;	//画面幅半分
	const int HalfHeight = Height / 2;	//画面高半分

}

//キャラ情報
namespace Infor
{
	//半径情報
	const float RADIUS_32 = 32.0f;
	const float RADIUS_16 = 16.0f;
}

// パラメータ：体力
namespace HP
{
	const int PLAYER = 50;		// プレイヤー
	const int SAMURAI = 15;		// 侍
	const int ARCHER = 9;		// 弓兵
	const int GIANT = 30;		// 大男
	const int BOSS = 150;		// ボス
}

// パラメータ：攻撃力
namespace POWER
{
	// プレイヤー
	const int PLAYER_SHURIKEN = 2;	// 手裏剣
	const int PLAYER_SLASH = 9;		// 斬撃
	const int PLAYER_BLAST = 15;	// 爆風

	// 敵
	const int ENEMY_PHYSICAL = 5;
	// 侍
	const int SAMURAI_SLASH = 10;
	// 弓兵
	const int ARCHER_ARROW = 5;
	// 大男
	const int GIANT_RUSH = 10;
	// ボス
	const int BOSS_SLASH = 12;
	// トゲ
	const int THORNS = 5;
}

// パラメータ：スピード
namespace SPEED
{
	// プレイヤー
	const int PLAYER = 5;
	const int PLAYER_SHURIKEN = 15;

	// 侍
	const double SAMURAI = 2.1;
	// 弓兵
	const double ARCHER = 1.4;
	// 矢
	const int ARROW = 12;
	// 大男
	const double GIANT_NORMAL = 1.1;
	const int GIANT_RUSH = 6;
	// ボス
	const double BOSS = 1.3;
}

// パラメータ：クールタイム
namespace COOL_TIME
{
	// プレイヤー
	const int PLAYER_SLASH = 50;		// 斬撃
	const int PLAYER_SHURIKEN = 20;		// 手裏剣

	// 侍
	const int SAMURAI_SLASH = 300;
	// 弓兵
	const int ARCHER_ARROW = 60;
	// 大男
	const int GIANT_ATK = 80;
	// ボス
	const int BOSS_SLASH = 80;
	const int BOSS_ARROW = 120;

	// トゲ
	const int THORNS = 70;
}

// 距離
namespace DISTANCE
{
	const int SAMURAI_SLASH = 60;	// 侍と斬撃の距離
	const int BOSS_SLASH = 100;	// ボスと斬撃の距離
}

// プレイヤーサイズ
namespace PLAYER_SIZE
{
	const float LEFT = 32;
	const float RIGHT = 32;
	const float TOP = 32;
	const float DOWN = 32;
}

// 侍サイズ
namespace SAMURAI_SIZE
{
	const float LEFT = 20;
	const float RIGHT = 9;
	const float TOP = 32;
	const float DOWN = 32;
}
// 弓兵サイズ
namespace ARCHER_SIZE
{
	const float LEFT = 20;
	const float RIGHT = 9;
	const float TOP = 32;
	const float DOWN = 32;
}
// 大男サイズ
namespace GIANT_SIZE
{
	const float LEFT = 30;
	const float RIGHT = 30;
	const float TOP = 35;
	const float DOWN = 35;
}
// ボスサイズ
namespace BOSS_SIZE
{
	const float LEFT = 40 + 40 ;
	const float RIGHT = 73 - 40 ;
	const float TOP = 70;
	const float DOWN = 80;
}

// 手裏剣サイズ
namespace SHURIKEN_SIZE
{
	const float LEFT = 8;
	const float RIGHT = 8;
	const float TOP = 8;
	const float DOWN = 8;
}
// 斬撃サイズ
namespace SLASH_SIZE
{
	const float LEFT = 32;
	const float RIGHT = 32;
	const float TOP = 32;
	const float DOWN = 32;
}
// 爆風サイズ
namespace BLAST_SIZE
{
	const float LEFT = 48*1.5;
	const float RIGHT = 48 * 1.5;
	const float TOP = 48 * 1.5;
	const float DOWN = 48 * 1.5;
}
// 矢サイズ
namespace ARROW_SIZE
{
	const float LEFT = 16;
	const float RIGHT = 16;
	const float TOP = 16;
	const float DOWN = 16;
}

// アイテム：爆弾サイズ
namespace ITEM_BOMB_SIZE
{
	const float LEFT = 56;
	const float RIGHT = 40;
	const float TOP = 24;
	const float DOWN = 24;
}
// アイテム：鍵サイズ
namespace ITEM_KEY_SIZE
{
	const float LEFT = 16;
	const float RIGHT = 16;
	const float TOP = 16;
	const float DOWN = 16;
}
// アイテム：回復サイズ
namespace ITEM_HELSE_SIZE
{
	const float LEFT = 16;
	const float RIGHT = 16;
	const float TOP = 16;
	const float DOWN = 16;
}
// アイテム：隠れ蓑サイズ
namespace ITEM_HIDE_SIZE
{
	const float LEFT = 32;
	const float RIGHT = 32;
	const float TOP = 32;
	const float DOWN = 32;
}

//汎用処理欄
namespace Utility
{
	/*当たり判定処理*/
	//0か1を返還
	bool bHitCheck(Math::Vector2 aScrPos,Math::Vector2 aScrMove, Math::Vector2 aDestPos,				// キャラ１座標、キャラ１移動量、キャラ２座標、
					float aScrRad_Left,float aScrRad_Right , float aScrRad_Top, float aScrRad_Bottom ,  // キャラ１半径 左右上下
					float aDesRad_Left,float aDesRad_Right,float aDesRad_Top,float aDesRad_Bottom);		// キャラ２半径 上下左右

	//0または1～4を返還
	int  iHitCheck(Math::Vector2 aScrPos,Math::Vector2 aScrMove, float aDestPosX, float aDestPosY,			// キャラ１座標、キャラ１移動量、キャラ２座標、
					float aScrRad_Left, float aScrRad_Right, float aScrRad_Top, float aScrRad_Bottom,		// キャラ１半径 左右上下
					float aDesRad_Left, float aDesRad_Right, float aDesRad_Top, float aDesRad_Bottom);		// キャラ２半径 上下左右

	//2点間の角度を求める
	float GetAngleDeg(Math::Vector2 src, Math::Vector2 dest);	//見る元の座標,見る先の座標 
	
	//2点間の距離を求める
	float GetDistance(Math::Vector2 src, Math::Vector2 dest);	//見る元の座標,見る先の座標 

	//サウンド読み込み
	std::shared_ptr<KdSoundInstance> Sound_Loading(std::shared_ptr<KdSoundEffect> se, const std::string& seName);
}