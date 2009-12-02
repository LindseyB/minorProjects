using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using Microsoft.Win32;
using System.Runtime.InteropServices;
using System.IO;

namespace WallpaperPaste
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }

    }

    class Wallpaper
    {
        const int SPI_SETDESKWALLPAPER = 20;
        const int SPIF_UPDATEINIFILE = 0x01;
        const int SPIF_SENDWININICHANGE = 0x02;

        private string filePath;
        private string fileName;
        private string wallStyle;

        public Wallpaper(string path, string name)
        {
            filePath = path;
            fileName = name;

            // default style stretched
            wallStyle = "stretch";
        }

        ~Wallpaper()
        {
            fileName = null;
            filePath = null;
            wallStyle = null; 
        }

        // dll stuff for setting wallpaper
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        static extern int SystemParametersInfo(
            int uAction, int uParam, string lpvParam, int fuWinIni);

        public override string ToString()
        {
            return fileName;
        }

        public string style
        {
            get { return wallStyle; }

            set { wallStyle = value; }
        }

        public string path
        {
            get { return filePath; }
        }

        public void setWallpaper()
        {
            RegistryKey key = Registry.CurrentUser.OpenSubKey("Control Panel\\Desktop", true);

            if (this.wallStyle == "stretch")
            {
                key.SetValue(@"WallpaperStyle", "2");
                key.SetValue(@"TileWallpaper", "0");
            }
            else if (this.wallStyle == "center")
            {
                key.SetValue(@"WallpaperStyle", "1");
                key.SetValue(@"TileWallpaper", "0"); 
            }
            else if (this.wallStyle == "tile")
            {
                key.SetValue(@"WallpaperStyle", "1");
                key.SetValue(@"TileWallpaper", "1");
            }

            SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, this.filePath, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

            key.Close();
        }
    }

}
