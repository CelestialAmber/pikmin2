#ifndef _PIKIAI_H
#define _PIKIAI_H

#include "types.h"
#include "Vector3.h"
#include "SysShape/MotionListener.h"
#include "Condition.h"
#include "CollInfo.h"
#include "Game/pelletMgr.h"
#include "Game/SlotChangeListener.h"
#include "Sys/Sphere.h"

namespace Sys {
struct Triangle;
} // namespace Sys

namespace SysShape {
struct KeyEvent;
} // namespace SysShape

namespace Game {
struct Piki;
struct CollEvent;
struct Onyon;
struct PlatEvent;
struct Pellet;
struct PathNode;
struct WayPoint;
struct Creature;
struct ItemGate;
struct BaseItem;
struct Navi;
struct CPlate;
struct BaseFlockMgr;
struct EnemyBase;
struct Footmark;

namespace ItemRock {
struct Item;
} // namespace ItemRock

namespace ItemBridge {
struct Item;
} // namespace ItemBridge

namespace ItemWeed {
struct Item;
} // namespace ItemWeed
} // namespace Game

struct Graphics;

struct FindCondition : public Condition<CollPart> {
	virtual bool satisfy(CollPart* part) // _08 (weak)
	{
		bool result = false;
		if (part->mChild == nullptr && part->mCurrentID.match('****', '*')) {
			result = true;
		}

		return result;
	}
};

struct SlotHandles {
	inline SlotHandles() { _08 = 0; }

	u16 _00[4]; // _00
	s16 _08;    // _08
};

namespace PikiAI {
struct ActAttack;
struct ActBattle;
struct ActBore;
struct ActBreakGate;
struct ActBreakRock;
struct ActBridge;
struct ActClimb;
struct ActCrop;
struct ActEnter;
struct ActExit;
struct ActFlockAttack;
struct ActFollowVectorField;
struct ActFormation;
struct ActFree;
struct ActGather;
struct ActGotoPos;
struct ActGotoSlot;
struct ActOneshot;
struct ActPathMove;
struct ActRescue;
struct ActRest;
struct ActStickAttack;
struct ActTeki;
struct ActTransport;
struct ActWeed;

enum PikiBrainAction {
	ACT_NULL      = -1,
	ACT_Formation = 0,
	ACT_Free      = 1,
	ACT_Enter     = 2,
	ACT_Exit      = 3,
	ACT_Transport = 4,
	ACT_Attack    = 5,
	ACT_BreakGate = 6,
	ACT_BreakRock = 7,
	ACT_Crop      = 8,
	ACT_Weed      = 9,
	ACT_Bridge    = 10,
	ACT_Teki      = 11,
	ACT_Rescue    = 12,
	ACT_Battle    = 13,
	ACT_ActionCount, // total number of actions
};

enum ActionExitCode {
	ACTEXEC_Success  = 0, // action is finished and completed successfully
	ACTEXEC_Continue = 1, // action is unfinshed
	ACTEXEC_Fail     = 2, // action is finished and failed
};

struct ActionArg {
	inline ActionArg() { }

	virtual char* getName() // _08 (weak)
	{
		return "ActionArg";
	}

	// _00 = VTBL
};

struct CreatureActionArg : public ActionArg {
	inline CreatureActionArg(Game::Creature* creature)
	    : mCreature(creature)
	{
	}

	virtual char* getName() // _08 (weak)
	{
		return "CreatureActionArg";
	}

	// _00 VTBL
	Game::Creature* mCreature; // _04
};

struct Action {
	Action(Game::Piki* piki);

	virtual void init(ActionArg* settings) { }                                // _08 (weak)
	virtual int exec() { return ACTEXEC_Continue; }                           // _0C (weak)
	virtual void cleanup() { }                                                // _10 (weak)
	virtual void emotion_success() { }                                        // _14 (weak)
	virtual void emotion_fail() { }                                           // _18 (weak)
	virtual bool applicable() { return true; }                                // _1C (weak)
	virtual u32 getNextAIType() { return ACT_Formation; }                     // _20 (weak)
	virtual void bounceCallback(Game::Piki* p, Sys::Triangle* hit) { }        // _24 (weak)
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event) { } // _28 (weak)
	virtual void platCallback(Game::Piki* p, Game::PlatEvent& event) { }      // _2C (weak)
	virtual void doDirectDraw(Graphics& gfx) { }                              // _30 (weak)
	virtual void wallCallback(Vector3f& pos) { }                              // _34 (weak)

	/// @brief Gets information about the action (usually name)
	/// @param Destination string
	virtual void getInfo(char* dest); // _38,

	inline bool checkArg(ActionArg* settings, const char* typeName)
	{
		return (settings != nullptr && (strcmp(typeName, settings->getName()) == 0));
	}

	inline bool checkName(ActionArg* settings, const char* typeName) { return strcmp(typeName, settings->getName()) != 0; }

	// _00 = VTBL
	Game::Piki* mParent; // _04
	char* mName;         // _08
};

struct ApproachPosActionArg : public ActionArg {
	// why is this ctor so annoying
	inline ApproachPosActionArg(Vector3f& pos, const f32 radius, f32 timeLimit)
	    : mGoalPosition(pos)
	    , mRadius(radius)
	{
		mTimeOutLimit   = timeLimit;
		mIsElasticSpeed = false;
		mIsCheck3D      = false;
	}

