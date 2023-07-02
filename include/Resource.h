#pragma once
#include "NativeWrapper.h"
#include <mbgl/storage/resource.hpp>

namespace DOTNET_NAMESPACE
{
    using FontStack = System::Collections::Generic::IEnumerable<System::String^>;
    
    public ref class Resource : NativeWrapper<mbgl::Resource>
    {
    public:
        ref class ResourceTileData;

        enum class ResourceKind : System::Byte
        {
            Unknown = 0,
            Style,
            Source,
            Tile,
            Glyphs,
            SpriteImage,
            SpriteJSON,
            Image
        };

        enum class ResourcePriority : System::Byte
        {
            Regular = false,
            Low = true
        };

        enum class ResourceUsage : System::Byte
        {
            Online,
            Offline
        };

        enum class ResourceStoragePolicy : System::Byte
        {
            Permanent,
            Volatile
        };

        enum class ResourceLoadingMethod : System::Byte
        {
            None = 0b00,
            Cache = 0b01,
            Network = 0b10,

            CacheOnly = Cache,
            NetworkOnly = Network,
            All = Cache | Network,
        };

        enum class TilesetScheme : System::Byte
        {
            XYZ,
            TMS
        };

        Resource(ResourceKind kind, System::String^ url);
        Resource(ResourceKind kind, System::String^ url, ResourceTileData^ tileData);
        Resource(ResourceKind kind, System::String^ url, ResourceTileData^ tileData, ResourceLoadingMethod loadingMethod);
        ~Resource();

        System::Void SetPriority(ResourcePriority p);
        System::Void SetUsage(ResourceUsage u);
        System::Boolean HasLoadingMethod(ResourceLoadingMethod method);

        static Resource^ Style(System::String^ url);
        static Resource^ Source(System::String^ url);
        
        static Resource^ Tile(
            System::String^ urlTemplate,
            System::Single pixelRatio,
            System::Int32 x,
            System::Int32 y,
            System::Byte z,
            TilesetScheme scheme
        );

        static Resource^ Tile(
            System::String^ urlTemplate,
            System::Single pixelRatio,
            System::Int32 x,
            System::Int32 y,
            System::Byte z,
            TilesetScheme scheme,
            ResourceLoadingMethod loadingMethod
        );

        static Resource^ Glyphs(
            System::String^ urlTemplate,
            FontStack^ fontStack,
            System::Tuple<System::UInt16, System::UInt16> glyphRange
        );

        static Resource^ SpriteImage(System::String^ base, System::Single pixelRatio);
        static Resource^ SpriteJSON(System::String^ base, System::Single pixelRatio);
        static Resource^ Image(System::String^ url);

        property ResourceKind Kind { ResourceKind get(); System::Void set(ResourceKind value); }
        property ResourceLoadingMethod LoadingMethod { ResourceLoadingMethod get(); System::Void set(ResourceLoadingMethod value); }
        property ResourceUsage Usage { ResourceUsage get(); System::Void set(ResourceUsage value); }
        property ResourcePriority Priority { ResourcePriority get(); System::Void set(ResourcePriority value); }
        property System::String^ Url { System::String^ get(); System::Void set(System::String^ value); }

        /// <summary>
        /// Includes auxiliary data if this is a tile request.
        /// </summary>
        property ResourceTileData^ TileData { ResourceTileData^ get(); System::Void set(ResourceTileData^ value); }
        property System::Nullable<System::DateTime> PriorModified { System::Nullable<System::DateTime> get(); System::Void set(System::Nullable<System::DateTime> value); }
        property System::Nullable<System::DateTime> PriorExpires { System::Nullable<System::DateTime> get(); System::Void set(System::Nullable<System::DateTime> value); }
        property System::String^ PriorEtag { System::String^ get(); System::Void set(System::String^ value); }
        property System::String^ PriorData { System::String^ get(); System::Void set(System::String^ value); }
        property System::TimeSpan MinimumUpdateInterval { System::TimeSpan get(); System::Void set(System::TimeSpan value); }
        property ResourceStoragePolicy StoragePolicy { ResourceStoragePolicy get(); System::Void set(ResourceStoragePolicy value); }

    private:
        Resource(NativePointerHolder<mbgl::Resource>^ nativePointerHolder);

        ResourceTileData^ _TileData;
    };

    ref class Resource::ResourceTileData : NativeWrapper<mbgl::Resource::TileData>
    {
    public:
        ResourceTileData();
        ResourceTileData(NativePointerHolder<mbgl::Resource::TileData>^ nativePointerHolder);
        ~ResourceTileData();

        property System::String^ UrlTemplate { System::String^ get(); System::Void set(System::String^ value); }
        property System::Byte PixelRatio { System::Byte get(); System::Void set(System::Byte value); }
        property System::Int32 X { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 Y { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::SByte Z { System::SByte get(); System::Void set(System::SByte value); }
    };
}
