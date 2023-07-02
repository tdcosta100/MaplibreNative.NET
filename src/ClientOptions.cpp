#include "Convert.h"
#include "ClientOptions.h"
#include <mbgl/util/client_options.hpp>

namespace DOTNET_NAMESPACE
{
    ClientOptions::ClientOptions() : NativeWrapper(new mbgl::ClientOptions())
    {
    }

    ClientOptions::ClientOptions(NativePointerHolder<mbgl::ClientOptions>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    ClientOptions::~ClientOptions()
    {
    }

    ClientOptions^ ClientOptions::Clone()
    {
        return gcnew ClientOptions(CreateNativePointerHolder(NativePointer->clone()));
    }

    ClientOptions^ ClientOptions::WithName(System::String^ name)
    {
        NativePointer->withName(Convert::ToStdString(name));

        return this;
    }

    ClientOptions^ ClientOptions::WithVersion(System::String^ version)
    {
        NativePointer->withVersion(Convert::ToStdString(version));
        
        return this;
    }

    System::String^ ClientOptions::Name::get()
    {
        return Convert::ToSystemString(NativePointer->name());
    }

    System::String^ ClientOptions::Version::get()
    {
        return Convert::ToSystemString(NativePointer->version());
    }
}
