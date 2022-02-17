#include "pch.h"
namespace tw
{
    Vec::Vec() :
        m_ptr(new _Imp(Eigen::Vector3d(0, 0, 0)))
    {
    }
    Vec::Vec(double x, double y, double z) :
        m_ptr(new _Imp(Eigen::Vector3d(x, y, z)))
    {
    }
    Vec::Vec(const Vec& ot) :
        m_ptr(nullptr)
    {
        _Imp* ptr = dynamic_cast<_Imp*>(ot.m_ptr);
        if (nullptr == ptr)
            return;
        m_ptr = new _Imp(ptr->m_imp);
    }
    Vec& Vec::operator=(const Vec& ot)
    {
        _Imp* ptrt = dynamic_cast<_Imp*>(ot.m_ptr);
        if (nullptr == ptrt)
            return *this;
        _Imp* ptr = dynamic_cast<_Imp*>(m_ptr);
        if (nullptr == ptr)
            return *this;
        ptr->m_imp = ptrt->m_imp;
        return *this;
    }
    Vec::~Vec()
    {
        if (nullptr == m_ptr)
            return;
        delete m_ptr;
        m_ptr = nullptr;
    }
}