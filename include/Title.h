#ifndef _TITLE_H
#define _TITLE_H

// Header for entire Demo namespace.

#include "DvdThreadCommand.h"
#include "Game/BaseHIO.h"
#include "Section.h"
#include "ebi/Option.h"
#include "ebi/Omake.h"
#include "ebi/TMainTitleMgr.h"

template <typename T>
struct IDelegate1;
struct JUTTexture;
struct Menu;

namespace Game {
struct THPPlayer;
}

namespace TitleDummy {
struct Section {
	Section(JKRHeap*);

	virtual ~Section();
	void init();
	void loadResource();
	bool doUpdate();
	void doDraw(Graphics& gfx);
};
} // namespace TitleDummy

namespace Title {

struct HIORootNode : public Game::HIORootNode {
	HIORootNode(Section* sect, const char* name)
	    : Game::HIORootNode(sect)
	{
		mName = name;
	}
};

// Size: 0x1B0
struct Section : public Game::BaseHIOSection {
	enum BGMIndex { BGM_MainTheme = 0, BGM_Options, BGM_HiScore, BGM_Bonus };
	enum State { State_Init, State_MainTitle, State_Options, State_Bonus, State_HiScore };
	Section(JKRHeap*);

	virtual ~Section();                         // _08
	virtual void run();                         // _0C
	virtual void init();                        // _18
	virtual void doExit();                      // _24
	virtual bool forceReset() { return false; } // _2C (weak)
	virtual void doLoadingStart();              // _34
	virtual bool doLoading();                   // _38
	virtual bool doUpdate();                    // _3C
	virtual void doDraw(Graphics& gfx);         // _40
	virtual bool isFinishable();                // _44
	virtual void loadResource();                // _50

	void loadResident();
	// void menuCancel(Menu&);
	// void menuSelect(Menu&);
	void doUpdateMainTitle();
	void doUpdateOmake();
	void menuCancel(Menu&);
	void menuSelect(Menu&);
	void drawShortCuts(Graphics&);
	void drawShortCut(Graphics&, int, int, int, char*);
	void drawDebugInfo(Graphics&);
	void updateMenu();
	void doUpdateHiScore();
	void doUpdateOption();

	// _00		= VTBL
	// _00-_48	= Game::BaseHIOSection
	int mState;                         // _0048
	f32 mGoToDemoTimer;                 // _004C
	Menu* mMenu;                        // _0050
	DvdThreadCommand mThreadCommand;    // _0054
	Delegate<Section>* mButtonCallback; // _00C0
	Controller* mController1;           // _00C4
	Controller* mController2;           // _00C8
	ebi::TMainTitleMgr mMainTitleMgr;   // _00CC
	ebi::Option::TMgr mOptionMgr;       // _1730
	ebi::Omake::TMgr mOmakeMgr;         // _2678
	Game::THPPlayer* mThpPlayer;        // _2F38
	int mMovieIndex;                    // _2F3C
	JKRArchive* mHiScoreTex;            // _2F40
	bool mDoCheckShortCut;              // _2F44
	u32 mLanguageID;                    // _2F48
};
} // namespace Title

#endif
