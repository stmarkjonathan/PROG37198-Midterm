#include "Texture.h"

ObjectPool<Texture>* Texture::Pool = nullptr;

Texture::Texture()
{
	m_imageInfo = { };
	m_texture = nullptr;
}

Texture::~Texture()
{
}

void Texture::Load(string _guid)
{
	TGAReader r = TGAReader();
	m_texture = r.LoadTGAFromFile(_guid, &m_imageInfo);
}

void Texture::Serialize(ostream& _stream)
{
	SerializeAsset(_stream, m_texture);
}

void Texture::Deserialize(istream& _stream)
{
	TGAReader r = TGAReader();
	DeserializeAsset(_stream, m_texture);
	r.ProcessAsset(m_texture, &m_imageInfo);
}

void Texture::ToString()
{
	cout << "TEXTURE" << endl;
	m_texture->ToString();
	Resource::ToString();
}