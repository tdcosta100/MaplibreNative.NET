#pragma once
#include "NativePointerHolder.h"

namespace DOTNET_NAMESPACE
{
    template <typename T>
    public interface class IManagedWrapper
    {
        property NativePointerHolder<T>^ PointerHolder { NativePointerHolder<T>^ get(); }
    };

    template <typename T>
    interface class INativeWrapper
    {
        property T* NativePointer { T* get(); }
    };

    template <typename T>
    public ref class NativeWrapper : IManagedWrapper<T>, INativeWrapper<T>
    {
    public:
        NativeWrapper(NativePointerHolder<T>^ nativePointerHolder) : _nativePointerHolder(nativePointerHolder)
        {
        }

        virtual ~NativeWrapper()
        {
            this->!NativeWrapper();
        }

        !NativeWrapper()
        {
            _nativePointerHolder->~NativePointerHolder();
        }

        virtual property NativePointerHolder<T>^ PointerHolder
        {
            virtual NativePointerHolder<T>^ get()
            {
                return _nativePointerHolder;
            }
        }
    internal:
        NativeWrapper(T* nativePointer) : _nativePointerHolder(CreateNativePointerHolder(nativePointer))
        {
        }

        virtual property T* NativePointer
        {
            virtual T* get() = INativeWrapper<T>::NativePointer::get
            {
                return _nativePointerHolder->NativePointer;
            }
        }

        static NativePointerHolder<T>^ CreateNativePointerHolder(T nativeObject)
        {
            return CreateNativePointerHolder(new T(std::move(nativeObject)));
        }

        static NativePointerHolder<T>^ CreateNativePointerHolder(T* nativePointer)
        {
            return CreateNativePointerHolder(nativePointer, true);
        }

        static NativePointerHolder<T>^ CreateNativePointerHolder(T* nativePointer, System::Boolean ownsPointer)
        {
            return NativePointerHolder<T>::Create(nativePointer, ownsPointer);
        }
    private:
        NativePointerHolder<T>^ _nativePointerHolder;
    };
}
