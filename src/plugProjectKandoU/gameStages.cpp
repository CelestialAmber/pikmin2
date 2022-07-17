#include "Game/gameStages.h"
#include "MapCollision.h"
#include "Dolphin/mtx.h"
#include "types.h"

/*
    Generated from dpostproc

    .section .rodata  # 0x804732E0 - 0x8049E220
    .global lbl_8047F8A8
    lbl_8047F8A8:
        .4byte 0x67616D65
        .4byte 0x53746167
        .4byte 0x65730000
    .global lbl_8047F8B4
    lbl_8047F8B4:
        .4byte 0x6B656967
        .4byte 0x6F5F6465
        .4byte 0x5F736F78
        .4byte 0x2E747874
        .4byte 0x00000000
        .4byte 0x6162655F
        .4byte 0x666F6C64
        .4byte 0x65720000
        .4byte 0x636F6C6C
        .4byte 0x6973696F
        .4byte 0x6E000000
        .4byte 0x77617465
        .4byte 0x72626F78
        .4byte 0x00000000
        .4byte 0x73746172
        .4byte 0x74616E67
        .4byte 0x6C650000
    .global lbl_8047F8F8
    lbl_8047F8F8:
        .4byte 0x67616D65
        .4byte 0x53746167
        .4byte 0x65732E63
        .4byte 0x70700000
    .global lbl_8047F908
    lbl_8047F908:
        .asciz "P2Assert"
        .skip 3
    .global lbl_8047F914
    lbl_8047F914:
        .4byte 0x75736572
        .4byte 0x2F416265
        .4byte 0x2F737461
        .4byte 0x6765732E
        .4byte 0x74787400
        .4byte 0x53656C65
        .4byte 0x63742043
        .4byte 0x6F757273
        .4byte 0x65000000
        .4byte 0x2573203A
        .4byte 0x20256420
        .4byte 0x63617665
        .4byte 0x730A0000
        .4byte 0x5B25735D
        .4byte 0x2025642F
        .4byte 0x25640000
        .4byte 0x00000000

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global __vt__Q24Game10CourseInfo
    __vt__Q24Game10CourseInfo:
        .4byte 0
        .4byte 0
        .4byte __dt__Q24Game10CourseInfoFv
        .4byte getChildCount__5CNodeFv
    .global __vt__Q24Game8LimitGen
    __vt__Q24Game8LimitGen:
        .4byte 0
        .4byte 0
        .4byte __dt__Q24Game8LimitGenFv
        .4byte getChildCount__5CNodeFv
    .global __vt__Q24Game11CaveOtakara
    __vt__Q24Game11CaveOtakara:
        .4byte 0
        .4byte 0
        .4byte __dt__Q24Game11CaveOtakaraFv
        .4byte getChildCount__5CNodeFv

    .section .sbss # 0x80514D80 - 0x80516360
    .global stageList__4Game
    stageList__4Game:
        .skip 0x8

    .section .sdata2, "a"     # 0x80516360 - 0x80520E40
    .global lbl_805192C8
    lbl_805192C8:
        .4byte 0x6E6F6E61
        .4byte 0x6D650000
    .global lbl_805192D0
    lbl_805192D0:
        .4byte 0x00000000
    .global lbl_805192D4
    lbl_805192D4:
        .4byte 0x6E616D65
        .4byte 0x00000000
    .global lbl_805192DC
    lbl_805192DC:
        .4byte 0x666F6C64
        .4byte 0x65720000
    .global lbl_805192E4
    lbl_805192E4:
        .4byte 0x6D6F6465
        .4byte 0x6C000000
    .global lbl_805192EC
    lbl_805192EC:
        .4byte 0x6D617063
        .4byte 0x6F646500
    .global lbl_805192F4
    lbl_805192F4:
        .4byte 0x6661726D
        .4byte 0x00000000
    .global lbl_805192FC
    lbl_805192FC:
        .4byte 0x726F7574
        .4byte 0x65000000
    .global lbl_80519304
    lbl_80519304:
        .4byte 0x73746172
        .4byte 0x74000000
    .global lbl_8051930C
    lbl_8051930C:
        .4byte 0x40490FDB
    .global lbl_80519310
    lbl_80519310:
        .4byte 0x3BB60B61
    .global lbl_80519314
    lbl_80519314:
        .4byte 0x25732F25
        .4byte 0x73000000
        .4byte 0x00000000
*/

