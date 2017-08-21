#include "engine/core/MetaData.h"
#include "engine/logging/Logging.h"
#include <assert.h>
#pragma once


std::mutex MetaDataStorage::s_SingletonMutex;

const MetaData* MetaDataStorage::Get(const std::string& str)
{
    auto it = m_StringMap.find(str);
    if (it == m_StringMap.end())
    {
        assert(false && "No metadata for this class");
        return nullptr;
    }
    return it->second;
}

void MetaDataStorage::Register(const MetaData* data)
{
    auto it = m_StringMap.find(data->GetName());
    if (it != m_StringMap.end())
    {
        assert(false && "Class already registered!");
        return;
    }

    m_StringMap.insert(std::pair<std::string, const MetaData*>(data->GetName(), data));
}

//std::shared_ptr<MetaDataStorage> MetaDataStorage::s_Instance;
MetaDataStorage* MetaDataStorage::s_Instance = nullptr;
