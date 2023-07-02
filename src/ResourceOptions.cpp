#include "Convert.h"
#include "ResourceOptions.h"
#include <mbgl/storage/resource_options.hpp>

namespace DOTNET_NAMESPACE
{
    ResourceOptions::ResourceOptions() : NativeWrapper(new mbgl::ResourceOptions())
    {
    }

    ResourceOptions::ResourceOptions(NativePointerHolder<mbgl::ResourceOptions>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    ResourceOptions::~ResourceOptions()
    {
    }

    ResourceOptions^ ResourceOptions::Clone()
    {
        return gcnew ResourceOptions(CreateNativePointerHolder(NativePointer->clone()));
    }

    ResourceOptions^ ResourceOptions::WithApiKey(System::String^ token)
    {
        NativePointer->withApiKey(Convert::ToStdString(token));
        
        return this;
    }

    // TODO: implement the managed version
    /*
    ResourceOptions^ ResourceOptions::WithTileServerOptions(TileServerOptions tileServerOptions)
    {
        NativePointer->withTileServerOptions(tileServerOptions);

        return this;
    }
    */

    ResourceOptions^ ResourceOptions::WithCachePath(System::String^ path)
    {
        NativePointer->withCachePath(Convert::ToStdString(path));

        return this;
    }

    ResourceOptions^ ResourceOptions::WithAssetPath(System::String^ path)
    {
        NativePointer->withAssetPath(Convert::ToStdString(path));
        
        return this;
    }

    ResourceOptions^ ResourceOptions::WithMaximumCacheSize(System::UInt64 size)
    {
        NativePointer->withMaximumCacheSize(size);
        
        return this;
    }

    ResourceOptions^ ResourceOptions::WithPlatformContext(System::IntPtr context)
    {
        NativePointer->withPlatformContext(context.ToPointer());
        
        return this;
    }

    ResourceOptions^ ResourceOptions::Default()
    {
        return gcnew ResourceOptions(CreateNativePointerHolder(mbgl::ResourceOptions::Default()));
    }

    System::String^ ResourceOptions::ApiKey::get()
    {
        return Convert::ToSystemString(NativePointer->apiKey());
    }

    // TODO: implement the managed version
    /*
    TileServerOptions ResourceOptions::TileServerOptions::get()
    {
        return NativePointer->tileServerOptions();
    }
    */

    System::String^ ResourceOptions::CachePath::get()
    {
        return Convert::ToSystemString(NativePointer->cachePath());
    }

    System::String^ ResourceOptions::AssetPath::get()
    {
        return Convert::ToSystemString(NativePointer->assetPath());
    }

    System::UInt64 ResourceOptions::MaximumCacheSize::get()
    {
        return NativePointer->maximumCacheSize();
    }

    System::IntPtr ResourceOptions::PlatformContext::get()
    {
        return System::IntPtr(NativePointer->platformContext());
    }
}
