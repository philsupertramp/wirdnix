#include "../engine/TextureLibrary.h"
#include "Engine.h"
#include "olcPGEX_Graphics3D.h"
#include "../engine/olcPixelGameEngine.h"
#include "Mesh.h"
#include <exception>
#include <string>
// idk, include
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

Mesh::Mesh(std::string const& fileName)
{
    if (!loadFromOBJfile(fileName))
    {
        throw std::runtime_error(std::string(__FUNCTION__) + " could not load file " + fileName);
    }
}

void Mesh::draw()
{
    Engine::instance().DrawMesh(_mesh, olc::GFX3D::RENDERFLAGS::RENDER_FLAT);
}

void Mesh::randomizeColors()
{
    for (auto& t : _mesh.tris)
    {
        t.col = olc::Pixel(rand() % 255, rand() % 255, rand() % 255, 250);
    }
}

bool Mesh::loadFromOBJfile(std::string const& fileName)
{
    std::ifstream fin(fileName);

    if (!fin)
    {
        fin.close();
        return false;
    }
    std::streampos p = fin.tellg();
    std::stringstream ss;
    ss << fin.rdbuf();
    fin.seekg(p);

    std::vector<olc::GFX3D::vec3d> vertices;
    vertices.push_back(olc::GFX3D::vec3d()); // offset as file is 1-indexed

    std::vector<olc::GFX3D::vec2d> verticesTexture;
    verticesTexture.push_back(olc::GFX3D::vec2d()); // offset

    // test
    while(!ss.eof())
    {
        std::string currentLine;
        std::getline(ss, currentLine);
        switch (currentLine[0])
        {
        case '#':
            // comment, ignore line
            break;

        case 'v':
        // line may contain a vertex
        {
            currentLine.erase(0, 1);
            char vertexKind = currentLine[0];
            if (   vertexKind != ' ' // geometric
                && vertexKind != 't' // texture
                && vertexKind != 'n' // normal
                && vertexKind != 'p' // parameter space
                )
            {
                // unrecognized vertex specifier, ignore line
                break;
            }
//            currentLine.erase(0, 1);

            size_t start0 = currentLine.find_first_of(' ');
            size_t end0   = currentLine.find_first_of(' ', start0+1);
            size_t start1 = currentLine.find_first_of(' ', end0);
            size_t end1   = currentLine.find_first_of(' ', start1+1);
            size_t start2 = currentLine.find_first_of(' ', end1);
            size_t end2   = currentLine.find_first_of(' ', start2+1);

            switch (vertexKind)
            {
            case ' ':
                // geometric vertex
            {
                float x = 0, y = 0, z = 0;

                if(start0 != std::string::npos && start0 < currentLine.size())
                try {
                    x = stof(currentLine.substr(start0, end0 - start0));
                } catch (...) { }

                if (start1 != std::string::npos && start1 < currentLine.size())
                try {
                    y = stof(currentLine.substr(start1, end1 - start1));
                }catch (...) { }

                if (start2 != std::string::npos && start2 < currentLine.size())
                try {
                    z = stof(currentLine.substr(start2, end2 - start2));
                }catch (...) { }

                olc::GFX3D::vec3d v(x, y, z);
                vertices.push_back(v);
                break;
            }
            case 't':
                // texture vertex
            {
                float x = 0, y = 0;

                if(start0 != std::string::npos && start0 < currentLine.size())
                try {
                    x = stof(currentLine.substr(start0, end0 - start0));
                } catch (...) { }

                if (start1 != std::string::npos && start1 < currentLine.size())
                try {
                    y = stof(currentLine.substr(start1, end1 - start1));
                }catch (...) { }

                olc::GFX3D::vec2d v(x, y);
                verticesTexture.push_back(v);
                break;
            }
            default: // dont handle anything else
                break;
            }
            break;
        }
        case 'f': // face definition
        {
            currentLine.erase(0, 1);

            size_t start0 = currentLine.find_first_of(' ');
            size_t end0   = currentLine.find_first_of(' ', start0+1);
            size_t start1 = currentLine.find_first_of(' ', end0);
            size_t end1   = currentLine.find_first_of(' ', start1+1);
            size_t start2 = currentLine.find_first_of(' ', end1);
            size_t end2   = currentLine.find_first_of(' ', start2+1);

            int p1 = 0, p2 = 0, p3 = 0;

            if(start0 != std::string::npos && start0 < currentLine.size())
            try {
                p1 = stoi(currentLine.substr(start0, end0 - start0));
            } catch (...) { }

            if (start1 != std::string::npos && start1 < currentLine.size())
            try {
                p2 = stoi(currentLine.substr(start1, end1 - start1));
            }catch (...) { }

            if (start2 != std::string::npos && start2 < currentLine.size())
            try {
                p3 = stoi(currentLine.substr(start2, end2 - start2));
            }catch (...) { }

            olc::GFX3D::triangle t;
            t.p[0] = vertices[p1];
            t.p[1] = vertices[p2];
            t.p[2] = vertices[p3];

            _mesh.tris.push_back(t);
            break;
        }
        default:
            break;
        }
    }

    return true;
}
