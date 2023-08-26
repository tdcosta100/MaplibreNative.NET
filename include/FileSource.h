#pragma once
#include "NativeWrapper.h"
#include <algorithm>
#include <memory>
#include <msclr/gcroot.h>

namespace mbgl
{
    class AsyncRequest;
    class FileSource;
    class Response;
}

namespace DOTNET_NAMESPACE
{
    ref class AsyncRequest;
    ref class ClientOptions;
    ref class Resource;
    ref class ResourceOptions;
    ref class ResourceTransform;
    ref class Response;

    using ClientOptions_ = ClientOptions;
    using ResourceOptions_ = ResourceOptions;
    
    public ref class FileSource : NativeWrapper<std::shared_ptr<mbgl::FileSource>>
    {
    public:
        delegate System::Void Callback(Response^ response);

        ~FileSource();
        !FileSource();
        
        /// <summary>
        /// Request a resource. The callback will be called asynchronously, in the
        /// same thread as the request was made. This thread must have an active
        /// RunLoop. The request may be cancelled before completion by releasing the
        /// returned AsyncRequest. If the request is cancelled before the callback
        /// is executed, the callback will not be executed.
        /// </summary>
        /// <param name="resource"></param>
        /// <param name="callback"></param>
        /// <returns></returns>
        virtual AsyncRequest^ Request(Resource^ resource, Callback^ callback);

        /// <summary>
        /// Allows to forward response from one source to another.
        /// Optionally, callback can be provided to receive notification for forward
        /// operation.
        /// </summary>
        /// <param name="resource"></param>
        /// <param name="response"></param>
        /// <param name="callback"></param>
        /// <returns></returns>
        virtual System::Void Forward(Resource^ resource, Response^ response, System::Action^ callback);

        /// <summary>
        /// When a file source supports consulting a local cache only, it must
        /// return true. Cache-only requests are requests that aren't as urgent, but
        /// could be useful, e.g. to cover part of the map while loading. The
        /// FileSource should only do cheap actions to retrieve the data, e.g. load
        /// it from a cache, but not from the internet.
        /// </summary>
        /// <returns></returns>
        virtual System::Boolean SupportsCacheOnlyRequests();

        /// <summary>
        /// Checks whether a resource could be requested from this file source.
        /// </summary>
        /// <param name="resource"></param>
        /// <returns></returns>
        virtual System::Boolean CanRequest(Resource^ resource);

        /// <summary>
        /// Pause file request activity.
        /// 
        /// If pause is called then no revalidation or network request activity
        /// will occur.
        /// </summary>
        /// <returns></returns>
        virtual System::Void Pause();

        /// <summary>
        /// Resume file request activity.
        /// 
        /// Calling resume will unpause the file source and process any tasks that
        /// expired while the file source was paused.
        /// </summary>
        /// <returns></returns>
        virtual System::Void Resume();

        /// <summary>
        /// Generic setter method
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        virtual System::Void SetProperty(System::String^ key, System::String^ value);

        /// <summary>
        /// Generic getter method
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        virtual System::String^ GetProperty(System::String^ key);

        /// <summary>
        /// When supported, sets the modifier of the requested resources.
        /// </summary>
        /// <param name="transform"></param>
        /// <returns></returns>
        virtual System::Void SetResourceTransform(ResourceTransform^ transform);

        virtual property ResourceOptions_^ ResourceOptions { ResourceOptions_^ get(); System::Void set(ResourceOptions_^ value); }
        virtual property ClientOptions_^ ClientOptions { ClientOptions_^ get(); System::Void set(ClientOptions_^ value); }
    internal:
        FileSource(NativePointerHolder<std::shared_ptr<mbgl::FileSource>>^ nativePointerHolder);
    };
}
