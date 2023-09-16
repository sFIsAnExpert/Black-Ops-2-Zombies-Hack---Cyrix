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
		ImGui::Checkbox(D("DRO").c_str(), &Globals::bEsp); 
		if (Globals::bEsp) {
			ImGui::SameLine();
			ImGui::Checkbox("Fill", &Globals::bAimbot);
		}
		ImGui::Checkbox(D("Rm`okhmdr").c_str(), &Globals::bSnapLines);
		if (ImGui::Checkbox(D("Bg`lr").c_str(), &Globals::bChams)) {
			Memory::External ext;
			if (Globals::bChams) {
				ext.WPM<float>(0x2A0F1C0, Globals::iChamsR);
				ext.WPM<float>(0x2A0F1C4, Globals::iChamsG);
				ext.WPM<float>(0x2A0F1C8, Globals::iChamsB);
			}
			else {
				ext.WPM<float>(0x2A0F1C0, 0);
				ext.WPM<float>(0x2A0F1C4, 0);
				ext.WPM<float>(0x2A0F1C8, 0);
			}
		}
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
		ImGui::SliderInt("ESP Color", &Globals::iRGBESP, 0, 16777215);
		ImGui::SameLine(); ImGui::Checkbox("Animate", &Globals::bEspAnim);
		ImGui::SliderInt("Snaplines Color", &Globals::iRGBSnap, 0, 16777215);
		ImGui::SameLine(); ImGui::Checkbox("Animate", &Globals::bSnapAnim);
		ImGui::SliderInt("Chams R", &Globals::iChamsR, 0, 255); 
		ImGui::SliderInt("Chams G", &Globals::iChamsG, 0, 255); 
		ImGui::SliderInt("Chams B", &Globals::iChamsB, 0, 255);
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
	CreateGui();
}