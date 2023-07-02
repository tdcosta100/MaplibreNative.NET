#pragma once
#include "NativeWrapper.h"
#include "Point.h"

namespace mbgl
{
    struct CameraOptions;
}

namespace DOTNET_NAMESPACE
{
    ref class EdgeInsets;
    ref class LatLng;
    
    /// <summary>
    /// Various options for describing the viewpoint of a map. All properties are
    /// optional.
    /// Anchor and center points are mutually exclusive, with preference for the
    /// center point when both are set.
    /// </summary>
    public ref class CameraOptions : NativeWrapper<mbgl::CameraOptions>
    {
    public:
        CameraOptions();
        ~CameraOptions();

        CameraOptions^ WithCenter(LatLng^ o);
        CameraOptions^ WithPadding(EdgeInsets^ p);
        CameraOptions^ WithAnchor(System::Nullable<ScreenCoordinate> o);
        CameraOptions^ WithZoom(System::Nullable<System::Double> o);
        CameraOptions^ WithBearing(System::Nullable<System::Double> o);
        CameraOptions^ WithPitch(System::Nullable<System::Double> o);

        /// <summary>
        /// Coordinate at the center of the map.
        /// </summary>
        property LatLng^ Center { LatLng^ get(); System::Void set(LatLng^ value); }

        /// <summary>
        /// Padding around the interior of the view that affects the frame of
        /// reference for <see cref="Center"/>.
        /// </summary>
        property EdgeInsets^ Padding { EdgeInsets^ get(); System::Void set(EdgeInsets^ value); }

        /// <summary>
        /// Point of reference for <see cref="Zoom"/>, <see cref="Bearing"/> and <see cref="Pitch"/>, assuming an origin at the
        /// top - left corner of the view.
        /// </summary>
        property System::Nullable<ScreenCoordinate> Anchor { System::Nullable<ScreenCoordinate> get(); System::Void set(System::Nullable<ScreenCoordinate> value); }

        /// <summary>
        /// Zero-based zoom level. Constrained to the minimum and maximum zoom levels.
        /// </summary>
        property System::Nullable<System::Double> Zoom { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        /// <summary>
        /// Bearing, measured in degrees from true north. Wrapped to [0, 360).
        /// </summary>
        property System::Nullable<System::Double> Bearing { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        /// <summary>
        /// Pitch toward the horizon measured in degrees , with 0 deg resulting in a
        /// two - dimensional map.
        /// </summary>
        property System::Nullable<System::Double> Pitch { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        static System::Boolean operator==(CameraOptions^ a, CameraOptions^ b);
        static System::Boolean operator!=(CameraOptions^ a, CameraOptions^ b);
    internal:
        CameraOptions(NativePointerHolder<mbgl::CameraOptions>^ nativePointerHolder);
    private:
        LatLng^ _Center;
        EdgeInsets^ _Padding;
        System::Nullable<ScreenCoordinate> _Anchor;
    };
}
