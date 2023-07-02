#pragma once
#include "NativeWrapper.h"
#include "RendererBackend.h"

namespace mbgl
{
    namespace gfx
    {
        class BackendScope;
    }
}

namespace DOTNET_NAMESPACE
{
    public ref class BackendScope : NativeWrapper<mbgl::gfx::BackendScope>
    {
    public:
        /// <summary>
        /// There are two types of scopes: Creating an "Implicit" scope tells Mapbox
        /// GL that the supporting windowing system has already activated the GL
        /// Backend and that no further actions are required. Creating an "Explicit"
        /// scope actually enables the GL Backend, and disables it when the
        /// BackendScope is destroyed.
        /// </summary>
        enum class ScopeType : System::Byte
        {
            Implicit,
            Explicit,
        };

        BackendScope(IRendererBackend^ backend);
        BackendScope(IRendererBackend^ backend, ScopeType scopeType);

        ~BackendScope();

        static System::Boolean Exists();
    };
}
