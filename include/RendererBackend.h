#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    namespace gfx
    {
        class RendererBackend;
    }
}

namespace DOTNET_NAMESPACE
{
    ref class RendererBackend;
    
    public interface class IRendererBackend
    {
        System::IntPtr GetNativePointer();
        RendererBackend^ GetRendererBackend();
    };

    public ref class RendererBackend : NativeWrapper<mbgl::gfx::RendererBackend>, IRendererBackend
    {
    public:
        ~RendererBackend();

        virtual System::IntPtr GetNativePointer();
        virtual RendererBackend^ GetRendererBackend();
    internal:
        RendererBackend(NativePointerHolder<mbgl::gfx::RendererBackend>^ nativePointerHolder);
    };
}
