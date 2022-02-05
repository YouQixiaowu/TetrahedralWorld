#pragma once
namespace tw
{
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
        __declspec(dllexport) MainProcedure(size_t procedureIndex);
        /// <summary>
        /// 析构反注册
        /// </summary>
        __declspec(dllexport) ~MainProcedure();
        /// <summary>
        /// 流程注册后会执行该函数
        /// </summary>
        virtual void execute() = 0;
    private:
        size_t m_procedureIndex;
    };
}