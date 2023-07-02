#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    namespace gfx
    {
        class Shader;
    }
}

namespace DOTNET_NAMESPACE
{
    ref class ShaderRegistry;

    /// <summary>
    /// A shader is used as the base class for all programs across any supported
    /// backend API. Shaders are registered with a <see cref="ShaderRegistry"/> instance.
    /// </summary>
    public ref class Shader : NativeWrapper<mbgl::gfx::Shader>
    {
    public:
        virtual ~Shader();

        /// <summary>
        /// Get the type name of this shader
        /// </summary>
        virtual property System::String^ TypeName { virtual System::String^ get(); }
    internal:
        Shader(NativePointerHolder<mbgl::gfx::Shader>^ nativePointerHolder);
    };
}
