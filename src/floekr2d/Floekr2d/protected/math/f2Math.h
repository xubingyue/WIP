#ifndef F2_MATH_H
#define F2_MATH_H

#include <Floekr2d/protected/f2Settings.h>

namespace Floekr2d
{
    namespace math
    {
        // 来自于box2d b2Math
        template <typename T>
        inline T f2Min(T a, T b)
        {
            return a < b ? a : b;
        }

        template <typename T>
        inline T f2Max(T a, T b)
        {
            return a > b ? a : b;
        }

        template <typename T>
        inline T f2Clamp(T a, T low, T high)
        {
            return f2Max(low, b2Min(a, high));
        }

        template<typename T> 
        inline void f2Swap(T& a, T& b)
        {
            T tmp = a;
            a = b;
            b = tmp;
        }

        // --!不使用模板防止传入基本类型以外的参数
        // 比较ab两书是否相等
        inline bool f2Equals(int32 a, int32 b, int32 tolerance = F2_TOLERANCE_INT)
        {
            return (a + tolerance >= b) && (a - tolerance <= b);
        }

        inline bool f2Equals(float32 a, float32 b, float32 tolerance = F2_TOLERANCE_FLOAT32)
        {
            return (a + tolerance >= b) && (a - tolerance <= b);
        }

        inline bool f2Equals(float64 a, float64 b, float64 tolerance = F2_TOLERANCE_FLOAT64)
        {
            return (a + tolerance >= b) && (a - tolerance <= b);
        }
        
        template<class Type>
        inline Type f2Square(Type& a)
        {
            return a * a;
        }

        inline float32 f2Random(float32 low, float32 high)
        {
            float32 a = (float32) rand();
            a /= RAND_MAX;
            a = (high - low) * a + low;
            return a;
        }

        inline bool f2Greater(float32 a, float32 b)
        {
            const float32 k_biasRelative = 0.95f;
            const float32 k_biasAbsolute = 0.01f;
            return a >= b * k_biasRelative + a * k_biasAbsolute;
        }
    }
}

#endif