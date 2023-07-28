#include "Vector.h"

namespace DOTNET_NAMESPACE
{
    template <typename T>
    ref class VectorEnumerator : System::Collections::Generic::IEnumerator<System::Double>
    {
    public:
        ~VectorEnumerator()
        {
            this->!VectorEnumerator();
        }

        !VectorEnumerator()
        {
            if (!_disposed)
            {
                delete _begin;
                delete _end;

                if (_current)
                {
                    delete _current;
                }
            }
        }

        virtual System::Boolean MoveNext()
        {
            if (!_current)
            {
                _current = new typename T::iterator(*_begin);
            }
            else if (*_current != *_end)
            {
                *_current = ++(*_current);
            }

            return *_current != *_end;
        }

        virtual System::Void Reset()
        {
            if (_current)
            {
                delete _current;
            }

            _current = nullptr;
        }

        property System::Double Current
        {
            virtual System::Double get()
            {
                return *(*_current);
            }
        }

        property System::Object^ CurrentObject
        {
            virtual System::Object^ get() = System::Collections::IEnumerator::Current::get
            {
                return safe_cast<System::Object^>(*(*_current));
            }
        }
    internal:
        VectorEnumerator(typename T::iterator* begin, typename T::iterator* end)
        {
            _begin = new typename T::iterator(*begin);
            _end = new typename T::iterator(*end);
            Reset();
        }
    private:
        System::Boolean _disposed = false;
        typename T::iterator* _begin;
        typename T::iterator* _end;
        typename T::iterator* _current;
    };

    Vec3::Vec3() : NativeWrapper(new mbgl::vec3())
    {
    }

