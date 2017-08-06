#include "engine/object/Transform.h"

Transform::Transform()
{
    m_GlobalMatrix = Mat3x3::Identity();
}