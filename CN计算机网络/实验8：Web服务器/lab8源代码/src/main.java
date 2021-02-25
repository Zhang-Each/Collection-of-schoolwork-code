import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class main {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(3772);
        while (true) {
            Socket socket = serverSocket.accept();
            new WebServer(socket, "./static").start();
        }
    }
}
