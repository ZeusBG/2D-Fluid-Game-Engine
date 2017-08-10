#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include "engine/logging/Logging.h"
typedef  std::function<std::shared_ptr<void>()> factoryFunc;

class MetaData
{
private:
    std::string m_Name;
    factoryFunc m_FactoryFunc;
public:
    MetaData(){}

    MetaData(const std::string& name, factoryFunc f):
        m_Name(name),
        m_FactoryFunc(f)
    {
        LOG_L1(METADATA, INFO, "Metadata for class %s created!", name.c_str());
    }

    inline const std::string& GetName() const { return m_Name; }
    inline const factoryFunc& GetFactoryFunc() const { return m_FactoryFunc; }

    std::shared_ptr<void> CreateInstance() const
    {
        return m_FactoryFunc();
    }
};

class MetaDataStorage
{
private:
    static std::unique_ptr<MetaDataStorage> s_Instance;
    std::unordered_map<std::string, const MetaData*> m_StringMap;
public:
    const MetaData* Get(const std::string& str);
    void Register(const MetaData*);
    static MetaDataStorage* GetInstance()
    {
        if (s_Instance == nullptr)
        {
            s_Instance.reset(new MetaDataStorage());
        }
        return s_Instance.get();
    }
};
template <typename T>
struct MetaDataRegister {
    MetaDataRegister()
    {
        MetaDataStorage::GetInstance()->Register(T::GetMetaData());
    }
};

#define META_DATA_COMMON \
public: \
    static const MetaData* GetMetaData(){ return &s_MetaData; } \
private: \
    const static MetaData s_MetaData;

//#define ADD_ABSTRACT_CLASS_METADATA(CLASS) \
//    META_DATA_COMMON \
//    static CLASS* FactoryFunc() { return nullptr; }

#define ADD_SOLID_CLASS_METADATA(CLASS) \
    META_DATA_COMMON \
    static std::shared_ptr<void> FactoryFunc() { return std::static_pointer_cast<void>(std::make_shared<CLASS>()); } \

#define IMPLEMENT_METADATA(CLASS) \
const MetaData CLASS::s_MetaData = MetaData(std::string(#CLASS), CLASS::FactoryFunc); \
MetaDataRegister<CLASS> autoRegister;

