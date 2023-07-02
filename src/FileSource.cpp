#include "AsyncRequest.h"
#include "ClientOptions.h"
#include "Convert.h"
#include "FileSource.h"
#include "Resource.h"
#include "ResourceOptions.h"
#include "ResourceTransform.h"
#include "Response.h"
#include <mbgl/util/async_request.hpp>
#include <mbgl/storage/file_source.hpp>

namespace
{
    using namespace ::DOTNET_NAMESPACE;
    
    void RequestCallback(mbgl::Response response, FileSource::Callback^ callback)
    {
        callback->Invoke(gcnew Response(Response::CreateNativePointerHolder(response)));
    }

    void ForwardCallback(System::Action^ callback)
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
        return gcnew AsyncRequest(
            AsyncRequest::CreateNativePointerHolder(
                NativePointer->get()->request(
                    *resource->NativePointer,
                    std::bind(&RequestCallback, std::placeholders::_1, msclr::gcroot<Callback^>(callback))
                )
                .release()
            )
        );
    }

    System::Void FileSource::Forward(Resource^ resource, Response^ response, System::Action^ callback)
    {
        NativePointer->get()->forward(
            *resource->NativePointer,
            *response->NativePointer,
            std::bind(&ForwardCallback, msclr::gcroot<System::Action^>(callback))
        );
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
        NativePointer->get()->pause();
    }

    System::Void FileSource::Resume()
    {
        NativePointer->get()->resume();
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
}
