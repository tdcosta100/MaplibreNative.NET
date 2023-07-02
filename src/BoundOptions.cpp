#include "BoundOptions.h"
#include "LatLng.h"
#include <mbgl/map/bound_options.hpp>

namespace DOTNET_NAMESPACE
{
    BoundOptions::BoundOptions() : NativeWrapper(new mbgl::BoundOptions())
    {
    }

    BoundOptions::BoundOptions(NativePointerHolder<mbgl::BoundOptions>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    BoundOptions::~BoundOptions()
    {
    }

    BoundOptions^ BoundOptions::WithLatLngBounds(LatLngBounds^ b)
    {
        NativePointer->withLatLngBounds(*b->NativePointer);
        return this;
    }

    BoundOptions^ BoundOptions::WithMinZoom(System::Double z)
    {
        NativePointer->withMinZoom(z);
        return this;
    }

    BoundOptions^ BoundOptions::WithMaxZoom(System::Double z)
    {
        NativePointer->withMaxZoom(z);
        return this;
    }

    BoundOptions^ BoundOptions::WithMinPitch(System::Double p)
    {
        NativePointer->withMinPitch(p);
        return this;
    }

    BoundOptions^ BoundOptions::WithMaxPitch(System::Double p)
    {
        NativePointer->withMaxPitch(p);
        return this;
    }

    LatLngBounds^ BoundOptions::Bounds::get()
    {
        if (NativePointer->bounds.has_value())
        {
            return gcnew LatLngBounds(LatLngBounds::CreateNativePointerHolder(NativePointer->bounds.value()));
        }
        
        return nullptr;
    }

    System::Void BoundOptions::Bounds::set(LatLngBounds^ value)
    {
        if (value)
        {
            NativePointer->bounds = *value->NativePointer;
        }
        else
        {
            NativePointer->bounds = std::nullopt;
        }
    }

    System::Nullable<System::Double> BoundOptions::MaxZoom::get()
    {
        if (NativePointer->maxZoom.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->maxZoom.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void BoundOptions::MaxZoom::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->maxZoom = value.Value;
        }
        else
        {
            NativePointer->maxZoom = std::nullopt;
        }
    }

    System::Nullable<System::Double> BoundOptions::MinZoom::get()
    {
        if (NativePointer->minZoom.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->minZoom.value());
        }

        return System::Nullable<System::Double>();
    }
    System::Void BoundOptions::MinZoom::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->minZoom = value.Value;
        }
        else
        {
            NativePointer->minZoom = std::nullopt;
        }
    }

    System::Nullable<System::Double> BoundOptions::MaxPitch::get()
    {
        if (NativePointer->maxPitch.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->maxPitch.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void BoundOptions::MaxPitch::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->maxPitch = value.Value;
        }
        else
        {
            NativePointer->maxPitch = std::nullopt;
        }
    }

    System::Nullable<System::Double> BoundOptions::MinPitch::get()
    {
        if (NativePointer->minPitch.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->minPitch.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void BoundOptions::MinPitch::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->minPitch = value.Value;
        }
        else
        {
            NativePointer->minPitch = std::nullopt;
        }
    }
}
