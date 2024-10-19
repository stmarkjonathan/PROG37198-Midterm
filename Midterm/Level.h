#ifndef LEVEL_H
#define LEVEL_H

#include "StandardIncludes.h"
#include "Timing.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "Unit.h"

class Level : public Resource
{
public:
	Level(Color _color);
	virtual ~Level();

	Color getLvlColour() { return Color(m_colour_R, m_colour_G, m_colour_B, m_colour_A); }
	vector<Unit*> GetUnits() { return m_units; }
	vector<Unit*> GetRocks() { return m_rocks; }

	void Clear();
	void CreateWarriors();
	void CreateRocks();
	void RunLevelLogic(Renderer* _r, SpriteSheet* sheet, SpriteSheet* rockSheet, Timing* t);
	void Serialize(ostream& _stream) override;
	void Deserialize(istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

private:

	byte m_colour_R;
	byte m_colour_G;
	byte m_colour_B;
	byte m_colour_A;
	vector<Unit*> m_units;
	vector<Unit*> m_rocks;

};

#endif