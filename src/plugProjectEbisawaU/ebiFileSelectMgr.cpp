#include "ebi/FileSelect.h"
#include "System.h"
#include "Game/MemoryCard/Mgr.h"
#include "MemoryCardMgr.h"

static const char name[] = "ebiFileSelectMgr";

namespace ebi {
namespace FileSelect {

TMgr* TMgr::msInstance;

/**
 * @note Address: 0x803E12E0
 * @note Size: 0x248
 */
void FSMStateMachine::init(TMgr* mgr)
{
	create(FSStateCount);
	registerState(new FSMState(FSSTATE_Standby, "Standby"));
	registerState(new FSMState_EmptyUpdate);
	registerState(new FSMState_MountCheck);
	registerState(new FSMState_GetPlayerHeader);
	registerState(new FSMState_CardError);
	registerState(new FSMState_ScreenFileSelect);
}

/**
 * @note Address: 0x803E1528
 * @note Size: 0x2C
 */
void FSMState::init(TMgr* mgr, Game::StateArg* arg) { do_init(mgr, arg); }

/**
 * @note Address: 0x803E1554
 * @note Size: 0x4
 */
void FSMState::do_init(TMgr*, Game::StateArg*) { }

/**
 * @note Address: 0x803E1558
 * @note Size: 0x2C
 */
void FSMState::exec(TMgr* mgr) { do_exec(mgr); }

/**
 * @note Address: 0x803E1584
 * @note Size: 0x4
 */
void FSMState::do_exec(TMgr*) { }

/**
 * @note Address: 0x803E1588
 * @note Size: 0x10
 */
void FSMState_EmptyUpdate::do_init(TMgr* mgr, Game::StateArg* arg)
{
	mCounter = 2;
	_14      = 2;
}

/**
 * @note Address: 0x803E1598
 * @note Size: 0x54
 */
void FSMState_EmptyUpdate::do_exec(TMgr* mgr)
{
	if (mCounter) {
		mCounter--;
	}
	if (!mCounter) {
		transit(mgr, FSSTATE_MountCheck, nullptr);
	}
}

/**
 * @note Address: 0x803E161C
 * @note Size: 0xC
 */
void FSMState_CardRequest::do_init(TMgr* mgr, Game::StateArg* arg) { mState = 0; }

/**
 * @note Address: 0x803E1628
 * @note Size: 0x278
 */
void FSMState_CardRequest::do_exec(TMgr* mgr)
{
	switch (mState) {
	case 0:
		bool check2 = (!sys->mCardMgr->mIsCard) && (sys->mCardMgr->checkStatus() != 11);
		if (check2) {
			P2ASSERTLINE(90, do_cardRequest(mgr));
			mState = 1;
		}
		break;
	case 1:
		bool check3 = (!sys->mCardMgr->mIsCard) && (sys->mCardMgr->checkStatus() != 11);
		if (check3) {
			mCardStatus = (int)static_cast<Game::MemoryCard::Mgr*>(sys->mCardMgr)->getCardStatus();
			static_cast<Game::MemoryCard::Mgr*>(sys->mCardMgr)->getCardStatus();
			mState = 2;
		}
		break;
	case 2:
		switch (mCardStatus) {
		case Game::MemoryCard::Mgr::MCS_IOError:
			do_transitCardReady(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_Ready:
			do_transitCardNoCard(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_Broken:
			do_transitCardIOError(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_Encoding:
			do_transitCardWrongDevice(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_NoFileSpace:
			do_transitCardWrongSector(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_WrongDevice:
			do_transitCardBroken(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_WrongSector:
			do_transitCardEncoding(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_NoFileEntry:
			do_transitCardNoFileSpace(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_FileOpenError:
			do_transitCardNoFileEntry(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_NoCard:
			do_transitCardFileOpenError(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_PlayerDataBroken:
			do_transitCardSerialNoError(mgr);
			break;
		case Game::MemoryCard::Mgr::MCS_13:
			do_transitCardPlayerDataBroken(mgr);
			break;
		default:
			JUT_PANICLINE(150, "※メモリーカードエラー:想定外のケースです\n");
			JUT_PANICLINE(151, "P2Assert");
			break;
		}
	}
}

/**
 * @note Address: 0x803E18A0
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardNoCard(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_NoCard;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E18DC
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardIOError(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_IOError;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E1918
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardWrongDevice(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_WrongDevice;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E1954
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardWrongSector(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_WrongSector;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E1990
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardBroken(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_DataBrokenAndDoYouFormat;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E19CC
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardEncoding(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_DataBrokenAndDoYouFormat;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E1A08
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardNoFileSpace(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_OverCapacity;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E1A44
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardNoFileEntry(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_OverCapacity;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E1A80
 * @note Size: 0x3C
 */
void FSMState_CardRequest::do_transitCardFileOpenError(TMgr* mgr)
{
	CardErrorStateArg arg;
	arg._00 = CardError::TMgr::Start_DoYouCreateNewFile;
	transit(mgr, FSSTATE_CardError, &arg);
}

/**
 * @note Address: 0x803E1ABC
 * @note Size: 0x2C
 */
void FSMState_CardRequest::do_transitCardPlayerDataBroken(TMgr* mgr) { do_transitCardReady(mgr); }

/**
 * @note Address: 0x803E1AE8
 * @note Size: 0x54
 */
void FSMState_CardRequest::do_transitCardSerialNoError(TMgr* mgr)
{
	JUT_PANICLINE(224, "※ロードでシリアルエラーはありえない\n"); // * There is no serial error during loading
	JUT_PANICLINE(225, "P2Assert");
}

/**
 * @note Address: 0x803E1B3C
 * @note Size: 0x28
 */
bool FSMState_MountCheck::do_cardRequest(TMgr* mgr) { return static_cast<Game::MemoryCard::Mgr*>(sys->mCardMgr)->resetError(); }

/**
 * @note Address: 0x803E1B64
 * @note Size: 0x34
 */
void FSMState_MountCheck::do_transitCardReady(TMgr* mgr) { transit(mgr, FSState_GetPlayerHeader, nullptr); }

/**
 * @note Address: 0x803E1B98
 * @note Size: 0x2C
 */
bool FSMState_GetPlayerHeader::do_cardRequest(TMgr* mgr)
{
	return static_cast<Game::MemoryCard::Mgr*>(sys->mCardMgr)->getPlayerHeader(&mgr->mPlayer);
}

/**
 * @note Address: 0x803E1BC4
 * @note Size: 0x34
 */
void FSMState_GetPlayerHeader::do_transitCardReady(TMgr* mgr) { transit(mgr, FSState_ScreenFileSelect, nullptr); }

/**
 * @note Address: 0x803E1BF8
 * @note Size: 0x38
 */
void FSMState_GetPlayerHeader::do_transitCardSerialNoError(TMgr* mgr) { JUT_PANICLINE(261, "P2Assert"); }

/**
 * @note Address: 0x803E1C30
 * @note Size: 0x44
 */
void FSMState_ScreenFileSelect::do_init(TMgr* mgr, Game::StateArg* arg)
{
	mgr->mMgrFS.perseInfo(mgr->mPlayer);
	mgr->mMgrFS.startSeq();
	mgr->mCardErrorMgr.forceQuitSeq();
}

/**
 * @note Address: 0x803E1C74
 * @note Size: 0xC4
 */
void FSMState_ScreenFileSelect::do_exec(TMgr* mgr)
{
	if (mgr->mMgrFS.isFinish()) {
		switch (mgr->mMgrFS.mEndStat) {
		case 1:
		case 2:
			transit(mgr, FSSTATE_MountCheck, nullptr);
			break;
		case 3:
			mgr->goEnd_(TMgr::End_2);
			break;
		case 4:
			mgr->goEnd_(TMgr::End_1);
			break;
		case 5:
			mgr->goEnd_(TMgr::End_3);
			break;
		}
	}
}

/**
 * @note Address: 0x803E1D38
 * @note Size: 0x60
 */
void FSMState_CardError::do_init(TMgr* mgr, Game::StateArg* arg)
{
	CardErrorStateArg* carg = static_cast<CardErrorStateArg*>(arg);
	P2ASSERTLINE(319, arg);
	mgr->mCardErrorMgr.startSeq((CardError::TMgr::enumStart)carg->_00);
}

/**
 * @note Address: 0x803E1D98
 * @note Size: 0xB8
 */
void FSMState_CardError::do_exec(TMgr* mgr)
{
	if (mgr->mCardErrorMgr.isGetEnd()) {
		switch (mgr->mCardErrorMgr.mEndStat) {
		case 1:
			static_cast<Game::MemoryCard::Mgr*>(sys->mCardMgr)->loadPlayerForNoCard(0);
			mgr->goEnd_(TMgr::End_1);
			break;
		case 2:
			mgr->start();
			break;
		default:
			JUT_PANICLINE(342, "※　mgr->mCardErrorMgr->getEnd=%d ってありえない！\n", mgr->mCardErrorMgr.mEndStat);
			JUT_PANICLINE(343, "P2Assert");
		}
	}
}

/**
 * @note Address: N/A
 * @note Size: 0xC0
 */
TMgr::TMgr()
    : mCounter(0)
    , _F44(0)
{
	mFsm.init(this);
	mFsm.start(this, FSSTATE_Standby, 0);
	mInError = false;
}

#pragma dont_inline on
/**
 * @note Address: 0x803E1ED8
 * @note Size: 0x84
 */
TMgr::~TMgr() { msInstance = nullptr; }
#pragma dont_inline reset

/**
 * @note Address: 0x803E1F5C
 * @note Size: 0xDC
 */
TMgr* TMgr::createInstance()
{
	if (!msInstance) {
		msInstance = new TMgr;
	}
	return msInstance;
}

/**
 * @note Address: N/A
 * @note Size: 0x48
 */
void TMgr::deleteInstance() { delete msInstance; }

/**
 * @note Address: N/A
 * @note Size: 0x8
 */
TMgr* TMgr::getInstance() { return msInstance; }

/**
 * @note Address: 0x803E2038
 * @note Size: 0x58
 */
void TMgr::onDvdErrorOccured()
{
	if (msInstance) {
		if (!msInstance->isFinish()) {
			msInstance->mInError = true;
			msInstance->forceQuit();
		} else {
			msInstance->mInError = false;
		}
	}
}

/**
 * @note Address: 0x803E2090
 * @note Size: 0x44
 */
void TMgr::onDvdErrorRecovered()
{
	if (msInstance && msInstance->mInError) {
		msInstance->start();
		msInstance->mInError = false;
	}
}

/**
 * @note Address: 0x803E20D4
 * @note Size: 0x4C
 */
void TMgr::start()
{
	_FE8   = true;
	mState = 0;
	mFsm.start(this, FSSTATE_EmptyUpdate, nullptr);
}

/**
 * @note Address: 0x803E2120
 * @note Size: 0x58
 */
void TMgr::forceQuit()
{
	mFsm.start(this, FSSTATE_Standby, nullptr);
	mCardErrorMgr.forceQuitSeq();
	mMgrFS.forceQuitSeq();
}

/**
 * @note Address: 0x803E2178
 * @note Size: 0x8C
 */
void TMgr::update()
{
	mFsm.exec(this);
	if (getStateID()) {
		sys->mCardMgr->update();
		mCardErrorMgr.update();
		mMgrFS.update();
		if (mCounter) {
			mCounter--;
		}
	}
}

/**
 * @note Address: 0x803E2204
 * @note Size: 0x44
 */
void TMgr::draw()
{
	if (getStateID()) {
		mMgrFS.draw();
		mCardErrorMgr.draw();
	}
}

/**
 * @note Address: 0x803E2248
 * @note Size: 0x4
 */
void TMgr::showInfo() { }

/**
 * @note Address: 0x803E224C
 * @note Size: 0x4C
 */
bool TMgr::isFinish()
{
	if (!getStateID() && !mInError) {
		return true;
	} else {
		return false;
	}
}

/**
 * @note Address: 0x803E2298
 * @note Size: 0x5C
 */
void TMgr::goEnd_(enumEnd end)
{
	mState = end;
	mFsm.transit(this, FSSTATE_Standby, nullptr);
	mMgrFS.forceQuitSeq();
	mCardErrorMgr.forceQuitSeq();
}

/**
 * @note Address: 0x803E22F4
 * @note Size: 0x58
 */
int TMgr::getStateID()
{
	P2ASSERTLINE(534, mCurrentState);
	return mCurrentState->mId;
}

} // namespace FileSelect

} // namespace ebi
