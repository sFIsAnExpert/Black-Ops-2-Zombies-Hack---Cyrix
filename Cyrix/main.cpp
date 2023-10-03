#include "main.h"
#include "ImGuiManage.h"
#include "kiero/minhook/include/MinHook.h"

void miscThread() {
	while (1) {
		if (Globals::bEspAnim) {
			Globals::iRGBESP = Rand(0, 16777215);
		}
		if (Globals::bSnapAnim) {
			Globals::iRGBSnap = Rand(0, 16777215);
		}
		Sleep(Globals::iAnimSpd);
	}
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.DisplaySize = { 250,250 };
	ImGuiStyle* style = &ImGui::GetStyle();

	if (io.ConfigFlags)
	{
		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 5.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(255, 0, 0, .70f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.f, 0.f, 1.f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0, 0, 0, 0);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(255, 0, 0, .70f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(255, 0, 0, .85f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(255, 0, 0, .85f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
		style->WindowRounding = 4.0f;
	}
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
			pDevice->GetImmediateContext(&pContext);
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

	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin(Xor("Cyrix - ChasePlays"));

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
				ImGui::GetBackgroundDrawList()->AddRect(ImVec2(screenpos.x - (width / 2.3), screenpos.y), ImVec2(screenpos.x + (width / 2.3), screenpos.y + height), ImColor(Globals::iRGBESP & 255, (Globals::iRGBESP >> 8) & 255, (Globals::iRGBESP >> 16)&255));
				if (Globals::bFill)
					ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(screenpos.x - (width / 2.3), screenpos.y), ImVec2(screenpos.x + (width / 2.3), screenpos.y + height), ImColor(0,0,0,70));
				if (Globals::bSnapLines)
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Resolution.x / 2, Resolution.y), ImVec2(screenpos.x, screenpos.y), ImColor(Globals::iRGBSnap & 255, (Globals::iRGBSnap >> 8) & 255, (Globals::iRGBSnap >> 16) & 255));
			}
		}
	}

	ManageImGui(pContext, mainRenderTargetView);

	ImGui::End();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(pSwapChain, SyncInterval, Flags);
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

	IntializeVehHook();

	std::thread tMisc(miscThread);
	tMisc.detach();

	while (true) {
		if (Globals::bInfMoney) {
			uintptr_t dwMoney = pInfo.moduleBase + 0x1F47D68;
			external.WPM<int>(dwMoney, 999999);
			Globals::bInfMoney = false;
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