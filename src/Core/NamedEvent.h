#pragma once
namespace tw
{
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
        __declspec(dllexport) NamedEvent(const std::string& eventName, bool needMain = false);
        /// <summary>
        /// ������ע��
        /// </summary>
        __declspec(dllexport) ~NamedEvent();
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
}
