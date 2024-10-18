#ifndef UNIT_H
#define UNIT_H

#include "Resource.h"

class Unit : public Resource
{

	const int BASE_SIZE = 75;

public:
	Unit();
	virtual ~Unit();

	Rect getPos()
	{
		return Rect(m_xPos, m_yPos, (BASE_SIZE * m_scale) + m_xPos, (BASE_SIZE + m_scale) + m_yPos);
	}

	void setXPos(int _xPos) { m_xPos = _xPos; }
	void setYPos(int _yPos) { m_yPos = _yPos; }

	int getRunSpeed() { return m_runSpeed; }
	void setRunSpeed(int _runSpeed) { m_runSpeed = _runSpeed; }
	float getScale() { return m_scale; }
	void setScale(float _scale) { m_scale = _scale; }
	float getAnimSpeed() { return m_animSpeed; }
	void setAnimSpeed(float _animSpeed) { m_animSpeed = _animSpeed; }
	string getGuid() { return m_texture_guid; }
	void setGuid(string _guid) { m_texture_guid = _guid; }
	
	void Move(int xSpeed, int ySpeed);

	virtual void Serialize(ostream& _stream) override;
	virtual void Deserialize(istream& _stream) override;
	virtual void AssignNonDefaultValues() override;
	virtual void ToString() override;

	static ObjectPool<Unit>* Pool;

private:

	string m_texture_guid;
	int m_xPos;
	int m_yPos;
	int m_runSpeed;
	float m_scale;
	float m_animSpeed; // linearly based of off m_runSpeed


};

#endif