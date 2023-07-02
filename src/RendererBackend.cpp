#include "RendererBackend.h"
#include <mbgl/gfx/renderer_backend.hpp>

namespace DOTNET_NAMESPACE
{
    RendererBackend::RendererBackend(NativePointerHolder<mbgl::gfx::RendererBackend>^ nativePointerHolder)
        : NativeWrapper(nativePointerHolder)
    {
    }

    RendererBackend::~RendererBackend()
    {
    }

    System::IntPtr RendererBackend::GetNativePointer()
    {
        return System::IntPtr(NativePointer);
    }

    RendererBackend^ RendererBackend::GetRendererBackend()
    {
        return this;
    }
}
