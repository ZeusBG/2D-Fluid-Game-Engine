#pragma once

#include "engine/object/Component.h"

#include "util/Collections.h"

#include "engine/rendering/Mesh.h"
#include "engine/rendering/IShader.h"

// TODO istoilov : make it read for a file with vertices. Clean up STL
#include <string.h>

class VisualComponent : public Component
{
    ADD_SOLID_CLASS_METADATA(VisualComponent)
public:
    //costructor with mesh file, PS and VS ?
    //forward to Mesh
    VisualComponent();
    inline void SetVertexShader(SharedShaderPtr shader) { m_VertexShader = shader; }
    inline SharedShaderPtr GetVertexShader() const { return m_VertexShader; }

    inline void SetPixelShader(SharedShaderPtr shader) { m_PixelShader = shader; }
    inline SharedShaderPtr GetPixelShader() const { return m_PixelShader; }

    inline void AddVertex(float x, float y);

    //Overrides:
    virtual void Init();

    virtual void Update(float delta);
    virtual const Mesh& GetMesh() { return m_Mesh; }

protected:
    Mesh m_Mesh;
    SharedShaderPtr m_VertexShader = nullptr;
    SharedShaderPtr m_PixelShader = nullptr;
    // TODO Add texture

};

using VisualComponentSP = std::shared_ptr<VisualComponent>;
