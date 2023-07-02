#pragma once
#include "Convert.h"
#include "NativeWrapper.h"
#include "Size.h"
#include <mbgl/util/image.hpp>

namespace DOTNET_NAMESPACE
{
    public enum class ImageAlphaMode
    {
        Unassociated,
        Premultiplied,

        /// <summary>
        /// Alpha-channel only
        /// </summary>
        Exclusive
    };

    ref class AlphaImage;
    ref class PremultipliedImage;
    ref class UnassociatedImage;

    using Size_ = Size;

    template <ImageAlphaMode Mode>
    struct ImageAlphaModeToType { using Type = PremultipliedImage; };

    template<>
    struct ImageAlphaModeToType<ImageAlphaMode::Exclusive> { using Type = AlphaImage; };

    template<>
    struct ImageAlphaModeToType<ImageAlphaMode::Unassociated> { using Type = UnassociatedImage; };

    template <ImageAlphaMode Mode = ImageAlphaMode::Premultiplied>
    public ref class ImageBase : NativeWrapper<mbgl::Image<(mbgl::ImageAlphaMode)Mode>>
    {
    public:
        ImageBase() : NativeWrapper(CreateImage())
        {
        }

        ImageBase(Size_^ size) : NativeWrapper(CreateImage(size))
        {
        }
        
        ImageBase(Size_^ size, cli::array<System::Byte>^ srcData) : NativeWrapper(CreateImage(size, srcData))
        {
        }
        
        virtual ~ImageBase()
        {
        }

        template<typename T = ImageAlphaModeToType<Mode>::Type>
        T^ Clone();

        System::Void Fill(System::Byte value)
        {
            NativePointer->fill(value);
        }

        System::Void Resize(Size_^ size)
        {
            NativePointer->resize(*size->NativePointer);
        }

        cli::array<System::Byte>^ Data()
        {
            cli::array<System::Byte>^ result = gcnew cli::array<System::Byte>(static_cast<System::Int32>(NativePointer->bytes()));

            System::Runtime::InteropServices::Marshal::Copy(System::IntPtr(NativePointer->data.get()), result, 0, result->Length);
            
            return result;
        }

        property System::Boolean Valid
        {
            System::Boolean get()
            {
                return NativePointer->valid();
            }
        }

        property System::UInt64 Stride
        {
            System::UInt64 get()
            {
                return NativePointer->stride();
            }
        }

        property System::UInt64 Bytes
        {
            System::UInt64 get()
            {
                return NativePointer->bytes();
            }
        }

        property Size_^ Size
        {
            Size_^ get()
            {
                return gcnew Size_(Size_::CreateNativePointerHolder(NativePointer->size));
            }
        }

        property System::Int64 Channels
        {
            System::Int64 get()
            {
                return NativePointer->channels;
            }
        }

        System::Boolean operator==(ImageBase<Mode>^ rhs)
        {
            return *NativePointer == *rhs->NativePointer;
        }

        System::Boolean operator!=(ImageBase<Mode>^ rhs)
        {
            return *NativePointer != *rhs->NativePointer;
        }

        /// <summary>
        /// Clears the rect area specified by <paramref name="pt"/> and <paramref name="size"/> from <paramref name="dstImg"/>.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="dstImg"></param>
        /// <param name="pt"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        template <typename T = ImageAlphaModeToType<Mode>::Type>
        static System::Void Clear(T^ dstImg, Point<System::UInt32> pt, Size_^ size);

        /// <summary>
        /// Copy image data at <paramref name="srcPt"/> within <paramref name="size"/> from <paramref name="srcImg"/> to the rectangle of the same
        /// size at <paramref name="dstPt"/> in <paramref name="dstImg"/>.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="srcImg"></param>
        /// <param name="dstImg"></param>
        /// <param name="srcPt"></param>
        /// <param name="dstPt"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        /// <exception cref="System::Exception">
        /// Thrown if the specified bounds exceed the bounds of the
        /// source or destination. Must not be used to
        /// move data within a single Image.
        /// </exception>
        template <typename T = ImageAlphaModeToType<Mode>::Type>
        static System::Void Copy(T^ srcImg, T^ dstImg, Point<System::UInt32> srcPt, Point<System::UInt32> dstPt, Size_^ size);
    internal:
        ImageBase(NativePointerHolder<mbgl::Image<(mbgl::ImageAlphaMode)Mode>>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
        {
        }
    private:
        static mbgl::Image<(mbgl::ImageAlphaMode)Mode>* CreateImage()
        {
            try
            {
                return new mbgl::Image<(mbgl::ImageAlphaMode)Mode>();
            }
            catch (const std::exception& ex)
            {
                throw gcnew System::Exception(Convert::ToSystemString(std::string(ex.what())));
            }
        }

        static mbgl::Image<(mbgl::ImageAlphaMode)Mode>* CreateImage(Size_^ size)
        {
            try
            {
                return new mbgl::Image<(mbgl::ImageAlphaMode)Mode>(*size->NativePointer);
            }
            catch (const std::exception& ex)
            {
                throw gcnew System::Exception(Convert::ToSystemString(std::string(ex.what())));
            }
        }

        static mbgl::Image<(mbgl::ImageAlphaMode)Mode>* CreateImage(Size_^ size, cli::array<System::Byte>^ srcData)
        {
            try
            {
                std::vector<uint8_t> nativeSrcData(srcData->Length);
                System::Runtime::InteropServices::Marshal::Copy(srcData, 0, System::IntPtr(nativeSrcData.data()), srcData->Length);
                return new mbgl::Image<(mbgl::ImageAlphaMode)Mode>(*size->NativePointer, nativeSrcData.data(), srcData->Length);
            }
            catch (const std::invalid_argument& ex)
            {
                throw gcnew System::ArgumentException(Convert::ToSystemString(std::string(ex.what())));
            }
            catch (const std::exception& ex)
            {
                throw gcnew System::Exception(Convert::ToSystemString(std::string(ex.what())));
            }
        }
    };

    template ref class ImageBase<ImageAlphaMode::Exclusive>;
    template ref class ImageBase<ImageAlphaMode::Premultiplied>;
    template ref class ImageBase<ImageAlphaMode::Unassociated>;

    using BaseAlphaImage = ImageBase<ImageAlphaMode::Exclusive>;
    using BasePremultipliedImage = ImageBase<ImageAlphaMode::Premultiplied>;
    using BaseUnassociatedImage = ImageBase<ImageAlphaMode::Unassociated>;
}
