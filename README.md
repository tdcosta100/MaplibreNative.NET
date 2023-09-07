![MapLibre Logo](https://maplibre.org/img/maplibre-logo-big.svg)

# MaplibreNative.NET

This is a .NET wrapper to the [maplibre-native](https://github.com/maplibre/maplibre-native). It is meant to be used in Windows and works with .NET Framework and .NET Core.

## Using in your project

Just add a reference to the `MaplibreNative.NET.dll` (see below how to build from sources), and you can immediately use the classes in the `MaplibreNative` namespace.

This is a minimal example using the `HeadlessFrontend` renderer, in a project with .NET 7.0 (Windows) and WPF enabled:

```cs
using MaplibreNative;
using Microsoft.Win32;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Media.Imaging;

...

var size = new Size(2048, 2048);

using (var runLoop = new RunLoop(RunLoop.Type.Default))
using (var frontend = new HeadlessFrontend(size))
using (var map = new Map(frontend, new MapObserver(), new MapOptions().WithSize(size).WithMapMode(MapMode.Static)))
{
    map.Style.LoadURL("https://raw.githubusercontent.com/maplibre/demotiles/gh-pages/style.json");

    byte[]? imageData = null;

    map.RenderStill(new CameraOptions().WithZoom(0), MapDebugOptions.NoDebug, ex =>
    {
        var image = frontend.ReadStillImage();
        imageData = new byte[image.Bytes];
        Marshal.Copy(image.Data, imageData, 0, (int)image.Bytes);

        runLoop.Stop();
    });

    runLoop.Run();

    var saveDialog = new SaveFileDialog();
    saveDialog.Filter = "PNG Image|*.png";

    if (saveDialog.ShowDialog() ?? false)
    {
        for (int i = 0; i < imageData.Length; i += 4)
        {
            var temp = imageData[i];
            imageData[i] = imageData[i + 2];
            imageData[i + 2] = temp;
        }

        var bitmap = new WriteableBitmap((int)size.Width, (int)size.Height, 96, 96, System.Windows.Media.PixelFormats.Pbgra32, null);
        bitmap.WritePixels(new System.Windows.Int32Rect(0, 0, bitmap.PixelWidth, bitmap.PixelHeight), imageData, bitmap.BackBufferStride, 0);
        var encoder = new PngBitmapEncoder();
        encoder.Frames.Add(BitmapFrame.Create(bitmap));

        using (var file = new FileStream(saveDialog.FileName, FileMode.Create))
        {
            encoder.Save(file);
        }
    }
}

...
```
You can check other examples at the [Examples](https://github.com/tdcosta100/MaplibreNative.NET/tree/main/Examples) directory.

**Attention:** the examples have a reference to `MaplibreNative.NET.dll` located at `build\Release` subdirectory. So you have to build MaplibreNative.NET with `Release` configuration before building the examples.

## Building the sources

### Prerequisites

As this is a .NET build, `Microsoft Visual Studio` is required. This project was developed using a `Microsoft Visual Studio 2022` environment, but it should work with `Microsoft Visual Studio 2019` as well.

To install the required Visual Studio components, open Visual Studio Installer and check `Desktop Development with C++` option. Make sure `C++ CMake tools for Windows` is selected in the right pane. If `git` is not already installed, select `Git for Windows` option in `Individual Components`. When Visual Studio finishes the install process, everything is ready to start.

### Downloading sources

Open `x64 Native Tools Command Prompt for VS 2022` and then clone the repository:

```cmd
git clone --recurse-submodules -j8 https://github.com/tdcosta100/MaplibreNative.NET.git
cd MaplibreNative.NET
```

### Configuring

Configure the build with the following command:

```cmd
cmake . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

It will take some time to build and install all components on which the project depends.

### Alternative configure commands

To configure build with EGL support (ANGLE libraries will be build), use the following command:

```cmd
cmake . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DMLN_WITH_EGL=ON
```

To configure build with OSMesa (software rendering), use the following command:

```
cmake . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DMLN_WITH_OSMESA=ON
```

**WARNING:** as OSMesa doesn't have static libraries, it's necessary to copy `libglapi.dll`, `libGLESv2.dll` and `osmesa.dll` from `dependencies\maplibre-native\platform\windows\vendor\mesa3d\<arch>` to executable/dll directory you want to use, otherwise it won't run.

### Building

Finally, build the project with the following command:

```cmd
cmake --build build
```

### Building with Microsoft Visual Studio

Just omit the `-G Ninja` option from the configure command:

```cmd
cmake . -B build
```

The same can be done with alternative configure commands:

```cmd
cmake . -B build -DMLN_WITH_EGL=ON
```
or
```cmd
cmake . -B build -DMLN_WITH_OSMESA=ON
```

Once configure is done, open the file `build\MaplibreNative.NET.sln`. Build the target `ALL_BUILD` to build all targets, or pick a specific target. Don't forget to pick a build configuration (`Release`, `RelWithDebInfo`, `MinSizeRel` or `Debug`), otherwise the project will be built with default configuration (`Debug`).
