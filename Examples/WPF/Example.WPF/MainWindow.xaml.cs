using MaplibreNative;
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Example.WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private nint _HDC;
        private nint _HGLRC;
        private WriteableBitmap? _Bitmap;
        private RunLoop? _RunLoop;
        private ExternalRenderingContextFrontend? _Frontend;
        private Map? _Map;

        private Point? _LastMousePosition;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _Bitmap = new WriteableBitmap((int)Map.Width, (int)Map.Height, 96, 96, PixelFormats.Bgra32, null);
            Map.Source = _Bitmap;

            _HDC = User32.GetDC(new WindowInteropHelper(this).Handle);

            var pfd = PixelFormatDescriptor.Build();
            pfd.Flags = PixelFormatDescriptorFlags.PFD_DRAW_TO_WINDOW | PixelFormatDescriptorFlags.PFD_SUPPORT_OPENGL | PixelFormatDescriptorFlags.PFD_GENERIC_ACCELERATED;

            var pixelFormat = Gdi32.ChoosePixelFormat(_HDC, ref pfd);

            if (!Gdi32.SetPixelFormat(_HDC, pixelFormat, ref pfd))
            {
                MessageBox.Show($"Error: could not set the pixel format for the map (HRESULT: 0x{Marshal.GetLastWin32Error():x})");
                Environment.Exit(-1);
            }

            _HGLRC = OpenGL32.wglCreateContext(_HDC);

            if (!OpenGL32.wglMakeCurrent(_HDC, _HGLRC))
            {
                MessageBox.Show($"Error: could not create the OpenGL context for the map (HRESULT: 0x{Marshal.GetLastWin32Error():x})");
                Environment.Exit(-1);
            }

            OpenGL32.Init();

            // Build the texture that will serve as the color attachment for the framebuffer.
            var color_renderbuffer = new uint[1];
            OpenGL32.glGenRenderbuffers!(1, color_renderbuffer);
            OpenGL32.glBindRenderbuffer!(OpenGL32.GL_RENDERBUFFER, color_renderbuffer[0]);
            OpenGL32.glRenderbufferStorage!(OpenGL32.GL_RENDERBUFFER, OpenGL32.GL_RGBA8, _Bitmap.PixelWidth, _Bitmap.PixelHeight);
            OpenGL32.glBindRenderbuffer(OpenGL32.GL_RENDERBUFFER, 0);

            // Build the texture that will serve as the depth attachment for the framebuffer.
            var depth_renderbuffer = new uint[1];
            OpenGL32.glGenRenderbuffers(1, depth_renderbuffer);
            OpenGL32.glBindRenderbuffer(OpenGL32.GL_RENDERBUFFER, depth_renderbuffer[0]);
            OpenGL32.glRenderbufferStorage(OpenGL32.GL_RENDERBUFFER, OpenGL32.GL_DEPTH_COMPONENT, _Bitmap.PixelWidth, _Bitmap.PixelHeight);
            OpenGL32.glBindRenderbuffer(OpenGL32.GL_RENDERBUFFER, 0);

            // Build the framebuffer.
            var framebuffer = new uint[1];
            OpenGL32.glGenFramebuffers!(1, framebuffer);
            OpenGL32.glBindFramebuffer!(OpenGL32.GL_FRAMEBUFFER, framebuffer[0]);
            OpenGL32.glFramebufferRenderbuffer!(OpenGL32.GL_FRAMEBUFFER, OpenGL32.GL_COLOR_ATTACHMENT0, OpenGL32.GL_RENDERBUFFER, color_renderbuffer[0]);
            OpenGL32.glFramebufferRenderbuffer(OpenGL32.GL_FRAMEBUFFER, OpenGL32.GL_DEPTH_ATTACHMENT, OpenGL32.GL_RENDERBUFFER, depth_renderbuffer[0]);

            var status = OpenGL32.glCheckFramebufferStatus!(OpenGL32.GL_FRAMEBUFFER);

            if (status != OpenGL32.GL_FRAMEBUFFER_COMPLETE)
            {
                MessageBox.Show("Error: could not create the framebuffer to show the map");
                Environment.Exit(-1);
            }

            var size = new MaplibreNative.Size((uint)_Bitmap.PixelWidth, (uint)_Bitmap.PixelHeight);

            _RunLoop = new RunLoop();
            _Frontend = new ExternalRenderingContextFrontend(nint.Zero, nint.Zero, size, 1.0f);
            _Map = new Map(_Frontend, new MapObserver(), new MapOptions().WithMapMode(MapMode.Continuous).WithSize(size).WithPixelRatio(1.0f));
            _Map.Style.LoadURL("https://raw.githubusercontent.com/maplibre/demotiles/gh-pages/style.json");

            Render();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosing(e);

            OpenGL32.wglMakeCurrent(nint.Zero, nint.Zero);
            OpenGL32.wglDeleteContext(_HGLRC);

            _HGLRC = nint.Zero;

            _Map!.Dispose();
            _Frontend!.Dispose();
            _RunLoop!.Dispose();
        }

        private void Render()
        {
            if (_HGLRC == nint.Zero)
            {
                return;
            }

            _RunLoop!.RunOnce();
            _Frontend!.Render();

            _Bitmap!.Lock();

            OpenGL32.glReadBuffer!(OpenGL32.GL_COLOR_ATTACHMENT0);
            OpenGL32.glReadPixels!(0, 0, _Bitmap.PixelWidth, _Bitmap.PixelHeight, OpenGL32.GL_RGBA, OpenGL32.GL_UNSIGNED_BYTE, _Bitmap.BackBuffer);

            _Bitmap.AddDirtyRect(new Int32Rect(0, 0, _Bitmap.PixelWidth, _Bitmap.PixelHeight));
            _Bitmap.Unlock();

            Task.Run(async () => { await Task.Delay(1); Dispatcher.Invoke(Render); });
        }

        private void Map_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Released && e.MiddleButton == MouseButtonState.Released && e.RightButton == MouseButtonState.Released)
            {
                _LastMousePosition = null;
                return;
            }
            else
            {
                var currentPosition = e.GetPosition(this);

                if (_LastMousePosition.HasValue)
                {
                    var movement = currentPosition - _LastMousePosition.Value;

                    if (e.LeftButton == MouseButtonState.Pressed)
                    {
                        _Map!.MoveBy(new PointDouble(movement.X, movement.Y));
                    }
                    
                    if (e.MiddleButton == MouseButtonState.Pressed)
                    {
                        _Map!.PitchBy(movement.Y);
                    }
                    
                    if (e.RightButton == MouseButtonState.Pressed)
                    {
                        _Map!.RotateBy(new PointDouble(_LastMousePosition.Value.X, _LastMousePosition.Value.Y), new PointDouble(currentPosition.X, currentPosition.Y));
                    }
                }

                _LastMousePosition = currentPosition;
            }
        }

        private void Map_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            var position = e.GetPosition(this);
            var factor = e.Delta / 1200.0;

            _Map!.ScaleBy(1 + factor, new PointDouble(position.X, position.Y));
        }
    }
}
