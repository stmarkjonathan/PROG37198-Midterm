#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Texture.h"
#include "SpriteAnim.h"
#include "BasicStructs.h"

enum AnimationNames
{
	EN_AN_IDLE = 0,
	EN_AN_RUN,
	EN_AN_TWO_COMBO_ATTACK,
	EN_AN_DEATH,
	EN_AN_HURT,
	EN_AN_JUMP_UP_FALL,
	EN_AN_EDGE_GRAB,
	EN_AN_EDGE_IDLE,
	EN_AN_WALL_SIDE,
	EN_AN_CROUCH,
	EN_AN_DASH,
	EN_AN_DASH_ATTACK,
	EN_AN_SLIDE,
	EN_AN_LADDER_GRAB
};

class SpriteSheet : public Texture
{

public:
	SpriteSheet();
	virtual ~SpriteSheet();

	void Serialize(ostream& _stream) override;
	void Deserialize(istream& _stream) override;
	void ToString() override;

	void SetSize(byte _rows, byte _columns, byte _clipSizeX, byte _clipSizeY);
	void AddAnimation(AnimationNames _name, short _clipStart, short _clipCount, float _clipSpeed);
	Rect Update(AnimationNames _name, float _deltaTime);
	int GetCurrentClip(AnimationNames _name);

	static ObjectPool<SpriteSheet>* Pool;

private:

	byte m_rows;
	byte m_columns;
	byte m_clipSizeX;
	byte m_clipSizeY;
	map<AnimationNames, SpriteAnim*> m_animations;

};

#endif