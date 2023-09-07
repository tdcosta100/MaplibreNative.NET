#include "Convert.h"
#include "Shader.h"
#include "ShaderGroup.h"
#include <mbgl/gfx/shader_group.hpp>

namespace DOTNET_NAMESPACE
{
    ShaderGroup::ShaderGroup(NativePointerHolder < mbgl::gfx::ShaderGroup>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    ShaderGroup::~ShaderGroup()
    {
    }

    bool ShaderGroup::IsShader(System::String^ shaderName)
    {
        return NativePointer->isShader(Convert::NativeToStdString(shaderName));
    }

    Shader^ ShaderGroup::GetShader(System::String^ shaderName)
    {
        return gcnew Shader(Shader::CreateNativePointerHolder(NativePointer->getShader(Convert::NativeToStdString(shaderName)).get(), false));
    }

    bool ShaderGroup::ReplaceShader(Shader^ shader)
    {
        return NativePointer->replaceShader(std::shared_ptr<mbgl::gfx::Shader>(shader->NativePointer));
    }

    bool ShaderGroup::ReplaceShader(Shader^ shader, System::String^ shaderName)
    {
        return NativePointer->replaceShader(std::shared_ptr<mbgl::gfx::Shader>(shader->NativePointer), Convert::NativeToStdString(shaderName));
    }

    bool ShaderGroup::RegisterShader(Shader^ shader)
    {
        return NativePointer->registerShader(std::shared_ptr<mbgl::gfx::Shader>(shader->NativePointer));
    }

    bool ShaderGroup::RegisterShader(Shader^ shader, System::String^ shaderName)
    {
        return NativePointer->registerShader(std::shared_ptr<mbgl::gfx::Shader>(shader->NativePointer), Convert::NativeToStdString(shaderName));
    }
}
