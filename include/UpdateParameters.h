#pragma once
#include "NativeWrapper.h"
#include <memory>

namespace mbgl
{
    class UpdateParameters;
}

namespace DOTNET_NAMESPACE
{
    public ref class UpdateParameters : NativeWrapper<std::shared_ptr<mbgl::UpdateParameters>>
    {
    public:
        ~UpdateParameters();
    internal:
        UpdateParameters(NativePointerHolder<std::shared_ptr<mbgl::UpdateParameters>>^ nativePointerHolder);
    };
}
