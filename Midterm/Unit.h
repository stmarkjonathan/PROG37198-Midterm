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
	static bool checkCollision(const Rect& a, const Rect& b) {
		return (a.X1 < b.X2 && a.X2 > b.X1 && a.Y1 < b.Y2 && a.Y2 > b.Y1);
	}

	void setXPos(float _xPos) { m_xPos = _xPos; }
	void setYPos(float _yPos) { m_yPos = _yPos; }

	int getXSpeed() { return m_xSpeed; }
	void setXSpeed(int _xSpeed) { m_xSpeed = _xSpeed; }

	int getYSpeed() { return m_ySpeed; }
	void setYSpeed(int _ySpeed) { m_ySpeed = _ySpeed; }

	float getScale() { return m_scale; }
	void setScale(float _scale) { m_scale = _scale; }

	float getAnimSpeed() { return m_animSpeed; }
	void setAnimSpeed(float _animSpeed) { m_animSpeed = _animSpeed; }

	string getGuid() { return m_texture_guid; }
	void setGuid(string _guid) { m_texture_guid = _guid; }
	
	void Move(float _deltaTime);

	virtual void Serialize(ostream& _stream) override;
	virtual void Deserialize(istream& _stream) override;
	virtual void AssignNonDefaultValues() override;
	virtual void ToString() override;

	static ObjectPool<Unit>* Pool;

private:

	string m_texture_guid;
	float m_xPos;
	float m_yPos;
	int m_xSpeed;
	int m_ySpeed;
	float m_scale;
	float m_animSpeed; // linearly based of off m_runSpeed


};

#endif