#include "pch.h"
namespace tw
{
    SettingsData* SettingsData::s_instance = nullptr;

    //void read_()
    //{
    //    std::ifstream infile("1.txt");
    //    std::string line;
    //    if (!infile) // 有该文件
    //    {
    //        std::cout << "no such file" << std::endl;
    //        return;
    //    }
    //    while (std::getline(infile, line))
    //    {
    //        std::cout << line << std::endl;
    //    }
    //}

    const std::string& SettingsData::get(const std::string key)
    {
        SettingsData& sd = instace();
        return sd.m_data[key];
    }

    void SettingsData::set(const std::string key, const std::string& val)
    {
        SettingsData& sd = instace();
        if (sd.write())
            return;
        Log::print("");
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

    bool SettingsData::read()
    {
        return true;
    }

    bool SettingsData::write()
    {
        std::ofstream outfile;
        outfile.open("settings.txt");
        if (!outfile)
            return false;
        outfile << "Hi" << std::endl;
        outfile.close();
    }
}