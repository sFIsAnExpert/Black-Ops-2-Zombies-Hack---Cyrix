#include "includes.h"
#include "Cyrix/Engine.h"
#include "Cyrix/D3D11Renderer.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef int(__cdecl* CL_WritePacket)(int);
CL_WritePacket pHookWritePacket = 0;
CL_WritePacket pHookWritePacketTarget = 0;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
D3D11Renderer* dxRender;

Memory::External external;
Memory::Internal inter;
Memory::ProcessInfo pInfo;
Offsets offsets;
Math m;
IW5Engine engine;
IntVector2 Resolution;

bool init = false;
float DeltaX = 0, DeltaY = 0;