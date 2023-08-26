#include "AnimationOptions.h"
#include "BoundOptions.h"
#include "CameraOptions.h"
#include "ClientOptions.h"
#include "EdgeInsets.h"
#include "FreeCameraOptions.h"
#include "Map.h"
#include "MapObserver.h"
#include "MapOptions.h"
#include "ProjectionMode.h"
#include "RendererFrontend.h"
#include "ResourceOptions.h"
#include "Size.h"
#include "Style.h"
#include "TransformState.h"
#include <mbgl/gfx/headless_frontend.hpp>
#include <mbgl/map/map.hpp>
#include <mbgl/map/transform_state.hpp>
#include <mbgl/style/style.hpp>

namespace
{
    using namespace ::DOTNET_NAMESPACE;
    
    void StillImageCallbackHandler(std::exception_ptr eptr, Map::StillImageCallback^ callback)
    {
        msclr::gcroot<System::Exception^> exception = nullptr;

        if (eptr)
        {
            try
            {
                std::rethrow_exception(eptr);
            }
            catch (const std::exception& ex)
            {
                exception = gcnew System::Exception(Convert::ToSystemString(ex.what()));
            }
        }

        callback->Invoke(exception);
    }
}

namespace DOTNET_NAMESPACE
{
    Map::Map(IRendererFrontend^ frontend) : Map(frontend, gcnew MapObserver())
    {
    }

    Map::Map(IRendererFrontend^ frontend, MapObserver^ observer) : Map(frontend, observer, gcnew MapOptions_())
    {
    }

    Map::Map(IRendererFrontend^ frontend, MapObserver^ observer, MapOptions_^ mapOptions) : Map(frontend, observer, mapOptions, ResourceOptions::Default())
    {
    }

    Map::Map(IRendererFrontend^ frontend, MapObserver^ observer, MapOptions_^ mapOptions, ResourceOptions^ resourceOptions)
        :
        _Observer(observer),
        _MapOptions(mapOptions),
        _ResourceOptions(resourceOptions),
        NativeWrapper(new mbgl::Map(
            *reinterpret_cast<mbgl::RendererFrontend*>(frontend->GetNativePointer().ToPointer()),
            *_Observer->NativePointer,
            *_MapOptions->NativePointer,
            *_ResourceOptions->NativePointer
        ))
    {
    }

    Map::Map(IRendererFrontend^ frontend, MapObserver^ observer, MapOptions_^ mapOptions, ResourceOptions^ resourceOptions, ClientOptions^ clientOptions)
        :
        _Observer(observer),
        _MapOptions(mapOptions),
        _ResourceOptions(resourceOptions),
        _ClientOptions(clientOptions),
        NativeWrapper(new mbgl::Map(
            *reinterpret_cast<mbgl::RendererFrontend*>(frontend->GetNativePointer().ToPointer()),
            *_Observer->NativePointer,
            *_MapOptions->NativePointer,
            *_ResourceOptions->NativePointer,
            *_ClientOptions->NativePointer
        ))
    {
    }

    Map::~Map()
    {
    }

    System::Void Map::RenderStill(StillImageCallback^ callback)
    {
        NativePointer->renderStill(std::bind(
            &StillImageCallbackHandler,
            std::placeholders::_1,
            msclr::gcroot<StillImageCallback^>(callback)
        ));
    }

    System::Void Map::RenderStill(CameraOptions^ camera, MapDebugOptions debugOptions, StillImageCallback^ callback)
    {
        NativePointer->renderStill(
            *camera->NativePointer,
            (mbgl::MapDebugOptions)debugOptions,
            std::bind(
                &StillImageCallbackHandler,
                std::placeholders::_1,
                msclr::gcroot<StillImageCallback^>(callback)
            )
        );
    }

    System::Void Map::TriggerRepaint()
    {
        NativePointer->triggerRepaint();
    }

    System::Void Map::CancelTransitions()
    {
        NativePointer->cancelTransitions();
    }

