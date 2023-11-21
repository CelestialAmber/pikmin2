#include "JSystem/J3D/J3DDisplayListObj.h"
#include "JSystem/J3D/J3DModel.h"
#include "JSystem/J3D/J3DMtxBuffer.h"
#include "JSystem/J3D/J3DPacket.h"
#include "JSystem/J3D/J3DSys.h"
#include "JSystem/J3D/J3DTexGenBlock.h"
#include "JSystem/J3D/J3DTexMtx.h"
#include "JSystem/J3D/J3DTypes.h"
#include "JSystem/J3D/J3DSkinDeform.h"
#include "JSystem/J3D/J3DVtxColorCalc.h"
#include "JSystem/J3D/J3DTransform.h"

/*
 * --INFO--
 * Address:	800662FC
 * Size:	000084
 */
void J3DModel::initialize()
{
	mModelData    = nullptr;
	mFlags        = 0;
	mDiffFlag     = 0;
	mCalcCallBack = nullptr;
	mUserArea     = 0;
	mModelScale.x = 1.0f;
	mModelScale.y = 1.0f;
	mModelScale.z = 1.0f;
	PSMTXIdentity(mPosMtx);
	PSMTXIdentity(mInternalView);
	mMtxBuffer    = nullptr;
	mMatPackets   = nullptr;
	mShapePackets = nullptr;
	mDeformData   = nullptr;
	mSkinDeform   = nullptr;
	mVtxColorCalc = nullptr;
	mUnkCalc1     = 0;
	mUnkCalc2     = nullptr;
}

/*
 * --INFO--
 * Address:	80066380
 * Size:	0000C4
 */
int J3DModel::entryModelData(J3DModelData* data, u32 p2, u32 modelType)
{
	mModelData = data;
	mMtxBuffer = new J3DMtxBuffer();
	int result = mMtxBuffer->create(data, modelType);
	if (result) {
		return result;
	}
	result = createShapePacket(data);
	if (result) {
		return result;
	}
	result = createMatPacket(data, p2);
	if (result) {
		return result;
	}
	mVertexBuffer.setVertexData(&data->mVertexData);
	prepareShapePackets();
	return 0;
}

/*
 * --INFO--
 * Address:	80066444
 * Size:	0000BC
 */
