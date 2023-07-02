#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    struct FreeCameraOptions;
}

namespace DOTNET_NAMESPACE
{
    ref class Vec3;
    ref class Vec4;
    ref class LatLng;
    ref class LatLngAltitude;

    /// <summary>
    /// Various options for accessing physical properties of the underlying camera
    /// entity. A direct access to these properties allows more flexible and precise
    /// controlling of the camera while also being fully compatible and
    /// interchangeable with CameraOptions. All properties are optional.
    /// </summary>
    public ref class FreeCameraOptions : NativeWrapper<mbgl::FreeCameraOptions>
    {
    public:
        FreeCameraOptions();
        ~FreeCameraOptions();

        /// <summary>
        /// Helper function for setting orientation of the camera by defining a
        /// focus point on the map. Up vector is required in certain scenarios where
        /// bearing can't be deduced from the viewing direction
        /// </summary>
        /// <param name="location"></param>
        /// <returns></returns>
        System::Void LookAtPoint(LatLng^ location);
        
        /// <summary>
        /// Helper function for setting orientation of the camera by defining a
        /// focus point on the map. Up vector is required in certain scenarios where
        /// bearing can't be deduced from the viewing direction
        /// </summary>
        /// <param name="location"></param>
        /// <returns></returns>
        System::Void LookAtPoint(LatLng^ location, Vec3^ upVector);

        /// <summary>
        /// Helper function for setting the orientation of the camera as a pitch and
        /// a bearing.Both values are in degrees
        /// </summary>
        /// <param name="pitch"></param>
        /// <param name="bearing"></param>
        /// <returns></returns>
        System::Void SetPitchBearing(System::Double pitch, System::Double bearing);

        /// <summary>
        /// Position of the camera in slightly modified web mercator coordinates
        ///  - The size of 1 unit is the width of the projected world instead of the
        /// "mercator meter". Coordinate [0, 0, 0] is the north-west corner and
        /// [1, 1, 0] is the south-east corner.
        ///  - Z coordinate is conformal and must respect minimum and maximum zoom
        /// values.
        ///  - Zoom is automatically computed from the altitude (z)
        /// </summary>
        property Vec3^ Position { Vec3^ get(); System::Void set(Vec3^ value); }

        /// <summary>
        /// Orientation of the camera represented as a unit quaternion [x, y, z, w].
        /// The default pose of the camera is such that the forward vector is
        /// looking up the -Z axis and the up vector is aligned with north
        /// orientation of the map: forward [0, 0, -1], up [0, -1, 0], right [1, 0, 0]
        /// 
        ///  Orientation can be set freely but certain constraints still apply
        ///   - Orientation must be representable with only pitch and bearing.
        ///   - Pitch has an upper limit
        /// </summary>
        property Vec4^ Orientation { Vec4^ get(); System::Void set(Vec4^ value); }

        /// <summary>
        /// Sets the mercator position as Lat&amp;Lng and altitude in meters.
        /// Fails to return a value if <see cref="Position"/>
        /// is invalid or is not set.
        /// </summary>
        property LatLngAltitude^ Location { LatLngAltitude^ get(); System::Void set(LatLngAltitude^ value); }
    internal:
        FreeCameraOptions(NativePointerHolder<mbgl::FreeCameraOptions>^ nativePointerHolder);
    };
}
