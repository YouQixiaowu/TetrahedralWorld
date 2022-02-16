#include "pch.h"
namespace tw
{
    SettingsData* SettingsData::s_instance = nullptr;

    const std::vector<std::string>& SettingsData::get(const std::string& key)
    {
        SettingsData& sd = instace();
        return sd.m_data[key];
    }

    void SettingsData::set(const std::string& key, const std::vector<std::string>& val)
    {
        SettingsData& sd = instace();
        sd.m_data[key] = val;
    }

    void SettingsData::synchronizeToFile()
    {
        SettingsData& sd = instace();
        Generic temp = RuntimeData::get("ExePath");
        if (!temp.is<std::string>())
            return;
        std::string path = temp.as<std::string>();
        std::ofstream settingsfile;
        settingsfile.open(path + "\\\\..\\\\" + "settings.txt");
        if (!settingsfile)
            return;
        for (auto iterI : sd.m_data)
        {
            settingsfile << iterI.first;
            for (auto iterII : iterI.second)
                settingsfile << " " << iterII;
            settingsfile << "\n";
        }
        settingsfile << std::endl;
        settingsfile.close();
    }

    void SettingsData::synchronizeFromFile()
    {
        SettingsData& sd = instace();
        Generic temp = RuntimeData::get("ExePath");
        if (!temp.is<std::string>())
            return;
        std::string path = temp.as<std::string>();
        std::ifstream settingsfile;
        settingsfile.open(path + "\\\\..\\\\" + "settings.txt");
        if (!settingsfile)
            return;
        std::string line;
        while (std::getline(settingsfile, line))
        {
            std::stringstream ss(line);
            std::string temp;
            ss >> temp;
            if (temp.empty())
                continue;
            std::vector<std::string>& val = sd.m_data[temp];
            val.clear();
            while (ss >> temp)
            {
                val.push_back(temp);
            }
        }
        return;
    }

    SettingsData::~SettingsData()
    {

    }

    SettingsData::SettingsData()
    {

    }

    SettingsData& SettingsData::instace()
    {
        if (s_instance == nullptr)
            s_instance = new SettingsData;
        return *s_instance;
    }
}