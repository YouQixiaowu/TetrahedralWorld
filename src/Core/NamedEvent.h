#pragma once
namespace tw
{
    /// <summary>
    /// 命名事件
    /// </summary>
    class NamedEvent
    {
    public:
        /// <summary>
        /// 构造注册
        /// </summary>
        /// <param name="eventName">事件名称</param>
        __declspec(dllexport) NamedEvent(const std::string& eventName, bool needMain = false);
        /// <summary>
        /// 析构反注册
        /// </summary>
        __declspec(dllexport) ~NamedEvent();
        /// <summary>
        /// 事件被触发时，会执行该函数。
        /// </summary>
        virtual void execute() = 0;
        /// <summary>
        /// 是否为主线程事件
        /// </summary>
        /// <returns>true 为主线程</returns>
        inline bool isMain()
        {
            return m_isMain;
        }
    private:
        std::string m_eventName;
        bool m_isMain;
    };
}