namespace Game {
/*
 * --INFO--
 * Address:	........
 * Size:	000068
 */
inline CaveOtakara::CaveOtakara()
{
	m_otakaraCount = 0;
	m_id.setID('xxxx');
	m_filename = "keigo_de_sox.txt";
}

/*
 * --INFO--
 * Address:	........
 * Size:	000090
 */
inline CaveOtakaraInfo::CaveOtakaraInfo()
{
	m_count = 0;
	m_owner.clearRelations();
}

/*
 * --INFO--
 * Address:	801AD378
 * Size:	000060
 * AUTOGEN
 */
CaveOtakara::~CaveOtakara() { }

/*
 * --INFO--
 * Address:	........
 * Size:	0000EC
 */
inline void CaveOtakaraInfo::read(Stream& stream)
{
	m_count = stream.readInt();
	for (int i = 0; i < m_count; i++) {
		CaveOtakara* currOtakara = new CaveOtakara;
		currOtakara->m_id.read(stream);
		currOtakara->m_otakaraCount = stream.readByte();
		currOtakara->m_filename     = stream.readString(nullptr, 0);
		m_owner.add(currOtakara);
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	000024
 */
inline int CaveOtakaraInfo::get_index(int)
{
	// TODO
	return 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00008C
 */
inline void CaveOtakaraInfo::get_id(ID32&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000080
 */
inline CaveOtakara* CaveOtakaraInfo::getCaveIndex_FromID(ID32& id) {
	CaveOtakara* caveNode;
	for (int i = 0; i < m_count; i++) {
		caveNode = (CaveOtakara*)m_owner.getChildAt(i);

		if ((caveNode->m_id == id.getID())) {
            return caveNode;
		} else {
			continue;
		}
	}
    return 0;
};

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
inline ID32* CaveOtakaraInfo::getCaveID_FromIndex(int)
{
	return nullptr;
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */
inline LimitGenInfo::LimitGenInfo()
{
	m_count = 0;
	m_owner.clearRelations();
}

/*
 * --INFO--
 * Address:	801AD3D8
 * Size:	000060
 * AUTOGEN
 */
LimitGen::~LimitGen() { }

/*
 * --INFO--
 * Address:	........
 * Size:	0000CC
 */
inline void LimitGenInfo::read(Stream& stream)
{
	m_count = stream.readInt();
	for (int i = 0; i < m_count; i++) {
		LimitGen* currLimitGen   = new LimitGen;
		currLimitGen->m_name     = stream.readString(nullptr, 0);
		currLimitGen->_18        = stream.readInt();
		currLimitGen->_1C        = stream.readInt();
		currLimitGen->m_dayLimit = stream.readInt();
		m_owner.add(currLimitGen);
	}
}

/*
 * --INFO--
 * Address:	801AD438
 * Size:	000154
 */
CourseInfo::CourseInfo()
{
	setName("noname");

	m_routePath     = 0;
	m_farmPath      = 0;
	m_mapcodePath   = 0;
	m_waterboxPath  = 0;
	m_collisionPath = 0;
	m_modelPath     = 0;
	m_folder        = 0;

	m_startPosition = 0.0f;
	m_startAngle    = 0;

	m_courseIndex = 0;

	PSMTXIdentity(_D0.m_matrix.mtxView);
	m_groundOtakaraMax = 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 * AUTOGEN
 */
CaveOtakaraInfo::~CaveOtakaraInfo(void) { }

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 * AUTOGEN
 */
LimitGenInfo::~LimitGenInfo(void) { }

/*
 * --INFO--
 * Address:	801AD58C
 * Size:	000004
 */
void CourseInfo::dump() { }

/*
 * --INFO--
 * Address:	801AD590
 * Size:	0004C4
 */
void CourseInfo::read(Stream& stream)
{
	char* currentBytes = stream.readString(nullptr, 0);
	if (strcmp(currentBytes, "name") == 0) {
		m_name       = stream.readString(nullptr, 0);
		currentBytes = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "folder") == 0) {
		m_folder     = stream.readString(nullptr, 0);
		currentBytes = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "abe_folder") == 0) {
		m_abeFolder  = stream.readString(nullptr, 0);
		currentBytes = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "model") == 0) {
		m_modelPath  = stream.readString(nullptr, 0);
		currentBytes = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "collision") == 0) {
		m_collisionPath = stream.readString(nullptr, 0);
		currentBytes    = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "waterbox") == 0) {
		m_waterboxPath = stream.readString(nullptr, 0);
		currentBytes   = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "mapcode") == 0) {
		m_mapcodePath = stream.readString(nullptr, 0);
		currentBytes  = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "farm") == 0) {
		m_farmPath   = stream.readString(nullptr, 0);
		currentBytes = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "route") == 0) {
		m_routePath  = stream.readString(nullptr, 0);
		currentBytes = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "start") == 0) {
		m_startPosition.read(stream);
		currentBytes = stream.readString(nullptr, 0);
	}

	if (strcmp(currentBytes, "startangle") == 0) {
		m_startAngle = stream.readFloat();
		stream.readString(nullptr, 0);

		// Convert angle to radians
		Vector3f vec(0.0f, PI * m_startAngle * (PI / 180), 0.0f);
		_D0.makeTR(m_startPosition, vec);
	}

	m_limitGenInfo.read(stream);
	m_loopGenInfo.read(stream);
	m_caveOtakaraInfo.read(stream);

	m_groundOtakaraMax = stream.readInt();
}

