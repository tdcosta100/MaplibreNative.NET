#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class ClientOptions;
}

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Holds values for client options.
    /// </summary>
    public ref class ClientOptions : NativeWrapper<mbgl::ClientOptions>
    {
    public:
        /// <summary>
        /// Constructs a ClientOptions object with default values.
        /// </summary>
        ClientOptions();
        ~ClientOptions();

        ClientOptions^ Clone();

        /// <summary>
        /// Sets the client name.
        /// </summary>
        /// <param name="name">Client name.</param>
        /// <returns>ClientOptions for chaining options together.</returns>
        ClientOptions^ WithName(System::String^ name);

        /// <summary>
        /// Sets the client version.
        /// </summary>
        /// <param name="version">Client version.</param>
        /// <returns>ClientOptions for chaining options together.</returns>
        ClientOptions^ WithVersion(System::String^ version);

        /// <summary>
        /// Gets the previously set (or default) client name.
        /// </summary>
        property System::String^ Name { System::String^ get(); }

        /// <summary>
        /// Gets the previously set (or default) client version.
        /// </summary>
        property System::String^ Version { System::String^ get(); }
    internal:
        ClientOptions(NativePointerHolder<mbgl::ClientOptions>^ nativePointerHolder);
    };
}
