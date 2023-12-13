#pragma once

#include "vec.h"

class WeaponCompleteDefArr
{
public:
	class WeaponCompleteDef* weaponCompleteDefArr[962]; //0x0000
};

class WeaponCompleteDef
{
public:
	char pad_0000[8]; //0x0000
	class WeaponDef* weapDef; //0x0008
	char pad_0010[120]; //0x0010
}; //Size: 0x0088
static_assert(sizeof(WeaponCompleteDef) == 0x88);

struct XModel;
struct WeaponAnimPackage;
struct XAnimParts;

struct WeaponDamageCommon
{
	int minDamage;
	int mid1Damage;
	int mid2Damage;
	int mid3Damage;
	int damage;
	float maxDamageRange;
	float mid1DamageRange;
	float mid2DamageRange;
	float mid3DamageRange;
	float minDamageRange;
};

enum AnimDamageType : __int32
{
	ANIM_DAMAGETYPE_NONE = 0x0,
	ANIM_DAMAGETYPE_EXPLOSION_LIGHT = 0x1,
	ANIM_DAMAGETYPE_EXPLOSION = 0x2,
	ANIM_DAMAGETYPE_MELEE = 0x3,
	ANIM_DAMAGETYPE_MELEE_DOG = 0x4,
	ANIM_DAMAGETYPE_MELEE_ALIEN = 0x5,
	ANIM_DAMAGETYPE_ENERGY_BULLET = 0x6,
	ANIM_DAMAGETYPE_FIRE_EXPLOSION = 0x7,
	ANIM_DAMAGETYPE_BULLET_SM = 0x8,
	ANIM_DAMAGETYPE_BULLET_MD = 0x9,
	ANIM_DAMAGETYPE_BULLET_LG = 0xA,
	ANIM_DAMAGETYPE_FALL = 0xB,
	ANIM_DAMAGETYPE_COUNT = 0xC,
};

struct WeaponDamageInfo
{
	WeaponDamageCommon damageData[3];
	AnimDamageType deathAnimDamageType;
	float terminateAtRange;
};

enum scr_string_t : __int32
{
};

struct FxCombinedDef
{
};

enum scriptedAnimEvent_t : __int32
{
	SCRIPTEDANIMEVENT_POWER_ACTIVE = 0x0,
	SCRIPTEDANIMEVENT_POWER_ACTIVE_CP = 0x1,
	SCRIPTEDANIMEVENT_COUNT = 0x2,
};

enum weapType_t : __int32
{
	WEAPTYPE_NONE = 0x0,
	WEAPTYPE_MODEL_ONLY = 0x1,
	WEAPTYPE_BULLET = 0x2,
	WEAPTYPE_GRENADE = 0x3,
	WEAPTYPE_PROJECTILE = 0x4,
	WEAPTYPE_RIOTSHIELD = 0x5,
	WEAPTYPE_SCRIPT = 0x6,
	WEAPTYPE_SHIELD = 0x7,
	WEAPTYPE_CHARGE_SHIELD = 0x8,
	WEAPTYPE_LOCATION_SELECT = 0x9,
	WEAPTYPE_EQUIP_DEPLOY = 0xA,
	WEAPTYPE_NUM = 0xB,
};

enum weapClass_t : __int32
{
	WEAPCLASS_RIFLE = 0x0,
	WEAPCLASS_SNIPER = 0x1,
	WEAPCLASS_MG = 0x2,
	WEAPCLASS_SMG = 0x3,
	WEAPCLASS_SPREAD = 0x4,
	WEAPCLASS_PISTOL = 0x5,
	WEAPCLASS_GRENADE = 0x6,
	WEAPCLASS_ROCKETLAUNCHER = 0x7,
	WEAPCLASS_TURRET = 0x8,
	WEAPCLASS_THROWINGKNIFE = 0x9,
	WEAPCLASS_NON_PLAYER = 0xA,
	WEAPCLASS_ITEM = 0xB,
	WEAPCLASS_BEAM = 0xC,
	WEAPCLASS_BALL = 0xD,
	WEAPCLASS_NONE = 0xE,
	WEAPCLASS_NUM = 0xF,
};

enum PenetrateType : __int32
{
	PENETRATE_TYPE_NONE = 0x0,
	PENETRATE_TYPE_SMALL = 0x1,
	PENETRATE_TYPE_MEDIUM = 0x2,
	PENETRATE_TYPE_LARGE = 0x3,
	PENETRATE_TYPE_MAXIMUM = 0x4,
	PENETRATE_TYPE_TABLE_ENTRY_COUNT = 0x4,
	PENETRATE_TYPE_RICOCHET = 0x5,
	PENETRATE_TYPE_COUNT = 0x6,
};

enum weapInventoryType_t : __int32
{
	WEAPINVENTORY_PRIMARY = 0x0,
	WEAPINVENTORY_OFFHAND = 0x1,
	WEAPINVENTORY_ITEM = 0x2,
	WEAPINVENTORY_ALTMODE = 0x3,
	WEAPINVENTORY_EXCLUSIVE = 0x4,
	WEAPINVENTORY_SCAVENGER = 0x5,
	WEAPINVENTORY_MODEL_ONLY = 0x6,
	WEAPINVENTORYCOUNT = 0x7,
};

enum weapFireType_t : __int32
{
	WEAPON_FIRETYPE_FULLAUTO = 0x0,
	WEAPON_FIRETYPE_SINGLESHOT = 0x1,
	WEAPON_FIRETYPE_BURST = 0x2,
	WEAPON_FIRETYPE_DOUBLEBARREL = 0x3,
	WEAPON_FIRETYPE_DOUBLEBARREL_DUALTRIGGER = 0x4,
	WEAPON_FIRETYPE_BEAM = 0x5,
	WEAPON_FIRETYPECOUNT = 0x6,
};

enum turretFireType_t : __int32
{
	TURRET_SINGLE_FIRE = 0x0,
	TURRET_ALTERNATE_FIRE = 0x1,
	TURRET_FIRE_TYPE_COUNT = 0x2,
};

enum targetAssistType_t : __int32
{
	TARGET_ASSISTTYPPE_DEFAULT = 0x0,
	TARGET_ASSISTTYPPE_CONE = 0x1,
	TARGET_ASSISTTYPPE_COUNT = 0x2,
};

enum targetAssistBehavior_t : __int32
{
	TARGET_ASSISTBEHAVE_DEFAULT = 0x0,
	TARGET_ASSISTBEHAVE_DIRECT_DAMAGE = 0x1,
	TARGET_ASSISTBEHAVE_TARGET_ONLY = 0x2,
	TARGET_ASSISTBEHAVE_BEAM = 0x3,
	TARGET_ASSISTBEHAVE_SMART_PELLET = 0x4,
	TARGET_ASSISTBEHAVE_COUNT = 0x5,
};

enum ReloadType : __int32
{
	RELOAD_TYPE_NORMAL = 0x0,
	RELOAD_TYPE_SEGMENTED = 0x1,
	RELOAD_TYPE_MULTIPLE_BULLET = 0x2,
	RELOAD_TYPE_MULTIPLE_PERCENTAGE = 0x3,
	RELOAD_TYPE_COUNT = 0x4,
};

