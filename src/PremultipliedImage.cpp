#include "PremultipliedImage.h"
#include "UnassociatedImage.h"
#include <mbgl/util/premultiply.hpp>

namespace DOTNET_NAMESPACE
{
    PremultipliedImage::PremultipliedImage() : ImageBase()
    {
    }

    PremultipliedImage::PremultipliedImage(Size_^ size) : ImageBase(size)
    {
    }

    PremultipliedImage::PremultipliedImage(Size_^ size, cli::array<System::Byte>^ srcData) : ImageBase(size, srcData)
    {
    }

    PremultipliedImage::PremultipliedImage(NativePointerHolder<mbgl::PremultipliedImage>^ nativePointerHolder) : ImageBase(nativePointerHolder)
    {
    }

    PremultipliedImage::~PremultipliedImage()
    {
    }

    PremultipliedImage^ PremultipliedImage::Clone()
    {
        return BasePremultipliedImage::Clone();
    }

    UnassociatedImage^ PremultipliedImage::Unpremultiply()
    {
        return gcnew UnassociatedImage(UnassociatedImage::CreateNativePointerHolder(mbgl::util::unpremultiply(NativePointer->clone())));
    }

    System::Void PremultipliedImage::Clear(PremultipliedImage^ dstImg, Point<System::UInt32> pt, Size_^ size)
    {
        BasePremultipliedImage::Clear(dstImg, pt, size);
    }

    System::Void PremultipliedImage::Copy(PremultipliedImage^ srcImg, PremultipliedImage^ dstImg, Point<System::UInt32> srcPt, Point<System::UInt32> dstPt, Size_^ size)
    {
        BasePremultipliedImage::Copy(srcImg, dstImg, srcPt, dstPt, size);
    }

    PremultipliedImage^ PremultipliedImage::DecodeImage(System::String^ data)
    {
        return gcnew PremultipliedImage(PremultipliedImage::CreateNativePointerHolder(mbgl::decodeImage(Convert::ToStdString(data))));
    }

    cli::array<System::Byte>^ PremultipliedImage::EncodePNG(PremultipliedImage^ image)
    {
        std::string nativeResult = mbgl::encodePNG(*image->NativePointer);
        cli::array<System::Byte>^ result = gcnew cli::array<System::Byte>(static_cast<System::Int32>(nativeResult.size()));

        System::Runtime::InteropServices::Marshal::Copy(System::IntPtr(const_cast<char*>(nativeResult.c_str())), result, 0, result->Length);

        return result;
    }
}
