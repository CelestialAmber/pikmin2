#include "PSSystem/SeqTrack.h"
#include "PSM/ObjCalc.h"
#include "PSM/Otakara.h"
#include "PSGame/Global.h"
#include "PSAutoBgm/PSAutoBgm.h"
#include "JSystem/JAudio/JALCalc.h"
#include "PSM/CreaturePrm.h"
#include "Game/Navi.h"
#include "utilityU.h"
#include "PSM/BossSeq.h"

/*
    Generated from dpostproc

    .section .rodata  # 0x804732E0 - 0x8049E220
    lbl_8049CD98:
        .asciz "damageD  "
        .skip 2
    lbl_8049CDA4:
        .asciz "lifeD    "
        .skip 2
    lbl_8049CDB0:
        .asciz "pikminD  "
        .skip 2
    lbl_8049CDBC:
        .asciz "PSMainSide_Director.cpp"
    lbl_8049CDD4:
        .asciz "P2Assert"
        .skip 3
    lbl_8049CDE0:
        .asciz "PSDirector.h"
        .skip 3
        .asciz "PSCommon.h"
        .skip 1
        .asciz "PSGame.h"
        .skip 3
        .asciz "PSScene.h"
        .skip 2
        .asciz "get sound scene at\ninvalid timming\n"
        .asciz "PSMainSide_ObjSound.h"
        .skip 2
    lbl_8049CE50:
        .asciz "pikatkD  "
        .skip 2
    lbl_8049CE5C:
        .asciz "tentionD "
        .skip 2

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global __vt__Q23PSM13ExiteDirector
    __vt__Q23PSM13ExiteDirector:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM13ExiteDirectorFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q28PSSystem12DirectorBaseFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .global
   __vt__Q23PSM17PikAttackDirector
    __vt__Q23PSM17PikAttackDirector:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM17PikAttackDirectorFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q28PSSystem12DirectorBaseFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .global
   __vt__Q23PSM19ActorDirector_Kehai
    __vt__Q23PSM19ActorDirector_Kehai:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM19ActorDirector_KehaiFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q23PSM19ActorDirector_EnemyFv
        .4byte execInner__Q23PSM20ActorDirector_ScaledFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .4byte
   getNearestDistance__Q23PSM20ActorDirector_ScaledFv .4byte
   onSetMinDistObj__Q23PSM19ActorDirector_EnemyFPQ24Game8Creature .4byte
   getVolZeroDist__Q23PSM19ActorDirector_KehaiFPQ24Game9EnemyBase .4byte
   getVolMaxDist__Q23PSM19ActorDirector_KehaiFPQ24Game9EnemyBase .global
   __vt__Q23PSM20ActorDirector_Battle
    __vt__Q23PSM20ActorDirector_Battle:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM20ActorDirector_BattleFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q23PSM19ActorDirector_EnemyFv
        .4byte execInner__Q23PSM20ActorDirector_ScaledFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .4byte
   getNearestDistance__Q23PSM20ActorDirector_ScaledFv .4byte
   onSetMinDistObj__Q23PSM19ActorDirector_EnemyFPQ24Game8Creature .4byte
   getVolZeroDist__Q23PSM20ActorDirector_BattleFPQ24Game9EnemyBase .4byte
   getVolMaxDist__Q23PSM20ActorDirector_BattleFPQ24Game9EnemyBase .global
   __vt__Q23PSM19ActorDirector_Enemy
    __vt__Q23PSM19ActorDirector_Enemy:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM19ActorDirector_EnemyFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q23PSM19ActorDirector_EnemyFv
        .4byte execInner__Q23PSM20ActorDirector_ScaledFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .4byte
   getNearestDistance__Q23PSM20ActorDirector_ScaledFv .4byte
   onSetMinDistObj__Q23PSM19ActorDirector_EnemyFPQ24Game8Creature .4byte 0
        .4byte 0
    .global __vt__Q23PSM20ActorDirector_Scaled
    __vt__Q23PSM20ActorDirector_Scaled:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM20ActorDirector_ScaledFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q23PSM22TrackOnDirector_ScaledFv
        .4byte execInner__Q23PSM20ActorDirector_ScaledFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .4byte
   getNearestDistance__Q23PSM20ActorDirector_ScaledFv .4byte
   onSetMinDistObj__Q23PSM20ActorDirector_ScaledFPQ24Game8Creature .global
   __vt__Q23PSM21ActorDirector_TrackOn
    __vt__Q23PSM21ActorDirector_TrackOn:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM21ActorDirector_TrackOnFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q23PSM21ActorDirector_TrackOnFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .global
   __vt__Q23PSM17ListDirectorActor
    __vt__Q23PSM17ListDirectorActor:
        .4byte 0
        .4byte 0
        .4byte exec__Q28PSSystem17DirectorCopyActorFPQ28PSSystem12DirectorBase
        .4byte onUpdateFromMasterD__Q23PSM17ListDirectorActorFv
        .4byte onUpdateFromSlaveD__Q28PSSystem17DirectorCopyActorFv
    .global __vt__Q23PSM22TrackOnDirector_Scaled
    __vt__Q23PSM22TrackOnDirector_Scaled:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM22TrackOnDirector_ScaledFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q23PSM22TrackOnDirector_ScaledFv
        .4byte execInner__Q28PSSystem12DirectorBaseFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .4byte 0 .global
   __vt__Q23PSM22TrackOnDirector_Voting
    __vt__Q23PSM22TrackOnDirector_Voting:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM22TrackOnDirector_VotingFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q23PSM22TrackOnDirector_VotingFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .global
   __vt__Q23PSM19TrackOnDirectorBase
    __vt__Q23PSM19TrackOnDirectorBase:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM19TrackOnDirectorBaseFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q28PSSystem12DirectorBaseFv
        .4byte
   directOnTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM19TrackOnDirectorBaseFRQ28PSSystem12SeqTrackBase .4byte
   doUpdateRequest__Q28PSSystem16SwitcherDirectorFv .4byte
   onPlayInit__Q23PSM19TrackOnDirectorBaseFP8JASTrack .4byte
   onDirectOn__Q28PSSystem12DirectorBaseFv .4byte
   onDirectOff__Q28PSSystem12DirectorBaseFv .global
   __vt__Q23PSM28PikminNumberDirector_AutoBgm
    __vt__Q23PSM28PikminNumberDirector_AutoBgm:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM28PikminNumberDirector_AutoBgmFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q23PSM20PikminNumberDirectorFv
        .4byte
   directOnTrack__Q23PSM28PikminNumberDirector_AutoBgmFRQ28PSSystem12SeqTrackBase
        .4byte
   directOffTrack__Q23PSM28PikminNumberDirector_AutoBgmFRQ28PSSystem12SeqTrackBase
        .4byte doUpdateRequest__Q28PSSystem16SwitcherDirectorFv
        .4byte onPlayInit__Q28PSSystem12DirectorBaseFP8JASTrack
        .4byte onDirectOn__Q28PSSystem12DirectorBaseFv
        .4byte onDirectOff__Q28PSSystem12DirectorBaseFv
    .global __vt__Q23PSM20PikminNumberDirector
    __vt__Q23PSM20PikminNumberDirector:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM20PikminNumberDirectorFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q23PSM20PikminNumberDirectorFv
        .4byte
   directOnTrack__Q23PSM20PikminNumberDirectorFRQ28PSSystem12SeqTrackBase .4byte
   directOffTrack__Q23PSM20PikminNumberDirectorFRQ28PSSystem12SeqTrackBase
        .4byte doUpdateRequest__Q28PSSystem16SwitcherDirectorFv
        .4byte onPlayInit__Q28PSSystem12DirectorBaseFP8JASTrack
        .4byte onDirectOn__Q28PSSystem12DirectorBaseFv
        .4byte onDirectOff__Q28PSSystem12DirectorBaseFv
    .global __vt__Q23PSM25ActorDirector_TempoChange
    __vt__Q23PSM25ActorDirector_TempoChange:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM25ActorDirector_TempoChangeFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q23PSM25ActorDirector_TempoChangeFv
        .4byte
   directOnTrack__Q23PSM23TempoChangeDirectorBaseFRQ28PSSystem12SeqTrackBase
        .4byte
   directOffTrack__Q23PSM23TempoChangeDirectorBaseFRQ28PSSystem12SeqTrackBase
        .4byte doUpdateRequest__Q28PSSystem16SwitcherDirectorFv
        .4byte onPlayInit__Q28PSSystem12DirectorBaseFP8JASTrack
        .4byte onDirectOn__Q28PSSystem12DirectorBaseFv
        .4byte onDirectOff__Q28PSSystem12DirectorBaseFv
    .global __vt__Q23PSM23TempoChangeDirectorBase
    __vt__Q23PSM23TempoChangeDirectorBase:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM23TempoChangeDirectorBaseFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q28PSSystem12DirectorBaseFv
        .4byte
   directOnTrack__Q23PSM23TempoChangeDirectorBaseFRQ28PSSystem12SeqTrackBase
        .4byte
   directOffTrack__Q23PSM23TempoChangeDirectorBaseFRQ28PSSystem12SeqTrackBase
        .4byte doUpdateRequest__Q28PSSystem16SwitcherDirectorFv
        .4byte onPlayInit__Q28PSSystem12DirectorBaseFP8JASTrack
        .4byte onDirectOn__Q28PSSystem12DirectorBaseFv
        .4byte onDirectOff__Q28PSSystem12DirectorBaseFv
    .global __vt__Q23PSM16SwitcherDirector
    __vt__Q23PSM16SwitcherDirector:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM16SwitcherDirectorFv
        .4byte exec__Q28PSSystem12DirectorBaseFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q28PSSystem12DirectorBaseFv
        .4byte 0
        .4byte 0
        .4byte doUpdateRequest__Q28PSSystem16SwitcherDirectorFv
        .4byte onPlayInit__Q28PSSystem12DirectorBaseFP8JASTrack
        .4byte onDirectOn__Q28PSSystem12DirectorBaseFv
        .4byte onDirectOff__Q28PSSystem12DirectorBaseFv
    .global __vt__Q23PSM14DamageDirector
    __vt__Q23PSM14DamageDirector:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM14DamageDirectorFv
        .4byte exec__Q28PSSystem15OneShotDirectorFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q23PSM14DamageDirectorFv
        .4byte directOnTrack__Q23PSM14DamageDirectorFRQ28PSSystem12SeqTrackBase
        .4byte
   directOffTrack__Q28PSSystem15OneShotDirectorFRQ28PSSystem12SeqTrackBase
        .4byte doUpdateRequest__Q28PSSystem12DirectorBaseFv
        .4byte onPlayInit__Q28PSSystem12DirectorBaseFP8JASTrack
        .4byte onDirectOn__Q28PSSystem12DirectorBaseFv
        .4byte onDirectOff__Q28PSSystem12DirectorBaseFv
    .global __vt__Q23PSM15OneShotDirector
    __vt__Q23PSM15OneShotDirector:
        .4byte 0
        .4byte 0
        .4byte __dt__Q23PSM15OneShotDirectorFv
        .4byte exec__Q28PSSystem15OneShotDirectorFv
        .4byte directOn__Q28PSSystem12DirectorBaseFv
        .4byte directOff__Q28PSSystem12DirectorBaseFv
        .4byte underDirection__Q28PSSystem12DirectorBaseFv
        .4byte execInner__Q28PSSystem12DirectorBaseFv
        .4byte 0
        .4byte
   directOffTrack__Q28PSSystem15OneShotDirectorFRQ28PSSystem12SeqTrackBase
        .4byte doUpdateRequest__Q28PSSystem12DirectorBaseFv
        .4byte onPlayInit__Q28PSSystem12DirectorBaseFP8JASTrack
        .4byte onDirectOn__Q28PSSystem12DirectorBaseFv
        .4byte onDirectOff__Q28PSSystem12DirectorBaseFv

    .section .sdata2, "a"     # 0x80516360 - 0x80520E40
    lbl_80520C00:
        .float 0.1
    lbl_80520C04:
        .float 5.0
    lbl_80520C08:
        .float 1.0
    lbl_80520C0C:
        .float 0.7
    lbl_80520C10:
        .float 0.0
    lbl_80520C14:
        .float 100000.0
    lbl_80520C18:
        .float 1000000.0
*/

