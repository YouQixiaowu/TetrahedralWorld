#pragma once
namespace tw
{
    /// <summary>
    /// 用户设置
    /// 生命周期为软件的安装周期
    /// </summary>
    class SettingsData
    {
    public:
        /// <summary>
        /// 读取用户设置
        /// </summary>
        /// <param name="key">设置项名</param>
        /// <returns>项值</returns>
        __declspec(dllexport) static const std::string& get(const std::string key);
        /// <summary>
        /// 修改用户设置
        /// </summary>
        /// <param name="key">设置项名</param>
        /// <param name="val">项值</param>
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