	virtual char* getName() { return "ApproachPosActionArg"; } // _08 (weak)

	// _00 = VTBL
	Vector3f mGoalPosition; // _04
	f32 mRadius;            // _10
	f32 mTimeOutLimit;      // _14, how long to retry before timing out (-1 = don't time out, keep retrying)
	bool mIsElasticSpeed;   // _18, speed up more if we're far away
	bool mIsCheck3D;        // _19, check height as well as 2D dist/angle
};

struct ActApproachPos : public Action {
	ActApproachPos(Game::Piki* p);

	virtual void init(ActionArg* settings); // _08
	virtual int exec();                     // _0C
	virtual void cleanup();                 // _10

	// _00     = VTBL
	// _00-_0C = Action
	f32 mRadius;            // _0C
	Vector3f mGoalPosition; // _10
	f32 mTimeOutLimit;      // _1C, how long to retry before timing out (-1 = don't time out, keep retrying)
	f32 mTimer;             // _20, timer, piki 'times out' of action once timer hits _1C (if _1C > 0)
	bool mIsElasticSpeed;   // _24, speed up more if we're far away
	bool mIsCheck3D;        // _25, check if 'close enough' vertically as well
};

struct ActAttackArg : public ActionArg {
	virtual char* getName() { return "ActAttackArg"; } // _08 (weak)

	// _00 = VTBL
	Game::Creature* mCreature; // _04
	CollPart* mCollPart;       // _08
};

struct ActAttack : public Action, virtual SysShape::MotionListener {
	enum AttackID {
		ATTACK_Stick      = 0,
		ATTACK_Adjust     = 1,
		ATTACK_JumpAdjust = 2,
		ATTACK_Jump       = 3,
		ATTACK_Search     = 4, // pikis have no object permanence
	};

	ActAttack(Game::Piki* p);

	virtual void init(ActionArg* settings);                                // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual void emotion_success();                                        // _14
	virtual bool applicable();                                             // _1C
	virtual u32 getNextAIType() { return ACT_Free; }                       // _20 (weak)
	virtual void bounceCallback(Game::Piki* p, Sys::Triangle* hit);        // _24
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void getInfo(char*);                                           // _38
	virtual void onKeyEvent(const SysShape::KeyEvent& event);              // _3C (weak)

	void initStickAttack();
	void initAdjust();
	void initJump();
	void initJumpAdjust();
	void calcAttackPos();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::Creature* mCreature;    // _10
	CollPart* mCollPart;          // _14
	u16 mAttackID;                // _18, see AttackID enum
	ActStickAttack* mStickAttack; // _1C
	ActApproachPos* mApproachPos; // _20
	Sys::Sphere mAttackSphere;    // _24
	s16 mSearchAnimIdx;           // _34, either SAGASU or SAGASU2, 50% chance of either
	bool mIsSearchAnimFinished;   // _36
	                              // _38 = MotionListener
};

struct ActBattleArg : public ActionArg {
	virtual char* getName() { return "ActBattleArg"; } // _08 (weak)

	inline ActBattleArg(Game::Piki* piki) { mAggressor = piki; }

	inline ActBattleArg(Game::Piki* piki, bool start)
	{
		mAggressor     = piki;
		mIsAttackStart = start;
	}

	// _00 = VTBL
	Game::Piki* mAggressor; // _04
	bool mIsAttackStart;    // _08
};

#define PIKIAI_ACTBATTLE_APPROACH (0)
#define PIKIAI_ACTBATTLE_BATTLE   (1)
#define PIKIAI_ACTBATTLE_DAMAGE   (2)

// Pikmin hitting eachother, like in VS mode
struct ActBattle : public Action, virtual SysShape::MotionListener {
	ActBattle(Game::Piki* p);

	virtual void init(ActionArg* settings);                                // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual void emotion_success();                                        // _14
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void onKeyEvent(const SysShape::KeyEvent& event);              // _3C (weak)

	void initApproach();
	int execApproach();
	void initBattle();
	int execBattle();
	int execDamage();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::Piki* mOther;           // _10, vs battle piki attack
	u8 mState;                    // _14
	ActApproachPos* mApproachPos; // _18
	s8 _1C;                       // _1C
	s8 _1D;                       // _1D
};

struct ActBoreBase : public Action, virtual SysShape::MotionListener {
	ActBoreBase(Game::Piki* piki)
	    : Action(piki)
	{
	}

	virtual void finish()                                    = 0; // _3C
	virtual void onKeyEvent(const SysShape::KeyEvent& event) = 0; // _40

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
};

struct ActBore : public Action {
	ActBore(Game::Piki* p);

	virtual void init(ActionArg* settings); // _08
	virtual int exec();                     // _0C
	virtual void cleanup();                 // _10

	void startCurrAction();
	void finish();

	inline void setFlag(u32 flag) { mFlag.typeView |= flag; }
	inline void resetFlag(u32 flag) { mFlag.typeView &= ~flag; }
	inline bool isFlag(u32 flag) const { return mFlag.typeView & flag; }

