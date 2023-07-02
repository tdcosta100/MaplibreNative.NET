#include "Convert.h"
#include "Shader.h"
#include <mbgl/gfx/shader.hpp>

namespace DOTNET_NAMESPACE
{
    Shader::Shader(NativePointerHolder<mbgl::gfx::Shader>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Shader::~Shader()
    {
    }

    System::String^ Shader::TypeName::get()
    {
        return Convert::ToSystemString(std::string(NativePointer->typeName()));
    }
}