enum OffhandClass : __int32
{
	OFFHAND_CLASS_NONE = 0x0,
	OFFHAND_CLASS_FRAG_GRENADE = 0x1,
	OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
	OFFHAND_CLASS_FLASH_GRENADE = 0x3,
	OFFHAND_CLASS_MOLOTOV = 0x4,
	OFFHAND_CLASS_THROWINGKNIFE = 0x5,
	OFFHAND_CLASS_SHIELD = 0x6,
	OFFHAND_CLASS_OTHER = 0x7,
	OFFHAND_CLASS_COUNT = 0x8,
};

enum weapStance_t : __int32
{
	WEAPSTANCE_STAND = 0x0,
	WEAPSTANCE_DUCK = 0x1,
	WEAPSTANCE_PRONE = 0x2,
	WEAPSTANCE_NUM = 0x3,
};

enum ReticleType : __int32
{
	RETICLE_TYPE_FOUR_SIDED = 0x0,
	RETICLE_TYPE_ONE_PIECE = 0x1,
	RETICLE_TYPE_COUNT = 0x2,
};

enum HitmarkerType : __int32
{
	HITMARKER_TYPE_SMALL = 0x0,
	HITMARKER_TYPE_MEDIUM = 0x1,
	HITMARKER_TYPE_LARGE = 0x2,
	HITMARKER_TYPE_COUNT = 0x3,
};

enum activeReticleType_t : __int32
{
	VEH_ACTIVE_RETICLE_NONE = 0x0,
	VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
	VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
	VEH_ACTIVE_RETICLE_COUNT = 0x3,
};

enum turret3pAnimType_t : __int32
{
	TURRET_3PANIM_MOUNTED = 0x0,
	TURRET_3PANIM_MOUNTED_INPLACE = 0x1,
	TURRET_3PANIM_MOUNTED_INPLACE_LEAN = 0x2,
	TURRET_3PANIM_COUNT = 0x3,
};

enum ammoCounterClipType_t : __int32
{
	AMMO_COUNTER_CLIP_NONE = 0x0,
	AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
	AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
	AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
	AMMO_COUNTER_CLIP_ROCKET = 0x4,
	AMMO_COUNTER_CLIP_BELTFED = 0x5,
	AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
	AMMO_COUNTER_CLIP_COUNT = 0x7,
};
enum weapOverlayReticle_t : __int32
{
	WEAPOVERLAYRETICLE_NONE = 0x0,
	WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
	WEAPOVERLAYRETICLE_NUM = 0x2,
};

struct WeaponVFXPackage;
struct WeaponSFXPackage;
struct Material;

enum AdsOffsetInterpolationType : __int32
{
	ADS_OFFSET_INTERP_TYPE_LINEAR = 0x0,
	ADS_OFFSET_INTERP_TYPE_EASEINOUTSINE = 0x1,
	ADS_OFFSET_INTERP_TYPE_EASEINOUTSMOOTHERSTEP = 0x2,
	ADS_OFFSET_INTERP_TYPE_EASEINCUBIC = 0x3,
	ADS_OFFSET_INTERP_TYPE_EASEOUTCUBIC = 0x4,
	ADS_OFFSET_INTERP_TYPE_EASEINQUARTIC = 0x5,
	ADS_OFFSET_INTERP_TYPE_EASEOUTQUARTIC = 0x6,
	ADS_OFFSET_INTERP_TYPE_EASEINEXPO = 0x7,
	ADS_OFFSET_INTERP_TYPE_EASEOUTEXPO = 0x8,
	ADS_OFFSET_INTERP_TYPE_COUNT = 0x9,
};

struct GfxImage;

struct __declspec(align(8)) ADSOverlay
{
	Material* shaderMat;
	Material* shaderLowResMat;
	Material* shaderEMPMat;
	Material* shaderEMPLowResMat;
	GfxImage* shaderImg;
	GfxImage* shaderLowResImg;
	GfxImage* shaderEMPImg;
	GfxImage* shaderEMPLowResImg;
	bool applyVisionSet;
	weapOverlayReticle_t reticle;
	float width;
	float height;
	float widthSplitscreen;
	float heightSplitscreen;
	const char* visionSetName;
	float visionSetADSFraction;
	int visionSetBlendInTimeMs;
	int visionSetBlendOutTimeMs;
};

enum WeapOverlayInteface_t : __int32
{
	WEAPOVERLAYINTERFACE_NONE = 0x0,
	WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
	WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
	WEAPOVERLAYINTERFACE_BINOCULARS = 0x3,
	WEAPOVERLAYINTERFACECOUNT = 0x4,
};

struct CommonSwaySettings
{
	float maxAngle;
	float lerpSpeed;
	float pitchScale;
	float yawScale;
	float horizScale;
	float vertScale;
	float gunAngleScale;
};

struct HipSwaySettings
{
	CommonSwaySettings common;
	float maxAngleSteadyAim;
};

struct AdsSwaySettings
{
	CommonSwaySettings common;
	float swayTransitionLerpSpeed;
	float adsSwayScale[3];
};

struct RumbleGraph;



struct __declspec(align(4)) SwaySettings
{
	HipSwaySettings hip;
	AdsSwaySettings ads;
	//AdvancedHipSwaySettings adv;
	float shellShockScale;
	bool overrideHip;
	bool overrideAds;
};

enum weaponIconRatioType_t : __int32
{
	WEAPON_ICON_RATIO_1TO1 = 0x0,
	WEAPON_ICON_RATIO_2TO1 = 0x1,
	WEAPON_ICON_RATIO_4TO1 = 0x2,
	WEAPON_ICON_RATIO_COUNT = 0x3,
};

enum weapProjExposion_t : __int32
{
	WEAPPROJEXP_GRENADE = 0x0,
	WEAPPROJEXP_ROCKET = 0x1,
	WEAPPROJEXP_FLASHBANG = 0x2,
	WEAPPROJEXP_MOLOTOV = 0x3,
	WEAPPROJEXP_NONE = 0x4,
	WEAPPROJEXP_DUD = 0x5,
	WEAPPROJEXP_SMOKE = 0x6,
	WEAPPROJEXP_HEAVY = 0x7,
	WEAPPROJEXP_NUM = 0x8,
};

enum WeapStickinessType : __int32
{
	WEAPSTICKINESS_NONE = 0x0,
	WEAPSTICKINESS_ALL = 0x1,
	WEAPSTICKINESS_ALL_ORIENT = 0x2,
	WEAPSTICKINESS_GROUND = 0x3,
	WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
	WEAPSTICKINESS_GROUND_ORIENT = 0x5,
	WEAPSTICKINESS_KNIFE = 0x6,
	WEAPSTICKINESS_COUNT = 0x7,
};

enum guidedMissileType_t : __int32
{
	MISSILE_GUIDANCE_NONE = 0x0,
	MISSILE_GUIDANCE_SIDEWINDER = 0x1,
	MISSILE_GUIDANCE_HELLFIRE = 0x2,
	MISSILE_GUIDANCE_JAVELIN = 0x3,
	MISSILE_GUIDANCE_ROBOTECH = 0x4,
	MISSILE_GUIDANCE_SOFTLOCKON = 0x5,
	MISSILE_GUIDANCE_COUNT = 0x6,
};

enum WeaponOffsetBlendInterpolationType : __int32
{
	WOBIT_LINEAR = 0x0,
	WOBIT_CUBIC_EASE_IN = 0x1,
	WOBIT_CUBIC_EASE_OUT = 0x2,
	WOBIT_QUARTIC_EASE_IN = 0x3,
	WOBIT_QUARTIC_EASE_OUT = 0x4,
	WOBIT_EXPONENTIAL_EASE_IN = 0x5,
	WOBIT_EXPONENTIAL_EASE_OUT = 0x6,
	NUM_WEAPON_OFFSET_BLEND_INTERPOLATION_TYPES = 0x7,
};