	// _00     = VTBL
	// _00-_0C = Action
	u8 mRandBehaviorType;     // _0C
	f32 _10;                  // _10
	f32 mTimer;               // _14
	BitFlag<u8> mFlag;        // _18
	ActBoreBase* mActions[2]; // _1C
};

struct ActBreakGateArg : public ActionArg {
	virtual char* getName() { return "ActBreakGateArg"; } // _08 (weak)

	// _00 = VTBL
	Game::ItemGate* mGate; // _04
};

struct ActBreakGate : public Action, virtual SysShape::MotionListener {
	ActBreakGate(Game::Piki* p);

	virtual void init(ActionArg* settings);                                // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual void emotion_success();                                        // _14
	virtual void bounceCallback(Game::Piki* p, Sys::Triangle* hit);        // _24
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void platCallback(Game::Piki* p, Game::PlatEvent& event);      // _2C
	virtual void onKeyEvent(const SysShape::KeyEvent& event);              // _3C

	void initFollow();
	void initStickAttack();
	void initGoto();
	void calcAttackPos();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::ItemGate* mGate;              // _10
	u16 mState;                         // _14
	ActStickAttack* mStickAttack;       // _18
	ActGotoPos* mGotoPos;               // _1C
	ActFollowVectorField* mFollowField; // _20
	u8 _24;                             // _24
	u8 _25[0x3];                        // _25, unknown/probably padding
	u8 _28[0xC];                        // _28, unknown
	                                    // _34 = MotionListener
};

struct ActBreakRockArg : public ActionArg {
	virtual char* getName() { return "ActBreakRockArg"; } // _08 (weak)

	// _00 = VTBL
	Game::BaseItem* mRock; // _04
};

struct ActBreakRock : public Action, public virtual SysShape::MotionListener {
	ActBreakRock(Game::Piki* p);

	virtual void init(ActionArg* settings);                                // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual void bounceCallback(Game::Piki* p, Sys::Triangle* hit);        // _24
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void platCallback(Game::Piki* p, Game::PlatEvent& event);      // _2C
	virtual void onKeyEvent(const SysShape::KeyEvent& event) { }           // _3C

	void initFollow();
	void initStickAttack();
	void initGoto();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::BaseItem* mRock;              // _10
	u16 mState;                         // _14
	ActStickAttack* mStickAttack;       // _18
	ActGotoPos* mGotoPos;               // _1C
	ActFollowVectorField* mFollowField; // _20
	u8 _24[0xC];                        // _24, unknown
	                                    // _30 = MotionListener
};

struct ActBridgeArg : public ActionArg {
	virtual char* getName() { return "ActBridgeArg"; } // _08 (weak)

	// _00 = VTBL
	Game::ItemBridge::Item* mBridge; // _04
};

#define PIKIAI_BRIDGE_DEFAULT     0
#define PIKIAI_BRIDGE_GOTOPOS     1
#define PIKIAI_BRIDGE_STICKATTACK 2

struct ActBridge : public Action, virtual SysShape::MotionListener {
	ActBridge(Game::Piki* p);

	virtual void init(PikiAI::ActionArg*);                                 // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual void bounceCallback(Game::Piki* p, Sys::Triangle* hit);        // _24
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void platCallback(Game::Piki* p, Game::PlatEvent& event);      // _2C
	virtual void onKeyEvent(const SysShape::KeyEvent& event) { }           // _3C (weak)

	void initFollow();
	void initGoto();
	void initStickAttack();
	void calcAttackPos();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::ItemBridge::Item* mBridge;    // _10
	u16 mState;                         // _14
	ActStickAttack* mStickAttack;       // _18
	ActGotoPos* mGotoPos;               // _1C
	ActFollowVectorField* mFollowField; // _20
	u32 _24;                            // _24
	u32 _28;                            // _28
	u32 _2C;                            // _2C
	u8 _30;                             // _30
	                                    // _34 = MotionListener
};

struct ClimbActionArg : public ActionArg {
	inline ClimbActionArg(CollPart* collPart, f32 speed, u8 isClimbTowards)
	    : mCollPart(collPart)
	    , mSpeed(speed)
	    , mIsClimbTowards(isClimbTowards)
	{
	}

	virtual char* getName() { return "ClimbActionArg"; } // _08 (weak)

	// _00 = VTBL
	CollPart* mCollPart;  // _04
	f32 mSpeed;           // _08
	bool mIsClimbTowards; // _0C
};

struct ActClimb : public Action {
	ActClimb(Game::Piki* p);

	virtual void init(ActionArg* settings); // _08
	virtual int exec();                     // _0C
	virtual void cleanup();                 // _10

	// _00     = VTBL
	// _00-_0C = Action
	CollPart* mCollPart;  // _0C
	f32 mSpeed;           // _10
	Vector3f mVelocity;   // _14
	bool mIsClimbTowards; // _20, which way are we going along tube
};

struct ActCropArg : public ActionArg {
	virtual char* getName() { return "ActCropArg"; } // _08 (weak)

	inline bool isOnyonOrShip()
	{
		bool isOnyonCheck = false;
		if (mCreature->mObjectTypeID == OBJTYPE_Onyon || mCreature->mObjectTypeID == OBJTYPE_Ufo) {
			isOnyonCheck = true;
		}
		return isOnyonCheck;
	}

