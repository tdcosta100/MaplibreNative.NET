#pragma once

namespace DOTNET_NAMESPACE
{
    template <typename T>
    public ref class NativePointerHolder
    {
    public:
        ~NativePointerHolder()
        {
            this->!NativePointerHolder();
        }

        !NativePointerHolder()
        {
            if (_deletePointer)
            {
                _deletePointer = false;
                delete _nativePointer;
            }
        }

        property System::IntPtr Pointer
        {
            System::IntPtr get()
            {
                return System::IntPtr(_nativePointer);
            }
        }
    internal:
        NativePointerHolder(T nativeObject) : NativePointerHolder(new T(std::move(nativeObject)))
        {
        }

        NativePointerHolder(T* nativePointer) : NativePointer(nativePointer, true)
        {
        }

        NativePointerHolder(T* nativePointer, System::Boolean ownsPointer)
            :
            _nativePointer(nativePointer),
            _deletePointer(ownsPointer)
        {
        }

        property T* NativePointer
        {
            T* get()
            {
                return _nativePointer;
            }
        }

        static NativePointerHolder<T>^ Create(T nativeObject)
        {
            return Create(new T(std::move(nativeObject)));
        }

        static NativePointerHolder<T>^ Create(T* nativePointer)
        {
            return Create(nativePointer, true);
        }

        static NativePointerHolder<T>^ Create(T* nativePointer, System::Boolean ownsPointer)
        {
            return gcnew NativePointerHolder<T>(nativePointer, ownsPointer);
        }
    private:
        T* _nativePointer;
        System::Boolean _deletePointer;
    };
}
