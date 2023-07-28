#pragma once
#include "NativeWrapper.h"
#include "LatLng.h"
#include "Point.h"

namespace mbgl
{
	class ProjectedMeters;
}

namespace DOTNET_NAMESPACE
{
	ref class ProjectedMeters;
	
	public ref class Projection abstract sealed
	{
	public:
		/// <summary>
		/// Map pixel width at given scale.
		/// </summary>
		/// <param name="scale"></param>
		/// <returns></returns>
		static System::Double WorldSize(System::Double scale);

		static System::Double GetMetersPerPixelAtLatitude(System::Double lat, System::Double zoom);
		static ProjectedMeters^ ProjectedMetersForLatLng(LatLng^ latLng);
		static LatLng^ LatLngForProjectedMeters(ProjectedMeters^ projectedMeters);
		static PointDouble Project(LatLng^ latLng, System::Double scale);
		static PointDouble Project(LatLng^ latLng, System::Int32 zoom);
		static LatLng^ Unproject(PointDouble p, System::Double scale);
		static LatLng^ Unproject(PointDouble p, System::Double scale, LatLng::WrapMode wrapMode);
	};

	public ref class ProjectedMeters : NativeWrapper<mbgl::ProjectedMeters>
	{
	public:
		ProjectedMeters(System::Double northing);
		ProjectedMeters(System::Double northing, System::Double easting);
		~ProjectedMeters();

		property System::Double Northing { System::Double get(); }
		property System::Double Easting { System::Double get(); }

		static System::Boolean operator==(ProjectedMeters^ a, ProjectedMeters^ b);
		static System::Boolean operator!=(ProjectedMeters^ a, ProjectedMeters^ b);
	internal:
		ProjectedMeters(NativePointerHolder<mbgl::ProjectedMeters>^ nativePointerHolder);
	};
}