#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class OverscaledTileID;
}

namespace DOTNET_NAMESPACE
{
    ref class CanonicalTileID;
    ref class UnwrappedTileID;
    
    /// <summary>
    /// Has integer z/x/y coordinates
    /// overscaledZ describes the zoom level this tile is intented to represent, e.g.
    /// when parsing data z is never larger than the source's maxzoom z/x/y describe
    /// </summary>
    public ref class OverscaledTileID : NativeWrapper<mbgl::OverscaledTileID>
    {
    public:
        OverscaledTileID(System::Byte overscaledZ, System::Int16 wrap, CanonicalTileID^ canonical);
        OverscaledTileID(System::Byte overscaledZ, System::Int16 wrap, System::Byte z, System::UInt32 x, System::UInt32 y);
        OverscaledTileID(System::Byte z, System::UInt32 x, System::UInt32 y);
        OverscaledTileID(CanonicalTileID^ canonical);
        ~OverscaledTileID();

        System::Boolean IsChildOf(OverscaledTileID^ rhs);
        System::UInt32 OverscaleFactor();
        OverscaledTileID^ ScaledTo(System::Byte z);
        UnwrappedTileID^ ToUnwrapped();
        OverscaledTileID^ UnwrapTo(System::Int16 wrap);

        property System::Byte OverscaledZ { System::Byte get(); System::Void set(System::Byte value); }
        property System::Int16 Wrap { System::Int16 get(); System::Void set(System::Int16 value); }
        property CanonicalTileID^ Canonical { CanonicalTileID^ get(); System::Void set(CanonicalTileID^ value); }

        System::Boolean operator==(OverscaledTileID^ rhs);
        System::Boolean operator!=(OverscaledTileID^ rhs);
        System::Boolean operator<(OverscaledTileID^ rhs);
    internal:
        OverscaledTileID(NativePointerHolder<mbgl::OverscaledTileID>^ nativePointerHolder);
    private:
        CanonicalTileID^ _Canonical;
    };
}
