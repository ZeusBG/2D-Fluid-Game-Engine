#pragma once

#include "engine/object/Component.h"

#include "util/Collections.h"
#include "util/Math.h"

#include "engine/rendering/Mesh.h"
#include "engine/rendering/IShader.h"

// TODO istoilov : make it read for a file with vertices. Clean up STL
#include <string.h>

class VisualComponent : public Component
{
public:
    //costructor with mesh file, PS and VS ?
    //forward to Mesh
    //inline void SetVertexShader(const string& vs) { m_VertexShader = vs; }
    //inline string GetVertexShader() const { return m_VertexShader; }

    inline void SetPixelShader(SharedShaderPtr shader) { m_PixelShader = shader; }
    inline SharedShaderPtr GetPixelShader() const { return m_PixelShader; }

    //inline AVector<float>& GetVertices() { return m_Vertices; }
    //inline float* GetRawData() { return m_Vertices.data(); }
    inline void AddVertex(float x, float y);
    
    //Overrides:
    virtual void Init();

    virtual void Update(float delta);

private:
    Mesh m_Mesh;
    SharedShaderPtr m_VertexShader;
    SharedShaderPtr m_PixelShader;
    // TODO Add texture

};