#pragma once
#include "NativeWrapper.h"
#include "Resource.h"
#include <mbgl/storage/resource_transform.hpp>
#include <functional>
#include <algorithm>
#include <msclr/gcroot.h>

namespace DOTNET_NAMESPACE
{
    public delegate System::Void ResourceTransformFinishedCallback(System::String^ url);
    public delegate System::Void ResourceTransformCallback(Resource::ResourceKind kind, System::String^ url, ResourceTransformFinishedCallback^ finishedCallback);
    
    class ResourceTransformNativeCallbackHelper;

    public ref class ResourceTransform : NativeWrapper<mbgl::ResourceTransform>
    {
    public:
        ResourceTransform(ResourceTransformCallback^ callback);
        ~ResourceTransform();
        !ResourceTransform();

        System::Void Transform(Resource::ResourceKind kind, System::String^ url, ResourceTransformFinishedCallback^ finishedCallback);
        System::Void ManagedFinishedCallbackHandler(System::String^ url);

        explicit operator bool();
    private:
        ResourceTransformCallback^ _TransformCallback;
        ResourceTransformNativeCallbackHelper* _CallbackHelper;
    };

    class ResourceTransformNativeCallbackHelper
    {
    public:
        ResourceTransformNativeCallbackHelper(ResourceTransform^ resourceTransform, ResourceTransformCallback^ callback);
        ~ResourceTransformNativeCallbackHelper();

        void NativeTransformCallbackHandler(mbgl::Resource::Kind kind, const std::string& url, mbgl::ResourceTransform::FinishedCallback callback);
        
        mbgl::ResourceTransform::FinishedCallback FinishedCallback;
    private:
        msclr::gcroot<ResourceTransform^> _ResourceTransform;
        msclr::gcroot<ResourceTransformCallback^> _ResourceTransformCallback;
    };
}
