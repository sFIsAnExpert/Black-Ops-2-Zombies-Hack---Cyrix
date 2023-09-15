#include "main.h"
#include "ImGuiManage.h"
#include "kiero/minhook/include/MinHook.h"

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.DisplaySize = { 250,250 };
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			dxRender = new D3D11Renderer(pSwapChain);
			pDevice->GetImmediateContext(&pContext);
			dxRender->Initialize();
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	dxRender->BeginScene();

	if (Globals::bEsp) {
		for (const gEntity& entity : engine.Server.World.GetGEntityList()) {
			ViewMatrix vm = engine.Player.View.GetViewMatrix();
			Vector3 pos = entity.Position;
			Vector3 headPos; headPos.x = pos.x; headPos.y = pos.y; headPos.z = pos.z + 75.f;
			Vector3 screenpos = WorldToScreen(pos, vm, Resolution.x, Resolution.y);
			Vector3 screenhead = WorldToScreen(headPos, vm, Resolution.x, Resolution.y);
			float height = screenhead.y - screenpos.y;
			float width = height / 2.4f;
			if (screenpos.z > 0.001f) {
				dxRender->FillRect(screenpos.x - (width / 2.3), screenpos.y, width, height, Color(Globals::A, Globals::R, Globals::G, Globals::B));
				if (Globals::bSnapLines)
					dxRender->DrawLine(Resolution.x / 2, Resolution.y, screenpos.x, screenpos.y, Color(Globals::A, Globals::R, Globals::G, Globals::B));
			}
		}
	}

	dxRender->EndScene();

	ManageImGui(pContext, mainRenderTargetView);

	return oPresent(pSwapChain, SyncInterval, Flags);
}

int __cdecl hkWritePacket(int num) {
	if (Globals::bSilentAim) {
		Vector3 AimbottedAngles = Vector3(0, 0, 0);
		input_s* input = (input_s*)engine.Player.Input.GetInput();

		static int BackUpAngles[3];

		usercmd_s* oldCmd = input->GetUserCmd(input->currentCmdNum - 1);
		usercmd_s* cmd = input->GetUserCmd(input->currentCmdNum);
		usercmd_s* newCmd = input->GetUserCmd(input->currentCmdNum + 1);

		CopyMemory(newCmd, cmd, sizeof(usercmd_s));
		++input->currentCmdNum;

		oldCmd->viewAngles[0] = BackUpAngles[0];
		oldCmd->viewAngles[1] = BackUpAngles[1];
		oldCmd->viewAngles[2] = BackUpAngles[2];

		BackUpAngles[0] = cmd->viewAngles[0];
		BackUpAngles[1] = cmd->viewAngles[1];
		BackUpAngles[2] = cmd->viewAngles[2];

		++oldCmd->serverTime;
		--cmd->serverTime;

		std::map<float, gEntity> distList = engine.Player.Location.GetClosestEntity();
		std::map<float, gEntity>::iterator it;
		if (!distList.empty()) {
			for (it = distList.begin(); it != distList.end(); it++);
			gEntity entity = it->second;
			LocalPlayer p = engine.Player.GetLocalPlayer();
			Vector3 them = entity.Position; them.z += 40.f;
			Vector3 self = Vector3(p.ViewOrigin.x, p.ViewOrigin.y, p.ViewOrigin.z);
			m.GetAngleToTarget(them, self, AimbottedAngles);
			DeltaX = AimbottedAngles.x - inter.RPM<float>(0x0103AC60);
			DeltaY = AimbottedAngles.y - inter.RPM<float>(0x0103AC5C);

			float flOldYaw = ShortToAngle(oldCmd->viewAngles[1]);

			oldCmd->viewAngles[0] += ANGLE2SHORT(DeltaY);
			oldCmd->viewAngles[1] += ANGLE2SHORT(DeltaX);
		}
	}

	return pHookWritePacket(num);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	CScreen::Info sInfo;
	external.GatherProcessInfo();
	Resolution = engine.Screen.GetResolution();
	sInfo.x = Resolution.x; sInfo.y = Resolution.y;
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);

	pHookWritePacketTarget = reinterpret_cast<CL_WritePacket>(offsets.CL_WritePacket);
	if (MH_CreateHook((LPVOID*)pHookWritePacketTarget, &hkWritePacket, (void**)&pHookWritePacket) != MH_OK)
	{
		MessageBoxA(0, "MH Failed", "Failed", 0);
	}

	while (true) {
		if (Globals::bInfMoney) {
			uintptr_t dwMoney = pInfo.moduleBase + 0x1F47D68;
			external.WPM<int>(dwMoney, 999999);
			Globals::bInfMoney = false;
		}
		if (Globals::bSilentAim) {
			if (Globals::bSilentAimChk) {
				Globals::bSilentAimChk = false;
				if (MH_EnableHook((LPVOID*)pHookWritePacketTarget) != MH_OK)
				{
					MessageBoxA(0, "MH Failed", "Failed", 0);
				}
			}
		}
		if (Globals::bSilentUnhook) {
			Globals::bSilentUnhook = false;
			if (MH_DisableHook((LPVOID*)pHookWritePacketTarget) != MH_OK)
			{
				MessageBoxA(0, "MH Failed", "Failed", 0);
			}
		}
		if (Globals::bAimbot) {
			if (GetAsyncKeyState(VK_RBUTTON)) {
				engine.Player.View.Aimbot();
			}
		}
		if (Globals::bInfAmmo) {
			Globals::bInfAmmo = false;
			engine.Player.Weapon.SetInfiniteAmmo();
		}
	}

	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}