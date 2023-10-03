#include "includes.h"
#include <random>
#include "VEH.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int Rand(int p, int p2) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(p, p2); 

    return dist6(rng);
}

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
IW5Engine engine;
IntVector2 Resolution;

bool init = false;