/*
 * --INFO--
 * Address:	801ADA54
 * Size:	000088
 * TODO: MATCH IT!
 */
int CourseInfo::getOtakaraNum(ID32& id)
{
	int i             = 0;
	CaveOtakara& node = m_caveOtakaraInfo.m_owner;

	CaveOtakara* caveNode;
	while (i < m_caveOtakaraInfo.m_count) {
		caveNode = (CaveOtakara*)node.getChildAt(i);

		if (caveNode->m_id == id.getID()) {
			break;
		} else {
			i++;
			caveNode = nullptr;
		}
	}

	if (caveNode) {
		return caveNode->m_otakaraCount;
	}

	return -1;
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stmw     r27, 0xc(r1)
	mr       r27, r3
	mr       r28, r4
	li       r31, 0
	addi     r29, r27, 0xa0
	b        lbl_801ADAA4

lbl_801ADA78:
	mr       r3, r29
	mr       r4, r31
	bl       getChildAt__5CNodeFi
	mr       r30, r3
	lwz      r4, 8(r28)
	addi     r3, r30, 0x18
	bl       __eq__4ID32FUl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801ADAA0
	b        lbl_801ADAB4

lbl_801ADAA0:
	addi     r31, r31, 1

lbl_801ADAA4:
	lwz      r0, 0x9c(r27)
	cmpw     r31, r0
	blt      lbl_801ADA78
	li       r30, 0

lbl_801ADAB4:
	cmplwi   r30, 0
	beq      lbl_801ADAC4
	lbz      r3, 0x24(r30)
	b        lbl_801ADAC8

lbl_801ADAC4:
	li       r3, -1

lbl_801ADAC8:
	lmw      r27, 0xc(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	801ADADC
 * Size:	000038
 */
int CourseInfo::getOtakaraNum(int childIdx)
{
	CaveOtakara* node = (CaveOtakara*)m_caveOtakaraInfo.m_owner.getChildAt(childIdx);

	if (node) {
		return node->m_otakaraCount;
	}

	return -1;
}

/*
 * --INFO--
 * Address:	801ADB14
 * Size:	00008C
 */
int CourseInfo::getCaveIndex_FromID(ID32&)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	li       r31, 0
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	mr       r29, r4
	stw      r28, 0x10(r1)
	mr       r28, r3
	addi     r30, r28, 0xa0
	b        lbl_801ADB6C

lbl_801ADB44:
	mr       r3, r30
	mr       r4, r31
	bl       getChildAt__5CNodeFi
	lwz      r4, 8(r29)
	addi     r3, r3, 0x18
	bl       __eq__4ID32FUl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801ADB68
	b        lbl_801ADB7C

lbl_801ADB68:
	addi     r31, r31, 1

lbl_801ADB6C:
	lwz      r0, 0x9c(r28)
	cmpw     r31, r0
	blt      lbl_801ADB44
	li       r31, -1

lbl_801ADB7C:
	lwz      r0, 0x24(r1)
	mr       r3, r31
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r29, 0x14(r1)
	lwz      r28, 0x10(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	801ADBA0
 * Size:	00009C
 */
char* CourseInfo::getCaveinfoFilename_FromID(ID32&)
{
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stmw     r27, 0xc(r1)
	mr       r27, r3
	mr       r28, r4
	li       r31, 0
	addi     r29, r27, 0xa0
	b        lbl_801ADBF0

lbl_801ADBC4:
	mr       r3, r29
	mr       r4, r31
	bl       getChildAt__5CNodeFi
	mr       r30, r3
	lwz      r4, 8(r28)
	addi     r3, r30, 0x18
	bl       __eq__4ID32FUl
	clrlwi.  r0, r3, 0x18
	beq      lbl_801ADBEC
	b        lbl_801ADC00

lbl_801ADBEC:
	addi     r31, r31, 1

lbl_801ADBF0:
	lwz      r0, 0x9c(r27)
	cmpw     r31, r0
	blt      lbl_801ADBC4
	li       r30, 0

lbl_801ADC00:
	cmplwi   r30, 0
	bne      lbl_801ADC24
	lis      r3, lbl_8047F8F8@ha
	lis      r5, lbl_8047F908@ha
	addi     r3, r3, lbl_8047F8F8@l
	li       r4, 0x11a
	addi     r5, r5, lbl_8047F908@l
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_801ADC24:
	lwz      r3, 0x28(r30)
	lmw      r27, 0xc(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	801ADC3C
 * Size:	00003C
 */
ID32* CourseInfo::getCaveID_FromIndex(int)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	addi     r3, r3, 0xa0
	stw      r0, 0x14(r1)
	bl       getChildAt__5CNodeFi
	cmplwi   r3, 0
	beq      lbl_801ADC60
	lwz      r3, 0x20(r3)
	b        lbl_801ADC68

lbl_801ADC60:
	lis      r3, 0x6E6F6E65@ha
	addi     r3, r3, 0x6E6F6E65@l

lbl_801ADC68:
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	801ADC78
 * Size:	000008
 */
int CourseInfo::getCaveNum()
{
	/*
	lwz      r3, 0x9c(r3)
	blr
	*/
}

/*
 * --INFO--
 * Address:	801ADC80
 * Size:	0001EC
 */
Stages::Stages(void)
{
	/*
	stwu     r1, -0x440(r1)
	mflr     r0
	stw      r0, 0x444(r1)
	stw      r31, 0x43c(r1)
	stw      r30, 0x438(r1)
	mr       r30, r3
	mr       r0, r30
	stw      r29, 0x434(r1)
	mr       r31, r0
	stw      r28, 0x430(r1)
	bl       __ct__5CNodeFv
	lis      r3, __vt__Q24Game10CourseInfo@ha
	addi     r29, r31, 0x50
	addi     r0, r3, __vt__Q24Game10CourseInfo@l
	stw      r0, 0(r31)
	mr       r3, r29
	bl       __ct__5CNodeFv
	lis      r3, __vt__Q24Game8LimitGen@ha
	addi     r28, r31, 0x78
	addi     r3, r3, __vt__Q24Game8LimitGen@l
	li       r0, 0
	stw      r3, 0(r29)
	mr       r3, r28
	stw      r0, 0x4c(r31)
	stw      r0, 0x60(r31)
	stw      r0, 0x5c(r31)
	stw      r0, 0x58(r31)
	stw      r0, 0x54(r31)
	bl       __ct__5CNodeFv
	lis      r3, __vt__Q24Game8LimitGen@ha
	addi     r29, r31, 0xa0
	addi     r3, r3, __vt__Q24Game8LimitGen@l
	li       r0, 0
	stw      r3, 0(r28)
	mr       r3, r29
	stw      r0, 0x74(r31)
	stw      r0, 0x88(r31)
	stw      r0, 0x84(r31)
	stw      r0, 0x80(r31)
	stw      r0, 0x7c(r31)
	bl       __ct__5CNodeFv
	lis      r4, __vt__Q24Game11CaveOtakara@ha
	addi     r3, r29, 0x18
	addi     r0, r4, __vt__Q24Game11CaveOtakara@l
	stw      r0, 0(r29)
	bl       __ct__4ID32Fv
	li       r0, 0
	lis      r4, 0x78787878@ha
	stb      r0, 0x24(r29)
	addi     r3, r29, 0x18
	addi     r4, r4, 0x78787878@l
	bl       setID__4ID32FUl
	lis      r3, lbl_8047F8B4@ha
	li       r4, 0
	addi     r3, r3, lbl_8047F8B4@l
	addi     r0, r2, lbl_805192C8@sda21
	stw      r3, 0x28(r29)
	addi     r3, r31, 0xd0
	lfs      f0, lbl_805192D0@sda21(r2)
	stw      r4, 0x9c(r31)
	stw      r4, 0xb0(r31)
	stw      r4, 0xac(r31)
	stw      r4, 0xa8(r31)
	stw      r4, 0xa4(r31)
	stw      r0, 0x14(r31)
	stw      r4, 0x34(r31)
	stw      r4, 0x30(r31)
	stw      r4, 0x2c(r31)
	stw      r4, 0x28(r31)
	stw      r4, 0x24(r31)
	stw      r4, 0x20(r31)
	stw      r4, 0x18(r31)
	stfs     f0, 0x38(r31)
	stfs     f0, 0x3c(r31)
	stfs     f0, 0x40(r31)
	stfs     f0, 0x44(r31)
	stw      r4, 0x48(r31)
	bl       PSMTXIdentity
	li       r0, 0
	lis      r3, lbl_8047F914@ha
	stw      r0, 0xcc(r31)
	addi     r3, r3, lbl_8047F914@l
	li       r4, 0
	li       r5, 0
	stw      r0, 0x10(r30)
	li       r6, 0
	li       r7, 0
	li       r8, 2
	stw      r0, 0xc(r30)
	li       r9, 0
	li       r10, 0
	stw      r0, 8(r30)
	stw      r0, 4(r30)
	sth      r0, 0x108(r30)
	stw      r0, 0x104(r30)
	stb      r0, 0x10a(r30)
	stw      r0, 8(r1)
	bl
loadToMainRAM__12JKRDvdRipperFPCcPUc15JKRExpandSwitchUlP7JKRHeapQ212JKRDvdRipper15EAllocDirectionUlPiPUl
	mr       r31, r3
	addi     r3, r1, 0x10
	li       r5, -1
	mr       r4, r31
	bl       __ct__9RamStreamFPvi
	li       r0, 1
	cmpwi    r0, 1
	stw      r0, 0x1c(r1)
	bne      lbl_801ADE34
	li       r0, 0
	stw      r0, 0x424(r1)

lbl_801ADE34:
	mr       r3, r30
	addi     r4, r1, 0x10
	bl       read__Q24Game6StagesFR6Stream
	mr       r3, r31
	bl       __dla__FPv
	lwz      r0, 0x444(r1)
	mr       r3, r30
	lwz      r31, 0x43c(r1)
	lwz      r30, 0x438(r1)
	lwz      r29, 0x434(r1)
	lwz      r28, 0x430(r1)
	mtlr     r0
	addi     r1, r1, 0x440
	blr
	*/
}

/*
 * --INFO--
 * Address:	801ADE6C
 * Size:	0000D0
 */
CourseInfo::~CourseInfo(void)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	or.      r30, r3, r3
	beq      lbl_801ADF20
	lis      r3, __vt__Q24Game10CourseInfo@ha
	addic.   r0, r30, 0x9c
	addi     r0, r3, __vt__Q24Game10CourseInfo@l
	stw      r0, 0(r30)
	beq      lbl_801ADEBC
	addic.   r3, r30, 0xa0
	beq      lbl_801ADEBC
	lis      r4, __vt__Q24Game11CaveOtakara@ha
	addi     r0, r4, __vt__Q24Game11CaveOtakara@l
	stw      r0, 0xa0(r30)
	li       r4, 0
	bl       __dt__5CNodeFv

lbl_801ADEBC:
	addic.   r0, r30, 0x74
	beq      lbl_801ADEE0
	addic.   r3, r30, 0x78
	beq      lbl_801ADEE0
	lis      r4, __vt__Q24Game8LimitGen@ha
	addi     r0, r4, __vt__Q24Game8LimitGen@l
	stw      r0, 0x78(r30)
	li       r4, 0
	bl       __dt__5CNodeFv

lbl_801ADEE0:
	addic.   r0, r30, 0x4c
	beq      lbl_801ADF04
	addic.   r3, r30, 0x50
	beq      lbl_801ADF04
	lis      r4, __vt__Q24Game8LimitGen@ha
	addi     r0, r4, __vt__Q24Game8LimitGen@l
	stw      r0, 0x50(r30)
	li       r4, 0
	bl       __dt__5CNodeFv

lbl_801ADF04:
	mr       r3, r30
	li       r4, 0
	bl       __dt__5CNodeFv
	extsh.   r0, r31
	ble      lbl_801ADF20
	mr       r3, r30
	bl       __dl__FPv

lbl_801ADF20:
	lwz      r0, 0x14(r1)
	mr       r3, r30
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void Stages::update()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	801ADF3C
 * Size:	000070
 */
CourseInfo* Stages::getCourseInfo(char* name)
{
	for (CNode* node = m_courseInfo.m_child; node; node = node->m_next) {
		if (!strncmp(name, node->m_name, strlen(name))) {
			return (CourseInfo*)node;
		}
	}

	return nullptr;
}

/*
 * --INFO--
 * Address:	801ADFAC
 * Size:	000074
 */
CourseInfo* Stages::getCourseInfo(int)
{
	// https://decomp.me/scratch/qH6cr
	/*
	cmpwi    r4, 0
	lwz      r3, 0x10(r3)
	li       r6, 0
	blelr
	cmpwi    r4, 8
	addi     r5, r4, -8
	ble      lbl_801AE004
	addi     r0, r5, 7
	srwi     r0, r0, 3
	mtctr    r0
	cmpwi    r5, 0
	ble      lbl_801AE004

lbl_801ADFDC:
	lwz      r3, 4(r3)
	addi     r6, r6, 8
	lwz      r3, 4(r3)
	lwz      r3, 4(r3)
	lwz      r3, 4(r3)
	lwz      r3, 4(r3)
	lwz      r3, 4(r3)
	lwz      r3, 4(r3)
	lwz      r3, 4(r3)
	bdnz     lbl_801ADFDC

lbl_801AE004:
	subf     r0, r6, r4
	mtctr    r0
	cmpw     r6, r4
	bgelr

lbl_801AE014:
	lwz      r3, 4(r3)
	bdnz     lbl_801AE014
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	0003FC
 */
void Stages::draw2d(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	801AE020
 * Size:	000234
 */
void Stages::createMapMgr(Game::CourseInfo*, Game::RouteMgr*)
{
	/*
	stwu     r1, -0x640(r1)
	mflr     r0
	stw      r0, 0x644(r1)
	stw      r31, 0x63c(r1)
	mr       r31, r4
	stw      r30, 0x638(r1)
	mr       r30, r3
	stw      r29, 0x634(r1)
	stw      r28, 0x630(r1)
	lwz      r6, 0x20(r3)
	cmplwi   r6, 0
	beq      lbl_801AE064
	lwz      r5, 0x18(r30)
	addi     r3, r1, 0x528
	addi     r4, r2, lbl_80519314@sda21
	crclr    6
	bl       sprintf

lbl_801AE064:
	lwz      r6, 0x24(r30)
	cmplwi   r6, 0
	beq      lbl_801AE084
	lwz      r5, 0x18(r30)
	addi     r3, r1, 0x428
	addi     r4, r2, lbl_80519314@sda21
	crclr    6
	bl       sprintf

lbl_801AE084:
	lwz      r6, 0x28(r30)
	cmplwi   r6, 0
	beq      lbl_801AE0A4
	lwz      r5, 0x18(r30)
	addi     r3, r1, 0x328
	addi     r4, r2, lbl_80519314@sda21
	crclr    6
	bl       sprintf

lbl_801AE0A4:
	lwz      r6, 0x2c(r30)
	cmplwi   r6, 0
	beq      lbl_801AE0C4
	lwz      r5, 0x18(r30)
	addi     r3, r1, 0x228
	addi     r4, r2, lbl_80519314@sda21
	crclr    6
	bl       sprintf

lbl_801AE0C4:
	lwz      r6, 0x30(r30)
	cmplwi   r6, 0
	beq      lbl_801AE0E4
	lwz      r5, 0x18(r30)
	addi     r3, r1, 0x128
	addi     r4, r2, lbl_80519314@sda21
	crclr    6
	bl       sprintf

lbl_801AE0E4:
	lwz      r6, 0x34(r30)
	cmplwi   r6, 0
	beq      lbl_801AE104
	lwz      r5, 0x1c(r30)
	addi     r3, r1, 0x28
	addi     r4, r2, lbl_80519314@sda21
	crclr    6
	bl       sprintf

lbl_801AE104:
	li       r3, 0x5c
	bl       __nw__FUl
	or.      r29, r3, r3
	beq      lbl_801AE170
	addi     r0, r29, 0x54
	lis      r4, __vt__16GenericObjectMgr@ha
	stw      r0, 0(r29)
	addi     r0, r4, __vt__16GenericObjectMgr@l
	li       r4, 0
	stw      r0, 0x54(r29)
	bl       __ct__Q24Game6MapMgrFv
	lis      r3, __vt__Q24Game11ShapeMapMgr@ha
	addi     r28, r29, 0x38
	addi     r3, r3, __vt__Q24Game11ShapeMapMgr@l
	addi     r0, r29, 0x54
	stw      r3, 4(r29)
	addi     r5, r3, 0x60
	mr       r3, r28
	lwz      r4, 0(r29)
	stw      r5, 0(r4)
	lwz      r4, 0(r29)
	subf     r0, r4, r0
	stw      r0, 4(r4)
	bl       __ct__5CNodeFv
	lis      r3, __vt__12MapCollision@ha
	addi     r0, r3, __vt__12MapCollision@l
	stw      r0, 0(r28)

lbl_801AE170:
	stw      r29, mapMgr__4Game@sda21(r13)
	addi     r12, r1, 0x28
	addi     r9, r1, 0x428
	addi     r3, r1, 0x528
	stw      r31, 8(r29)
	li       r6, 0
	addi     r5, r1, 0x328
	addi     r0, r1, 0x228
	lwz      r7, mapMgr__4Game@sda21(r13)
	addi     r4, r1, 8
	stw      r30, 0xc(r7)
	lwz      r10, 0x34(r30)
	lwz      r11, 0x24(r30)
	lwz      r8, 0x20(r30)
	neg      r7, r10
	or       r7, r7, r10
	neg      r10, r11
	srawi    r31, r7, 0x1f
	neg      r7, r8
	or       r10, r10, r11
	stw      r6, 0x18(r1)
	srawi    r10, r10, 0x1f
	or       r7, r7, r8
	srawi    r7, r7, 0x1f
	and      r8, r12, r31
	and      r9, r9, r10
	stw      r8, 0x24(r1)
	and      r7, r3, r7
	lwz      r3, mapMgr__4Game@sda21(r13)
	stw      r7, 0x10(r1)
	stw      r9, 0x14(r1)
	stw      r6, 0x20(r1)
	lwz      r6, 0x18(r30)
	stw      r6, 8(r1)
	lwz      r6, 0x1c(r30)
	stw      r6, 0xc(r1)
	lwz      r7, 0x28(r30)
	neg      r6, r7
	or       r6, r6, r7
	srawi    r6, r6, 0x1f
	and      r5, r5, r6
	stw      r5, 0x18(r1)
	lwz      r6, 0x2c(r30)
	neg      r5, r6
	or       r5, r5, r6
	srawi    r5, r5, 0x1f
	and      r0, r0, r5
	stw      r0, 0x1c(r1)
	bl       load__Q24Game11ShapeMapMgrFRQ34Game11ShapeMapMgr7LoadArg
	lwz      r0, 0x644(r1)
	lwz      r31, 0x63c(r1)
	lwz      r30, 0x638(r1)
	lwz      r29, 0x634(r1)
	lwz      r28, 0x630(r1)
	mtlr     r0
	addi     r1, r1, 0x640
	blr
	*/
}

} // namespace Game

/*
 * --INFO--
 * Address:	801AE254
 * Size:	000060
 * AUTOGEN
 */
// MapCollision::~MapCollision() { }

namespace Game {

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
void Stages::dump(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	801AE2B4
 * Size:	000194
 */
void Stages::read(Stream&)
{
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stmw     r25, 0x14(r1)
	mr       r28, r4
	mr       r27, r3
	mr       r3, r28
	bl       readShort__6StreamFv
	sth      r3, 0x100(r27)
	clrlwi   r30, r3, 0x10
	li       r29, 0
	b        lbl_801AE42C

lbl_801AE2E4:
	li       r3, 0x100
	bl       __nw__FUl
	or.      r31, r3, r3
	beq      lbl_801AE40C
	bl       __ct__5CNodeFv
	lis      r3, __vt__Q24Game10CourseInfo@ha
	addi     r26, r31, 0x50
	addi     r0, r3, __vt__Q24Game10CourseInfo@l
	stw      r0, 0(r31)
	mr       r3, r26
	bl       __ct__5CNodeFv
	lis      r3, __vt__Q24Game8LimitGen@ha
	addi     r25, r31, 0x78
	addi     r3, r3, __vt__Q24Game8LimitGen@l
	li       r0, 0
	stw      r3, 0(r26)
	mr       r3, r25
	stw      r0, 0x4c(r31)
	stw      r0, 0x60(r31)
	stw      r0, 0x5c(r31)
	stw      r0, 0x58(r31)
	stw      r0, 0x54(r31)
	bl       __ct__5CNodeFv
	lis      r3, __vt__Q24Game8LimitGen@ha
	addi     r26, r31, 0xa0
	addi     r3, r3, __vt__Q24Game8LimitGen@l
	li       r0, 0
	stw      r3, 0(r25)
	mr       r3, r26
	stw      r0, 0x74(r31)
	stw      r0, 0x88(r31)
	stw      r0, 0x84(r31)
	stw      r0, 0x80(r31)
	stw      r0, 0x7c(r31)
	bl       __ct__5CNodeFv
	lis      r4, __vt__Q24Game11CaveOtakara@ha
	addi     r3, r26, 0x18
	addi     r0, r4, __vt__Q24Game11CaveOtakara@l
	stw      r0, 0(r26)
	bl       __ct__4ID32Fv
	li       r0, 0
	lis      r4, 0x78787878@ha
	stb      r0, 0x24(r26)
	addi     r3, r26, 0x18
	addi     r4, r4, 0x78787878@l
	bl       setID__4ID32FUl
	lis      r3, lbl_8047F8B4@ha
	li       r4, 0
	addi     r3, r3, lbl_8047F8B4@l
	addi     r0, r2, lbl_805192C8@sda21
	stw      r3, 0x28(r26)
	addi     r3, r31, 0xd0
	lfs      f0, lbl_805192D0@sda21(r2)
	stw      r4, 0x9c(r31)
	stw      r4, 0xb0(r31)
	stw      r4, 0xac(r31)
	stw      r4, 0xa8(r31)
	stw      r4, 0xa4(r31)
	stw      r0, 0x14(r31)
	stw      r4, 0x34(r31)
	stw      r4, 0x30(r31)
	stw      r4, 0x2c(r31)
	stw      r4, 0x28(r31)
	stw      r4, 0x24(r31)
	stw      r4, 0x20(r31)
	stw      r4, 0x18(r31)
	stfs     f0, 0x38(r31)
	stfs     f0, 0x3c(r31)
	stfs     f0, 0x40(r31)
	stfs     f0, 0x44(r31)
	stw      r4, 0x48(r31)
	bl       PSMTXIdentity
	li       r0, 0
	stw      r0, 0xcc(r31)

lbl_801AE40C:
	stw      r29, 0x48(r31)
	mr       r3, r31
	mr       r4, r28
	bl       read__Q24Game10CourseInfoFR6Stream
	mr       r3, r27
	mr       r4, r31
	bl       add__5CNodeFP5CNode
	addi     r29, r29, 1

lbl_801AE42C:
	cmpw     r29, r30
	blt      lbl_801AE2E4
	lmw      r25, 0x14(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}
} // namespace Game
