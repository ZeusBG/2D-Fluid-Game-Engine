#include "engine/Transform.h"

Transform::Transform()
{
    m_GlobalMatrix = Mat3x3::Identity();
}