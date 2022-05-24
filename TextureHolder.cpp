#include "TextureHolder.h"

#include <assert.h>

//class is set up so the texture can only be loaded into the GPU once

//sets pointer to null
TextureHolder* TextureHolder::m_s_Instance = nullptr;
//constructor built so we have a pointer to a TextureHolder that points to the only instance of itself
TextureHolder::TextureHolder()
{
	//asserts stops game from executing is m_s_instance is not null
	assert(m_s_Instance == nullptr);
	//m_s_instance is assigned to this instance
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename)
{
	//ref to m_textures using m_s_instance, auto is equiv of map<string, texture>
	auto& m = m_s_Instance->m_textures;

	//iterator to hold key-value-pair(kvp) and search for it using the passed in name
	//auto is equive of map<string, texture>::iterator
	auto keyValuePair = m.find(filename);
	//looks for match
	if (keyValuePair != m.end())
	{
		//if found returns second value, the texture
		return keyValuePair->second;
	}
	else
	{
		//if not found, crates a new kvp using the filename
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}