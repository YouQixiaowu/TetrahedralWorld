#pragma once
namespace tw
{
    /// <summary>
    /// ·ºÐÍ´úÀí
    /// </summary>
    class Generic
    {
    private:
        class _Base
        {
        public:
            _Base()
            {
            }
            virtual ~_Base()
            {
            }
            virtual _Base* _copy() = 0;
        };
        template<typename T>
        class _Ptr :
            public _Base
        {
        public:
            _Ptr(const T& other) :
                _imp(other)
            {
            }
            ~_Ptr()
            {
            }
            _Base* _copy() override
            {
                return new _Ptr<T>(_imp);
            }
            T _imp;
        };
    public:
        Generic() :
            _ptr(nullptr)
        {
        }
        ~Generic()
        {
            _setPtr(nullptr);
        }
        Generic(const Generic& gnrc) :
            _ptr(gnrc._ptr == nullptr ? nullptr : gnrc._ptr->_copy())
        {
        }
        Generic(Generic&& gnrc) noexcept :
            _ptr(gnrc._ptr)
        {
            gnrc._ptr = nullptr;
        }
        Generic& operator=(const Generic& gnrc)
        {
            _setPtr(gnrc._ptr == nullptr ? nullptr : gnrc._ptr->_copy());
            return *this;
        }
        Generic& operator=(Generic&& gnrc) noexcept
        {
            _setPtr(gnrc._ptr); return *this;
        }
        template<typename T>
        inline Generic(const T& variable) :
            _ptr(new _Ptr<T>(variable))
        {
        }
        template<typename T>
        inline T& as()
        {
            return dynamic_cast<_Ptr<T>*>(_ptr)->_imp;
        }
        template<typename T>
        inline const T& as() const
        {
            return dynamic_cast<_Ptr<T>*>(_ptr)->_imp;
        }
        template<typename T>
        inline bool is() const
        {
            return dynamic_cast<_Ptr<T>*>(_ptr) != nullptr;
        }
    private:
        inline void _setPtr(_Base* ptr)
        {
            if (_ptr != nullptr) delete _ptr;
            _ptr = ptr;
        }
        _Base* _ptr;
    };
}