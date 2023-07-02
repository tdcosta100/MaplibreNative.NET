#include "CanonicalTileID.h"
#include "OverscaledTileID.h"
#include "UnwrappedTileID.h"
#include <mbgl/tile/tile_id.hpp>

namespace DOTNET_NAMESPACE
{
    OverscaledTileID::OverscaledTileID(System::Byte overscaledZ, System::Int16 wrap, CanonicalTileID^ canonical)
        : NativeWrapper(new mbgl::OverscaledTileID(overscaledZ, wrap, *canonical->NativePointer))
    {
    }
    
    OverscaledTileID::OverscaledTileID(System::Byte overscaledZ, System::Int16 wrap, System::Byte z, System::UInt32 x, System::UInt32 y)
        : NativeWrapper(new mbgl::OverscaledTileID(overscaledZ, wrap, z, x, y))
    {
    }

    OverscaledTileID::OverscaledTileID(System::Byte z, System::UInt32 x, System::UInt32 y)
        : NativeWrapper(new mbgl::OverscaledTileID(z, x, y))
    {
    }

    OverscaledTileID::OverscaledTileID(CanonicalTileID^ canonical)
        : NativeWrapper(new mbgl::OverscaledTileID(*canonical->NativePointer))
    {
    }

    OverscaledTileID::OverscaledTileID(NativePointerHolder<mbgl::OverscaledTileID>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    OverscaledTileID::~OverscaledTileID()
    {
    }

    System::Boolean OverscaledTileID::IsChildOf(OverscaledTileID^ rhs)
    {
        return NativePointer->isChildOf(*rhs->NativePointer);
    }

    System::UInt32 OverscaledTileID::OverscaleFactor()
    {
        return NativePointer->overscaleFactor();
    }

    OverscaledTileID^ OverscaledTileID::ScaledTo(System::Byte z)
    {
        return gcnew OverscaledTileID(CreateNativePointerHolder(NativePointer->scaledTo(z)));
    }

    UnwrappedTileID^ OverscaledTileID::ToUnwrapped()
    {
        return gcnew UnwrappedTileID(UnwrappedTileID::CreateNativePointerHolder(NativePointer->toUnwrapped()));
    }

    OverscaledTileID^ OverscaledTileID::UnwrapTo(System::Int16 wrap)
    {
        return gcnew OverscaledTileID(CreateNativePointerHolder(NativePointer->unwrapTo(wrap)));
    }

    System::Byte OverscaledTileID::OverscaledZ::get()
    {
        return NativePointer->overscaledZ;
    }

    System::Void OverscaledTileID::OverscaledZ::set(System::Byte value)
    {
        NativePointer->overscaledZ = value;
    }

    System::Int16 OverscaledTileID::Wrap::get()
    {
        return NativePointer->wrap;
    }

    System::Void OverscaledTileID::Wrap::set(System::Int16 value)
    {
        NativePointer->wrap = value;
    }

    CanonicalTileID^ OverscaledTileID::Canonical::get()
    {
        if (!_Canonical)
        {
            _Canonical = gcnew CanonicalTileID(CanonicalTileID::CreateNativePointerHolder(NativePointer->canonical));
        }

        return _Canonical;
    }

    System::Void OverscaledTileID::Canonical::set(CanonicalTileID^ value)
    {
        _Canonical = value;
        NativePointer->canonical = *value->NativePointer;
    }

    System::Boolean OverscaledTileID::operator==(OverscaledTileID^ rhs)
    {
        return NativePointer->operator==(*rhs->NativePointer);
    }

    System::Boolean OverscaledTileID::operator!=(OverscaledTileID^ rhs)
    {
        return NativePointer->operator!=(*rhs->NativePointer);
    }

    System::Boolean OverscaledTileID::operator<(OverscaledTileID^ rhs)
    {
        return NativePointer->operator<(*rhs->NativePointer);
    }
}
