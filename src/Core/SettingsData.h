#pragma once
namespace tw
{
    class SettingsData
    {
    public:
        __declspec(dllexport) static const std::string& get(const std::string key);
        __declspec(dllexport) static void set(const std::string key, const std::string& val);
        ~SettingsData();
    private:
        SettingsData();
        static SettingsData* s_instance;
        static SettingsData& instace();
        std::map<std::string, std::string> m_data;
        bool read();
        bool write();
    };
}
