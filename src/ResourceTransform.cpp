#include "Convert.h"
#include "ResourceTransform.h"

namespace DOTNET_NAMESPACE
{
    ResourceTransform::ResourceTransform(ResourceTransformCallback^ callback)
        :
        _TransformCallback(callback),
        _CallbackHelper(new ResourceTransformNativeCallbackHelper(this, callback)),
        NativeWrapper(
            new mbgl::ResourceTransform(
                std::bind(
                    &ResourceTransformNativeCallbackHelper::NativeTransformCallbackHandler,
                    *_CallbackHelper,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3
                )
            )
        )
    {
    }

    ResourceTransform::~ResourceTransform()
    {
        this->!ResourceTransform();
    }

    ResourceTransform::!ResourceTransform()
    {
        delete _CallbackHelper;
    }

    System::Void ResourceTransform::Transform(Resource::ResourceKind kind, System::String^ url, ResourceTransformFinishedCallback^ finishedCallback)
    {
    }

    System::Void ResourceTransform::ManagedFinishedCallbackHandler(System::String^ url)
    {
        _CallbackHelper->FinishedCallback(Convert::ToStdString(url));
    }

    ResourceTransform::operator bool()
    {
        return NativePointer->operator bool();
    }

    ResourceTransformNativeCallbackHelper::ResourceTransformNativeCallbackHelper(ResourceTransform^ resourceTransform, ResourceTransformCallback^ callback)
        :
        _ResourceTransform(resourceTransform),
        _ResourceTransformCallback(callback)
    {
    }

    ResourceTransformNativeCallbackHelper::~ResourceTransformNativeCallbackHelper()
    {
    }

    void ResourceTransformNativeCallbackHelper::NativeTransformCallbackHandler(mbgl::Resource::Kind kind, const std::string& url, mbgl::ResourceTransform::FinishedCallback callback)
    {
        if (static_cast<ResourceTransformCallback^>(_ResourceTransformCallback))
        {
            FinishedCallback = callback;

            _ResourceTransformCallback->Invoke(
                (Resource::ResourceKind)kind,
                Convert::ToSystemString(url),
                gcnew ResourceTransformFinishedCallback(_ResourceTransform, &ResourceTransform::ManagedFinishedCallbackHandler)
            );
        }
    }
}
