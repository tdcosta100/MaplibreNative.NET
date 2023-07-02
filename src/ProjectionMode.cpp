#include "ProjectionMode.h"
#include <mbgl/map/projection_mode.hpp>

namespace DOTNET_NAMESPACE
{
    ProjectionMode::ProjectionMode() : NativeWrapper(new mbgl::ProjectionMode())
    {
    }

    ProjectionMode::ProjectionMode(NativePointerHolder<mbgl::ProjectionMode>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    ProjectionMode::~ProjectionMode()
    {
    }

    ProjectionMode^ ProjectionMode::WithAxonometric(System::Boolean o)
    {
        NativePointer->withAxonometric(o);
        return this;
    }

    ProjectionMode^ ProjectionMode::WithXSkew(System::Double o)
    {
        NativePointer->withXSkew(o);
        return this;
    }

    ProjectionMode^ ProjectionMode::WithYSkew(System::Double o)
    {
        NativePointer->withYSkew(o);
        return this;
    }

    System::Nullable<System::Boolean> ProjectionMode::Axonometric::get()
    {
        if (NativePointer->axonometric.has_value())
        {
            return System::Nullable<System::Boolean>(NativePointer->axonometric.value());
        }

        return System::Nullable<System::Boolean>();
    }

    System::Void ProjectionMode::Axonometric::set(System::Nullable<System::Boolean> value)
    {
        if (value.HasValue)
        {
            NativePointer->axonometric = value.Value;
        }
        else
        {
            NativePointer->axonometric = std::nullopt;
        }
    }

    System::Nullable<System::Double> ProjectionMode::XSkew::get()
    {
        if (NativePointer->xSkew.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->xSkew.value());
        }
        
        return System::Nullable<System::Double>();
    }

    System::Void ProjectionMode::XSkew::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->xSkew = value.Value;
        }
        else
        {
            NativePointer->xSkew = std::nullopt;
        }
    }

    System::Nullable<System::Double> ProjectionMode::YSkew::get()
    {
        if (NativePointer->ySkew.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->ySkew.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void ProjectionMode::YSkew::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->ySkew = value.Value;
        }
        else
        {
            NativePointer->ySkew = std::nullopt;
        }
    }
}
