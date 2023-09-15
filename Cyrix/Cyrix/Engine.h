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
		int CL_GetCurrentCmdNumber();
	};
	Screen Screen;
	Player Player;
	Server Server;
	Functions Functions;
};



