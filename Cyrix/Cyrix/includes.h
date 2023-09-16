#pragma once

#include <cmath>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <Psapi.h>
#include <string>
#include <map>
#include <thread>
#include <intrin.h>
#include <cmath>
#include <math.h>
#include <intrin.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <d3dcompiler.h>
#include <D3D11Shader.h>
#include <D3DX11.h>
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib,"D3DCompiler.lib")
#pragma comment(lib, "d3d11.lib")


#pragma once
#ifndef GLOBALS_H_
#define GLOBALS_H_

namespace Globals
{
	inline int iTabCount = 0;
	inline int iTab = 0, iChatAmount = 1, iRGBESP = 255, iRGBSnap = 255, iChamsR = 255, iChamsG = 0, iChamsB = 0;
	inline int iSmoothness = 50, iCircleRadius = 40, iRadius = 10;
	inline float iCircleThickness = 1.5f, iFoV = 1.25;
	inline bool bEsp = false, bDrawCircle = false, bDrawHealth = false, bSnapLines = false, bInfMoney = false, bAimbot = false, bSilentAim = false, bInfAmmo = false;
	inline bool bGodmode = false, bGodmodeChk = false, bLockedOn = false, bHoldingAimbot = false, bSilentAimChk = false, bSilentUnhook = false, bChams = false;
	inline bool bEspAnim = false, bSnapAnim = false;
}

#endif