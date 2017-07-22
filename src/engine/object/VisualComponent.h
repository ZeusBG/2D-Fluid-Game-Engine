#pragma once

#include "Component.h"
#include "../../util/Math.h" 

// TODO istoilov : make it read for a file with vertices. Clean up STL
#include <vector>
#include <string.h>

using namespace std;


class VisualComponent : public Component
{
public:
    inline void SetVertexShader(const string& vs) { m_VertexShader = vs; }
    inline string GetVertexShader() const { return m_VertexShader; }

    inline void SetPixelShader(const string& ps) { m_PixelShader = ps; }
    inline string GetPixelShader() const { return m_PixelShader; }

    inline vector<Vec2>& GetVertices() { return m_Vertices; }
    inline void AddVertex(const Vec2& v) { m_Vertices.push_back(v); }

public:
    //Overrides:
    virtual void Update(float delta) {}

private:
    vector<Vec2> m_Vertices;

    //shader filename;
    string m_VertexShader;

    //shader filename;
    string m_PixelShader;

};