#include "CanonicalTileID.h"
#include "Convert.h"
#include "OverscaledTileID.h"
#include "UnwrappedTileID.h"
#include <mbgl/tile/tile_id.hpp>

namespace DOTNET_NAMESPACE
{
    UnwrappedTileID::UnwrappedTileID(System::Byte z, System::Int64 x, System::Int64 y)
        : NativeWrapper(new mbgl::UnwrappedTileID(z, x, y))
    {
    }

    UnwrappedTileID::UnwrappedTileID(System::Int16 wrap, CanonicalTileID^ canonical)
        : NativeWrapper(new mbgl::UnwrappedTileID(wrap, *canonical->NativePointer))
    {
    }

    UnwrappedTileID::UnwrappedTileID(NativePointerHolder<mbgl::UnwrappedTileID>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    UnwrappedTileID::~UnwrappedTileID()
    {
    }

    System::Boolean UnwrappedTileID::IsChildOf(UnwrappedTileID^ parent)
    {
        return NativePointer->isChildOf(*parent->NativePointer);
    }

    System::Collections::Generic::IEnumerable<UnwrappedTileID^>^ UnwrappedTileID::Children()
    {
        return Convert::ToSystemArray<mbgl::UnwrappedTileID, UnwrappedTileID, 4>(NativePointer->children());
    }

    OverscaledTileID^ UnwrappedTileID::OverscaleTo(System::Byte z)
    {
        return gcnew OverscaledTileID(OverscaledTileID::CreateNativePointerHolder(NativePointer->overscaleTo(z)));
    }

    System::Single UnwrappedTileID::PixelsToTileUnits(System::Single pixelValue, System::Single zoom)
    {
        return NativePointer->pixelsToTileUnits(pixelValue, zoom);
    }

    UnwrappedTileID^ UnwrappedTileID::UnwrapTo(System::Int16 wrap)
    {
        return gcnew UnwrappedTileID(CreateNativePointerHolder(NativePointer->unwrapTo(wrap)));
    }

    System::Int16 UnwrappedTileID::Wrap::get()
    {
        return NativePointer->wrap;
    }

    System::Void UnwrappedTileID::Wrap::set(System::Int16 value)
    {
        NativePointer->wrap = value;
    }

    CanonicalTileID^ UnwrappedTileID::Canonical::get()
    {
        if (!_Canonical)
        {
            _Canonical = gcnew CanonicalTileID(CanonicalTileID::CreateNativePointerHolder(NativePointer->canonical));
        }

        return _Canonical;
    }

    System::Void UnwrappedTileID::Canonical::set(CanonicalTileID^ value)
    {
        _Canonical = value;
        NativePointer->canonical = *value->NativePointer;
    }

    System::Boolean UnwrappedTileID::operator==(UnwrappedTileID^ rhs)
    {
        return NativePointer->operator==(*rhs->NativePointer);
    }

    System::Boolean UnwrappedTileID::operator!=(UnwrappedTileID^ rhs)
    {
        return NativePointer->operator!=(*rhs->NativePointer);
    }

    System::Boolean UnwrappedTileID::operator<(UnwrappedTileID^ rhs)
    {
        return NativePointer->operator<(*rhs->NativePointer);
    }
}