int J3DModel::createShapePacket(J3DModelData* data)
{
	if (data->mShapeTable.mCount) {
		mShapePackets = new J3DShapePacket[data->mShapeTable.mCount];
		for (s32 i = 0; i < data->mShapeTable.mCount; i++) {
			mShapePackets[i].mShape = data->mShapeTable.getItem(i);
			mShapePackets[i].mModel = this;
		}
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80066500
 * Size:	0001D8
 */
int J3DModel::createMatPacket(J3DModelData* data, u32 flags)
{
	if (data->mMaterialTable.mMaterialNum != 0) {
		mMatPackets = new J3DMatPacket[data->mMaterialTable.mMaterialNum];
	}
	u16 count = data->mMaterialTable.mMaterialNum;
	for (u16 i = 0; i < count; i++) {
		J3DMaterial* material       = data->mMaterialTable.mMaterials[i];
		J3DMatPacket* matPacket     = &mMatPackets[i];
		J3DShapePacket* shapePacket = &mShapePackets[material->mShape->mId];
		matPacket->mMaterial        = material;
		matPacket->mInitShapePacket = shapePacket;
		matPacket->addShapePacket(shapePacket);
		matPacket->mTexture  = data->mMaterialTable.mTextures;
		matPacket->mDiffFlag = material->mDiffFlag;
		if (data->mJointTree.mFlags == 1) {
			matPacket->mFlags = matPacket->mFlags | 1;
		}
		if ((flags & 0x80000) != 0) {
			matPacket->mDisplayList = material->mSharedDLObj;
		} else {
			if (data->mJointTree.mFlags == 1) {
				if ((flags & 0x40000) != 0) {
					matPacket->mDisplayList = material->mSharedDLObj;
				} else {
					J3DDisplayListObj* dl = material->mSharedDLObj;
					J3DErrType result     = dl->single_To_Double();
					if (result != JET_Success) {
						return result;
					}
					matPacket->mDisplayList = dl;
				}
			} else if ((flags & 0x20000) != 0) {
				if ((flags & 0x40000) != 0) {
					material->newSingleSharedDisplayList(material->countDLSize());
					matPacket->mDisplayList = material->mSharedDLObj;
				} else {
					material->newSharedDisplayList(material->countDLSize());
					J3DDisplayListObj* dl = material->mSharedDLObj;
					dl->single_To_Double();
					matPacket->mDisplayList = dl;
				}
			} else {
				if ((flags & 0x40000) != 0) {
					matPacket->newSingleDisplayList(material->countDLSize());
				} else {
					matPacket->newDisplayList(material->countDLSize());
				}
			}
		}
	}
	return JET_Success;
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stmw     r23, 0xc(r1)
	mr       r24, r4
	mr       r23, r3
	mr       r26, r5
	lhz      r25, 0x5c(r4)
	cmplwi   r25, 0
	beq      lbl_80066554
	rlwinm   r3, r25, 6, 0xa, 0x19
	addi     r3, r3, 0x10
	bl       __nwa__FUl
	lis      r4, __ct__12J3DMatPacketFv@ha
	lis      r5, __dt__12J3DMatPacketFv@ha
	addi     r4, r4, __ct__12J3DMatPacketFv@l
	mr       r7, r25
	addi     r5, r5, __dt__12J3DMatPacketFv@l
	li       r6, 0x40
	bl       __construct_new_array
	stw      r3, 0xc0(r23)

lbl_80066554:
	lhz      r31, 0x5c(r24)
	rlwinm   r29, r26, 0, 0xc, 0xc
	rlwinm   r28, r26, 0, 0xd, 0xd
	rlwinm   r27, r26, 0, 0xe, 0xe
	li       r26, 0
	b        lbl_800666B4

lbl_8006656C:
	lwz      r5, 0x60(r24)
	rlwinm   r4, r26, 2, 0xe, 0x1d
	lwz      r3, 0xc0(r23)
	rlwinm   r0, r26, 6, 0xa, 0x19
	lwzx     r30, r5, r4
	add      r25, r3, r0
	lwz      r5, 0xc4(r23)
	lwz      r4, 8(r30)
	mr       r3, r25
	lhz      r0, 8(r4)
	mulli    r0, r0, 0x3c
	stw      r30, 0x30(r25)
	add      r4, r5, r0
	stw      r4, 0x28(r25)
	bl       addShapePacket__12J3DMatPacketFP14J3DShapePacket
	lwz      r0, 0x6c(r24)
	stw      r0, 0x38(r25)
	lwz      r0, 0x20(r30)
	stw      r0, 0x34(r25)
	lwz      r0, 0x1c(r24)
	cmplwi   r0, 1
	bne      lbl_800665D0
	lwz      r0, 0x10(r25)
	ori      r0, r0, 1
	stw      r0, 0x10(r25)

lbl_800665D0:
	cmplwi   r29, 0
	beq      lbl_800665E4
	lwz      r0, 0x48(r30)
	stw      r0, 0x20(r25)
	b        lbl_800666B0

lbl_800665E4:
	lwz      r0, 0x1c(r24)
	cmplwi   r0, 1
	bne      lbl_80066624
	cmplwi   r28, 0
	beq      lbl_80066604
	lwz      r0, 0x48(r30)
	stw      r0, 0x20(r25)
	b        lbl_800666B0

lbl_80066604:
	lwz      r30, 0x48(r30)
	mr       r3, r30
	bl       single_To_Double__17J3DDisplayListObjFv
	cmpwi    r3, 0
	beq      lbl_8006661C
	b        lbl_800666C4

lbl_8006661C:
	stw      r30, 0x20(r25)
	b        lbl_800666B0

lbl_80066624:
	cmplwi   r27, 0
	beq      lbl_8006667C
	cmplwi   r28, 0
	beq      lbl_80066654
	mr       r3, r30
	bl       countDLSize__11J3DMaterialFv
	mr       r4, r3
	mr       r3, r30
	bl       newSingleSharedDisplayList__11J3DMaterialFUl
	lwz      r0, 0x48(r30)
	stw      r0, 0x20(r25)
	b        lbl_800666B0

lbl_80066654:
	mr       r3, r30
	bl       countDLSize__11J3DMaterialFv
	mr       r4, r3
	mr       r3, r30
	bl       newSharedDisplayList__11J3DMaterialFUl
	lwz      r30, 0x48(r30)
	mr       r3, r30
	bl       single_To_Double__17J3DDisplayListObjFv
	stw      r30, 0x20(r25)
	b        lbl_800666B0

lbl_8006667C:
	cmplwi   r28, 0
	beq      lbl_8006669C
	mr       r3, r30
	bl       countDLSize__11J3DMaterialFv
	mr       r4, r3
	mr       r3, r25
	bl       newSingleDisplayList__13J3DDrawPacketFUl
	b        lbl_800666B0

lbl_8006669C:
	mr       r3, r30
	bl       countDLSize__11J3DMaterialFv
	mr       r4, r3
	mr       r3, r25
	bl       newDisplayList__13J3DDrawPacketFUl

lbl_800666B0:
	addi     r26, r26, 1

lbl_800666B4:
	clrlwi   r0, r26, 0x10
	cmplw    r0, r31
	blt      lbl_8006656C
	li       r3, 0

lbl_800666C4:
	lmw      r23, 0xc(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	800666D8
 * Size:	000090
 */
int J3DModel::newDifferedDisplayList(u32 displayListFlag)
{
	mDiffFlag = displayListFlag;
	// It sure is wild what pre-fetching the limit will do.
	// for (u16 i = 0; i < mModelData->mShapeTable.mCount; i++) {
	u16 count = mModelData->mShapeTable.mCount;
	for (u16 i = 0; i < count; i++) {
		int result = mShapePackets[i].newDifferedDisplayList(displayListFlag);
		if (result) {
			return result;
		}
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80066768
 * Size:	00008C
 */
int J3DModel::newDifferedTexMtx(J3DTexDiffFlag texDiffFlag)
{
	u16 count = mModelData->mShapeTable.mCount;
	for (u16 i = 0; i < count; i++) {
		int result = mShapePackets[i].newDifferedTexMtx(texDiffFlag);
		if (result) {
			return result;
		}
	}
	return 0;
}

/*
 * --INFO--
 * Address:	800667F4
 * Size:	000130
 */
void J3DModel::lock()
{
	int count = mModelData->mMaterialTable.mMaterialNum;
	for (int i = 0; i < count; i++) {
		mMatPackets[i].mFlags |= 1;
	}
}

/*
 * --INFO--
 * Address:	80066924
 * Size:	0000A4
 */
void J3DModel::makeDL()
{
	j3dSys.mModel   = this;
	j3dSys.mTexture = mModelData->mMaterialTable.mTextures;
	u32 count       = mModelData->mMaterialTable.mMaterialNum;
	for (u16 i = 0; i < count; i++) {
		j3dSys.mMatPacket = &mMatPackets[i];
		mModelData->mMaterialTable.mMaterials[i]->makeDisplayList();
	}
}

/*
 * --INFO--
 * Address:	800669C8
 * Size:	000164
 */
void J3DModel::calcMaterial()
{
	j3dSys.setModel(this);

	if (checkFlag(4)) {
		j3dSys.onFlag(4);
	} else {
		j3dSys.offFlag(4);
	}

	if (checkFlag(8)) {
		j3dSys.onFlag(8);
	} else {
		j3dSys.offFlag(8);
	}

	mModelData->syncJ3DSysFlags();
	j3dSys.setTexture(mModelData->getTexture());

	u16 matNum = mModelData->getMaterialNum();
	for (u16 i = 0; i < matNum; i++) {
		j3dSys.setMatPacket(&mMatPackets[i]);

		J3DMaterial* material = mModelData->getMaterialNodePointer(i);
		if (material->getMaterialAnm() != nullptr) {
			material->getMaterialAnm()->calc(material);
		}

		int jntNo = material->getJoint()->getJntNo();
		material->calc(getAnmMtx(jntNo));
	}

	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	lis      r4, j3dSys@ha
	stw      r0, 0x24(r1)
	stmw     r26, 8(r1)
	mr       r28, r3
	addi     r3, r4, j3dSys@l
	stw      r28, 0x38(r3)
	lwz      r0, 8(r28)
	rlwinm.  r0, r0, 0, 0x1d, 0x1d
	beq      lbl_80066A04
	lwz      r0, 0x34(r3)
	ori      r0, r0, 4
	stw      r0, 0x34(r3)
	b        lbl_80066A10

lbl_80066A04:
	lwz      r0, 0x34(r3)
	rlwinm   r0, r0, 0, 0x1e, 0x1c
	stw      r0, 0x34(r3)

lbl_80066A10:
	lwz      r0, 8(r28)
	rlwinm.  r0, r0, 0, 0x1c, 0x1c
	beq      lbl_80066A34
	lis      r3, j3dSys@ha
	addi     r3, r3, j3dSys@l
	lwz      r0, 0x34(r3)
	ori      r0, r0, 8
	stw      r0, 0x34(r3)
	b        lbl_80066A48

lbl_80066A34:
	lis      r3, j3dSys@ha
	addi     r3, r3, j3dSys@l
	lwz      r0, 0x34(r3)
	rlwinm   r0, r0, 0, 0x1d, 0x1b
	stw      r0, 0x34(r3)

lbl_80066A48:
	lwz      r3, 4(r28)
	bl       syncJ3DSysFlags__12J3DModelDataCFv
	lwz      r4, 4(r28)
	lis      r3, j3dSys@ha
	addi     r31, r3, j3dSys@l
	li       r29, 0
	lwz      r0, 0x6c(r4)
	lis      r27, 0xc000
	stw      r0, 0x58(r31)
	lhz      r30, 0x5c(r4)
	b        lbl_80066B0C

lbl_80066A74:
	lwz      r4, 0xc0(r28)
	rlwinm   r3, r29, 6, 0xa, 0x19
	rlwinm   r0, r29, 2, 0xe, 0x1d
	add      r3, r4, r3
	stw      r3, 0x3c(r31)
	lwz      r3, 4(r28)
	lwz      r3, 0x60(r3)
	lwzx     r26, r3, r0
	lwz      r3, 0x3c(r26)
	cmplw    r3, r27
	bge      lbl_80066AA8
	mr       r0, r3
	b        lbl_80066AAC

lbl_80066AA8:
	li       r0, 0

lbl_80066AAC:
	cmplwi   r0, 0
	beq      lbl_80066ADC
	lis      r0, 0xc000
	cmplw    r3, r0
	bge      lbl_80066AC4
	b        lbl_80066AC8

lbl_80066AC4:
	li       r3, 0

lbl_80066AC8:
	lwz      r12, 0(r3)
	mr       r4, r26
	lwz      r12, 0xc(r12)
	mtctr    r12
	bctrl

lbl_80066ADC:
	lwz      r4, 0xc(r26)
	mr       r3, r26
	lwz      r5, 0x84(r28)
	lhz      r0, 0x14(r4)
	lwz      r12, 0(r26)
	mulli    r0, r0, 0x30
	lwz      r4, 0xc(r5)
	lwz      r12, 8(r12)
	add      r4, r4, r0
	mtctr    r12
	bctrl
	addi     r29, r29, 1

lbl_80066B0C:
	clrlwi   r0, r29, 0x10
	cmplw    r0, r30
	blt      lbl_80066A74
	lmw      r26, 8(r1)
	lwz      r0, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	80066B2C
 * Size:	000140
 */
void J3DModel::calcDiffTexMtx()
{
	j3dSys.mModel = this;
	u32 count     = mModelData->mMaterialTable.mMaterialNum;
	for (u16 i = 0; i < count; i++) {
		j3dSys.mMatPacket     = &mMatPackets[i];
		J3DMaterial* material = mModelData->mMaterialTable.mMaterials[i];
		material->calcDiffTexMtx(mMtxBuffer->mWorldMatrices[material->mJoint->getJntNo()]);
	}
	count = mModelData->mShapeTable.mCount;
	for (u16 i = 0; i < count; i++) {
		J3DShapePacket* packet = &mShapePackets[i];
		J3DTexGenBlock* block  = mModelData->mShapeTable.getItem(i)->mMaterial->mTexGenBlock;
		for (u16 j = 0; j < 8; j++) {
			J3DTexMtx* texMtx1 = block->getTexMtx(j);
			J3DTexMtxObj* v1   = packet->mTexMtxObj;
			if (texMtx1 && v1) {
				PSMTXCopy(texMtx1->mMtx, v1->mTexMtx[j]);
			}
		}
	}
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	lis      r4, j3dSys@ha
	stw      r0, 0x34(r1)
	stmw     r25, 0x14(r1)
	mr       r30, r3
	addi     r31, r4, j3dSys@l
	li       r26, 0
	stw      r30, 0x38(r31)
	lwz      r3, 4(r3)
	lhz      r29, 0x5c(r3)
	b        lbl_80066BA8

lbl_80066B5C:
	lwz      r4, 0xc0(r30)
	rlwinm   r3, r26, 6, 0xa, 0x19
	rlwinm   r0, r26, 2, 0xe, 0x1d
	add      r3, r4, r3
	stw      r3, 0x3c(r31)
	lwz      r4, 4(r30)
	lwz      r3, 0x84(r30)
	lwz      r4, 0x60(r4)
	lwz      r5, 0xc(r3)
	lwzx     r3, r4, r0
	lwz      r4, 0xc(r3)
	lwz      r12, 0(r3)
	lhz      r0, 0x14(r4)
	lwz      r12, 0xc(r12)
	mulli    r0, r0, 0x30
	add      r4, r5, r0
	mtctr    r12
	bctrl
	addi     r26, r26, 1

lbl_80066BA8:
	clrlwi   r0, r26, 0x10
	cmplw    r0, r29
	blt      lbl_80066B5C
	lwz      r3, 4(r30)
	li       r31, 0
	lhz      r29, 0x7c(r3)
	b        lbl_80066C4C

lbl_80066BC4:
	lwz      r3, 4(r30)
	clrlwi   r4, r31, 0x10
	rlwinm   r0, r31, 2, 0xe, 0x1d
	lwz      r5, 0xc4(r30)
	lwz      r3, 0x80(r3)
	mulli    r4, r4, 0x3c
	li       r25, 0
	lwzx     r3, r3, r0
	add      r28, r5, r4
	lwz      r3, 4(r3)
	lwz      r27, 0x28(r3)
	b        lbl_80066C3C

lbl_80066BF4:
	mr       r3, r27
	clrlwi   r26, r25, 0x10
	lwz      r12, 0(r27)
	mr       r4, r26
	lwz      r12, 0x50(r12)
	mtctr    r12
	bctrl
	cmplwi   r3, 0
	lwz      r4, 0x24(r28)
	beq      lbl_80066C38
	cmplwi   r4, 0
	beq      lbl_80066C38
	mulli    r0, r26, 0x30
	lwz      r4, 0(r4)
	addi     r3, r3, 0x64
	add      r4, r4, r0
	bl       PSMTXCopy

lbl_80066C38:
	addi     r25, r25, 1

lbl_80066C3C:
	clrlwi   r0, r25, 0x10
	cmpwi    r0, 8
	blt      lbl_80066BF4
	addi     r31, r31, 1

lbl_80066C4C:
	clrlwi   r0, r31, 0x10
	cmplw    r0, r29
	blt      lbl_80066BC4
	lmw      r25, 0x14(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	80066C6C
 * Size:	00009C
 * diff__8J3DModelFv
 */
void J3DModel::diff()
{
	u16 count = mModelData->mMaterialTable.mMaterialNum;
	for (u16 i = 0; i < count; i++) {
		j3dSys.mMatPacket = &mMatPackets[i];
		mModelData->mMaterialTable.mMaterials[i]->diff(mDiffFlag);
	}
}

/*
 * --INFO--
 * Address:	80066D08
 * Size:	000034
 */
void J3DModel::setVtxColorCalc(J3DVtxColorCalc* vtxColorCalc, J3DDeformAttachFlag deformAttachFlag)
{
	mVtxColorCalc = vtxColorCalc;
	if (vtxColorCalc) {
		mVertexBuffer.copyVtxColorArray(deformAttachFlag);
	}
}

/*
 * --INFO--
 * Address:	80066D3C
 * Size:	00004C
 */
void J3DModel::calcWeightEnvelopeMtx()
{
	if (mModelData->mJointTree.mEnvelopeCnt && !(mFlags & 0x10) && !(mModelData->mModelLoaderFlags & J3DMLF_09)) {
		mMtxBuffer->calcWeightEnvelopeMtx();
	}
}

/*
 * --INFO--
 * Address:	80066D88
 * Size:	00004C
 * update__8J3DModelFv
 */
void J3DModel::update()
{
	calc();
	entry();
}

/*
 * --INFO--
 * Address:	80066DD4
 * Size:	0001E0
 */
void J3DModel::calc()
{
	j3dSys.setModel(this);

	if (checkFlag(J3DMODEL_SkinPosCpu)) {
		j3dSys.onFlag(J3DSysFlag_SkinPosCpu);
	} else {
		j3dSys.offFlag(J3DSysFlag_SkinPosCpu);
	}

	if (checkFlag(J3DMODEL_SkinNrmCpu)) {
		j3dSys.onFlag(J3DSysFlag_SkinNrmCpu);
	} else {
		j3dSys.offFlag(J3DSysFlag_SkinNrmCpu);
	}

	getModelData()->syncJ3DSysFlags();
	mVertexBuffer.frameInit();

	if (mUnkCalc2 != nullptr) {
		mUnkCalc2->calc(getModelData());
	}

	if (mDeformData != nullptr) {
		mDeformData->deform(this);
	}

	if (mVtxColorCalc != nullptr) {
		mVtxColorCalc->calc(this);
	}

	if (mUnkCalc1 != nullptr) {
		mUnkCalc1->calc(this);
	}

	j3dSys.setModel(this);

	if (checkFlag(2)) {
		getModelData()->getJointTree().calc(mMtxBuffer, j3dDefaultScale, j3dDefaultMtx);
	} else {
		getModelData()->getJointTree().calc(mMtxBuffer, mModelScale, mPosMtx);
	}

	calcWeightEnvelopeMtx();

	if (mSkinDeform != nullptr) {
		mSkinDeform->deform(this);
	}

	if (mCalcCallBack != nullptr) {
		mCalcCallBack(this, 0);
	}
}

/*
 * --INFO--
 * Address:	80066FB4
 * Size:	0000F4
 * entry__8J3DModelFv
 */
void J3DModel::entry()
{
	j3dSys.mModel = this;
	if (mFlags & 4) {
		j3dSys.mFlags |= 0x4;
	} else {
		j3dSys.mFlags &= ~0x4;
	}
	if (mFlags & 8) {
		j3dSys.mFlags |= 0x8;
	} else {
		j3dSys.mFlags &= ~0x8;
	}
	mModelData->syncJ3DSysFlags();
	j3dSys.mTexture = mModelData->mMaterialTable.mTextures;
	for (u16 i = 0; i < mModelData->mJointTree.mJointCnt; i++) {
		J3DJoint* joint = mModelData->mJointTree.mJoints[i];
		if (joint->mMaterial) {
			joint->entryIn();
		}
	}
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	lis      r4, j3dSys@ha
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r3
	addi     r3, r4, j3dSys@l
	stw      r30, 8(r1)
	stw      r31, 0x38(r3)
	lwz      r0, 8(r31)
	rlwinm.  r0, r0, 0, 0x1d, 0x1d
	beq      lbl_80066FF4
	lwz      r0, 0x34(r3)
	ori      r0, r0, 4
	stw      r0, 0x34(r3)
	b        lbl_80067000

lbl_80066FF4:
	lwz      r0, 0x34(r3)
	rlwinm   r0, r0, 0, 0x1e, 0x1c
	stw      r0, 0x34(r3)

lbl_80067000:
	lwz      r0, 8(r31)
	rlwinm.  r0, r0, 0, 0x1c, 0x1c
	beq      lbl_80067024
	lis      r3, j3dSys@ha
	addi     r3, r3, j3dSys@l
	lwz      r0, 0x34(r3)
	ori      r0, r0, 8
	stw      r0, 0x34(r3)
	b        lbl_80067038

lbl_80067024:
	lis      r3, j3dSys@ha
	addi     r3, r3, j3dSys@l
	lwz      r0, 0x34(r3)
	rlwinm   r0, r0, 0, 0x1d, 0x1b
	stw      r0, 0x34(r3)

lbl_80067038:
	lwz      r3, 4(r31)
	bl       syncJ3DSysFlags__12J3DModelDataCFv
	lwz      r4, 4(r31)
	lis      r3, j3dSys@ha
	addi     r3, r3, j3dSys@l
	li       r30, 0
	lwz      r0, 0x6c(r4)
	stw      r0, 0x58(r3)
	b        lbl_8006707C

lbl_8006705C:
	lwz      r3, 0x28(r4)
	rlwinm   r0, r30, 2, 0xe, 0x1d
	lwzx     r3, r3, r0
	lwz      r0, 0x58(r3)
	cmplwi   r0, 0
	beq      lbl_80067078
	bl       entryIn__8J3DJointFv

lbl_80067078:
	addi     r30, r30, 1

lbl_8006707C:
	lwz      r4, 4(r31)
	clrlwi   r0, r30, 0x10
	lhz      r3, 0x2c(r4)
	cmplw    r0, r3
	blt      lbl_8006705C
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	800670A8
 * Size:	000368
 */
void J3DModel::viewCalc()
{
	mMtxBuffer->swapDrawMtx();
	mMtxBuffer->swapNrmMtx();

	if (mModelData->checkFlag(0x10)) {
		if (getMtxCalcMode() == 2) {
			J3DCalcViewBaseMtx(*j3dSys.getViewMtx(), mModelScale, mPosMtx, (MtxP)&mInternalView);
		}
	} else if (isCpuSkinningOn()) {
		if (getMtxCalcMode() == 2) {
			J3DCalcViewBaseMtx(*j3dSys.getViewMtx(), mModelScale, mPosMtx, (MtxP)&mInternalView);
		}
	} else if (checkFlag(J3DMODEL_SkinPosCpu)) {
		mMtxBuffer->calcDrawMtx(getMtxCalcMode(), mModelScale, mPosMtx);
		calcNrmMtx();
		calcBumpMtx();
		DCStoreRangeNoSync(getDrawMtxPtr(), mModelData->getDrawMtxNum() * sizeof(Mtx));
		DCStoreRange(getNrmMtxPtr(), mModelData->getDrawMtxNum() * sizeof(Mtx33));
	} else if (checkFlag(J3DMODEL_SkinNrmCpu)) {
		mMtxBuffer->calcDrawMtx(getMtxCalcMode(), mModelScale, mPosMtx);
		calcBBoardMtx();
		DCStoreRange(getDrawMtxPtr(), mModelData->getDrawMtxNum() * sizeof(Mtx));
	} else {
		mMtxBuffer->calcDrawMtx(getMtxCalcMode(), mModelScale, mPosMtx);
		calcNrmMtx();
		calcBBoardMtx();
		calcBumpMtx();
		DCStoreRangeNoSync(getDrawMtxPtr(), mModelData->getDrawMtxNum() * sizeof(Mtx));
		DCStoreRange(getNrmMtxPtr(), mModelData->getDrawMtxNum() * sizeof(Mtx33));
	}

	prepareShapePackets();
	/*
	stwu     r1, -0x70(r1)
	mflr     r0
	stw      r0, 0x74(r1)
	stw      r31, 0x6c(r1)
	mr       r31, r3
	lwz      r6, 0x84(r3)
	lwz      r0, 0x30(r6)
	lwz      r4, 0x14(r6)
	slwi     r7, r0, 2
	lwz      r3, 0x18(r6)
	lwzx     r5, r4, r7
	lwzx     r0, r3, r7
	stwx     r0, r4, r7
	lwz      r0, 0x30(r6)
	lwz      r3, 0x18(r6)
	slwi     r0, r0, 2
	stwx     r5, r3, r0
	lwz      r6, 0x84(r31)
	lwz      r0, 0x30(r6)
	lwz      r4, 0x1c(r6)
	slwi     r7, r0, 2
	lwz      r3, 0x20(r6)
	lwzx     r5, r4, r7
	lwzx     r0, r3, r7
	stwx     r0, r4, r7
	lwz      r0, 0x30(r6)
	lwz      r3, 0x20(r6)
	slwi     r0, r0, 2
	stwx     r5, r3, r0
	lwz      r3, 4(r31)
	lwz      r0, 8(r3)
	rlwinm.  r0, r0, 0, 0x1b, 0x1b
	beq      lbl_800671E4
	lwz      r0, 8(r31)
	clrlwi   r0, r0, 0x1e
	cmplwi   r0, 2
	bne      lbl_800673F4
	lfs      f0, 0x24(r31)
	lis      r3, j3dSys@ha
	lfs      f3, 0x18(r31)
	addi     r3, r3, j3dSys@l
	addi     r4, r1, 0x38
	addi     r5, r31, 0x54
	fmuls    f0, f0, f3
	stfs     f0, 0x38(r1)
	lfs      f0, 0x28(r31)
	lfs      f2, 0x1c(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x3c(r1)
	lfs      f0, 0x2c(r31)
	lfs      f1, 0x20(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x40(r1)
	lfs      f0, 0x30(r31)
	stfs     f0, 0x44(r1)
	lfs      f0, 0x34(r31)
	fmuls    f0, f0, f3
	stfs     f0, 0x48(r1)
	lfs      f0, 0x38(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x4c(r1)
	lfs      f0, 0x3c(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x50(r1)
	lfs      f0, 0x40(r31)
	stfs     f0, 0x54(r1)
	lfs      f0, 0x44(r31)
	fmuls    f0, f0, f3
	stfs     f0, 0x58(r1)
	lfs      f0, 0x48(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x5c(r1)
	lfs      f0, 0x4c(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x60(r1)
	lfs      f0, 0x50(r31)
	stfs     f0, 0x64(r1)
	bl       PSMTXConcat
	b        lbl_800673F4

lbl_800671E4:
	lwz      r4, 8(r31)
	li       r3, 0
	rlwinm.  r5, r4, 0, 0x1d, 0x1d
	beq      lbl_80067200
	rlwinm.  r0, r4, 0, 0x1c, 0x1c
	beq      lbl_80067200
	li       r3, 1

lbl_80067200:
	clrlwi.  r0, r3, 0x18
	beq      lbl_800672BC
	clrlwi   r0, r4, 0x1e
	cmplwi   r0, 2
	bne      lbl_800673F4
	lfs      f0, 0x24(r31)
	lis      r3, j3dSys@ha
	lfs      f3, 0x18(r31)
	addi     r3, r3, j3dSys@l
	addi     r4, r1, 8
	addi     r5, r31, 0x54
	fmuls    f0, f0, f3
	stfs     f0, 8(r1)
	lfs      f0, 0x28(r31)
	lfs      f2, 0x1c(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0xc(r1)
	lfs      f0, 0x2c(r31)
	lfs      f1, 0x20(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x10(r1)
	lfs      f0, 0x30(r31)
	stfs     f0, 0x14(r1)
	lfs      f0, 0x34(r31)
	fmuls    f0, f0, f3
	stfs     f0, 0x18(r1)
	lfs      f0, 0x38(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x1c(r1)
	lfs      f0, 0x3c(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x20(r1)
	lfs      f0, 0x40(r31)
	stfs     f0, 0x24(r1)
	lfs      f0, 0x44(r31)
	fmuls    f0, f0, f3
	stfs     f0, 0x28(r1)
	lfs      f0, 0x48(r31)
	fmuls    f0, f0, f2
	stfs     f0, 0x2c(r1)
	lfs      f0, 0x4c(r31)
	fmuls    f0, f0, f1
	stfs     f0, 0x30(r1)
	lfs      f0, 0x50(r31)
	stfs     f0, 0x34(r1)
	bl       PSMTXConcat
	b        lbl_800673F4

lbl_800672BC:
	cmplwi   r5, 0
	beq      lbl_80067334
	lwz      r3, 0x84(r31)
	clrlwi   r4, r4, 0x1e
	addi     r5, r31, 0x18
	addi     r6, r31, 0x24
	bl       calcDrawMtx__12J3DMtxBufferFUlRC3VecRA3_A4_Cf
	mr       r3, r31
	bl       calcNrmMtx__8J3DModelFv
	mr       r3, r31
	bl       calcBumpMtx__8J3DModelFv
	lwz      r5, 0x84(r31)
	lwz      r3, 4(r31)
	lwz      r4, 0x30(r5)
	lhz      r0, 0x44(r3)
	lwz      r5, 0x18(r5)
	slwi     r3, r4, 2
	mulli    r4, r0, 0x30
	lwzx     r3, r5, r3
	bl       DCStoreRangeNoSync
	lwz      r5, 0x84(r31)
	lwz      r3, 4(r31)
	lwz      r4, 0x30(r5)
	lhz      r0, 0x44(r3)
	lwz      r5, 0x20(r5)
	slwi     r3, r4, 2
	mulli    r4, r0, 0x24
	lwzx     r3, r5, r3
	bl       DCStoreRange
	b        lbl_800673F4

lbl_80067334:
	rlwinm.  r0, r4, 0, 0x1c, 0x1c
	beq      lbl_80067380
	lwz      r3, 0x84(r31)
	clrlwi   r4, r4, 0x1e
	addi     r5, r31, 0x18
	addi     r6, r31, 0x24
	bl       calcDrawMtx__12J3DMtxBufferFUlRC3VecRA3_A4_Cf
	mr       r3, r31
	bl       calcBBoardMtx__8J3DModelFv
	lwz      r5, 0x84(r31)
	lwz      r3, 4(r31)
	lwz      r4, 0x30(r5)
	lhz      r0, 0x44(r3)
	lwz      r5, 0x18(r5)
	slwi     r3, r4, 2
	mulli    r4, r0, 0x30
	lwzx     r3, r5, r3
	bl       DCStoreRange
	b        lbl_800673F4

lbl_80067380:
	lwz      r3, 0x84(r31)
	clrlwi   r4, r4, 0x1e
	addi     r5, r31, 0x18
	addi     r6, r31, 0x24
	bl       calcDrawMtx__12J3DMtxBufferFUlRC3VecRA3_A4_Cf
	mr       r3, r31
	bl       calcNrmMtx__8J3DModelFv
	mr       r3, r31
	bl       calcBBoardMtx__8J3DModelFv
	mr       r3, r31
	bl       calcBumpMtx__8J3DModelFv
	lwz      r5, 0x84(r31)
	lwz      r3, 4(r31)
	lwz      r4, 0x30(r5)
	lhz      r0, 0x44(r3)
	lwz      r5, 0x18(r5)
	slwi     r3, r4, 2
	mulli    r4, r0, 0x30
	lwzx     r3, r5, r3
	bl       DCStoreRangeNoSync
	lwz      r5, 0x84(r31)
	lwz      r3, 4(r31)
	lwz      r4, 0x30(r5)
	lhz      r0, 0x44(r3)
	lwz      r5, 0x20(r5)
	slwi     r3, r4, 2
	mulli    r4, r0, 0x24
	lwzx     r3, r5, r3
	bl       DCStoreRange

lbl_800673F4:
	mr       r3, r31
	bl       prepareShapePackets__8J3DModelFv
	lwz      r0, 0x74(r1)
	lwz      r31, 0x6c(r1)
	mtlr     r0
	addi     r1, r1, 0x70
	blr
	*/
}

/*
 * --INFO--
 * Address:	80067410
 * Size:	000024
 */
void J3DModel::calcNrmMtx() { mMtxBuffer->calcNrmMtx(); }

/*
 * --INFO--
 * Address:	80067434
 * Size:	000100
 */
void J3DModel::calcBumpMtx()
{
	if (getModelData()->checkBumpFlag() == 1) {
		u32 bumpMtxIdx  = 0;
		u16 materialNum = getModelData()->getMaterialNum();

		for (u16 i = 0; i < materialNum; i++) {
			J3DMaterial* material = getModelData()->getMaterialNodePointer(i);
			if (material->getNBTScale()->mbHasScale == 1) {
				material->getShape()->calcNBTScale(*material->getNBTScale()->getScale(), getNrmMtxPtr(), getBumpMtxPtr(bumpMtxIdx));
				DCStoreRange(getBumpMtxPtr(bumpMtxIdx), getModelData()->getDrawMtxNum() * 0x24);
				bumpMtxIdx++;
			}
		}
	}

	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	stmw     r25, 0x14(r1)
	mr       r28, r3
	lwz      r3, 4(r3)
	lhz      r0, 0xc(r3)
	cmplwi   r0, 1
	bne      lbl_80067520
	lhz      r31, 0x5c(r3)
	li       r29, 0
	li       r30, 0
	b        lbl_80067514

lbl_80067468:
	lwz      r3, 4(r28)
	rlwinm   r0, r29, 2, 0xe, 0x1d
	lwz      r3, 0x60(r3)
	lwzx     r27, r3, r0
	lwz      r3, 0x28(r27)
	lwz      r12, 0(r3)
	lwz      r12, 0x5c(r12)
	mtctr    r12
	bctrl
	lbz      r0, 0(r3)
	cmplwi   r0, 1
	bne      lbl_80067510
	lwz      r6, 0x84(r28)
	lwz      r3, 0x28(r27)
	lwz      r4, 0x28(r6)
	lwz      r12, 0(r3)
	lwz      r0, 0x30(r6)
	lwzx     r5, r4, r30
	slwi     r0, r0, 2
	lwz      r4, 0x20(r6)
	lwz      r12, 0x5c(r12)
	lwzx     r26, r5, r0
	lwzx     r25, r4, r0
	mtctr    r12
	bctrl
	mr       r4, r3
	lwz      r3, 8(r27)
	mr       r5, r25
	mr       r6, r26
	addi     r4, r4, 4
	bl       calcNBTScale__8J3DShapeFRC3VecPA3_A3_fPA3_A3_f
	lwz      r4, 0x84(r28)
	lwz      r3, 4(r28)
	lwz      r5, 0x28(r4)
	lwz      r4, 0x30(r4)
	lhz      r0, 0x44(r3)
	lwzx     r5, r5, r30
	slwi     r3, r4, 2
	mulli    r4, r0, 0x24
	lwzx     r3, r5, r3
	bl       DCStoreRange
	addi     r30, r30, 4

lbl_80067510:
	addi     r29, r29, 1

lbl_80067514:
	clrlwi   r0, r29, 0x10
	cmplw    r0, r31
	blt      lbl_80067468

lbl_80067520:
	lmw      r25, 0x14(r1)
	lwz      r0, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	80067534
 * Size:	000034
 */
void J3DModel::calcBBoardMtx()
{
	if (mModelData->mBillboardFlag == 1) {
		mMtxBuffer->calcBBoardMtx();
	}
}

/*
 * --INFO--
 * Address:	80067568
 * Size:	000064
 */
void J3DModel::prepareShapePackets()
{
	u16 shapeNum = getModelData()->getShapeNum();

	for (u16 i = 0; i < shapeNum; i++) {
		J3DShape* xx        = mModelData->getShapeNodePointer(i);
		J3DShapePacket* pkt = getShapePacket(i);
		pkt->setMtxBuffer(mMtxBuffer);
		if (getMtxCalcMode() == 2) {
			pkt->setBaseMtxPtr(&mInternalView);
		} else {
			pkt->setBaseMtxPtr(&j3dSys.mViewMtx);
		}
	}

	/*
	lwz      r6, 4(r3)
	lis      r4, j3dSys@ha
	addi     r5, r3, 0x54
	li       r9, 0
	lhz      r8, 0x7c(r6)
	addi     r4, r4, j3dSys@l
	b        lbl_800675BC

lbl_80067584:
	clrlwi   r0, r9, 0x10
	lwz      r7, 0xc4(r3)
	mulli    r6, r0, 0x3c
	lwz      r0, 0x84(r3)
	add      r6, r7, r6
	stw      r0, 0x2c(r6)
	lwz      r0, 8(r3)
	clrlwi   r0, r0, 0x1e
	cmplwi   r0, 2
	bne      lbl_800675B4
	stw      r5, 0x30(r6)
	b        lbl_800675B8

lbl_800675B4:
	stw      r4, 0x30(r6)

lbl_800675B8:
	addi     r9, r9, 1

lbl_800675BC:
	clrlwi   r0, r9, 0x10
	cmplw    r0, r8
	blt      lbl_80067584
	blr
	*/
}
