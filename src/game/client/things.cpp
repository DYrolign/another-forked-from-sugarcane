
#include "things.h"

/* InfClassR */
const std::vector<EInfClass> &AllInfClassClasses()
{
	static std::vector<EInfClass> Classes;
	if(Classes.empty())
	{
		for(int i = START_HUMANCLASS + 1; i < END_HUMANCLASS; i++)
		{
			Classes.push_back(static_cast<EInfClass>(i));
		}
		for(int i = START_INFECTEDCLASS + 1; i < END_INFECTEDCLASS; i++)
		{
			Classes.push_back(static_cast<EInfClass>(i));
		}
	}
	return Classes;
}

const char *GetClassDisplayName(EInfClass PlayerClass)
{
	switch (PlayerClass)
	{
		case EInfClass::PLAYERCLASS_MERCENARY:
			return "Mercenary";
		case EInfClass::PLAYERCLASS_MEDIC:
			return "Medic";
		case EInfClass::PLAYERCLASS_HERO:
			return "Hero";
		case EInfClass::PLAYERCLASS_ENGINEER:
			return "Engineer";
		case EInfClass::PLAYERCLASS_SOLDIER:
			return "Soldier";
		case EInfClass::PLAYERCLASS_NINJA:
			return "Ninja";
		case EInfClass::PLAYERCLASS_SNIPER:
			return "Sniper";
		case EInfClass::PLAYERCLASS_SCIENTIST:
			return "Scientist";
		case EInfClass::PLAYERCLASS_BIOLOGIST:
			return "Biologist";
		case EInfClass::PLAYERCLASS_LOOPER:
			return "Looper";

		case EInfClass::PLAYERCLASS_SMOKER:
			return "Smoker";
		case EInfClass::PLAYERCLASS_BOOMER:
			return "Boomer";
		case EInfClass::PLAYERCLASS_HUNTER:
			return "Hunter";
		case EInfClass::PLAYERCLASS_BAT:
			return "Bat";
		case EInfClass::PLAYERCLASS_GHOST:
			return "Ghost";
		case EInfClass::PLAYERCLASS_SPIDER:
			return "Spider";
		case EInfClass::PLAYERCLASS_GHOUL:
			return "Ghoul";
		case EInfClass::PLAYERCLASS_SLUG:
			return "Slug";
		case EInfClass::PLAYERCLASS_VOODOO:
			return "Voodoo";
		case EInfClass::PLAYERCLASS_WITCH:
			return "Witch";
		case EInfClass::PLAYERCLASS_UNDEAD:
			return "Undead";

		default:
			return "Unknown class";
	}
}

EInfClass GetClass(const char *pClanName)
{
	for(auto& Class : AllInfClassClasses())
	{
		if(str_find_nocase(pClanName, GetClassDisplayName(Class)))
			return Class;
	}
	return EInfClass::PLAYERCLASS_INVALID;
}

bool IsInfect(const char *pClanName)
{
	EInfClass Class = GetClass(pClanName);
	return Class > START_INFECTEDCLASS && Class < END_INFECTEDCLASS;
}

bool IsHuman(const char *pClanName)
{
	return !IsInfect(pClanName);
}

int IsDefender(const char *pClanName)
{
	EInfClass Class = GetClass(pClanName);
	if(Class == EInfClass::PLAYERCLASS_ENGINEER)
		return 5;
	if(Class == EInfClass::PLAYERCLASS_SOLDIER)
		return 4;
	if(Class == EInfClass::PLAYERCLASS_SCIENTIST)
		return 3;
	if(Class == EInfClass::PLAYERCLASS_BIOLOGIST)
		return 2;
	if(Class == EInfClass::PLAYERCLASS_LOOPER)
		return 1;
	return 0;
}

/* Sugarcane */
namespace AIRandom
{
	float random_float(float Min, float Max)
	{
		std::uniform_real_distribution<float> Distribution(Min, Max);
		return Distribution(s_RandomEngine);
	}

	vec2 random_direction()
	{
		return direction(2.0f * pi * random_float(0.0f, 1.0f));
	}
}