	// _00 = VTBL
	Game::Creature* mCreature; // _04
};

struct ActCrop : public Action, virtual SysShape::MotionListener {
	enum CropState {
		CROP_Goto   = 0,
		CROP_Climb  = 1,
		CROP_Attack = 2,
	};

	ActCrop(Game::Piki* parent);

	virtual void init(ActionArg* settings);                                // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual u32 getNextAIType() { return ACT_Free; }                       // _20 (weak)
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void onKeyEvent(const SysShape::KeyEvent& event);              // _3C (weak)

	int execClimb();
	void initGoto();
	void initAttack();

	void initClimb();
	void prepareClimb();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::Creature* mCreature;    // _10
	CollPart* mCollPart;          // _14
	Vector3f mClimbDirection;     // _18
	f32 mPlantHeightRatio;        // _24, 1 / tube tree length
	u16 mState;                   // _28
	ActStickAttack* mStickAttack; // _2C
	ActGotoPos* mGotoPos;         // _30
	u32 _34;                      // _34, unknown
	f32 mAttackDir;               // _38
	bool _3C;                     // _3C
	                              // _40 = MotionListener
};

struct ActEnter : public Action, virtual SysShape::MotionListener {
	enum EnterState {
		// states for entering onyon
		ENTER_OnyonBegin = 0,
		ENTER_OnyonClimb = 1,

		// states for entering ship
		ENTER_ShipGoto = 2,
		ENTER_ShipStay = 3,
		ENTER_ShipSuck = 4,
	};

	ActEnter(Game::Piki* p);

	virtual void init(ActionArg* settings);                   // _08
	virtual int exec();                                       // _0C
	virtual void cleanup();                                   // _10
	virtual void onKeyEvent(const SysShape::KeyEvent& event); // _3C (weak)

	void initStay();
	int execStay();
	void initSuck();
	int execSuck();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	u16 mState;            // _10
	ActGotoPos* mGotoPos;  // _14
	ActClimb* mClimb;      // _18
	CollPart* mOnyonLeg;   // _1C
	CollPart* mOnyonFoot;  // _20
	Game::Onyon* mOnyon;   // _24
	Vector3f mSuckGoalPos; // _28, position pikis entering ship get sucked to
	Vector3f mSuckDir;     // _34, direction (vector) pikis entering ship get sucked along
	f32 mTimer;            // _40, timer for pikis entering ship, reused by stay and suck
	f32 mVertSuckDist;     // _44, distance left to travel before entering ship, Y
	f32 mHorizSuckDist;    // _48, distance left to travel before entering ship, XZ
	u8 _4C;                // _4C
	Vector3f mSuckPos;     // _50, current suck position
	f32 mBaseScale;        // _54
	                       // _58 = MotionListener
};

struct ActExit : public Action {
	ActExit(Game::Piki* parent);

	virtual void init(ActionArg* settings); // _08
	virtual int exec();                     // _0C
	virtual void cleanup();                 // _10

	// _00     = VTBL
	// _00-_0C = Action
	ActClimb* mClimb;          // _0C
	CollPart* mOnyonLeg;       // _10
	Game::Creature* mCreature; // _14
	f32 mBaseScale;            // _18
};

/**
 * @fabricated.
 * Attempting to resolve StickAttackActionArg init issues in aiBreakGate.
 */
struct Attack {
	inline Attack(f32 damage, Game::Creature* target)
	    : mDamage(damage)
	    , mTarget(target)
	{
	}

	f32 mDamage;             // _00
	Game::Creature* mTarget; // _04
};

struct FlockAttackActionArg : public ActionArg {
	inline FlockAttackActionArg(f32 damage, int type, Game::BaseItem* target, int flockIndex)
	    : ActionArg()
	    , mDamage(damage)
	    , mTarget(target)
	    , mFlockIndex(flockIndex)
	    , mType(type)
	{
	}

	virtual char* getName() { return "FlockAttackActionArg"; } // _08 (weak)

	// _00-_04 = ActionArg
	f32 mDamage;             // _04
	Game::BaseItem* mTarget; // _08
	int mFlockIndex;         // _0C
	int mType;               // _10, weed type - 0=stone, 1=grass - see Game::ItemWeed::cWeedType enum
};

struct ActFlockAttack : public Action, virtual SysShape::MotionListener {
	enum FlockFlag {
		FLOCK_AttackReady    = 0x1,
		FLOCK_Unk2           = 0x2, // unused in aiWeed
		FLOCK_AnimFinished   = 0x4,
		FLOCK_AttackFinished = 0x8,
		FLOCK_Dead           = 0x10,
	};

	ActFlockAttack(Game::Piki* parent);

	virtual void init(ActionArg* settings);                   // _08
	virtual int exec();                                       // _0C
	virtual void cleanup();                                   // _10
	virtual void onKeyEvent(const SysShape::KeyEvent& event); // _3C (weak)