namespace PSM {

/**
 * @note Address: 0x80456AF8
 * @note Size: 0x80
 */
DamageDirector::DamageDirector()
    : mPitchMod1(0.1f)
    , mPitchMod2(5.0f)
    , mDuration(225)
{
}

/**
 * @note Address: 0x80456BF8
 * @note Size: 0x34
 */
void DamageDirector::directOnTrack(PSSystem::SeqTrackBase& seqTrack)
{
	static_cast<PSSystem::SeqTrackRoot&>(seqTrack).pitchModulation(mPitchMod1, mPitchMod2, mDuration, this);
}

/**
 * @note Address: 0x80456C2C
 * @note Size: 0x3C
 */
void DamageDirector::execInner()
{
	if (mActor) {
		mActor->exec(this);
	}
}

/**
 * @note Address: 0x80456CE8
 * @note Size: 0x30
 */
void TempoChangeDirectorBase::directOnTrack(PSSystem::SeqTrackBase& seqTrack)
{
	static_cast<PSSystem::SeqTrackRoot&>(seqTrack).tempoChange(mTempoValue, mTimeBase, this);
}

/**
 * @note Address: 0x80456D18
 * @note Size: 0x30
 */
void TempoChangeDirectorBase::directOffTrack(PSSystem::SeqTrackBase& seqTrack)
{
	static_cast<PSSystem::SeqTrackRoot&>(seqTrack).tempoChange(1.0f, mTimeBase, this);
}

/**
 * @note Address: 0x80456D48
 * @note Size: 0x84
 */
ActorDirector_TempoChange::ActorDirector_TempoChange() { }

/**
 * @note Address: 0x80456E5C
 * @note Size: 0x3C
 */
void ActorDirector_TempoChange::execInner()
{
	if (mActor) {
		mActor->exec(this);
	}
}

/**
 * @note Address: 0x80456E98
 * @note Size: 0x78
 */
PikminNumberDirector::PikminNumberDirector(int type, u8 mask, PSSystem::DirectedBgm& bgm)
    : SwitcherDirector(type, "pikminD  ")
    , mActor(nullptr)
    , mMaskId(mask)
// It seems like mActor is supposed to be a member of SwitcherDirector, but that messes up everything else that inherits it
{
}

/**
 * @note Address: 0x80456F10
 * @note Size: 0x4C
 */
void PikminNumberDirector::directOnTrack(PSSystem::SeqTrackBase& seqTrack)
{
	seqTrack.getTaskEntryList();
	static_cast<PSSystem::SeqTrackChild&>(seqTrack).setIdMask(mMaskId, this);
}

/**
 * @note Address: 0x80456F5C
 * @note Size: 0x2C
 */
void PikminNumberDirector::directOffTrack(PSSystem::SeqTrackBase& seqTrack)
{
	static_cast<PSSystem::SeqTrackChild&>(seqTrack).setIdMask(0, this);
}

/**
 * @note Address: 0x80456F88
 * @note Size: 0x3C
 */
void PikminNumberDirector::execInner()
{
	if (mActor) {
		mActor->exec(this);
	}
}

/**
 * @note Address: 0x80456FC4
 * @note Size: 0x94
 */
PikminNumberDirector_AutoBgm::PikminNumberDirector_AutoBgm(int p1, u8 p2, PSSystem::DirectedBgm& bgm)
    : PikminNumberDirector(p1, p2, bgm)
    , mDirectedBgm(&bgm)
{
	/*
	.loc_0x0:
	  stwu      r1, -0x20(r1)
	  mflr      r0
	  lis       r7, 0x804A
	  stw       r0, 0x24(r1)
	  subi      r0, r7, 0x3250
	  stw       r31, 0x1C(r1)
	  mr        r31, r6
	  stw       r30, 0x18(r1)
	  mr        r30, r5
	  mr        r5, r0
	  stw       r29, 0x14(r1)
	  mr        r29, r3
	  bl        -0x114140
	  lis       r4, 0x804E
	  lis       r3, 0x804F
	  subi      r0, r4, 0x5030
	  lis       r4, 0x804F
	  stw       r0, 0x0(r29)
	  subi      r0, r3, 0x1F50
	  lis       r3, 0x804F
	  li        r5, 0
	  stw       r0, 0x0(r29)
	  subi      r4, r4, 0x1FF8
	  subi      r0, r3, 0x2030
	  mr        r3, r29
	  stw       r5, 0x48(r29)
	  stw       r4, 0x0(r29)
	  stb       r30, 0x4C(r29)
	  stw       r0, 0x0(r29)
	  stw       r31, 0x50(r29)
	  lwz       r31, 0x1C(r1)
	  lwz       r30, 0x18(r1)
	  lwz       r29, 0x14(r1)
	  lwz       r0, 0x24(r1)
	  mtlr      r0
	  addi      r1, r1, 0x20
	  blr
	*/
}

/**
 * @note Address: 0x804570E8
 * @note Size: 0x88
 */
void PikminNumberDirector_AutoBgm::directOnTrack(PSSystem::SeqTrackBase& track)
{
	PSAutoBgm::Track* subtrack = getTrack(track);
	PSAutoBgm::AutoBgm* bgm    = static_cast<PSAutoBgm::AutoBgm*>(mDirectedBgm);
	bgm->mMeloArr.mIsActive    = true;

	FOREACH_NODE(JSULink<PSAutoBgm::MeloArrBase>, bgm->mMeloArr.mList.getFirst(), link)
	{
		PSAutoBgm::MeloArrBase* melo = link->getObject();
		bool valid                   = (bool)melo->_18 == 1;
		if (valid) {
			melo->directOn(subtrack);
		}
	}
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r3
	bl getTrack__Q23PSM28PikminNumberDirector_AutoBgmFRQ28PSSystem12SeqTrackBase
	lwz      r4, 0x50(r30)
	li       r0, 1
	mr       r30, r3
	stb      r0, 0x34e(r4)
	lwz      r31, 0x340(r4)
	b        lbl_80457150

lbl_8045711C:
	lwz      r3, 0(r31)
	lbz      r4, 0x18(r3)
	neg      r0, r4
	or       r0, r0, r4
	srwi     r0, r0, 0x1f
	cmplwi   r0, 1
	bne      lbl_8045714C
	lwz      r12, 0x14(r3)
	mr       r4, r30
	lwz      r12, 0x14(r12)
	mtctr    r12
	bctrl

lbl_8045714C:
	lwz      r31, 0xc(r31)

lbl_80457150:
	cmplwi   r31, 0
	bne      lbl_8045711C
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x80457170
 * @note Size: 0x88
 */
void PikminNumberDirector_AutoBgm::directOffTrack(PSSystem::SeqTrackBase& track)
{
	PSAutoBgm::Track* subtrack = getTrack(track);
	PSAutoBgm::AutoBgm* bgm    = static_cast<PSAutoBgm::AutoBgm*>(mDirectedBgm);
	bgm->mMeloArr.mIsActive    = false;

	FOREACH_NODE(JSULink<PSAutoBgm::MeloArrBase>, bgm->mMeloArr.mList.getFirst(), link)
	{
		PSAutoBgm::MeloArrBase* melo = link->getObject();
		bool valid                   = (bool)melo->_18 == 1;
		if (valid) {
			melo->directOff(subtrack);
		}
	}
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r3
	bl getTrack__Q23PSM28PikminNumberDirector_AutoBgmFRQ28PSSystem12SeqTrackBase
	lwz      r4, 0x50(r30)
	li       r0, 0
	mr       r30, r3
	stb      r0, 0x34e(r4)
	lwz      r31, 0x340(r4)
	b        lbl_804571D8

lbl_804571A4:
	lwz      r3, 0(r31)
	lbz      r4, 0x18(r3)
	neg      r0, r4
	or       r0, r0, r4
	srwi     r0, r0, 0x1f
	cmplwi   r0, 1
	bne      lbl_804571D4
	lwz      r12, 0x14(r3)
	mr       r4, r30
	lwz      r12, 0x18(r12)
	mtctr    r12
	bctrl

lbl_804571D4:
	lwz      r31, 0xc(r31)

lbl_804571D8:
	cmplwi   r31, 0
	bne      lbl_804571A4
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x804571F8
 * @note Size: 0xB8
 */
PSAutoBgm::Track* PikminNumberDirector_AutoBgm::getTrack(PSSystem::SeqTrackBase& parent)
{
	PSSystem::TaskEntryMgr* mgr = parent.getTaskEntryList();
	u8 maxTrack                 = (u8)(mgr->mTrack->_348 & 0xf);
	u8 childNum                 = static_cast<PSAutoBgm::AutoBgm*>(mDirectedBgm)->mConductorMgr.mPrmSetRc->getChildNum();
	P2ASSERTLINE(194, childNum < maxTrack);
	PSAutoBgm::Track* track = static_cast<PSAutoBgm::AutoBgm*>(mDirectedBgm)->mConductorMgr.mPrmSetRc->getChild(maxTrack);
	P2ASSERTLINE(196, track);
	return track;

	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	stw      r30, 8(r1)
	mr       r30, r3
	mr       r3, r4
	bl       getTaskEntryList__Q28PSSystem12SeqTrackBaseFv
	lwz      r4, 0x24(r3)
	lwz      r3, 0x50(r30)
	lwz      r0, 0x348(r4)
	lwz      r3, 0x308(r3)
	clrlwi   r0, r0, 0x1c
	mr       r31, r0
	bl       "getChildNum__Q210JADUtility28PrmSetRc<Q29PSAutoBgm5Track>Fv"
	clrlwi   r3, r3, 0x18
	clrlwi   r0, r31, 0x18
	cmplw    r0, r3
	blt      lbl_80457260
	lis      r3, lbl_8049CDBC@ha
	lis      r5, lbl_8049CDD4@ha
	addi     r3, r3, lbl_8049CDBC@l
	li       r4, 0xc2
	addi     r5, r5, lbl_8049CDD4@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80457260:
	lwz      r3, 0x50(r30)
	mr       r4, r31
	lwz      r3, 0x308(r3)
	bl       "getChild__Q210JADUtility28PrmSetRc<Q29PSAutoBgm5Track>FUc"
	or.      r31, r3, r3
	bne      lbl_80457294
	lis      r3, lbl_8049CDBC@ha
	lis      r5, lbl_8049CDD4@ha
	addi     r3, r3, lbl_8049CDBC@l
	li       r4, 0xc4
	addi     r5, r5, lbl_8049CDD4@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80457294:
	lwz      r0, 0x14(r1)
	mr       r3, r31
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/**
 * @note Address: 0x804572B0
 * @note Size: 0x7C
 */
TrackOnDirectorBase::TrackOnDirectorBase(int type, const char* name, s32 in, s32 out)
    : SwitcherDirector(type, name)
    , mFadeInValue(in)
    , mFadeOutValue(out)
    , mEnableType(0)
{
}

/**
 * @note Address: 0x8045732C
 * @note Size: 0x34
 */
void TrackOnDirectorBase::onPlayInit(JASTrack* track)
{
	track->_358 |= 0x60;
	track->muteTrack(true);
}

/**
 * @note Address: 0x80457360
 * @note Size: 0x50
 */
void TrackOnDirectorBase::directOnTrack(PSSystem::SeqTrackBase& seqTrack)
{
	if (mEnableType) {
		static_cast<PSSystem::SeqTrackChild&>(seqTrack).muteOffAndFadeIn(0.0f, 0, this);
	} else {
		static_cast<PSSystem::SeqTrackChild&>(seqTrack).muteOffAndFadeIn(1.0f, mFadeInValue, this);
	}
}

/**
 * @note Address: 0x804573B0
 * @note Size: 0x2C
 */
void TrackOnDirectorBase::directOffTrack(PSSystem::SeqTrackBase& seqTrack)
{
	static_cast<PSSystem::SeqTrackChild&>(seqTrack).fadeoutAndMute(mFadeOutValue, this);
}

/**
 * @note Address: 0x804573DC
 * @note Size: 0x90
 */
void TrackOnDirector_Voting::execInner()
{
	if (mVoteState == 0 && isUnderDirection()) {
		directOff();
	} else if (mVoteState != 0 && !isUnderDirection()) {
		directOn();
	}
	mVoteState = 0;
}

/**
 * @note Address: 0x804574FC
 * @note Size: 0xFC
 */
void TrackOnDirector_Scaled::underDirection()
{
	f32 rate = 1.0f;
	if (!PSSystem::DirectorBase::sToolMode) {
		rate          = getNearestDistance();
		mCurrDistance = rate;
		rate          = JALCalc::linearTransform(mCurrDistance, _58, _54, 0.0f, 1.0f, false);
	}

	fadeAllTracks(rate, _60);
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stfd     f31, 0x20(r1)
	psq_st   f31, 40(r1), 0, qr0
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	stw      r28, 0x10(r1)
	lbz      r0, sToolMode__Q28PSSystem12DirectorBase@sda21(r13)
	mr       r28, r3
	lfs      f31, lbl_80520C08@sda21(r2)
	cmplwi   r0, 0
	bne      lbl_80457568
	lwz      r12, 0(r3)
	lwz      r12, 0x38(r12)
	mtctr    r12
	bctrl
	stfs     f1, 0x5c(r28)
	li       r3, 0
	lfs      f4, lbl_80520C10@sda21(r2)
	lfs      f1, 0x5c(r28)
	lfs      f2, 0x58(r28)
	lfs      f3, 0x54(r28)
	lfs      f5, lbl_80520C08@sda21(r2)
	bl       linearTransform__7JALCalcFfffffb
	fmr      f31, f1

lbl_80457568:
	lis      r4, lbl_8049CDE0@ha
	lis      r3, lbl_8049CDD4@ha
	addi     r30, r4, lbl_8049CDE0@l
	li       r29, 0
	addi     r31, r3, lbl_8049CDD4@l
	b        lbl_804575C0

lbl_80457580:
	clrlwi   r0, r29, 0x18
	cmplw    r0, r3
	blt      lbl_804575A0
	mr       r3, r30
	mr       r5, r31
	li       r4, 0x33
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_804575A0:
	lwz      r3, 4(r28)
	rlwinm   r0, r29, 2, 0x16, 0x1d
	fmr      f1, f31
	lwz      r4, 0x60(r28)
	lwzx     r3, r3, r0
	li       r5, 0
	bl       fade__Q28PSSystem13SeqTrackChildFfUlPQ28PSSystem12DirectorBase
	addi     r29, r29, 1

lbl_804575C0:
	lbz      r3, 0x41(r28)
	clrlwi   r0, r29, 0x18
	cmplw    r0, r3
	blt      lbl_80457580
	psq_l    f31, 40(r1), 0, qr0
	lwz      r0, 0x34(r1)
	lfd      f31, 0x20(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/**
 * @note Address: 0x804575F8
 * @note Size: 0x8C
 */
void ListDirectorActor::onUpdateFromMasterD()
{
	if (!mHead && mDirectorChild->isUnderDirection()) {
		mDirectorChild->directOff();
	} else if (mHead && !mDirectorChild->isUnderDirection()) {
		mDirectorChild->directOn();
	}
}

/**
 * @note Address: 0x80457684
 * @note Size: 0x98
 */
ActorDirector_TrackOn::ActorDirector_TrackOn(const char* p1, int p2, s32 p3, s32 p4)
    : TrackOnDirectorBase(p2, p1, p3, p4)
    , mActor(nullptr)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	mr       r0, r4
	mr       r4, r5
	stw      r31, 0x1c(r1)
	mr       r31, r7
	mr       r5, r0
	stw      r30, 0x18(r1)
	mr       r30, r6
	stw      r29, 0x14(r1)
	mr       r29, r3
	bl       __ct__Q28PSSystem12DirectorBaseFiPCc
	lis      r4, __vt__Q28PSSystem16SwitcherDirector@ha
	lis      r3, __vt__Q23PSM16SwitcherDirector@ha
	addi     r0, r4, __vt__Q28PSSystem16SwitcherDirector@l
	lis      r4, __vt__Q23PSM19TrackOnDirectorBase@ha
	stw      r0, 0(r29)
	addi     r0, r3, __vt__Q23PSM16SwitcherDirector@l
	lis      r3, __vt__Q23PSM21ActorDirector_TrackOn@ha
	addi     r5, r4, __vt__Q23PSM19TrackOnDirectorBase@l
	stw      r0, 0(r29)
	li       r4, 0
	addi     r0, r3, __vt__Q23PSM21ActorDirector_TrackOn@l
	mr       r3, r29
	stw      r5, 0(r29)
	stw      r30, 0x48(r29)
	stw      r31, 0x4c(r29)
	stb      r4, 0x50(r29)
	stw      r4, 0x54(r29)
	stw      r0, 0(r29)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/**
 * @note Address: 0x8045771C
 * @note Size: 0x3C
 */
void ActorDirector_TrackOn::execInner()
{
	if (mActor) {
		mActor->exec(this);
	}
}

/**
 * @note Address: 0x80457758
 * @note Size: 0xF4
 */
ActorDirector_Scaled::ActorDirector_Scaled(const char* name, int p2, f32 p3, f32 p4, s32 p5, s32 p6, u32 p7)
    : TrackOnDirector_Scaled(name, p2, p3, p4, p5, p6, p7)
{
}

/**
 * @note Address: 0x804578EC
 * @note Size: 0x3C
 */
void ActorDirector_Scaled::execInner()
{
	if (mActor) {
		mActor->exec(this);
	}
}

/**
 * @note Address: 0x80457928
 * @note Size: 0x614
 */
f32 ActorDirector_Scaled::getNearestDistance()
{
	bool is1P   = PSSystem::SingletonBase<PSM::ObjCalcBase>::getInstance()->is1PGame();
	f32 minDist = 100000.0f;
	if (!is1P) {
		Game::Navi* olimar = Game::naviMgr->getAt(NAVIID_Captain1);
		Game::Navi* louie  = Game::naviMgr->getAt(NAVIID_Captain2);
		P2ASSERTBOOLLINE(394, olimar && louie);

		Vector3f oPos = olimar->getPosition();
		Vector3f lPos = louie->getPosition();

		FOREACH_NODE(JSULink<Game::Creature>, mActor->getFirst(), link)
		{
			Game::Creature* obj = link->getObject();
			Vector3f objpos     = obj->getPosition();
			f32 p1Dist          = oPos.distance(objpos);
			f32 p2Dist          = lPos.distance(objpos);
			if (p1Dist <= p2Dist) {
				if (p1Dist < minDist) {
					onSetMinDistObj(obj);
					minDist = p1Dist;
				}
			} else if (p2Dist < minDist) {
				onSetMinDistObj(obj);
				minDist = p2Dist;
			}
		}

	} else {
		Game::Navi* navi = Game::naviMgr->getActiveNavi();
		Vector3f naviPos;
		if (!navi) {
			u8 id                = PSSystem::SingletonBase<PSM::ObjCalcBase>::sInstance->getPlayerNo(nullptr);
			JAInter::Camera* cam = &JAIBasic::msBasic->mCameras[id];
			naviPos              = (*cam->mVec1);
		} else {
			naviPos = navi->getPosition();
		}

		FOREACH_NODE(JSULink<Game::Creature>, mActor->getFirst(), link)
		{
			Game::Creature* obj = link->getObject();
			Vector3f objpos     = obj->getPosition();
			f32 dist            = naviPos.distance(objpos);
			if (dist < minDist) {
				minDist = dist;
				onSetMinDistObj(obj);
			}
		}
	}
	/*
	stwu     r1, -0x1d0(r1)
	mflr     r0
	stw      r0, 0x1d4(r1)
	stfd     f31, 0x1c0(r1)
	psq_st   f31, 456(r1), 0, qr0
	stfd     f30, 0x1b0(r1)
	psq_st   f30, 440(r1), 0, qr0
	stfd     f29, 0x1a0(r1)
	psq_st   f29, 424(r1), 0, qr0
	stfd     f28, 0x190(r1)
	psq_st   f28, 408(r1), 0, qr0
	stfd     f27, 0x180(r1)
	psq_st   f27, 392(r1), 0, qr0
	stfd     f26, 0x170(r1)
	psq_st   f26, 376(r1), 0, qr0
	stfd     f25, 0x160(r1)
	psq_st   f25, 360(r1), 0, qr0
	stfd     f24, 0x150(r1)
	psq_st   f24, 344(r1), 0, qr0
	stw      r31, 0x14c(r1)
	stw      r30, 0x148(r1)
	stw      r29, 0x144(r1)
	stw      r28, 0x140(r1)
	lwz      r0,
"sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13) lis r4,
lbl_8049CD98@ha mr       r30, r3 cmplwi   r0, 0 addi     r31, r4, lbl_8049CD98@l
	bne      lbl_804579B0
	addi     r3, r31, 0x58
	addi     r5, r31, 0x3c
	li       r4, 0x89
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_804579B0:
	lwz      r3,
"sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13) lwz r12,
0(r3) lwz      r12, 0x18(r12) mtctr    r12 bctrl clrlwi.  r0, r3, 0x18 lfs f24,
lbl_80520C18@sda21(r2) bne      lbl_80457D14 lwz      r3,
naviMgr__4Game@sda21(r13) li       r4, 0 lwz      r12, 0(r3) lwz      r12,
0x24(r12) mtctr    r12 bctrl mr       r0, r3 lwz      r3,
naviMgr__4Game@sda21(r13) mr       r29, r0 li       r4, 1 lwz      r12, 0(r3)
	lwz      r12, 0x24(r12)
	mtctr    r12
	bctrl
	cmplwi   r29, 0
	mr       r28, r3
	li       r0, 0
	beq      lbl_80457A24
	cmplwi   r28, 0
	beq      lbl_80457A24
	li       r0, 1

lbl_80457A24:
	clrlwi.  r0, r0, 0x18
	bne      lbl_80457A40
	addi     r3, r31, 0x24
	addi     r5, r31, 0x3c
	li       r4, 0x18a
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80457A40:
	mr       r4, r29
	addi     r3, r1, 0x134
	lwz      r12, 0(r29)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	mr       r4, r28
	addi     r3, r1, 0x128
	lwz      r12, 0(r28)
	lfs      f30, 0x134(r1)
	lwz      r12, 8(r12)
	lfs      f29, 0x138(r1)
	lfs      f28, 0x13c(r1)
	mtctr    r12
	bctrl
	lwz      r3, 0x64(r30)
	lfs      f27, 0x128(r1)
	cmplwi   r3, 0
	lfs      f26, 0x12c(r1)
	lfs      f25, 0x130(r1)
	beq      lbl_80457A98
	addi     r3, r3, 0xc

lbl_80457A98:
	lwz      r31, 0(r3)
	lfs      f31, lbl_80520C10@sda21(r2)
	b        lbl_80457D08

lbl_80457AA4:
	lwz      r4, 0(r31)
	addi     r3, r1, 0x11c
	lwz      r12, 0(r4)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f1, 0x120(r1)
	lfs      f0, 0x11c(r1)
	stfs     f30, 0xa4(r1)
	lfs      f2, 0x124(r1)
	stfs     f29, 0xa8(r1)
	lwz      r0, 0xa4(r1)
	stfs     f0, 0xb0(r1)
	lwz      r6, 0xa8(r1)
	stfs     f1, 0xb4(r1)
	lwz      r4, 0xb0(r1)
	lwz      r3, 0xb4(r1)
	stfs     f28, 0xac(r1)
	lfs      f0, 0x11c(r1)
	stfs     f2, 0xb8(r1)
	lwz      r5, 0xac(r1)
	stw      r0, 0x104(r1)
	lwz      r0, 0xb8(r1)
	stw      r6, 0x108(r1)
	lfs      f5, 0x104(r1)
	stw      r4, 0x110(r1)
	lfs      f3, 0x108(r1)
	stw      r3, 0x114(r1)
	lfs      f6, 0x110(r1)
	lfs      f4, 0x114(r1)
	stw      r5, 0x10c(r1)
	fsubs    f6, f6, f5
	fsubs    f5, f4, f3
	stw      r0, 0x118(r1)
	lfs      f3, 0x10c(r1)
	lfs      f4, 0x118(r1)
	stfs     f6, 0x68(r1)
	fsubs    f3, f4, f3
	stfs     f5, 0x6c(r1)
	lwz      r0, 0x68(r1)
	lwz      r3, 0x6c(r1)
	stfs     f3, 0x70(r1)
	stw      r0, 0x50(r1)
	lwz      r0, 0x70(r1)
	stw      r3, 0x54(r1)
	lfs      f4, 0x50(r1)
	lfs      f3, 0x54(r1)
	stw      r0, 0x58(r1)
	fmuls    f5, f4, f4
	fmuls    f4, f3, f3
	lfs      f3, 0x58(r1)
	stfs     f5, 0x50(r1)
	fmuls    f3, f3, f3
	stfs     f4, 0x54(r1)
	lwz      r0, 0x50(r1)
	lwz      r3, 0x54(r1)
	stfs     f3, 0x58(r1)
	stw      r0, 0x5c(r1)
	lwz      r0, 0x58(r1)
	stw      r3, 0x60(r1)
	lfs      f4, 0x5c(r1)
	lfs      f3, 0x60(r1)
	stw      r0, 0x64(r1)
	fadds    f3, f4, f3
	lfs      f4, 0x64(r1)
	fadds    f4, f4, f3
	fcmpo    cr0, f4, f31
	ble      lbl_80457BBC
	frsqrte  f3, f4
	fmuls    f4, f3, f4

lbl_80457BBC:
	stfs     f27, 0x8c(r1)
	stfs     f26, 0x90(r1)
	lwz      r0, 0x8c(r1)
	stfs     f0, 0x98(r1)
	lwz      r6, 0x90(r1)
	stfs     f1, 0x9c(r1)
	lwz      r4, 0x98(r1)
	lwz      r3, 0x9c(r1)
	stfs     f25, 0x94(r1)
	stfs     f2, 0xa0(r1)
	lwz      r5, 0x94(r1)
	stw      r0, 0xec(r1)
	lwz      r0, 0xa0(r1)
	stw      r6, 0xf0(r1)
	lfs      f2, 0xec(r1)
	stw      r4, 0xf8(r1)
	lfs      f0, 0xf0(r1)
	stw      r3, 0xfc(r1)
	lfs      f3, 0xf8(r1)
	lfs      f1, 0xfc(r1)
	stw      r5, 0xf4(r1)
	fsubs    f3, f3, f2
	fsubs    f2, f1, f0
	stw      r0, 0x100(r1)
	lfs      f0, 0xf4(r1)
	lfs      f1, 0x100(r1)
	stfs     f3, 0x44(r1)
	fsubs    f0, f1, f0
	stfs     f2, 0x48(r1)
	lwz      r0, 0x44(r1)
	lwz      r3, 0x48(r1)
	stfs     f0, 0x4c(r1)
	stw      r0, 0x2c(r1)
	lwz      r0, 0x4c(r1)
	stw      r3, 0x30(r1)
	lfs      f1, 0x2c(r1)
	lfs      f0, 0x30(r1)
	stw      r0, 0x34(r1)
	fmuls    f2, f1, f1
	fmuls    f1, f0, f0
	lfs      f0, 0x34(r1)
	stfs     f2, 0x2c(r1)
	fmuls    f0, f0, f0
	stfs     f1, 0x30(r1)
	lwz      r0, 0x2c(r1)
	lwz      r3, 0x30(r1)
	stfs     f0, 0x34(r1)
	stw      r0, 0x38(r1)
	lwz      r0, 0x34(r1)
	stw      r3, 0x3c(r1)
	lfs      f1, 0x38(r1)
	lfs      f0, 0x3c(r1)
	stw      r0, 0x40(r1)
	fadds    f0, f1, f0
	lfs      f1, 0x40(r1)
	fadds    f0, f1, f0
	fcmpo    cr0, f0, f31
	ble      lbl_80457CAC
	frsqrte  f1, f0
	fmuls    f0, f1, f0

lbl_80457CAC:
	fcmpo    cr0, f4, f0
	cror     2, 0, 2
	bne      lbl_80457CE0
	fcmpo    cr0, f4, f24
	bge      lbl_80457D04
	mr       r3, r30
	fmr      f24, f4
	lwz      r12, 0(r30)
	lwz      r4, 0(r31)
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl
	b        lbl_80457D04

lbl_80457CE0:
	fcmpo    cr0, f0, f24
	bge      lbl_80457D04
	mr       r3, r30
	fmr      f24, f0
	lwz      r12, 0(r30)
	lwz      r4, 0(r31)
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl

lbl_80457D04:
	lwz      r31, 0xc(r31)

lbl_80457D08:
	cmplwi   r31, 0
	bne      lbl_80457AA4
	b        lbl_80457ED8

lbl_80457D14:
	lwz      r3, naviMgr__4Game@sda21(r13)
	bl       getActiveNavi__Q24Game7NaviMgrFv
	cmplwi   r3, 0
	bne      lbl_80457D60
	lwz      r3,
"sInstance__Q28PSSystem34SingletonBase<Q23PSM11ObjCalcBase>"@sda21(r13) li r4, 0
	lwz      r12, 0(r3)
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	lwz      r3, msBasic__8JAIBasic@sda21(r13)
	mulli    r0, r0, 0xc
	lwz      r3, 4(r3)
	lwzx     r3, r3, r0
	lfs      f25, 0(r3)
	lfs      f26, 4(r3)
	lfs      f27, 8(r3)
	b        lbl_80457D84

lbl_80457D60:
	mr       r4, r3
	addi     r3, r1, 0xe0
	lwz      r12, 0(r4)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f25, 0xe0(r1)
	lfs      f26, 0xe4(r1)
	lfs      f27, 0xe8(r1)

lbl_80457D84:
	lwz      r3, 0x64(r30)
	lfs      f28, lbl_80520C10@sda21(r2)
	lwz      r31, 0xc(r3)
	b        lbl_80457ED0

lbl_80457D94:
	lwz      r4, 0(r31)
	addi     r3, r1, 0xd4
	lwz      r12, 0(r4)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f2, 0xd4(r1)
	lfs      f1, 0xd8(r1)
	stfs     f25, 0x74(r1)
	lfs      f0, 0xdc(r1)
	stfs     f26, 0x78(r1)
	lwz      r0, 0x74(r1)
	stfs     f2, 0x80(r1)
	lwz      r6, 0x78(r1)
	stfs     f1, 0x84(r1)
	lwz      r4, 0x80(r1)
	lwz      r3, 0x84(r1)
	stfs     f27, 0x7c(r1)
	stfs     f0, 0x88(r1)
	lwz      r5, 0x7c(r1)
	stw      r0, 0xbc(r1)
	lwz      r0, 0x88(r1)
	stw      r6, 0xc0(r1)
	lfs      f2, 0xbc(r1)
	stw      r4, 0xc8(r1)
	lfs      f0, 0xc0(r1)
	stw      r3, 0xcc(r1)
	lfs      f3, 0xc8(r1)
	lfs      f1, 0xcc(r1)
	stw      r5, 0xc4(r1)
	fsubs    f3, f3, f2
	fsubs    f2, f1, f0
	stw      r0, 0xd0(r1)
	lfs      f0, 0xc4(r1)
	lfs      f1, 0xd0(r1)
	stfs     f3, 0x20(r1)
	fsubs    f0, f1, f0
	stfs     f2, 0x24(r1)
	lwz      r0, 0x20(r1)
	lwz      r3, 0x24(r1)
	stfs     f0, 0x28(r1)
	stw      r0, 8(r1)
	lwz      r0, 0x28(r1)
	stw      r3, 0xc(r1)
	lfs      f1, 8(r1)
	lfs      f0, 0xc(r1)
	stw      r0, 0x10(r1)
	fmuls    f2, f1, f1
	fmuls    f1, f0, f0
	lfs      f0, 0x10(r1)
	stfs     f2, 8(r1)
	fmuls    f0, f0, f0
	stfs     f1, 0xc(r1)
	lwz      r0, 8(r1)
	lwz      r3, 0xc(r1)
	stfs     f0, 0x10(r1)
	stw      r0, 0x14(r1)
	lwz      r0, 0x10(r1)
	stw      r3, 0x18(r1)
	lfs      f1, 0x14(r1)
	lfs      f0, 0x18(r1)
	stw      r0, 0x1c(r1)
	fadds    f0, f1, f0
	lfs      f1, 0x1c(r1)
	fadds    f0, f1, f0
	fcmpo    cr0, f0, f28
	ble      lbl_80457EA8
	frsqrte  f1, f0
	fmuls    f0, f1, f0

lbl_80457EA8:
	fcmpo    cr0, f0, f24
	bge      lbl_80457ECC
	mr       r3, r30
	fmr      f24, f0
	lwz      r12, 0(r30)
	lwz      r4, 0(r31)
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl

lbl_80457ECC:
	lwz      r31, 0xc(r31)

lbl_80457ED0:
	cmplwi   r31, 0
	bne      lbl_80457D94

lbl_80457ED8:
	fmr      f1, f24
	psq_l    f31, 456(r1), 0, qr0
	lfd      f31, 0x1c0(r1)
	psq_l    f30, 440(r1), 0, qr0
	lfd      f30, 0x1b0(r1)
	psq_l    f29, 424(r1), 0, qr0
	lfd      f29, 0x1a0(r1)
	psq_l    f28, 408(r1), 0, qr0
	lfd      f28, 0x190(r1)
	psq_l    f27, 392(r1), 0, qr0
	lfd      f27, 0x180(r1)
	psq_l    f26, 376(r1), 0, qr0
	lfd      f26, 0x170(r1)
	psq_l    f25, 360(r1), 0, qr0
	lfd      f25, 0x160(r1)
	psq_l    f24, 344(r1), 0, qr0
	lfd      f24, 0x150(r1)
	lwz      r31, 0x14c(r1)
	lwz      r30, 0x148(r1)
	lwz      r29, 0x144(r1)
	lwz      r0, 0x1d4(r1)
	lwz      r28, 0x140(r1)
	mtlr     r0
	addi     r1, r1, 0x1d0
	blr
	*/
}

/**
 * @note Address: 0x80457F3C
 * @note Size: 0xE4
 */
ActorDirector_Enemy::ActorDirector_Enemy(const char* name, int p2, s32 p3, s32 p4, u32 p5)
    : ActorDirector_Scaled(name, p2, 1.0f, 0.0f, p3, p4, p5)
    , mGameObject(nullptr)
{
}

/**
 * @note Address: 0x804580D0
 * @note Size: 0x8
 */
void ActorDirector_Enemy::onSetMinDistObj(Game::Creature* obj) { mGameObject = static_cast<Game::EnemyBase*>(obj); }

/**
 * @note Address: 0x804580D8
 * @note Size: 0x1D0
 */
void ActorDirector_Enemy::underDirection()
{
	mGameObject = nullptr;
	f32 rate    = 1.0f;
	if (!PSSystem::DirectorBase::sToolMode) {
		if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::PIKLOPEDIA) {
			rate = 1.0f;
		} else {
			rate          = getNearestDistance();
			mCurrDistance = rate;
			rate = JALCalc::linearTransform(mCurrDistance, getVolZeroDist(mGameObject), getVolMaxDist(mGameObject), 0.0f, 1.0f, false);
		}
	}

	fadeAllTracks(rate, _60);

	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stfd     f31, 0x20(r1)
	psq_st   f31, 40(r1), 0, qr0
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r3
	li       r0, 0
	stw      r0, 0x68(r3)
	lis      r3, lbl_8049CD98@ha
	lfs      f31, lbl_80520C08@sda21(r2)
	addi     r31, r3, lbl_8049CD98@l
	lbz      r0, sToolMode__Q28PSSystem12DirectorBase@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_8045822C
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_8045813C
	addi     r3, r31, 0x64
	addi     r5, r31, 0x3c
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045813C:
	lwz      r30, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r30, 0
	bne      lbl_8045815C
	addi     r3, r31, 0x64
	addi     r5, r31, 0x3c
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045815C:
	lwz      r0, 4(r30)
	cmplwi   r0, 0
	bne      lbl_8045817C
	addi     r3, r31, 0x70
	addi     r5, r31, 0x3c
	li       r4, 0xcf
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_8045817C:
	lwz      r3, 4(r30)
	lwz      r30, 4(r3)
	cmplwi   r30, 0
	bne      lbl_804581A0
	addi     r3, r31, 0x70
	addi     r5, r31, 0x7c
	li       r4, 0xd1
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_804581A0:
	mr       r3, r30
	bl       getSceneInfoA__Q23PSM9SceneBaseFv
	lbz      r0, 6(r3)
	cmplwi   r0, 0xd
	bne      lbl_804581BC
	lfs      f31, lbl_80520C08@sda21(r2)
	b        lbl_8045822C

lbl_804581BC:
	mr       r3, r29
	lwz      r12, 0(r29)
	lwz      r12, 0x38(r12)
	mtctr    r12
	bctrl
	stfs     f1, 0x5c(r29)
	mr       r3, r29
	lwz      r12, 0(r29)
	lwz      r4, 0x68(r29)
	lwz      r12, 0x40(r12)
	mtctr    r12
	bctrl
	lwz      r12, 0(r29)
	fmr      f31, f1
	mr       r3, r29
	lwz      r4, 0x68(r29)
	lwz      r12, 0x44(r12)
	mtctr    r12
	bctrl
	fmr      f0, f1
	lfs      f1, 0x5c(r29)
	fmr      f2, f31
	lfs      f4, lbl_80520C10@sda21(r2)
	lfs      f5, lbl_80520C08@sda21(r2)
	li       r3, 0
	fmr      f3, f0
	bl       linearTransform__7JALCalcFfffffb
	fmr      f31, f1

lbl_8045822C:
	li       r30, 0
	b        lbl_80458274

lbl_80458234:
	clrlwi   r0, r30, 0x18
	cmplw    r0, r3
	blt      lbl_80458254
	addi     r3, r31, 0x48
	addi     r5, r31, 0x3c
	li       r4, 0x33
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80458254:
	lwz      r3, 4(r29)
	rlwinm   r0, r30, 2, 0x16, 0x1d
	fmr      f1, f31
	lwz      r4, 0x60(r29)
	lwzx     r3, r3, r0
	li       r5, 0
	bl       fade__Q28PSSystem13SeqTrackChildFfUlPQ28PSSystem12DirectorBase
	addi     r30, r30, 1

lbl_80458274:
	lbz      r3, 0x41(r29)
	clrlwi   r0, r30, 0x18
	cmplw    r0, r3
	blt      lbl_80458234
	psq_l    f31, 40(r1), 0, qr0
	lwz      r0, 0x34(r1)
	lfd      f31, 0x20(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/**
 * @note Address: 0x804582A8
 * @note Size: 0x44
 */
f64 ActorDirector_Battle::getVolZeroDist(Game::EnemyBase* enemy)
{
	int id = enemy->mSoundObj->getCastType() - 2;
	return CreaturePrm::cVolZeroDist_Battle[id];
}

/**
 * @note Address: 0x804582EC
 * @note Size: 0x44
 */
f64 ActorDirector_Battle::getVolMaxDist(Game::EnemyBase* enemy)
{
	int id = enemy->mSoundObj->getCastType() - 2;
	return CreaturePrm::cVolMaxDist_Battle[id];
}

/**
 * @note Address: 0x80458330
 * @note Size: 0x44
 */
f64 ActorDirector_Kehai::getVolZeroDist(Game::EnemyBase* enemy)
{
	int id = enemy->mSoundObj->getCastType() - 2;
	return CreaturePrm::cVolZeroDist_Kehai[id];
}

/**
 * @note Address: 0x80458374
 * @note Size: 0x44
 */
f64 ActorDirector_Kehai::getVolMaxDist(Game::EnemyBase* enemy)
{
	int id = enemy->mSoundObj->getCastType() - 2;
	return CreaturePrm::cVolMaxDist_Kehai[id];
}

// exists here but doesnt seem to be used by any panics
static const char* unusedpath = "PSMainSide_ObjSound.h";

/**
 * @note Address: 0x804583B8
 * @note Size: 0x7C
 */
PikAttackDirector::PikAttackDirector(int p1)
    : TrackOnDirectorBase(p1, "pikatkD  ", 100, 100)
{
}

/**
 * @note Address: 0x80458434
 * @note Size: 0x7C
 */
ExiteDirector::ExiteDirector(int p1)
    : TrackOnDirectorBase(p1, "tentionD ", 100, 100)
{
}

/**
 * @note Address: 0x804584B0
 * @note Size: 0x68
 */
DirectorUpdator::DirectorUpdator(PSSystem::DirectorBase* director, u8 number, PSM::DirectorUpdator::Type type)
    : mUpdateNum(number)
    , mType(type)
    , _08(0)
    , _09(0)
    , mDirector(director)
{
	P2ASSERTLINE(698, number != 0);
}

/**
 * @note Address: 0x80458518
 * @note Size: 0x34
 */
void DirectorUpdator::directOn(u8 id)
{
	if (_09 & 1) {
		return;
	}
	id = 1 << id;
	_08 |= id;
	_09 |= id;
	/*
	clrlwi   r0, r4, 0x18
	li       r4, 1
	lbz      r5, 9(r3)
	slw      r4, r4, r0
	and.     r0, r5, r4
	bnelr
	lbz      r0, 8(r3)
	or       r0, r0, r4
	stb      r0, 8(r3)
	lbz      r0, 9(r3)
	or       r0, r0, r4
	stb      r0, 9(r3)
	blr
	*/
}

/**
 * @note Address: 0x8045854C
 * @note Size: 0x34
 */
void DirectorUpdator::directOff(u8 id)
{
	if (_09 & 1) {
		return;
	}
	id = 1 << id;
	_08 &= ~id;
	_09 |= id;
	/*
	clrlwi   r0, r4, 0x18
	li       r4, 1
	lbz      r5, 9(r3)
	slw      r4, r4, r0
	and.     r0, r5, r4
	bnelr
	lbz      r0, 8(r3)
	andc     r0, r0, r4
	stb      r0, 8(r3)
	lbz      r0, 9(r3)
	or       r0, r0, r4
	stb      r0, 9(r3)
	blr
	*/
}

/**
 * @note Address: 0x80458580
 * @note Size: 0x12C
 */
void DirectorUpdator::frameEndWork()
{
	if (mDirector) {
		bool end = false;
		switch (mType) {
		case PSM::DirectorUpdator::TYPE_0:
			for (u8 i = 0; i < mUpdateNum; i++) {
				if (_08 & 1 << i) {
					end = true;
					break;
				}
			}
			break;
		case PSM::DirectorUpdator::TYPE_1:
			end = true;
			for (u8 i = 0; i < mUpdateNum; i++) {
				if (!(_08 & 1 << i)) {
					end = false;
					break;
				}
			}
			break;
		}

		if (end) {
			if (!mDirector->isUnderDirection()) {
				mDirector->directOn();
			}
		} else {
			if (mDirector->isUnderDirection()) {
				mDirector->directOff();
			}
		}
		_08 = 0;
		_09 = 0;
	}
}

} // namespace PSM

/**
 * @note Address: 0x804586AC
 * @note Size: 0x148
 */
PSSystem::DirectorBase* PSMGetBattleDirector(u8 flag)
{
	PSM::MiddleBossSeq* seq = PSMGetMiddleBossSeq();
	if (!seq) {
		return nullptr;
	}
	P2ASSERTBOOLLINE(810, seq->getCastType() == 2 || seq->getCastType() == 4);
	return seq->getDirectorP(flag);
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, lbl_8049CD98@ha
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	addi     r30, r4, lbl_8049CD98@l
	stw      r29, 0x14(r1)
	stw      r28, 0x10(r1)
	mr       r28, r3
	lwz      r0, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r0, 0
	bne      lbl_804586F4
	addi     r3, r30, 0x64
	addi     r5, r30, 0x3c
	li       r4, 0x1d3
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_804586F4:
	lwz      r29, spSceneMgr__8PSSystem@sda21(r13)
	cmplwi   r29, 0
	bne      lbl_80458714
	addi     r3, r30, 0x64
	addi     r5, r30, 0x3c
	li       r4, 0x1dc
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80458714:
	lwz      r0, 4(r29)
	cmplwi   r0, 0
	bne      lbl_80458734
	addi     r3, r30, 0x70
	addi     r5, r30, 0x3c
	li       r4, 0xc7
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80458734:
	lwz      r3, 4(r29)
	lwz      r3, 4(r3)
	cmplwi   r3, 0
	bne      lbl_8045874C
	li       r29, 0
	b        lbl_80458754

lbl_8045874C:
	bl       getMiddleBossBgm__Q26PSGame8PikSceneFv
	mr       r29, r3

lbl_80458754:
	cmplwi   r29, 0
	bne      lbl_80458764
	li       r3, 0
	b        lbl_804587D4

lbl_80458764:
	mr       r3, r29
	li       r31, 0
	lwz      r12, 0x10(r29)
	lwz      r12, 0x24(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 2
	beq      lbl_804587A8
	mr       r3, r29
	lwz      r12, 0x10(r29)
	lwz      r12, 0x24(r12)
	mtctr    r12
	bctrl
	clrlwi   r0, r3, 0x18
	cmplwi   r0, 4
	bne      lbl_804587AC

lbl_804587A8:
	li       r31, 1

lbl_804587AC:
	clrlwi.  r0, r31, 0x18
	bne      lbl_804587C8
	addi     r3, r30, 0x24
	addi     r5, r30, 0x3c
	li       r4, 0x32a
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_804587C8:
	mr       r3, r29
	mr       r4, r28
	bl       getDirectorP__Q28PSSystem11DirectedBgmFUc

lbl_804587D4:
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/**
 * @note Address: 0x804587F4
 * @note Size: 0x108
 */
PSM::ActorDirector_Kehai* PSMGetKehaiD()
{
	if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_Kehai*>(bgm->getDirectorP(1));
		}
		return nullptr;
	} else {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_Kehai*>(bgm->getDirectorP(2));
		}
		return nullptr;
	}
}

/**
 * @note Address: 0x804588FC
 * @note Size: 0x108
 */
PSM::ActorDirector_Battle* PSMGetBattleD()
{
	if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_Battle*>(bgm->getDirectorP(2));
		}
		return nullptr;
	} else {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_Battle*>(bgm->getDirectorP(3));
		}
		return nullptr;
	}
}

/**
 * @note Address: 0x80458A04
 * @note Size: 0x108
 */
PSM::ActorDirector_Scaled* PSMGetEventD()
{
	if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_Battle*>(bgm->getDirectorP(0));
		}
		return nullptr;
	} else {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_Battle*>(bgm->getDirectorP(0));
		}
		return nullptr;
	}
}

