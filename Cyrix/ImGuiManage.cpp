#pragma once
#include "ImGuiManage.h"

void CreateGui() {
	
	if (ImGui::Button(Xor("Visuals"), ImVec2(150, 25))) { 
		Globals::iTab = 1;
	}
	ImGui::SameLine();
	if (ImGui::Button(Xor("Aim"), ImVec2(150, 25))) { 
		Globals::iTab = 2;
	}
	ImGui::SameLine();
	if (ImGui::Button(Xor("Misc"), ImVec2(150, 25))) { 
		Globals::iTab = 3;
	}
	ImGui::SameLine();
	if (ImGui::Button(Xor("Account"), ImVec2(150, 25))) { 
		Globals::iTab = 4;
	}
	ImGui::SameLine();
	if (ImGui::Button(Xor("Host Only"), ImVec2(150, 25))) { 
		Globals::iTab = 5;
	}
	ImGui::NewLine();
	if (Globals::iTab == 1) {
		ImGui::Checkbox(Xor("ESP"), &Globals::bEsp);
		if (Globals::bEsp) {
			ImGui::SameLine();
			ImGui::Checkbox(Xor("Fill"), &Globals::bFill);
		}
		ImGui::Checkbox(Xor("Snaplines"), &Globals::bSnapLines);
		if (ImGui::Checkbox(Xor("Chams"), &Globals::bChams)) {
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
		ImGui::Checkbox(Xor("Aimbot"), &Globals::bAimbot);
		ImGui::SliderInt(Xor("Smoothness"), &Globals::iSmoothness, 10, 1000);
		ImGui::SliderInt(Xor("Radius"), &Globals::iRadius, 0, 100);
		ImGui::NewLine();
		if (ImGui::Checkbox(Xor("Silent Aim"), &Globals::bSilentAim)) {
			if (Globals::bSilentAim && !Globals::bSilentAimChk)
				Globals::bSilentAimChk = true;
			else if (!Globals::bSilentAim && !Globals::bSilentAimChk) {
				Globals::bSilentUnhook = true;
			}
		}
	}
	if (Globals::iTab == 3) {
		ImGui::SliderInt(Xor("ESP Color"), &Globals::iRGBESP, 0, 16777215);
		ImGui::SameLine(); ImGui::Checkbox(Xor("ESP Animate"), &Globals::bEspAnim);
		ImGui::SliderInt("Snaplines Color", &Globals::iRGBSnap, 0, 16777215);
		ImGui::SameLine(); ImGui::Checkbox(Xor("Snap Animate"), &Globals::bSnapAnim);
		ImGui::SliderInt(Xor("Animation Speed"), &Globals::iAnimSpd, 0, 10000);
		ImGui::SliderInt(Xor("Chams R"), &Globals::iChamsR, 0, 255); 
		ImGui::SliderInt(Xor("Chams G"), &Globals::iChamsG, 0, 255); 
		ImGui::SliderInt(Xor("Chams B"), &Globals::iChamsB, 0, 255);
	}
	if (Globals::iTab == 5) {
		ImGui::Checkbox(Xor("Infinite Money"), &Globals::bInfMoney);
		ImGui::SameLine();
		ImGui::Checkbox(Xor("Infinite Ammo"), &Globals::bInfAmmo);
		ImGui::NewLine();
		if (ImGui::Checkbox(Xor("God Mode"), &Globals::bGodmode)) {
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