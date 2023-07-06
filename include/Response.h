#pragma once
#include "NativeWrapper.h"
#include <mbgl/storage/response.hpp>

namespace DOTNET_NAMESPACE
{
    public ref class Response : NativeWrapper<mbgl::Response>
    {
    public:
        ref class ResponseError;
        Response();
        ~Response();

        System::Boolean IsFresh();

        /// <summary>
        /// Indicates whether we are allowed to use this response according to HTTP
        /// caching rules. It may or may not be stale.
        /// </summary>
        /// <returns></returns>
        System::Boolean IsUsable();

        /// <summary>
        /// When this property is <see langword="null"/>, the response was successful.
        /// </summary>
        property ResponseError^ Error { ResponseError^ get(); System::Void set(ResponseError^ value); }

        /// <summary>
        /// This is set to <see langword="true"/> for 204 Not Modified responses, and, for backward
        /// compatibility, for 404 Not Found responses for tiles.
        /// </summary>
        property System::Boolean NoContent { System::Boolean get(); System::Void set(System::Boolean value); }

        /// <summary>
        /// This is set to <see langword="true"/> for 304 Not Modified responses.
        /// </summary>
        property System::Boolean NotModified { System::Boolean get(); System::Void set(System::Boolean value); }

        /// <summary>
        /// This is set to <see langword="true"/> when the server requested that no expired resources
        /// be used by specifying "Cache-Control: must-revalidate".
        /// </summary>
        property System::Boolean MustRevalidate { System::Boolean get(); System::Void set(System::Boolean value); }

        /// <summary>
        /// The actual data of the response. Present only for non-error, non-notModified responses.
        /// </summary>
        property cli::array<System::Byte>^ Data { cli::array<System::Byte>^ get(); System::Void set(cli::array<System::Byte>^ value); }

        property System::Nullable<System::DateTime> Modified { System::Nullable<System::DateTime> get(); System::Void set(System::Nullable<System::DateTime> value); }
        property System::Nullable<System::DateTime> Expires { System::Nullable<System::DateTime> get(); System::Void set(System::Nullable<System::DateTime> value); }
        property System::String^ ETag { System::String^ get(); System::Void set(System::String^ value); }
    internal:
        Response(NativePointerHolder<mbgl::Response>^ nativePointerHolder);
    private:
        ResponseError^ _Error;
    };

    ref class Response::ResponseError : NativeWrapper<mbgl::Response::Error>
    {
    public:
        enum class ErrorReason : System::Byte
        {
            Success = 1,
            NotFound = 2,
            Server = 3,
            Connection = 4,
            RateLimit = 5,
            Other = 6,
        };

        ResponseError(ErrorReason reason, System::String^ message, System::Nullable<System::DateTime> retryAfter);
        ~ResponseError();

        property ErrorReason Reason { ErrorReason get(); System::Void set(ErrorReason value); }

        /// <summary>
        /// An error message from the request handler, e.g. a server message or a
        /// system message informing the user about the reason for the failure.
        /// </summary>
        property System::String^ Message { System::String^ get(); System::Void set(System::String^ value); }
        property System::Nullable<System::DateTime> RetryAfter { System::Nullable<System::DateTime> get(); System::Void set(System::Nullable<System::DateTime> value); }
    internal:
        ResponseError(NativePointerHolder<mbgl::Response::Error>^ nativePointerHolder);
    };
}
