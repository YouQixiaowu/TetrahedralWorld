#pragma once
namespace tw
{
    class Transform
    {
    public:
        __declspec(dllexport) Transform();
        __declspec(dllexport) ~Transform();
        __declspec(dllexport) Transform(const Transform& ot);
        __declspec(dllexport) Transform& operator=(const Transform& ot);
        __declspec(dllexport) Transform operator*(const Transform& ob) const;
        __declspec(dllexport) Vec operator*(const Vec& ob) const;
        __declspec(dllexport) std::vector<Vec> operator*(const std::vector<Vec>& ob) const;
        __declspec(dllexport) void act_on(Vec& ob);
        __declspec(dllexport) void act_on(std::vector<Vec>& ob);
    private:
        class Base
        {
        public:
            virtual ~Base() {}
        };
        Base* m_ptr;
        template <typename T>
        class _Imp :public Base
        {
        public:
            _Imp(const T& init) :
                m_imp(init)
            {
            }
            T m_imp;
        };
        static Base* _copy(const Transform& ot);
        std::type_index m_type;
        void set_ptr(Base* ptr);
        friend Transform inverse(const Transform& o);
    };
    Transform inverse(const Transform& o);
}

