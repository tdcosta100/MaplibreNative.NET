#include "Vector.h"

namespace DOTNET_NAMESPACE
{
    Vec3::Vec3() : NativeWrapper(new mbgl::vec3())
    {
    }

    Vec3::Vec3(NativePointerHolder<mbgl::vec3>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Vec3::~Vec3()
    {
    }

    Vec4::Vec4() : NativeWrapper(new mbgl::vec4())
    {
    }

    Vec4::Vec4(NativePointerHolder<mbgl::vec4>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Vec4::~Vec4()
    {
    }

    Mat4::Mat4() : NativeWrapper(new mbgl::mat4())
    {
    }

    Mat4::Mat4(NativePointerHolder<mbgl::mat4>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Mat4::~Mat4()
    {
    }
}
