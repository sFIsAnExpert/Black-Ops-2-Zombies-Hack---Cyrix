#include "Engine.h"

Memory::External ext;
Memory::Internal in;

Offsets off;
ViewMatrix IW5Engine::Player::View::GetViewMatrix()
{
	return in.RPM<ViewMatrix>(off.dwViewMatrix);
}

uintptr_t IW5Engine::Server::World::GEntity()
{
	Memory::ProcessInfo info;
	uintptr_t base = info.moduleBase + 0x31266FC;
	return ext.FinalAddress(base, { 0x2C }) - 0x3AC;
}

std::vector<centity_t> IW5Engine::Server::World::GetEntityList()
{
    std::vector<centity_t> list = {};
    int toNext = off.dwToNextLocal;
    for (int i = 0; i < 255; i++) {
        centity_t entity = ext.RPM<centity_t>(off.dwEntityList + toNext);
        if(entity.Health > 0)
            list.push_back(entity);
        toNext += off.dwToNextLocal;
    }

    return list;
}

std::vector<gEntity> IW5Engine::Server::World::GetGEntityList()
{
	std::vector<gEntity> list = {};
	uintptr_t listBase = this->GEntity();
	int toNext = off.dwToNextGEntity;
	for (int i = 0; i < 255; i++) {
		gEntity entity = ext.RPM<gEntity>(listBase + toNext);
		if (entity.Valid == State::ALIVE && entity.ClientNum > 0 && entity.Position.x != 0 && entity.Position.y != 0 && entity.Position.z != 0) {
			list.push_back(entity);
		}
		toNext += off.dwToNextGEntity;
	}

	return list;
}

bool IW5Engine::Functions::IsFriendly(int cNum, const gEntity* cEntity)
{
	typedef bool(__cdecl* stup)(int, const gEntity*);
	stup setup = reinterpret_cast<stup>(off.CG_IsEntityFriendlyNotEnemy);
	return setup(cNum, cEntity);
}

int IW5Engine::Functions::AimTarget_IsTargetVisible(int cNum, gEntity* cEntity)
{
	typedef char(__cdecl* stup)(int, gEntity*);
	stup setup = reinterpret_cast<stup>(off.AimTarget_IsTargetVisible);
	return setup(cNum, cEntity);
}

IntVector2 IW5Engine::Screen::GetResolution()
{
	Memory::ProcessInfo info;
	uintptr_t res = info.moduleBase + 0xDA554C;
	return in.RPM<IntVector2>(res);
}

void IW5Engine::Functions::print_to_screen(std::string msg) {
    typedef void(__stdcall* setup)(int a1, int a2, const char* Message, ...);
    setup print_to_screen = reinterpret_cast<setup>(off.cg_printToScreen);
    std::string fStr = "; \"" + msg + "\"";
    print_to_screen(0, 0, fStr.c_str());
}

int IW5Engine::Functions::CL_GetCurrentCmdNumber()
{
	typedef int(__cdecl* setup)(int num);
	setup GetCmdNum = reinterpret_cast<setup>(off.CL_GetCurrentCmdNumber);
	return GetCmdNum(0);
}

std::map<float, gEntity> IW5Engine::Player::Location::GetClosestEntity()
{
	Offsets offset; std::map<float, gEntity> distList = {}; Memory::External ext; IW5Engine engine;

	for (gEntity entity : engine.Server.World.GetGEntityList()) {
		float dist = Dist3D(engine.Player.Location.Position(), entity.Position);
		if (!engine.Functions.IsFriendly(entity.ClientNum, &entity)) {
			if (dist <= 9999999) {
				distList.insert({ dist, entity });
			}
		}
	}
	std::map<float, gEntity>::iterator it; float min_val = 99999999;
	for (it = distList.begin(); it != distList.end(); it++) {
		if (it->first < min_val) {
			min_val = it->first;
		}
	}
	gEntity rtn = distList.find(min_val)->second;
	std::map<float, gEntity> finalMap = {};
	finalMap.insert({ min_val, rtn });

	return finalMap;
}

std::map<float, gEntity> IW5Engine::Player::Location::GetClosestEntityAim()
{
	Offsets offset; std::map<float, gEntity> distList = {}; Memory::External ext; IW5Engine engine;
	CScreen::Info inf; Math math;
	if (!engine.Server.World.GetGEntityList().empty()) {
		for (gEntity& entity : engine.Server.World.GetGEntityList()) {
			float dist = Dist3D(engine.Player.Location.Position(), entity.Position);
			if (dist <= 99999 && dist >= 2) {
				if (!engine.Functions.IsFriendly(entity.ClientNum, &entity)) {
					distList.insert({ dist, entity });
				}
			}
		}
	}
	if (!distList.empty()) {
		std::map<float, gEntity>::iterator it; float min_val = 999999;
		for (it = distList.begin(); it != distList.end(); it++) {
			if (it->first < min_val) {
				min_val = it->first;
			}
		}
		gEntity rtn = distList.find(min_val)->second;
		std::map<float, gEntity> finalMap = {};
		if (rtn.Position.x != 0 && rtn.Position.y != 0 && rtn.Position.z != 0 && rtn.ClientNum > 0 && rtn.Valid == State::ALIVE) {
			finalMap.insert({ min_val, rtn });
			return finalMap;
		}
	}
	
	std::map<float, gEntity> emptyMap = {};
	return emptyMap;
}

void IW5Engine::Player::View::Aimbot()
{
	IW5Engine engine; Math math; CScreen::Info inf;
	std::map<float, gEntity> distList = engine.Player.Location.GetClosestEntityAim();
	std::map<float, gEntity>::iterator it;
	if (!distList.empty()) {
		for (it = distList.begin(); it != distList.end(); it++);
		gEntity entity = it->second;

		if (entity.Position.x != 0 && entity.Position.y != 0 && entity.Position.z != 0 && entity.ClientNum > 0 && entity.Valid == State::ALIVE) {
			ViewMatrix vm = engine.Player.View.GetViewMatrix();
			Vector3 pos = entity.Position;
			pos.z += 50.f;
			Vector3 screenpos = WorldToScreen(pos, vm, inf.x, inf.y);
			float threshold = math.Dist2D(Vector2(inf.x / 2 + Globals::iRadius, inf.y / 2 + Globals::iRadius), Vector2(inf.x / 2 - Globals::iRadius, inf.y / 2 - Globals::iRadius));
			float dist = math.Dist2D(Vector2(screenpos.x, screenpos.y), Vector2(inf.x / 2, inf.y / 2));
			if (dist <= threshold)
				AimAtPos(screenpos.x, screenpos.y, inf.x, inf.y, Globals::iSmoothness);
		}
	}
}


LocalPlayer IW5Engine::Player::GetLocalPlayer()
{
	return in.RPM<LocalPlayer>(off.dwLocalPlayer);
}

Vector3 IW5Engine::Player::Location::Position()
{
	return in.RPM<Vector3>(off.dwLocalPlayerPos);
}

uintptr_t IW5Engine::Player::Input::GetInput()
{
	uintptr_t base = ext.GetModuleBase(L"plutonium-bootstrapper-win32.exe") + 0xDFD1C8;
	return ext.FinalAddress(base, { 0x10,0x60,0x0}) - 0x7CFE8;
}

void IW5Engine::Player::Weapon::SetInfiniteAmmo()
{
	ext.WPM<int>(off.cg_weapon1_ammo, 999999);
	ext.WPM<int>(off.cg_weapon2_ammo, 999999);
}

void IW5Engine::Player::Health::SetHealth(int rV)
{
	ext.WPM<int>(off.dwHealth, rV);
}
