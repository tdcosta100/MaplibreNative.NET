#pragma once

namespace DOTNET_NAMESPACE
{
    public enum class MapMode : System::UInt32
    {
        Continuous,
        Static,
        Tile
    };

    public enum class ConstrainMode : System::UInt32
    {
        None,
        HeightOnly,
        WidthAndHeight,
    };

    public enum class ViewportMode : System::UInt32
    {
        Default,
        FlippedY,
    };

    /// <summary>
    /// Determines the orientation of the map.
    /// </summary>
    public enum class NorthOrientation : System::Byte
    {
        /// <summary>
        /// Default
        /// </summary>
        Upwards,
        Rightwards,
        Downwards,
        Leftwards,
    };
}