    CameraOptions^ Map::GetCameraOptions()
    {
        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(NativePointer->getCameraOptions()));
    }

    CameraOptions^ Map::GetCameraOptions(EdgeInsets^ padding)
    {
        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(NativePointer->getCameraOptions(*padding->NativePointer)));
    }

    System::Void Map::JumpTo(CameraOptions^ camera)
    {
        NativePointer->jumpTo(*camera->NativePointer);
    }

    System::Void Map::EaseTo(CameraOptions^ camera, AnimationOptions^ animation)
    {
        NativePointer->easeTo(*camera->NativePointer, *animation->NativePointer);
    }

    System::Void Map::FlyTo(CameraOptions^ camera, AnimationOptions^ animation)
    {
        NativePointer->flyTo(*camera->NativePointer, *animation->NativePointer);
    }

    System::Void Map::MoveBy(ScreenCoordinate point)
    {
        NativePointer->moveBy(mbgl::ScreenCoordinate(point.X, point.Y));
    }

    System::Void Map::MoveBy(ScreenCoordinate point, AnimationOptions^ animation)
    {
        NativePointer->moveBy(mbgl::ScreenCoordinate(point.X, point.Y), *animation->NativePointer);
    }

    System::Void Map::ScaleBy(System::Double scale, System::Nullable<ScreenCoordinate> anchor)
    {
        NativePointer->scaleBy(
            scale,
            anchor.HasValue
            ?
            std::optional<mbgl::ScreenCoordinate>(mbgl::ScreenCoordinate(anchor.Value.X, anchor.Value.Y))
            :
            std::nullopt
        );
    }

    System::Void Map::ScaleBy(System::Double scale, System::Nullable<ScreenCoordinate> anchor, AnimationOptions^ animation)
    {
        NativePointer->scaleBy(
            scale,
            anchor.HasValue
            ?
            std::optional<mbgl::ScreenCoordinate>(mbgl::ScreenCoordinate(anchor.Value.X, anchor.Value.Y))
            :
            std::nullopt,
            *animation->NativePointer
        );
    }

    System::Void Map::PitchBy(System::Double pitch)
    {
        NativePointer->pitchBy(pitch);
    }

    System::Void Map::PitchBy(System::Double pitch, AnimationOptions^ animation)
    {
        NativePointer->pitchBy(pitch, *animation->NativePointer);
    }

    System::Void Map::RotateBy(ScreenCoordinate first, ScreenCoordinate second)
    {
        NativePointer->rotateBy(
            mbgl::ScreenCoordinate(first.X, first.Y),
            mbgl::ScreenCoordinate(second.X, second.Y)
        );
    }

    System::Void Map::RotateBy(ScreenCoordinate first, ScreenCoordinate second, AnimationOptions^ animation)
    {
        NativePointer->rotateBy(
            mbgl::ScreenCoordinate(first.X, first.Y),
            mbgl::ScreenCoordinate(second.X, second.Y),
            *animation->NativePointer
        );
    }

    CameraOptions^ Map::CameraForLatLngBounds(
        LatLngBounds^ bounds,
        EdgeInsets^ padding
    )
    {
        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(
            NativePointer->cameraForLatLngBounds(
                *bounds->NativePointer,
                *padding->NativePointer
            )
        ));
    }

    CameraOptions^ Map::CameraForLatLngBounds(
        LatLngBounds^ bounds,
        EdgeInsets^ padding,
        System::Nullable<System::Double> bearing
    )
    {
        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(
            NativePointer->cameraForLatLngBounds(
                *bounds->NativePointer,
                *padding->NativePointer,
                bearing.HasValue
                ?
                std::optional<double>(bearing.Value)
                :
                std::nullopt
            )
        ));
    }

    CameraOptions^ Map::CameraForLatLngBounds(
        LatLngBounds^ bounds,
        EdgeInsets^ padding,
        System::Nullable<System::Double> bearing,
        System::Nullable<System::Double> pitch
    )
    {
        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(
            NativePointer->cameraForLatLngBounds(
                *bounds->NativePointer,
                *padding->NativePointer,
                bearing.HasValue
                ?
                std::optional<double>(bearing.Value)
                :
                std::nullopt,
                pitch.HasValue
                ?
                std::optional<double>(pitch.Value)
                :
                std::nullopt
            )
        ));
    }

    CameraOptions^ Map::CameraForLatLngs(
        System::Collections::Generic::IEnumerable<LatLng^>^ latLngs,
        EdgeInsets^ padding
    )
    {
        std::vector<mbgl::LatLng> result;

        for each (LatLng^ latLng in latLngs)
        {
            result.emplace_back(*latLng->NativePointer);
        }
        
        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(
            NativePointer->cameraForLatLngs(
                result,
                *padding->NativePointer
            )
        ));
    }

    CameraOptions^ Map::CameraForLatLngs(
        System::Collections::Generic::IEnumerable<LatLng^>^ latLngs,
        EdgeInsets^ padding,
        System::Nullable<System::Double> bearing
    )
    {
        std::vector<mbgl::LatLng> result;

        for each (LatLng ^ latLng in latLngs)
        {
            result.emplace_back(*latLng->NativePointer);
        }

        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(
            NativePointer->cameraForLatLngs(
                result,
                *padding->NativePointer,
                bearing.HasValue
                ?
                std::optional<double>(bearing.Value)
                :
                std::nullopt
            )
        ));
    }

    CameraOptions^ Map::CameraForLatLngs(
        System::Collections::Generic::IEnumerable<LatLng^>^ latLngs,
        EdgeInsets^ padding,
        System::Nullable<System::Double> bearing,
        System::Nullable<System::Double> pitch
    )
    {
        std::vector<mbgl::LatLng> result;

        for each (LatLng ^ latLng in latLngs)
        {
            result.emplace_back(*latLng->NativePointer);
        }

        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(
            NativePointer->cameraForLatLngs(
                result,
                *padding->NativePointer,
                bearing.HasValue
                ?
                std::optional<double>(bearing.Value)
                :
                std::nullopt,
                pitch.HasValue
                ?
                std::optional<double>(pitch.Value)
                :
                std::nullopt
            )
        ));
    }

    LatLngBounds^ Map::LatLngBoundsForCamera(CameraOptions^ camera)
    {
        return gcnew LatLngBounds(LatLngBounds::CreateNativePointerHolder(NativePointer->latLngBoundsForCamera(*camera->NativePointer)));
    }

    LatLngBounds^ Map::LatLngBoundsForCameraUnwrapped(CameraOptions^ camera)
    {
        return gcnew LatLngBounds(LatLngBounds::CreateNativePointerHolder(NativePointer->latLngBoundsForCameraUnwrapped(*camera->NativePointer)));
    }

    System::Void Map::SetNorthOrientation(NorthOrientation orientation)
    {
        NativePointer->setNorthOrientation((mbgl::NorthOrientation)orientation);
    }

    System::Void Map::SetConstrainMode(ConstrainMode mode)
    {
        NativePointer->setConstrainMode((mbgl::ConstrainMode)mode);
    }

    System::Void Map::SetViewportMode(ViewportMode mode)
    {
        NativePointer->setViewportMode((mbgl::ViewportMode)mode);
    }

    System::Void Map::SetSize(Size^ size)
    {
        NativePointer->setSize(*size->NativePointer);
    }

    ScreenCoordinate Map::PixelForLatLng(LatLng^ latLng)
    {
        return ScreenCoordinate(NativePointer->pixelForLatLng(*latLng->NativePointer));
    }

    LatLng^ Map::LatLngForPixel(ScreenCoordinate pixel)
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->latLngForPixel(mbgl::ScreenCoordinate(pixel.X, pixel.Y))));
    }

    System::Collections::Generic::IEnumerable<ScreenCoordinate>^ Map::PixelsForLatLngs(System::Collections::Generic::IEnumerable<LatLng^>^ latLngs)
    {
        std::vector<mbgl::LatLng> nativeLatLngs;

        for each (LatLng^ latLng in latLngs)
        {
            nativeLatLngs.emplace_back(*latLng->NativePointer);
        }

        std::vector<mbgl::ScreenCoordinate> nativeResult = NativePointer->pixelsForLatLngs(nativeLatLngs);
        cli::array<ScreenCoordinate>^ result = gcnew cli::array<ScreenCoordinate>(static_cast<System::Int32>(nativeResult.size()));

        for (int i = 0; i < result->Length; i++)
        {
            result[i] = ScreenCoordinate(nativeResult[i].x, nativeResult[i].y);
        }

        return result;
    }

    System::Collections::Generic::IEnumerable<LatLng^>^ Map::LatLngsForPixels(System::Collections::Generic::IEnumerable<ScreenCoordinate>^ screenCoords)
    {
        std::vector<mbgl::ScreenCoordinate> nativeScreenCoords;

        for each (ScreenCoordinate pixel in screenCoords)
        {
            nativeScreenCoords.emplace_back(mbgl::ScreenCoordinate(pixel.X, pixel.Y));
        }

        std::vector<mbgl::LatLng> nativeResult = NativePointer->latLngsForPixels(nativeScreenCoords);
        cli::array<LatLng^>^ result = gcnew cli::array<LatLng^>(static_cast<System::Int32>(nativeResult.size()));

        for (int i = 0; i < result->Length; i++)
        {
            result[i] = gcnew LatLng(LatLng::CreateNativePointerHolder(nativeResult[i]));
        }

        return result;
    }

    System::Void Map::DumpDebugLogs()
    {
        NativePointer->dumpDebugLogs();
    }

    Style_^ Map::Style::get()
    {
        if (!_Style)
        {
            _Style = gcnew Style_(Style_::CreateNativePointerHolder(&NativePointer->getStyle(), false));
        }
        
        return _Style;
    }

    System::Void Map::Style::set(Style_^ value)
    {
        _Style = value;
        NativePointer->setStyle(std::unique_ptr<mbgl::style::Style>(value->NativePointer));
    }

    System::Boolean Map::IsGestureInProgress::get()
    {
        return NativePointer->isGestureInProgress();
    }

    System::Void Map::IsGestureInProgress::set(System::Boolean value)
    {
        NativePointer->setGestureInProgress(value);
    }

    System::Boolean Map::IsRotating::get()
    {
        return NativePointer->isRotating();
    }

    System::Boolean Map::IsScaling::get()
    {
        return NativePointer->isScaling();
    }

    System::Boolean Map::IsPanning::get()
    {
        return NativePointer->isPanning();
    }

    BoundOptions^ Map::Bounds::get()
    {
        return gcnew BoundOptions(BoundOptions::CreateNativePointerHolder(NativePointer->getBounds()));
    }

    System::Void Map::Bounds::set(BoundOptions^ value)
    {
        NativePointer->setBounds(*value->NativePointer);
    }

    MapOptions_^ Map::MapOptions::get()
    {
        return _MapOptions;
    }

    ProjectionMode_^ Map::ProjectionMode::get()
    {
        return gcnew ProjectionMode_(ProjectionMode_::CreateNativePointerHolder(NativePointer->getProjectionMode()));
    }

    System::Void Map::ProjectionMode::set(ProjectionMode_^ value)
    {
        NativePointer->setProjectionMode(*value->NativePointer);
    }

    TransformState_^ Map::TransformState::get()
    {
        return gcnew TransformState_(TransformState_::CreateNativePointerHolder(NativePointer->getTransfromState()));
    }

    System::Byte Map::PrefetchZoomDelta::get()
    {
        return NativePointer->getPrefetchZoomDelta();
    }

    System::Void Map::PrefetchZoomDelta::set(System::Byte value)
    {
        NativePointer->setPrefetchZoomDelta(value);
    }

    MapDebugOptions Map::Debug::get()
    {
        return (MapDebugOptions)NativePointer->getDebug();
    }

    System::Void Map::Debug::set(MapDebugOptions value)
    {
        NativePointer->setDebug((mbgl::MapDebugOptions)value);
    }

    System::Boolean Map::IsFullyLoaded::get()
    {
        return NativePointer->isFullyLoaded();
    }

    FreeCameraOptions_^ Map::FreeCameraOptions::get()
    {
        return gcnew FreeCameraOptions_(FreeCameraOptions_::CreateNativePointerHolder(NativePointer->getFreeCameraOptions()));
    }

    System::Void Map::FreeCameraOptions::set(FreeCameraOptions_^ value)
    {
        NativePointer->setFreeCameraOptions(*value->NativePointer);
    }
}
