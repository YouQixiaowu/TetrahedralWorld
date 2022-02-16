#pragma once
#include <string>
#include <map>
#include <vector>
namespace tw
{
    /// <summary>
    /// 泛型代理
    /// </summary>
    class Generic
    {
    private:
        class _Base
        {
        public:
            _Base()
            {
            }
            virtual ~_Base()
            {
            }
            virtual _Base* _copy() = 0;
        };
        template<typename T>
        class _Ptr :
            public _Base
        {
        public:
            _Ptr(const T& other) :
                _imp(other)
            {
            }
            ~_Ptr()
            {
            }
            _Base* _copy() override
            {
                return new _Ptr<T>(_imp);
            }
            T _imp;
        };
    public:
        Generic() :
            _ptr(nullptr)
        {
        }
        ~Generic()
        {
            _setPtr(nullptr);
        }
        Generic(const Generic& gnrc) :
            _ptr(gnrc._ptr == nullptr ? nullptr : gnrc._ptr->_copy())
        {
        }
        Generic(Generic&& gnrc) noexcept :
            _ptr(gnrc._ptr)
        {
            gnrc._ptr = nullptr;
        }
        Generic& operator=(const Generic& gnrc)
        {
            _setPtr(gnrc._ptr == nullptr ? nullptr : gnrc._ptr->_copy());
            return *this;
        }
        Generic& operator=(Generic&& gnrc) noexcept
        {
            _setPtr(gnrc._ptr); return *this;
        }
        template<typename T>
        inline Generic(const T& variable) :
            _ptr(new _Ptr<T>(variable))
        {
        }
        template<typename T>
        inline T& as()
        {
            return *dynamic_cast<_Ptr<T>*>(_ptr);
        }
        template<typename T>
        inline const T& as() const
        {
            return *dynamic_cast<_Ptr<T>*>(_ptr);
        }
        template<typename T>
        inline bool is() const
        {
            return dynamic_cast<_Ptr<T>*>(_ptr) != nullptr;
        }
    private:
        inline void _setPtr(_Base* ptr)
        {
            if (_ptr != nullptr) delete _ptr;
            _ptr = ptr;
        }
        _Base* _ptr;
    };

    /// <summary>
    /// 主线程流程
    /// </summary>
    class MainProcedure
    {
    public:
        /// <summary>
        /// 构造注册
        /// </summary>
        /// <param name="procedureIndex">流程位置号</param>
        __declspec(dllimport) MainProcedure(size_t procedureIndex);
        /// <summary>
        /// 析构反注册
        /// </summary>
        __declspec(dllimport) ~MainProcedure();
        /// <summary>
        /// 流程注册后会执行该函数
        /// </summary>
        virtual void execute() = 0;
    private:
        size_t m_procedureIndex;
    };

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
        __declspec(dllimport) NamedEvent(const std::string& eventName, bool needMain);
        /// <summary>
        /// 析构反注册
        /// </summary>
        __declspec(dllimport) ~NamedEvent();
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

    /// <summary>
    /// 主管
    /// </summary>
    class Supervisor
    {
    public:
        /// <summary>
        /// 触发命名事件，命令会交由管家线程异步执行。
        /// </summary>
        /// <param name="eventName">命名事件名</param>
        __declspec(dllimport) static void intend(const std::string& eventName);
        /// <summary>
        /// 进入主循环（由主线程调用一次）
        /// </summary>
        __declspec(dllimport) static void employ();
    private:
        Supervisor();
    };

    /// <summary>
    /// 设置数据
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
        __declspec(dllexport) static const std::vector<std::string>& get(const std::string& key);
        /// <summary>
        /// 修改用户设置
        /// </summary>
        /// <param name="key">设置项名</param>
        /// <param name="val">项值</param>
        __declspec(dllexport) static void set(const std::string& key, const std::vector<std::string>& val);
        /// <summary>
        /// 同步设置信息到本地文件
        /// </summary>
        __declspec(dllexport) static void synchronizeToFile();
        /// <summary>
        /// 从本地文件同步设置信息到内存
        /// </summary>
        __declspec(dllexport) static void synchronizeFromFile();
        ~SettingsData();
    private:
        SettingsData();
    };

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
        __declspec(dllimport) static const Generic& get(const std::string& key);
        /// <summary>
        /// 设置运行时全局数据
        /// </summary>
        /// <param name="key">关键字</param>
        /// <param name="val">值</param>
        __declspec(dllimport) static void set(const std::string& key, const Generic& val);
    private:
        RuntimeData();
    };

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
        __declspec(dllimport) static void loadExtension(const std::string& name);
        /// <summary>
        /// 从设置加载扩展
        /// </summary>
        __declspec(dllimport) static void loadExtensionFromSettings();
        /// <summary>
        /// 卸载扩展
        /// </summary>
        /// <param name="name">扩展名称</param>
        __declspec(dllimport) static void unloadExtension(const std::string& name);
        /// <summary>
        /// 卸载全部扩展
        /// </summary>
        __declspec(dllimport) static void unloadAllExtension();
    private:
        ExtensionManager();
    };
}
