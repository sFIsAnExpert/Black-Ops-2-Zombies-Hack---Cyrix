#pragma once
#include <Windows.h>
#include "Math.h"

struct Offsets {
	uintptr_t dwEntityList = 0x21C5828;
	uintptr_t dwPlayerList = 0x21C13C0;
	uintptr_t dwToNextLocal = 0x31C;
	uintptr_t dwToNextGEntity = 0x380;
	uintptr_t dwViewMatrix = 0x33F0EE0;
	uintptr_t cg_printToScreen = 0x5F4F10;
	uintptr_t dwLocalPlayer = 0x0103AC48;
	uintptr_t dwResolution = 0x03A0D6B0;
	uintptr_t dwLocalPlayerPos = 0x23427C8;
	uintptr_t cg_weapon1_ammo = 0x2342BCC;
	uintptr_t CG_IsEntityFriendlyNotEnemy = 0x66E870;
	uintptr_t AimTarget_IsTargetVisible = 0x51D750;
	uintptr_t cg_weapon2_ammo = 0x2342BD4;
	uintptr_t dwPlayerInfo_t = 0x23427A0;
	uintptr_t dwHealth = 0x21C1568;

	uintptr_t R_AddDObjToScene = 0x724CC0;
	uintptr_t CL_GetCurrentCmdNumber = 0x490A50;
	uintptr_t CL_WritePacket = 0x444C60;
};

struct Chams {
public:
	float R, G, B, A;
};


enum EntityFlags : unsigned __int32 {
	STANDING = 2,
	CROUCH = 6,
	PRONE = 10,
	BARRIER = 237,
	ZM = 67110914,
};

enum TeamType : __int32 {
	FRIEND = 1,
};

struct TeamInfo_t {
	char _0x0000[4];    // 0x0000
	TeamType Team;    // 0x0004 // TeamType
	char _0x0008[56];    // 0x0008

}; // Size 0x0040

enum EntityType : unsigned short {
	GENERAL,
	PLAYER,
	PLAYER_CORPSE,
	ITEM,
	MISSILE,
	INVISIBLE,
	SCRIPTMOVIER,
	SOUND_BLEND,
	FX,
	LOOP_FX,
	PRIMARY_LIGHT,
	TURRET,
	HELICOPTER,
	PLANE,
	VEHICLE,
	VEHICLE_CORPSE,
	ZOMBIE,
	ZOMBIE_SPAWNER,
	ZOMBIE_CORPSE,
	STREAMER_HINT,
	ZBARRIER,
};

typedef char pad;

struct PlayerInfo_t {
	__int32 ServerTime;		// 0x0000 -> 23427A0
	char pad_0x0004[0x24];		// 0x0004
	Vector3 Position;			// 0x0028 -> 23427C8 // Position (x,y,z)
	Vector3 Velocity;			// 0x0034 -> 23427D4 // Velocity (x,y,z)
	pad _0x0040[0x4C];		// 0x0040
	__int32 Gravity;		// 0x008C -> 234282C
	pad _0x0090[0x4];		// 0x0090
	__int32 Speed;			// 0x0094 -> 2342834
	pad _0x0098[0x2C];		// 0x0098
	float LastJump;			// 0x00C4 -> 2342864 // Height where standing on last jump
	pad _0x00C8[0x118];		// 0x00C8
	float ADS;				// 0x01E4 -> 2342980 // % (0.00 to 1.00) of how much ADS
	pad _0x01E8[0x14];		// 0x01E8
	Vector2 Angle;				// 0x01FC -> 2342998 // x(-85up 85down) y(-180 180)
	pad _0x0200[0x04];		// 0x0200
	__int32 HeightInt;		// 0x0204 -> 23429A4
	float HeightFloat;		// 0x0208 
	pad _0x020C[0x2C];		// 0x020C
	__int32 Health;			// 0x0238 -> 23429D8 // Read only
	pad _0x023C[0x4];		// 0x023C
	__int32 MaxHealth;		// 0x0240 // xd doesn't work
	pad _0x0244[0x04];		// 0x0244
	__int32 Weapon2ID;		// 0x0248 -> 23429E8
	pad _0x024C[0x18];		// 0x024C -> 23429EC
	__int32 Weapon1ID;		// 0x0264 -> 2342A04
	pad _0x0268[0x18];		// 0x0268 -> 2342A08
	__int32 LethalID;		// 0x0280 -> 2342A20
	char _0x0284[0x18];		// 0x0284 -> 2342A24
	__int32 TacticalID;	// 0x02B8 -> 2342A3C
	char _0x02BC[0x14C];	// 0x02BC -> 2342A40
	__int32 Weapon1Stock;	// 0x03F0 -> 2342B8C
	char _0x03F4[0x4];		// 0x03F4
	__int32 Weapon2Stock;	// 0x03F8 
	char _0x03FC[0x30];		// 0x03FC
	__int32 Weapon1Clip;	// 0x042C -> 2342BC8
	pad fuk[0x4];			// 0x042C
	__int32 LethalAmmo;		// 0x0430 -> 2342BD0
	__int32 Weapon2Clip;	// 0x0434 
	__int32 TacticalAmmo;	// 0x0438 
	char _0x043C[0x110];	// 0x043C
	__int32 PerkFlags;		// 0x054C // 0x10 = Reduced Spread, 0x80000 = Faster Knife
	char _0x0550[0x4F5C];	// 0x0550
	char NameReadOnly[32];	// 0x54AC -> 2347C4C // Readonly 
	char _0x54BC[0x20];		// 0x54BC
	pad fuckinghell[0x48];
	char Name[32];			// 0x5534 -> 2347CD4 // Writable (Null terminate plz)
	char _0x5544[0x74];		// 0x5544
	__int32 Score;			// 0x55C8 -> 2347D68
	__int32 Kills1;			// 0x55CC -> 2347D6C
	pad _0x55D0[0x10];		// 0x55D0 -> 2347D70
	__int32 Kills;			// 0x55E0 -> 2347D80
	__int32 Downs;			// 0x55E4 -> 2347D84
	__int32 Revives;		// 0x55E8 -> 2347D88
	__int32 Headshots;		// 0x55EC -> 2347D8C
	pad _0x55F0[0x08];		// 0x55F0 -> 2347D90
	__int32 Headshots1;		// 0x55F8 -> 2347D98
	pad _0x55FC[0x28];		// 0x55FC -> 2347D9C
	__int32 Kills2;			// 0x5620 -> 2347DC0
	pad _0x5624[0x38];		// 0x5624 -> 2347DC4
	__int32 Headshots2;		// 0x565C -> 2347DFC
}; // Size 0x045C ???

