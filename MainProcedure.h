#pragma once
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
        __declspec(dllexport) MainProcedure(size_t procedureIndex);
        /// <summary>
        /// ������ע��
        /// </summary>
        __declspec(dllexport) ~MainProcedure();
        /// <summary>
        /// ����ע����ִ�иú���
        /// </summary>
        virtual void execute() = 0;
    private:
        size_t m_procedureIndex;
    };
}