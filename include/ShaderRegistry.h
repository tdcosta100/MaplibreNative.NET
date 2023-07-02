#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    namespace gfx
    {
        class ShaderRegistry;
    }
}

namespace DOTNET_NAMESPACE
{
    ref class Shader;

    /// <summary>
    /// A ShaderRegistry contains a collection of gfx::Shader instances.
    /// Using the registry, shaders may be dynamically registered or replaced
    /// at runtime.
    /// </summary>
    public ref class ShaderRegistry : NativeWrapper<mbgl::gfx::ShaderRegistry>
    {
    public:
        virtual ~ShaderRegistry();

        /// <summary>
        /// Checks if a shader exists in the registry for the given name.
        /// </summary>
        /// <param name="shaderName">Name of shader</param>
        /// <returns>If a shader is found, true</returns>
        virtual bool IsShader(System::String^ shaderName);

        /// <summary>
        /// Get a shader from the registry by name.
        /// </summary>
        /// <param name="shaderName">Name of shader</param>
        /// <returns>A <see cref="Shader"/> or <see langword="nullptr"/> if no shader is found with the given name</returns>
        virtual Shader^ GetShader(System::String^ shaderName);

        /// <summary>
        /// Replace a matching shader in the registry with the provided
        /// instance. Shader type-names must match.
        /// </summary>
        /// <param name="shader">A <see cref="Shader"/>. The ShaderRegistry will take ownership.</param>
        /// <returns><see langword="true"/> if a match was found and the shader was replaced, <see langword="false"/> otherwise.</returns>
        virtual bool ReplaceShader(Shader^ shader);

        /// <summary>
        /// Replace a matching shader in the registry with the provided
        /// instance. Shader type-names must match.
        /// This variant replaces by explicit name.
        /// </summary>
        /// <param name="shader">A <see cref="Shader"/>. The ShaderRegistry will take ownership.</param>
        /// <param name="shaderName">Unique name to register the shader under.</param>
        /// <returns><see langword="true"/> if a match was found and the shader was replaced, <see langword="false"/> otherwise.</returns>
        virtual bool ReplaceShader(Shader^ shader, System::String^ shaderName);

        /// <summary>
        /// Register a new shader with the registry. If a shader is present
        /// in the registry with a conflicting name, registration will fail.
        /// </summary>
        /// <param name="shader">A <see cref="Shader"/> to register. The ShaderRegistry will take ownership.</param>
        /// <returns><see langword="true"/> if the shader was registered, <see langword="false"/> if another shader is already present with a conflicting name.</returns>
        virtual bool RegisterShader(Shader^ shader);

        /// <summary>
        /// Register a new shader with the registry. If a shader is present
        /// in the registry with a conflicting name, registration will fail.
        /// This variant registers using an explicit name.
        /// </summary>
        /// <param name="shader">A <see cref="Shader"/> to register. The ShaderRegistry will take ownership.</param>
        /// <param name="shaderName">Unique name to register the shader under.</param>
        /// <returns><see langword="true"/> if the shader was registered, <see langword="false"/> if another shader is already present with a conflicting name.</returns>
        virtual bool RegisterShader(Shader^ shader, System::String^ shaderName);
    internal:
        ShaderRegistry(NativePointerHolder<mbgl::gfx::ShaderRegistry>^ nativePointerHolder);
    };
}
