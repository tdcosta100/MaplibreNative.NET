#include "Convert.h"
#include "Shader.h"
#include "ShaderRegistry.h"
#include <mbgl/gfx/shader_registry.hpp>

namespace DOTNET_NAMESPACE
{
    ShaderRegistry::ShaderRegistry(NativePointerHolder<mbgl::gfx::ShaderRegistry>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    ShaderRegistry::~ShaderRegistry()
    {
    }

    bool ShaderRegistry::IsShader(System::String^ shaderName)
    {
        return NativePointer->isShader(Convert::ToStdString(shaderName));
    }

    Shader^ ShaderRegistry::GetShader(System::String^ shaderName)
    {
        return gcnew Shader(Shader::CreateNativePointerHolder(NativePointer->getShader(Convert::ToStdString(shaderName)).get(), false));
    }

    bool ShaderRegistry::ReplaceShader(Shader^ shader)
    {
        return NativePointer->replaceShader(std::shared_ptr<mbgl::gfx::Shader>(shader->NativePointer));
    }

    bool ShaderRegistry::ReplaceShader(Shader^ shader, System::String^ shaderName)
    {
        return NativePointer->replaceShader(std::shared_ptr<mbgl::gfx::Shader>(shader->NativePointer), Convert::ToStdString(shaderName));
    }

    bool ShaderRegistry::RegisterShader(Shader^ shader)
    {
        return NativePointer->registerShader(std::shared_ptr<mbgl::gfx::Shader>(shader->NativePointer));
    }

    bool ShaderRegistry::RegisterShader(Shader^ shader, System::String^ shaderName)
    {
        return NativePointer->registerShader(std::shared_ptr<mbgl::gfx::Shader>(shader->NativePointer), Convert::ToStdString(shaderName));
    }
}
