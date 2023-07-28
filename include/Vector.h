#pragma once
#include "NativeWrapper.h"
#include <mbgl/util/vectors.hpp>
#include <mbgl/util/mat4.hpp>

namespace DOTNET_NAMESPACE
{
    ref class Mat4;
    
    public ref class Vec3 : NativeWrapper<mbgl::vec3>, System::Collections::Generic::IReadOnlyList<System::Double>
    {
    public:
        Vec3();
        ~Vec3();

        virtual System::Collections::Generic::IEnumerator<System::Double>^ GetEnumerator();
        virtual System::Collections::IEnumerator^ GetEnumeratorObject() = System::Collections::IEnumerable::GetEnumerator;

        property System::Double default[System::Int32] { virtual System::Double get(System::Int32 index); System::Void set(System::Int32 index, System::Double value); };
        property System::Int32 Count { virtual System::Int32 get(); }
    internal:
        Vec3(NativePointerHolder<mbgl::vec3>^ nativePointerHolder);
    };

    public ref class Vec4 : NativeWrapper<mbgl::vec4>, System::Collections::Generic::IReadOnlyList<System::Double>
    {
    public:
        Vec4();
        ~Vec4();

        virtual System::Collections::Generic::IEnumerator<System::Double>^ GetEnumerator();
        virtual System::Collections::IEnumerator^ GetEnumeratorObject() = System::Collections::IEnumerable::GetEnumerator;

        property System::Double default[System::Int32] { virtual System::Double get(System::Int32 index); System::Void set(System::Int32 index, System::Double value); };
        property System::Int32 Count { virtual System::Int32 get(); }

        static System::Void TransformMat4(Vec4^ out, Mat4^ m);
        static System::Void TransformMat4(Vec4^ out, Vec4^ a, Mat4^ m);
    internal:
        Vec4(NativePointerHolder<mbgl::vec4>^ nativePointerHolder);
    };

    public ref class Mat4 : NativeWrapper<mbgl::mat4>, System::Collections::Generic::IReadOnlyList<System::Double>
    {
    public:
        Mat4();
        Mat4(Mat4^ source);
        ~Mat4();

        virtual System::Collections::Generic::IEnumerator<System::Double>^ GetEnumerator();
        virtual System::Collections::IEnumerator^ GetEnumeratorObject() = System::Collections::IEnumerable::GetEnumerator;

        property System::Double default[System::Int32] { virtual System::Double get(System::Int32 index); System::Void set(System::Int32 index, System::Double value); };
        property System::Int32 Count { virtual System::Int32 get(); }

        static System::Void Identity(Mat4^ out);
        static System::Boolean Invert(Mat4^ out);
        static System::Boolean Invert(Mat4^ out, Mat4^ a);
        static System::Void Ortho(Mat4^ out, System::Double left, System::Double right, System::Double bottom, System::Double top, System::Double near, System::Double far);
        static System::Void Perspective(Mat4^ out, System::Double fovy, System::Double aspect, System::Double near, System::Double far);
        static System::Void Copy(Mat4^ out, Mat4^ a);
        static System::Void Translate(Mat4^ out, System::Double x, System::Double y, System::Double z);
        static System::Void Translate(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z);
        static System::Void RotateX(Mat4^ out, System::Double rad);
        static System::Void RotateX(Mat4^ out, Mat4^ a, System::Double rad);
        static System::Void RotateY(Mat4^ out, System::Double rad);
        static System::Void RotateY(Mat4^ out, Mat4^ a, System::Double rad);
        static System::Void RotateZ(Mat4^ out, System::Double rad);
        static System::Void RotateZ(Mat4^ out, Mat4^ a, System::Double rad);
        static System::Void Scale(Mat4^ out, System::Double x, System::Double y, System::Double z);
        static System::Void Scale(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z);
        static System::Void Multiply(Mat4^ out, Mat4^ a);
        static System::Void Multiply(Mat4^ out, Mat4^ a, Mat4^ b);
    internal:
        Mat4(NativePointerHolder<mbgl::mat4>^ nativePointerHolder);
    };

    [System::Runtime::CompilerServices::ExtensionAttribute]
    public ref class MatrixExtensions abstract sealed
    {
    public:
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Identity(Mat4^ out);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Boolean Invert(Mat4^ out);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Boolean Invert(Mat4^ out, Mat4^ a);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Ortho(Mat4^ out, System::Double left, System::Double right, System::Double bottom, System::Double top, System::Double near, System::Double far);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Perspective(Mat4^ out, System::Double fovy, System::Double aspect, System::Double near, System::Double far);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Copy(Mat4^ out, Mat4^ a);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Translate(Mat4^ out, System::Double x, System::Double y, System::Double z);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Translate(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateX(Mat4^ out, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateX(Mat4^ out, Mat4^ a, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateY(Mat4^ out, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateY(Mat4^ out, Mat4^ a, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateZ(Mat4^ out, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void RotateZ(Mat4^ out, Mat4^ a, System::Double rad);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Scale(Mat4^ out, System::Double x, System::Double y, System::Double z);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Scale(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Multiply(Mat4^ out, Mat4^ a);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void Multiply(Mat4^ out, Mat4^ a, Mat4^ b);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void TransformMat4(Vec4^ out, Mat4^ m);
        [System::Runtime::CompilerServices::ExtensionAttribute]
        static System::Void TransformMat4(Vec4^ out, Vec4^ a, Mat4^ m);
    };
}
