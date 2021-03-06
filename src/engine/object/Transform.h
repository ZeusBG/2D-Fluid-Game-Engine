#pragma once
#include "util/math/Vec.h" 
#include "util/math/Mat.h" 

class Transform
{
public:
    Transform();
    ~Transform() {}
    
    inline Vec2 GetTranslate() const { return Vec2(m_GlobalMatrix.mat[0][2], m_GlobalMatrix.mat[1][2]); }
    inline Vec3 GetTranslate3() const { return Vec3(m_GlobalMatrix.mat[0][2], m_GlobalMatrix.mat[1][2], m_GlobalMatrix.mat[2][2]); }

	inline void SetTranslate(const Vec2& translate) { m_GlobalMatrix.mat[0][2] = translate.x; m_GlobalMatrix[1][2] = translate.y; }
	inline void SetTranslate3(const Vec3& translate) { m_GlobalMatrix.mat[0][2] = translate.x; m_GlobalMatrix[1][2] = translate.y; m_GlobalMatrix[2][2] = translate.z; }

    inline void Translate(float x, float y) { m_GlobalMatrix.Translate(x, y, 0); }

    inline void Scale(float c) { m_GlobalMatrix.Scale(c); }
	inline void Scale(float x, float y) { m_GlobalMatrix.Scale(x, y); }
    inline void SetSight(const Vec2& sight) { //m_GlobalMatrix.SetRowI(sight.getRPerp()); m_GlobalMatrix.SetRowJ(sight);
	}

    inline Vec2 GetSight() const { return m_GlobalMatrix.GetRowJ2(); }
    inline Vec3 GetSight3() const { return m_GlobalMatrix.GetRowJ(); }

	inline Vec2 GetScale() const { return Vec2(m_GlobalMatrix[0][0], m_GlobalMatrix[1][1]); }

    const Mat3x3& GetMatrix() const { return m_GlobalMatrix; }
	Mat3x3& GetMatrix() { return m_GlobalMatrix; }
private:
    Mat3x3 m_GlobalMatrix;
};

