using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using Microsoft.Win32;

namespace WallpaperPaste
{
    
    public partial class Form1 : Form
    {
        private int tickMinutes;
        private int changeMinutes;
        private bool random = true;
        private bool randomStart = false;
        private Random randomNum = new Random();

        public Form1()
        {
            InitializeComponent();
            this.Resize += new EventHandler(Form1_Resize);
            listBox1.KeyDown += new KeyEventHandler(listBox1_KeyDown);

            // close and hide the window
            this.Visible = false;
            this.WindowState = FormWindowState.Minimized;

            string appPath = Application.StartupPath;
            string dataPath = appPath + "\\userdata.dat";

            openFileDialog1.InitialDirectory = appPath;

            // read the data
            if (File.Exists(dataPath))
            {
                readData();
            }

            if (listBox1.Items.Count > 0)
            {
                // pick a random start image
                if (randomStart == true)
                {
                    randomNum.Next();
                    int index = randomNum.Next(listBox1.Items.Count);
                    listBox1.SelectedIndex = index;
                    Wallpaper newWall = (Wallpaper)listBox1.SelectedItem;

                    newWall.setWallpaper();
                }
            }

            // start the timer
            tickMinutes = 0;
            timer1.Interval = 60000;
            timer1.Start();
        }

        private void Form1_Resize(object sender, System.EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.Visible = false;
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 aboutBox1 = new AboutBox1();
            aboutBox1.Show();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void addWallpaperToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int i = 0;
            openFileDialog1.ShowDialog();
            
            foreach (string name in openFileDialog1.FileNames)
            {
                Wallpaper newWall = new Wallpaper(name, openFileDialog1.SafeFileNames.ElementAt<string>(i));
                listBox1.Items.Add(newWall);
                i++;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {
                Wallpaper selectedWall = (Wallpaper)listBox1.SelectedItem;
                selectedWall.style = "center";
            }

            updateImage();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {
                Wallpaper selectedWall = (Wallpaper)listBox1.SelectedItem;
                selectedWall.style = "tile";
            }

            updateImage();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {
                Wallpaper selectedWall = (Wallpaper)listBox1.SelectedItem;
                selectedWall.style = "stretch";
            }

            updateImage();
        }

        private void writeData()
        {
            string appPath = Application.StartupPath;
            string dataPath = appPath + "\\userdata.dat";


            FileInfo f = new FileInfo(dataPath);

            FileStream s = f.Open(FileMode.Truncate, FileAccess.ReadWrite);
            s.Close();

            BinaryWriter bw = new BinaryWriter(f.OpenWrite());

            int checkedVal;

            if (checkBox1.Checked == true)
            {
                checkedVal = 1;
            }
            else
            {
                checkedVal = 0;
            }

            bw.Write(random);
            bw.Write(randomStart);

            bw.Write(checkedVal);
            bw.Write(changeMinutes);

            foreach (Object wall in listBox1.Items)
            {
                Wallpaper current = (Wallpaper)wall;
                bw.Write(current.path);
                bw.Write(current.ToString());
                bw.Write(current.style);
            }

            bw.Close();
        }

        private void readData()
        {
            string path;
            string name;
            string style;

            string appPath = Application.StartupPath;
            string dataPath = appPath + "\\userdata.dat";

            FileInfo f = new FileInfo(dataPath);
            BinaryReader br = new BinaryReader(f.OpenRead());
         
            random = br.ReadBoolean();
            randomStart = br.ReadBoolean();

            if (br.ReadInt32() == 0)
            {
                checkBox1.Checked = false;
            }
            else
            {
                checkBox1.Checked = true;
            }

            checkBox2.Checked = random;
            checkBox3.Checked = randomStart;

            changeMinutes = br.ReadInt32();

            int days = (int)Math.Floor((decimal)changeMinutes / 1440);
            int hours = (int)Math.Floor((decimal)(changeMinutes - (days * 1440)) / 60);
            int minutes = changeMinutes - ((days * 1440) + (hours * 60));

            numericUpDown1.Value = days;
            numericUpDown2.Value = hours;
            numericUpDown3.Value = minutes;

            while (br.PeekChar() != -1)
            {
                path = br.ReadString();
                name = br.ReadString();
                style = br.ReadString();

                if (File.Exists(path))
                {
                    Wallpaper wall = new Wallpaper(path, name);
                    wall.style = style;

                    listBox1.Items.Add(wall);
                }
            }

            br.Close();

        }

        private void updateImage()
        {
            if (listBox1.SelectedItem == null)
                return;

            float deskHeight = Screen.PrimaryScreen.Bounds.Height;
            float deskWidth = Screen.PrimaryScreen.Bounds.Width;

            Wallpaper selectedWall = (Wallpaper)listBox1.SelectedItem;
            string path = selectedWall.path;

            if (File.Exists(path))
            {

                System.Drawing.Image image = System.Drawing.Image.FromFile(path);

                // stretched
                if (selectedWall.style == "stretch")
                {
                    pictureBox1.BackgroundImage = null;

                    System.Drawing.Image wallpaperThumb = image.GetThumbnailImage(200, 150, null, System.IntPtr.Zero);

                    pictureBox1.Image = wallpaperThumb;
                }

                // centered
                if (selectedWall.style == "center")
                {
                    pictureBox1.BackgroundImage = null;

                    float newWidth = (200 / deskWidth) * image.Width;
                    float newHeight = (150 / deskHeight) * image.Height;

                    System.Drawing.Image wallpaperThumb = image.GetThumbnailImage((int)newWidth, (int)newHeight, null, System.IntPtr.Zero);
                    pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;

                    pictureBox1.Image = wallpaperThumb;
                }

                // tiled
                if (selectedWall.style == "tile")
                {
                    pictureBox1.Image = null;

                    float newWidth = (200 / deskWidth) * image.Width;
                    float newHeight = (150 / deskHeight) * image.Height;

                    System.Drawing.Image wallpaperThumb = image.GetThumbnailImage((int)newWidth, (int)newHeight, null, System.IntPtr.Zero);
                    pictureBox1.BackgroundImage = wallpaperThumb;
                    pictureBox1.BackgroundImageLayout = ImageLayout.Tile;
                }
            }
            else
            {
                listBox1.Items.Remove(selectedWall);
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {
                updateImage();
            }
        }

        private void listBox1_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete && listBox1.SelectedItem != null)
            {
                int index = listBox1.SelectedIndex;

                listBox1.Items.Remove(listBox1.SelectedItem);
                pictureBox1.Image = null;
                pictureBox1.BackgroundImage = null;

                if (listBox1.Items.Count > 0)
                {

                    if (index > 0)
                    {
                        listBox1.SelectedIndex = index - 1;
                    }
                    else
                    {
                        listBox1.SelectedIndex = index;
                    }
                }

            }
        }


