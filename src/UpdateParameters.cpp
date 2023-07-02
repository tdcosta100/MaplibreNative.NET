#include "UpdateParameters.h"
#include <mbgl/renderer/update_parameters.hpp>

namespace DOTNET_NAMESPACE
{
    UpdateParameters::UpdateParameters(NativePointerHolder<std::shared_ptr<mbgl::UpdateParameters>>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    UpdateParameters::~UpdateParameters()
    {
    }
}
