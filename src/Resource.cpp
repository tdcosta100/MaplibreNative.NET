#include "Convert.h"
#include "Resource.h"
#include <mbgl/storage/resource.hpp>

namespace DOTNET_NAMESPACE
{
    Resource::Resource(ResourceKind kind, System::String^ url)
        : Resource(kind, url, nullptr)
    {
    }

    Resource::Resource(ResourceKind kind, System::String^ url, ResourceTileData^ tileData)
        : Resource(kind, url, tileData, ResourceLoadingMethod::All)
    {
    }

    Resource::Resource(ResourceKind kind, System::String^ url, ResourceTileData^ tileData, ResourceLoadingMethod loadingMethod)
        : NativeWrapper(new mbgl::Resource(
            (mbgl::Resource::Kind)kind,
            Convert::ToStdString(url),
            tileData
            ?
            std::optional<mbgl::Resource::TileData>(*tileData->NativePointer)
            :
            std::nullopt,
            (mbgl::Resource::LoadingMethod)loadingMethod
        ))
    {
    }

    Resource::~Resource()
    {
    }

    System::Void Resource::SetPriority(ResourcePriority p)
    {
        NativePointer->setPriority((mbgl::Resource::Priority)p);
    }

    System::Void Resource::SetUsage(ResourceUsage u)
    {
        NativePointer->setUsage((mbgl::Resource::Usage)u);
    }

    System::Boolean Resource::HasLoadingMethod(ResourceLoadingMethod method)
    {
        return NativePointer->hasLoadingMethod((mbgl::Resource::LoadingMethod)method);
    }

    Resource^ Resource::Style(System::String^ url)
    {
        return gcnew Resource(CreateNativePointerHolder(mbgl::Resource::style(Convert::ToStdString(url))));
    }

    Resource^ Resource::Source(System::String^ url)
    {
        return gcnew Resource(CreateNativePointerHolder(mbgl::Resource::source(Convert::ToStdString(url))));
    }

    Resource^ Resource::Tile(
        System::String^ urlTemplate,
        System::Single pixelRatio,
        System::Int32 x,
        System::Int32 y,
        System::Byte z,
        TilesetScheme scheme
    )
    {
        return Tile(urlTemplate, pixelRatio, x, y, z, scheme, ResourceLoadingMethod::All);
    }

    Resource^ Resource::Tile(
        System::String^ urlTemplate,
        System::Single pixelRatio,
        System::Int32 x,
        System::Int32 y,
        System::Byte z,
        TilesetScheme scheme,
        ResourceLoadingMethod loadingMethod
    )
    {
        return gcnew Resource(CreateNativePointerHolder(mbgl::Resource::tile(
            Convert::ToStdString(urlTemplate),
            pixelRatio,
            x,
            y,
            z,
            (mbgl::Tileset::Scheme)scheme,
            (mbgl::Resource::LoadingMethod)loadingMethod
        )));
    }

    Resource^ Resource::Glyphs(
        System::String^ urlTemplate,
        FontStack^ fontStack,
        System::Tuple<System::UInt16, System::UInt16> glyphRange
    )
    {
        return gcnew Resource(CreateNativePointerHolder(mbgl::Resource::glyphs(
            Convert::ToStdString(urlTemplate),
            Convert::ToStdVector<System::String^, std::string>(fontStack),
            std::pair<uint16_t, uint16_t>(glyphRange.Item1, glyphRange.Item2)
        )));
    }

    Resource^ Resource::SpriteImage(System::String^ base, System::Single pixelRatio)
    {
        return gcnew Resource(CreateNativePointerHolder(mbgl::Resource::spriteImage(Convert::ToStdString(base), pixelRatio)));
    }

    Resource^ Resource::SpriteJSON(System::String^ base, System::Single pixelRatio)
    {
        return gcnew Resource(CreateNativePointerHolder(mbgl::Resource::spriteJSON(Convert::ToStdString(base), pixelRatio)));
    }

    Resource^ Resource::Image(System::String^ url)
    {
        return gcnew Resource(CreateNativePointerHolder(mbgl::Resource::image(Convert::ToStdString(url))));
    }

    Resource::ResourceKind Resource::Kind::get()
    {
        return (Resource::ResourceKind)NativePointer->kind;
    }

    System::Void Resource::Kind::set(ResourceKind value)
    {
        NativePointer->kind = (mbgl::Resource::Kind)value;
    }

    Resource::ResourceLoadingMethod Resource::LoadingMethod::get()
    {
        return (Resource::ResourceLoadingMethod)NativePointer->loadingMethod;
    }

    System::Void Resource::LoadingMethod::set(Resource::ResourceLoadingMethod value)
    {
        NativePointer->loadingMethod = (mbgl::Resource::LoadingMethod)value;
    }

    Resource::ResourceUsage Resource::Usage::get()
    {
        return (Resource::ResourceUsage)NativePointer->usage;
    }

    System::Void Resource::Usage::set(Resource::ResourceUsage value)
    {
        NativePointer->usage = (mbgl::Resource::Usage)value;
    }

    Resource::ResourcePriority Resource::Priority::get()
    {
        return (Resource::ResourcePriority)NativePointer->priority;
    }

    System::Void Resource::Priority::set(Resource::ResourcePriority value)
    {
        NativePointer->priority = (mbgl::Resource::Priority)value;
    }

