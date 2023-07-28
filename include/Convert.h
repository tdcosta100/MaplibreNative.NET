#pragma once
#include "NativePointerHolder.h"
#include "Point.h"
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <msclr/marshal_cppstd.h>

namespace
{
    // Ticks at 1970-01-01T00:00:00Z
    const System::UInt64 epochTicks = 621355968000000000;
}

namespace DOTNET_NAMESPACE
{
    class Convert
    {
    public:
        template <typename T, typename U>
        static System::Boolean IsInstanceOf(U u)
        {
            return dynamic_cast<T>(u) != nullptr;
        }

        static msclr::gcroot<System::String^> NativeToSystemString(const std::string& string)
        {
            return msclr::gcroot<System::String^>(msclr::interop::marshal_as<System::String^>(string));
        }

        static System::String^ ToSystemString(const std::string& string)
        {
            return msclr::interop::marshal_as<System::String^>(string);
        }

        static std::string NativeToStdString(msclr::gcroot<System::String^> string)
        {
            return msclr::interop::marshal_as<std::string>(static_cast<System::String^>(string));
        }

        static std::string ToStdString(System::String^ string)
        {
            return msclr::interop::marshal_as<std::string>(string);
        }

        static std::string ToStdString(cli::array<System::Byte>^ array)
        {
            pin_ptr<System::Byte> pointer = &array[0];

            return std::string(reinterpret_cast<char*>(pointer), array->Length);
        }

        static System::DateTime ToSystemDateTime(std::chrono::time_point<std::chrono::system_clock> dateTime)
        {
            return System::DateTime(std::chrono::time_point_cast<std::chrono::nanoseconds>(dateTime).time_since_epoch().count() / 100 + epochTicks);
        }

        template <typename Duration>
        static std::chrono::time_point<std::chrono::system_clock, Duration> ToTimePoint(System::DateTime^ dateTime)
        {
            return std::chrono::time_point_cast<Duration>(
                std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>(
                    std::chrono::nanoseconds((dateTime->Ticks - epochTicks) * 100)
                    )
                );
        }

        template <typename Duration>
        static System::TimeSpan ToSystemTimeSpan(Duration duration)
        {
            return System::TimeSpan::FromTicks(std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() / 100);
        }

        template<typename Duration>
        static Duration ToDuration(System::TimeSpan timeSpan)
        {
            return std::chrono::duration_cast<Duration>(std::chrono::nanoseconds(timeSpan.Ticks * 100));
        }

        template <typename TypeFrom, typename TypeTo>
        static cli::array<TypeTo>^ ToSystemArray(TypeFrom* sourceArray, System::Int32 size)
        {
            cli::array<TypeTo>^ result = gcnew cli::array<TypeTo^>(size);

            for (int i = 0; i < result->Length; i++)
            {
                result[i] = gcnew TypeTo(NativePointerHolder<TypeFrom>::Create(&sourceArray[i]));
            }

            return result;
        }

        template<>
        static cli::array<System::Byte>^ ToSystemArray<uint8_t, System::Byte>(uint8_t* sourceArray, System::Int32 size)
        {
            cli::array<System::Byte>^ result = gcnew cli::array<System::Byte>(size);

            System::Runtime::InteropServices::Marshal::Copy(System::IntPtr(sourceArray), result, 0, size);

            return result;
        }

        template <typename TypeFrom, typename TypeTo, size_t size>
        static cli::array<TypeTo^>^ ToSystemArray(std::array<TypeFrom, size> sourceArray)
        {
            cli::array<TypeTo^>^ result = gcnew cli::array<TypeTo^>(size);

            for (int i = 0; i < result->Length; i++)
            {
                result[i] = gcnew TypeTo(NativePointerHolder<TypeFrom>::Create(&sourceArray[i]));
            }

            return result;
        }

        template <typename TypeFrom, typename TypeTo>
        static System::Collections::Generic::IEnumerable<TypeTo>^ ToSystemIEnumerable(std::vector<TypeFrom> source, std::function<TypeTo(const TypeFrom&)> converter)
        {
            cli::array<TypeTo>^ result = gcnew cli::array<TypeTo>(static_cast<System::Int32>(source.size()));

            for (int i = 0; i < result->Length; i++)
            {
                result[i] = converter(source[i]);
            }

            return result;
        }

        template <typename TypeFrom, typename TypeTo>
        static std::vector<TypeTo> ToStdVector(System::Collections::Generic::IEnumerable<TypeFrom>^ source)
        {
            std::vector<TypeTo> result;

            for each(TypeFrom element in source)
            {
                result.emplace_back(element);
            }

            return result;
        }

        template <typename TypeFrom, typename TypeTo>
        static std::vector<TypeTo> ToStdVector(msclr::gcroot<System::Collections::Generic::IEnumerable<TypeFrom>^> source, std::function<TypeTo(TypeFrom)> converter)
        {
            std::vector<TypeTo> result;

            for each(TypeFrom element in static_cast<System::Collections::Generic::IEnumerable<TypeFrom>^>(source))
            {
                result.emplace_back(converter(element));
            }

            return result;
        }

        template<>
        static std::vector<std::string> ToStdVector<System::String^, std::string>(System::Collections::Generic::IEnumerable<System::String^>^ source)
        {
            std::vector<std::string> result;

            for each(System::String^ element in source)
            {
                result.emplace_back(Convert::ToStdString(element));
            }

            return result;
        }

        static PointDouble ToPoint(mbgl::Point<double> point)
        {
            return PointDouble(point.x, point.y);
        }

        static PointShort ToPoint(mbgl::Point<int16_t> point)
        {
            return PointShort(point.x, point.y);
        }

        static PointUInt ToPoint(mbgl::Point<uint32_t> point)
        {
            return PointUInt(point.x, point.y);
        }

        static mbgl::Point<double> ToNativePoint(PointDouble point)
        {
            return mbgl::Point<double>(point.X, point.Y);
        }

        static mbgl::Point<int16_t> ToNativePoint(PointShort point)
        {
            return mbgl::Point<int16_t>(point.X, point.Y);
        }

        static mbgl::Point<uint32_t> ToNativePoint(PointUInt point)
        {
            return mbgl::Point<uint32_t>(point.X, point.Y);
        }
    };
}
