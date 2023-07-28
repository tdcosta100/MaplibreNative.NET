#pragma once
#include "Image.h"
#include "NativeWrapper.h"
#include "Point.h"
#include "RendererFrontend.h"

namespace mbgl
{
    class HeadlessFrontend;
}

namespace DOTNET_NAMESPACE
{
    ref class CameraOptions;
    ref class LatLng;
    ref class Map;
    ref class PremultipliedImage;
    ref class Renderer;
    ref class RendererBackend;
    ref class RenderingStats;
    ref class Size;
    ref class TransformState;

    using CameraOptions_ = CameraOptions;
    using Renderer_ = Renderer;
    using Size_ = Size;
    using TransformState_ = TransformState;

    /// <summary>
    /// Common headless backend interface, provides HeadlessBackend backend factory
    /// and enables extending gfx::Renderable with platform specific implementation
    /// of <see cref="ReadStillImage"/>.
    /// </summary>
    public ref class HeadlessFrontend : NativeWrapper<mbgl::HeadlessFrontend>, IRendererFrontend
    {
    public:
        enum class SwapBehaviour
        {
            NoFlush,
            Flush
        };

        value struct RenderResult
        {
            property PremultipliedImage^ Image;
            property RenderingStats^ Stats;
        };

        HeadlessFrontend();
        HeadlessFrontend(Size_^ size);
        HeadlessFrontend(Size_^ size, System::Single pixelRatio);
        ~HeadlessFrontend();

        virtual System::Void Reset();
        virtual System::Void SetObserver(RendererObserver^ observer);
        virtual System::Void Update(UpdateParameters^ parameters);
        virtual System::IntPtr GetNativePointer();

        System::Boolean HasImage(System::String^ id);
        System::Boolean HasLayer(System::String^ id);
        System::Boolean HasSource(System::String^ id);

        ScreenCoordinate PixelForLatLng(LatLng^ coordinate);
        LatLng^ LatLngForPixel(ScreenCoordinate point);

        PremultipliedImage^ ReadStillImage();
        RenderResult Render(Map^ map);
        System::Void RenderOnce(Map^ map);

        property System::Double FrameTime { System::Double get(); }
        property Size_^ Size { Size_^ get(); System::Void set(Size_^ value); }
        property Renderer_^ Renderer { Renderer_^ get(); }
        property CameraOptions_^ CameraOptions { CameraOptions_^ get(); }
        property TransformState_^ TransformState { TransformState_^ get(); }
    internal:
        HeadlessFrontend(NativePointerHolder<mbgl::HeadlessFrontend>^ nativePointerHolder);
    private:
        System::Void ResetInThread();
        System::Void UpdateInThread(UpdateParameters^ parameters);

        PremultipliedImage^ ReadStillImageInThread();
        RenderResult RenderInThread(Map^ map);
        System::Void RenderOnceInThread(Map^ map);
        System::Void SetSizeInThread(Size_^ value);
    };
}