	inline void setFlag(u32 flag) { mFlags.typeView |= flag; }
	inline void resetFlag(u32 flag) { mFlags.typeView &= ~flag; }
	inline bool isFlag(u32 flag) const { return mFlags.typeView & flag; }

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	u8 mWeedType;            // _10, 0=stone, 1=grass
	Game::Creature* mTarget; // _14, unknown
	f32 mDamage;             // _18
	BitFlag<u8> mFlags;      // _1C
	int mAnimIdx;            // _20
	u32 mFlockIndex;         // _24, unknown

	// _28 = MotionListener
};

struct FollowVectorFieldActionArg : public ActionArg {
	inline FollowVectorFieldActionArg(Game::BaseItem* item)
	    : mItem(item)
	{
	}

	virtual char* getName() // _08 (weak) uncomment this when linking aiBreakGate.cpp
	{
		return "FollowVectorFieldActionArg";
	}

	// _00 = VTBL
	Game::BaseItem* mItem; // _04
};

struct ActFollowVectorField : public Action {
	ActFollowVectorField(Game::Piki* p);

	virtual void init(ActionArg* settings); // _08
	virtual int exec();                     // _0C
	virtual void cleanup();                 // _10

	// _00     = VTBL
	// _00-_0C = Action
	Game::BaseItem* mItem; // _0C
};

struct ActFormationInitArg : public CreatureActionArg {
	inline ActFormationInitArg(Game::Creature* navi, bool b1)
	    : CreatureActionArg(navi)
	    , _08(b1)
	{
	}

	inline ActFormationInitArg(Game::Creature* navi)
	    : CreatureActionArg(navi)
	    , _08(false)
	    , _09(0)
	{
	}

	// _00     = VTBL
	// _00-_08 = CreatureActionArg, Creature* = Navi*
	bool _08; // _08
	u8 _09;   // _09
};

#define FORMATION_SORT_NONE    (0)
#define FORMATION_SORT_FORMED  (1)
#define FORMATION_SORT_STARTED (2)

struct ActFormation : public Action, virtual Game::SlotChangeListener, virtual SysShape::MotionListener {
	ActFormation(Game::Piki* p);

	virtual void init(ActionArg* settings);                                // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual u32 getNextAIType();                                           // _20 (weak)
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void platCallback(Game::Piki* p, Game::PlatEvent& event);      // _2C
	virtual void wallCallback(Vector3f& pos);                              // _34
	virtual bool resumable();                                              // _3C (weak)
	virtual void inform(int);                                              // _40 (weak)
	virtual void onKeyEvent(const SysShape::KeyEvent& event);              // _44 (weak)

	void startSort();
	void setFormed();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = SlotChangeListener*
	// _10-_14 = MotionListener*
	Game::Navi* mNavi;            // _14
	ActFormationInitArg mInitArg; // _18
	int mNextAIType;              // _24
	u16 mSortState;               // _28, use FORMATION_SORT_ enum
	u16 _2A;                      // _2A
	u16 _2C;                      // _2C
	u16 _2E;                      // _2E
	u8 _30;                       // _30
	u8 _31;                       // _31
	int mSlotID;                  // _34
	u8 _38;                       // _38
	Game::Footmark* mFootmark;    // _3C
	u8 _40;                       // _40
	int mFrameTimer;              // _44
	int _48;                      // _48
	int _4C;                      // _4C
	f32 _50;                      // _50
	u8 _54;                       // _54
	f32 _58;                      // _58, timer?
	Game::CPlate* mCPlate;        // _5C
	bool _60;                     // _60
	bool _61;                     // _61
	                              // _64 = SlotChangeListener
	                              // _6C = MotionListener
};

struct ActFreeArg : public ActionArg {
	virtual char* getName() { return "ActFreeArg"; } // _08 (weak)

	// _00 = VTBL
	u8 mToGather;          // _04
	Vector3f mDestination; // _08
	f32 _14;               // _14
};

#define PIKIAI_FREE_DEFAULT 0
#define PIKIAI_FREE_GATHER  1
#define PIKIAI_FREE_BORE    2

struct ActFree : public Action, virtual SysShape::MotionListener {
	ActFree(Game::Piki* p);

	virtual void init(PikiAI::ActionArg* arg);                                // _08
	virtual int exec();                                                       // _0C
	virtual void cleanup();                                                   // _10
	virtual u32 getNextAIType() { return PIKIAI_FREE_BORE; }                  // _20 (weak)
	virtual void collisionCallback(Game::Piki* piki, Game::CollEvent& event); // _28
	virtual void onKeyEvent(const SysShape::KeyEvent& event);                 // _3C

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	u16 mState;         // _10
	ActGather* mGather; // _14
	ActBore* mBore;     // _18
	u16 mDelayTimer;    // _1C
	                    // _20 = MotionListener
};

struct GatherActionArg : public ActionArg {
	inline GatherActionArg(ActFreeArg* arg)
	{
		mDestination.x = arg->mDestination.x;
		mDestination.y = arg->mDestination.y;
		mDestination.z = arg->mDestination.z;
		mRadius        = arg->_14;
	}

	virtual char* getName() { return "GatherActionArg"; } // _08 (weak)

	// _00 = VTBL
	Vector3f mDestination; // _04
	f32 mRadius;           // _10
};

struct ActGather : public Action {
	ActGather(Game::Piki* p);

	virtual void cleanup();                // _08
	virtual int exec();                    // _0C
	virtual void init(PikiAI::ActionArg*); // _10

