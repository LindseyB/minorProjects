/**************************************************************
*  JavaClient.java                                            *
*  Lindsey Bieda                                              *
*                                                             *
* An extremely simple threaded java client that connects to a *
* server and recieves and sends messages.                     *
**************************************************************/

import java.util.*;
import java.io.*;
import java.net.*;

/********************************* EXAMPLE OUTPUT *******************************
Connected to socket: Socket[addr=localhost/127.0.0.1,port=4242,localport=50177]

Hi Server
Server: Hi Client
*********************************************************************************/

// implements the runnable so we can use threads
public class JavaClient implements Runnable
{
	public static final int PORT = 4242;
	Thread readThread, writeThread;
	boolean online;
	PrintWriter output;
	BufferedReader input;
	Scanner scan;

	public JavaClient()
	{
		try
		{
			// connect to local host
			InetAddress addr = InetAddress.getByName("localhost");
			Socket socket = new Socket(addr, PORT);

			System.out.println(" Connected to socket: " + socket);
			online = true;

			// setup input and output for the socket
			output = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
			input = new BufferedReader(new InputStreamReader(socket.getInputStream()));

			// create and run the threads
			readThread = new Thread(this);
			readThread.start();
			writeThread = new Thread(this);
			writeThread.start();

			scan = new Scanner(System.in);
		}
		catch( Exception e)
		{
			System.out.println("Problem " + e + " with connection");
		}
	}


	// thread actions
	public void run()
	{
		String userInput;
		String servOutput;

		try
		{
			// while online handle user input and output from the server
			while(online)
			{

					if (Thread.currentThread() == readThread)
					{
						servOutput = input.readLine();
						System.out.println("Server: " + servOutput);
					}
					else if(Thread.currentThread() == writeThread)
					{
						if(scan.hasNext())
						{
							userInput = scan.nextLine();
							output.println(userInput);
						}
					}
			}
		}
		catch (IOException e)
		{
			System.out.println("Notice: Server went offline. Terminating");
			online = false;
		}
	}

	public static void main(String[] args)
	{
		// create the client object
		JavaClient jc = new JavaClient();
	}
}