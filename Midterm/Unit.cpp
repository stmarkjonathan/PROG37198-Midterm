#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit()
{
	m_xPos = 0;
	m_yPos = 0;
	m_runSpeed = 0;
	m_scale = 0.0;
	m_animSpeed = 0.0;
}

Unit::~Unit()
{
	delete Unit::Pool;
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
	cout << "RUNSPEED: " << m_runSpeed << endl;
	cout << "ANIM_SPEED: " << m_animSpeed << endl;
	Resource::ToString();
}