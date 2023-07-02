#pragma once
#include "NativeWrapper.h"
#include <mbgl/util/geojson.hpp>

namespace DOTNET_NAMESPACE
{
    public ref class GeoJSON : NativeWrapper<mbgl::GeoJSON>
    {
    public:
        ~GeoJSON();
    internal:
        GeoJSON(NativePointerHolder<mbgl::GeoJSON>^ nativePointerHolder);
    };
}
