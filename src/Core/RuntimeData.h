#pragma once
namespace tw
{
    /// <summary>
    /// 运行时数据，生命周期随进程一致
    /// </summary>
    class RuntimeData
    {
    public:
        /// <summary>
        /// 读取运行时全局数据
        /// </summary>
        /// <param name="key">关键字</param>
        /// <returns>返回值</returns>
        __declspec(dllexport) static const Generic& get(const std::string& key);
        /// <summary>
        /// 设置运行时全局数据
        /// </summary>
        /// <param name="key">关键字</param>
        /// <param name="val">值</param>
        __declspec(dllexport) static void set(const std::string& key, const Generic& val);
    private:
        RuntimeData();
        static RuntimeData* s_instance;
        static RuntimeData& instance();
        std::map<std::string, Generic> m_data;
    };
}
