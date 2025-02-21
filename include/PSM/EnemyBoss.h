#ifndef _PSM_ENEMYSPECIAL_H
#define _PSM_ENEMYSPECIAL_H

#include "PSM/EnemyBase.h"
#include "types.h"

namespace PSM {
/**
 * @size = 0x100
 */
struct EnemyBoss : public EnemyBase {
	EnemyBoss(Game::EnemyBase* gameObj);

	virtual ~EnemyBoss();                                            // _14 (weak)
	virtual CreatureCastType getCastType() { return CCT_EnemyBoss; } // _1C (weak)
	virtual void exec();                                             // _20
	virtual void onCalcOn();                                         // _28
	virtual bool judgeNearWithPlayer(const Vec&, const Vec&, f32,
	                                 f32);    // _34
	virtual void onPlayingSe(u32, JAISound*); // _38
	virtual void setKilled();                 // _C8
	virtual void jumpRequest(u16)     = 0;    // _D4
	virtual void postPikiAttack(bool) = 0;    // _D8
	virtual void updateDisappearing();        // _DC
	virtual void onDeathMotionTop();          // _E0
	virtual void onAppear() { }               // _E4 (weak)
	virtual void onAppear1st() { }            // _E8 (weak)
	virtual void onDisappear() { }            // _EC (weak)

	void calcDistance();
	void setAppearFlag(bool);
	void dyingFrameWork();
	bool isOnDisappearing();

	f32 mNaviDistance;        // _E0
	u16 mDisappearTimer;      // _E4
	u32 _E8;                  // _E8
	JSULink<EnemyBoss> mLink; // _EC
	bool mAppearFlag;         // _FC
	bool mIsFirstAppear;      // _FD
	u8 _FE;                   // _FE - unknown
	u8 mHasReset;             // _FF
};

/**
 * @size = 0x11C
 */
struct EnemyMidBoss : public EnemyBoss {
	EnemyMidBoss(Game::EnemyBase*);

	virtual ~EnemyMidBoss();                                            // _14 (weak)
	virtual CreatureCastType getCastType() { return CCT_EnemyMidBoss; } // _1C (weak)
	virtual void onCalcOn();                                            // _28
	virtual void jumpRequest(u16);                                      // _D4
	virtual void postPikiAttack(bool);                                  // _D8
	virtual void onAppear1st();                                         // _E8

	u32 mNumLinks;                 // _100
	f32 _104;                      // _104
	JSULink<PSM::EnemyBoss> mLink; // _108
	u8 _118;                       // _118
};

/**
 * @size = 0x11E
 */
struct EnemyBigBoss : public EnemyMidBoss {
	EnemyBigBoss(Game::EnemyBase*);

	virtual ~EnemyBigBoss();                                            // _14 (weak)
	virtual CreatureCastType getCastType() { return CCT_EnemyBigBoss; } // _1C (weak)
	virtual void jumpRequest(u16);                                      // _D4
	virtual void onDeathMotionTop();                                    // _E0
	virtual void onAppear1st();                                         // _E8

	u16 mCurrBgmState; // _11C

	static EnemyBigBoss* sBigBoss;
};

} // namespace PSM

#endif
