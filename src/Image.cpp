#include "Image.h"
#include "AlphaImage.h"
#include "PremultipliedImage.h"
#include "UnassociatedImage.h"

namespace DOTNET_NAMESPACE
{
    template <ImageAlphaMode Mode>
    template <typename T>
    T^ ImageBase<Mode>::Clone()
    {
        return gcnew T(T::CreateNativePointerHolder(NativePointer->clone()));
    }

    template <ImageAlphaMode Mode>
    template <typename T>
    System::Void ImageBase<Mode>::Clear(T^ dstImg, Point<System::UInt32> pt, Size_^ size)
    {
        mbgl::Image<(mbgl::ImageAlphaMode)Mode>::clear(
            *dstImg->NativePointer,
            mbgl::Point<uint32_t>(pt.X, pt.Y),
            *size->NativePointer
        );
    }

    template <ImageAlphaMode Mode>
    template <typename T>
    System::Void ImageBase<Mode>::Copy(T^ srcImg, T^ dstImg, Point<System::UInt32> srcPt, Point<System::UInt32> dstPt, Size_^ size)
    {
        mbgl::Image<(mbgl::ImageAlphaMode)Mode>::copy(
            *srcImg->NativePointer,
            *dstImg->NativePointer,
            mbgl::Point<uint32_t>(srcPt.X, srcPt.Y),
            mbgl::Point<uint32_t>(dstPt.X, dstPt.Y),
            *size->NativePointer
        );
    }

    template AlphaImage^ BaseAlphaImage::Clone();
    template System::Void BaseAlphaImage::Clear(AlphaImage^ dstImg, Point<System::UInt32> pt, Size_^ size);
    template System::Void BaseAlphaImage::Copy(AlphaImage^ srcImg, AlphaImage^ dstImg, Point<System::UInt32> srcPt, Point<System::UInt32> dstPt, Size_^ size);
    
    template PremultipliedImage^ BasePremultipliedImage::Clone();
    template System::Void BasePremultipliedImage::Clear(PremultipliedImage^ dstImg, Point<System::UInt32> pt, Size_^ size);
    template System::Void BasePremultipliedImage::Copy(PremultipliedImage^ srcImg, PremultipliedImage^ dstImg, Point<System::UInt32> srcPt, Point<System::UInt32> dstPt, Size_^ size);
    
    template UnassociatedImage^ BaseUnassociatedImage::Clone();
    template System::Void BaseUnassociatedImage::Clear(UnassociatedImage^ dstImg, Point<System::UInt32> pt, Size_^ size);
    template System::Void BaseUnassociatedImage::Copy(UnassociatedImage^ srcImg, UnassociatedImage^ dstImg, Point<System::UInt32> srcPt, Point<System::UInt32> dstPt, Size_^ size);

}
