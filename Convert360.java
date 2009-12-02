/**********************************************************
* Conver360.java - creates a batch file for converting
* many .AVI, .XVID, .MOV, and .MP4 files to WMV files the
* xbox360 can play using VideoLAN
*
* main() takes the user inputs and checkDir() generates a
* list of files to be converted given those inputs
*
* Lindsey Bieda
**********************************************************/


import java.io.*;
import java.util.*;


public class Convert360
{

	public static void main(String[] args)
	{

		Scanner keyIn = new Scanner(System.in);
		String vlcPath, inPath, outPath;
		Vector<String> fileList = null;
		String fileName, curFile;
		File convert = null;

		System.out.println("Automated BAT file generator for VLC\n");

		System.out.print("Please enter the path for vlc (with trailing \\): ");
		vlcPath = keyIn.nextLine() + "vlc";

		System.out.print("Please enter the path where the files should but output (with trailing \\): ");
		outPath = keyIn.nextLine();

		System.out.print("Please enter the path where the files are located (with trailing \\): ");
		inPath = keyIn.nextLine();
		System.out.println();

		//generate the list of files
		fileList = checkDir(inPath);

		try
		{
			convert = new File("convert.bat");
			boolean created = convert.createNewFile();

			if(created)
			{
				//new file made
			}
			else
			{
				//file already exists
			}

			FileOutputStream output = new FileOutputStream("convert.bat");
			PrintStream filePrint = new PrintStream(output);

			System.out.println("\nWriting batch file...");

			for(int i=0; i<fileList.size(); i++)
			{
				curFile = fileList.elementAt(i);
				fileName = curFile.substring(curFile.lastIndexOf('\\')+1);

				//write the string to the file
				filePrint.println("\"" + vlcPath + "\" -vvv \"" + curFile + "\" --sout=#transcode{vcodec=WMV2,scale=1,acodec=wma,ab=96,channels=2,samplerate=44100,soverlay}:duplicate{dst=std{access=file,mux=asf,dst=\""+ outPath + fileName.substring(0, fileName.lastIndexOf('.')) +".wmv\"}} vlc:quit");
			}

			filePrint.close();
			System.out.println("DONE");

		}
		catch(IOException e){}

	}

	//method for checking a directory for valid files
	public static Vector<String> checkDir(String dir)
	{
		File inputDir = new File(dir);
		File[] inputs = inputDir.listFiles();
		Vector<String> list = new Vector<String>();
		String ext, fileName;

		for(int i=0; i<inputs.length; i++)
		{

			//if it is a directory dive into it
			if(inputs[i].isDirectory())
			{
				list.addAll(checkDir(inputs[i].toString()));
			}
			//if it is a file add it to the list
			else
			{
				fileName = inputs[i].toString();

				//finds the file extension
				ext = fileName.substring(fileName.lastIndexOf('.')+1);
				ext = ext.toLowerCase();

				//if the file is of a valid format add it
				if(ext.equals("avi") || ext.equals("xvid") || ext.equals("mov") || ext.equals("mp4"))
				{
					list.add(inputs[i].toString());
				}
			}
		}

		return list;
	}

}