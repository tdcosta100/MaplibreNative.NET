#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class AsyncRequest;
}

namespace DOTNET_NAMESPACE
{
    public ref class AsyncRequest : NativeWrapper<mbgl::AsyncRequest>
    {
    public:
        AsyncRequest();
        ~AsyncRequest();
    internal:
        AsyncRequest(NativePointerHolder<mbgl::AsyncRequest>^ nativePointerHolder);
    };
}
