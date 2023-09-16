#include "includes.h"
#include "Cyrix/Engine.h"
#include <random>


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int Rand(int p, int p2) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(p, p2); 

    return dist6(rng);
}

typedef int(__cdecl* R_AddDObjToScene)(int* a1, int ent, int ent_num, int renderflags, int a2, int a3, int a4, bool a5, int a6, int scs, int a8, float a9, bool a10);
R_AddDObjToScene rAdd, rAddTarget;

typedef int(__cdecl* CL_WritePacket)(int);
CL_WritePacket pHookWritePacket = 0;
CL_WritePacket pHookWritePacketTarget = 0;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

Memory::External external;
Memory::Internal inter;
Memory::ProcessInfo pInfo;
Offsets offsets;
Math m;
IW5Engine engine;
IntVector2 Resolution;

bool init = false;
float DeltaX = 0, DeltaY = 0;