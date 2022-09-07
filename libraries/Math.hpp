#pragma once
#include <math.h>
#include <iostream>

namespace Core
{
    namespace myMath
    {
        const float mPI = 3.141592653589793;

        inline double sqrt(double x)
        {
            if (x == 0)
                return 0;
            double result = x / 4;
            for (int i = 0; i < 8; i++)
            {
                result = (result + x / result) / 2;
            }
            return result;
        }

        template <typename T>
        inline T Lerp(T a, T b, float t)
        {
            return a * (1 - t) + b * t;
        }


        inline float pow(float x, int p)
        {
            float result = 1;
            for (int i = 0; i < p; i++)
            {
                result *= x;
            }
            return result;
        }

        inline float Clamp(float value, float min, float max)
        {
            if (value < min)
                return min;
            if (value > max)
                return max;
            return value;
        }

        inline float SmootherStep(float x)
        {
            return x * x * x * (x * (x * 6 - 15) + 10);
        }

        template <typename T>
        inline T Min(const T & a, const T & b)
        {
            return a < b ? a : b;
        }

        template <typename T>
        inline T Max(const T & a, const T & b)
        {
            return a > b ? a : b;
        }

        template <typename T>
        inline T Abs(const T & a)
        {
            return a < 0 ? -a : a;
        }

        class Vec2
        {
        public:
            float x;
            float y;




            Vec2(float _x = 0, float _y = 0)
            {
                x = _x;
                y = _y;
            }

            ~Vec2() {};

            float GetNorm()
            {
                return sqrtf((x * x) + (y * y));
            }

            inline Vec2 operator+(const Vec2& b) const
            {
                return Vec2(this->x + b.x, this->y + b.y);
            }

            inline Vec2 operator+=(const Vec2& b)
            {
                *this = *this + b;
                return *this;
            }

            inline Vec2 operator-(const Vec2& b) const
            {
                return Vec2(this->x - b.x, this->y - b.y);
            }

            inline Vec2 operator-=(const Vec2& b)
            {
                *this = *this - b;
                return *this;
            }

            inline Vec2 operator*(const float b) const
            {
                return Vec2(x * b, y * b);
            }

            inline Vec2 operator*=(const float b)
            {
                *this = *this * b;
                return *this;
            }

            inline Vec2 operator/(const float b) const
            {
                return Vec2(this->x / b, this->y / b);
            }

            inline float operator*(const Vec2& b) const
            {
                return (float)(this->x * b.x + this->y * b.y);
            }

            friend std::ostream& operator<<(std::ostream& stream, const Vec2& a)
            {
                return stream << "(" << a.x << ", " << a.y << ")";
            }

            inline Vec2 Normalized()
            {
                return Vec2(x / GetNorm(), y / GetNorm());
            }

            inline float operator^(const Vec2& b) const
            {
                return this->x * b.y - this->y * b.x;
            }

            inline bool operator==(const Vec2& b) const
            {
                return (this->x == b.x && this->y == b.y);
            }

            inline bool operator!=(const Vec2& b) const
            {
                return (this->x != b.x && this->y != b.y);
            }

            inline Vec2 Rotate(const Vec2& origin, const float angle) const
            {
                Vec2 op = *this - origin;
                Vec2 opP;
                opP.x = cos(angle) * op.x - sin(angle) * op.y;
                opP.y = sin(angle) * op.x + cos(angle) * op.y;
                return opP + origin;
            }

            inline Vec2 Projection(const Vec2& b, const Vec2& c) const
            {
                Vec2 axis = c - b;
                Vec2 point = *this - b;

                return axis * ((point * axis) / (axis * axis)) + b;
            }

            inline float EdgeFunction(const Vec2& a, const Vec2& b) const
            {
                return (b - a) ^ (*this - a);
            }

            inline Vec2 Abs() const
            {
                return { abs(x), abs(y) };
            }
        };

        inline float Distance(const Vec2 & a, const Vec2 & b)
        {
            return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
        }

        inline float BiLerp(const Vec2 & t, const float Q00, const float Q01, const float Q10, const float Q11)
        {
            float a = Lerp(Q00, Q10, t.x);
            float b = Lerp(Q01, Q11, t.x);
            return Lerp(a, b, t.y);
        }

