#include "pch.h"
namespace tw
{
    RuntimeData* RuntimeData::s_instance = nullptr;

    const Generic& RuntimeData::get(const std::string& key)
    {
        RuntimeData& data = instance();
        return data.m_data[key];
    }

    void RuntimeData::set(const std::string& key, const Generic& val)
    {
        RuntimeData& data = instance();
        data.m_data[key] = val;
    }

    RuntimeData::RuntimeData()
    {

    }

    RuntimeData& RuntimeData::instance()
    {
        if (s_instance==nullptr)
            s_instance = new RuntimeData;
        return *s_instance;
    }
}