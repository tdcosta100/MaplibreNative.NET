#include "LatLng.h"
#include "TileCoordinate.h"
#include "TransformState.h"
#include "UnwrappedTileID.h"
#include <mbgl/util/tile_coordinate.hpp>

namespace DOTNET_NAMESPACE
{
    TileCoordinate::TileCoordinate() : NativeWrapper(new mbgl::TileCoordinate())
    {
    }

    TileCoordinate::TileCoordinate(NativePointerHolder<mbgl::TileCoordinate>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    TileCoordinate::~TileCoordinate()
    {
    }

    TileCoordinate^ TileCoordinate::ZoomTo(System::Double zoom)
    {
        return gcnew TileCoordinate(CreateNativePointerHolder(NativePointer->zoomTo(zoom)));
    }

    TileCoordinatePoint TileCoordinate::P::get()
    {
        return TileCoordinatePoint(NativePointer->p);
    }

    System::Void TileCoordinate::P::set(TileCoordinatePoint value)
    {
        NativePointer->p = mbgl::TileCoordinatePoint(value.X, value.Y);
    }

    System::Double TileCoordinate::Z::get()
    {
        return NativePointer->z;
    }

    System::Void TileCoordinate::Z::set(System::Double value)
    {
        NativePointer->z = value;
    }

    TileCoordinate^ TileCoordinate::FromLatLng(System::Double zoom, LatLng^ latLng)
    {
        return gcnew TileCoordinate(CreateNativePointerHolder(mbgl::TileCoordinate::fromLatLng(zoom, *latLng->NativePointer)));
    }

    TileCoordinate^ TileCoordinate::FromScreenCoordinate(TransformState^ state, System::Byte zoom, ScreenCoordinate screenCoordinate)
    {
        return gcnew TileCoordinate(CreateNativePointerHolder(mbgl::TileCoordinate::fromScreenCoordinate(*state->NativePointer, zoom, mbgl::ScreenCoordinate(screenCoordinate.X, screenCoordinate.Y))));
    }

    GeometryCoordinate TileCoordinate::ToGeometryCoordinate(UnwrappedTileID^ tileID, TileCoordinatePoint point)
    {
        return GeometryCoordinate(mbgl::TileCoordinate::toGeometryCoordinate(*tileID->NativePointer, mbgl::TileCoordinatePoint(point.X, point.Y)));
    }
}
