#include "LatLng.h"
#include "Projection.h"
#include <mbgl/util/projection.hpp>

namespace DOTNET_NAMESPACE
{
	System::Double Projection::WorldSize(System::Double scale)
	{
		return mbgl::Projection::worldSize(scale);
	}

	System::Double Projection::GetMetersPerPixelAtLatitude(System::Double lat, System::Double zoom)
	{
		return mbgl::Projection::getMetersPerPixelAtLatitude(lat, zoom);
	}

	ProjectedMeters^ Projection::ProjectedMetersForLatLng(LatLng^ latLng)
	{
		return gcnew ProjectedMeters(ProjectedMeters::CreateNativePointerHolder(mbgl::Projection::projectedMetersForLatLng(*latLng->NativePointer)));
	}

	LatLng^ Projection::LatLngForProjectedMeters(ProjectedMeters^ projectedMeters)
	{
		return gcnew LatLng(LatLng::CreateNativePointerHolder(mbgl::Projection::latLngForProjectedMeters(*projectedMeters->NativePointer)));
	}

	PointDouble Projection::Project(LatLng^ latLng, System::Double scale)
	{
		return PointDouble(mbgl::Projection::project(*latLng->NativePointer, scale));
	}

	PointDouble Projection::Project(LatLng^ latLng, System::Int32 zoom)
	{
		return PointDouble(mbgl::Projection::project(*latLng->NativePointer, zoom));
	}

	LatLng^ Projection::Unproject(PointDouble p, System::Double scale)
	{
		return gcnew LatLng(LatLng::CreateNativePointerHolder(mbgl::Projection::unproject(mbgl::ScreenCoordinate(p.X, p.Y), scale)));
	}

	LatLng^ Projection::Unproject(PointDouble p, System::Double scale, LatLng::WrapMode wrapMode)
	{
		return gcnew LatLng(LatLng::CreateNativePointerHolder(mbgl::Projection::unproject(mbgl::ScreenCoordinate(p.X, p.Y), scale, (mbgl::LatLng::WrapMode)wrapMode)));
	}

	ProjectedMeters::ProjectedMeters(System::Double northing) : ProjectedMeters(northing, 0)
	{
	}

	ProjectedMeters::ProjectedMeters(System::Double northing, System::Double easting) : NativeWrapper(new mbgl::ProjectedMeters(northing, easting))
	{
	}

	ProjectedMeters::ProjectedMeters(NativePointerHolder<mbgl::ProjectedMeters>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
	{
	}

	ProjectedMeters::~ProjectedMeters()
	{
	}

	System::Double ProjectedMeters::Northing::get()
	{
		return NativePointer->northing();
	}

	System::Double ProjectedMeters::Easting::get()
	{
		return NativePointer->easting();
	}

	System::Boolean ProjectedMeters::operator==(ProjectedMeters^ a, ProjectedMeters^ b)
	{
		return *a->NativePointer == *b->NativePointer;
	}

	System::Boolean ProjectedMeters::operator!=(ProjectedMeters^ a, ProjectedMeters^ b)
	{
		return *a->NativePointer != *b->NativePointer;
	}
}
