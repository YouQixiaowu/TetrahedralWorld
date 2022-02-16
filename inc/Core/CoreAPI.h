#pragma once
#include <string>
#include <map>
#include <vector>
namespace tw
{
    /// <summary>
    /// ���ʹ���
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
    /// ���߳�����
    /// </summary>
    class MainProcedure
    {
    public:
        /// <summary>
        /// ����ע��
        /// </summary>
        /// <param name="procedureIndex">����λ�ú�</param>
        __declspec(dllimport) MainProcedure(size_t procedureIndex);
        /// <summary>
        /// ������ע��
        /// </summary>
        __declspec(dllimport) ~MainProcedure();
        /// <summary>
        /// ����ע����ִ�иú���
        /// </summary>
        virtual void execute() = 0;
    private:
        size_t m_procedureIndex;
    };

    /// <summary>
    /// �����¼�
    /// </summary>
    class NamedEvent
    {
    public:
        /// <summary>
        /// ����ע��
        /// </summary>
        /// <param name="eventName">�¼�����</param>
        __declspec(dllimport) NamedEvent(const std::string& eventName, bool needMain);
        /// <summary>
        /// ������ע��
        /// </summary>
        __declspec(dllimport) ~NamedEvent();
        /// <summary>
        /// �¼�������ʱ����ִ�иú�����
        /// </summary>
        virtual void execute() = 0;
        /// <summary>
        /// �Ƿ�Ϊ���߳��¼�
        /// </summary>
        /// <returns>true Ϊ���߳�</returns>
        inline bool isMain()
        {
            return m_isMain;
        }
    private:
        std::string m_eventName;
        bool m_isMain;
    };

    /// <summary>
    /// ����
    /// </summary>
    class Supervisor
    {
    public:
        /// <summary>
        /// ���������¼�������ύ�ɹܼ��߳��첽ִ�С�
        /// </summary>
        /// <param name="eventName">�����¼���</param>
        __declspec(dllimport) static void intend(const std::string& eventName);
        /// <summary>
        /// ������ѭ���������̵߳���һ�Σ�
        /// </summary>
        __declspec(dllimport) static void employ();
    private:
        Supervisor();
    };

    /// <summary>
    /// ��������
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
        __declspec(dllexport) static const std::vector<std::string>& get(const std::string& key);
        /// <summary>
        /// �޸��û�����
        /// </summary>
        /// <param name="key">��������</param>
        /// <param name="val">��ֵ</param>
        __declspec(dllexport) static void set(const std::string& key, const std::vector<std::string>& val);
        /// <summary>
        /// ͬ��������Ϣ�������ļ�
        /// </summary>
        __declspec(dllexport) static void synchronizeToFile();
        /// <summary>
        /// �ӱ����ļ�ͬ��������Ϣ���ڴ�
        /// </summary>
        __declspec(dllexport) static void synchronizeFromFile();
        ~SettingsData();
    private:
        SettingsData();
    };

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
        __declspec(dllimport) static const Generic& get(const std::string& key);
        /// <summary>
        /// ��������ʱȫ������
        /// </summary>
        /// <param name="key">�ؼ���</param>
        /// <param name="val">ֵ</param>
        __declspec(dllimport) static void set(const std::string& key, const Generic& val);
    private:
        RuntimeData();
    };

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
        __declspec(dllimport) static void loadExtension(const std::string& name);
        /// <summary>
        /// �����ü�����չ
        /// </summary>
        __declspec(dllimport) static void loadExtensionFromSettings();
        /// <summary>
        /// ж����չ
        /// </summary>
        /// <param name="name">��չ����</param>
        __declspec(dllimport) static void unloadExtension(const std::string& name);
        /// <summary>
        /// ж��ȫ����չ
        /// </summary>
        __declspec(dllimport) static void unloadAllExtension();
    private:
        ExtensionManager();
    };
}
