#include "CameraOptions.h"
#include "EdgeInsets.h"
#include "LatLng.h"
#include "Point.h"
#include <mbgl/map/camera.hpp>

namespace DOTNET_NAMESPACE
{
    CameraOptions::CameraOptions() : NativeWrapper(new mbgl::CameraOptions())
    {
    }

    CameraOptions::CameraOptions(NativePointerHolder<mbgl::CameraOptions>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    CameraOptions::~CameraOptions()
    {
    }

    CameraOptions^ CameraOptions::WithCenter(LatLng^ o)
    {
        if (o)
        {
            NativePointer->withCenter(*o->NativePointer);
        }
        else
        {
            NativePointer->withCenter(std::nullopt);
        }
        
        return this;
    }

    CameraOptions^ CameraOptions::WithPadding(EdgeInsets^ p)
    {
        if (p)
        {
            NativePointer->withPadding(*p->NativePointer);
        }
        else
        {
            NativePointer->withPadding(std::nullopt);
        }
        
        return this;
    }

    CameraOptions^ CameraOptions::WithAnchor(System::Nullable<ScreenCoordinate> o)
    {
        if (o.HasValue)
        {
            NativePointer->withAnchor(mbgl::ScreenCoordinate(o.Value.X, o.Value.Y));
        }
        else
        {
            NativePointer->withAnchor(std::nullopt);
        }

        return this;
    }

    CameraOptions^ CameraOptions::WithZoom(System::Nullable<System::Double> o)
    {
        if (o.HasValue)
        {
            NativePointer->withZoom(o.Value);
        }
        else
        {
            NativePointer->withZoom(std::nullopt);
        }
        
        return this;
    }

    CameraOptions^ CameraOptions::WithBearing(System::Nullable<System::Double> o)
    {
        if (o.HasValue)
        {
            NativePointer->withBearing(o.Value);
        }
        else
        {
            NativePointer->withBearing(std::nullopt);
        }

        return this;
    }

    CameraOptions^ CameraOptions::WithPitch(System::Nullable<System::Double> o)
    {
        if (o.HasValue)
        {
            NativePointer->withPitch(o.Value);
        }
        else
        {
            NativePointer->withPitch(std::nullopt);
        }

        return this;
    }

    LatLng^ CameraOptions::Center::get()
    {
        if (!_Center && NativePointer->center.has_value())
        {
            _Center = gcnew LatLng(LatLng::CreateNativePointerHolder(&NativePointer->center.value(), false));
        }
        else if (_Center && !NativePointer->center.has_value())
        {
            _Center = nullptr;
        }
        
        return _Center;
    }

    System::Void CameraOptions::Center::set(LatLng^ value)
    {
        _Center = value;
        NativePointer->center = *value->NativePointer;
    }

    EdgeInsets^ CameraOptions::Padding::get()
    {
        if (!_Padding && NativePointer->padding.has_value())
        {
            _Padding = gcnew EdgeInsets(EdgeInsets::CreateNativePointerHolder(&NativePointer->padding.value(), false));
        }
        else if (_Padding && !NativePointer->padding.has_value())
        {
            _Padding = nullptr;
        }

        return _Padding;
    }

    System::Void CameraOptions::Padding::set(EdgeInsets^ value)
    {
        _Padding = value;
        NativePointer->padding = *value->NativePointer;
    }

    System::Nullable<ScreenCoordinate> CameraOptions::Anchor::get()
    {
        if (!_Anchor.HasValue && NativePointer->anchor.has_value())
        {
            _Anchor = System::Nullable<ScreenCoordinate>(ScreenCoordinate(NativePointer->anchor.value()));
        }
        else if (_Anchor.HasValue && !NativePointer->anchor.has_value())
        {
            _Anchor = System::Nullable<ScreenCoordinate>();
        }

        return _Anchor;
    }

    System::Void CameraOptions::Anchor::set(System::Nullable<ScreenCoordinate> value)
    {
        _Anchor = value;

        if (_Anchor.HasValue)
        {
            NativePointer->anchor = mbgl::ScreenCoordinate(value.Value.X, value.Value.Y);
        }
        else
        {
            NativePointer->anchor = std::nullopt;
        }
    }

    System::Nullable<System::Double> CameraOptions::Zoom::get()
    {
        if (NativePointer->zoom.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->zoom.value());
        }
        
        return System::Nullable<System::Double>();
    }

    System::Void CameraOptions::Zoom::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->zoom = value.Value;
        }
        else
        {
            NativePointer->zoom = std::nullopt;
        }
    }

    System::Nullable<System::Double> CameraOptions::Bearing::get()
    {
        if (NativePointer->bearing.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->bearing.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void CameraOptions::Bearing::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->bearing = value.Value;
        }
        else
        {
            NativePointer->bearing = std::nullopt;
        }
    }

    System::Nullable<System::Double> CameraOptions::Pitch::get()
    {
        if (NativePointer->pitch.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->pitch.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void CameraOptions::Pitch::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->pitch = value.Value;
        }
        else
        {
            NativePointer->pitch = std::nullopt;
        }
    }

    System::Boolean CameraOptions::operator==(CameraOptions^ a, CameraOptions^ b)
    {
        return *a->NativePointer == *b->NativePointer;
    }

    System::Boolean CameraOptions::operator!=(CameraOptions^ a, CameraOptions^ b)
    {
        return *a->NativePointer != *b->NativePointer;
    }
}