	// _00     = VTBL
	// _00-_0C = Action
	Vector3f mDestination; // _0C
	f32 mRadius;           // _18
	f32 mTimer;            // _1C
};

struct GotoPosActionArg : public ActionArg {
	virtual char* getName() { return "GotoPosActionArg"; } // _08 (weak)

	// _00 = VTBL
	Vector3f mPosition; // _04
	f32 mRadius;        // _10
};

struct ActGotoPos : public Action {
	ActGotoPos(Game::Piki* p);

	virtual void init(PikiAI::ActionArg*); // _08
	virtual int exec();                    // _0C
	virtual void cleanup();                // _10

	// _00     = VTBL
	// _00-_0C = Action
	f32 mRadius;        // _0C
	Vector3f mPosition; // _10
};

enum GotoSlotSearchType {
	SLOTSEARCH_Random  = 0,
	SLOTSEARCH_Nearest = 1,
};

struct GotoSlotArg : public ActionArg {
	inline GotoSlotArg(Game::Pellet* pellet, u8 searchType)
	    : ActionArg()
	    , mPellet(pellet)
	    , mSlotSearchType(searchType)
	{
	}

	virtual char* getName() { return "GotoSlotArg"; } // _08 (weak)

	// _00 = VTBL
	Game::Pellet* mPellet; // _04
	u8 mSlotSearchType;    // _08
};

struct ActGotoSlot : public Action {
	ActGotoSlot(Game::Piki* p);

	virtual void init(ActionArg* arg);        // _08
	virtual int exec();                       // _0C
	virtual void cleanup();                   // _10
	virtual void wallCallback(Vector3f& pos); // _34

	void resetTimers();

	// _00     = VTBL
	// _00-_0C = Action
	Game::Pellet* mPellet; // _0C
	s16 mSlotId;           // _10
	int mRetryCounter;     // _14, counts when we "should" grab soon - if we hit 60, fail.
	f32 mRefreshSlotTimer; // _18, start at 3 - if this hits 0, find a new slot
	u8 mWallTimer;         // _1C, increments on wall collision up to 100, but doesn't seem to be used
	bool mIsFirstPiki;     // _1D, no other pikis grabbing = all slots free
};

struct ActOneshotArg : public ActionArg {
	ActOneshotArg() { mAnimID = Game::IPikiAnims::NULLANIM; }

	// _00 = VTBL
	int mAnimID; // _04
};

struct ActOneshot : public ActBoreBase {
	ActOneshot(Game::Piki* p);

	virtual void init(ActionArg* arg);                        // _08
	virtual int exec();                                       // _0C
	virtual void cleanup();                                   // _10
	virtual void finish();                                    // _3C
	virtual void onKeyEvent(const SysShape::KeyEvent& event); // _40 (weak)

	// _00     = VTBL
	// _00-_10 = ActBoreBase
	ActOneshotArg mOneshotArg; // _10
	u8 mFlag;                  // _18

	// _1C = MotionListener
};

struct PathMoveArg : public ActionArg {
	inline PathMoveArg(Game::Pellet* pellet, Vector3f& p2, s16 p3, u32 p4)
	    : ActionArg()
	    , mPellet(pellet)
	    , _08(p2)
	    , _14(p3)
	    , _18(p4)
	{
	}

	virtual char* getName() { return "PathMoveArg"; } // _08 (weak)

	// _00 = VTBL
	Game::Pellet* mPellet; // _04
	Vector3f _08;          // _08, unused??
	s16 _14;               // _14, unused??
	int _18;               // _18, unused??
};

struct ActPathMove : public Action {
	enum PathMoveState {
		PATHMOVE_Pathfinding = 0,
		PATHMOVE_Move        = 1,
		PATHMOVE_MoveGoal    = 2,
		PATHMOVE_MoveGuru    = 3,
	};

	enum CRPointID {
		CRMOVE_Prev     = 0,
		CRMOVE_Curr     = 1,
		CRMOVE_Next     = 2,
		CRMOVE_NextNext = 3,
		CRMOVE_Count, // 4
	};

	ActPathMove(Game::Piki* p);

	virtual void init(ActionArg* settings); // _08
	virtual int exec();                     // _0C
	virtual void cleanup();                 // _10

	void initPathfinding(bool);
	Game::Onyon* decideGoal();
	int execPathfinding();
	int execMoveGoal();
	bool isAllBlue();
	void carry(Vector3f&);
	f32 getCarrySpeed();
	int execMove();
	int execMoveGuru();
	Game::WayPoint* getWayPoint(int);
	Vector3f crGetPoint(int);
	bool contextCheck(int);
	f32 crGetRadius(int);
	void crInit();
	void crMakeRefs();
	bool crMove();
	bool crPointOpen(int);

