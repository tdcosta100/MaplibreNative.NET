#pragma once
#include "NativeWrapper.h"
#include "RendererBackend.h"
#include <mbgl/gfx/renderable.hpp>
#include <mbgl/gl/renderer_backend.hpp>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace DOTNET_NAMESPACE
{
    ref class Size;
    using Size_ = Size;

    class NativeExternalRenderingContextBackend;

    public ref class ExternalRenderingContextBackend : NativeWrapper<NativeExternalRenderingContextBackend>, IRendererBackend
    {
    public:
        ExternalRenderingContextBackend(System::IntPtr deviceContext, System::IntPtr renderingContext, Size_^ size);
        ~ExternalRenderingContextBackend();

        virtual System::IntPtr GetNativePointer();
        virtual RendererBackend^ GetRendererBackend();

        property Size_^ Size { Size_^ get(); System::Void set(Size_^ value); }
    internal:
        ExternalRenderingContextBackend(NativePointerHolder<NativeExternalRenderingContextBackend>^ nativePointerHolder);
    };

    class NativeExternalRenderingContextBackend
        :
        public mbgl::gfx::Renderable,
        public mbgl::gl::RendererBackend
    {
    public:
        NativeExternalRenderingContextBackend(HDC deviceContext, HGLRC renderingContext, mbgl::Size size);
        ~NativeExternalRenderingContextBackend() override;

        mbgl::gfx::Renderable& getDefaultRenderable() override;

        void setSize(mbgl::Size size);
    protected:
        void activate() override;
        void deactivate() override;
#ifdef _MSC_VER
        mbgl::gl::ProcAddress getExtensionFunctionPointer(const char* name) override;
#endif
        void updateAssumedState() override;
    private:
        HDC _DeviceContext;
        HGLRC _RenderingContext;
    };
}
