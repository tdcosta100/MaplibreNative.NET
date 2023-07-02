#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    struct BoundOptions;
}

namespace DOTNET_NAMESPACE
{
    ref class LatLngBounds;

    /// <summary>
    /// Holds options to limit what parts of a map are visible. All properties are optional.
    /// </summary>
    public ref class BoundOptions : NativeWrapper<mbgl::BoundOptions>
    {
    public:
        BoundOptions();
        ~BoundOptions();

        /// <summary>
        /// Sets the latitude and longitude bounds to which the camera center are constrained
        /// </summary>
        /// <param name="b"></param>
        /// <returns></returns>
        BoundOptions^ WithLatLngBounds(LatLngBounds^ b);

        /// <summary>
        /// Sets the minimum zoom level
        /// </summary>
        /// <param name="z"></param>
        /// <returns></returns>
        BoundOptions^ WithMinZoom(System::Double z);

        /// <summary>
        /// Sets the maximum zoom level
        /// </summary>
        /// <param name="z"></param>
        /// <returns></returns>
        BoundOptions^ WithMaxZoom(System::Double z);
        
        /// <summary>
        /// Sets the minimum pitch
        /// </summary>
        /// <param name="p"></param>
        /// <returns></returns>
        BoundOptions^ WithMinPitch(System::Double p);

        /// <summary>
        /// Sets the maximum pitch
        /// </summary>
        /// <param name="p"></param>
        /// <returns></returns>
        BoundOptions^ WithMaxPitch(System::Double p);

        /// <summary>
        /// Constrain the center of the camera to be within these bounds.
        /// </summary>
        property LatLngBounds^ Bounds { LatLngBounds^ get(); System::Void set(LatLngBounds^ value); }

        /// <summary>
        /// Maximum zoom level allowed.
        /// </summary>
        property System::Nullable<System::Double> MaxZoom { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        /// <summary>
        /// Minimum zoom level allowed.
        /// </summary>
        property System::Nullable<System::Double> MinZoom { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        /// <summary>
        /// Maximum pitch allowed in degrees.
        /// </summary>
        property System::Nullable<System::Double> MaxPitch { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        /// <summary>
        /// Minimum pitch allowed in degrees.
        /// </summary>
        property System::Nullable<System::Double> MinPitch { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
    internal:
        BoundOptions(NativePointerHolder<mbgl::BoundOptions>^ nativePointerHolder);
    };
}
