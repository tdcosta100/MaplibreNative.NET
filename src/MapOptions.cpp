#include "MapOptions.h"
#include "Size.h"
#include <mbgl/map/map_options.hpp>

namespace DOTNET_NAMESPACE
{
    MapOptions::MapOptions() : NativeWrapper(new mbgl::MapOptions())
    {
    }

    MapOptions::MapOptions(NativePointerHolder<mbgl::MapOptions>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    MapOptions::~MapOptions()
    {
    }

    MapOptions^ MapOptions::WithMapMode(DOTNET_NAMESPACE::MapMode mode)
    {
        NativePointer->withMapMode((mbgl::MapMode)mode);
        
        return this;
    }

    MapOptions^ MapOptions::WithConstrainMode(DOTNET_NAMESPACE::ConstrainMode mode)
    {
        NativePointer->withConstrainMode((mbgl::ConstrainMode)mode);
        
        return this;
    }

    MapOptions^ MapOptions::WithViewportMode(DOTNET_NAMESPACE::ViewportMode mode)
    {
        NativePointer->withViewportMode((mbgl::ViewportMode)mode);

        return this;
    }

    MapOptions^ MapOptions::WithCrossSourceCollisions(System::Boolean enableCollisions)
    {
        NativePointer->withCrossSourceCollisions(enableCollisions);

        return this;
    }

    MapOptions^ MapOptions::WithNorthOrientation(DOTNET_NAMESPACE::NorthOrientation orientation)
    {
        NativePointer->withNorthOrientation((mbgl::NorthOrientation)orientation);
        
        return this;
    }

    MapOptions^ MapOptions::WithSize(Size_^ size)
    {
        NativePointer->withSize(*size->NativePointer);
        
        return this;
    }

    MapOptions^ MapOptions::WithPixelRatio(System::Single ratio)
    {
        NativePointer->withPixelRatio(ratio);
        
        return this;
    }

    MapMode MapOptions::MapMode::get()
    {
        return (DOTNET_NAMESPACE::MapMode)NativePointer->mapMode();
    }

    ConstrainMode MapOptions::ConstrainMode::get()
    {
        return (DOTNET_NAMESPACE::ConstrainMode)NativePointer->constrainMode();
    }

    ViewportMode MapOptions::ViewportMode::get()
    {
        return (DOTNET_NAMESPACE::ViewportMode)NativePointer->viewportMode();
    }

    System::Boolean MapOptions::CrossSourceCollisions::get()
    {
        return NativePointer->crossSourceCollisions();
    }

    NorthOrientation MapOptions::NorthOrientation::get()
    {
        return (DOTNET_NAMESPACE::NorthOrientation)NativePointer->northOrientation();
    }

    Size_^ MapOptions::Size::get()
    {
        return gcnew Size_(Size_::CreateNativePointerHolder(NativePointer->size()));
    }

    System::Single MapOptions::PixelRatio::get()
    {
        return NativePointer->pixelRatio();
    }
}
