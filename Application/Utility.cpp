#include "Utility.h"

//四辺の当たり判定チェック
//当たったらtrueかfalseを返す
bool Utility::bHitCheck(Math::Vector2 aScrPos, Math::Vector2 aScrMove, Math::Vector2 aDestPos, 
	float aScrRad_Left, float aScrRad_Right, float aScrRad_Top, float aScrRad_Bottom,
	float aDesRad_Left, float aDesRad_Right, float aDesRad_Top, float aDesRad_Bottom)
{
	//キャラ1の現在座標の四辺
	const float aScrLeft = aScrPos.x - aScrRad_Left;		//左辺
	const float aScrRight = aScrPos.x + aScrRad_Right;		//右辺
	const float aScrTop = aScrPos.y + aScrRad_Top;			//上辺
	const float aScrBottom = aScrPos.y - aScrRad_Bottom;	//下辺

	//キャラ1の未来座標の四辺
	const float nextLeft = aScrLeft + aScrMove.x;				//左辺
	const float nextRight = aScrRight + aScrMove.x;			//右辺
	const float nextTop = aScrTop + aScrMove.y;				//上辺
	const float nextBottom = aScrBottom + aScrMove.y;			//下辺

	//キャラ2の現在座標の四辺
	const float aDestLeft = aDestPos.x - aDesRad_Left;	//左辺
	const float aDestRight = aDestPos.x + aDesRad_Right;	//右辺
	const float aDestTop = aDestPos.y + aDesRad_Top;	//上辺
	const float aDestBottom = aDestPos.y - aDesRad_Bottom;	//下辺

	/* 現在座標 :左右当たり判定*/
	if (aScrRight > aDestLeft && aScrLeft < aDestRight)
	{
		//未来座標 :上からあたったか判定
		if (nextBottom < aDestTop && nextTop > aDestTop)
		{
			return false;
		}
		//未来座標 :下からあたったか判定
		else if (nextTop > aDestBottom && nextBottom < aDestBottom)
		{
			return false;
		}
	}

	/* 現在座標 :上下当たり判定*/
	if (aScrTop > aDestBottom && aScrBottom < aDestTop)
	{
		//未来座標 :左からあたったか判定
		if (nextRight > aDestLeft && nextLeft < aDestLeft)
		{
			return false;
		}
		//未来座標 :右からあたったか判定
		else if (nextLeft < aDestRight && nextRight > aDestRight)
		{
			return false;
		}
	}
	return true;
}

//四辺の当たり判定を個々に判定
//1:上判定 2:下判定 3:右 4:左
int Utility::iHitCheck(Math::Vector2 aScrPos, Math::Vector2 aScrMove, float aDestPosX, float aDestPosY, float aScrRad_Left, float aScrRad_Right, float aScrRad_Top, float aScrRad_Bottom, float aDesRad_Left, float aDesRad_Right, float aDesRad_Top, float aDesRad_Bottom)
{
	//キャラ1の現在座標の四辺
	const float aScrLeft = aScrPos.x - aScrRad_Left;		//左辺
	const float aScrRight = aScrPos.x + aScrRad_Right;		//右辺
	const float aScrTop = aScrPos.y + aScrRad_Top;			//上辺
	const float aScrBottom = aScrPos.y - aScrRad_Bottom;	//下辺

	//キャラ1の未来座標の四辺
	const float nextLeft = aScrLeft + aScrMove.x;			//左辺
	const float nextRight = aScrRight + aScrMove.x;			//右辺
	const float nextTop = aScrTop + aScrMove.y;				//上辺
	const float nextBottom = aScrBottom + aScrMove.y;		//下辺

	//キャラ2の現在座標の四辺
	const float aDestLeft = aDestPosX - aDesRad_Left;		//左辺
	const float aDestRight = aDestPosX + aDesRad_Right;		//右辺
	const float aDestTop = aDestPosY + aDesRad_Top;			//上辺
	const float aDestBottom = aDestPosY - aDesRad_Bottom;	//下辺

	/* 現在座標 :左右当たり判定*/
	if (aScrRight > aDestLeft && aScrLeft < aDestRight)
	{
		//未来座標 :上からあたったか判定
		if (nextBottom < aDestTop && nextTop > aDestTop)
		{
			return 1;	//上に押し戻し
		}
		//未来座標 :下からあたったか判定
		else if (aScrTop > aDestBottom && aScrBottom < aDestBottom)
		{
			return 2;	//下に押し戻し
		}
	}

	/* 現在座標 :上下当たり判定*/
	if (aScrTop > aDestBottom && aScrBottom < aDestTop)
	{
		//未来座標 :左からあたったか判定
		if (nextRight > aDestLeft && nextLeft < aDestLeft)
		{
			return 3;	//左に押し戻し
		}
		//未来座標 :右からあたったか判定
		else if (nextLeft < aDestRight && nextRight > aDestRight)
		{
			return 4;	//右に押し戻し
		}
	}

	return 0;
}

//2点間の角度を求める
float Utility::GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)
{
	float a;	// 底辺
	float b;	// 高さ
	float rad;	// ラジアン
	float deg;	// デグリー

	//底辺と高さを求める
	a = dest.x - src.x;
	b = dest.y - src.y;

	// tanの逆関数で角度を求める  atan2(Y,X)引数の順番に注意
	rad = atan2f(b, a);

	//デグリーへ変換(計算式または関数利用)
	deg = DirectX::XMConvertToDegrees(rad);

	// 負の値の場合は正の値に補正
	if (deg < 0)
	{
		deg += 360;
	}

	//角度を返す
	return deg;
}

//2点間の距離を求める
float Utility::GetDistance(Math::Vector2 src, Math::Vector2 dest)
{
	float a, b, c;

	a = dest.x - src.x;			// 底辺を求める
	b = dest.y - src.y;			// 高さを求める
	c = sqrt(a * a + b * b);	// 斜辺を求める<-これが直線距離
	return c;
}

//サウンド読み込み
std::shared_ptr<KdSoundInstance> Utility::Sound_Loading(std::shared_ptr<KdSoundEffect> se, const std::string& seName)
{
	//①領域確保
	se = std::make_shared<KdSoundEffect>();
	//②音読み込み
	se->Load(seName);

	return se->CreateInstance(false);

}