/**
 * @note Address: 0x80458B0C
 * @note Size: 0xF0
 */
PSM::ActorDirector_TrackOn* PSMGetOtakaraEventD()
{
	if (PSGameGetSceneInfo()->mSceneType != PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_TrackOn*>(bgm->getDirectorP(1));
		}
		return nullptr;
	}
	return nullptr;
}

/**
 * @note Address: 0x80458BFC
 * @note Size: 0x194
 */
PSM::ActorDirector_Scaled* PSMGetGroundD()
{
	if (PSGameGetSceneInfo()->mSceneType != PSGame::SceneInfo::TWO_PLAYER_BATTLE && !PSGameGetSceneInfo()->isCaveFloor()) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_Scaled*>(bgm->getDirectorP(4));
		}
		return nullptr;
	}

	return nullptr;
}

/**
 * @note Address: 0x80458D90
 * @note Size: 0xF0
 */
PSM::PikminNumberDirector* PSMGetPikminNumD()
{
	if (PSGameGetSceneInfo()->mSceneType != PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::PikminNumberDirector*>(bgm->getDirectorP(5));
		}
		return nullptr;
	}
	return nullptr;
}

/**
 * @note Address: 0x80458E80
 * @note Size: 0xF0
 */
PSM::DamageDirector* PSMGetDamageD()
{
	if (PSGameGetSceneInfo()->mSceneType != PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::DamageDirector*>(bgm->getDirectorP(6));
		}
		return nullptr;
	}
	return nullptr;
}

