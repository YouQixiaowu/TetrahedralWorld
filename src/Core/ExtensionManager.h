#pragma once
namespace tw
{
    /// <summary>
    /// 扩展管理
    /// </summary>
    class ExtensionManager
    {
    public:
        /// <summary>
        /// 加载扩展
        /// </summary>
        /// <param name="name">扩展名</param>
        __declspec(dllexport) static void loadExtension(const std::string& name);
        /// <summary>
        /// 从设置加载扩展
        /// </summary>
        __declspec(dllexport) static void loadExtensionFromSettings();
        /// <summary>
        /// 卸载扩展
        /// </summary>
        /// <param name="name">扩展名称</param>
        __declspec(dllexport) static void unloadExtension(const std::string& name);
        /// <summary>
        /// 卸载全部扩展
        /// </summary>
        __declspec(dllexport) static void unloadAllExtension();
    private:
        ExtensionManager();
        static ExtensionManager* s_instance;
        static ExtensionManager& instance();
        std::map<std::string, HINSTANCE> m_data;
    };
}