        private void button7_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {
                int index = listBox1.SelectedIndex;

                listBox1.Items.Remove(listBox1.SelectedItem);
                pictureBox1.Image = null;
                pictureBox1.BackgroundImage = null;

                if (listBox1.Items.Count > 0)
                {
                    if (index > 0)
                    {
                        listBox1.SelectedIndex = index - 1;
                    }
                    else
                    {
                        listBox1.SelectedIndex = index;
                    }
                }
            }
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.Visible = true;
                this.WindowState = FormWindowState.Normal;
            }
            else if (this.WindowState == FormWindowState.Normal)
            {
                this.WindowState = FormWindowState.Minimized;
                this.Visible = false;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (listBox1.Items.Count > 0 && changeMinutes <= tickMinutes)
            {
                int index;

                if (random == true)
                {
                    index = randomNum.Next(listBox1.Items.Count);
                }
                else
                {
                    index = (listBox1.SelectedIndex + 1)%listBox1.Items.Count;

                }

                listBox1.SelectedIndex = index;
                Wallpaper newWall = (Wallpaper)listBox1.SelectedItem;

                if (File.Exists(newWall.path))
                {
                    newWall.setWallpaper();

                    // reset timer
                    tickMinutes = 0;
                }
                else
                {
                    listBox1.Items.RemoveAt(index);
                }
            }
            else
            {
                tickMinutes++;
            }
        }

        private void updateMinutes()
        {
            changeMinutes = 1440 * (int)numericUpDown1.Value;
            changeMinutes += 60 * (int)numericUpDown2.Value;
            changeMinutes += (int)numericUpDown3.Value;
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            updateMinutes();
        }

        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            updateMinutes();
        }

        private void numericUpDown3_ValueChanged(object sender, EventArgs e)
        {
            updateMinutes();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            writeData();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            RegistryKey rkApp = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);

            if (checkBox1.Checked == true)
            {
                rkApp.SetValue("WallpaperPaste", Application.ExecutablePath.ToString());
            }
            else
            {
                rkApp.DeleteValue("WallpaperPaste", false);
            }

            rkApp.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {

                Wallpaper setWall = (Wallpaper)listBox1.SelectedItem;
                setWall.setWallpaper();

                // reset timer
                tickMinutes = 0;
            }
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked == true)
            {
                random = true;
            }
            else
            {
                random = false;
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked == true)
            {
                randomStart = true;
            }
            else
            {
                randomStart = false;
            }
        }

        private void helpToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Form2 helpForm = new Form2();
            helpForm.Show();
        }

        // move selection up
        private void button8_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem == null || listBox1.SelectedIndex == 0)
                return;

            int dest = listBox1.SelectedIndex - 1;
            int source = listBox1.SelectedIndex;

            // swap with one above it
            Object moveObject = listBox1.SelectedItem;

            listBox1.Items.RemoveAt(source);
            listBox1.Items.Insert(dest, moveObject);

            listBox1.SelectedIndex = dest;
        }

        // move selection down
        private void button5_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem == null || listBox1.SelectedIndex == listBox1.Items.Count - 1)
                return;

            int dest = listBox1.SelectedIndex + 1;
            int source = listBox1.SelectedIndex;

            // swap with one above it
            Object moveObject = listBox1.SelectedItem;

            listBox1.Items.RemoveAt(source);
            listBox1.Items.Insert(dest, moveObject);

            listBox1.SelectedIndex = dest;
        }

    }
}
