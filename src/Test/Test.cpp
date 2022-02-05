#include "pch.h"
#include <iostream>
#include <thread>
namespace tw
{
    class Test1 :public MainProcedure
    {
    public:
        Test1() :
            MainProcedure(0)
        {
        }
        void execute() override
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Test1" << std::endl;
            Supervisor::intend("Test2");
        }
    };
    class Test2 :public NamedEvent
    {
    public:
        Test2() :
            NamedEvent("Test2", true)
        {
        }
        void execute() override
        {
            std::cout << "Test2" << std::endl;
        }
    };
    static Test1 s_test1;
    static Test2 s_test2;
}