struct WeaponOffsetCurveDescription
{
	float blendTime;
	float decayTime;
	float shotDecayFireTimeFrac;
	float holdTime;
	float adsFractionBegin;
	float adsFractionEnd;
	WeaponOffsetBlendInterpolationType interpType;
	WeaponOffsetBlendInterpolationType interpTypeOut;
};

enum WeaponOffsetBlendCurveId : __int32
{
	WOBC_HOLD_FIRE_BLEND_SLOW = 0x0,
	WOBC_HOLD_FIRE_BLEND_FAST = 0x1,
	WOBC_KICK_BLEND = 0x2,
	WOBC_SNAP_DECAY_BLEND = 0x3,
	WOBC_ADS_BLEND = 0x4,
	WOBC_ALWAYS_ON = 0x5,
	NUM_WEAPON_OFFSET_BLEND_CURVES = 0x6,
};

enum WeaponOffsetPatternId : __int32
{
	WOP_KEYFRAME = 0x0,
	WOP_NOISY_SINE = 0x1,
	WOP_RANDOM_SQUARE = 0x2,
	WOP_SINE = 0x3,
	NUM_WEAPON_OFFSET_PATTERNS = 0x4,
};

enum WeaponOffsetTransformType : __int32
{
	WOTT_VIEW_ORIGIN = 0x0,
	WOTT_VIEW_ANGLES = 0x1,
	WOTT_WEAPON_ORIGIN = 0x2,
	WOTT_WEAPON_ANGLES = 0x3,
	NUM_WEAPON_OFFSET_TRANSFORM_TYPES = 0x4,
};

struct WeaponOffsetPatternDescription
{
	bool active;
	scr_string_t patternKey;
	WeaponOffsetBlendCurveId curveType;
	WeaponOffsetPatternId patternType;
	WeaponOffsetTransformType transformType;
	float frequency;
	float blendTime;
	Vector3 magnitude;
	float hipScale;
	float rotationOffset;
	float bulletDirScale;
	float fullAutoScale;
	int fullAutoBullets;
	float fullAutoDecay;
	int referenceIndex;
	int kickOrSnapDecayIndex;
};

struct RumbleInfo;

enum tracerStyle_t : __int32
{
	TRACERSTYLE_TRACER = 0x0,
	TRACERSTYLE_BEAM = 0x1,
	TRACERSTYLE_NUM = 0x2,
};

struct TracerDef;
struct LaserDef;

struct SndAliasLookup
{
	const char* name;
};

enum offhandShieldMaxSpeed_t : __int32
{
	WEAP_OFFHAND_SHIELD_SPEED_WALK = 0x0,
	WEAP_OFFHAND_SHIELD_SPEED_RUN = 0x1,
	WEAP_OFFHAND_SHIELD_SPEED_SPRINT = 0x2,
	WEAP_OFFHAND_SHIELD_SPEED_COUNT = 0x3,
};

struct Gesture;

enum offhandShieldButton_t : __int32
{
	WEAP_OFFHAND_SHIELD_BUTTON_DEFAULT = 0x0,
	WEAP_OFFHAND_SHIELD_BUTTON_ADS = 0x1,
	WEAP_OFFHAND_SHIELD_BUTTON_COUNT = 0x2,
};

struct LaserSettings
{
	bool forceLaserOn;
	bool localPlayerADSLaserEnabled;
	bool localPlayerHipLaserEnabled;
	bool localPlayerNVGADSLaserEnabled;
	bool localPlayerNVGHipLaserEnabled;
	bool remotePlayerADSLaserEnabled;
	bool remotePlayerHipLaserEnabled;
	bool remotePlayerNVGADSLaserEnabled;
	bool remotePlayerNVGHipLaserEnabled;
	bool laserViewCenterInAds;
};

enum DualWieldType : __int32
{
	DUAL_WIELD_TYPE_DEFAULT = 0x0,
	DUAL_WIELD_TYPE_ALT_MODE = 0x1,
	DUAL_WIELD_TYPE_COUNT = 0x2,
};

enum WeapDetonateType : __int32
{
	DETONATE_TYPE_NONE = 0x0,
	DETONATE_TYPE_GESTURE = 0x1,
	DETONATE_TYPE_VIEWMODEL = 0x2,
	DETONATE_TYPE_COUNT = 0x3,
};

enum GrenadeRotationDirection : __int32
{
	GRD_RANDOM = 0x0,
	GRD_CLOCKWISE = 0x1,
	GRD_COUNTERCLOCKWISE = 0x2,
	GRD_COUNT = 0x3,
};

struct __declspec(align(4)) GrenadeRotationParams
{
	float initialPitch;
	float initialYaw;
	float initialRoll;
	GrenadeRotationDirection rotationPitchDir;
	int rotationPitchMin;
	int rotationPitchMax;
	GrenadeRotationDirection rotationYawDir;
	int rotationYawMin;
	int rotationYawMax;
	GrenadeRotationDirection rotationRollDir;
	int rotationRollMin;
	int rotationRollMax;
	bool rotate;
};

//enum WeaponChargeType : __int32
//{
//	NONE = 0x0,
//	HALF = 0x1,
//	HALF_HALF = 0x2,
//	LONG = 0x3,
//	LONG_LONG = 0x4,
//	MAX_INT = 0x5,
//	SIZE_T = 0x6,
//	PTRDIFF = 0x7,
//	LONG_DOUBLE = 0x8,
//};
//
//enum ParticleGroupID : __int32
//{
//	NONE = 0x0,
//	HALF = 0x1,
//	HALF_HALF = 0x2,
//	LONG = 0x3,
//	LONG_LONG = 0x4,
//	MAX_INT = 0x5,
//	SIZE_T = 0x6,
//	PTRDIFF = 0x7,
//	LONG_DOUBLE = 0x8,
//};

enum WeaponSlot : __int32
{
	WEAPON_SLOT_NONE = 0x0,
	WEAPON_SLOT_PRIMARY = 0x1,
	WEAPON_SLOT_HEAVY = 0x2,
	WEAPON_SLOT_MELEE = 0x3,
	WEAPON_SLOT_EXECUTION = 0x4,
	WEAPON_SLOT_ACCESSORY = 0x5,
	WEAPON_SLOT_NUM = 0x6,
};

enum EnergyType : __int32
{
	MOVEMENT = 0x0,
	DODGE = 0x1,
	COUNT = 0x2,
};

typedef EnergyType DeployType;

struct AnimOverride;

enum CarryObjectType : __int32
{
	CARRYOBJECTTYPE_GENERIC = 0x0,
	CARRYOBJECTTYPE_HUMAN = 0x1,
	CARRYOBJECTTYPE_COUNT = 0x2,
};

struct CarryAnimOverride
{
	CarryObjectType carryObjectType;
	WeaponAnimPackage* animPackage;
	WeaponAnimPackage* animPackageAlt;
};

struct SFXOverride;

struct VFXOverride;

struct WeaponOffsetPatternScale;

struct WeaponOffsetPatternScaleInfo
{
	int numPatternScales;
	WeaponOffsetPatternScale* patternScales;
};

