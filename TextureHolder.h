#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>
//class is set up so the texture can only be loaded into the GPU once
using namespace sf;
using namespace std;

class TextureHolder
{
private:
	//map to hold pairs of strings and textures
	map <string, Texture> m_textures;
	//pointer of the same type as the class and the only instance
	static TextureHolder* m_s_Instance;
public:
	TextureHolder();
	static Texture& GetTexture(string const& filename);
};
#endif // !TEXTURE_HOLDER_H

