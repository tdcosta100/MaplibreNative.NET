#include "CanonicalTileID.h"
#include "LatLng.h"
#include "UnwrappedTileID.h"
#include <mbgl/util/geo.hpp>
#include <mbgl/tile/tile_id.hpp>

namespace DOTNET_NAMESPACE
{
    LatLng::LatLng() : NativeWrapper(new mbgl::LatLng())
    {
    }

    LatLng::LatLng(System::Double lat, System::Double lon) : NativeWrapper(new mbgl::LatLng(lat, lon))
    {
    }

    LatLng::LatLng(System::Double lat, System::Double lon, WrapMode mode) : NativeWrapper(new mbgl::LatLng(lat, lon, (mbgl::LatLng::WrapMode)mode))
    {
    }

    LatLng::LatLng(CanonicalTileID^ id) : NativeWrapper(new mbgl::LatLng(*id->NativePointer))
    {
    }

    LatLng::LatLng(UnwrappedTileID^ id) : NativeWrapper(new mbgl::LatLng(*id->NativePointer))
    {
    }

    LatLng::LatLng(NativePointerHolder<mbgl::LatLng>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    LatLng::~LatLng()
    {
    }

    LatLng^ LatLng::Wrapped()
    {
        return gcnew LatLng(CreateNativePointerHolder(NativePointer->wrapped()));
    }

    System::Void LatLng::Wrap()
    {
        NativePointer->wrap();
    }

    System::Void LatLng::UnwrapForShortestPath(LatLng^ end)
    {
        NativePointer->unwrapForShortestPath(*end->NativePointer);
    }

    System::Double LatLng::Latitude::get()
    {
        return NativePointer->latitude();
    }

    System::Double LatLng::Longitude::get()
    {
        return NativePointer->longitude();
    }

    System::Boolean LatLng::operator==(LatLng^ a, LatLng^ b)
    {
        return *a->NativePointer == *b->NativePointer;
    }

    System::Boolean LatLng::operator!=(LatLng^ a, LatLng^ b)
    {
        return *a->NativePointer != *b->NativePointer;
    }

    LatLngBounds::LatLngBounds() : NativeWrapper(new mbgl::LatLngBounds())
    {
    }

    LatLngBounds::LatLngBounds(CanonicalTileID^ id) : NativeWrapper(new mbgl::LatLngBounds(*id->NativePointer))
    {
    }

    LatLngBounds::LatLngBounds(NativePointerHolder<mbgl::LatLngBounds>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    LatLngBounds::~LatLngBounds()
    {
    }

    LatLngBounds^ LatLngBounds::World()
    {
        return gcnew LatLngBounds(LatLngBounds::CreateNativePointerHolder(mbgl::LatLngBounds::world()));
    }

    LatLngBounds^ LatLngBounds::Singleton(LatLng^ a)
    {
        return gcnew LatLngBounds(LatLngBounds::CreateNativePointerHolder(mbgl::LatLngBounds::singleton(*a->NativePointer)));
    }

    LatLngBounds^ LatLngBounds::Hull(LatLng^ a, LatLng^ b)
    {
        return gcnew LatLngBounds(LatLngBounds::CreateNativePointerHolder(mbgl::LatLngBounds::hull(*a->NativePointer, *b->NativePointer)));
    }

    LatLngBounds^ LatLngBounds::Empty()
    {
        return gcnew LatLngBounds(LatLngBounds::CreateNativePointerHolder(mbgl::LatLngBounds::empty()));
    }

    LatLng^ LatLngBounds::Constrain(LatLng^ p)
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->constrain(*p->NativePointer)));
    }

    System::Void LatLngBounds::Extend(LatLng^ point)
    {
        NativePointer->extend(*point->NativePointer);
    }

    System::Void LatLngBounds::Extend(LatLngBounds^ bounds)
    {
        NativePointer->extend(*bounds->NativePointer);
    }

    System::Boolean LatLngBounds::Contains(CanonicalTileID^ tileID)
    {
        return NativePointer->contains(*tileID->NativePointer);
    }

    System::Boolean LatLngBounds::Contains(LatLng^ point)
    {
        return NativePointer->contains(*point->NativePointer);
    }

    System::Boolean LatLngBounds::Contains(LatLng^ point, LatLng::WrapMode wrap)
    {
        return NativePointer->contains(*point->NativePointer, (mbgl::LatLng::WrapMode)wrap);
    }

    System::Boolean LatLngBounds::Contains(LatLngBounds^ area)
    {
        return NativePointer->contains(*area->NativePointer);
    }

    System::Boolean LatLngBounds::Contains(LatLngBounds^ area, LatLng::WrapMode wrap)
    {
        return NativePointer->contains(*area->NativePointer, (mbgl::LatLng::WrapMode)wrap);
    }

    System::Boolean LatLngBounds::Intersects(LatLngBounds^ area)
    {
        return NativePointer->intersects(*area->NativePointer);
    }

    System::Boolean LatLngBounds::Intersects(LatLngBounds^ area, LatLng::WrapMode wrap)
    {
        return NativePointer->intersects(*area->NativePointer, (mbgl::LatLng::WrapMode)wrap);
    }

    System::Boolean LatLngBounds::Valid::get()
    {
        return NativePointer->valid();
    }

    System::Double LatLngBounds::South::get()
    {
        return NativePointer->south();
    }

    System::Double LatLngBounds::West::get()
    {
        return NativePointer->west();
    }

    System::Double LatLngBounds::North::get()
    {
        return NativePointer->north();
    }

    System::Double LatLngBounds::East::get()
    {
        return NativePointer->east();
    }

    LatLng^ LatLngBounds::Southwest::get()
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->southwest()));
    }

    LatLng^ LatLngBounds::Northeast::get()
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->northeast()));
    }

    LatLng^ LatLngBounds::Southeast::get()
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->southeast()));
    }

    LatLng^ LatLngBounds::Northwest::get()
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->northwest()));
    }

    LatLng^ LatLngBounds::Center::get()
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->center()));
    }

    System::Boolean LatLngBounds::IsEmpty::get()
    {
        return NativePointer->isEmpty();
    }

    System::Boolean LatLngBounds::CrossesAntimeridian::get()
    {
        return NativePointer->crossesAntimeridian();
    }

    LatLngAltitude::LatLngAltitude() : NativeWrapper(new mbgl::LatLngAltitude())
    {
    }

    LatLngAltitude::LatLngAltitude(NativePointerHolder<mbgl::LatLngAltitude>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    LatLngAltitude::~LatLngAltitude()
    {
    }

    LatLng^ LatLngAltitude::Location::get()
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->location));
    }

    System::Void LatLngAltitude::Location::set(LatLng^ value)
    {
        NativePointer->location = *value->NativePointer;
    }

    System::Double LatLngAltitude::Altitude::get()
    {
        return NativePointer->altitude;
    }

    System::Void LatLngAltitude::Altitude::set(System::Double value)
    {
        NativePointer->altitude = value;
    }
}
