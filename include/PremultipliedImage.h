#pragma once
#include "Image.h"

namespace DOTNET_NAMESPACE
{
    public ref class PremultipliedImage : BasePremultipliedImage
    {
    public:
        PremultipliedImage();
        PremultipliedImage(Size_^ size);
        PremultipliedImage(Size_^ size, cli::array<System::Byte>^ srcData);
        ~PremultipliedImage();

        PremultipliedImage^ Clone();
        UnassociatedImage^ Unpremultiply();

        /// <summary>
        /// Clears the rect area specified by <paramref name="pt"/> and <paramref name="size"/> from <paramref name="dstImg"/>.
        /// </summary>
        /// <param name="dstImg"></param>
        /// <param name="pt"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        static System::Void Clear(PremultipliedImage^ dstImg, PointUInt pt, Size_^ size);

        /// <summary>
        /// Copy image data at <paramref name="srcPt"/> within <paramref name="size"/> from <paramref name="srcImg"/> to the rectangle of the same
        /// size at <paramref name="dstPt"/> in <paramref name="dstImg"/>.
        /// </summary>
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
        static System::Void Copy(PremultipliedImage^ srcImg, PremultipliedImage^ dstImg, PointUInt srcPt, PointUInt dstPt, Size_^ size);
        
        static PremultipliedImage^ DecodeImage(System::String^ data);
        static cli::array<System::Byte>^ EncodePNG(PremultipliedImage^ image);
    internal:
        PremultipliedImage(NativePointerHolder<mbgl::PremultipliedImage>^ nativePointerHolder);
    };
}
