package Server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.sql.SQLException;
import java.util.Iterator;
import java.util.Vector;

public class ClientThread implements Runnable {
    private Socket socket;
    private Server server;
    private boolean isRunning;
    private String name;

    public BufferedReader input = null;
    public PrintWriter output = null;

    public ClientThread(Socket socket, Server server) {
        this.socket = socket;
        this.server = server;
        this.server.addClient(this);
        isRunning = true;
    }

    @Override
    public void run() {
        try {
            input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            output = new PrintWriter(socket.getOutputStream(), true);
            System.out.println("服务端建立新的子线程：" + socket.getInetAddress());
            this.receiveInfo();
            System.out.println("子线程运行结束.......服务器依然在运行......");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendInfo(String things) {
        output.println(things);
    }

    public void sendHistory(Vector<String> history) {
        Iterator<String> it = history.iterator();
        while (it.hasNext()) {
            this.sendInfo("!history!" + it.next());
        }

    }

    public void receiveInfo() {
        String line;
        try {
            while (isRunning) {
                Thread.sleep(10);
                line = input.readLine();
                if (!line.isEmpty()) {
                    String msg = "服务端收到消息：" + this.socket.getInetAddress() + " " + line;
                    System.out.println(msg);
                    if (line.startsWith("!register!")) {
                        this.name = line.substring(10);
                        System.out.println("当前连接用户：" + name);
                        this.server.sendToAllClient("!list!" + name);
                    } else if (line.startsWith("!login!")) {
                        //登录处理部分
                        String info = line.substring(7);
                        int pos = info.indexOf(' ');
                        String name = info.substring(0, pos), pass = info.substring(pos + 1);
                        System.out.println("输入的用户名和密码是：\n" + name + "\n" + pass);
                        if (this.server.checkLogin(name, pass)) {
                            this.sendInfo("!login!1");
                        } else {
                            this.sendInfo("!login!2");
                        }
                    } else if (line.startsWith("!msg!")) {
                        //收发聊天消息的处理部分,广播给所有的客户端
                        this.server.sendToAllClient(line);
                        this.server.storeMessageToDB(line, this.name);
                    } else if (line.startsWith("!history!")) {
                        this.sendHistory(this.server.selectHistoryMessageFromDB());
                    } else if (line.startsWith("!logout!")) {
                        this.server.removeClient(this);
                        this.input.close();
                        this.output.close();
                        this.socket.close();
                        System.out.println("用户登出！");
                        return;
                    }
                }

            }
        } catch (InterruptedException | IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}
