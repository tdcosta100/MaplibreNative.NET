#include "Convert.h"
#include "Value.h"
#include <mapbox/compatibility/value.hpp>

mapbox::base::ValueArray ToValueArray(System::Collections::Generic::IEnumerable<DOTNET_NAMESPACE::Value^>^ a)
{
    mapbox::base::ValueArray valueArray;

    for each (DOTNET_NAMESPACE::Value^ value in a)
    {
        valueArray.emplace_back(*value->NativePointer);
    }

    return valueArray;
}

mapbox::base::ValueObject ToValueObject(System::Collections::Generic::IDictionary<System::String^, DOTNET_NAMESPACE::Value^>^ o)
{
    mapbox::base::ValueObject valueObject;

    for each(System::Collections::Generic::KeyValuePair<System::String^, DOTNET_NAMESPACE::Value^>^ keyValuePair in o)
    {
        valueObject.emplace(DOTNET_NAMESPACE::Convert::ToStdString(keyValuePair->Key), *keyValuePair->Value->NativePointer);
    }

    return valueObject;
}

namespace DOTNET_NAMESPACE
{
    Value::Value() : NativeWrapper(new mapbox::base::Value())
    {
    }

    Value::Value(System::Boolean v) : NativeWrapper(new mapbox::base::Value(v))
    {
    }

    Value::Value(System::String^ str) : NativeWrapper(new mapbox::base::Value(Convert::ToStdString(str)))
    {
    }

    Value::Value(System::SByte n) : Value((System::Int64)n)
    {
    }

    Value::Value(System::Int16 n) : Value((System::Int64)n)
    {
    }

    Value::Value(System::Int32 n) : Value((System::Int64)n)
    {
    }

    Value::Value(System::Int64 n) : NativeWrapper(new mapbox::base::Value(n))
    {
    }

    Value::Value(System::Byte n) : Value((System::UInt64)n)
    {
    }

    Value::Value(System::UInt16 n) : Value((System::UInt64)n)
    {
    }

    Value::Value(System::UInt32 n) : Value((System::UInt64)n)
    {
    }

    Value::Value(System::UInt64 n) : NativeWrapper(new mapbox::base::Value(n))
    {
    }

    Value::Value(System::Single n) : Value((System::Double)n)
    {
    }

    Value::Value(System::Double n) : NativeWrapper(new mapbox::base::Value(n))
    {
    }

    Value::Value(System::Collections::Generic::IEnumerable<Value^>^ a) : NativeWrapper(new mapbox::base::Value(ToValueArray(a)))
    {
    }

    Value::Value(System::Collections::Generic::IDictionary<System::String^, Value^>^ o) : NativeWrapper(new mapbox::base::Value(ToValueObject(o)))
    {
    }

    Value::Value(NativePointerHolder<mapbox::base::Value>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Value::~Value()
    {
    }

    System::Nullable<System::Int64> Value::GetInt()
    {
        if (int64_t* value = NativePointer->getInt())
        {
            return System::Nullable<System::Int64>(*value);
        }
        
        return System::Nullable<System::Int64>();
    }

    System::Nullable<System::UInt64> Value::GetUInt()
    {
        if (uint64_t* value = NativePointer->getUint())
        {
            return System::Nullable<System::UInt64>(*value);
        }
        
        return System::Nullable<System::UInt64>();
    }

    System::Nullable<System::Boolean> Value::GetBool()
    {
        if (bool* value = NativePointer->getBool())
        {
            return System::Nullable<System::Boolean>(*value);
        }
        
        return System::Nullable<System::Boolean>();
    }

    System::Nullable<System::Double> Value::GetDouble()
    {
        if (double* value = NativePointer->getDouble())
        {
            return System::Nullable<System::Double>(*value);
        }
        
        return System::Nullable<System::Double>();
    }

    System::Collections::Generic::IEnumerable<Value^>^ Value::GetArray()
    {
        if (mapbox::base::ValueArray* value = NativePointer->getArray())
        {
            cli::array<Value^>^ result = gcnew cli::array<Value^>(static_cast<System::Int32>(value->size()));

            for (int i = 0; i < result->Length; i++)
            {
                result[i] = gcnew Value(CreateNativePointerHolder((*value)[i]));
            }

            return result;
        }

        return nullptr;
    }

    System::Collections::Generic::IDictionary<System::String^, Value^>^ Value::GetObject()
    {
        if (mapbox::base::ValueObject* value = NativePointer->getObject())
        {
            System::Collections::Generic::IDictionary<System::String^, Value^>^ result = gcnew System::Collections::Generic::Dictionary<System::String^, Value^>();

            for (const std::pair<std::string, mapbox::base::Value>& pair : *value)
            {
                result->Add(Convert::ToSystemString(pair.first), gcnew Value(CreateNativePointerHolder(pair.second)));
            }

            return result;
        }

        return nullptr;
    }

    System::String^ Value::GetString()
    {
        if (std::string* value = NativePointer->getString())
        {
            return Convert::ToSystemString(*value);
        }

        return nullptr;
    }

    Value::operator bool()
    {
        return NativePointer->operator bool();
    }
}