        inline int floor(const int value, const int i)
        {
            return value - (value % i);
        }

        

        class Vec3
        {
        public:
            float x;
            float y;
            float z;

            Vec3(float _x = 0, float _y = 0, float _z = 0)
            {
                x = _x;
                y = _y;
                z = _z;
            }

            Vec3(Vec2 v, float _z)
            {
                x = v.x;
                y = v.y;
                z = _z;
            }

            
           

            ~Vec3() {};

            float GetNorm() const
            {
                return sqrtf((x * x) + (y * y) + (z * z));
            }

            inline Vec3 operator+(const Vec3& b) const
            {
                return Vec3(this->x + b.x, this->y + b.y, z + b.z);
            }

            inline Vec3 operator+=(const Vec3& b)
            {
                *this = *this + b;
                return *this;
            }

            inline Vec3 operator-(const Vec3& b) const
            {
                return Vec3(this->x - b.x, this->y - b.y, z - b.z);
            }

            inline Vec3 operator-() const
            {
                return Vec3(-x, -y, -z);
            }

            inline Vec3 operator-=(const Vec3& b)
            {
                *this = *this - b;
                return *this;
            }

            inline Vec3 operator*(const float b) const
            {
                
                return Vec3(x * b, y * b, z * b);
            }

            inline Vec3 operator*=(const float b)
            {
                *this = *this * b;
                return *this;
            }

            inline Vec3 operator/(const float b) const
            {
                return Vec3(this->x / b, this->y / b, z / b);
            }

            inline float operator*(const Vec3& b) const
            {
                return (float)(this->x * b.x + this->y * b.y + z * b.z);
            }

            friend std::ostream& operator<<(std::ostream& stream, const Vec3& a)
            {
                return stream << "(" << a.x << ", " << a.y << ", " << a.z << ")";
            }

            inline Vec3 Normalized() const
            {
                if (GetNorm() == 0) return Vec3(0, 0, 0);
                return Vec3(x / GetNorm(), y / GetNorm(), z / GetNorm());
            }

            inline Vec3 operator^(const Vec3& b) const
            {
                return Vec3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
            }

            inline bool operator==(const Vec3& b) const
            {
                return (this->x == b.x && this->y == b.y && z == b.z);
            }

            inline bool operator!=(const Vec3& b) const
            {
                return (this->x != b.x || this->y != b.y || z != b.z);
            }

            inline Vec3 Abs()
            {
                return { abs(x), abs(y), abs(z) };
            }

            inline Vec2 toVec2() const
            {
                return Vec2{ x, y };
            }
        };
        inline Vec3 GetSphericalCoords(float r, float theta, float phi)
        {
            return { r * sinf(theta) * cosf(phi),
                    r * cosf(theta),
                    r * sinf(theta) * sinf(phi) };
        }

        inline float Distance(const Vec3& a, const Vec3& b)
        {
            return (b - a).GetNorm();
        }

        class Vec4
        {
        public:
            float x;
            float y;
            float z;
            float w;

            Vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 0)
            {
                x = _x;
                y = _y;
                z = _z;
                w = _w;
            }

            inline Vec4 Homogenize()
            {
                x /= w;
                y /= w;
                z /= w;
                w = 1;
                return *this;
            }

            inline float GetMagnitude() const
            {
                Vec4 a = *this;
                a.Homogenize();
                return a.GetNorm();
            }

            Vec4(Vec3 v, float _w)
            {
                x = v.x;
                y = v.y;
                z = v.z;
                w = _w;
            }

            Vec3 toVec3() const
            {
                return Vec3(x, y, z);
            }

            float GetNorm() const
            {
                return sqrt((x * x) + (y * y) + (z * z) + (w * w));
            }

            inline Vec4 operator+(const Vec4& b) const
            {
                return Vec4(this->x + b.x, this->y + b.y, z + b.z, w);
            }

            inline Vec4 operator+=(const Vec4& b)
            {
                *this = *this + b;
                return *this;
            }

            inline Vec4 operator-(const Vec4& b) const
            {
                return Vec4(x - b.x, y - b.y, z - b.z, w);
            }