    System::String^ Resource::Url::get()
    {
        return Convert::ToSystemString(NativePointer->url);
    }

    System::Void Resource::Url::set(System::String^ value)
    {
        NativePointer->url = Convert::ToStdString(value);
    }

    Resource::ResourceTileData^ Resource::TileData::get()
    {
        if (!_TileData && NativePointer->tileData.has_value())
        {
            _TileData = gcnew ResourceTileData(ResourceTileData::CreateNativePointerHolder(NativePointer->tileData.value()));
        }

        return _TileData;
    }

    System::Void Resource::TileData::set(ResourceTileData^ value)
    {
        _TileData = value;

        if (value)
        {
            NativePointer->tileData = *value->NativePointer;
        }
        else
        {
            NativePointer->tileData = std::nullopt;
        }
    }
    System::Nullable<System::DateTime> Resource::PriorModified::get()
    {
        if (NativePointer->priorModified.has_value())
        {
            return Convert::ToSystemDateTime(NativePointer->priorModified.value());
        }

        return System::Nullable<System::DateTime>();
    }

    System::Void Resource::PriorModified::set(System::Nullable<System::DateTime> value)
    {
        if (value.HasValue)
        {
            NativePointer->priorModified = Convert::ToTimePoint<mbgl::Timestamp::duration>(value.Value);
        }
        else
        {
            NativePointer->priorModified = std::nullopt;
        }
    }

    System::Nullable<System::DateTime> Resource::PriorExpires::get()
    {
        if (NativePointer->priorExpires.has_value())
        {
            return Convert::ToSystemDateTime(NativePointer->priorExpires.value());
        }

        return System::Nullable<System::DateTime>();
    }

    System::Void Resource::PriorExpires::set(System::Nullable<System::DateTime> value)
    {
        if (value.HasValue)
        {
            NativePointer->priorExpires = Convert::ToTimePoint<mbgl::Timestamp::duration>(value.Value);
        }
        else
        {
            NativePointer->priorExpires = std::nullopt;
        }
    }

    System::String^ Resource::PriorEtag::get()
    {
        if (NativePointer->priorEtag.has_value())
        {
            return Convert::ToSystemString(NativePointer->priorEtag.value());
        }

        return nullptr;
    }

    System::Void Resource::PriorEtag::set(System::String^ value)
    {
        if (value)
        {
            NativePointer->priorEtag = Convert::ToStdString(value);
        }
        else
        {
            NativePointer->priorEtag = std::nullopt;
        }
    }

    System::String^ Resource::PriorData::get()
    {
        if (NativePointer->priorData)
        {
            return Convert::ToSystemString(*NativePointer->priorData);
        }

        return nullptr;
    }

    System::Void Resource::PriorData::set(System::String^ value)
    {
        if (value)
        {
            NativePointer->priorData = std::shared_ptr<const std::string>(&Convert::ToStdString(value));
        }
        else
        {
            NativePointer->priorData.reset();
        }
    }

    System::TimeSpan Resource::MinimumUpdateInterval::get()
    {
        return Convert::ToSystemTimeSpan(NativePointer->minimumUpdateInterval);
    }

    System::Void Resource::MinimumUpdateInterval::set(System::TimeSpan value)
    {
        NativePointer->minimumUpdateInterval = Convert::ToDuration<mbgl::Duration>(value);
    }

    Resource::ResourceStoragePolicy Resource::StoragePolicy::get()
    {
        return (Resource::ResourceStoragePolicy)NativePointer->storagePolicy;
    }

    System::Void Resource::StoragePolicy::set(ResourceStoragePolicy value)
    {
        NativePointer->storagePolicy = (mbgl::Resource::StoragePolicy)value;
    }

    Resource::Resource(NativePointerHolder<mbgl::Resource>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Resource::ResourceTileData::ResourceTileData() : NativeWrapper(new mbgl::Resource::TileData())
    {
    }

    Resource::ResourceTileData::ResourceTileData(NativePointerHolder<mbgl::Resource::TileData>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Resource::ResourceTileData::~ResourceTileData()
    {
    }

    System::String^ Resource::ResourceTileData::UrlTemplate::get()
    {
        return Convert::ToSystemString(NativePointer->urlTemplate);
    }

    System::Void Resource::ResourceTileData::UrlTemplate::set(System::String^ value)
    {
        NativePointer->urlTemplate = Convert::ToStdString(value);
    }

    System::Byte Resource::ResourceTileData::PixelRatio::get()
    {
        return NativePointer->pixelRatio;
    }

    System::Void Resource::ResourceTileData::PixelRatio::set(System::Byte value)
    {
        NativePointer->pixelRatio = value;
    }

    System::Int32 Resource::ResourceTileData::X::get()
    {
        return NativePointer->x;
    }

    System::Void Resource::ResourceTileData::X::set(System::Int32 value)
    {
        NativePointer->x = value;
    }

    System::Int32 Resource::ResourceTileData::Y::get()
    {
        return NativePointer->y;
    }

    System::Void Resource::ResourceTileData::Y::set(System::Int32 value)
    {
        NativePointer->y = value;
    }

    System::SByte Resource::ResourceTileData::Z::get()
    {
        return NativePointer->z;
    }

    System::Void Resource::ResourceTileData::Z::set(System::SByte value)
    {
        NativePointer->z = value;
    }
}