	// _00     = VTBL
	// _00-_0C = Action
	SlotHandles* mHandles;              // _0C
	Vector3f mPrevDisplacement;         // _10, vector we moved along, last frame to this frame - debug?
	s16 mStartWPIndex;                  // _1C
	u16 mState;                         // _1E
	u32 mContextHandle;                 // _20, pathfinding context handle id
	Vector3f mGoalPosition;             // _24
	Game::Pellet* mPellet;              // _30
	Game::Onyon* mOnyon;                // _34
	f32 _38;                            // _38, unused??
	u8 _3C;                             // _3C, unused??
	u8 mVsWayPointCounter;              // _3D, something to do with vs mode
	int mPathFindCounter;               // _40, how many frames have we been pathfinding for?
	Game::PathNode* mStartNode;         // _44
	Game::PathNode* mRootNode;          // _48, set to same as mStartNode, nodes on path are in this linked list
	int mWayPointCount;                 // _4C, number of waypoints to goal
	int mStartPathFindCounter;          // _50, keeps track of how many times we've started the actual pathfinder
	s16 mPathFindWPIndex;               // _54, where to start pathfinding from (set same as mStartWPIndex)
	s16 mGoalWPIndex;                   // _56
	Vector3f mPacePosition;             // _58, position to use when guided by MoveGuru (circling waiting)
	Game::WayPoint* mNextWayPoint;      // _64
	f32 mPaceAngle;                     // _68, angle used to calculate wait circle when next waypoint is closed
	bool mIsPickedUp;                   // _6C, is the pellet being carried
	int mCurrGraphIdx;                  // _70, how far through our node graph are we? starts at -1
	Vector3f mCRControls[CRMOVE_Count]; // _74, num 4 - indexed by CRMoveID (prev, curr, next, nextnext)
	Vector3f mStartPosition;            // _A4, starting pellet position
	Vector3f mNewVelocity;              // _B0, velocity to update pellet carry with on next execMove call
};

struct ActRescueArg : public ActionArg {
	// _00 = VTBL
	Game::Piki* mTarget; // _04
};

struct ActRescue : public Action, virtual SysShape::MotionListener {
	enum RescueState {
		RESCUE_Approach = 0,
		RESCUE_Go       = 1,
		RESCUE_Throw    = 2,
	};

	enum ThrowFlag {
		THROW_Null    = 0,
		THROW_DoThrow = 1,
		THROW_Stop    = 2,
	};

	ActRescue(Game::Piki* piki);

	virtual void init(ActionArg* arg);                                        // _08
	virtual int exec();                                                       // _0C
	virtual void cleanup();                                                   // _10
	virtual void emotion_success();                                           // _14
	virtual u32 getNextAIType() { return 1; }                                 // _20 (weak)
	virtual void collisionCallback(Game::Piki* piki, Game::CollEvent& event); // _28
	virtual void doDirectDraw(Graphics& gfx);                                 // _30
	virtual void onKeyEvent(const SysShape::KeyEvent& event);                 // _3C (weak)

	void initApproach();
	int execApproach();
	void initGo();
	int execGo();
	void initThrow();
	int execThrow();
	ActionExitCode checkPikmin();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	int mState;                   // _10
	u8 mThrowFlag;                // _14
	ActApproachPos* mApproachPos; // _18
	Game::Piki* mTargetPiki;      // _1C
	Game::WayPoint* mWayPoint;    // _20
	u8 mTimeLimit;                // _24
	                              // _28 = MotionListener
};

struct ActRest : public ActBoreBase {
	ActRest(Game::Piki* p);

	virtual void init(ActionArg* settings);                   // _08
	virtual int exec();                                       // _0C
	virtual void cleanup();                                   // _10
	virtual void finish();                                    // _3C
	virtual void onKeyEvent(const SysShape::KeyEvent& event); // _40 (weak)

	void sitDown();
	void standUp();

	// _00     = VTBL
	// _00-_10 = ActBoreBase
	u8 mState;  // _10
	f32 mTimer; // _14
	u8 mFlag;   // _18

	// _1C = MotionListener
};

enum StickAttackObjType {
	STICKATK_Default    = 0, // regular attack + attacking berries
	STICKATK_WhiteGate  = 1,
	STICKATK_BlackGate  = 2,
	STICKATK_ElecGate   = 3,
	STICKATK_Bridge     = 4,
	STICKATK_BreakStone = 5, // barrel/plug or bigfountain
	STICKATK_Treasure   = 6, // digging buried treasure
	STICKATK_Rock       = 7, // mold
};

struct StickAttackActionArg : public ActionArg {
	inline StickAttackActionArg(f32 damage, Game::Creature* creature, int animIdx, u8 objType)
	    : mAttackDamage(damage)
	    , mCreature(creature)
	    , mAnimIdx(animIdx)
	    , mObjType(objType)
	{
	}

	virtual char* getName() { return "StickAttackActionArg"; } // _08 (weak)

	// _00 = VTBL
	f32 mAttackDamage;         // _04
	Game::Creature* mCreature; // _08
	int mAnimIdx;              // _0C
	u8 mObjType;               // _10, see StickAttackObjType enum
};

struct ActStickAttack : public Action, virtual SysShape::MotionListener {
	ActStickAttack(Game::Piki* p);

	virtual void init(ActionArg* settings);                   // _08
	virtual int exec();                                       // _0C
	virtual void cleanup();                                   // _10
	virtual void onKeyEvent(const SysShape::KeyEvent& event); // _3C (weak)

