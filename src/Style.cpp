#include "Convert.h"
#include "FileSource.h"
#include "RunLoop.h"
#include "Style.h"
#include <mbgl/style/style.hpp>

namespace
{
    using namespace ::DOTNET_NAMESPACE;

    void LoadJSOURLNHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action<System::String^>^> action,
        msclr::gcroot<System::String^> value
    )
    {
        action->Invoke(value);
        taskCompletionSource->SetResult(true);
    }
}

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
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &LoadJSOURLNHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<System::String^>^>(gcnew System::Action<System::String^>(this, &Style::LoadJSONInThread)),
                msclr::gcroot<System::String^>(json)
            )
        );

        taskCompletionSource->Task->Wait();
    }

    System::Void Style::LoadURL(System::String^ url)
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        RunLoop::Get()->NativePointer->ExecuteInThread(
            std::bind(
                &LoadJSOURLNHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action<System::String^>^>(gcnew System::Action<System::String^>(this, &Style::LoadURLInThread)),
                msclr::gcroot<System::String^>(url)
            )
        );

        taskCompletionSource->Task->Wait();
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

    System::Void Style::LoadJSONInThread(System::String^ json)
    {
        NativePointer->loadJSON(Convert::ToStdString(json));
    }

    System::Void Style::LoadURLInThread(System::String^ url)
    {
        NativePointer->loadURL(Convert::ToStdString(url));
    }
}
