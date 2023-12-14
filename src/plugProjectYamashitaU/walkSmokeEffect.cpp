#include "types.h"
#include "Game/WalkSmokeEffect.h"
#include "JSystem/JUtility/JUTException.h"
#include "Game/EnemyBase.h"
#include "Game/MapMgr.h"
#include "SysShape/Model.h"
#include "SysShape/Joint.h"
#include "efx/TEnemyWalkSmoke.h"

const char filename[] = "walkSmoke";

namespace Game {
namespace WalkSmokeEffect {

/*
 * --INFO--
 * Address:	8012A320
 * Size:	000034
 */
Obj::Obj()
{
	mIsEffectCreated = false;
	mMatrix          = nullptr;
	mHeightOffset    = 0.0f;
	mPosition        = Vector3f::zero;
}

void Obj::update(EnemyBase* enemy)
{
	Vector3f pos;
	mMatrix->getTranslation(pos);
	pos.y -= mHeightOffset;

	if (!mIsEffectCreated) {
		if ((pos.y - mPosition.y) < 0.0f) {
			if (pos.y < mapMgr->getMinY(pos)) {
				if (!enemy->inWater()) {
					f32 scaleMod                      = enemy->mScaleModifier;
					EnemyTypeID::EEnemyTypeID enemyID = enemy->getEnemyTypeID();

					efx::ArgEnemyType effectArg(pos, enemyID, scaleMod);
					efx::TEnemyWalkSmoke walkSmoke;
					walkSmoke.create(&effectArg);
				}

				mIsEffectCreated = true;
			}
		}
	} else if (pos.y > mapMgr->getMinY(pos)) {
		mIsEffectCreated = false;
	}

	mPosition = pos;
}

/*
 * --INFO--
 * Address:	8012A354
 * Size:	000010
 */
Mgr::Mgr()
{
	mNumObjects = 0;
	mObjects    = nullptr;
}

/*
 * --INFO--
 * Address:	8012A364
 * Size:	0000B4
 */
void Mgr::alloc(int count)
{
	if (mObjects == nullptr) {
		mNumObjects = count;
		mObjects    = new Obj[mNumObjects];

		if (mObjects == nullptr) {
			// failed to allocate an object array
			JUT_PANICLINE(168, "alloc error\n");
		}

	} else {
		// object array already allocated
		JUT_PANICLINE(173, "second alloc");
	}
}

/*
 * --INFO--
 * Address:	8012A418
 * Size:	0001C8
 */
void Mgr::update(EnemyBase* enemy)
{
	for (int i = 0; i < mNumObjects; i++) {
		mObjects[i].update(enemy);
	}
}

/*
 * --INFO--
 * Address:	8012A5E0
 * Size:	000090
 */
void Mgr::setup(int objIdx, SysShape::Model* model, char* name, f32 heightOffset)
{
	Matrixf* worldMat = model->getJoint(name)->getWorldMatrix();

	Obj* obj           = &mObjects[objIdx];
	obj->mMatrix       = worldMat;
	obj->mHeightOffset = heightOffset;

	obj->mMatrix->getTranslation(obj->mPosition);

	obj->mIsEffectCreated = true;
}
} // namespace WalkSmokeEffect
} // namespace Game
