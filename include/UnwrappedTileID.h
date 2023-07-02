#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class UnwrappedTileID;
}

namespace DOTNET_NAMESPACE
{
    ref class CanonicalTileID;
    ref class OverscaledTileID;
    
    /// <summary>
    /// Has integer z/x/y coordinates
    /// wrap describes tiles that are left/right of the main tile pyramid, e.g. when
    /// wrapping the world Used for describing what position tiles are getting
    /// rendered at (= calc the matrix) z is never larger than the source's maxzoom
    /// </summary>
    public ref class UnwrappedTileID : NativeWrapper<mbgl::UnwrappedTileID>
    {
    public:
        UnwrappedTileID(System::Byte z, System::Int64 x, System::Int64 y);
        UnwrappedTileID(System::Int16 wrap, CanonicalTileID^ canonical);
        ~UnwrappedTileID();

        System::Boolean IsChildOf(UnwrappedTileID^ parent);
        System::Collections::Generic::IEnumerable<UnwrappedTileID^>^ Children();
        OverscaledTileID^ OverscaleTo(System::Byte z);
        System::Single PixelsToTileUnits(System::Single pixelValue, System::Single zoom);
        UnwrappedTileID^ UnwrapTo(System::Int16 wrap);

        property System::Int16 Wrap { System::Int16 get(); System::Void set(System::Int16 value); }
        property CanonicalTileID^ Canonical { CanonicalTileID^ get(); System::Void set(CanonicalTileID^ value); }

        System::Boolean operator==(UnwrappedTileID^ rhs);
        System::Boolean operator!=(UnwrappedTileID^ rhs);
        System::Boolean operator<(UnwrappedTileID^ rhs);
    internal:
        UnwrappedTileID(NativePointerHolder<mbgl::UnwrappedTileID>^ nativePointerHolder);
    private:
        CanonicalTileID^ _Canonical;
    };
}
