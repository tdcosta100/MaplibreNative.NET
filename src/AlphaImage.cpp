#include "AlphaImage.h"
#include "Convert.h"

namespace DOTNET_NAMESPACE
{
    AlphaImage::AlphaImage() : BaseAlphaImage()
    {
    }

    AlphaImage::AlphaImage(Size_^ size) : BaseAlphaImage(size)
    {
    }

    AlphaImage::AlphaImage(Size_^ size, cli::array<System::Byte>^ srcData) : BaseAlphaImage(size, srcData)
    {
    }

    AlphaImage::AlphaImage(NativePointerHolder<mbgl::AlphaImage>^ nativePointerHolder) : BaseAlphaImage(nativePointerHolder)
    {
    }

    AlphaImage::~AlphaImage()
    {
    }

    AlphaImage^ AlphaImage::Clone()
    {
        return BaseAlphaImage::Clone();
    }

    System::Void AlphaImage::Clear(AlphaImage^ dstImg, PointUInt pt, Size_^ size)
    {
        BaseAlphaImage::Clear(dstImg, pt, size);
    }

    System::Void AlphaImage::Copy(AlphaImage^ srcImg, AlphaImage^ dstImg, PointUInt srcPt, PointUInt dstPt, Size_^ size)
    {
        BaseAlphaImage::Copy(srcImg, dstImg, srcPt, dstPt, size);
    }
}
