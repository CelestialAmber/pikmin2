#ifndef _GAME_DYNPARTICLEMGR_H
#define _GAME_DYNPARTICLEMGR_H

/*
    __vt__Q24Game14DynParticleMgr:
    .4byte 0
    .4byte 0
    .4byte __dt__Q24Game14DynParticleMgrFv
    .4byte getChildCount__5CNodeFv
    .4byte "getObject__31Container<Q24Game11DynParticle>FPv"
    .4byte "getNext__35MonoObjectMgr<Q24Game11DynParticle>FPv"
    .4byte "getStart__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "getEnd__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "get__35MonoObjectMgr<Q24Game11DynParticle>FPv"
    .4byte "getAt__35MonoObjectMgr<Q24Game11DynParticle>Fi"
    .4byte "getTo__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte 0
    .4byte 0
    .4byte "@28@doAnimation__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "@28@doEntry__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "@28@doSetView__35MonoObjectMgr<Q24Game11DynParticle>Fi"
    .4byte "@28@doViewCalc__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "@28@doSimulation__35MonoObjectMgr<Q24Game11DynParticle>Ff"
    .4byte "@28@doDirectDraw__35MonoObjectMgr<Q24Game11DynParticle>FR8Graphics"
    .4byte doSimpleDraw__16GenericObjectMgrFP8Viewport
    .4byte loadResources__16GenericObjectMgrFv
    .4byte "@28@resetMgr__Q24Game14DynParticleMgrFv"
    .4byte pausable__16GenericObjectMgrFv
    .4byte frozenable__16GenericObjectMgrFv
    .4byte getMatrixLoadType__16GenericObjectMgrFv
    .4byte "doAnimation__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "doEntry__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "doSetView__35MonoObjectMgr<Q24Game11DynParticle>Fi"
    .4byte "doViewCalc__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "doSimulation__35MonoObjectMgr<Q24Game11DynParticle>Ff"
    .4byte "doDirectDraw__35MonoObjectMgr<Q24Game11DynParticle>FR8Graphics"
    .4byte "birth__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte resetMgr__Q24Game14DynParticleMgrFv
    .4byte "clearMgr__35MonoObjectMgr<Q24Game11DynParticle>Fv"
    .4byte "onAlloc__35MonoObjectMgr<Q24Game11DynParticle>Fv"
*/

struct CNode {
	virtual ~CNode();             // _08 (weak)
	virtual void getChildCount(); // _0C
};

struct Container<Game::DynParticle> {
	virtual ~Container<DynParticle>(); // _08 (weak)
	virtual void _0C() = 0;            // _0C
	virtual void getObject(void*);     // _10 (weak)
};

struct MonoObjectMgr<Game::DynParticle> {
	virtual ~MonoObjectMgr<DynParticle>(); // _08 (weak)
	virtual void _0C() = 0;                // _0C
	virtual void _10() = 0;                // _10
	virtual void getNext(void*);           // _14 (weak)
	virtual void getStart();               // _18 (weak)
	virtual void getEnd();                 // _1C (weak)
	virtual void get(void*);               // _20 (weak)
	virtual void getAt(int);               // _24 (weak)
	virtual void getTo();                  // _28 (weak)
	virtual void _2C() = 0;                // _2C
	virtual void _30() = 0;                // _30
	virtual void _34() = 0;                // _34
	virtual void _38() = 0;                // _38
	virtual void _3C() = 0;                // _3C
	virtual void _40() = 0;                // _40
	virtual void _44() = 0;                // _44
	virtual void _48() = 0;                // _48
	virtual void _4C() = 0;                // _4C
	virtual void _50() = 0;                // _50
	virtual void _54() = 0;                // _54
	virtual void _58() = 0;                // _58
	virtual void _5C() = 0;                // _5C
	virtual void _60() = 0;                // _60
	virtual void doAnimation();            // _64 (weak)
	virtual void doEntry();                // _68 (weak)
	virtual void doSetView(int);           // _6C (weak)
	virtual void doViewCalc();             // _70 (weak)
	virtual void doSimulation(float);      // _74 (weak)
	virtual void doDirectDraw(Graphics&);  // _78 (weak)
	virtual void birth();                  // _7C (weak)
	virtual void resetMgr();               // _80 (weak)
	virtual void clearMgr();               // _84 (weak)
	virtual void onAlloc();                // _88 (weak)
};

struct GenericObjectMgr {
	virtual ~GenericObjectMgr();          // _08 (weak)
	virtual void _0C() = 0;               // _0C
	virtual void _10() = 0;               // _10
	virtual void _14() = 0;               // _14
	virtual void _18() = 0;               // _18
	virtual void _1C() = 0;               // _1C
	virtual void _20() = 0;               // _20
	virtual void _24() = 0;               // _24
	virtual void _28() = 0;               // _28
	virtual void _2C() = 0;               // _2C
	virtual void _30() = 0;               // _30
	virtual void _34() = 0;               // _34
	virtual void _38() = 0;               // _38
	virtual void _3C() = 0;               // _3C
	virtual void _40() = 0;               // _40
	virtual void _44() = 0;               // _44
	virtual void _48() = 0;               // _48
	virtual void doSimpleDraw(Viewport*); // _4C (weak)
	virtual void loadResources();         // _50 (weak)
	virtual void _54() = 0;               // _54
	virtual void pausable();              // _58 (weak)
	virtual void frozenable();            // _5C (weak)
	virtual void getMatrixLoadType();     // _60 (weak)
};

namespace Game {
struct DynParticleMgr : public CNode,
                        public Container<Game::DynParticle>,
                        public MonoObjectMgr<Game::DynParticle>,
                        public GenericObjectMgr {
	virtual ~DynParticleMgr(); // _08 (weak)
	virtual void _2C() = 0;    // _2C
	virtual void _30() = 0;    // _30
	virtual void resetMgr();   // _80 (weak)

	DynParticleMgr(int);
};
} // namespace Game

#endif