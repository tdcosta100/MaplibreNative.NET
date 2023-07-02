#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class ResourceOptions;
}

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Holds values for resource options.
    /// </summary>
    public ref class ResourceOptions : NativeWrapper<mbgl::ResourceOptions>
    {
    public:
        /// <summary>
        /// Constructs a ResourceOptions object with default values.
        /// </summary>
        ResourceOptions();
        ~ResourceOptions();

        ResourceOptions^ Clone();

        /// <summary>
        /// Sets the Mapbox access token - see
        /// <see href="https://docs.mapbox.com/help/how-mapbox-works/access-tokens/"/> for details.
        /// </summary>
        /// <param name="token">Mapbox access token.</param>
        /// <returns>ResourceOptions for chaining options together.</returns>
        ResourceOptions^ WithApiKey(System::String^ token);
        
        // TODO: implement the managed version
        //ResourceOptions^ WithTileServerOptions(TileServerOptions tileServerOptions);

        /// <summary>
        /// Sets the cache path.
        /// </summary>
        /// <param name="path">Cache path.</param>
        /// <returns>ResourceOptions for chaining options together.</returns>
        ResourceOptions^ WithCachePath(System::String^ path);

        /// <summary>
        /// Sets the asset path, which is the root directory from where the asset:// scheme gets resolved in a style.
        /// </summary>
        /// <param name="path">Asset path.</param>
        /// <returns>ResourceOptions for chaining options together.</returns>
        ResourceOptions^ WithAssetPath(System::String^ path);

        /// <summary>
        /// Sets the maximum cache size.
        /// </summary>
        /// <param name="size">Cache maximum size in bytes.</param>
        /// <returns>ResourceOptions for chaining options together.</returns>
        ResourceOptions^ WithMaximumCacheSize(System::UInt64 size);

        /// <summary>
        /// Sets the platform context. A platform context is usually an object that assists the creation of a file source.
        /// </summary>
        /// <param name="context">Platform context.</param>
        /// <returns>ResourceOptions for chaining options together.</returns>
        ResourceOptions^ WithPlatformContext(System::IntPtr context);

        /// <summary>
        /// Returns default resource options.
        /// </summary>
        /// <returns>Resource options.</returns>
        static ResourceOptions^ Default();

        /// <summary>
        /// Gets the previously set (or default) Mapbox access token.
        /// </summary>
        property System::String^ ApiKey { System::String^ get(); }
        
        // TODO: implement the managed version
        //property TileServerOptions TileServerOptions { TileServerOptions get(); }

        /// <summary>
        /// Gets the previously set (or default) cache path.
        /// </summary>
        property System::String^ CachePath { System::String^ get(); }

        /// <summary>
        /// Gets the previously set (or default) asset path.
        /// </summary>
        property System::String^ AssetPath { System::String^ get(); }

        /// <summary>
        /// Gets the previously set (or default) maximum allowed cache size in bytes.
        /// </summary>
        property System::UInt64 MaximumCacheSize { System::UInt64 get(); }

        /// <summary>
        /// Gets the previously set (or default) platform context.
        /// </summary>
        property System::IntPtr PlatformContext { System::IntPtr get(); }
    internal:
        ResourceOptions(NativePointerHolder<mbgl::ResourceOptions>^ nativePointerHolder);
    };
}
