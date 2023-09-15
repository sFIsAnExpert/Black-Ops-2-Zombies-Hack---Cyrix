#pragma once
#include <Windows.h>
#include "Math.h"

struct Offsets {
	uintptr_t dwEntityList = 0x021C5B44;
	uintptr_t dwToNextLocal = 0x31C;
	uintptr_t dwToNextGEntity = 0x380;
	uintptr_t dwViewMatrix = 0x33F0EE0;
	uintptr_t cg_printToScreen = 0x5F4F10;
	uintptr_t dwLocalPlayer = 0x0103AC48;
	uintptr_t dwResolution = 0x03A0D6B0;
	uintptr_t dwLocalPlayerPos = 0x23427C8;
	uintptr_t cg_weapon1_ammo = 0x2342BCC;
	uintptr_t cg_weapon2_ammo = 0x2342BD4;
	uintptr_t dwHealth = 0x21C1568;

	uintptr_t CL_GetCurrentCmdNumber = 0x490A50;
	uintptr_t CL_WritePacket = 0x444C60;
};

struct centity_t {
public:
	char pad_0000[24]; //0x0000
	Vector3 Position; //0x0018
	char pad_0024[388]; //0x0024
	int Health; //0x01A8
	int MaxHealth; //0x01AC
}; //Size: 0x0448

struct gEntity
{
public:
	char pad_0000[24]; //0x0000
	Vector3 Position; //0x0018
	char pad_0024[424]; //0x0024
	int32_t Valid; //0x01CC
}; //Size: 0x0748

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

enum Stance {
	STANDING = 2,
	CROUCH = 6,
	PRONE = 10,
	RUNNING = 131074
};
