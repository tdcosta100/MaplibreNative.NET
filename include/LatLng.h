#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class LatLng;
    class LatLngBounds;
    struct LatLngAltitude;
}

namespace DOTNET_NAMESPACE
{
    ref class CanonicalTileID;
    ref class UnwrappedTileID;
    
    public ref class LatLng : NativeWrapper<mbgl::LatLng>
    {
    public:
        enum class WrapMode : System::Byte { Unwrapped, Wrapped };

        LatLng();
        LatLng(System::Double lat, System::Double lon);
        LatLng(System::Double lat, System::Double lon, WrapMode mode);

        /// <summary>
        /// Constructs a LatLng object with the top left position of the specified tile.
        /// </summary>
        /// <param name="id"></param>
        LatLng(CanonicalTileID^ id);
        LatLng(UnwrappedTileID^ id);
        LatLng(NativePointerHolder<mbgl::LatLng>^ nativePointerHolder);
        ~LatLng();

        LatLng^ Wrapped();
        System::Void Wrap();

        /// <summary>
        /// If the distance from start to end longitudes is between half and full
        /// world, unwrap the start longitude to ensure the shortest path is taken.
        /// </summary>
        /// <param name="end"></param>
        /// <returns></returns>
        System::Void UnwrapForShortestPath(LatLng^ end);

        property System::Double Latitude { System::Double get(); }
        property System::Double Longitude { System::Double get(); }

        static System::Boolean operator==(LatLng^ a, LatLng^ b);
        static System::Boolean operator!=(LatLng^ a, LatLng^ b);
    };

    public ref class LatLngBounds : NativeWrapper<mbgl::LatLngBounds>
    {
    public:
        /// <summary>
        /// Construct an infinite bound, a bound for which the constrain method
        /// returns its input unmodified.
        ///
        /// Note: this is different than <see cref="World"/> since arbitrary
        /// unwrapped coordinates are also inside the bounds.
        /// </summary>
        LatLngBounds();

        /// <summary>
        /// Constructs a LatLngBounds object with the tile's exact boundaries.
        /// </summary>
        /// <param name="id"></param>
        LatLngBounds(CanonicalTileID^ id);
        LatLngBounds(NativePointerHolder<mbgl::LatLngBounds>^ nativePointerHolder);
        ~LatLngBounds();

        /// <summary>
        /// Return a bounds covering the entire (unwrapped) world.
        /// </summary>
        /// <returns></returns>
        static LatLngBounds^ World();

        /// <summary>
        /// Return the bounds consisting of the single point.
        /// </summary>
        /// <param name="a"></param>
        /// <returns></returns>
        static LatLngBounds^ Singleton(LatLng^ a);

        /// <summary>
        /// Return the convex hull of two points; the smallest bounds that contains both.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        static LatLngBounds^ Hull(LatLng^ a, LatLng^ b);

        /// <summary>
        /// Return a bounds that may serve as the identity element for the extend operation.
        /// </summary>
        /// <returns></returns>
        static LatLngBounds^ Empty();

        LatLng^ Constrain(LatLng^ p);
        System::Void Extend(LatLng^ point);
        System::Void Extend(LatLngBounds^ bounds);
        System::Boolean Contains(CanonicalTileID^ tileID);
        System::Boolean Contains(LatLng^ point);
        System::Boolean Contains(LatLng^ point, LatLng::WrapMode wrap);
        System::Boolean Contains(LatLngBounds^ area);
        System::Boolean Contains(LatLngBounds^ area, LatLng::WrapMode wrap);
        System::Boolean Intersects(LatLngBounds^ area);
        System::Boolean Intersects(LatLngBounds^ area, LatLng::WrapMode wrap);

        property System::Boolean Valid { System::Boolean get(); }
        property System::Double South { System::Double get(); }
        property System::Double West { System::Double get(); }
        property System::Double North { System::Double get(); }
        property System::Double East { System::Double get(); }
        property LatLng^ Southwest { LatLng^ get(); }
        property LatLng^ Northeast { LatLng^ get(); }
        property LatLng^ Southeast { LatLng^ get(); }
        property LatLng^ Northwest { LatLng^ get(); }
        property LatLng^ Center { LatLng^ get(); }
        property System::Boolean IsEmpty { System::Boolean get(); }
        property System::Boolean CrossesAntimeridian { System::Boolean get(); }
    };

    public ref class LatLngAltitude : NativeWrapper<mbgl::LatLngAltitude>
    {
    public:
        LatLngAltitude();
        LatLngAltitude(NativePointerHolder<mbgl::LatLngAltitude>^ nativePointerHolder);
        ~LatLngAltitude();

        property LatLng^ Location { LatLng^ get(); System::Void set(LatLng^ value); }
        property System::Double Altitude { System::Double get(); System::Void set(System::Double value); }
    };
}
