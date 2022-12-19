/*
 *  Materials.hpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */
#ifndef MATERIALS_HPP_
#define MATERIALS_HPP_

#include <list>
using std::list;

namespace asteroids
{

class Texture;

struct Color
{
    Color() : r(125), g(125), b(125) {};
    float r;
    float g;
    float b;
};

struct TexCoord
{
    float u;
    float v;
};

struct Material
{
    Color       m_ambient;
    Color       m_diffuse;
    Color       m_specular;
    float       m_shininess;
    Texture*    m_texture;
};

struct MaterialFaceList
{
    int         m_matIndex;
    list<int>   m_faces;
};

typedef list<MaterialFaceList*> MaterialFaceLists;

} // namespace asteroids

#endif /* MATERIALS_HPP_ */
