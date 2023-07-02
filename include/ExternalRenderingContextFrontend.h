#pragma once
#include "NativeWrapper.h"
#include "RendererFrontend.h"
#include <mbgl/renderer/renderer_frontend.hpp>
#include <algorithm>
#include <msclr/gcroot.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace mbgl
{
    class Renderer;
    class RendererObserver;
    class UpdateParameters;
}

namespace DOTNET_NAMESPACE
{
    class NativeExternalRenderingContextBackend;
    ref class ExternalRenderingContextBackend;
    ref class Renderer;
    ref class Size;

    using Renderer_ = Renderer;
    using Size_ = Size;
    using UpdateParameters_ = UpdateParameters;

    class NativeExternalRenderingContextFrontend;

    public ref class ExternalRenderingContextFrontend : NativeWrapper<NativeExternalRenderingContextFrontend>, IRendererFrontend
    {
    public:
        delegate System::Void UpdatedHandler(UpdateParameters_^ parameters);

        event UpdatedHandler^ Updated;

        ExternalRenderingContextFrontend(System::IntPtr deviceContext, System::IntPtr renderingContext, Size_^ size, System::Single pixelRatio);
        ~ExternalRenderingContextFrontend();

        virtual System::Void Reset();
        virtual System::Void SetObserver(RendererObserver^ observer);
        virtual System::Void Update(UpdateParameters_^ parameters);
        System::Void Render();

        virtual System::IntPtr GetNativePointer();

        property ExternalRenderingContextBackend^ Backend { ExternalRenderingContextBackend^ get(); }
        property Renderer_^ Renderer { Renderer_^ get(); }
    internal:
        delegate System::Void InternalUpdatedHandler(UpdateParameters_^ parameters, System::Boolean updateNativeFrontend);
        ExternalRenderingContextFrontend(NativePointerHolder<NativeExternalRenderingContextFrontend>^ nativePointerHolder);
        System::Void InternalUpdate(UpdateParameters_^ parameters, System::Boolean updateNativeFrontend);
    private:
        ExternalRenderingContextBackend^ _Backend;
        Renderer_^ _Renderer;
    };

    class NativeExternalRenderingContextFrontend : mbgl::RendererFrontend
    {
    public:
        NativeExternalRenderingContextFrontend(HDC deviceContext, HGLRC renderingContext, mbgl::Size size, float pixelRatio, msclr::gcroot<ExternalRenderingContextFrontend::InternalUpdatedHandler^> updatedHandler);
        ~NativeExternalRenderingContextFrontend();

        void reset() override;
        void setObserver(mbgl::RendererObserver& observer) override;
        void update(std::shared_ptr<mbgl::UpdateParameters> parameters) override;
        void update(std::shared_ptr<mbgl::UpdateParameters> parameters, bool callUpdatedHandler);
        void render();
        NativeExternalRenderingContextBackend* getBackend();
        mbgl::Renderer* getRenderer();
    private:
        std::unique_ptr<NativeExternalRenderingContextBackend> _Backend;
        std::unique_ptr<mbgl::Renderer> _Renderer;
        std::shared_ptr<mbgl::UpdateParameters> _UpdateParameters;
        msclr::gcroot<ExternalRenderingContextFrontend::InternalUpdatedHandler^> _UpdatedHandler;
    };
}
