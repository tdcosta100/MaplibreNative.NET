using MaplibreNative;
using Microsoft.Win32;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Media.Imaging;

namespace Example.Console
{
    internal class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            var size = new Size(2048, 2048);

            using var runLoop = new RunLoop(RunLoop.Type.Default);
            using var frontend = new HeadlessFrontend(size);
            using var map = new Map(frontend, new MapObserver(), new MapOptions().WithSize(size).WithMapMode(MapMode.Static));
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
                for (int i = 0; i < imageData!.Length; i += 4)
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
    }
}