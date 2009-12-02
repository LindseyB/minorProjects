using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace ScreensaveToggler 
{
    class Program {

        static void Main(string[] args) {
            Console.WriteLine(GetScreenSaverActive());
            if (GetScreenSaverActive()) 
            {
                SetScreenSaverActive(false);
            }
            else 
            {
                SetScreenSaverActive(true);
            }    
        }

        public static bool GetScreenSaverActive() 
        {
            RegistryKey key = Registry.CurrentUser.OpenSubKey("Control Panel\\Desktop", true);
            
            // hackey way to tell if screensaver is enabled or disabled due to a bug with screensaveactive
            if (key.GetValue("SCRNSAVE.EXE") == null || key.GetValue("ScreenSaveTimeOut").ToString() ==  "0")
                return false;
            return true;
        }

        public static void SetScreenSaverActive(bool setActive) 
        {
            RegistryKey key = Registry.CurrentUser.OpenSubKey(@"Control Panel\\Desktop", true);

            // disabling the screen is done by setting the timeout value because screensaveactive
            // is always true no matter what
            if (setActive)
            {
                // set timeout to 30 minutes
                key.SetValue("ScreenSaveTimeOut", "1800");
            }
            else
            {
                // set timeout to nothing
                key.SetValue("ScreenSaveTimeOut", "0");
            }

            key.Close();
        }

    }
}
