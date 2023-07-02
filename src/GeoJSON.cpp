#include "GeoJSON.h"
#include <mbgl/util/geojson.hpp>

namespace DOTNET_NAMESPACE
{
    GeoJSON::GeoJSON(NativePointerHolder<mbgl::GeoJSON>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    GeoJSON::~GeoJSON()
    {
    }
}
