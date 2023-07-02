#include "FreeCameraOptions.h"
#include "LatLng.h"
#include "Vector.h"
#include <mbgl/map/camera.hpp>

namespace DOTNET_NAMESPACE
{
    FreeCameraOptions::FreeCameraOptions() : NativeWrapper(new mbgl::FreeCameraOptions())
    {
    }

    FreeCameraOptions::FreeCameraOptions(NativePointerHolder<mbgl::FreeCameraOptions>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    FreeCameraOptions::~FreeCameraOptions()
    {
    }

    System::Void FreeCameraOptions::LookAtPoint(LatLng^ location)
    {
        NativePointer->lookAtPoint(*location->NativePointer);
    }

    System::Void FreeCameraOptions::LookAtPoint(LatLng^ location, Vec3^ upVector)
    {
        NativePointer->lookAtPoint(*location->NativePointer, *upVector->NativePointer);
    }

    System::Void FreeCameraOptions::SetPitchBearing(System::Double pitch, System::Double bearing)
    {
        NativePointer->setPitchBearing(pitch, bearing);
    }

    Vec3^ FreeCameraOptions::Position::get()
    {
        if (NativePointer->position.has_value())
        {
            return gcnew Vec3(Vec3::CreateNativePointerHolder(NativePointer->position.value()));
        }

        return nullptr;
    }

    System::Void FreeCameraOptions::Position::set(Vec3^ value)
    {
        if (value)
        {
            NativePointer->position = *value->NativePointer;
        }
        else
        {
            NativePointer->position = std::nullopt;
        }
    }

    Vec4^ FreeCameraOptions::Orientation::get()
    {
        if (NativePointer->orientation.has_value())
        {
            return gcnew Vec4(Vec4::CreateNativePointerHolder(NativePointer->orientation.value()));
        }
        
        return nullptr;
    }

    System::Void FreeCameraOptions::Orientation::set(Vec4^ value)
    {
        if (value)
        {
            NativePointer->orientation = *value->NativePointer;
        }
        else
        {
            NativePointer->orientation = std::nullopt;
        }
    }

    LatLngAltitude^ FreeCameraOptions::Location::get()
    {
        if (NativePointer->getLocation().has_value())
        {
            return gcnew LatLngAltitude(LatLngAltitude::CreateNativePointerHolder(NativePointer->getLocation().value()));
        }

        return nullptr;
    }

    System::Void FreeCameraOptions::Location::set(LatLngAltitude^ value)
    {
        NativePointer->setLocation(*value->NativePointer);
    }
}
