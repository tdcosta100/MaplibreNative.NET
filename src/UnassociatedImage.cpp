#include "PremultipliedImage.h"
#include "UnassociatedImage.h"
#include <mbgl/util/premultiply.hpp>

namespace DOTNET_NAMESPACE
{
    UnassociatedImage::UnassociatedImage() : BaseUnassociatedImage()
    {
    }

    UnassociatedImage::UnassociatedImage(Size_^ size) : BaseUnassociatedImage(size)
    {
    }

    UnassociatedImage::UnassociatedImage(Size_^ size, cli::array<System::Byte>^ srcData) : BaseUnassociatedImage(size, srcData)
    {
    }

    UnassociatedImage::UnassociatedImage(NativePointerHolder<mbgl::UnassociatedImage>^ nativePointerHolder) : BaseUnassociatedImage(nativePointerHolder)
    {
    }

    UnassociatedImage::~UnassociatedImage()
    {
    }

    UnassociatedImage^ UnassociatedImage::Clone()
    {
        return BaseUnassociatedImage::Clone();
    }

    PremultipliedImage^ UnassociatedImage::Premultiply()
    {
        return gcnew PremultipliedImage(PremultipliedImage::CreateNativePointerHolder(mbgl::util::premultiply(NativePointer->clone())));
    }

    System::Void UnassociatedImage::Clear(UnassociatedImage^ dstImg, PointUInt pt, Size_^ size)
    {
        BaseUnassociatedImage::Clear(dstImg, pt, size);
    }

    System::Void UnassociatedImage::Copy(UnassociatedImage^ srcImg, UnassociatedImage^ dstImg, PointUInt srcPt, PointUInt dstPt, Size_^ size)
    {
        BaseUnassociatedImage::Copy(srcImg, dstImg, srcPt, dstPt, size);
    }
}
