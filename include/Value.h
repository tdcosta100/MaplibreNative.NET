#pragma once
#include "NativeWrapper.h"
#include <mapbox/compatibility/value.hpp>

namespace DOTNET_NAMESPACE
{
    public ref class Value : NativeWrapper<mapbox::base::Value>
    {
    public:
        Value();
        Value(System::Boolean v);
        Value(System::String^ str);
        Value(System::SByte n);
        Value(System::Int16 n);
        Value(System::Int32 n);
        Value(System::Int64 n);
        Value(System::Byte n);
        Value(System::UInt16 n);
        Value(System::UInt32 n);
        Value(System::UInt64 n);
        Value(System::Single n);
        Value(System::Double n);
        Value(System::Collections::Generic::IEnumerable<Value^>^ a);
        Value(System::Collections::Generic::IDictionary<System::String^, Value^>^ o);
        ~Value();

        System::Nullable<System::Int64> GetInt();
        System::Nullable<System::UInt64> GetUInt();
        System::Nullable<System::Boolean> GetBool();
        System::Nullable<System::Double> GetDouble();
        System::Collections::Generic::IEnumerable<Value^>^ GetArray();
        System::Collections::Generic::IDictionary<System::String^, Value^>^ GetObject();
        System::String^ GetString();

        explicit operator bool();
    internal:
        Value(NativePointerHolder<mapbox::base::Value>^ nativePointerHolder);
    };
}
