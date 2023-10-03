#pragma once
#include "Memory.h"
#include "offsets.h"


struct IW5Engine {
public:
	struct Player {
	public:
		struct Weapon {
		public:
			void SetInfiniteAmmo();
		};
		struct Input {
			uintptr_t GetInput();
		};
		struct Location {
		public:
			Vector3 Position();
			centity_t SilentClosestEntity();
			std::map<float, centity_t> GetClosestEntity();
			std::map<float, centity_t> GetClosestEntityAim();
		};
		struct Health {
		public:
			void SetHealth(int rV);
		};
		struct View {
		public:
			void Aimbot();
			ViewMatrix GetViewMatrix();
		};
		LocalPlayer GetLocalPlayer();
		Location Location;
		View View;
		Input Input;
		Weapon Weapon;
		Health Health;
	};
	struct Server {
	public:
		struct World {
		public:
			uintptr_t CEntityPtr();
			std::vector<centity_t> GetEntityList();
		};
		World World;
	};
	struct Screen {
	public:
		IntVector2 GetResolution();
	};
	struct Functions {
	public:
		void print_to_screen(std::string msg);
		Vector3* AdjustModelState(Vector3* vec, int state);
		bool IsFriendly(int, const centity_t*);
		int AimTarget_IsTargetVisible(centity_t* entity);
		int CL_GetCurrentCmdNumber();
	};
	Screen Screen;
	Player Player;
	Server Server;
	Functions Functions;
};