struct centity_t {
	__int32 ClientNum;			// 0x0000
	EntityFlags Flags;			// 0x0004 // EntityFlags
	char _0x0008[16];			// 0x0008
	Vector3 Position;				// 0x0018 // Position
	char _0x0024[24];			// 0x0024
	Vector2 Angles;				// 0x003C // Angles x(-85up 85down) y(-180 180)
	char _0x0044[28];			// 0x0044
	__int32 HeldWeapon;			// 0x0060 // Weapon they're currently using
	char _0x0064[116];			// 0x0064
	EntityType Type;			// 0x00D8
	char _0x00DA[66];			// 0x00DA
	Vector3 ViewOrigin;				// 0x011C // Other position ??
	char _0x0128[44];			// 0x0128
	PlayerInfo_t* PlayerInfo;	// 0x0154 
	char _0x0158[4];			// 0x0158
	TeamInfo_t* TeamInfo;		// 0x015C 
	char _0x0160[12];			// 0x0160
	__int32 ModelIndex;			// 0x016C // Model ID (44 == Bus)
	char _0x0170[56];			// 0x0170
	__int32 Health;				// 0x01A8 // Health
	char _0x01AC[29320];		// 0x01AC
};

struct gEntity
{
public:
	char pad_0000[44]; //0x0000
	Vector3 Position; //0x002C
	char pad_0038[12]; //0x0038
	Vector3 PositionOld; //0x0044
	Vector3 ViewOrigin; //0x0050
	char pad_005C[260]; //0x005C
	int32_t Valid; //0x0160
	char pad_0164[120]; //0x0164
	int32_t ClientNum; //0x01DC
	char pad_01E0[20]; //0x01E0
	Vector3 PositionNew; //0x01F4
	char pad_0200[608]; //0x0200
}; //Size: 0x0460

struct LocalPlayer
{
public:
	char pad_0000[8]; //0x0000
	Vector3 Position; //0x0008
	Vector2 LookAngle; //0x0014
	char pad_001C[4]; //0x001C
	Vector3 Velocity; //0x0020
	char pad_002C[12]; //0x002C
	int32_t Stance; //0x0038
	char pad_003C[28]; //0x003C
	float Aiming; //0x0058
	char pad_005C[60]; //0x005C
	Vector3 ViewOrigin; //0x0098
}; 
struct usercmd_s
{
public:
	int serverTime;
	int iButtons[2];
	int viewAngles[3];
private:
	char _0x18[0xC];
public:
	char forwardmove;
	char sidemove;
private:
	char _0x26[0x16];
};

struct input_s
{
	usercmd_s usercmds[128]; // 0x0
	int currentCmdNum; // 0x1E00

	usercmd_s* GetUserCmd(int cmdNum)
	{
		return &usercmds[(cmdNum & 0x7F)];
	}
};

enum State {
	DEAD = 264194,
	ALIVE = 2050
};

enum Animation {
	AIMING = 1
};
