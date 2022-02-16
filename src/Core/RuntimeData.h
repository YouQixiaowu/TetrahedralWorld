#pragma once
namespace tw
{
    /// <summary>
    /// ����ʱ���ݣ��������������һ��
    /// </summary>
    class RuntimeData
    {
    public:
        /// <summary>
        /// ��ȡ����ʱȫ������
        /// </summary>
        /// <param name="key">�ؼ���</param>
        /// <returns>����ֵ</returns>
        __declspec(dllexport) static const Generic& get(const std::string& key);
        /// <summary>
        /// ��������ʱȫ������
        /// </summary>
        /// <param name="key">�ؼ���</param>
        /// <param name="val">ֵ</param>
        __declspec(dllexport) static void set(const std::string& key, const Generic& val);
    private:
        RuntimeData();
        static RuntimeData* s_instance;
        static RuntimeData& instance();
        std::map<std::string, Generic> m_data;
    };
}
