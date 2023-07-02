#include "BackendScope.h"
#include <mbgl/gfx/backend_scope.hpp>
#include <mbgl/gfx/renderer_backend.hpp>

namespace DOTNET_NAMESPACE
{
    BackendScope::BackendScope(IRendererBackend^ backend)
        : NativeWrapper(new mbgl::gfx::BackendScope(*backend->GetRendererBackend()->NativePointer))
    {
    }

    BackendScope::BackendScope(IRendererBackend^ backend, ScopeType scopeType)
        : NativeWrapper(new mbgl::gfx::BackendScope(*((NativeWrapper<mbgl::gfx::RendererBackend>^)backend)->NativePointer, (mbgl::gfx::BackendScope::ScopeType)scopeType))
    {
    }

    BackendScope::~BackendScope()
    {
    }

    System::Boolean BackendScope::Exists()
    {
        return mbgl::gfx::BackendScope::exists();
    }
}