struct AdvancedIdleSettings
{
	bool useAdvancedIdleSettings;
	bool useRandomPointsAlgorithm;
	float breathGaspScaleOverride;
	float idleSwaySetting1_HipBulletDirScale;
	float idleSwaySetting1_HipIdleSpeed;
	float idleSwaySetting1_HipWeaponMagnitudeX;
	float idleSwaySetting1_HipWeaponMagnitudeY;
	float idleSwaySetting1_HipWeaponMagnitudeZ;
	float idleSwaySetting1_HipWeaponMagnitudeF;
	float idleSwaySetting1_HipWeaponRotationOffset;
	float idleSwaySetting1_HipViewMagnitudeX;
	float idleSwaySetting1_HipViewMagnitudeY;
	float idleSwaySetting1_AdsBulletDirScale;
	float idleSwaySetting1_AdsIdleSpeed;
	float idleSwaySetting1_AdsWeaponMagnitudeX;
	float idleSwaySetting1_AdsWeaponMagnitudeY;
	float idleSwaySetting1_AdsWeaponMagnitudeZ;
	float idleSwaySetting1_AdsWeaponMagnitudeF;
	float idleSwaySetting1_AdsWeaponRotationOffset;
	float idleSwaySetting1_AdsViewMagnitudeX;
	float idleSwaySetting1_AdsViewMagnitudeY;
	float idleSwaySetting2_HipBulletDirScale;
	float idleSwaySetting2_HipIdleSpeed;
	float idleSwaySetting2_HipWeaponMagnitudeX;
	float idleSwaySetting2_HipWeaponMagnitudeY;
	float idleSwaySetting2_HipWeaponMagnitudeZ;
	float idleSwaySetting2_HipWeaponMagnitudeF;
	float idleSwaySetting2_HipWeaponRotationOffset;
	float idleSwaySetting2_HipViewMagnitudeX;
	float idleSwaySetting2_HipViewMagnitudeY;
	float idleSwaySetting2_AdsBulletDirScale;
	float idleSwaySetting2_AdsIdleSpeed;
	float idleSwaySetting2_AdsWeaponMagnitudeX;
	float idleSwaySetting2_AdsWeaponMagnitudeY;
	float idleSwaySetting2_AdsWeaponMagnitudeZ;
	float idleSwaySetting2_AdsWeaponMagnitudeF;
	float idleSwaySetting2_AdsWeaponRotationOffset;
	float idleSwaySetting2_AdsViewMagnitudeX;
	float idleSwaySetting2_AdsViewMagnitudeY;
};

struct BallisticInfoCalculated
{
	float* distances;
	float zeroingAngle;
	int numDistanceEntries;
};

struct BallisticInfo
{
	float muzzleVelocity;
	float ballisticCoefficient;
	float diameter;
	float mass;
	float gravityFactor;
	float zeroingDistance;
	BallisticInfoCalculated* calculated;
	bool enableBallisticTrajectory;
	int lifeTimeMs;
};

struct __declspec(align(4)) HyperBurstInfo
{
	float fireTimeFraction;
	int coolDownMs;
	bool enabled;
};

enum WeaponEntityNotifyFlags : __int32
{
	WEAP_NOTIFY_FLAG_NONE = 0x0,
	WEAP_NOFITY_FLAG_CHECK_TEAM = 0x1,
	WEAP_NOFITY_FLAG_CHECK_VISIBLE = 0x2,
};

struct WeaponEntityNotify
{
	WeaponEntityNotifyFlags flags;
	float radius;
	float height;
	float minSpeed;
};

