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

#include <cstring> // for the linux - inclined
#include <iostream> // for output <<-operator
#include <iomanip>

#include <algorithm>
#include <vector>
#include <list>
#undef min
#undef max

namespace olc
{
    // Container class for Advanced 2D Drawing functions
    class GFX3D
        : public olc::PGEX
    {
    public:
        struct vec2d
        {
            float x = 0;
            float y = 0;
            float z = 0;

            //JNL why z == 0? div by 0 should not be a possible idea
            vec2d(float x_ = 0, float y_ = 0, float z_ = 1)
                : x(x_)
                , y(y_)
                , z(z_)
            { }

            friend std::ostream& operator<< (std::ostream& ostr, vec2d const& v)
            {
                return ostr << "(" << v.x << ", " << v.y << ": " << v.z << ")";
            }
        };

        struct vec3d
        {
            float x = 0;
            float y = 0;
            float z = 0;
            float w = 1; // Need a 4th term to perform sensible matrix vector multiplication

            vec3d(float x_ = 0, float y_ = 0, float z_ = 0, float w_ = 1)
                : x(x_)
                , y(y_)
                , z(z_)
                , w(w_)
            { }

            inline vec3d const& normalize()
            {
                float l = (float)length();

                x /= l;
                y /= l;
                z /= l;

                w = 1;

                return *this;
            }

            inline vec3d const& homogenize()
            {
                x /= w;
                y /= w;
                z /= w;
                w = 1;

                return *this;
            }

            float angleTo(vec3d const& other) const
            {
                float cosTheta = (float)(operator* (other) / (this->length() * other.length()));

                return acosf(cosTheta);
            }

            inline float length() const
            {
                return sqrtf(x*x + y*y + z*z);
            }

            inline float operator* (vec3d const& v) const
            {
                return x * v.x + y * v.y + z * v.z;
            }

            inline vec3d operator* (float s) const
            {
                vec3d res = *this;
                return res *= s;
            }

            inline vec3d& operator*= (float s)
            {
                x *= s;
                y *= s;
                z *= s;

                return *this;
            }

            inline vec3d operator/ (float s) const
            {
                vec3d res = *this;
                return res /= s;
            }

            inline vec3d& operator/= (float s)
            {
                x /= s;
                y /= s;
                z /= s;

                return *this;
            }

            inline vec3d operator+ (vec3d const& v) const
            {
                vec3d res = *this;
                return res += v;
            }

            inline vec3d& operator+= (vec3d const& v)
            {
                x += v.x;
                y += v.y;
                z += v.z;

                return *this;
            }

            inline vec3d operator- (vec3d const& v) const
            {
                vec3d res = *this;
                return res -= v;
            }

            inline vec3d& operator-= (vec3d const& v)
            {
                x -= v.x;
                y -= v.y;
                z -= v.z;

                return *this;
            }

            // cross product time!
            inline vec3d operator& (vec3d const& v) const
            {
                vec3d res;

                res.x = y*v.z - z*v.y;
                res.y = z*v.x - x*v.z;
                res.z = x*v.y - y*v.x;

                return res;
            }

            friend std::ostream& operator<< (std::ostream& ostr, vec3d const& v)
            {
                std::streamsize width = ostr.precision();
                auto a = ostr.flags();
                ostr.setf(ostr.showpos);
                ostr << std::setprecision(4) << std::fixed;
                ostr << "(" << std::setprecision(4) << v.x << ", " << v.y << ", " << v.z << ": " << v.w << " l:" << v.length() << ")";
                ostr << std::setprecision(width);
                ostr.flags(a);
                return ostr;
            }
        };

        struct triangle
        {
            triangle() {}
            vec3d p[3];
            vec2d t[3];
            olc::Pixel col;
        };

        struct mat4x4
        {
            float m[4][4] = { 0 };

            inline vec3d operator* (vec3d const& v) const
            {
                vec3d res = v;
                mat4x4 t = *this;
                res = Math::Mat_MultiplyVector(t, res);
                return res;
            }

            inline mat4x4 operator* (mat4x4 const& other)
            {
                mat4x4 res;
                for (int c = 0; c < 4; ++c)
                {
                    for (int r = 0; r < 4; ++r)
                    {
                        res.m[r][c] = m[r][0] * other.m[0][c]
                                    + m[r][1] * other.m[1][c]
                                    + m[r][2] * other.m[2][c]
                                    + m[r][3] * other.m[3][c];
                    }
                }
                return res;
            }

            void transpose()
            {
                for (int c = 0; c < 4; ++c)
                {
                    for (int r = c; r < 4; ++r)
                    {
                        std::swap(m[c][r], m[r][c]);
                    }
                }
            }

            friend std::ostream& operator<< (std::ostream& ostr, mat4x4 const& mat)
            {
                std::streamsize width = ostr.precision();
                auto a = ostr.flags();
                ostr.setf(ostr.showpos);
                ostr << std::setprecision(4) << std::fixed;
                ostr << "[" << std::setprecision(4);

                for (int c = 0; c < 4; ++c)
                {
                    ostr << (c == 0 ? "" : " ") << "[";
                    for (int r = 0; r < 4; ++r)
                    {
                        ostr << mat.m[r][c] << " ";
                    }
                    ostr << "]" << (c == 3 ? "" : "\n");
                }

                ostr << "]" << std::setprecision(width);
                ostr.flags(a);
                return ostr;
            }
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
            inline static vec3d Mat_MultiplyVector(mat4x4 const& m, vec3d const& i)
            {
                vec3d v;
                v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
                v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
                v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
                v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
                return v;
            }

            inline static mat4x4 Mat_MultiplyMatrix(mat4x4& m1, mat4x4& m2)
            {
                mat4x4 matrix;
                for (int c = 0; c < 4; c++)
                {
                    for (int r = 0; r < 4; r++)
                    {
                        matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
                    }
                }
                return matrix;
            }

            inline static mat4x4 Mat_MakeIdentity()
            {
                mat4x4 matrix;
                matrix.m[0][0] = 1.0f;
                matrix.m[1][1] = 1.0f;
                matrix.m[2][2] = 1.0f;
                matrix.m[3][3] = 1.0f;
                return matrix;
            }
            inline static mat4x4 Mat_MakeRotationX(float fAngleRad)
            {
                mat4x4 matrix;
                matrix.m[0][0] = 1.0f;
                matrix.m[1][1] = cosf(fAngleRad);
                matrix.m[1][2] = sinf(fAngleRad);
                matrix.m[2][1] = -sinf(fAngleRad);
                matrix.m[2][2] = cosf(fAngleRad);
                matrix.m[3][3] = 1.0f;
                return matrix;
            }
            inline static mat4x4 Mat_MakeRotationY(float fAngleRad)
            {
                mat4x4 matrix;
                matrix.m[0][0] = cosf(fAngleRad);
                matrix.m[0][2] = sinf(fAngleRad);
                matrix.m[2][0] = -sinf(fAngleRad);
                matrix.m[1][1] = 1.0f;
                matrix.m[2][2] = cosf(fAngleRad);
                matrix.m[3][3] = 1.0f;
                return matrix;
            }
            inline static mat4x4 Mat_MakeRotationZ(float fAngleRad)
            {
                mat4x4 matrix;
                matrix.m[0][0] = cosf(fAngleRad);
                matrix.m[0][1] = sinf(fAngleRad);
                matrix.m[1][0] = -sinf(fAngleRad);
                matrix.m[1][1] = cosf(fAngleRad);
                matrix.m[2][2] = 1.0f;
                matrix.m[3][3] = 1.0f;
                return matrix;
            }
            inline static mat4x4 Mat_MakeRotationU(vec3d const& u, float fAngleRad)
            {
                mat4x4 res;

                float sinT = sin(fAngleRad);
                float cosT = cos(fAngleRad);

                res.m[0][0] =    cosT + u.x*u.x * (1 - cosT);     res.m[1][0] = u.x*u.y * (1 - cosT) - u.z * sinT;  res.m[2][0] = u.x*u.z * (1 - cosT) + u.y * sinT;
                res.m[0][1] = u.y*u.x * (1 - cosT) + u.z * sinT;  res.m[1][1] =    cosT + u.y*u.y * (1 - cosT);     res.m[2][1] = u.y*u.z * (1 - cosT) - u.x * sinT; // fucking helps if i can copy the formula correctly
                res.m[0][2] = u.z*u.x * (1 - cosT) - u.y * sinT;  res.m[1][2] = u.z*u.y * (1 - cosT) + u.x * sinT;  res.m[2][2] =   cosT + u.z*u.z * (1 - cosT);
                res.m[3][3] = 1;
                return res;
            }

            inline static mat4x4 Mat_MakeScale(float x, float y, float z);
            inline static mat4x4 Mat_MakeTranslation(float x, float y, float z);
            inline static mat4x4 Mat_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
            inline static mat4x4 Mat_PointAt(vec3d const& pos, vec3d const& target, vec3d const& up);
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
            inline static vec3d Vec_IntersectPlane(vec3d const& plane_p, vec3d& plane_n, vec3d const& lineStart, vec3d const& lineEnd, float& t);

            inline static int Triangle_ClipAgainstPlane(vec3d plane_p, vec3d plane_n, triangle const& in_tri, triangle& out_tri1, triangle& out_tri2);
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
            void SetCamera(olc::GFX3D::vec3d const& pos, olc::GFX3D::vec3d const& lookat, olc::GFX3D::vec3d const& up);
            void SetTransform(olc::GFX3D::mat4x4& transform);
            void SetTexture(olc::Sprite* texture);
            void SetLightSource(olc::GFX3D::vec3d& pos, olc::GFX3D::vec3d& dir, olc::Pixel& col);
            uint32_t Render(std::vector<olc::GFX3D::triangle> const& triangles, uint32_t flags = RENDER_CULL_CW | RENDER_TEXTURED | RENDER_DEPTH);

        private:
            olc::GFX3D::mat4x4 matProj;
            olc::GFX3D::mat4x4 matView;
            olc::GFX3D::mat4x4 matWorld;
            olc::Sprite* sprTexture = nullptr;
            float fViewX;
            float fViewY;
            float fViewW;
            float fViewH;
        };



    public:
        //static const int RF_TEXTURE = 0x00000001;
        //static const int RF_ = 0x00000002;

        inline static void ConfigureDisplay()
        {
            if (m_DepthBuffer != nullptr)
            {
                ClearDepth();
            }
            else
            {
                auto length = pge->ScreenWidth() * pge->ScreenHeight();
                m_DepthBuffer = new float[length] { 0 };
            }
        }

        inline static void ClearDepth()
        {
            memset(m_DepthBuffer, 0, pge->ScreenWidth() * pge->ScreenHeight() * sizeof(float));
        }

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
