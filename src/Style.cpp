#include "Convert.h"
#include "FileSource.h"
#include "Style.h"
#include <mbgl/style/style.hpp>

namespace DOTNET_NAMESPACE
{
    Style::Style(FileSource^ fileSource, System::Single pixelRatio) : NativeWrapper(new mbgl::style::Style(*fileSource->NativePointer, pixelRatio))
    {
    }

    Style::Style(NativePointerHolder<mbgl::style::Style>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Style::~Style()
    {
    }

    System::Void Style::LoadJSON(System::String^ json)
    {
        NativePointer->loadJSON(Convert::ToStdString(json));
    }

    System::Void Style::LoadURL(System::String^ url)
    {
        NativePointer->loadURL(Convert::ToStdString(url));
    }

    System::String^ Style::GetJSON()
    {
        return Convert::ToSystemString(NativePointer->getJSON());
    }

    System::String^ Style::GetURL()
    {
        return Convert::ToSystemString(NativePointer->getURL());
    }

    System::String^ Style::GetName()
    {
        return Convert::ToSystemString(NativePointer->getName());
    }
}
