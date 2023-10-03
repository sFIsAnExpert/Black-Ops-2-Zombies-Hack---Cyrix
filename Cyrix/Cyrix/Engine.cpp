#include "Engine.h"

Memory::External ext;
Memory::Internal in;

Offsets off;
ViewMatrix IW5Engine::Player::View::GetViewMatrix()
{
	return in.RPM<ViewMatrix>(off.dwViewMatrix);
}

uintptr_t IW5Engine::Server::World::CEntityPtr()
{
	Memory::ProcessInfo info;
	uintptr_t base = info.moduleBase + 0x31266FC;
	uintptr_t finalPtr = ext.FinalAddress(base, { 0x2C }) - 0x3AC;
	return finalPtr;
}


Vector3* IW5Engine::Functions::AdjustModelState(Vector3* vec, int state)
{
	Vector3* ret = new Vector3(); ret->x = vec->x; ret->y = vec->y; ret->z = vec->z;
	if (state == MODEL_STATE::STANDING || state == MODEL_STATE::STANDING2)
		ret->z += 53.f;
	else if (state == MODEL_STATE::CROUCH || state == MODEL_STATE::CROUCH2)
		ret->z += 42.f;
	else if (state == MODEL_STATE::PRONE || state == MODEL_STATE::PRONE2)
		ret->z += 12.f;
	else
		ret->z += 53.f;

	return ret;
}

std::vector<centity_t> IW5Engine::Server::World::GetEntityList()
{
	std::vector<centity_t> list = {};
	uintptr_t listBase = this->CEntityPtr();
	int toNext = off.dwToNextcentity_t;
	for (int i = 0; i <150; i++) {
		centity_t entity = ext.RPM<centity_t>(listBase + toNext);
		if (entity.Valid == State::ALIVE && entity.ClientNum > 0) {
			list.push_back(entity);
		}
		toNext += off.dwToNextcentity_t;
	}

	return list;
}

bool IW5Engine::Functions::IsFriendly(int cNum, const centity_t* cEntity)
{
	typedef bool(__cdecl* stup)(int, const centity_t*);
	stup setup = reinterpret_cast<stup>(off.CG_IsEntityFriendlyNotEnemy);
	return setup(cNum, cEntity);
}

int IW5Engine::Functions::AimTarget_IsTargetVisible(centity_t* entity)
{
	typedef char(__cdecl* stup)(int, centity_t*);
	stup setup = reinterpret_cast<stup>(off.AimTarget_IsTargetVisible);
	
	return setup(0, entity);
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

centity_t IW5Engine::Player::Location::SilentClosestEntity()
{
	IW5Engine engine; int max_dist = 999999, i = 0, entAt = 0;
	centity_t badEnt; badEnt.Valid = EntityState::BAD_ENTITY; bool isVis = false;
	std::vector<centity_t> list = engine.Server.World.GetEntityList();
	for (centity_t entity : list) {
		int dist = (int)(Dist3D(engine.Player.GetLocalPlayer().Position, entity.Position));
		if (engine.Functions.AimTarget_IsTargetVisible(&entity)) {
			if (!isVis)
				max_dist = 999999;
			isVis = true;
			if (dist < max_dist) {
				max_dist = dist;
				entAt = i;
			}
		}
		else if (dist < max_dist && !isVis) {
			max_dist = dist;
			entAt = i;
		}
		i++;
	}

	if (max_dist < 999999)
		return list.at(entAt);
	else
		return badEnt;

	return badEnt;
}

std::map<float, centity_t> IW5Engine::Player::Location::GetClosestEntity()
{
	Offsets offset; std::map<float, centity_t> distList = {}; Memory::External ext; IW5Engine engine;

	if (!engine.Server.World.GetEntityList().empty()) {
		for (centity_t& entity : engine.Server.World.GetEntityList()) {
			float dist = Dist3D(engine.Player.Location.Position(), entity.Position);
			if (dist <= 9999999) {
				if (!engine.Functions.IsFriendly(entity.ClientNum, &entity)) {
					distList.insert({ dist, entity });
				}
			}
		}
	}
	if (!distList.empty()) {
		std::map<float, centity_t>::iterator it; float min_val = 999999;
		for (it = distList.begin(); it != distList.end(); it++) {
			if (it->first < min_val) {
				min_val = it->first;
			}
		}
		centity_t rtn = distList.find(min_val)->second;
		std::map<float, centity_t> finalMap = {};
		finalMap.insert({ min_val, rtn });
		return finalMap;
	}

	std::map<float, centity_t> emptyMap = {};
	return emptyMap;
}

std::map<float, centity_t> IW5Engine::Player::Location::GetClosestEntityAim()
{
	Offsets offset; std::map<float, centity_t> distList = {}; Memory::External ext; IW5Engine engine;
	CScreen::Info inf; Math math;
	if (!engine.Server.World.GetEntityList().empty()) {
		for (centity_t& entity : engine.Server.World.GetEntityList()) {
			float dist = Dist3D(engine.Player.Location.Position(), entity.Position);
			if (dist <= 99999) {
				if (!engine.Functions.IsFriendly(entity.ClientNum, &entity)) {
					distList.insert({ dist, entity });
				}
			}
		}
	}
	if (!distList.empty()) {
		std::map<float, centity_t>::iterator it; float min_val = 999999;
		for (it = distList.begin(); it != distList.end(); it++) {
			if (it->first < min_val) {
				min_val = it->first;
			}
		}
		centity_t rtn = distList.find(min_val)->second;
		std::map<float, centity_t> finalMap = {};
		finalMap.insert({ min_val, rtn });
		return finalMap;
	}
	
	std::map<float, centity_t> emptyMap = {};
	return emptyMap;
}

void IW5Engine::Player::View::Aimbot()
{
	IW5Engine engine; Math math; CScreen::Info inf;
	std::map<float, centity_t> distList = engine.Player.Location.GetClosestEntityAim();
	std::map<float, centity_t>::iterator it;
	if (!distList.empty()) {
		for (it = distList.begin(); it != distList.end(); it++);
		centity_t entity = it->second;

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
