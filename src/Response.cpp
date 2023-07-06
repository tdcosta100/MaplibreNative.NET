#include "Convert.h"
#include "Response.h"
#include <mbgl/storage/response.hpp>

namespace DOTNET_NAMESPACE
{
    Response::Response() : NativeWrapper(new mbgl::Response())
    {
    }

    Response::Response(NativePointerHolder<mbgl::Response>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Response::~Response()
    {
    }

    System::Boolean Response::IsFresh()
    {
        return NativePointer->isFresh();
    }

    System::Boolean Response::IsUsable()
    {
        return NativePointer->isUsable();
    }

    Response::ResponseError^ Response::Error::get()
    {
        if (!_Error && NativePointer->error)
        {
            _Error = gcnew ResponseError(ResponseError::CreateNativePointerHolder(const_cast<mbgl::Response::Error*>(NativePointer->error.get())));
        }
        else if (_Error && !NativePointer->error)
        {
            _Error = nullptr;
        }
        
        return _Error;
    }

    System::Void Response::Error::set(ResponseError^ value)
    {
        _Error = value;

        if (value)
        {
            NativePointer->error = std::unique_ptr<const mbgl::Response::Error>(value->NativePointer);
        }
        else
        {
            NativePointer->error.reset();
        }
    }

    System::Boolean Response::NoContent::get()
    {
        return NativePointer->noContent;
    }

    System::Void Response::NoContent::set(System::Boolean value)
    {
        NativePointer->noContent = value;
    }

    System::Boolean Response::NotModified::get()
    {
        return NativePointer->notModified;
    }

    System::Void Response::NotModified::set(System::Boolean value)
    {
        NativePointer->notModified = value;
    }

    System::Boolean Response::MustRevalidate::get()
    {
        return NativePointer->mustRevalidate;
    }

    System::Void Response::MustRevalidate::set(System::Boolean value)
    {
        NativePointer->mustRevalidate = value;
    }

    cli::array<System::Byte>^ Response::Data::get()
    {
        if (NativePointer->data)
        {
            return Convert::ToSystemArray<uint8_t, System::Byte>(reinterpret_cast<uint8_t*>(const_cast<char*>(NativePointer->data->data())), static_cast<System::Int32>(NativePointer->data->size()));
        }
        
        return nullptr;
    }

    System::Void Response::Data::set(cli::array<System::Byte>^ value)
    {
        if (value)
        {
            NativePointer->data = std::shared_ptr<const std::string>(&Convert::ToStdString(value));
        }
        else
        {
            NativePointer->data.reset();
        }
    }

    System::Nullable<System::DateTime> Response::Modified::get()
    {
        if (NativePointer->modified.has_value())
        {
            return Convert::ToSystemDateTime(NativePointer->modified.value());
        }

        return System::Nullable<System::DateTime>();
    }

    System::Void Response::Modified::set(System::Nullable<System::DateTime> value)
    {
        if (value.HasValue)
        {
            NativePointer->modified = Convert::ToTimePoint<mbgl::Timestamp::duration>(value.Value);
        }
        else
        {
            NativePointer->modified = std::nullopt;
        }
    }

    System::Nullable<System::DateTime> Response::Expires::get()
    {
        if (NativePointer->expires.has_value())
        {
            return Convert::ToSystemDateTime(NativePointer->expires.value());
        }

        return System::Nullable<System::DateTime>();
    }

    System::Void Response::Expires::set(System::Nullable<System::DateTime> value)
    {
        if (value.HasValue)
        {
            NativePointer->expires = Convert::ToTimePoint<mbgl::Timestamp::duration>(value.Value);
        }
        else
        {
            NativePointer->expires = std::nullopt;
        }
    }

    System::String^ Response::ETag::get()
    {
        if (NativePointer->etag.has_value())
        {
            return Convert::ToSystemString(NativePointer->etag.value());
        }

        return nullptr;
    }

    System::Void Response::ETag::set(System::String^ value)
    {
        if (value)
        {
            NativePointer->etag = Convert::ToStdString(value);
        }
        else
        {
            NativePointer->etag = std::nullopt;
        }
    }

    Response::ResponseError::ResponseError(ErrorReason reason, System::String^ message, System::Nullable<System::DateTime> retryAfter)
        : NativeWrapper(new mbgl::Response::Error(
            (mbgl::Response::Error::Reason)reason,
            message
                ?
                Convert::ToStdString(message) 
                :
                std::string(),
            retryAfter.HasValue
                ?
                std::optional<mbgl::Timestamp>(Convert::ToTimePoint<mbgl::Timestamp::duration>(retryAfter.Value))
                :
                std::nullopt
        ))
    {
    }

    Response::ResponseError::~ResponseError()
    {
    }

    Response::ResponseError::ErrorReason Response::ResponseError::Reason::get()
    {
        return (Response::ResponseError::ErrorReason)NativePointer->reason;
    }

    System::Void Response::ResponseError::Reason::set(Response::ResponseError::ErrorReason value)
    {
        NativePointer->reason = (mbgl::Response::Error::Reason)value;
    }

    System::String^ Response::ResponseError::Message::get()
    {
        return Convert::ToSystemString(NativePointer->message);
    }

    System::Void Response::ResponseError::Message::set(System::String^ value)
    {
        NativePointer->message = Convert::ToStdString(value);
    }

    System::Nullable<System::DateTime> Response::ResponseError::RetryAfter::get()
    {
        if (NativePointer->retryAfter.has_value())
        {
            return System::Nullable<System::DateTime>(Convert::ToSystemDateTime(NativePointer->retryAfter.value()));
        }

        return System::Nullable<System::DateTime>();
    }

    System::Void Response::ResponseError::RetryAfter::set(System::Nullable<System::DateTime> value)
    {
        if (value.HasValue)
        {
            NativePointer->retryAfter = Convert::ToTimePoint<mbgl::Timestamp::duration>(value.Value);
        }
        else
        {
            NativePointer->retryAfter = std::nullopt;
        }
    }

    Response::ResponseError::ResponseError(NativePointerHolder<mbgl::Response::Error>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }
}
