#include "nans.h"
#include "sysMath.h"
#include "Light.h"

// Fix rodata mismatch with null bytes
static const char _RODATA_FIX[0xC] = { '\0' };

namespace TreasureLight {
/*
 * --INFO--
 * Address:	8013286C
 * Size:	000150
 */
Mgr::Mgr()
    : LightMgr("���󃉃C�g")
{
	mRotationAngle  = 300.0f;
	mElevationAngle = 330.0f;

	mMainLight             = new LightObj("���C�����C�g", GX_LIGHT0, TYPE_2, JUtility::TColor(0xFF, 0xFF, 0xFF, 0xFF));
	mMainLight->mSpotFn    = 3;
	mMainLight->mElevation = Vector3f(0.0f, -1.0f, 0.0f);
	registLightObj(mMainLight);

	mSpecLight          = new LightObj("�X�y�L����-���C�g", GX_LIGHT7, TYPE_4, JUtility::TColor(0xFF, 0xFF, 0xFF, 0xFF));
	mSpecLight->mKScale = 40.0f;
	registLightObj(mSpecLight);

	mAmbientLight.mColor = Color4(0x32, 0x32, 0x32, 0xFF);
}

/*
 * --INFO--
 * Address:	801329BC
 * Size:	000004
 */
void Mgr::update() { }

/*
 * --INFO--
 * Address:	801329C0
 * Size:	000044
 */
void Mgr::set(Graphics& gfx)
{
	setCommonProc();
	LightMgr::set(gfx);
}

/*
 * --INFO--
 * Address:	80132A04
 * Size:	000044
 */
void Mgr::set(Matrixf& mtx)
{
	setCommonProc();
	LightMgr::set(mtx);
}

/*
 * --INFO--
 * Address:	80132A48
 * Size:	000184
 * Credits: Altafen
 *
 * https://en.wikipedia.org/wiki/Spherical_coordinate_system
 * You can convert an angle �� to its position on a circle of radius r:
 * x = r * cos(��)
 * y = r * sin(��)
 *
 * So now imagine a line going in the direction of the 2D angle where
 * y is now height, x is now how far away it is from the center pole
 *
 * height   = r * sin(��)
 * distance = r * cos(��)
 *
 * Since the 2D x/y have to shrink a bit as the sphere gets smaller the
 * higher you go, use distance as the radius before putting them in the
 * 2D equations, and you get
 *
 * x = (r * cos(��)) * cos(��)
 * y = (r * cos(��)) * sin(��)
 * z = r * sin(��)
 *
 * For pikmin it's slightly different (y/z swap)
 */
void Mgr::setCommonProc()
{
	f32 rotation_angle  = (mRotationAngle * DEG2RAD) * PI;
	f32 elevation_angle = (mElevationAngle * DEG2RAD) * PI;

	f32 radius = 3000.0f;
	Vector3f rotation;
	rotation.x = pikmin2_cosf(elevation_angle) * radius * pikmin2_sinf(rotation_angle);
	rotation.y = pikmin2_sinf(elevation_angle) * -radius;
	rotation.z = pikmin2_cosf(elevation_angle) * radius * pikmin2_cosf(rotation_angle);

	Vector3f elevation(-rotation.x, -rotation.y, -rotation.z);

	f32 dist = pikmin2_sqrtf(VECTOR_SQUARE_MAG(elevation));
	if (dist > 0.0f) {
		elevation.x *= 1 / dist;
		elevation.y *= 1 / dist;
		elevation.z *= 1 / dist;
	}

	mMainLight->mPosition      = rotation;
	mMainLight->mElevation     = elevation;
	mMainLight->mRefBrightness = 0.85f;

	mSpecLight->mPosition  = rotation;
	mSpecLight->mElevation = elevation;
}

/*
 * --INFO--
 * Address:	80132BCC
 * Size:	000020
 */
void Mgr::drawDebugInfo(Graphics& gfx) { LightMgr::drawDebugInfo(gfx); }
} // namespace TreasureLight
