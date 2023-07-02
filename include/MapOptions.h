#pragma once
#include "Enums.h"
#include "NativeWrapper.h"

namespace mbgl
{
    class MapOptions;
}

namespace DOTNET_NAMESPACE
{
    ref class Size;

    using Size_ = Size;

    /// <summary>
    /// Holds values for Map options.
    /// </summary>
    public ref class MapOptions : NativeWrapper<mbgl::MapOptions>
    {
    public:
        /// <summary>
        /// Constructs a MapOptions object with default values.
        /// </summary>
        MapOptions();
        ~MapOptions();

        /// <summary>
        /// Sets the map rendering mode. By default, it is set to Continuous
        /// so the map will render as data arrives from the network and react
        /// immediately to state changes.
        /// </summary>
        /// <param name="mode">Map rendering mode.</param>
        /// <returns>MapOptions for chaining options together.</returns>
        MapOptions^ WithMapMode(DOTNET_NAMESPACE::MapMode mode);

        /// <summary>
        /// Sets the map constrain mode. This can be used to limit the map
        /// to wrap around the globe horizontally. By default, it is set to
        /// HeightOnly.
        /// </summary>
        /// <param name="mode">Map constrain mode.</param>
        /// <returns>MapOptions for chaining options together.</returns>
        MapOptions^ WithConstrainMode(DOTNET_NAMESPACE::ConstrainMode mode);

        /// <summary>
        /// Sets the viewport mode. This can be used to flip the vertical
        /// orientation of the map as some devices may use inverted orientation.
        /// </summary>
        /// <param name="mode">Viewport mode.</param>
        /// <returns>MapOptions for chaining options together.</returns>
        MapOptions^ WithViewportMode(DOTNET_NAMESPACE::ViewportMode mode);

        /// <summary>
        /// Specify whether to enable cross-source symbol collision detection
        /// or not. By default, it is set to true.
        /// </summary>
        /// <param name="enableCollisions"><see langword="true"/> to enable, <see langword="false"/> to disable</param>
        /// <returns>MapOptions for chaining options together.</returns>
        MapOptions^ WithCrossSourceCollisions(System::Boolean enableCollisions);

        /// <summary>
        /// Sets the orientation of the Map. By default, it is set to Upwards.
        /// </summary>
        /// <param name="orientation">Orientation of the Map.</param>
        /// <returns>MapOptions for chaining options together.</returns>
        MapOptions^ WithNorthOrientation(DOTNET_NAMESPACE::NorthOrientation orientation);

        /// <summary>
        /// Sets the size to resize the map object and renderer backend.
        /// </summary>
        /// <param name="size">A size given in logical pixels.</param>
        /// <returns>MapOptions for chaining options together.</returns>
        MapOptions^ WithSize(Size_^ size);

        /// <summary>
        /// Sets the custom pixel ratio. By default, it is set to 1.
        /// </summary>
        /// <param name="ratio">Pixel ratio value.</param>
        /// <returns>MapOptions for chaining options together.</returns>
        MapOptions^ WithPixelRatio(System::Single ratio);

        /// <summary>
        /// Gets the previously set (or default) Map mode.
        /// </summary>
        property DOTNET_NAMESPACE::MapMode MapMode { DOTNET_NAMESPACE::MapMode get(); }

        /// <summary>
        /// Gets the previously set (or default) Constrain mode.
        /// </summary>
        property DOTNET_NAMESPACE::ConstrainMode ConstrainMode { DOTNET_NAMESPACE::ConstrainMode get(); }

        /// <summary>
        /// Gets the previously set (or default) Viewport mode.
        /// </summary>
        property DOTNET_NAMESPACE::ViewportMode ViewportMode { DOTNET_NAMESPACE::ViewportMode get(); }

        /// <summary>
        /// Gets the previously set (or default) CrossSourceCollisions value.
        /// </summary>
        property System::Boolean CrossSourceCollisions { System::Boolean get(); }

        /// <summary>
        /// Gets the previously set (or default) Orientation.
        /// </summary>
        property DOTNET_NAMESPACE::NorthOrientation NorthOrientation { DOTNET_NAMESPACE::NorthOrientation get(); }

        /// <summary>
        /// Gets the previously set size.
        /// </summary>
        property Size_^ Size { Size_^ get(); }

        /// <summary>
        /// Gets the previously set (or default) pixel ratio value.
        /// </summary>
        property System::Single PixelRatio { System::Single get(); }
    internal:
        MapOptions(NativePointerHolder<mbgl::MapOptions>^ nativePointerHolder);
    };
}
