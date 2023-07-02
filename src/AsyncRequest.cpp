#include "AsyncRequest.h"
#include <mbgl/util/async_request.hpp>

namespace DOTNET_NAMESPACE
{
    AsyncRequest::AsyncRequest() : NativeWrapper(new mbgl::AsyncRequest())
    {
    }

    AsyncRequest::AsyncRequest(NativePointerHolder<mbgl::AsyncRequest>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    AsyncRequest::~AsyncRequest()
    {
    }
}
