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
    ref class ShaderGroup;

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
        /// Get the legacy shader group.
        /// </summary>
        /// <returns>A <see cref="ShaderGroup"/></returns>
        ShaderGroup^ GetLegacyGroup();

        /// <summary>
        /// Checks if a shader group exists in the registry for the given name.
        /// </summary>
        /// <param name="shaderGroupName">Name of shader group</param>
        /// <returns>If a shader group is found, true</returns>
        virtual bool IsShaderGroup(System::String^ shaderGroupName);

        /// <summary>
        /// Get a shader group from the registry by name.
        /// </summary>
        /// <param name="shaderGroupName">Name of shader group</param>
        /// <returns>A <see cref="ShaderGroup"/> or <see langword="null"/> if no shader group is found with the given name</returns>
        virtual ShaderGroup^ GetShaderGroup(System::String^ shaderGroupName);

        /// <summary>
        /// Replace a matching shader group in the registry with the provided name.
        /// </summary>
        /// <param name="shaderGroup">A <see cref="ShaderGroup"/>.</param>
        /// <param name="shaderName">Unique name to register the shader group under.</param>
        /// <returns>True if a match was found and the shader group was replaced, false otherwise.</returns>
        virtual bool ReplaceShader(ShaderGroup^ shaderGroup, System::String^ shaderName);

        /// <summary>
        /// Register a new shader group with the registry for the given name.
        /// If a shader group is present in the registry with a conflicting name, registration will fail.
        /// </summary>
        /// <param name="shaderGroup">A <see cref="ShaderGroup"/> to register.</param>
        /// <param name="shaderGroupName">Unique name to register the shader group under.</param>
        /// <returns>True if the shader group was registered, false if another shader group is
        /// already present with a conflicting name.</returns>
        virtual bool RegisterShaderGroup(ShaderGroup^ shaderGroup, System::String^ shaderGroupName);
    internal:
        ShaderRegistry(NativePointerHolder<mbgl::gfx::ShaderRegistry>^ nativePointerHolder);
    };
}