            inline Vec4 operator-=(const Vec4& b)
            {
                *this = *this - b;
                return *this;
            }

            inline Vec4 operator*(const float b) const
            {
                return Vec4(x * b, y * b, z * b, w);
            }

            inline Vec4 operator*=(const float b)
            {
                *this = *this * b;
                return *this;
            }

            inline Vec4 operator/(const float b) const
            {
                return Vec4(x / b, y / b, z / b, w);
            }

            inline float operator*(const Vec4& b) const
            {
                return (float)(x * b.x + y * b.y + z * b.z);
            }

            friend std::ostream& operator<<(std::ostream& stream, const Vec4& a)
            {
                return stream << "(" << a.x << ", " << a.y << ", " << a.z << ", " << a.w << ")";
            }

            inline Vec4 Normalized()
            {
                return Vec4(x / GetNorm(), y / GetNorm(), z / GetNorm(), w / GetNorm());
            }

            inline bool operator==(const Vec4& b) const
            {
                return (x == b.x && y == b.y && z == b.z && w == b.w);
            }

            inline bool operator!=(const Vec4& b) const
            {
                return (x != b.x || y != b.y || z != b.z || w != b.w);
            }

            inline Vec3 toVec3()
            {
                return Vec3{ x, y, z };
            }
        };

        class mat4x4
        {
        public:
            float value[4][4];

