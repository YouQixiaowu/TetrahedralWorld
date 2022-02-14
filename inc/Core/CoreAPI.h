#pragma once
#include <string>
#include <map>
namespace tw
{
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
        __declspec(dllexport) static void intend(const std::string& eventName);
        /// <summary>
        /// ������ѭ���������̵߳���һ�Σ�
        /// </summary>
        __declspec(dllexport) static void employ();
    private:
        Supervisor();
        Supervisor(const Supervisor&) = delete;
        void operator=(const Supervisor&) = delete;
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
        __declspec(dllimport) static const std::string& get(const std::string key);
        /// <summary>
        /// �޸��û�����
        /// </summary>
        /// <param name="key">��������</param>
        /// <param name="val">��ֵ</param>
        __declspec(dllimport) static void set(const std::string key, const std::string& val);
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
