#include "Convert.h"
#include "Shader.h"
#include "ShaderGroup.h"
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

    ShaderGroup^ ShaderRegistry::GetLegacyGroup()
    {
        return gcnew ShaderGroup(ShaderGroup::CreateNativePointerHolder(&NativePointer->getLegacyGroup(), false));
    }

    bool ShaderRegistry::IsShaderGroup(System::String^ shaderGroupName)
    {
        return NativePointer->isShaderGroup(Convert::NativeToStdString(shaderGroupName));
    }

    ShaderGroup^ ShaderRegistry::GetShaderGroup(System::String^ shaderGroupName)
    {
        return gcnew ShaderGroup(ShaderGroup::CreateNativePointerHolder(NativePointer->getShaderGroup(Convert::NativeToStdString(shaderGroupName)).get(), false));
    }

    bool ShaderRegistry::ReplaceShader(ShaderGroup^ shaderGroup, System::String^ shaderName)
    {
        return NativePointer->replaceShader(std::shared_ptr<mbgl::gfx::ShaderGroup>(shaderGroup->NativePointer), Convert::NativeToStdString(shaderName));
    }

    bool ShaderRegistry::RegisterShaderGroup(ShaderGroup^ shaderGroup, System::String^ shaderGroupName)
    {
        return NativePointer->registerShaderGroup(std::shared_ptr<mbgl::gfx::ShaderGroup>(shaderGroup->NativePointer), Convert::NativeToStdString(shaderGroupName));
    }
}
