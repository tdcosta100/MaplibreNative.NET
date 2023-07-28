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
#include "RunLoop.h"
#include "Size.h"
#include "TransformState.h"
#include "UpdateParameters.h"
#include <mbgl/gfx/headless_frontend.hpp>
#include <mbgl/map/map.hpp>
#include <mbgl/renderer/renderer.hpp>
#include <mbgl/renderer/update_parameters.hpp>

namespace
{
    using namespace ::DOTNET_NAMESPACE;

    mbgl::HeadlessFrontend* Create(mbgl::Size size, float pixelRatio)
    {
        mbgl::HeadlessFrontend* result = nullptr;

        std::mutex mutex;
        std::condition_variable condition_variable;

        RunLoop::Get()->NativePointer->ExecuteInThread(
            [&mutex, &condition_variable, &size, &pixelRatio, &result]
            {
                std::unique_lock<std::mutex> lock(mutex);
                result = new mbgl::HeadlessFrontend(size, pixelRatio);
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
        msclr::gcroot<NativePointerHolder<mbgl::HeadlessFrontend>^> pointerHolder
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

    void UpdateHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<UpdateParameters^>^> action,
        msclr::gcroot<UpdateParameters^> parameters
    )
    {
        action->Invoke(parameters);
        taskCompletionSource->SetResult(true);
    }

    void ReadStillImageHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<PremultipliedImage^>^> taskCompletionSource,
        msclr::gcroot<System::Func<PremultipliedImage^>^> action
    )
    {
        taskCompletionSource->SetResult(action->Invoke());
    }

    void RenderHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<HeadlessFrontend::RenderResult>^> taskCompletionSource,
        msclr::gcroot<System::Func<Map^, HeadlessFrontend::RenderResult>^> action,
        msclr::gcroot<Map^> map
    )
    {
        taskCompletionSource->SetResult(action->Invoke(map));
    }

    void RenderOnceHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<Map^>^> action,
        msclr::gcroot<Map^> map
    )
    {
        action->Invoke(map);
        taskCompletionSource->SetResult(true);
    }

    void SetSizeHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<Size_^>^> action,
        msclr::gcroot<Size_^> size
    )
    {
        action->Invoke(size);
        taskCompletionSource->SetResult(true);
    }
}

namespace DOTNET_NAMESPACE
{
    HeadlessFrontend::HeadlessFrontend() : HeadlessFrontend(gcnew Size_(512, 512))
    {
    }
    
    HeadlessFrontend::HeadlessFrontend(Size_^ size) : HeadlessFrontend(size, 1.0f)
    {
    }
    
    HeadlessFrontend::HeadlessFrontend(Size_^ size, System::Single pixelRatio)
        : NativeWrapper(Create(*size->NativePointer, pixelRatio))
    {
    }

    HeadlessFrontend::HeadlessFrontend(NativePointerHolder<mbgl::HeadlessFrontend>^ nativePointerHolder)
        : NativeWrapper(nativePointerHolder)
    {
    }

    HeadlessFrontend::~HeadlessFrontend()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &Destroy,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<NativePointerHolder<mbgl::HeadlessFrontend>^>(PointerHolder)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void HeadlessFrontend::Reset()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &HeadlessFrontend::ResetInThread))
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void HeadlessFrontend::SetObserver(RendererObserver^ observer)
    {
        NativePointer->setObserver(*observer->NativePointer);
    }

    System::Void HeadlessFrontend::Update(UpdateParameters^ parameters)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &UpdateHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<UpdateParameters^>^>(gcnew System::Action<UpdateParameters^>(this, &HeadlessFrontend::UpdateInThread)),
                msclr::gcroot<UpdateParameters^>(parameters)
            )
        );

        taskCompletionSource->Task->Wait();
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
        System::Threading::Tasks::TaskCompletionSource<PremultipliedImage^>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<PremultipliedImage^>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &ReadStillImageHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<PremultipliedImage^>^>(taskCompletionSource),
                msclr::gcroot<System::Func<PremultipliedImage^>^>(gcnew System::Func<PremultipliedImage^>(this, &HeadlessFrontend::ReadStillImageInThread))
            )
        );

        return taskCompletionSource->Task->Result;
    }

    HeadlessFrontend::RenderResult HeadlessFrontend::Render(Map^ map)
    {
        System::Threading::Tasks::TaskCompletionSource<HeadlessFrontend::RenderResult>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<HeadlessFrontend::RenderResult>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &RenderHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<HeadlessFrontend::RenderResult>^>(taskCompletionSource),
                msclr::gcroot<System::Func<Map^, HeadlessFrontend::RenderResult>^>(gcnew System::Func<Map^, HeadlessFrontend::RenderResult>(this, &HeadlessFrontend::RenderInThread)),
                msclr::gcroot<Map^>(map)
            )
        );

        return taskCompletionSource->Task->Result;
    }

    System::Void HeadlessFrontend::RenderOnce(Map^ map)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &RenderOnceHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<Map^>^>(gcnew System::Action<Map^>(this, &HeadlessFrontend::RenderOnceInThread)),
                msclr::gcroot<Map^>(map)
            )
        );

        taskCompletionSource->Task->Wait();
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
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SetSizeHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<Size_^>^>(gcnew System::Action<Size_^>(this, &HeadlessFrontend::SetSizeInThread)),
                msclr::gcroot<Size_^>(value)
            )
        );

        taskCompletionSource->Task->Wait();
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

    System::Void HeadlessFrontend::ResetInThread()
    {
        NativePointer->reset();
    }

    System::Void HeadlessFrontend::UpdateInThread(UpdateParameters^ parameters)
    {
        NativePointer->update(*parameters->NativePointer);
    }

    PremultipliedImage^ HeadlessFrontend::ReadStillImageInThread()
    {
        return gcnew PremultipliedImage(PremultipliedImage::CreateNativePointerHolder(NativePointer->readStillImage()));
    }

    HeadlessFrontend::RenderResult HeadlessFrontend::RenderInThread(Map^ map)
    {
        mbgl::HeadlessFrontend::RenderResult nativeResult = NativePointer->render(*map->NativePointer);

        RenderResult result;
        result.Image = gcnew PremultipliedImage(PremultipliedImage::CreateNativePointerHolder(std::move(nativeResult.image)));
        result.Stats = gcnew RenderingStats(RenderingStats::CreateNativePointerHolder(nativeResult.stats));

        return result;
    }

    System::Void HeadlessFrontend::RenderOnceInThread(Map^ map)
    {
        NativePointer->renderOnce(*map->NativePointer);
    }

    System::Void HeadlessFrontend::SetSizeInThread(Size_^ value)
    {
        NativePointer->setSize(*value->NativePointer);
    }
}