class WeaponDef
{
public:
	const char* szOverlayName;
	XModel* gunXModel;
	XModel* gunXModelLeftHand;
	XModel* gunXModelRightHand;
	XModel* defaultViewModel;
	XModel* defaultWorldModelLeftHand;
	XModel* defaultWorldModelRightHand;
	XModel* worldModel;
	XModel* worldXModelLeftHand;
	XModel* worldXModelRightHand;
	XModel* defaultWorldModel;
	XModel* censorshipWorldModel;
	XModel* censorshipWorldModelLeftHand;
	XModel* censorshipWorldModelRightHand;
	XModel* playerShadowModel;
	XModel* playerShadowModelLeftHand;
	XModel* playerShadowModelRightHand;
	XModel* handXModel;
	WeaponAnimPackage* szXAnims;
	WeaponAnimPackage* szXAnimsRightHanded;
	WeaponAnimPackage* szXAnimsLeftHanded;
	XAnimParts* turretRaiseAnim;
	XAnimParts* turretIdleAnim;
	XAnimParts* turretFireAnim;
	WeaponDamageInfo damageInfo;
	int iFireTime;
	int iFireDelay;
	int iFireTimeAkimbo;
	int iFireDelayAkimbo;
	float sprintOutTimerScale;
	const char* szModeName;
	scr_string_t* notetrackRumbleMapKeys;
	scr_string_t* notetrackRumbleMapValues;
	scr_string_t* notetrackFXMapKeys;
	FxCombinedDef* notetrackFXMapValues;
	scr_string_t* notetrackFXMapTagValues;
	int playerAnimType;
	scriptedAnimEvent_t scriptedAnimEvent;
	int scriptedAnimType;
	weapType_t weapType;
	weapClass_t weapClass;
	PenetrateType penetrateType;
	weapInventoryType_t inventoryType;
	weapFireType_t fireType;
	turretFireType_t turretFireType;
	int burstCount;
	targetAssistType_t targetAssistType;
	targetAssistBehavior_t targetAssistBehavior;
	float targetAssistRange;
	float targetAssistAngle;
	float targetAssistLosOffsetForward;
	float targetAssistLosOffsetRight;
	float targetAssistLosOffsetUp;
	bool targetAssistOnlyAvailableInAds;
	ReloadType reloadType;
	float burstFireCooldown;
	bool burstFireAuto;
	float viewPitchMaxSpeed;
	float viewYawMaxSpeed;
	bool alignBarrelWithTurretBody;
	bool keepOrientationOnExit;
	float kickBackForceMultiplier;
	bool autoAdjust;
	bool networkLODRangeOverride;
	float networkLODRangeOverrideDistance;
	OffhandClass offhandClass;
	weapStance_t stance;
	WeaponVFXPackage* vfxPackage;
	WeaponSFXPackage* sfxPackage;
	bool disableBreathOffhand;
	ReticleType reticleType;
	HitmarkerType hitmarkerType;
	Material* reticleCenter;
	Material* reticleSide;
	Material* reticleOnePiece;
	int iReticleCenterSize;
	int iReticleSideSize;
	int iReticleMinOfs;
	bool reticleCenterPulse;
	int iReticleShakeDuration;
	int iReticleSettleDuration;
	int iReticleNumBulletsToRapidFire;
	activeReticleType_t activeReticleType;
	bool useTurretViewmodelAnims;
	bool useTurret3pIK;
	turret3pAnimType_t turret3pAnimType;
	float turretFireAnimMinTime;
	Vector3 vStandOfs;
	Vector3 vStandOfsRot;
	Vector3 vStandOfsRotPivot;
	Vector3 vStandMove;
	Vector3 vStandRot;
	Vector3 strafeMove;
	Vector3 strafeRot;
	AdsOffsetInterpolationType hipOffsetLerpType;
	Vector3 vDuckedOfs;
	Vector3 vDuckedOfsRot;
	Vector3 vDuckedOfsRotPivot;
	Vector3 vDuckedMove;
	Vector3 vDuckedRot;
	Vector3 vProneOfs;
	Vector3 vProneMove;
	Vector3 vProneRot;
	float adsForwardOffset;
	float adsRoll;
	float fPosMoveRate;
	float fPosProneMoveRate;
	float fStandMoveMinSpeed;
	float fDuckedMoveMinSpeed;
	float fProneMoveMinSpeed;
	float fPosRotRate;
	float fPosProneRotRate;
	float fDuckedOfsRotRate;
	float fStandRotMinSpeed;
	float fDuckedRotMinSpeed;
	float fProneRotMinSpeed;
	float fReticleShakeMagnitude;
	float fReticleRapidFireMultiplier;
	XModel* worldClipModel;
	XModel* rocketModel;
	GfxImage* hudIcon;
	GfxImage* pickupIcon;
	GfxImage* dangerIconImg;
	GfxImage* throwBackIconImg;
	Material* dangerIconMat;
	Material* throwBackIconMat;
	bool hideWarningIcons;
	float warningIconsDelay;
	ammoCounterClipType_t ammoCounterClip;
	int iStartAmmo;
	int iPerkStartAmmo;
	int iPerkMaxAmmo;
	const char* szAmmoName;
	int iAmmoIndex;
	int iMaxAmmo;
	int shotCount;
	const char* szSharedAmmoCapName;
	int iSharedAmmoCapIndex;
	int iSharedAmmoCap;
	int iAmmoUsedPerShot;
	bool requireAmmoUsedPerShot;
	bool disableNoAmmoWarning;
	float lowAmmoWarningThreshold;
	int lowAmmoWarningCount;
	int iDamageType;
	int iMeleeDamage;
	int iMeleeCountToFinisher;
	bool hasMeleeFinisher;
	float autoAimRange;
	float aimAssistRange;
	float aimAssistRangeAds;
	float aimAssistPitchSlowdown;
	float aimAssistPitchSlowdownAds;
	float aimAssistYawSlowdown;
	float aimAssistYawSlowdownAds;
	float aimAssistLockonStrength;
	float aimPadding;
	float enemyCrosshairRange;
	float moveSpeedScale;
	float adsMoveSpeedScale;
	float sprintDurationScale;
	float sprintRestoreDelay;
	ADSOverlay overlay;
	WeapOverlayInteface_t overlayInterface;
	float fAdsBobFactor;
	float fAdsViewBobMult;
	float fAdsGunBobPitchScale;
	float fAdsGunBobYawScale;
	float fAdsGunBobTiltPitchScale;
	float fAdsGunBobTiltYawScale;
	float fAdsGunBobTiltRollScale;
	float fAdsGunBobTiltBulletDirScale;
	float fAdsGunBobTiltOffset;
	float fAdsGunBobCrouchFactor;
	float adsCrouchViewKickFactor;
	float adsCrouchGunKickFactor;
	float adsProneViewKickFactor;
	float adsProneGunKickFactor;
	float fHipSpreadStandMin;
	float fHipSpreadDuckedMin;
	float fHipSpreadProneMin;
	float hipSpreadSprintMin;
	float hipSpreadInAirMin;
	float hipSpreadStandMax;
	float hipSpreadDuckedMax;
	float hipSpreadProneMax;
	float hipSpreadSprintMax;
	float hipSpreadInAirMax;
	float fHipSpreadDecayRate;
	float fHipSpreadFireAdd;
	float fHipSpreadTurnAdd;
	float fHipSpreadMoveAdd;
	float fHipSpreadDuckedDecay; // start no spread
	float fHipSpreadProneDecay;
	float hipSpreadSprintDecay;
	float hipSpreadInAirDecay;
	float fHipReticleSidePos;
	float fAdsIdleAmount;
	float fHipIdleAmount;
	float adsIdleSpeed;
	float hipIdleSpeed;
	float fIdleCrouchFactor;
	float fIdleProneFactor;
	float fGunMaxPitch;
	float fGunMaxYaw; // start no spread during moving and shooting
	float fViewMaxPitch;
	float fViewMaxYaw;
	float adsIdleLerpStartTime;
	float adsIdleLerpTime;
	bool useUninterruptedAdsIdleMotion;
	bool disableInputDrivenViewReturnDampening;
	float slideSpreadMin;
	float slideSpreadMax;
	float slideSpreadDecayRate;
	float slideSpreadFireAdd;
	float slideSpreadTurnAdd; // end no spread
	SwaySettings swaySettings;
	float adsFireRateScale;
	float adsDamageRangeScale;
	float adsFireAnimFrac;
	float fireTimerLerpToAdsScale;
	bool alwaysFireAtMaxRangeInAds;
	bool adsAlignEnabled;
	bool disableTagAlignX;
	Vector3 adsAlignOffset;
	AdsOffsetInterpolationType adsAlignOffsetLerpType;
	AdsOffsetInterpolationType adsAlignLerpType;
	float adsMovementAnimLerpStart;
	float adsMovementAnimLerpEnd;
	float dualWieldViewModelOffset;
	float fScopeDriftDelay;
	float fScopeDriftLerpInTime;
	float fScopeDriftSteadyTime;
	float fScopeDriftLerpOutTime;
	float fScopeDriftSteadyFactor;
	float fScopeDriftUnsteadyFactor;
	weaponIconRatioType_t killIconRatio;
	int iReloadAmmoAdd;
	int iReloadStartAdd;
	bool reloadTwoRound;
	int ammoDropStockMin;
	int ammoDropClipPercentMin;
	int ammoDropClipPercentMax;
	float cameraShakeScale;
	int cameraShakeDuration;
	float cameraShakeRadius;
	int iExplosionRadius;
	int iExplosionRadiusMin;
	int iExplosionForceRadius;
	int iExplosionInnerDamage;
	int iExplosionOuterDamage; // START NO RECOIL
	float explosionForceScalar;
	float damageConeAngle;
	float bulletExplDmgMultMin;
	float bulletExplDmgMult;
	float bulletExplRadiusMult;
	int iProjectileSpeed;
	int iProjectileSpeedUp;
	int iProjectileSpeedForward;
	int iProjectileActivateDist;
	int iProjectileDetonationRadius;
	float projLifetime;
	float projLifetimeStdDeviation;
	float timeToAccelerate;
	float projectileCurvature;
	XModel* projectileModel;
	weapProjExposion_t projExplosion;
	FxCombinedDef projExplosionEffect;
	FxCombinedDef projDudEffect;
	FxCombinedDef projTimeoutEffect;
	bool disableFxOnTimeout;
	WeapStickinessType stickiness;
	float ricochetChance;
	int iExplosionSteppedRadiusInner;
	int iExplosionSteppedRadiusMid;
	int iExplosionSteppedRadiusOuter;
	int iExplosionSteppedDamageInner;
	int iExplosionSteppedDamageMid;
	int iExplosionSteppedDamageOuter;
	bool riotShieldEnableDamage;
	int riotShieldHealth;
	float riotShieldDamageMult;
	float* parallelBounce;
	float* perpendicularBounce;
	FxCombinedDef vmProjBodyEffect;
	FxCombinedDef projBodyEffect;
	FxCombinedDef projTrailEffect;
	FxCombinedDef projBeaconEffect;
	Vector3 vProjectileColor;
	guidedMissileType_t guidedMissileType;
	float maxSteeringAccel;
	int projIgnitionDelay;
	FxCombinedDef projIgnitionEffect;
	float fAdsAimPitch;
	float adsInCrosshairAlphaStart;
	float adsInCrosshairAlphaEnd;
	float adsOutCrosshairAlphaStart;
	float adsOutCrosshairAlphaEnd;
	bool adsShouldShowCrosshair;
	float fAdsGunKickPitchMin;
	float fAdsGunKickPitchMax;
	float fAdsGunKickYawMin;
	float fAdsGunKickYawMax;
	float fAdsGunKickMagMin;
	float fAdsGunKickAccel;
	float fAdsGunKickSpeedMax;
	float fAdsGunKickSpeedDecay;
	float fAdsGunKickStaticDecay;
	float fAdsViewKickPitchMin;
	float fAdsViewKickPitchMax;
	float fAdsViewKickYawMin;
	float fAdsViewKickYawMax;
	float fAdsViewKickMagMin;
	float fAdsViewScatterMin;
	float fAdsViewScatterMax;
	float fAdsSpread;
	float fAdsSpreadNVG;
	float adsSpreadStartFrac;
	float adsSpreadEndFrac;
	int iVisibilityAxis;
	float fVisibilityUpOffset;
	float fHipGunKickPitchMin;
	float fHipGunKickPitchMax;
	float fHipGunKickYawMin;
	float fHipGunKickYawMax;
	float fHipGunKickMagMin;
	float fHipGunKickAccel;
	float fHipGunKickSpeedMax;
	float fHipGunKickSpeedDecay;
	float fHipGunKickStaticDecay;
	float fHipViewKickPitchMin;
	float fHipViewKickPitchMax;
	float fHipViewKickYawMin;
	float fHipViewKickYawMax;
	float fHipViewKickMagMin;
	float fHipViewScatterMin;
	float fHipViewScatterMax;
	float multipleReloadClipPercentage;
	float hipStartingGunKickPercent;
	float hipStartingViewKickPercent;
	int adsStartingKickBullets;
	float adsStartingGunKickPercent;
	float adsStartingViewKickPercent;
	float hipEndingGunKickPercent;
	float hipEndingViewKickPercent;
	int adsEndingKickBullets;
	float adsEndingGunKickPercent;
	float adsEndingViewKickPercent;
	float kickAlignedInputScalar;
	float kickOpposedInputScalar;
	float viewKickMaintainFraction;
	float adsGunTiltPitchFactor;
	float adsGunTiltYawFactor;
	float adsGunTiltRollFactor;
	float adsGunTiltOffset;
	float hipGunTiltPitchFactor;
	float hipGunTiltYawFactor;
	float hipGunTiltRollFactor;
	float hipGunTiltOffset;
	bool useNewViewKick;
	bool useNewGunKick;
	bool useAngularViewKick;
	bool useAngularGunKick;
	float hipAngularViewKickDir[6];
	float hipAngularViewKickDev[6];
	float hipAngularViewKickStrengthMin[6];
	float hipAngularViewKickStrengthMax[6];
	float hipAngularViewKickPitchScale[6];
	float adsAngularViewKickDir[6];
	float adsAngularViewKickDev[6];
	float adsAngularViewKickStrengthMin[6];
	float adsAngularViewKickStrengthMax[6];
	float adsAngularViewKickPitchScale[6];
	int adsAngularViewKickBullet[6];        // 0x99C
	bool adsAngularViewKickUseSet[6];       // 0x9B4
	float hipAngularGunKickDir[6];          // 0x9BC
	float hipAngularGunKickDev[6];          // 0x9D4
	float hipAngularGunKickStrengthMin[6];
	float hipAngularGunKickStrengthMax[6];
	float hipAngularGunKickPitchScale[6];
	float adsAngularGunKickDir[6];
	float adsAngularGunKickDev[6];
	float adsAngularGunKickStrengthMin[6];
	float adsAngularGunKickStrengthMax[6];
	float adsAngularGunKickPitchScale[6];
	int adsAngularGunKickBullet[6];
	bool adsAngularGunKickUseSet[6];
	float hipViewKickReturnAccelScale;
	float adsViewKickReturnAccelScale;
	float hipViewKickReturnSpeedCurveScale;
	float adsViewKickReturnSpeedCurveScale;
	float hipGunKickReturnAccelScale;
	float adsGunKickReturnAccelScale;
	float hipGunKickReturnSpeedCurveScale;
	float adsGunKickReturnSpeedCurveScale;
	float hipSpreadStandMoveMax;
	float hipSpreadDuckedMoveMax;
	float hipSpreadProneMoveMax;
	float hipSpreadSprintMoveMax;
	float hipSpreadInAirMoveMax;
	float slideSpreadMoveMax;
	WeaponOffsetCurveDescription weaponOffsetCurveHoldFireSlow;
	WeaponOffsetCurveDescription weaponOffsetCurveHoldFireFast; // END NO RECOIL
	WeaponOffsetCurveDescription weaponOffsetCurveAds;
	WeaponOffsetCurveDescription weaponOffsetCurveAlwaysOn;
	WeaponOffsetCurveDescription weaponOffsetCurveKick;
	WeaponOffsetCurveDescription weaponOffsetCurveSnapDecay;
	int numWeaponOffsetPatterns;
	WeaponOffsetPatternDescription* weaponOffsetPatterns;
	int numWeaponOffsetPatternsKickOrSnapDecay;
	WeaponOffsetPatternDescription** weaponOffsetPatternsKickOrSnapDecay;
	float fightDist;
	float maxDist;
	const char* accuracyGraphName[2];
	Vector2* originalAccuracyGraphKnots[2];
	unsigned __int16 originalAccuracyGraphKnotCount[2];
	int iPositionReloadTransTime;
	float leftArc;
	float rightArc;
	float topArc;
	float bottomArc;
	float visualPitchLimitTop;
	float visualPitchLimitBottom;
	bool softLeftRightArc;
	float accuracy;
	float aiSpread;
	float playerSpread;
	float minTurnSpeed[2];
	float maxTurnSpeed[2];
	float pitchConvergenceTime;
	float yawConvergenceTime;
	float suppressTime;
	float suppressTimeTargetKilled;
	float aiReturnToDefaultSpeed[2];
	float maxRange;
	float fAnimHorRotateInc;
	float fPlayerPositionDist;
	const char* szUseHintString;
	const char* dropHintString;
	unsigned int iUseHintStringIndex;
	unsigned int dropHintStringIndex;
	float horizViewJitter;
	float vertViewJitter;
	bool enableViewBounceFire;
	float viewBounceFireDecay;
	float viewBounceFireFrequency;
	float viewBounceFirePitchScale;
	float viewBounceFireRollScale;
	float scanSpeed;
	float scanAccel;
	int scanPauseTime;
	const char* szScript;
	float adsSpeedMs[2];
	float adsAccelSec[2];
	bool deferDamageToParentVehicle;
	bool useSteppedExplosionDamage;
	float destabilizationRateTime;
	float destabilizationCurvatureMax;
	int destabilizeDistance;
	float robotechMaxPitch;
	float robotechMaxYaw;
	float robotechFrequency;
	float robotechVariancePitch;
	float robotechVarianceYaw;
	float robotechVarianceFrequency;
	float* locationDamageMultipliers;
	unsigned __int8* hitLocPriorityMap;
	float unittypeMultipliers[7];
	RumbleInfo* fireRumble;
	RumbleInfo* meleeImpactRumble;
	float heatAccumulationPerShot;
	float heatDissipationPerSecond;
	float heatSmokeStartThreshold;
	float heatSmokeStopThreshold;
	bool heatIsOpenBolt;
	tracerStyle_t tracerStyle;
	TracerDef* tracerType;
	TracerDef* overchargeTracerType;
	LaserDef* laserTypeViewModel;
	LaserDef* laserTypeViewModelAlt;
	LaserDef* laserTypeFriendly;
	LaserDef* laserTypeEnemy;
	bool turretADSEnabled;
	float turretADSTime;
	float turretFov;
	float turretFovADS;
	float turretScopeZoomRate;
	float turretScopeZoomMin;
	float turretScopeZoomMax;
	float turretOverheatPenalty;
	SndAliasLookup turretOverheatSound;
	FxCombinedDef turretOverheatEffect;
	RumbleInfo* turretBarrelSpinRumble;
	float turretBarrelSpinSpeed;
	float turretBarrelSpinUpTime;
	float turretBarrelSpinDownTime;
	SndAliasLookup turretBarrelSpinMaxSnd;
	SndAliasLookup turretBarrelSpinUpSnd[4];
	SndAliasLookup turretBarrelSpinDownSnd[4];
	SndAliasLookup missileConeSoundAlias;
	SndAliasLookup missileConeSoundAliasAtBase;
	float missileConeSoundRadiusAtTop;
	float missileConeSoundRadiusAtBase;
	float missileConeSoundHeight;
	float missileConeSoundOriginOffset;
	float missileConeSoundVolumescaleAtCore;
	float missileConeSoundVolumescaleAtEdge;
	float missileConeSoundVolumescaleCoreSize;
	float missileConeSoundPitchAtTop;
	float missileConeSoundPitchAtBottom;
	float missileConeSoundPitchTopSize;
	float missileConeSoundPitchBottomSize;
	float missileConeSoundCrossfadeTopSize;
	float missileConeSoundCrossfadeBottomSize;
	bool meleeOverrideValues;
	float aim_automelee_lerp;
	float aim_automelee_region_height;
	float aim_automelee_region_width;
	float aim_automelee_maxPitchMovement;
	float aim_automelee_maxYawMovement;
	float player_meleeHeight;
	float player_meleeWidth;
	float playerMeleeRangeStanding;
	float playerMeleeRangeCrouched;
	float playerMeleeRangeProne;
	float playerMeleeRangeChargeStanding;
	float playerMeleeRangeChargeCrouched;
	float playerMeleeChargeHeightTolerance;
	bool shieldAllowFiring;
	offhandShieldMaxSpeed_t shieldMaxSpeed;
	bool shieldAlwaysDisplay;
	Gesture* shieldDeployGesture;
	Gesture* shieldFireWeapGesture;
	Gesture* shieldDeployWhileFiring;
	Gesture* shieldRetractWhileFiring;
	Gesture* shieldBashGesture;
	FxCombinedDef shieldMeleeFx;
	float shieldMeleeFxDelay;
	float HitEarthquakeScale;
	float HitEarthquakeDuration;
	float HitEarthquakeRadius;
	RumbleInfo* shieldHitRumble;
	float MissEarthquakeScale;
	float MissEarthquakeDuration;
	float MissEarthquakeRadius;
	RumbleInfo* shieldMissRumble;
	offhandShieldButton_t shieldDeployButton;
	bool shieldUsesEnergy;
	float shieldMaxEnergy;
	float shieldConsumptionRate;
	float shieldMeleeEnergyCost;
	float shieldMeleeHitEnergyCost;
	float reactiveMotionRadiusScale;
	float reactiveMotionFrequencyScale;
	float reactiveMotionAmplitudeScale;
	float reactiveMotionFalloff;
	float reactiveMotionLifetime;
	unsigned __int8 transientBaseViewFlags;
	unsigned __int8 transientBaseWorldFlags;
	bool hasAnyTransientModels;
	bool blendFireAnimations;
	bool sharedAmmo;
	bool lockonSupported;
	bool requireLockonToFire;
	bool isAirburstWeapon;
	bool bigExplosion;
	bool noAdsWhenMagEmpty;
	bool avoidDropCleanup;
	bool allowGrenadeSwitching;
	bool inheritsPerks;
	bool forceUse;
	bool ladderWeapon;
	bool executionVictimHiddenWeapon;
	bool crosshairColorChange;
	bool bRifleBullet;
	bool bEnergyBullet;
	bool bIncendiaryBullet;
	bool armorPiercing;
	bool impaling;
	bool bBoltAction;
	bool aimDownSight;
	bool canHoldBreath;
	bool meleeOnly;
	bool supportsAlternateMelee;
	bool bRechamberWhileAds;
	bool reloadWhileAds;
	bool bBulletExplosiveDamage;
	bool bCookOffHold;
	bool overCookIsNotLethal;
	bool reticleSpin45;
	bool bClipOnly;
	bool bDoesNotConsumeAmmo;
	bool bRemoveWeaponOnEmpty;
	bool noAmmoPickup;
	bool adsFireOnly;
	bool cancelAutoHolsterWhenEmpty;
	bool disableSwitchToWhenEmpty;
	bool suppressAmmoPrimaryDisplay;
	bool suppressAmmoReserveDisplay;
	LaserSettings laserSettings;
	bool markableViewmodel;
	bool isPredictedProjectile;
	int clientTrajectoryBlendOutTime;
	int serverTrajectoryBlendInTime;
	DualWieldType dualWieldType;
	bool flipKillIcon;
	bool bNoPartialReload;
	bool reloadDisabled;
	bool blocksProne;
	bool silenced;
	bool doNotSuppressAI;
	bool isRollingGrenade;
	bool dropGrenadeHeldOnDeath;
	bool projExplosionEffectForceNormalUp;
	bool projExplosionEffectInheritParentDirection;
	bool bProjImpactExplode;
	bool spawnProjAtMuzzle;
	bool correctBulletTrajectory;
	float maxCorrectionAngle;
	bool disableProjectileCrumpleCheck;
	bool bProjTrajectoryEvents;
	bool bProjWhizByEnabled;
	bool stickToPlayers;
	bool stickToVehicles;
	bool stickToTurrets;
	bool stickToNonStick;
	bool projEnableMissileStickiness;
	bool enableMissileRicochet;
	bool thrownSideways;
	bool disableFiring;
	bool firesOnWeaponSwitch;
	bool disableHolding;
	bool timedDetonation;
	float missileRicochetMinAngleOfIncidence;
	float missileCrumpleMinSpeed;
	WeapDetonateType detonateType;
	XModel* detonatorWorldModel;
	int explosiveDamageDelay;
	int fuseTime;
	int aiFuseTime;
	int maxHoldTime;
	GrenadeRotationParams rotationParams;
	bool holdButtonToThrow;
	bool autoHold;
	bool infiniteHold;
	bool freezeMovementWhenFiring;
	bool offhandAllowsSprint;
	bool thermalScope;
	bool thermalToggle;
	bool outlineEnemies;
	bool outlineDepthTest;
	bool outlineFill;
	float enemyOutlineR;
	float enemyOutlineG;
	float enemyOutlineB;
	float enemyOutlineA;
	float allyOutlineR;
	float allyOutlineG;
	float allyOutlineB;
	float allyOutlineA;
	bool depthScan;
	float depthScanThickness;
	float depthScanR;
	float depthScanG;
	float depthScanB;
	float depthScanA;
	float depthScanOutlineThickness;
	float depthScanOutlineR;
	float depthScanOutlineG;
	float depthScanOutlineB;
	float depthScanOutlineA;
	bool depthScanOverlay;
	float depthScanOverlayStrength;
	float depthScanOverlayXTiles;
	float depthScanOverlayYTiles;
	float depthScanOverlayXScroll;
	float depthScanOverlayYScroll;
	float blurSceneAdsInFraction;
	float blurSceneAdsOutFraction;
	bool altModeSameWeapon;
	bool playAltGesturesForOffhandWeapons;
	bool turretBarrelSpinEnabled;
	bool missileConeSoundEnabled;
	bool missileConeSoundPitchshiftEnabled;
	bool missileConeSoundCrossfadeEnabled;
	bool offhandHoldIsCancelable;
	bool doNotAllowAttachmentsToOverrideSpread;
	bool useScopeDrift;
	bool alwaysShatterGlassOnImpact;
	bool jumpSpread;
	bool noFullViewmodelAnimations;
	float killcamOffset;
	bool useDualFOV;
	bool showViewModelInDualFOV;
	bool syncedFOVInDualFOV;
	bool disableDrop;
	bool preferredDrop;
	Gesture* gestureAnimation;
	float gestureFireStateTime;
	Gesture* gesturePullback;
	Gesture* gesturePullbackAlt;
	float minPullbackTime;
	float minPullbackToThrowBlendTime;
	float maxPullbackToThrowBlendTime;
	Gesture* gestureThrow;
	Gesture* gestureThrowAlt;
	float gestureFireTime;
	Gesture* gestureDetonate;
	Gesture* gestureDetonateAlt;
	float gestureDetonationTime;
	bool gesturesDisablePrimary;
	FxCombinedDef cameraFireEffect;
	float cameraFireEffectDurationSec;
	float changedFireTime;
	float changedFireTimeAkimbo;
	int changedFireTimeNumBullets;
	__int32 chargeType;
	float chargeGain;
	float chargeCostPerShot;
	float chargeLossWhenIdle;
	float chargeEmptyCooldown;
	float chargeFireAtMaxDamageMultiplier;
	int chargeMeterEffectBoneCount;
	FxCombinedDef chargeMeterEffect;
	SndAliasLookup chargeUpSound;
	SndAliasLookup chargeDownSound;
	SndAliasLookup chargeUpSoundPlayer;
	SndAliasLookup chargeDownSoundPlayer;
	SndAliasLookup chargeDownToUpSound;
	SndAliasLookup chargeDownToUpSoundPlayer;
	SndAliasLookup chargeUpToDownSound;
	SndAliasLookup chargeUpToDownSoundPlayer;
	SndAliasLookup chargeMaxSound;
	SndAliasLookup chargeMaxSoundPlayer;
	bool chargeHudReveal;
	RumbleInfo* chargeRumble;
	scr_string_t stowTag;
	XModel* stowOffsetModel;
	scr_string_t stowOffsetAttachTag;
	WeaponSlot slot;
	float maxTargetAngle;
	bool spaceshipSecondaryWeapon;
	float impulseFieldRadius;
	float impulseFieldInitialSpeed;
	float impulseFieldMaxSpeed;
	float impulseFieldAcceleration;
	float impulseFieldInAirImpulseMultiplier;
	float impulseFieldInAirImpulseMultiplierInterpTime;
	float impulseFieldSlideMultiplier;
	float impulseFieldSlideMultiplierInterpTime;
	bool impulseFieldIsPush;
	bool impulseFieldAffectsFriendlies;
	bool impulseFieldAffectsSelf;
	bool impulseFieldAffectsProne;
	bool regenerationEnabled;
	int regenerationTimeMs;
	int regenerationAddTimeMs;
	int regenerationAmount;
	bool regenerationConsumeStock;
	bool regenerationDisableWhileFiring;
	DeployType deployType;
	bool deployRequireOnWalkableSurface;
	bool deployRequireOnNavmesh;
	bool deployRequireSkyAbove;
	bool deployRequireNoOverhang;
	bool deployAlwaysUpright;
	bool deployEdgeSnap;
	float deployCylinderRadius;
	float deployCylinderHeight;
	float deployMaxDistance;
	float deployMaxHeightAboveEye;
	float deployEffectHeightOffset;
	float deployMaxSlope;
	FxCombinedDef deployEffect;
	__int32 deployValidGroupId;
	__int32 deployIndoorGroupId;
	__int32 deployInvalidGroupId;
	__int32 deployOutOfRangeGroupId;
	unsigned int numAnimOverrides;
	AnimOverride* animOverrides;
	CarryAnimOverride carryAnimOverrides[5];
	unsigned int numSfxOverrides;
	SFXOverride* sfxOverrides;
	unsigned int numVfxOverrides;
	VFXOverride* vfxOverrides;
	float reactiveEmitterDelay;
	float grenadeDangerIconDistance;
	float bulletDirGunAngleModifierIdleHip;
	float bulletDirGunAngleModifierIdleAds;
	float bulletDirGunAngleModifierGunKickHip;
	float bulletDirGunAngleModifierGunKickAds;
	float bulletDirGunAngleModifierGunTiltHip;
	float bulletDirGunAngleModifierGunTiltAds;
	float viewClampPitchCatchUpTimeSec;
	float viewClampYawCatchUpTimeSec;
	bool mountTopEnable;
	bool mountTopYawClamp;
	float mountTopYawMax;
	float mountTopGunKickScale;
	float mountTopGunCenterScale;
	float mountTopViewKickScale;
	float mountTopViewCenterScale;
	float mountTopGunIdleMotionScale;
	float mountTopViewIdleMotionScale;
	int mountTopEnterDurationMs;
	int mountTopExitDurationMs;
	float mountTopEdgeToEyeDistanceForward;
	float mountTopEdgeToEyeDistanceAbove;
	bool mountSideEnable;
	bool mountSideTransitionEnable;
	float mountSideRoll;
	float mountSideRollStartFrac;
	float mountSideRollEndFrac;
	float mountSideGunKickScale;
	float mountSideGunCenterScale;
	float mountSideViewKickScale;
	float mountSideViewCenterScale;
	float mountSideGunIdleMotionScale;
	float mountSideViewIdleMotionScale;
	int mountSideEnterDurationMs;
	int mountSideExitDurationMs;
	float mountSideEdgeToEyeDistanceForward;
	float mountSideEdgeToEyeDistanceAbove;
	float mountViewmodelOffset;
	float mountFOVScale;
	RumbleInfo* mountRumble;
	WeaponOffsetPatternScaleInfo mountWeaponOffsetPatternScaleInfo;
	float adsFireMotionBlur;
	int adsFireMotionBlurDurationMs;
	float adsFireMotionBlurDecayExponent;
	float hipFireMotionBlur;
	int hipFireMotionBlurDurationMs;
	float hipFireMotionBlurDecayExponent;
	float adsCameraShakeRotationScale;
	float adsCameraShakeTranslationScale;
	AdvancedIdleSettings advancedIdleSettings;
	WeaponOffsetPatternScaleInfo crouchedWeaponOffsetPatternScaleInfo;
	WeaponOffsetPatternScaleInfo proneWeaponOffsetPatternScaleInfo;
	BallisticInfo ballisticInfo;
	HyperBurstInfo hyperBurstInfo;
	WeaponEntityNotify* notifyTypes[2];
	float dlcFloat[6];
	bool dlcBool[3];
	bool enableWeaponInspect;
	bool stowedOcclusionTestEnabled;
	bool ignoreMinTracerSpawnDistance;
	bool tracerOverrideEnabled;
	bool boltActionReloadIncludesRechamber;
};