/**
 * @note Address: 0x80458F70
 * @note Size: 0xF0
 */
PSM::ActorDirector_TempoChange* PSMGetLifeD()
{
	if (PSGameGetSceneInfo()->mSceneType != PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_TempoChange*>(bgm->getDirectorP(7));
		}
		return nullptr;
	}
	return nullptr;
}

/**
 * @note Address: 0x80459060
 * @note Size: 0xF0
 */
PSM::ActorDirector_TrackOn* PSMGetBeedamaForOrimerD()
{
	if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_TrackOn*>(bgm->getDirectorP(3));
		}
		return nullptr;
	}
	return nullptr;
}

/**
 * @note Address: 0x80459150
 * @note Size: 0xF0
 */
PSM::ActorDirector_TrackOn* PSMGetBeedamaForLugieD()
{
	if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_TrackOn*>(bgm->getDirectorP(4));
		}
		return nullptr;
	}
	return nullptr;
}

/**
 * @note Address: 0x80459240
 * @note Size: 0xF0
 */
PSM::ActorDirector_TrackOn* PSMGetIchouForOrimerD()
{
	if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_TrackOn*>(bgm->getDirectorP(5));
		}
		return nullptr;
	}
	return nullptr;
}

/**
 * @note Address: 0x80459330
 * @note Size: 0xF0
 */
PSM::ActorDirector_TrackOn* PSMGetIchouForLugieD()
{
	if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::ActorDirector_TrackOn*>(bgm->getDirectorP(6));
		}
		return nullptr;
	}
	return nullptr;
}

/**
 * @note Address: 0x80459420
 * @note Size: 0xF0
 */
PSM::TrackOnDirector_Voting* PSMGetPikiBattleD()
{
	if (PSGameGetSceneInfo()->mSceneType == PSGame::SceneInfo::TWO_PLAYER_BATTLE) {
		PSSystem::DirectedBgm* bgm = PSGetDirectedMainBgm();
		if (bgm) {
			return static_cast<PSM::TrackOnDirector_Voting*>(bgm->getDirectorP(7));
		}
		return nullptr;
	}
	return nullptr;
}
