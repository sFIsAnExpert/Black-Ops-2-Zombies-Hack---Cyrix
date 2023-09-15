#pragma once
#include "ImGuiManage.h"

DWORD hex = 0xFFF;

std::string D(std::string txt) {
	std::string rtn = "";
	for (char rC : txt) {
		if (rC != ' ') {
			DWORD at = (DWORD)rC;
			rtn += (char)(at -= hex);
		}
		else
			rtn += " ";
	}

	return rtn;
}

void CreateGui() {
	
	if (ImGui::Button(D("Uhrt`kr").c_str(), ImVec2(150, 25))) { //Visuals
		Globals::iTab = 1;
	}
	ImGui::SameLine();
	if (ImGui::Button(D("@hl").c_str(), ImVec2(150, 25))) { //Aim
		Globals::iTab = 2;
	}
	ImGui::SameLine();
	if (ImGui::Button(D("Lhrb").c_str(), ImVec2(150, 25))) { //Misc
		Globals::iTab = 3;
	}
	ImGui::SameLine();
	if (ImGui::Button(D("@bbntms").c_str(), ImVec2(150, 25))) { //Account
		Globals::iTab = 4;
	}
	ImGui::SameLine();
	if (ImGui::Button(D("Gnrs Nmkx").c_str(), ImVec2(150, 25))) { //Host Only
		Globals::iTab = 5;
	}
	ImGui::NewLine();
	if (Globals::iTab == 1) {
		ImGui::Checkbox(D("DRO").c_str(), &Globals::bEsp); ImGui::SameLine();
		ImGui::Checkbox(D("Rm`okhmdr").c_str(), &Globals::bSnapLines);
	}
	if (Globals::iTab == 2) {
		ImGui::Checkbox(D("@hlans").c_str(), &Globals::bAimbot);
		ImGui::SliderInt(D("Rlnnsgmdrr").c_str(), & Globals::iSmoothness, 10, 1000);
		ImGui::SliderInt(D("Q`chtr").c_str(), &Globals::iRadius, 0, 100);
		ImGui::NewLine();
		if (ImGui::Checkbox(D("Rhkdms @hl").c_str(), &Globals::bSilentAim)) {
			if (Globals::bSilentAim && !Globals::bSilentAimChk)
				Globals::bSilentAimChk = true;
			else if (!Globals::bSilentAim && !Globals::bSilentAimChk) {
				Globals::bSilentUnhook = true;
			}
		}
	}
	if (Globals::iTab == 3) {
		ImGui::SliderFloat("R", &Globals::R, 0, 255);
		ImGui::SliderFloat("G", &Globals::G, 0, 255);
		ImGui::SliderFloat("B", &Globals::B, 0, 255);
		ImGui::SliderFloat("A", &Globals::A, 0, 255);
	}
	if (Globals::iTab == 5) {
		ImGui::Checkbox(D("Hmehmhsd Lnmdx").c_str(), &Globals::bInfMoney);
		ImGui::SameLine();
		ImGui::Checkbox(D("Hmehmhsd @lln").c_str(), & Globals::bInfAmmo);
		ImGui::NewLine();
		if (ImGui::Checkbox(D("Fnclncd").c_str(), &Globals::bGodmode)) {
			IW5Engine engine;
			if (!Globals::bGodmode) {
				engine.Player.Health.SetHealth(100);
			}
			else
				engine.Player.Health.SetHealth(9999999);
		}
	}
}

void ManageImGui(ID3D11DeviceContext* pContext, ID3D11RenderTargetView* mainRenderTargetView) {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin(D("Oktsnmhtl Ynlahdr , Bg`rdOk`xr").c_str());

	CreateGui();
	ImGui::End();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}