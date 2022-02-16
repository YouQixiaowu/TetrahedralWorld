#include "pch.h"
namespace tw
{

    ExtensionManager* ExtensionManager::s_instance = nullptr;
    void ExtensionManager::loadExtension(const std::string& name)
    {
        ExtensionManager& inst = instance();
        auto iter = inst.m_data.find(name);
        if (iter != inst.m_data.end())
            return; // 排除重复加载的情况
        HINSTANCE hdll;
        hdll = LoadLibraryA(name.c_str());
        if (hdll == NULL)
        {
            DWORD err = GetLastError();
            Log::print("Failed to load dynamic library" + name + ". Error code is " + std::to_string(err) , tw::Log::LOG_WARNING);
            return;
        }
        inst.m_data[name] = hdll;
    }

    void ExtensionManager::loadExtensionFromSettings()
    {
        ExtensionManager& inst = instance();
        std::vector<std::string> temp = tw::SettingsData::get("LOAD_DLL_LIST");
        for (auto iter : temp)
            loadExtension(iter);
    }

    void ExtensionManager::unloadExtension(const std::string& name)
    {
        ExtensionManager& inst = instance();
        auto iter = inst.m_data.find(name);
        if (iter == inst.m_data.end())
            return;
        if (FreeLibrary(iter->second) == 0)
        {
            DWORD err = GetLastError();
            Log::print("An error occurred while Free the dynamic library. Error code is " + std::to_string(err), tw::Log::LOG_ERROR);
        }
        inst.m_data.erase(iter);
    }

    void ExtensionManager::unloadAllExtension()
    {
        ExtensionManager& inst = instance();
        for (auto iter : inst.m_data)
            unloadExtension(iter.first);
    }

    ExtensionManager::ExtensionManager()
    {
    }

    ExtensionManager& ExtensionManager::instance()
    {
        if (s_instance == nullptr)
            s_instance = new ExtensionManager;
        return *s_instance;
    }

}