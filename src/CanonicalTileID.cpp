#include "CanonicalTileID.h"
#include <mbgl/tile/tile_id.hpp>

namespace DOTNET_NAMESPACE
{
    CanonicalTileID::CanonicalTileID(System::Byte z, System::UInt32 x, System::UInt32 y)
        : NativeWrapper(new mbgl::CanonicalTileID(z, x, y))
    {
    }

    CanonicalTileID::CanonicalTileID(NativePointerHolder<mbgl::CanonicalTileID>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    CanonicalTileID::~CanonicalTileID()
    {
    }

    System::Boolean CanonicalTileID::IsChildOf(CanonicalTileID^ parent)
    {
        return NativePointer->isChildOf(*parent->NativePointer);
    }

    CanonicalTileID^ CanonicalTileID::ScaledTo(System::Byte z)
    {
        return gcnew CanonicalTileID(CreateNativePointerHolder(NativePointer->scaledTo(z)));
    }

    System::Collections::Generic::IEnumerable<CanonicalTileID^>^ CanonicalTileID::Children()
    {
        cli::array<CanonicalTileID^>^ managedResult = gcnew cli::array<CanonicalTileID^>(4);
        std::array<mbgl::CanonicalTileID, 4> nativeResult = NativePointer->children();

        for (int i = 0; i < nativeResult.size(); i++)
        {
            managedResult[i] = gcnew CanonicalTileID(CreateNativePointerHolder(nativeResult[i]));
        }

        return managedResult;
    }

    System::Byte CanonicalTileID::Z::get()
    {
        return NativePointer->z;
    }

    System::Void CanonicalTileID::Z::set(System::Byte value)
    {
        NativePointer->z = value;
    }

    System::UInt32 CanonicalTileID::X::get()
    {
        return NativePointer->x;
    }

    System::Void CanonicalTileID::X::set(System::UInt32 value)
    {
        NativePointer->x = value;
    }

    System::UInt32 CanonicalTileID::Y::get()
    {
        return NativePointer->y;
    }

    System::Void CanonicalTileID::Y::set(System::UInt32 value)
    {
        NativePointer->y = value;
    }

    System::Boolean CanonicalTileID::operator==(CanonicalTileID^ rhs)
    {
        return NativePointer->operator==(*rhs->NativePointer);
    }

    System::Boolean CanonicalTileID::operator!=(CanonicalTileID^ rhs)
    {
        return NativePointer->operator!=(*rhs->NativePointer);
    }

    System::Boolean CanonicalTileID::operator<(CanonicalTileID^ rhs)
    {
        return NativePointer->operator<(*rhs->NativePointer);
    }
}
