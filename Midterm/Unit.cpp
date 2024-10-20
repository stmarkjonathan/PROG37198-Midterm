#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit()
{
	m_texture_guid = "";
	m_xPos = 0;
	m_yPos = 0;
	m_xSpeed = 0;
	m_ySpeed = 0;
	m_scale = 0.0;
	m_animSpeed = 0.0;
}

Unit::~Unit()
{
	delete Unit::Pool;
}

void Unit::Move(float _deltaTime)
{
	if (m_isAlive) {//only allowign aliv eobjects to move
		m_xPos += m_xSpeed * _deltaTime;
		m_yPos += m_ySpeed * _deltaTime;
	}
	//m_xPos += m_xSpeed * _deltaTime;
	//m_yPos += m_ySpeed * _deltaTime;
}

void Unit::AssignNonDefaultValues()
{

	Resource::AssignNonDefaultValues();
}

void Unit::Serialize(ostream& _stream)
{
	Resource::Serialize(_stream);
}

void Unit::Deserialize(istream& _stream)
{
	Resource::Deserialize(_stream);
}

void Unit::ToString()
{
	cout << "UNIT" << endl;
	cout << "RUNSPEED: " << m_xSpeed << endl;
	cout << "ANIM_SPEED: " << m_animSpeed << endl;
	Resource::ToString();
}