            mat4x4(float* _value)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        value[i][j] = _value[i * 4 + j];
                    }
                }
            }

            mat4x4()
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        value[i][j] = 0;
                    }
                }
            }

            static mat4x4 Diagonal(const float& f = 1)
            {
                mat4x4 result;

                result.value[0][0] = f;
                result.value[1][1] = f;
                result.value[2][2] = f;
                result.value[3][3] = f;

                return result;
            }

            static mat4x4 Diagonal(const Vec4& v)
            {
                mat4x4 result;

                result.value[0][0] = v.x;
                result.value[1][1] = v.y;
                result.value[2][2] = v.z;
                result.value[3][3] = v.w;

                return result;
            }

            static mat4x4 Translation(const Vec3& v)
            {
                mat4x4 result;

                result.value[0][0] = 1;
                result.value[1][1] = 1;
                result.value[2][2] = 1;
                result.value[3][3] = 1;

                result.value[0][3] = v.x;
                result.value[1][3] = v.y;
                result.value[2][3] = v.z;

                return result;
            }

            static mat4x4 AdjugateMatrix4(mat4x4 m)
            {
                mat4x4 res;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        mat4x4 copy = m;
                        for (int y = 0; y < 4; y++)
                        {
                            for (int x = 0; x < 4; x++)
                            {
                                if (x == j && y == i)
                                {
                                    copy.value[y][x] = 1;
                                }
                                else if (x == j || y == i)
                                {
                                    copy.value[y][x] = 0;
                                }
                            }
                        }
                        res.value[i][j] = copy.GetDeterminant();
                    }
                }
                return res;
            }
            static mat4x4 Inverse(mat4x4 m)
            {
                mat4x4 copy = m;
                float determinant = copy.GetDeterminant();
                copy = AdjugateMatrix4(copy);
                copy.Transpose();
                if (determinant == 0)
                {
                    mat4x4 null;
                    return null;
                }
                return copy *(1/ determinant);
            }

            

            static mat4x4 Rotation(const Vec3& v)
            {
                Vec3 radv = v * (mPI / 180.f);
                float matX[16] = { 1, 0, 0, 0,
                                  0, cosf(radv.x), -sinf(radv.x), 0,
                                  0, sinf(radv.x), cosf(radv.x), 0,
                                  0, 0, 0, 1 };

                float matY[16] = { cosf(radv.y), 0, sinf(radv.y), 0,
                                  0, 1, 0, 0,
                                  -sinf(radv.y), 0, cosf(radv.y), 0,
                                  0, 0, 0, 1 };

                float matZ[16] = { cosf(radv.z), -sinf(radv.z), 0, 0,
                                  sinf(radv.z), cosf(radv.z), 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1 };


                return mat4x4{ matX } * mat4x4{ matY } * mat4x4{ matZ };
            }

            static mat4x4 Scale(const Vec3& v)
            {
                mat4x4 result;
                result.value[0][0] = v.x;
                result.value[1][1] = v.y;
                result.value[2][2] = v.z;
                result.value[3][3] = 1;
                return result;
            }

            static mat4x4 LookAt(const Vec3& pos, const Vec3& point, const Vec3& up)
            {
                // May be optimized eventually.

                Vec3 Up = up / up.GetNorm();
                Vec3 F = (pos - point).Normalized();
                Vec3 L = (Up ^ F).Normalized();
                Vec3 U = (F ^ L).Normalized();
                Vec3 T = { -(L * pos), -(U * pos), -(F * pos) };

                float matRot[16] = { L.x, L.y, L.z, T.x,
                                    U.x, U.y, U.z, T.y,
                                    F.x, F.y, F.z, T.z,
                                    0, 0, 0, 1 };

                return mat4x4{ matRot };
            }

            static mat4x4 ViewFPS(const Vec3& pos, const float pitch, const float yaw)
            {
                float p = pitch * mPI / 180.f;
                float y = yaw * mPI / 180.f;
                float cosPitch = cos(p);     
                float sinPitch = sin(p);
                float cosYaw = cos(y);
                float sinYaw = sin(y);

                Vec3 xaxis = { cosYaw, 0, -sinYaw };
                Vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
                Vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };


                float view[16] = {
                    xaxis.x, xaxis.y, xaxis.z, -(xaxis * pos),
                    yaxis.x, yaxis.y, yaxis.z, -(yaxis * pos),
                    zaxis.x, zaxis.y, zaxis.z, -(zaxis * pos),
                    0, 0, 0, 1 };

                return mat4x4{ view };
            }

            static mat4x4 Perspective(const float fov, const float near, const float far, const float hvRatio)
            {
                float S = 1 / tanf(fov * myMath::mPI / 360);
                float result[16] = { S * hvRatio, 0, 0, 0,
                                    0, S, 0, 0,
                                    0, 0, (far / (far - near)), -((far * near) / (far - near)),
                                    0, 0, 1, 0 };
                return mat4x4{ result };
            }

            friend std::ostream& operator<<(std::ostream& stream, const mat4x4& a)
            {
                return stream << "{" << a.value[0][0] << ", " << a.value[0][1] << ", " << a.value[0][2] << ", " << a.value[0][3] << "}, " << std::endl
                    << "{" << a.value[1][0] << ", " << a.value[1][1] << ", " << a.value[1][2] << ", " << a.value[1][3] << "}, " << std::endl
                    << "{" << a.value[2][0] << ", " << a.value[2][1] << ", " << a.value[2][2] << ", " << a.value[2][3] << "}, " << std::endl
                    << "{" << a.value[3][0] << ", " << a.value[3][1] << ", " << a.value[3][2] << ", " << a.value[3][3] << "}";
            }

            inline void Transpose()
            {
                mat4x4 tmp;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        tmp.value[i][j] = value[j][i];
                    }
                }
                *this = tmp;
            }

            inline mat4x4 operator*(float f) const
            {
                float res[16] = {
                    value[0][0] * f, value[0][1] * f, value[0][2] * f, value[0][3] * f,
                        value[1][0] * f, value[1][1] * f, value[1][2] * f, value[1][3] * f,
                        value[2][0] * f, value[2][1] * f, value[2][2] * f, value[2][3] * f,
                        value[3][0] * f, value[3][1] * f, value[3][2] * f, value[3][3] * f };

                return mat4x4(res);
                
            }

            inline Vec4 operator*(const Vec4& b) const
            {
                return Vec4 {
                    value[0][0] * b.x + value[0][1] * b.y + value[0][2] * b.z + value[0][3] * b.w,
                        value[1][0] * b.x + value[1][1] * b.y + value[1][2] * b.z + value[1][3] * b.w,
                        value[2][0] * b.x + value[2][1] * b.y + value[2][2] * b.z + value[2][3] * b.w,
                        value[3][0] * b.x + value[3][1] * b.y + value[3][2] * b.z + value[3][3] * b.w,
                };
            }

            inline mat4x4 operator*(const mat4x4& b) const
            {
                mat4x4 result;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        result.value[i][j] = value[0][j] * b.value[i][0] + value[1][j] * b.value[i][1] + value[2][j] * b.value[i][2] + value[3][j] * b.value[i][3];
                    }
                }
                return mat4x4{ result };
            }

            inline float GetDeterminant() const
            {
                return value[0][0] * (value[1][1] * value[2][2] * value[3][3] - value[1][1] * value[2][3] * value[3][2] -
                    value[1][2] * value[2][1] * value[3][3] + value[1][2] * value[2][3] * value[3][1] +
                    value[1][3] * value[2][1] * value[3][2] - value[1][3] * value[2][2] * value[3][1]) -
                    value[0][1] * (value[1][0] * value[2][2] * value[3][3] - value[1][0] * value[2][3] * value[3][2] -
                        value[1][2] * value[2][0] * value[3][3] + value[1][2] * value[2][3] * value[3][0] +
                        value[1][3] * value[2][0] * value[3][2] - value[1][3] * value[2][2] * value[3][0]) +
                    value[0][2] * (value[1][0] * value[2][1] * value[3][3] - value[1][0] * value[2][3] * value[3][1] -
                        value[1][1] * value[2][0] * value[3][3] + value[1][1] * value[2][3] * value[3][0] +
                        value[1][3] * value[2][0] * value[3][1] - value[1][3] * value[2][1] * value[3][0]) -
                    value[0][3] * (value[1][0] * value[2][1] * value[3][2] - value[1][0] * value[2][2] * value[3][1] -
                        value[1][1] * value[2][0] * value[3][2] + value[1][1] * value[2][2] * value[3][0] +
                        value[1][2] * value[2][0] * value[3][1] - value[1][2] * value[2][1] * value[3][0]);
            }
        };
    }

    /*namespace collision
    {

        class Box
        {
        public:
            myMath::Vec2 min;
            myMath::Vec2 max;

            Box() {};

            Box(myMath::Vec2 _min, myMath::Vec2 _max)
            {
                min = _min;
                max = _max;
            }

            Box(float x, float y, int width, int height)
            {
                min = (myMath::Vec2)(x, y);
                max = (myMath::Vec2)(x + width, y + height);
            }

            inline Box operator+(const myMath::Vec2& b)
            {
                return Box { min + b, max + b };
            }

            inline Box Truncate(const collision::Box& b)
            {
                this->min.x = myMath::Max(b.min.x, this->min.x);
                this->max.x = myMath::Min(b.max.x, this->max.x);
                this->min.y = myMath::Max(b.min.y, this->min.y);
                this->max.y = myMath::Min(b.max.y, this->max.y);

                return *this;
            }
        };

        inline bool Collision(const Box& box, const myMath::Vec2& point)
        {
            return (point.x > box.min.x && point.x < box.max.x&&
                point.y > box.min.y && point.y < box.max.y);
        }

        inline bool Collision(const myMath::Vec2& c1, const float r1, const myMath::Vec2& c2, const float r2)
        {
            return (Distance(c1, c2) <= r1 + r2);
        }

        inline float Max3(float x, float y, float z)
        {
            float res = x;
            if (y > res)
                res = y;
            if (z > res)
                res = z;
            return res;
        }

        inline float Min3(float x, float y, float z)
        {
            float res = x;
            if (y < res)
                res = y;
            if (z < res)
                res = z;
            return res;
        }

        inline Box GetAABB(const myMath::Vec3& p0, const myMath::Vec3& p1, const myMath::Vec3& p2)
        {
            float resMinX = Min3(p0.x, p1.x, p2.x);
            float resMaxX = Max3(p0.x, p1.x, p2.x);
            float resMinY = Min3(p0.y, p1.y, p2.y);
            float resMaxY = Max3(p0.y, p1.y, p2.y);

            return Box { myMath::Vec2 { resMinX, resMinY }, myMath::Vec2 { resMaxX, resMaxY } };
        }
    }*/

    template <typename T>
    inline void Swap(T& a, T& b)
    {
        T buffer = b;
        b = a;
        a = buffer;
    }

}

