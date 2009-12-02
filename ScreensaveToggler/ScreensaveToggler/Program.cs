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
            
            // workaround for seeing if screensaver is active
            if (key.GetValue("SCRNSAVE.EXE") == null)
                return false;
            return true;
        }

        public static void SetScreenSaverActive(bool setActive) 
        {
            RegistryKey key = Registry.CurrentUser.OpenSubKey(@"Control Panel\\Desktop", true);
            String screensaver;

            if (setActive)
            {
                // get what the screensaver was and restore screensaver key
                try
                {
                    screensaver = key.GetValue("Dummy").ToString();
                }
                catch (System.NullReferenceException)
                {
                    return;
                }

                key.CreateSubKey("SCRNSAVE.EXE");
                key.SetValue("SCRNSAVE.EXE", screensaver);
                key.DeleteValue("Dummy");
            }
            else
            {
                // making inactive
                // create a key to store the screensaver in and delete original
                screensaver = key.GetValue("SCRNSAVE.EXE").ToString();
                key.CreateSubKey("Dummy");
                key.SetValue("Dummy", screensaver);
                key.DeleteValue("SCRNSAVE.EXE");
                
            }

            key.Close();
        }

    }
}