	void createEfx();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::Creature* mCreature; // _10
	f32 mDamage;               // _14
	bool mIsAttackReady;       // _18
	bool mIsInitialStick;      // _19, is piki stuck to object initially (attack fails if it falls off)
	bool mIsAnimFinished;      // _1A
	bool mHasAttacked;         // _1B
	bool mIsAttackSuccessful;  // _1C
	u8 mObjType;               // _1D, see StickAttackObjType enum
	int mAnimIdx;              // _20

	// _24 = MotionListener
};

struct ActTeki : public Action, virtual SysShape::MotionListener {
	ActTeki(Game::Piki* p);

	virtual void init(ActionArg* settings);                                // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual void emotion_success();                                        // _14
	virtual u32 getNextAIType() { return 1; }                              // _20 (weak)
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void doDirectDraw(Graphics& gfx);                              // _30
	virtual void onKeyEvent(const SysShape::KeyEvent& event);              // _3C (weak)

	void makeTarget();
	void test_0();
	void setTimer();

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::EnemyBase* mFollowingTeki; // _10
	bool mToPanicFinish;             // _14
	bool mToEmote;                   // _15
	Game::Footmark* mFollowMark;     // _18
	s32 _1C;                         // _1C
	f32 _20;                         // _20
	f32 mMoveSpeed;                  // _24
	u32 _28;                         // _28
	Vector3f _2C;                    // _2C
	f32 _38;                         // _38
	f32 _3C;                         // _3C
	f32 _40;                         // _40
	f32 _44;                         // _44
	                                 // _48 = MotionListener
};

struct ActTransportArg : public ActionArg {
	virtual char* getName() { return "ActTransportArg"; } // _08 (weak)

	// _00 = VTBL
	Game::Pellet* mPellet; // _04
	Game::Onyon* mGoal;    // _08
	Vector3f _0C;          // _0C
	s16 _18;               // _18, slot maybe?
};

struct ActTransport : public Action, virtual SysShape::MotionListener {
	enum TransportState {
		TRANSPORT_Slot = 0, // finding a slot
		TRANSPORT_Lift = 1, // lifting pellet
		TRANSPORT_Move = 2, // moving with pellet
	};

	ActTransport(Game::Piki* parent);

	virtual void init(ActionArg* settings);                   // _08
	virtual int exec();                                       // _0C
	virtual void cleanup();                                   // _10
	virtual void emotion_success();                           // _14
	virtual void emotion_fail();                              // _18
	virtual void getInfo(char* infoStringBuffer);             // _38
	virtual void onKeyEvent(const SysShape::KeyEvent& event); // _3C (weak)

	bool isStickLeader();
	void initLift();
	int execLift();

	// unused/inlined:
	int getNumStickers();

	inline bool isPelletSatisfied(int pikiCount) { return (pikiCount >= mPellet->getPelletConfigMin()); }

	// _00     = VTBL
	// _00-_0C = Action
	// _0C-_10 = MotionListener*
	Game::Pellet* mPellet;  // _10
	Game::Onyon* mGoal;     // _14
	u16 mState;             // _18
	Vector3f _1C;           // _1C, gets passed to PathMove
	s16 _28;                // _28, gets passed to PathMove
	ActGotoSlot* mGotoSlot; // _2C
	ActPathMove* mPathMove; // _30
	bool mIsLiftAnimReady;  // _34, has reached point in lift anim to actually lift
	s16 mLiftTimer;         // _36
	bool mIsPathMoveActive; // _38
	bool mIsMoving;         // _39
	bool mIsCaptured;       // _3A
	                        // _3C = MotionListener
};

struct ActWeedArg : public ActionArg {
	virtual char* getName() { return "ActWeedArg"; } // _08 (weak)

	// _00 = VTBL
	Game::ItemWeed::Item* mWeed; // _04
};

struct ActWeed : public Action {
	enum WeedState {
		WEED_Attack = 0, // attack
		WEED_Adjust = 1, // move to new target
	};

	ActWeed(Game::Piki* parent);

	virtual void init(ActionArg* settings);                                // _08
	virtual int exec();                                                    // _0C
	virtual void cleanup();                                                // _10
	virtual void collisionCallback(Game::Piki* p, Game::CollEvent& event); // _28
	virtual void getInfo(char* infoStringBuffer);                          // _38

	void decideTarget();
	void initAdjust();
	void calcAttackPos();

	// unused/inlined:
	void initStickAttack();

	// _00     = VTBL
	// _00-_0C = Action
	Game::ItemWeed::Item* mWeed;   // _0C
	Game::BaseFlockMgr* mFlockMgr; // _10
	u16 mState;                    // _14
	ActFlockAttack* mFlockAttack;  // _18
	ActApproachPos* mApproachPos;  // _1C
	bool mIsAttacking;             // _20
	int mTargetFlockIdx;           // _24
	Vector3f mAttackPosition;      // _28
};

struct Brain {
	Brain(Game::Piki* p);

	void addAction(PikiAI::Action*);
	void init();
	void exec();
	PikiAI::Action* getCurrAction();
	Game::Navi* searchOrima();
	bool start(int, PikiAI::ActionArg*);

	Action** mActions; // _00, might be array of ptrs instead
	int mActionCnt;    // _04
	int mActionId;     // _08
	Game::Piki* mPiki; // _0C
};
}; // namespace PikiAI

#endif
