#pragma once
namespace tw
{
    /// <summary>
    /// ��չ����
    /// </summary>
    class ExtensionManager
    {
    public:
        /// <summary>
        /// ������չ
        /// </summary>
        /// <param name="name">��չ��</param>
        __declspec(dllexport) static void loadExtension(const std::string& name);
        /// <summary>
        /// �����ü�����չ
        /// </summary>
        __declspec(dllexport) static void loadExtensionFromSettings();
        /// <summary>
        /// ж����չ
        /// </summary>
        /// <param name="name">��չ����</param>
        __declspec(dllexport) static void unloadExtension(const std::string& name);
        /// <summary>
        /// ж��ȫ����չ
        /// </summary>
        __declspec(dllexport) static void unloadAllExtension();
    private:
        ExtensionManager();
        static ExtensionManager* s_instance;
        static ExtensionManager& instance();
        std::map<std::string, HINSTANCE> m_data;
    };
}
