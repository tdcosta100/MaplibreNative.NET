#include "AsyncRequest.h"
#include "ClientOptions.h"
#include "Convert.h"
#include "FileSource.h"
#include "Resource.h"
#include "ResourceOptions.h"
#include "ResourceTransform.h"
#include "Response.h"
#include "RunLoop.h"
#include <mbgl/util/async_request.hpp>
#include <mbgl/storage/file_source.hpp>

namespace
{
    using namespace ::DOTNET_NAMESPACE;
    
    void SystemActionHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action^> action
    )
    {
        action->Invoke();
        taskCompletionSource->SetResult(true);
    }

    void RequestHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<AsyncRequest^>^> taskCompletionSource,
        msclr::gcroot<System::Func<Resource^, FileSource::Callback^, AsyncRequest^>^> action,
        msclr::gcroot<Resource^> resource,
        msclr::gcroot<FileSource::Callback^> callback
    )
    {
        taskCompletionSource->SetResult(action->Invoke(resource, callback));
    }

    void ForwardHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<Resource^, Response^, System::Action^>^> action,
        msclr::gcroot<Resource^> resource,
        msclr::gcroot<Response^> response,
        msclr::gcroot<System::Action^> callback
    )
    {
        action->Invoke(resource, response, callback);
        taskCompletionSource->SetResult(true);
    }

    void RequestCallbackHelper(mbgl::Response response, FileSource::Callback^ callback)
    {
        callback->Invoke(gcnew Response(Response::CreateNativePointerHolder(response)));
    }

    void ForwardCallbackHelper(System::Action^ callback)
    {
        callback->Invoke();
    }
}

namespace DOTNET_NAMESPACE
{
    FileSource::FileSource(NativePointerHolder<std::shared_ptr<mbgl::FileSource>>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    FileSource::~FileSource()
    {
        this->!FileSource();
    }

    FileSource::!FileSource()
    {
    }

    AsyncRequest^ FileSource::Request(Resource^ resource, Callback^ callback)
    {
        System::Threading::Tasks::TaskCompletionSource<AsyncRequest^>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<AsyncRequest^>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &RequestHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<AsyncRequest^>^>(taskCompletionSource),
                msclr::gcroot<System::Func<Resource^, Callback^, AsyncRequest^>^>(gcnew System::Func<Resource^, Callback^, AsyncRequest^>(this, &FileSource::RequestInThread)),
                msclr::gcroot<Resource^>(resource),
                msclr::gcroot<Callback^>(callback)
            )
        );

        return taskCompletionSource->Task->Result;
    }

    System::Void FileSource::Forward(Resource^ resource, Response^ response, System::Action^ callback)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &ForwardHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<Resource^, Response^, System::Action^>^>(gcnew System::Action<Resource^, Response^, System::Action^>(this, &FileSource::ForwardInThread)),
                msclr::gcroot<Resource^>(resource),
                msclr::gcroot<Response^>(response),
                msclr::gcroot<System::Action^>(callback)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Boolean FileSource::SupportsCacheOnlyRequests()
    {
        return NativePointer->get()->supportsCacheOnlyRequests();
    }

    System::Boolean FileSource::CanRequest(Resource^ resource)
    {
        return NativePointer->get()->canRequest(*resource->NativePointer);
    }

    System::Void FileSource::Pause()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &FileSource::PauseInThread))
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void FileSource::Resume()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &FileSource::ResumeInThread))
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void FileSource::SetProperty(System::String^ key, System::String^ value)
    {
        NativePointer->get()->setProperty(
            Convert::ToStdString(key),
            Convert::ToStdString(value)
        );
    }

    System::String^ FileSource::GetProperty(System::String^ key)
    {
        return Convert::ToSystemString(*NativePointer->get()->getProperty(Convert::ToStdString(key)).getString());
    }

    System::Void FileSource::SetResourceTransform(ResourceTransform^ transform)
    {
        NativePointer->get()->setResourceTransform(*transform->NativePointer);
    }

    ResourceOptions_^ FileSource::ResourceOptions::get()
    {
        return gcnew ResourceOptions_(ResourceOptions_::CreateNativePointerHolder(NativePointer->get()->getResourceOptions()));
    }

    System::Void FileSource::ResourceOptions::set(ResourceOptions_^ value)
    {
        NativePointer->get()->setResourceOptions(value->NativePointer->clone());
    }

    ClientOptions_^ FileSource::ClientOptions::get()
    {
        return gcnew ClientOptions_(ClientOptions_::CreateNativePointerHolder(NativePointer->get()->getClientOptions()));
    }

    System::Void FileSource::ClientOptions::set(ClientOptions_^ value)
    {
        NativePointer->get()->setClientOptions(value->NativePointer->clone());
    }

    AsyncRequest^ FileSource::RequestInThread(Resource^ resource, Callback^ callback)
    {
        return gcnew AsyncRequest(
            AsyncRequest::CreateNativePointerHolder(
                NativePointer->get()->request(
                    *resource->NativePointer,
                    std::bind(&RequestCallbackHelper, std::placeholders::_1, msclr::gcroot<Callback^>(callback))
                )
                .release()
            )
        );
    }

    System::Void FileSource::ForwardInThread(Resource^ resource, Response^ response, System::Action^ callback)
    {
        NativePointer->get()->forward(
            *resource->NativePointer,
            *response->NativePointer,
            std::bind(&ForwardCallbackHelper, msclr::gcroot<System::Action^>(callback))
        );
    }

    System::Void FileSource::PauseInThread()
    {
        NativePointer->get()->pause();
    }

    System::Void FileSource::ResumeInThread()
    {
        NativePointer->get()->resume();
    }
}
