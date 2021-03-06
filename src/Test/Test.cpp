#include "pch.h"
#include <iostream>
#include <thread>
namespace tw
{
    class Test1 :public MainProcedure
    {
    public:
        Test1() :
            MainProcedure(1)
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
            NamedEvent("Test2", false)
        {
        }
        void execute() override
        {
            static int i = 0;
            i++;
            std::cout << "Test2" << std::endl;
            if (i > 5)
            {
                //Supervisor::intend("Exit");
                Supervisor::intend("ExTest2it");
            }
        }
    };
    static Test1 s_test1;
    static Test2 s_test2;
}