#ifndef _GAME_CAVE_INFO_H
#define _GAME_CAVE_INFO_H

#include "CNode.h"
#include "Game/enemyInfo.h"
#include "BaseParm.h"
#include "stream.h"
#include "Graphics.h"
#include "Matrixf.h"
#include "Vector3.h"
#include "types.h"
#include "Game/pelletMgr.h"

namespace Game {
namespace Cave {

enum EnemyDropMode {
	DROP_NoDrop         = 0,
	DROP_PikminOrLeader = 1,
	DROP_Pikmin         = 2,
	DROP_Leader         = 3,
	DROP_CarryPikmin    = 4,
	DROP_Earthquake     = 5,
};

/**
 * @size{0x38}
 */
struct BaseGen : public CNode {
	/**
	 * Spawn type used by BaseGen (caves).
	 * UNUSED_3 is player 1 spawn in vs mode? (see
	 * Game::Cave::RandMapMgr::getStartPosition)
	 */
	enum CaveGenType {
		CGT_EnemyEasy = 0, // AKA TekiA / Easy Teki
		CGT_EnemyHard,     // AKA TekiB / Hard Teki
		CGT_TreasureItem,
		CGT_Unknown3,
		CGT_HoleOrGeyser,
		CGT_DoorSeam,
		CGT_Plant,
		CGT_Start,
		CGT_EnemySpecial, // AKA TekiF / Special Teki, contribute 0 to score, spawn individually
		CGT_Alcove
	};

	BaseGen();

	virtual ~BaseGen() { }                              // _08 (weak)
	virtual void read(Stream& input);                   // _10
	virtual void draw(Graphics& gfx, Matrixf* drawMtx); // _14

	// _00     = VTBL
	// _00-_18 = CNode
	CaveGenType mSpawnType; // _18
	Vector3f mPosition;     // _1C
	f32 mAngle;             // _28
	f32 mRadius;            // _2C
	int mMinimum;           // _30
	int mMaximum;           // _34
};

/**
 * @size{0x28}
 */
struct TekiInfo : public CNode {
	inline TekiInfo()
	{
		mEnemyID  = EnemyTypeID::EnemyID_Pelplant;
		mWeight   = 1;
		mType     = BaseGen::CGT_EnemyEasy;
		mDropMode = DROP_NoDrop;
	}

	virtual ~TekiInfo() { }           // _08 (weak)
	virtual void read(Stream& input); // _10

	// _00     = VTBL
	// _00-_18 = CNode
	EnemyTypeID::EEnemyTypeID mEnemyID; // _18
	int mWeight;                        // _1C
	BaseGen::CaveGenType mType;         // _20
	u8 mDropMode;                       // _24
	u8 : 0;
	Game::PelletMgr::OtakaraItemCode mOtakaraItemCode; // _26
};

/**
 * @size{0x20}
 */
struct ItemInfo : public CNode {
	inline ItemInfo()
	    : CNode()
	    , mCaveID(0)
	    , mWeight(1)
	{
	}

	virtual ~ItemInfo() { }           // _08 (weak)
	virtual void read(Stream& input); // _10

	// _00     = VTBL
	// _00-_18 = CNode
	int mCaveID; // _18
	int mWeight; // _1C
};

/**
 * @size{0x24}
 */
struct GateInfo : public CNode {
	inline GateInfo()
	    : CNode()
	    , mCaveID(0)
	{
		mWeight = 1;
		mLife   = 0.0f;
	}

	virtual ~GateInfo() { }           // _08 (weak)
	virtual void read(Stream& input); // _10

	// _00     = VTBL
	// _00-_18 = CNode
	int mCaveID; // _18
	f32 mLife;   // _1C
	int mWeight; // _20
};

/**
 * @size{0x20}
 */
struct CapInfo : public CNode {
	inline CapInfo()
	    : CNode()
	    , mIsTekiEmpty(1)
	    , mTekiInfo(nullptr)
	{
	}

	virtual ~CapInfo() { }            // _08 (weak)
	virtual void read(Stream& input); // _10

	TekiInfo* getTekiInfo();

	// _00     = VTBL
	// _00-_18 = CNode
	u8 mIsTekiEmpty;     // _18, AKA does not have a teki
	TekiInfo* mTekiInfo; // _1C
};

/**
 * @size{0x388}
 */
struct FloorInfo : public CNode {
	struct Parms : Parameters {
		Parms();

		Parm<int> mFloorIndex1;       // _00C  /* f000 */
		Parm<int> mFloorIndex2;       // _034  /* f001 */
		Parm<int> mTekiMax;           // _05C  /* f002 */
		Parm<int> mItemMax;           // _084  /* f003 */
		Parm<int> mGateMax;           // _0AC  /* f004 */
		Parm<int> mCapMax;            // _0D4  /* f014 */
		Parm<int> mRoomCount;         // _0FC  /* f005 */
		Parm<f32> mRouteRatio;        // _124  /* f006 */
		Parm<int> mHasEscapeFountain; // _14C  /* f007 */
		ParmString mCaveUnitFile;     // _174  /* f008 */
		ParmString mLightingFile;     // _194  /* f009 */
		ParmString mVrBox;            // _1B4  /* f00A */
		Parm<int> mIsHoleClogged;     // _1D4  /* f010 */
		ParmEnum mFloorAlphaType;     // _1FC  /* f011 */

		ParmEnum mFloorBetaType; // _220  /* f012 */

		ParmEnum mFloorHidden; // _244  /* f013 */

		Parm<int> mVersion;          // _268  /* f015 */
		Parm<f32> mWaterwraithTimer; // _290  /* f016 */
		Parm<int> mGlitchySeesaw;    // _2B8  /* f017 */

		// void* mEnd;                  // _2E0
	};

	FloorInfo();

	virtual ~FloorInfo() {};          // _08 (weak)
	virtual void read(Stream& input); // _10

	int getTekiMax();
	int getTekiInfoNum();
	TekiInfo* getTekiInfo(int idx);
	int getTekiWeightSum();

	int getItemMax();
	int getItemInfoNum();
	ItemInfo* getItemInfo(int idx);
	int getItemWeightSum();

	int getGateMax();
	int getGateInfoNum();
	GateInfo* getGateInfo(int idx);
	int getGateWeightSum();

	int getCapMax();
	int getCapInfoNum();
	CapInfo* getCapInfo(int idx);

	int getRoomNum();
	f32 getRouteRatio();
	bool hasEscapeFountain(int floorIndex);
	bool hasHiddenCollision();
	bool useKaidanBarrel();

	// _00     = VTBL
	// _00-_18 = CNode
	Parms mParms;       // _018
	TekiInfo mTekiInfo; // _2FC
	ItemInfo mItemInfo; // _324
	GateInfo mGateInfo; // _344
	CapInfo mCapInfo;   // _368
};

/**
 * @size{0x3D8}
 */
struct CaveInfo : public CNode {
	/* Erased? */
	struct Parms : Parameters {
		inline Parms()
		    : Parameters(nullptr, "CaveInfo")
		    , mFloorMax(this, 'c000', "�K�w", 1, 1, 128)
		{
		}

		Parm<int> mFloorMax; // _0C
	};

	CaveInfo();

	virtual ~CaveInfo() {};           // _08 (weak)
	virtual void read(Stream& input); // _10

	void disablePelplant();
	int getFloorMax();
	FloorInfo* getFloorInfo(int floorIndex);
	static CaveInfo* load(char* path);

	// _00     = VTBL
	// _00-_18 = CNode
	Parms mParms;         // _18
	FloorInfo mFloorInfo; // _50
};
} // namespace Cave
} // namespace Game

#endif
