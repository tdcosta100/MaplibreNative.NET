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
#include "RunLoop.h"
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
    
    mbgl::Map* Create(
        mbgl::RendererFrontend& frontend,
        mbgl::MapObserver& observer,
        const mbgl::MapOptions& mapOptions,
        const mbgl::ResourceOptions& resourceOptions,
        const mbgl::ClientOptions& clientOptions = mbgl::ClientOptions()
    )
    {
        mbgl::Map* result = nullptr;

        std::mutex mutex;
        std::condition_variable condition_variable;

        RunLoop::Get()->NativePointer->ExecuteInThread(
            [&mutex, &condition_variable, &frontend, &observer, &mapOptions, &resourceOptions, &clientOptions, &result]
            {
                std::unique_lock<std::mutex> lock(mutex);
                result = new mbgl::Map(frontend, observer, mapOptions, resourceOptions, clientOptions);
                lock.unlock();
                condition_variable.notify_all();
            }
        );

        std::unique_lock<std::mutex> lock(mutex);
        condition_variable.wait(lock, [&result] { return result != nullptr; });
        lock.unlock();

        return result;
    }

    void Destroy(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<NativePointerHolder<mbgl::Map>^> pointerHolder
    )
    {
        delete pointerHolder;
        taskCompletionSource->SetResult(true);
    }

    void SystemActionHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action^> action
    )
    {
        action->Invoke();
        taskCompletionSource->SetResult(true);
    }

    void RenderStillHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<Map::StillImageCallback^>^> action,
        msclr::gcroot<Map::StillImageCallback^> callback
    )
    {
        action->Invoke(callback);
        taskCompletionSource->SetResult(true);
    }

    void RenderStillHelper2(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<CameraOptions^, MapDebugOptions, Map::StillImageCallback^>^> action,
        msclr::gcroot<CameraOptions^> camera,
        msclr::gcroot<MapDebugOptions> debugOptions,
        msclr::gcroot<Map::StillImageCallback^> callback
    )
    {
        action->Invoke(camera, debugOptions, callback);
        taskCompletionSource->SetResult(true);
    }

    void JumpToHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<CameraOptions^>^> action,
        msclr::gcroot<CameraOptions^> camera
    )
    {
        action->Invoke(camera);
        taskCompletionSource->SetResult(true);
    }

    void EaseToFlyToHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<CameraOptions^, AnimationOptions^>^> action,
        msclr::gcroot<CameraOptions^> camera,
        msclr::gcroot<AnimationOptions^> animation
    )
    {
        action->Invoke(camera, animation);
        taskCompletionSource->SetResult(true);
    }

    void MoveByHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<ScreenCoordinate>^> action,
        msclr::gcroot<ScreenCoordinate> point
    )
    {
        action->Invoke(point);
        taskCompletionSource->SetResult(true);
    }

    void MoveByHelper2(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<ScreenCoordinate, AnimationOptions^>^> action,
        msclr::gcroot<ScreenCoordinate> point,
        msclr::gcroot<AnimationOptions^> animation
    )
    {
        action->Invoke(point, animation);
        taskCompletionSource->SetResult(true);
    }

    void ScaleByHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<System::Double, System::Nullable<ScreenCoordinate>>^> action,
        msclr::gcroot<System::Double> scale,
        msclr::gcroot<System::Nullable<ScreenCoordinate>> anchor
    )
    {
        action->Invoke(scale, anchor);
        taskCompletionSource->SetResult(true);
    }

    void ScaleByHelper2(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<System::Double, System::Nullable<ScreenCoordinate>, AnimationOptions^>^> action,
        msclr::gcroot<System::Double> scale,
        msclr::gcroot<System::Nullable<ScreenCoordinate>> anchor,
        msclr::gcroot<AnimationOptions^> animation
    )
    {
        action->Invoke(scale, anchor, animation);
        taskCompletionSource->SetResult(true);
    }

    void PitchByHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<System::Double>^> action,
        msclr::gcroot<System::Double> pitch
    )
    {
        action->Invoke(pitch);
        taskCompletionSource->SetResult(true);
    }

    void PitchByHelper2(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<System::Double, AnimationOptions^>^> action,
        msclr::gcroot<System::Double> pitch,
        msclr::gcroot<AnimationOptions^> animation
    )
    {
        action->Invoke(pitch, animation);
        taskCompletionSource->SetResult(true);
    }

    void RotateByHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<ScreenCoordinate, ScreenCoordinate>^> action,
        msclr::gcroot<ScreenCoordinate> first,
        msclr::gcroot<ScreenCoordinate> second
    )
    {
        action->Invoke(first, second);
        taskCompletionSource->SetResult(true);
    }

    void RotateByHelper2(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<ScreenCoordinate, ScreenCoordinate, AnimationOptions^>^> action,
        msclr::gcroot<ScreenCoordinate> first,
        msclr::gcroot<ScreenCoordinate> second,
        msclr::gcroot<AnimationOptions^> animation
    )
    {
        action->Invoke(first, second, animation);
        taskCompletionSource->SetResult(true);
    }

    void SetNorthOrientationHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<NorthOrientation>^> action,
        msclr::gcroot<NorthOrientation> orientation
    )
    {
        action->Invoke(orientation);
        taskCompletionSource->SetResult(true);
    }

    void SetConstrainModeHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<ConstrainMode>^> action,
        msclr::gcroot<ConstrainMode> mode
    )
    {
        action->Invoke(mode);
        taskCompletionSource->SetResult(true);
    }

    void SetViewportModeHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<ViewportMode>^> action,
        msclr::gcroot<ViewportMode> mode
    )
    {
        action->Invoke(mode);
        taskCompletionSource->SetResult(true);
    }

    void SetSizeHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<Size^>^> action,
        msclr::gcroot<Size^> size
    )
    {
        action->Invoke(size);
        taskCompletionSource->SetResult(true);
    }

    void SetGestureInProgressHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<System::Boolean>^> action,
        msclr::gcroot<System::Boolean> value
    )
    {
        action->Invoke(value);
        taskCompletionSource->SetResult(true);
    }

    void SetProjectionModeHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<ProjectionMode_^>^> action,
        msclr::gcroot<ProjectionMode_^> value
    )
    {
        action->Invoke(value);
        taskCompletionSource->SetResult(true);
    }

    void SetDebugHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<MapDebugOptions>^> action,
        msclr::gcroot<MapDebugOptions> value
    )
    {
        action->Invoke(value);
        taskCompletionSource->SetResult(true);
    }

    void SetFreeCameraOptionsHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<FreeCameraOptions_^>^> action,
        msclr::gcroot<FreeCameraOptions_^> value
    )
    {
        action->Invoke(value);
        taskCompletionSource->SetResult(true);
    }

    void StillImageCallbackHelper(std::exception_ptr eptr, Map::StillImageCallback^ callback)
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
        NativeWrapper(Create(
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
        NativeWrapper(
            CreateNativePointerHolder(
                Create(
                    *reinterpret_cast<mbgl::RendererFrontend*>(frontend->GetNativePointer().ToPointer()),
                    *_Observer->NativePointer,
                    *_MapOptions->NativePointer,
                    *_ResourceOptions->NativePointer,
                    *_ClientOptions->NativePointer
                ),
                false
            )
        )
    {
    }

    Map::~Map()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &Destroy,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<NativePointerHolder<mbgl::Map>^>(PointerHolder)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::RenderStill(StillImageCallback^ callback)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &RenderStillHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<StillImageCallback^>^>(gcnew System::Action<StillImageCallback^>(this, &Map::RenderStillInThread)),
                msclr::gcroot<StillImageCallback^>(callback)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::RenderStill(CameraOptions^ camera, MapDebugOptions debugOptions, StillImageCallback^ callback)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &RenderStillHelper2,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<CameraOptions^, MapDebugOptions, StillImageCallback^>^>(gcnew System::Action<CameraOptions^, MapDebugOptions, StillImageCallback^>(this, &Map::RenderStillInThread2)),
                msclr::gcroot<CameraOptions^>(camera),
                msclr::gcroot<MapDebugOptions>(debugOptions),
                msclr::gcroot<StillImageCallback^>(callback)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::TriggerRepaint()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &Map::TriggerRepaintInThread))
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::CancelTransitions()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &Map::CancelTransitionsInThread))
            )
        );

        taskCompletionSource->Task->Wait();
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
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &JumpToHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<CameraOptions^>^>(gcnew System::Action<CameraOptions^>(this, &Map::JumpToInThread)),
                msclr::gcroot<CameraOptions^>(camera)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::EaseTo(CameraOptions^ camera, AnimationOptions^ animation)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &EaseToFlyToHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<CameraOptions^, AnimationOptions^>^>(gcnew System::Action<CameraOptions^, AnimationOptions^>(this, &Map::EaseToInThread)),
                msclr::gcroot<CameraOptions^>(camera),
                msclr::gcroot<AnimationOptions^>(animation)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::FlyTo(CameraOptions^ camera, AnimationOptions^ animation)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &EaseToFlyToHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<CameraOptions^, AnimationOptions^>^>(gcnew System::Action<CameraOptions^, AnimationOptions^>(this, &Map::FlyToInThread)),
                msclr::gcroot<CameraOptions^>(camera),
                msclr::gcroot<AnimationOptions^>(animation)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::MoveBy(ScreenCoordinate point)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &MoveByHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<ScreenCoordinate>^>(gcnew System::Action<ScreenCoordinate>(this, &Map::MoveByInThread)),
                msclr::gcroot<ScreenCoordinate>(point)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::MoveBy(ScreenCoordinate point, AnimationOptions^ animation)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &MoveByHelper2,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<ScreenCoordinate, AnimationOptions^>^>(gcnew System::Action<ScreenCoordinate, AnimationOptions^>(this, &Map::MoveByInThread2)),
                msclr::gcroot<ScreenCoordinate>(point),
                msclr::gcroot<AnimationOptions^>(animation)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::ScaleBy(System::Double scale, System::Nullable<ScreenCoordinate> anchor)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &ScaleByHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<System::Double, System::Nullable<ScreenCoordinate>>^>(gcnew System::Action<System::Double, System::Nullable<ScreenCoordinate>>(this, &Map::ScaleByInThread)),
                msclr::gcroot<System::Double>(scale),
                msclr::gcroot<System::Nullable<ScreenCoordinate>>(anchor)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::ScaleBy(System::Double scale, System::Nullable<ScreenCoordinate> anchor, AnimationOptions^ animation)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &ScaleByHelper2,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<System::Double, System::Nullable<ScreenCoordinate>, AnimationOptions^>^>(gcnew System::Action<System::Double, System::Nullable<ScreenCoordinate>, AnimationOptions^>(this, &Map::ScaleByInThread2)),
                msclr::gcroot<System::Double>(scale),
                msclr::gcroot<System::Nullable<ScreenCoordinate>>(anchor),
                msclr::gcroot<AnimationOptions^>(animation)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::PitchBy(System::Double pitch)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &PitchByHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<System::Double>^>(gcnew System::Action<System::Double>(this, &Map::PitchByInThread)),
                msclr::gcroot<System::Double>(pitch)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::PitchBy(System::Double pitch, AnimationOptions^ animation)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &PitchByHelper2,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<System::Double, AnimationOptions^>^>(gcnew System::Action<System::Double, AnimationOptions^>(this, &Map::PitchByInThread2)),
                msclr::gcroot<System::Double>(pitch),
                msclr::gcroot<AnimationOptions^>(animation)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::RotateBy(ScreenCoordinate first, ScreenCoordinate second)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &RotateByHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<ScreenCoordinate, ScreenCoordinate>^>(gcnew System::Action<ScreenCoordinate, ScreenCoordinate>(this, &Map::RotateByInThread)),
                msclr::gcroot<ScreenCoordinate>(first),
                msclr::gcroot<ScreenCoordinate>(second)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::RotateBy(ScreenCoordinate first, ScreenCoordinate second, AnimationOptions^ animation)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &RotateByHelper2,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<ScreenCoordinate, ScreenCoordinate, AnimationOptions^>^>(gcnew System::Action<ScreenCoordinate, ScreenCoordinate, AnimationOptions^>(this, &Map::RotateByInThread2)),
                msclr::gcroot<ScreenCoordinate>(first),
                msclr::gcroot<ScreenCoordinate>(second),
                msclr::gcroot<AnimationOptions^>(animation)
            )
        );

        taskCompletionSource->Task->Wait();
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
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetNorthOrientationHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<NorthOrientation>^>(gcnew System::Action<NorthOrientation>(this, &Map::SetNorthOrientationInThread)),
                msclr::gcroot<NorthOrientation>(orientation)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::SetConstrainMode(ConstrainMode mode)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetConstrainModeHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<ConstrainMode>^>(gcnew System::Action<ConstrainMode>(this, &Map::SetConstrainModeInThread)),
                msclr::gcroot<ConstrainMode>(mode)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::SetViewportMode(ViewportMode mode)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetViewportModeHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<ViewportMode>^>(gcnew System::Action<ViewportMode>(this, &Map::SetViewportModeInThread)),
                msclr::gcroot<ViewportMode>(mode)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::SetSize(Size^ size)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetSizeHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<Size^>^>(gcnew System::Action<Size^>(this, &Map::SetSizeInThread)),
                msclr::gcroot<Size^>(size)
            )
        );

        taskCompletionSource->Task->Wait();
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
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetGestureInProgressHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<System::Boolean>^>(gcnew System::Action<System::Boolean>(this, &Map::SetGestureInProgressInThread)),
                msclr::gcroot<System::Boolean>(value)
            )
        );

        taskCompletionSource->Task->Wait();
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
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetProjectionModeHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<ProjectionMode_^>^>(gcnew System::Action<ProjectionMode_^>(this, &Map::SetProjectionModeInThread)),
                msclr::gcroot<ProjectionMode_^>(value)
            )
        );

        taskCompletionSource->Task->Wait();
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
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetDebugHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<MapDebugOptions>^>(gcnew System::Action<MapDebugOptions>(this, &Map::SetDebugInThread)),
                msclr::gcroot<MapDebugOptions>(value)
            )
        );

        taskCompletionSource->Task->Wait();
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
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetFreeCameraOptionsHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<FreeCameraOptions_^>^>(gcnew System::Action<FreeCameraOptions_^>(this, &Map::SetFreeCameraOptionsInThread)),
                msclr::gcroot<FreeCameraOptions_^>(value)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Map::RenderStillInThread(StillImageCallback^ callback)
    {
        NativePointer->renderStill(std::bind(
            &StillImageCallbackHelper,
            std::placeholders::_1,
            msclr::gcroot<StillImageCallback^>(callback)
        ));
    }

    System::Void Map::RenderStillInThread2(CameraOptions^ camera, MapDebugOptions debugOptions, StillImageCallback^ callback)
    {
        NativePointer->renderStill(
            *camera->NativePointer,
            (mbgl::MapDebugOptions)debugOptions,
            std::bind(
                &StillImageCallbackHelper,
                std::placeholders::_1,
                msclr::gcroot<StillImageCallback^>(callback)
            )
        );
    }

    System::Void Map::TriggerRepaintInThread()
    {
        NativePointer->triggerRepaint();
    }

    System::Void Map::CancelTransitionsInThread()
    {
        NativePointer->cancelTransitions();
    }

    System::Void Map::JumpToInThread(CameraOptions^ camera)
    {
        NativePointer->jumpTo(*camera->NativePointer);
    }

    System::Void Map::EaseToInThread(CameraOptions^ camera, AnimationOptions^ animation)
    {
        NativePointer->easeTo(*camera->NativePointer, *animation->NativePointer);
    }

    System::Void Map::FlyToInThread(CameraOptions^ camera, AnimationOptions^ animation)
    {
        NativePointer->flyTo(*camera->NativePointer, *animation->NativePointer);
    }

    System::Void Map::MoveByInThread(ScreenCoordinate point)
    {
        NativePointer->moveBy(mbgl::ScreenCoordinate(point.X, point.Y));
    }

    System::Void Map::MoveByInThread2(ScreenCoordinate point, AnimationOptions^ animation)
    {
        NativePointer->moveBy(mbgl::ScreenCoordinate(point.X, point.Y), *animation->NativePointer);
    }

    System::Void Map::ScaleByInThread(System::Double scale, System::Nullable<ScreenCoordinate> anchor)
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

    System::Void Map::ScaleByInThread2(System::Double scale, System::Nullable<ScreenCoordinate> anchor, AnimationOptions^ animation)
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

    System::Void Map::PitchByInThread(System::Double pitch)
    {
        NativePointer->pitchBy(pitch);
    }

    System::Void Map::PitchByInThread2(System::Double pitch, AnimationOptions^ animation)
    {
        NativePointer->pitchBy(pitch, *animation->NativePointer);
    }

    System::Void Map::RotateByInThread(ScreenCoordinate first, ScreenCoordinate second)
    {
        NativePointer->rotateBy(
            mbgl::ScreenCoordinate(first.X, first.Y),
            mbgl::ScreenCoordinate(second.X, second.Y)
        );
    }

    System::Void Map::RotateByInThread2(ScreenCoordinate first, ScreenCoordinate second, AnimationOptions^ animation)
    {
        NativePointer->rotateBy(
            mbgl::ScreenCoordinate(first.X, first.Y),
            mbgl::ScreenCoordinate(second.X, second.Y),
            *animation->NativePointer
        );
    }

    System::Void Map::SetNorthOrientationInThread(NorthOrientation orientation)
    {
        NativePointer->setNorthOrientation((mbgl::NorthOrientation)orientation);
    }

    System::Void Map::SetConstrainModeInThread(ConstrainMode mode)
    {
        NativePointer->setConstrainMode((mbgl::ConstrainMode)mode);
    }

    System::Void Map::SetViewportModeInThread(ViewportMode mode)
    {
        NativePointer->setViewportMode((mbgl::ViewportMode)mode);
    }

    System::Void Map::SetSizeInThread(Size^ size)
    {
        NativePointer->setSize(*size->NativePointer);
    }

    System::Void Map::SetGestureInProgressInThread(System::Boolean value)
    {
        NativePointer->setGestureInProgress(value);
    }

    System::Void Map::SetProjectionModeInThread(ProjectionMode_^ value)
    {
        NativePointer->setProjectionMode(*value->NativePointer);
    }

    System::Void Map::SetDebugInThread(MapDebugOptions value)
    {
        NativePointer->setDebug((mbgl::MapDebugOptions)value);
    }

    System::Void Map::SetFreeCameraOptionsInThread(FreeCameraOptions_^ value)
    {
        NativePointer->setFreeCameraOptions(*value->NativePointer);
    }
}
