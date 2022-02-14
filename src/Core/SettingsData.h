#pragma once
namespace tw
{
    /// <summary>
    /// �û�����
    /// ��������Ϊ����İ�װ����
    /// </summary>
    class SettingsData
    {
    public:
        /// <summary>
        /// ��ȡ�û�����
        /// </summary>
        /// <param name="key">��������</param>
        /// <returns>��ֵ</returns>
        __declspec(dllexport) static const std::string& get(const std::string key);
        /// <summary>
        /// �޸��û�����
        /// </summary>
        /// <param name="key">��������</param>
        /// <param name="val">��ֵ</param>
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
