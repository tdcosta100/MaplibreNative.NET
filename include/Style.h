#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    namespace style
    {
        class Style;
    }
}

namespace DOTNET_NAMESPACE
{
    ref class CameraOptions;
    ref class FileSource;
    ref class TransitionOptions;

    public ref class Style : NativeWrapper<mbgl::style::Style>
    {
    public:
        Style(FileSource^ fileSource, System::Single pixelRatio);
        ~Style();

        System::Void LoadJSON(System::String^ json);
        System::Void LoadURL(System::String^ url);
        System::String^ GetJSON();
        System::String^ GetURL();
        System::String^ GetName();

        /*
        CameraOptions^ GetDefaultCamera();
        TransitionOptions^ GetTransitionOptions();
        System::Void SetTransitionOptions(TransitionOptions^ options);
        Light* getLight();
        const Light* getLight() const;

        void setLight(std::unique_ptr<Light>);

        // Images
        optional<Image> getImage(const std::string&) const;
        void addImage(std::unique_ptr<Image>);
        void removeImage(const std::string&);

        // Sources
        std::vector<      Source*> getSources();
        std::vector<const Source*> getSources() const;

        Source* getSource(const std::string&);
        const Source* getSource(const std::string&) const;

        void addSource(std::unique_ptr<Source>);
        std::unique_ptr<Source> removeSource(const std::string& sourceID);

        // Layers
        std::vector<      Layer*> getLayers();
        std::vector<const Layer*> getLayers() const;

        Layer* getLayer(const std::string&);
        const Layer* getLayer(const std::string&) const;

        void addLayer(std::unique_ptr<Layer>, const optional<std::string>& beforeLayerID = {});
        std::unique_ptr<Layer> removeLayer(const std::string& layerID);
        */
    internal:
        Style(NativePointerHolder<mbgl::style::Style>^ nativePointerHolder);
    private:
        System::Void LoadJSONInThread(System::String^ json);
        System::Void LoadURLInThread(System::String^ url);
    };
}
