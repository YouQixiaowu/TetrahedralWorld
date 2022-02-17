#pragma once
namespace tw
{
    class Vec
    {
    public:
        __declspec(dllexport) Vec();
        __declspec(dllexport) Vec(double x, double y, double z);
        __declspec(dllexport) Vec(const Vec& ot);
        __declspec(dllexport) Vec& operator=(const Vec& ot);
        __declspec(dllexport) ~Vec();
    public:
        class Base
        {
        public:
            virtual ~Base() {}
        };
        Base* m_ptr;
        class _Imp :public Base
        {
        public:
            _Imp(const Eigen::Vector3d& init) :
                m_imp(init)
            {
            }
            Eigen::Vector3d m_imp;
        };
    };
}

