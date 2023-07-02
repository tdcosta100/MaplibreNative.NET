#pragma once
#include "NativeWrapper.h"
#include <mbgl/util/vectors.hpp>
#include <mbgl/util/mat4.hpp>

namespace DOTNET_NAMESPACE
{
    public ref class Vec3 : NativeWrapper<mbgl::vec3>
    {
    public:
        Vec3();
        ~Vec3();
    internal:
        Vec3(NativePointerHolder<mbgl::vec3>^ nativePointerHolder);
    };

    public ref class Vec4 : NativeWrapper<mbgl::vec4>
    {
    public:
        Vec4();
        ~Vec4();
    internal:
        Vec4(NativePointerHolder<mbgl::vec4>^ nativePointerHolder);
    };

    public ref class Mat4 : NativeWrapper<mbgl::mat4>
    {
    public:
        Mat4();
        ~Mat4();
    internal:
        Mat4(NativePointerHolder<mbgl::mat4>^ nativePointerHolder);
    };

}
