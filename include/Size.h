#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class Size;
}

namespace DOTNET_NAMESPACE
{
    public ref class Size : NativeWrapper<mbgl::Size>
    {
    public:
        Size();
        Size(System::UInt32 width, System::UInt32 height);
        ~Size();

        property System::UInt32 Width { System::UInt32 get(); System::Void set(System::UInt32 value); }
        property System::UInt32 Height { System::UInt32 get(); System::Void set(System::UInt32 value); }
        property System::UInt32 Area { System::UInt32 get(); }
        property System::Single AspectRatio { System::Single get(); }
        property System::Boolean IsEmpty { System::Boolean get(); }

        static System::Boolean operator==(Size^ a, Size^ b);
        static System::Boolean operator!=(Size^ a, Size^ b);
    internal:
        Size(NativePointerHolder<mbgl::Size>^ nativePointerHolder);
    };
}
