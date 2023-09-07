#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
	namespace gfx
	{
		class ShaderGroup;
	}
}

namespace DOTNET_NAMESPACE
{
	ref class Shader;

	/// <summary>
	/// A ShaderGroup contains a collection of <see cref="Shader"/>.
	/// Using the group, shaders may be dynamically registered or replaced
	/// at runtime.
	/// </summary>
	public ref class ShaderGroup : NativeWrapper<mbgl::gfx::ShaderGroup>
	{
	public:
		virtual ~ShaderGroup();

		/// <summary>
		/// Checks if a shader exists in the group for the given name.
		/// </summary>
		/// <param name="shaderName">Name of shader</param>
		/// <returns>If a shader is found, true</returns>
		virtual bool IsShader(System::String^ shaderName);

		/// <summary>
		/// Get a shader from the group by name
		/// </summary>
		/// <param name="shaderName">Name of shader</param>
		/// <returns>A <see cref="Shader"/> or <see langword="null"/> if no shader is found with the given name</returns>
		virtual Shader^ GetShader(System::String^ shaderName);

		/// <summary>
		/// Replace a matching shader in the group with the provided instance. Shader type-names must match.
		/// </summary>
		/// <param name="shader">A <see cref="Shader"/>.</param>
		/// <returns>True if a match was found and the shader was replaced, false otherwise.</returns>
		virtual bool ReplaceShader(Shader^ shader);

		/// <summary>
		/// Replace a matching shader in the group with the provided instance. Shader type-names must match.
		/// This variant replaces by explicit name.
		/// </summary>
		/// <param name="shader">A <see cref="Shader"/>.</param>
		/// <param name="shaderName">Unique name to register the shader under.</param>
		/// <returns>True if a match was found and the shader was replaced, false otherwise.</returns>
		virtual bool ReplaceShader(Shader^ shader, System::String^ shaderName);

		/// <summary>
		/// Register a new shader with the group. If a shader is present
		/// in the group with a conflicting name, registration will fail.
		/// </summary>
		/// <param name="shader">A <see cref="Shader"/> to register.</param>
		/// <returns>True if the shader was registered, false if another shader is already present with a conflicting name.</returns>
		virtual bool RegisterShader(Shader^ shader);

		/// <summary>
		/// Register a new shader with the group. If a shader is present
		/// in the group with a conflicting name, registration will fail.
		/// This variant registers using an explicit name.
		/// </summary>
		/// <param name="shader">A <see cref="Shader"/>.</param>
		/// <param name="shaderName">Unique name to register the shader under.</param>
		/// <returns>True if the shader was registered, false if another shader is already present with a conflicting name.</returns>
		virtual bool RegisterShader(Shader^ shader, System::String^ shaderName);
	internal:
		ShaderGroup(NativePointerHolder < mbgl::gfx::ShaderGroup>^ nativePointerHolder);
	};
}
