#include "ExternalRenderingContextBackend.h"
#include "Size.h"
#include <mbgl/gfx/backend.hpp>
#include <mbgl/gl/renderable_resource.hpp>

#if !defined(MLN_WITH_EGL) && !defined(MLN_WITH_OSMESA)
extern "C" PROC WINAPI wgl_GetProcAddress(LPCSTR procName);
#endif

namespace
{
    class NativeExternalRenderingContextBackendRenderableResource : public mbgl::gl::RenderableResource
    {
    public:
        NativeExternalRenderingContextBackendRenderableResource(DOTNET_NAMESPACE::NativeExternalRenderingContextBackend& backend) : _Backend(backend)
        {
        }

        ~NativeExternalRenderingContextBackendRenderableResource()
        {
        }

        void bind() override
        {
            _Backend.setFramebufferBinding(0);
            _Backend.setViewport(0, 0, _Backend.getSize());
        }
    private:
        DOTNET_NAMESPACE::NativeExternalRenderingContextBackend& _Backend;
    };
}

namespace DOTNET_NAMESPACE
{
    ExternalRenderingContextBackend::ExternalRenderingContextBackend(System::IntPtr deviceContext, System::IntPtr renderingContext, Size_^ size)
        : NativeWrapper(new NativeExternalRenderingContextBackend(
            reinterpret_cast<HDC>(deviceContext.ToPointer()),
            reinterpret_cast<HGLRC>(renderingContext.ToPointer()),
            *size->NativePointer
        ))
    {
    }

    ExternalRenderingContextBackend::ExternalRenderingContextBackend(NativePointerHolder<NativeExternalRenderingContextBackend>^ nativePointerHolder)
        : NativeWrapper(nativePointerHolder)
    {
    }

    ExternalRenderingContextBackend::~ExternalRenderingContextBackend()
    {
    }

    System::IntPtr ExternalRenderingContextBackend::GetNativePointer()
    {
        return System::IntPtr(NativePointer);
    }

    RendererBackend^ ExternalRenderingContextBackend::GetRendererBackend()
    {
        return gcnew RendererBackend(RendererBackend::CreateNativePointerHolder(dynamic_cast<mbgl::gfx::RendererBackend*>(NativePointer), false));
    }

    Size_^ ExternalRenderingContextBackend::Size::get()
    {
        return gcnew Size_(Size_::CreateNativePointerHolder(NativePointer->getSize()));
    }

    System::Void ExternalRenderingContextBackend::Size::set(Size_^ value)
    {
        NativePointer->setSize(*value->NativePointer);
    }

    NativeExternalRenderingContextBackend::NativeExternalRenderingContextBackend(HDC deviceContext, HGLRC renderingContext, mbgl::Size size)
        :
        mbgl::gfx::Renderable(size, std::make_unique<NativeExternalRenderingContextBackendRenderableResource>(*this)),
        mbgl::gl::RendererBackend(mbgl::gfx::ContextMode::Unique),
        _RenderingContext(renderingContext)
    {
        this->size = size;
    }

    NativeExternalRenderingContextBackend::~NativeExternalRenderingContextBackend()
    {
    }

    mbgl::gfx::Renderable& NativeExternalRenderingContextBackend::getDefaultRenderable()
    {
        return *this;
    }

    void NativeExternalRenderingContextBackend::setSize(mbgl::Size size)
    {
        this->size = size;
    }

    void NativeExternalRenderingContextBackend::activate()
    {
    }

    void NativeExternalRenderingContextBackend::deactivate()
    {
    }

    mbgl::gl::ProcAddress NativeExternalRenderingContextBackend::getExtensionFunctionPointer(const char* name)
    {
#if defined(MLN_WITH_EGL)
        return (mbgl::gl::ProcAddress)::eglGetProcAddress(name);
#elif defined(MLN_WITH_OSMESA)
        return (mbgl::gl::ProcAddress)::OSMesaGetProcAddress(name);
#else
        return (mbgl::gl::ProcAddress)::wgl_GetProcAddress(name);
#endif
    }

    void NativeExternalRenderingContextBackend::updateAssumedState()
    {
        assumeFramebufferBinding(mbgl::gl::RendererBackend::ImplicitFramebufferBinding);
        assumeViewport(0, 0, size);
    }
}

namespace mbgl
{
    namespace gfx
    {
        template <>
        std::unique_ptr<DOTNET_NAMESPACE::NativeExternalRenderingContextBackend>
        Backend::Create<mbgl::gfx::Backend::Type::OpenGL>(HDC deviceContext, HGLRC renderingContext, mbgl::Size size)
        {
            return std::make_unique<DOTNET_NAMESPACE::NativeExternalRenderingContextBackend>(deviceContext, renderingContext, size);
        }

    } // namespace gfx
} // namespace mbgl
