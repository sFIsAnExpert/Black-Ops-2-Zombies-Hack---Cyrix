#include "VEH.h"

PVOID hVeh;
uintptr_t PreCorruptedContents;
uintptr_t* PointerToCorrupt = (uintptr_t*)(0x1198444);
IW5Engine tengine; Math m; Memory::Internal inte;

float DeltaX, DeltaY;
void CL_WritePacketHook() {
	if (Globals::bSilentAim) {
		if (GetAsyncKeyState(VK_RBUTTON)) {
			Vector3 AimbottedAngles = Vector3(0, 0, 0);
			input_s* input = (input_s*)tengine.Player.Input.GetInput();

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

			centity_t entity = tengine.Player.Location.SilentClosestEntity();
			if (entity.Valid != EntityState::BAD_ENTITY) {
				LocalPlayer p = tengine.Player.GetLocalPlayer();
				Vector3 them = entity.Position; them.z += 52.f;
				Vector3 self = Vector3(p.ViewOrigin.x, p.ViewOrigin.y, p.ViewOrigin.z);
				m.GetAngleToTarget(them, self, AimbottedAngles);
				DeltaX = AimbottedAngles.x - inte.RPM<float>(0x0103AC60);
				DeltaY = AimbottedAngles.y - inte.RPM<float>(0x0103AC5C);

				float flOldYaw = ShortToAngle(oldCmd->viewAngles[1]);

				oldCmd->viewAngles[0] += ANGLE2SHORT(DeltaY);
				oldCmd->viewAngles[1] += ANGLE2SHORT(DeltaX);
			}
		}
	}
}

LONG CALLBACK pVectoredExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo) {
	if (pExceptionInfo->ExceptionRecord->ExceptionCode != EXCEPTION_GUARD_PAGE)
	{
		switch (pExceptionInfo->ContextRecord->Eax) {
		case 33833:
			pExceptionInfo->ContextRecord->Eax = PreCorruptedContents;
			CL_WritePacketHook();
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		if (pExceptionInfo->ContextRecord->Eip == 0x6F165B)
		{
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

void IntializeVehHook()
{
	SetUnhandledExceptionFilter(0);
	hVeh = AddVectoredExceptionHandler(true, (PVECTORED_EXCEPTION_HANDLER)pVectoredExceptionHandler);
	PreCorruptedContents = *PointerToCorrupt;
	*PointerToCorrupt = 33833;
}