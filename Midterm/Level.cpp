#include "Level.h"

Level::Level(Color _color)
{
	m_colour_R = _color.R;
	m_colour_G = _color.G;
	m_colour_B = _color.B;
	m_colour_A = _color.A;
	Unit::Pool = new ObjectPool<Unit>();
}

Level::~Level()
{
	Clear();
}

void Level::Clear()
{
	m_units.clear();
	delete Unit::Pool;
}

void Level::CreateUnits()
{
	int yOffset = 0;
	for (int count = 0; count < 10; count++)
	{
		Unit* unit = Unit::Pool->GetResource();
		unit->setXPos(0);
		unit->setYPos(10 + yOffset);
		unit->setScale(1.8);
		unit->setRunSpeed(rand() % 21 + 80);
		unit->setAnimSpeed(float((rand() % 13 + 48))/10.0);
		m_units.push_back(unit);
		unit->ToString();
		yOffset += 100;
	}
}

void Level::AssignNonDefaultValues()
{
	for (int count = 0; count < 5; count++)
	{
		Unit* unit = Unit::Pool->GetResource();
		unit->AssignNonDefaultValues();
		m_units.push_back(unit);
	}

	Resource::AssignNonDefaultValues();
}

void Level::Serialize(ostream& _stream)
{


	_stream.write(reinterpret_cast<char*>(&m_colour_R), sizeof(m_colour_R));
	_stream.write(reinterpret_cast<char*>(&m_colour_G), sizeof(m_colour_G));
	_stream.write(reinterpret_cast<char*>(&m_colour_B), sizeof(m_colour_B));
	_stream.write(reinterpret_cast<char*>(&m_colour_A), sizeof(m_colour_A));

	int numberOfUnits = m_units.size();
	_stream.write(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++)
	{
		SerializePointer(_stream, m_units[count]);
	}

	Resource::Serialize(_stream);
}

void Level::Deserialize(istream& _stream)
{

	Clear();

	_stream.read(reinterpret_cast<char*>(&m_colour_R), sizeof(m_colour_R));
	_stream.read(reinterpret_cast<char*>(&m_colour_G), sizeof(m_colour_G));
	_stream.read(reinterpret_cast<char*>(&m_colour_B), sizeof(m_colour_B));
	_stream.read(reinterpret_cast<char*>(&m_colour_A), sizeof(m_colour_A));
	
	int numberOfUnits;
	_stream.read(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++)
	{
		Unit* unit;
		DeserializePointer(_stream, unit);
		m_units.push_back(unit);
	}

	Resource::Deserialize(_stream);
}

void Level::ToString()
{
	cout << "LEVEL" << endl;
	cout << "Colour R: " << m_colour_R << endl;
	cout << "Colour G: " << m_colour_G << endl;
	cout << "Colour B: " << m_colour_B << endl;

	for (int count = 0; count < m_units.size(); count++)
	{
		m_units[count]->ToString();
	}

	Resource::ToString();
}