#include "ClientOptions.h"
#include "Enums.h"
#include "FileSource.h"
#include "FileSourceManager.h"
#include "ResourceOptions.h"
#include <mbgl/storage/file_source_manager.hpp>

namespace DOTNET_NAMESPACE
{
    FileSourceManager::FileSourceManager()
    {
    }

    FileSourceManager::~FileSourceManager()
    {
    }

    FileSource^ FileSourceManager::GetFileSource(FileSourceType type, ResourceOptions^ resourceOptions)
    {
        return gcnew FileSource(
            FileSource::CreateNativePointerHolder(
                new std::shared_ptr<mbgl::FileSource>(
                    std::move(
                        mbgl::FileSourceManager::get()->getFileSource((mbgl::FileSourceType)type, *resourceOptions->NativePointer)
                    )
                )
            )
        );
    }

    FileSource^ FileSourceManager::GetFileSource(FileSourceType type, ResourceOptions^ resourceOptions, ClientOptions^ clientOptions)
    {
        return gcnew FileSource(
            FileSource::CreateNativePointerHolder(
                new std::shared_ptr<mbgl::FileSource>(
                    std::move(
                        mbgl::FileSourceManager::get()->getFileSource((mbgl::FileSourceType)type, *resourceOptions->NativePointer, *clientOptions->NativePointer)
                    )
                )
            )
        );
    }
}