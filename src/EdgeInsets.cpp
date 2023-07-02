#include "EdgeInsets.h"
#include "Point.h"
#include <mbgl/util/geo.hpp>

namespace DOTNET_NAMESPACE
{
    EdgeInsets::EdgeInsets()
        : NativeWrapper(new mbgl::EdgeInsets())
    {
    }

    EdgeInsets::EdgeInsets(System::Double top)
        : NativeWrapper(new mbgl::EdgeInsets(top))
    {
    }

    EdgeInsets::EdgeInsets(System::Double top, System::Double left)
        : NativeWrapper(new mbgl::EdgeInsets(top, left))
    {
    }

    EdgeInsets::EdgeInsets(System::Double top, System::Double left, System::Double bottom)
        : NativeWrapper(new mbgl::EdgeInsets(top, left, bottom))
    {
    }

    EdgeInsets::EdgeInsets(System::Double top, System::Double left, System::Double bottom, System::Double right)
        : NativeWrapper(new mbgl::EdgeInsets(top, left, bottom, right))
    {
    }

    EdgeInsets::EdgeInsets(NativePointerHolder<mbgl::EdgeInsets>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    EdgeInsets::~EdgeInsets()
    {
    }

    System::Boolean EdgeInsets::IsFlush()
    {
        return NativePointer->isFlush();
    }

    ScreenCoordinate EdgeInsets::GetCenter(System::UInt16 width, System::UInt16 height)
    {
        return ScreenCoordinate(NativePointer->getCenter(width, height));
    }

    System::Double EdgeInsets::Top::get()
    {
        return NativePointer->top();
    }

    System::Double EdgeInsets::Left::get()
    {
        return NativePointer->left();
    }

    System::Double EdgeInsets::Bottom::get()
    {
        return NativePointer->bottom();
    }

    System::Double EdgeInsets::Right::get()
    {
        return NativePointer->right();
    }

    System::Void EdgeInsets::operator+=(EdgeInsets^ o)
    {
        NativePointer->operator+=(*o->NativePointer);
    }

    EdgeInsets^ EdgeInsets::operator+(EdgeInsets^ o)
    {
        return gcnew EdgeInsets(CreateNativePointerHolder(NativePointer->operator+(*o->NativePointer)));
    }

    System::Boolean EdgeInsets::operator==(EdgeInsets^ a, EdgeInsets^ b)
    {
        return *a->NativePointer == *b->NativePointer;
    }

    System::Boolean EdgeInsets::operator!=(EdgeInsets^ a, EdgeInsets^ b)
    {
        return *a->NativePointer == *b->NativePointer;
    }
}
