import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

/**
 * Java program to create a simple HTTP Server to demonstrate how to use
 * ServerSocket and Socket class.
 * 
 * @author Javin Paul
 */
public class Testserver {

    public static void main(String args[]) throws IOException {

        ServerSocket server = new ServerSocket(8080);
        System.out.println("Listening for connection on port 8080 ....");
        while (true) {
            try (Socket socket = server.accept()) {
                System.out.println("New connection from "+socket.getInetAddress().toString());        
                
                Date today = new Date();
                String httpResponse = "HTTP/1.1 200 OK\r\n\r\n" + today;
                socket.getOutputStream().write(httpResponse.getBytes("UTF-8"));
                
                BufferedReader in =
                    new BufferedReader(
                        new InputStreamReader(socket.getInputStream()));
                String l;
                while((l=in.readLine())!=null) {
                    System.out.println(l);
                }
                System.out.println("Socket closed");
            }
        }
    }

}
