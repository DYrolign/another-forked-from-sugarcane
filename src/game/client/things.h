#ifndef GAME_CLIENT_THINGS_H
#define GAME_CLIENT_THINGS_H

#include <random>
#include <vector>

#include <base/system.h>
#include <base/vmath.h>


/* InfClassR */
enum EInfClass
{
	PLAYERCLASS_INVALID = -1,
	PLAYERCLASS_RANDOM = 0,
	
	START_HUMANCLASS,
	PLAYERCLASS_MERCENARY,
	PLAYERCLASS_MEDIC,
	PLAYERCLASS_HERO,
	PLAYERCLASS_ENGINEER,
	PLAYERCLASS_SOLDIER,
	PLAYERCLASS_NINJA,
	PLAYERCLASS_SNIPER,
	PLAYERCLASS_SCIENTIST,
	PLAYERCLASS_BIOLOGIST,
	PLAYERCLASS_LOOPER,
	END_HUMANCLASS,
	
	START_INFECTEDCLASS,
	PLAYERCLASS_SMOKER,
	PLAYERCLASS_BOOMER,
	PLAYERCLASS_HUNTER,
	PLAYERCLASS_BAT,
	PLAYERCLASS_GHOST,
	PLAYERCLASS_SPIDER,
	PLAYERCLASS_GHOUL,
	PLAYERCLASS_SLUG,
	PLAYERCLASS_VOODOO,
	PLAYERCLASS_WITCH,
	PLAYERCLASS_UNDEAD,
	END_INFECTEDCLASS,
};

const std::vector<EInfClass> &AllInfClassClasses();

inline const char *GetClassDisplayName(EInfClass PlayerClass);

inline EInfClass GetClass(const char *pClanName);
bool IsInfect(const char *pClanName);
bool IsHuman(const char *pClanName);
// return trust point
int IsDefender(const char *pClanName);


/* Sugarcane */
namespace AIRandom
{
	static std::random_device s_RandomDevice;
	static std::default_random_engine s_RandomEngine(s_RandomDevice());

	float random_float(float Min, float Max);
	vec2 random_direction();
};

namespace AStar
{
	class nodevec2
	{
	public:
		int x;
		int y;

		nodevec2() = default;
		nodevec2(vec2 pos) :
			x(pos.x), y(pos.y)
		{
		}
		nodevec2(int nx, int ny) :
			x(nx), y(ny)
		{
		}

		nodevec2 operator-() const { return nodevec2(-x, -y); }
		nodevec2 operator-(const nodevec2 &vec) const { return nodevec2(x - vec.x, y - vec.y); }
		nodevec2 operator+(const nodevec2 &vec) const { return nodevec2(x + vec.x, y + vec.y); }
		nodevec2 operator*(const int rhs) const { return nodevec2(x * rhs, y * rhs); }
		nodevec2 operator*(const nodevec2 &vec) const { return nodevec2(x * vec.x, y * vec.y); }
		nodevec2 operator/(const int rhs) const { return nodevec2(x / rhs, y / rhs); }
		nodevec2 operator/(const nodevec2 &vec) const { return nodevec2(x / vec.x, y / vec.y); }

		const nodevec2 &operator+=(const nodevec2 &vec)
		{
			x += vec.x;
			y += vec.y;
			return *this;
		}
		const nodevec2 &operator-=(const nodevec2 &vec)
		{
			x -= vec.x;
			y -= vec.y;
			return *this;
		}
		const nodevec2 &operator*=(const int rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}
		const nodevec2 &operator*=(const nodevec2 &vec)
		{
			x *= vec.x;
			y *= vec.y;
			return *this;
		}
		const nodevec2 &operator/=(const int rhs)
		{
			x /= rhs;
			y /= rhs;
			return *this;
		}
		const nodevec2 &operator/=(const nodevec2 &vec)
		{
			x /= vec.x;
			y /= vec.y;
			return *this;
		}

		bool operator==(const nodevec2 &vec) const { return x == vec.x && y == vec.y; } //TODO: do this with an eps instead
		bool operator!=(const nodevec2 &vec) const { return x != vec.x || y != vec.y; }
		bool operator<(const nodevec2 &vec) const { return x < vec.x || (x == vec.x && y < vec.y); }

		int &operator[](const int index) { return index ? y : x; }
		vec2 operator()() { return vec2(x, y); }
	};

	struct SPoint
	{
		nodevec2 m_Pos;
		int m_Final;
		int m_Give = 0;
		int m_Hope;

		SPoint() = default;
		SPoint(vec2 Pos)
		{
			m_Pos = Pos;
		}

		bool operator==(const SPoint& Point)
		{
			return m_Pos == Point.m_Pos;
		}

		void GetHope(const SPoint& Begin, const SPoint& End)
		{
			m_Hope = (absolute(Begin.m_Pos.x - End.m_Pos.x) + absolute(Begin.m_Pos.y - End.m_Pos.y)) * 2;
		}

		inline void GetFinal()
		{
			m_Final = m_Give + m_Hope;
		}
	};

	struct SNode
	{
		SPoint m_Point;
		SNode* m_pParent;
		SNode* m_pWinnerChild;

		SNode(const SPoint& Point)
		{
			m_Point = Point;
			m_pParent = nullptr;
			m_pWinnerChild = nullptr;
		}
	};
}

#endif // GAME_CLIENT_THINGS_H
