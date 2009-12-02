/**************************************************************
*  JavaServer.java                                            *
*  Lindsey Bieda                                              *
*                                                             *
* An extremely simple threaded java server that listens for   *
* a client, will accept a connection and then take and        *
* deliver messages from the server to the client and recieve  *
* messages from the client and echo them                      *
**************************************************************/

import java.util.*;
import java.io.*;
import java.net.*;

/********************************* EXAMPLE OUTPUT *******************************
Server running...
Client connected.
Client: Hi Server
Hi Client
*********************************************************************************/

// implements the runnable so we can use threads
public class JavaServer implements Runnable
{
	public static final int PORT = 4242;
	Thread readThread, writeThread;
	boolean online;
	PrintWriter output;
	BufferedReader input;
	Scanner scan;

	JavaServer() throws IOException
	{
		ServerSocket s = new ServerSocket(PORT);
		System.out.println("Server running...");

		try
		{
			// wait for someone to connect
			Socket socket = s.accept();
			online = true;

			System.out.println("Client connected.");

			// setup the input and output
			output = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
			input = new BufferedReader(new InputStreamReader(socket.getInputStream()));


			scan = new Scanner(System.in);

			// create and run the threads
			readThread = new Thread(this);
			readThread.start();
			writeThread = new Thread(this);
			writeThread.start();
		}
		catch (Exception  e)
		{
			System.out.println("Problem " + e + " with connection");
		}
	}


	// thread actions
	public void run()
	{
		while(online)
		{
			String inString;
			String outString;

			try
			{
				// while online handle user input and output from the client
				while(online)
				{

						if (Thread.currentThread() == readThread)
						{
							inString = input.readLine();

							System.out.println("Client: " + inString);
						}
						else if(Thread.currentThread() == writeThread)
						{
							if(scan.hasNext())
							{
								outString = scan.nextLine();
								output.println(outString);
							}

						}
				}
			}
			catch (IOException e)
			{
				System.out.println("Notice: Client went offline. Terminating");
				online = false;
			}
		}
	}

	public static void main(String[] args) throws IOException
	{
		// create the server object
		JavaServer js = new JavaServer();
	}
}