    Vec3::Vec3(NativePointerHolder<mbgl::vec3>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Vec3::~Vec3()
    {
    }

    System::Collections::Generic::IEnumerator<System::Double>^ Vec3::GetEnumerator()
    {
        return gcnew VectorEnumerator<mbgl::vec3>(&NativePointer->begin(), &NativePointer->end());
    }

    System::Collections::IEnumerator^ Vec3::GetEnumeratorObject()
    {
        return gcnew VectorEnumerator<mbgl::vec3>(&NativePointer->begin(), &NativePointer->end());
    }

    System::Double Vec3::default::get(System::Int32 index)
    {
        if (index < 0 || index >= static_cast<System::Int32>(NativePointer->size()))
        {
            throw gcnew System::IndexOutOfRangeException();
        }

        return NativePointer->at(static_cast<size_t>(index));
    }

    System::Void Vec3::default::set(System::Int32 index, System::Double value)
    {
        if (index < 0 || index >= static_cast<System::Int32>(NativePointer->size()))
        {
            throw gcnew System::IndexOutOfRangeException();
        }

        NativePointer->at(static_cast<size_t>(index)) = value;
    }

    System::Int32 Vec3::Count::get()
    {
        return static_cast<int>(NativePointer->size());
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

    System::Collections::Generic::IEnumerator<System::Double>^ Vec4::GetEnumerator()
    {
        return gcnew VectorEnumerator<mbgl::vec4>(&NativePointer->begin(), &NativePointer->end());
    }

    System::Collections::IEnumerator^ Vec4::GetEnumeratorObject()
    {
        return gcnew VectorEnumerator<mbgl::vec4>(&NativePointer->begin(), &NativePointer->end());
    }

    System::Double Vec4::default::get(System::Int32 index)
    {
        if (index < 0 || index >= static_cast<System::Int32>(NativePointer->size()))
        {
            throw gcnew System::IndexOutOfRangeException();
        }

        return NativePointer->at(static_cast<size_t>(index));
    }

    System::Void Vec4::default::set(System::Int32 index, System::Double value)
    {
        if (index < 0 || index >= static_cast<System::Int32>(NativePointer->size()))
        {
            throw gcnew System::IndexOutOfRangeException();
        }

        NativePointer->at(static_cast<size_t>(index)) = value;
    }

    System::Int32 Vec4::Count::get()
    {
        return static_cast<int>(NativePointer->size());
    }

    System::Void Vec4::TransformMat4(Vec4^ out, Mat4^ m)
    {
        mbgl::matrix::transformMat4(*out->NativePointer, *out->NativePointer, *m->NativePointer);
    }

    System::Void Vec4::TransformMat4(Vec4^ out, Vec4^ a, Mat4^ m)
    {
        mbgl::matrix::transformMat4(*out->NativePointer, *a->NativePointer, *m->NativePointer);
    }

    Mat4::Mat4() : NativeWrapper(new mbgl::mat4())
    {
    }

    Mat4::Mat4(Mat4^ source) : NativeWrapper(new mbgl::mat4())
    {
        Copy(this, source);
    }

    Mat4::Mat4(NativePointerHolder<mbgl::mat4>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Mat4::~Mat4()
    {
    }

    System::Collections::Generic::IEnumerator<System::Double>^ Mat4::GetEnumerator()
    {
        return gcnew VectorEnumerator<mbgl::mat4>(&NativePointer->begin(), &NativePointer->end());
    }

    System::Collections::IEnumerator^ Mat4::GetEnumeratorObject()
    {
        return gcnew VectorEnumerator<mbgl::mat4>(&NativePointer->begin(), &NativePointer->end());
    }

    System::Double Mat4::default::get(System::Int32 index)
    {
        if (index < 0 || index >= static_cast<System::Int32>(NativePointer->size()))
        {
            throw gcnew System::IndexOutOfRangeException();
        }

        return NativePointer->at(static_cast<size_t>(index));
    }

    System::Void Mat4::default::set(System::Int32 index, System::Double value)
    {
        if (index < 0 || index >= static_cast<System::Int32>(NativePointer->size()))
        {
            throw gcnew System::IndexOutOfRangeException();
        }

        NativePointer->at(static_cast<size_t>(index)) = value;
    }

    System::Int32 Mat4::Count::get()
    {
        return static_cast<int>(NativePointer->size());
    }

    System::Void Mat4::Identity(Mat4^ out)
    {
        mbgl::matrix::identity(*out->NativePointer);
    }

    System::Boolean Mat4::Invert(Mat4^ out)
    {
        return mbgl::matrix::invert(*out->NativePointer, *out->NativePointer);
    }

    System::Boolean Mat4::Invert(Mat4^ out, Mat4^ a)
    {
        return mbgl::matrix::invert(*out->NativePointer, *a->NativePointer);
    }

    System::Void Mat4::Ortho(Mat4^ out, System::Double left, System::Double right, System::Double bottom, System::Double top, System::Double near, System::Double far)
    {
        mbgl::matrix::ortho(*out->NativePointer, left, right, bottom, top, near, far);
    }

    System::Void Mat4::Perspective(Mat4^ out, System::Double fovy, System::Double aspect, System::Double near, System::Double far)
    {
        mbgl::matrix::perspective(*out->NativePointer, fovy, aspect, near, far);
    }

    System::Void Mat4::Copy(Mat4^ out, Mat4^ a)
    {
        mbgl::matrix::copy(*out->NativePointer, *a->NativePointer);
    }

    System::Void Mat4::Translate(Mat4^ out, System::Double x, System::Double y, System::Double z)
    {
        mbgl::matrix::translate(*out->NativePointer, *out->NativePointer, x, y, z);
    }

    System::Void Mat4::Translate(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z)
    {
        mbgl::matrix::translate(*out->NativePointer, *a->NativePointer, x, y, z);
    }

    System::Void Mat4::RotateX(Mat4^ out, System::Double rad)
    {
        mbgl::matrix::rotate_x(*out->NativePointer, *out->NativePointer, rad);
    }

    System::Void Mat4::RotateX(Mat4^ out, Mat4^ a, System::Double rad)
    {
        mbgl::matrix::rotate_x(*out->NativePointer, *a->NativePointer, rad);
    }

    System::Void Mat4::RotateY(Mat4^ out, System::Double rad)
    {
        mbgl::matrix::rotate_y(*out->NativePointer, *out->NativePointer, rad);
    }

    System::Void Mat4::RotateY(Mat4^ out, Mat4^ a, System::Double rad)
    {
        mbgl::matrix::rotate_y(*out->NativePointer, *a->NativePointer, rad);
    }

    System::Void Mat4::RotateZ(Mat4^ out, System::Double rad)
    {
        mbgl::matrix::rotate_z(*out->NativePointer, *out->NativePointer, rad);
    }

    System::Void Mat4::RotateZ(Mat4^ out, Mat4^ a, System::Double rad)
    {
        mbgl::matrix::rotate_z(*out->NativePointer, *a->NativePointer, rad);
    }

    System::Void Mat4::Scale(Mat4^ out, System::Double x, System::Double y, System::Double z)
    {
        mbgl::matrix::scale(*out->NativePointer, *out->NativePointer, x, y, z);
    }

    System::Void Mat4::Scale(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z)
    {
        mbgl::matrix::scale(*out->NativePointer, *a->NativePointer, x, y, z);
    }

    System::Void Mat4::Multiply(Mat4^ out, Mat4^ a)
    {
        mbgl::matrix::multiply(*out->NativePointer, *out->NativePointer, *a->NativePointer);
    }

    System::Void Mat4::Multiply(Mat4^ out, Mat4^ a, Mat4^ b)
    {
        mbgl::matrix::multiply(*out->NativePointer, *a->NativePointer, *b->NativePointer);
    }

    System::Void MatrixExtensions::Identity(Mat4^ out)
    {
        Mat4::Identity(out);
    }

    System::Boolean MatrixExtensions::Invert(Mat4^ out)
    {
        return Mat4::Invert(out);
    }

    System::Boolean MatrixExtensions::Invert(Mat4^ out, Mat4^ a)
    {
        return Mat4::Invert(out, a);
    }

    System::Void MatrixExtensions::Ortho(Mat4^ out, System::Double left, System::Double right, System::Double bottom, System::Double top, System::Double near, System::Double far)
    {
        Mat4::Ortho(out, left, right, bottom, top, near, far);
    }

    System::Void MatrixExtensions::Perspective(Mat4^ out, System::Double fovy, System::Double aspect, System::Double near, System::Double far)
    {
        Mat4::Perspective(out, fovy, aspect, near, far);
    }

    System::Void MatrixExtensions::Copy(Mat4^ out, Mat4^ a)
    {
        Mat4::Copy(out, a);
    }

    System::Void MatrixExtensions::Translate(Mat4^ out, System::Double x, System::Double y, System::Double z)
    {
        Mat4::Translate(out, x, y, z);
    }

    System::Void MatrixExtensions::Translate(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z)
    {
        Mat4::Translate(out, a, x, y, z);
    }

    System::Void MatrixExtensions::RotateX(Mat4^ out, System::Double rad)
    {
        Mat4::RotateX(out, rad);
    }

    System::Void MatrixExtensions::RotateX(Mat4^ out, Mat4^ a, System::Double rad)
    {
        Mat4::RotateX(out, a, rad);
    }

    System::Void MatrixExtensions::RotateY(Mat4^ out, System::Double rad)
    {
        Mat4::RotateY(out, rad);
    }

    System::Void MatrixExtensions::RotateY(Mat4^ out, Mat4^ a, System::Double rad)
    {
        Mat4::RotateY(out, a, rad);
    }

    System::Void MatrixExtensions::RotateZ(Mat4^ out, System::Double rad)
    {
        Mat4::RotateZ(out, rad);
    }

    System::Void MatrixExtensions::RotateZ(Mat4^ out, Mat4^ a, System::Double rad)
    {
        Mat4::RotateZ(out, a, rad);
    }

    System::Void MatrixExtensions::Scale(Mat4^ out, System::Double x, System::Double y, System::Double z)
    {
        Mat4::Scale(out, x, y, z);
    }

    System::Void MatrixExtensions::Scale(Mat4^ out, Mat4^ a, System::Double x, System::Double y, System::Double z)
    {
        Mat4::Scale(out, a, x, y, z);
    }

    System::Void MatrixExtensions::Multiply(Mat4^ out, Mat4^ a)
    {
        Mat4::Multiply(out, a);
    }

    System::Void MatrixExtensions::Multiply(Mat4^ out, Mat4^ a, Mat4^ b)
    {
        Mat4::Multiply(out, a, b);
    }

    System::Void MatrixExtensions::TransformMat4(Vec4^ out, Mat4^ m)
    {
        Vec4::TransformMat4(out, m);
    }

    System::Void MatrixExtensions::TransformMat4(Vec4^ out, Vec4^ a, Mat4^ m)
    {
        Vec4::TransformMat4(out, a, m);
    }
}
