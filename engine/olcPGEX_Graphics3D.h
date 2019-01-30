/*
    olcPGEX_Graphics3D.h

    +-------------------------------------------------------------+
    |         OneLoneCoder Pixel Game Engine Extension            |
    |                    3D Rendering - v0.1                      |
    +-------------------------------------------------------------+

    What is this?
    ~~~~~~~~~~~~~
    This is an extension to the olcPixelGameEngine, which provides
    support for software rendering 3D graphics.

    NOTE!!! This file is under development and may change!

    License (OLC-3)
    ~~~~~~~~~~~~~~~

    Copyright 2018-2019 OneLoneCoder.com

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions or derivations of source code must retain the above
    copyright notice, this list of conditions and the following disclaimer.

    2. Redistributions or derivative works in binary form must reproduce
    the above copyright notice. This list of conditions and the following
    disclaimer must be reproduced in the documentation and/or other
    materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Links
    ~~~~~
    YouTube:    https://www.youtube.com/javidx9
    Discord:    https://discord.gg/WhwHUMV
    Twitter:    https://www.twitter.com/javidx9
    Twitch:     https://www.twitch.tv/javidx9
    GitHub:     https://www.github.com/onelonecoder
    Patreon:    https://www.patreon.com/javidx9
    Homepage:   https://www.onelonecoder.com

    Author
    ~~~~~~
    David Barr, aka javidx9, ©OneLoneCoder 2018
*/


#ifndef OLC_PGEX_GFX3D
#define OLC_PGEX_GFX3D

#include "olcPixelGameEngine.h"

#include <algorithm>
#include <vector>
#include <list>
#undef min
#undef max

namespace olc
{
    // Container class for Advanced 2D Drawing functions
    class GFX3D : public olc::PGEX
    {

    public:

        struct vec2d
        {
            float x = 0;
            float y = 0;
            float z = 0;
        };

        struct vec3d
        {
            float x = 0;
            float y = 0;
            float z = 0;
            float w = 1; // Need a 4th term to perform sensible matrix vector multiplication
        };

        struct triangle
        {
            vec3d p[3];
            vec2d t[3];
            olc::Pixel col;
        };

        struct mat4x4
        {
            float m[4][4] = { 0 };
        };

        struct mesh
        {
            std::vector<triangle> tris;
        };

        class Math
        {
        public:
            inline Math();
        public:
            inline static vec3d  Mat_MultiplyVector(mat4x4& m, vec3d& i);
            inline static mat4x4 Mat_MultiplyMatrix(mat4x4& m1, mat4x4& m2);
            inline static mat4x4 Mat_MakeIdentity();
            inline static mat4x4 Mat_MakeRotationX(float fAngleRad);
            inline static mat4x4 Mat_MakeRotationY(float fAngleRad);
            inline static mat4x4 Mat_MakeRotationZ(float fAngleRad);
            inline static mat4x4 Mat_MakeScale(float x, float y, float z);
            inline static mat4x4 Mat_MakeTranslation(float x, float y, float z);
            inline static mat4x4 Mat_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
            inline static mat4x4 Mat_PointAt(vec3d& pos, vec3d& target, vec3d& up);
            inline static mat4x4 Mat_QuickInverse(mat4x4& m); // Only for Rotation/Translation Matrices
            inline static mat4x4 Mat_Inverse(olc::GFX3D::mat4x4& m);

            inline static vec3d Vec_Add(vec3d& v1, vec3d& v2);
            inline static vec3d Vec_Sub(vec3d& v1, vec3d& v2);
            inline static vec3d Vec_Mul(vec3d& v1, float k);
            inline static vec3d Vec_Div(vec3d& v1, float k);
            inline static float Vec_DotProduct(vec3d& v1, vec3d& v2);
            inline static float Vec_Length(vec3d& v);
            inline static vec3d Vec_Normalise(vec3d& v);
            inline static vec3d Vec_CrossProduct(vec3d& v1, vec3d& v2);
            inline static vec3d Vec_IntersectPlane(vec3d& plane_p, vec3d& plane_n, vec3d& lineStart, vec3d& lineEnd, float& t);

            inline static int Triangle_ClipAgainstPlane(vec3d plane_p, vec3d plane_n, triangle& in_tri, triangle& out_tri1, triangle& out_tri2);
        };

        enum RENDERFLAGS
        {
            RENDER_WIRE = 0x01,
            RENDER_FLAT = 0x02,
            RENDER_TEXTURED = 0x04,
            RENDER_CULL_CW = 0x08,
            RENDER_CULL_CCW = 0x10,
            RENDER_DEPTH = 0x20,
        };


        class PipeLine
        {
        public:
            PipeLine();

        public:
            void SetProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar, float fLeft, float fTop, float fWidth, float fHeight);
            void SetCamera(olc::GFX3D::vec3d& pos, olc::GFX3D::vec3d& lookat, olc::GFX3D::vec3d& up);
            void SetTransform(olc::GFX3D::mat4x4& transform);
            void SetTexture(olc::Sprite* texture);
            void SetLightSource(olc::GFX3D::vec3d& pos, olc::GFX3D::vec3d& dir, olc::Pixel& col);
            uint32_t Render(std::vector<olc::GFX3D::triangle>& triangles, uint32_t flags = RENDER_CULL_CW | RENDER_TEXTURED | RENDER_DEPTH);

        private:
            olc::GFX3D::mat4x4 matProj;
            olc::GFX3D::mat4x4 matView;
            olc::GFX3D::mat4x4 matWorld;
            olc::Sprite* sprTexture;
            float fViewX;
            float fViewY;
            float fViewW;
            float fViewH;
        };



    public:
        //static const int RF_TEXTURE = 0x00000001;
        //static const int RF_ = 0x00000002;

        inline static void ConfigureDisplay();
        inline static void ClearDepth();
        inline static void AddTriangleToScene(olc::GFX3D::triangle& tri);
        inline static void RenderScene();

        inline static void DrawTriangleFlat(olc::GFX3D::triangle& tri);
        inline static void DrawTriangleWire(olc::GFX3D::triangle& tri, olc::Pixel col = olc::WHITE);
        inline static void DrawTriangleTex(olc::GFX3D::triangle& tri, olc::Sprite* spr);
        inline static void TexturedTriangle(int x1, int y1, float u1, float v1, float w1,
            int x2, int y2, float u2, float v2, float w2,
            int x3, int y3, float u3, float v3, float w3, olc::Sprite* spr);

        // Draws a sprite with the transform applied
        //inline static void DrawSprite(olc::Sprite* sprite, olc::GFX2D::Transform2D& transform);

    private:
        static float* m_DepthBuffer;
    };
}

#endif
