#include "CameraOptions.h"
#include "Convert.h"
#include "HeadlessFrontend.h"
#include "LatLng.h"
#include "Map.h"
#include "Point.h"
#include "PremultipliedImage.h"
#include "Renderer.h"
#include "RendererObserver.h"
#include "RenderingStats.h"
#include "Size.h"
#include "TransformState.h"
#include "UpdateParameters.h"
#include <mbgl/gfx/headless_frontend.hpp>
#include <mbgl/map/map.hpp>
#include <mbgl/renderer/renderer.hpp>
#include <mbgl/renderer/update_parameters.hpp>

namespace DOTNET_NAMESPACE
{
    HeadlessFrontend::HeadlessFrontend() : HeadlessFrontend(gcnew Size_(512, 512))
    {
    }
    
    HeadlessFrontend::HeadlessFrontend(Size_^ size) : HeadlessFrontend(size, 1.0f)
    {
    }
    
    HeadlessFrontend::HeadlessFrontend(Size_^ size, System::Single pixelRatio)
        : NativeWrapper(new mbgl::HeadlessFrontend(*size->NativePointer, pixelRatio))
    {
    }

    HeadlessFrontend::HeadlessFrontend(NativePointerHolder<mbgl::HeadlessFrontend>^ nativePointerHolder)
        : NativeWrapper(nativePointerHolder)
    {
    }

    HeadlessFrontend::~HeadlessFrontend()
    {
    }

    System::Void HeadlessFrontend::Reset()
    {
        NativePointer->reset();
    }

    System::Void HeadlessFrontend::SetObserver(RendererObserver^ observer)
    {
        NativePointer->setObserver(*observer->NativePointer);
    }

    System::Void HeadlessFrontend::Update(UpdateParameters^ parameters)
    {
        NativePointer->update(*parameters->NativePointer);
    }

    System::IntPtr HeadlessFrontend::GetNativePointer()
    {
        return System::IntPtr(NativePointer);
    }

    System::Boolean HeadlessFrontend::HasImage(System::String^ id)
    {
        return NativePointer->hasImage(Convert::ToStdString(id));
    }

    System::Boolean HeadlessFrontend::HasLayer(System::String^ id)
    {
        return NativePointer->hasLayer(Convert::ToStdString(id));
    }

    System::Boolean HeadlessFrontend::HasSource(System::String^ id)
    {
        return NativePointer->hasSource(Convert::ToStdString(id));
    }

    ScreenCoordinate HeadlessFrontend::PixelForLatLng(LatLng^ coordinate)
    {
        return ScreenCoordinate(NativePointer->pixelForLatLng(*coordinate->NativePointer));
    }

    LatLng^ HeadlessFrontend::LatLngForPixel(ScreenCoordinate point)
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->latLngForPixel(mbgl::ScreenCoordinate(point.X, point.Y))));
    }

    PremultipliedImage^ HeadlessFrontend::ReadStillImage()
    {
        return gcnew PremultipliedImage(PremultipliedImage::CreateNativePointerHolder(NativePointer->readStillImage()));
    }

    HeadlessFrontend::RenderResult HeadlessFrontend::Render(Map^ map)
    {
        mbgl::HeadlessFrontend::RenderResult nativeResult = NativePointer->render(*map->NativePointer);

        RenderResult result;
        result.Image = gcnew PremultipliedImage(PremultipliedImage::CreateNativePointerHolder(std::move(nativeResult.image)));
        result.Stats = gcnew RenderingStats(RenderingStats::CreateNativePointerHolder(nativeResult.stats));

        return result;
    }

    System::Void HeadlessFrontend::RenderOnce(Map^ map)
    {
        NativePointer->renderOnce(*map->NativePointer);
    }

    System::Double HeadlessFrontend::FrameTime::get()
    {
        return NativePointer->getFrameTime();
    }

    Size_^ HeadlessFrontend::Size::get()
    {
        return gcnew Size_(Size_::CreateNativePointerHolder(NativePointer->getSize()));
    }

    System::Void HeadlessFrontend::Size::set(Size_^ value)
    {
        NativePointer->setSize(*value->NativePointer);
    }
    
    Renderer_^ HeadlessFrontend::Renderer::get()
    {
        return gcnew Renderer_(Renderer_::CreateNativePointerHolder(NativePointer->getRenderer()));
    }

    CameraOptions_^ HeadlessFrontend::CameraOptions::get()
    {
        return gcnew CameraOptions_(CameraOptions_::CreateNativePointerHolder(NativePointer->getCameraOptions()));
    }

    TransformState_^ HeadlessFrontend::TransformState::get()
    {
        if (NativePointer->getTransformState().has_value())
        {
            return gcnew TransformState_(TransformState_::CreateNativePointerHolder(NativePointer->getTransformState().value()));
        }

        return nullptr;
    }
}
