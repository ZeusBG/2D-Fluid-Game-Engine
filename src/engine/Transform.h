#pragma once
#include "util/math/Vec.h" 
#include "util/math/Mat.h" 

class Transform
{
public:
    Transform();
    ~Transform() {}
    
    inline Vec2 GetGlobalPosition() const { return Vec2(m_GlobalMatrix.mat[2][0], m_GlobalMatrix.mat[2][1]); }
    inline void Translate(float x, float y) { m_GlobalMatrix.Translate(x, y, 0); }
    inline void SetSight(const Vec2& sight) { m_GlobalMatrix.SetRowI(sight.getRPerp()); m_GlobalMatrix.SetRowJ(sight);}

    const Mat3x3& GetMatrix() const { return m_GlobalMatrix; }
private:
    Mat3x3 m_GlobalMatrix;
};

