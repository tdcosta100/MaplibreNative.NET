#include "ExternalRenderingContextBackend.h"
#include "ExternalRenderingContextFrontend.h"
#include "Renderer.h"
#include "RendererObserver.h"
#include "Size.h"
#include "UpdateParameters.h"
#include <mbgl/gfx/backend_scope.hpp>
#include <mbgl/renderer/renderer.hpp>
#include <mbgl/renderer/update_parameters.hpp>

namespace DOTNET_NAMESPACE
{
    ExternalRenderingContextFrontend::ExternalRenderingContextFrontend(System::IntPtr deviceContext, System::IntPtr renderingContext, Size_^ size, System::Single pixelRatio)
        : NativeWrapper(new NativeExternalRenderingContextFrontend(
            reinterpret_cast<HDC>(deviceContext.ToPointer()),
            reinterpret_cast<HGLRC>(renderingContext.ToPointer()),
            mbgl::Size(*size->NativePointer),
            pixelRatio,
            gcnew InternalUpdatedHandler(this, &ExternalRenderingContextFrontend::InternalUpdate)
        ))
    {
    }

    ExternalRenderingContextFrontend::ExternalRenderingContextFrontend(NativePointerHolder<NativeExternalRenderingContextFrontend>^ nativePointerHolder)
        : NativeWrapper(nativePointerHolder)
    {
    }

    ExternalRenderingContextFrontend::~ExternalRenderingContextFrontend()
    {
    }

    System::Void ExternalRenderingContextFrontend::Reset()
    {
        NativePointer->reset();
    }

    System::Void ExternalRenderingContextFrontend::SetObserver(RendererObserver^ observer)
    {
        NativePointer->setObserver(*observer->NativePointer);
    }

    System::Void ExternalRenderingContextFrontend::Update(UpdateParameters^ parameters)
    {
        InternalUpdate(parameters, true);
    }

    System::Void ExternalRenderingContextFrontend::InternalUpdate(UpdateParameters^ parameters, System::Boolean updateNativeFrontend)
    {
        if (updateNativeFrontend)
        {
            NativePointer->update(*parameters->NativePointer, false);
        }

        Updated(parameters);
    }

    System::Void ExternalRenderingContextFrontend::Render()
    {
        NativePointer->render();
    }

    System::IntPtr ExternalRenderingContextFrontend::GetNativePointer()
    {
        return System::IntPtr(NativePointer);
    }

    ExternalRenderingContextBackend^ ExternalRenderingContextFrontend::Backend::get()
    {
        if (!_Backend)
        {
            _Backend = gcnew ExternalRenderingContextBackend(ExternalRenderingContextBackend::CreateNativePointerHolder(NativePointer->getBackend(), false));
        }

        return _Backend;
    }

    Renderer_^ ExternalRenderingContextFrontend::Renderer::get()
    {
        if (!_Renderer)
        {
            _Renderer = gcnew Renderer_(Renderer_::CreateNativePointerHolder(NativePointer->getRenderer(), false));
        }

        return _Renderer;
    }

    NativeExternalRenderingContextFrontend::NativeExternalRenderingContextFrontend(HDC deviceContext, HGLRC renderingContext, mbgl::Size size, float pixelRatio, msclr::gcroot<ExternalRenderingContextFrontend::InternalUpdatedHandler^> updatedHandler)
        :
        _Backend(std::make_unique<NativeExternalRenderingContextBackend>(deviceContext, renderingContext, size)),
        _Renderer(std::make_unique<mbgl::Renderer>(*_Backend, pixelRatio)),
        _UpdatedHandler(updatedHandler)
    {
    }

    NativeExternalRenderingContextFrontend::~NativeExternalRenderingContextFrontend()
    {
        _Renderer.reset();
        _Backend.reset();
    }

    void NativeExternalRenderingContextFrontend::reset()
    {
        assert(_Renderer);
        _Renderer.reset();
    }

    void NativeExternalRenderingContextFrontend::setObserver(mbgl::RendererObserver& observer)
    {
        assert(_Renderer);
        _Renderer->setObserver(&observer);
    }

    void NativeExternalRenderingContextFrontend::update(std::shared_ptr<mbgl::UpdateParameters> parameters)
    {
        update(parameters, true);
    }

    void NativeExternalRenderingContextFrontend::update(std::shared_ptr<mbgl::UpdateParameters> parameters, bool callUpdatedHandler)
    {
        _UpdateParameters = parameters;

        if (callUpdatedHandler)
        {
            _UpdatedHandler->Invoke(gcnew UpdateParameters(UpdateParameters::CreateNativePointerHolder(std::shared_ptr<mbgl::UpdateParameters>(_UpdateParameters))), false);
        }
    }

    void NativeExternalRenderingContextFrontend::render()
    {
        assert(_Renderer);

        if (!_UpdateParameters)
        {
            return;
        }

        mbgl::gfx::BackendScope guard(*_Backend, mbgl::gfx::BackendScope::ScopeType::Implicit);

        std::shared_ptr<mbgl::UpdateParameters> updateParameters = _UpdateParameters;
        _Renderer->render(updateParameters);
    }

    NativeExternalRenderingContextBackend* NativeExternalRenderingContextFrontend::getBackend()
    {
        return _Backend.get();
    }

    mbgl::Renderer* NativeExternalRenderingContextFrontend::getRenderer()
    {
        assert(_Renderer);
        return _Renderer.get();
    }
}
