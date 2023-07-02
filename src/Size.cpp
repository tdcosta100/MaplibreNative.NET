#include "Size.h"
#include <mbgl/util/size.hpp>

namespace DOTNET_NAMESPACE
{
    Size::Size() : NativeWrapper(new mbgl::Size())
    {
    }

    Size::Size(System::UInt32 width, System::UInt32 height) : NativeWrapper(new mbgl::Size(width, height))
    {
    }

    Size::~Size()
    {
    }

    System::UInt32 Size::Width::get()
    {
        return NativePointer->width;
    }

    System::Void Size::Width::set(System::UInt32 value)
    {
        NativePointer->width = value;
    }

    System::UInt32 Size::Height::get()
    {
        return NativePointer->height;
    }

    System::Void Size::Height::set(System::UInt32 value)
    {
        NativePointer->height = value;
    }

    System::UInt32 Size::Area::get()
    {
        return NativePointer->area();
    }

    System::Single Size::AspectRatio::get()
    {
        return NativePointer->aspectRatio();
    }

    System::Boolean Size::IsEmpty::get()
    {
        return NativePointer->isEmpty();
    }

    System::Boolean Size::operator==(Size^ a, Size^ b)
    {
        return *a->NativePointer == *b->NativePointer;
    }

    System::Boolean Size::operator!=(Size^ a, Size^ b)
    {
        return *a->NativePointer != *b->NativePointer;
    }
    
    Size::Size(NativePointerHolder<mbgl::Size>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }
}
