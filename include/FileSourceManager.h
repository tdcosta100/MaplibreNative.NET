#pragma once
#include "NativeWrapper.h"

namespace DOTNET_NAMESPACE
{
    ref class ClientOptions;
    ref class FileSource;
    ref class ResourceOptions;
    
    /// <summary>
    /// A singleton class responsible for managing file sources.
    /// 
    /// The FileSourceManager provides following functionality:
    /// 
    /// - provides access to file sources of a specific type and configuration
    /// - caches previously created file sources of a (type, configuration) tuples
    /// </summary>
    public ref class FileSourceManager
    {
    public:
        /// <summary>
        /// Returns shared instance of a file source for (type, options) tuple.
        /// Creates new instance via registered factory if needed. If new instance
        /// cannot be created, nullptr would be returned.
        /// </summary>
        /// <param name="type"></param>
        /// <param name="resourceOptions"></param>
        /// <returns></returns>
        static FileSource^ GetFileSource(FileSourceType type, ResourceOptions^ resourceOptions);

        /// <summary>
        /// Returns shared instance of a file source for (type, options) tuple.
        /// Creates new instance via registered factory if needed. If new instance
        /// cannot be created, nullptr would be returned.
        /// </summary>
        /// <param name="type"></param>
        /// <param name="resourceOptions"></param>
        /// <param name="clientOptions"></param>
        /// <returns></returns>
        static FileSource^ GetFileSource(FileSourceType type, ResourceOptions^ resourceOptions, ClientOptions^ clientOptions);
    private:
        FileSourceManager();
        ~FileSourceManager();
    };
}