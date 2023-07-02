#pragma once
#include "Image.h"

namespace DOTNET_NAMESPACE
{
    ref class Size;

    public ref class AlphaImage : BaseAlphaImage
    {
    public:
        AlphaImage();
        AlphaImage(Size_^ size);
        AlphaImage(Size_^ size, cli::array<System::Byte>^ srcData);
        ~AlphaImage();

        AlphaImage^ Clone();

        /// <summary>
        /// Clears the rect area specified by <paramref name="pt"/> and <paramref name="size"/> from <paramref name="dstImg"/>.
        /// </summary>
        /// <param name="dstImg"></param>
        /// <param name="pt"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        static System::Void Clear(AlphaImage^ dstImg, Point<System::UInt32> pt, Size_^ size);

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
        static System::Void Copy(AlphaImage^ srcImg, AlphaImage^ dstImg, Point<System::UInt32> srcPt, Point<System::UInt32> dstPt, Size_^ size);
    internal:
        AlphaImage(NativePointerHolder<mbgl::AlphaImage>^ nativePointerHolder);
    };
}
