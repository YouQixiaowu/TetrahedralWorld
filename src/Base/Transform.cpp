#include "pch.h"
namespace tw
{
    using ETransform = Eigen::Transform<double, 3, Eigen::TransformTraits::AffineCompact>;
    Transform::Transform() :
        m_type(typeid(ETransform)),
        m_ptr(new _Imp<ETransform>(ETransform::Identity()))
    {
    }

    Transform::~Transform()
    {
        set_ptr(nullptr);
    }

    Transform::Base* Transform::_copy(const Transform& ot)
    {
        if (ot.m_type == typeid(ETransform))
            return new _Imp<ETransform>(dynamic_cast<_Imp<ETransform>*>(ot.m_ptr)->m_imp);
        return nullptr;
    }

    template<typename T, typename Y>
    static auto _multiply(const T& oa, const Y& ob) -> decltype(oa* ob)
    {
        return oa * ob;
    }

    void Transform::set_ptr(Base* ptr)
    {
        if (m_ptr == ptr)
            return;
        if (m_ptr != nullptr)
            delete m_ptr;
        m_ptr = ptr;
    }

    Transform::Transform(const Transform& ot) :
        m_type(ot.m_type),
        m_ptr(_copy(ot))
    {
    }

    Transform& Transform::operator=(const Transform& ot)
    {
        set_ptr(_copy(ot));
        return *this;
    }

    Transform Transform::operator*(const Transform& ob) const
    {
        Transform res;
        if (m_type == typeid(ETransform))
        {
            _Imp<ETransform>* impa = dynamic_cast<_Imp<ETransform>*>(m_ptr);
            if (nullptr == impa)
                return res;
            ETransform& ta = impa->m_imp;

            if (ob.m_type == typeid(ETransform))
            {
                _Imp<ETransform>* impb = dynamic_cast<_Imp<ETransform>*>(ob.m_ptr);
                if (nullptr == impb)
                    return res;
                ETransform& tb = impb->m_imp;
                res.set_ptr(new _Imp<decltype(ta* tb)>(ta * tb));
            }
        }
        return res;
    }

    Vec Transform::operator*(const Vec& ob) const
    {
        Vec res;
        if (m_type == typeid(ETransform))
        {
            _Imp<ETransform>* impa = dynamic_cast<_Imp<ETransform>*>(m_ptr);
            if (nullptr == impa)
                return res;
            ETransform& ta = impa->m_imp;
            Vec::_Imp* ptrres = dynamic_cast<Vec::_Imp*>(res.m_ptr);
            if (nullptr == ptrres)
                return res;
            Vec::_Imp* ptrb = dynamic_cast<Vec::_Imp*>(ob.m_ptr);
            if (nullptr == ptrb)
                return res;
            ptrres->m_imp = ta * ptrb->m_imp;
        }
        return res;
    }

    std::vector<Vec> Transform::operator*(const std::vector<Vec>& ob) const
    {
        std::vector<Vec> res;
        res.resize(ob.size());
        for (size_t i = 0; i < ob.size(); i++)
            res.at(i) = (*this) * ob.at(i);
        return res;
    }

    void Transform::act_on(Vec& ob)
    {
        ob = (*this) * ob;
    }

    void Transform::act_on(std::vector<Vec>& ob)
    {
        for (size_t i = 0; i < ob.size(); i++)
            ob.at(i) = (*this) * ob.at(i);
    }

    Transform inverse(const Transform& o)
    {
        Transform res;
        if (o.m_type == typeid(ETransform))
        {
            Transform::_Imp<ETransform>* impa = dynamic_cast<Transform::_Imp<ETransform>*>(o.m_ptr);
            if (nullptr == impa)
                return res;
            impa->m_imp = impa->m_imp.inverse();
        }
        return res;
    }
}