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
			gEntity SilentClosestEntity();
			std::map<float, gEntity> GetClosestEntity();
			std::map<float, gEntity> GetClosestEntityAim();
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
			uintptr_t GEntity();
			std::vector<centity_t> GetEntityList();
			std::vector<gEntity> GetGEntityList();
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
		bool IsFriendly(int, const gEntity*);
		int AimTarget_IsTargetVisible(gEntity* entity);
		int CL_GetCurrentCmdNumber();
		gEntity* CG_GetEntity(int cNum);
	};
	Screen Screen;
	Player Player;
	Server Server;
	Functions Functions;
};



