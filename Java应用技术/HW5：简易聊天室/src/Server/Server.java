package Server;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.sql.*;
import java.util.Iterator;
import java.util.Vector;

import Client.Client;
import com.mysql.jdbc.Driver;
import com.sun.org.apache.bcel.internal.generic.FSUB;


public class Server {
    // JDBC数据库相关的常量
    public static final String url = "jdbc:mysql://localhost/java?characterEncoding=utf8&useSSL=false&allowPublicKeyRetrieval=true";
    public static final String user = "root";
    public static final String password = "zjxczyc123";

    // 服务器socket相关的常量
    public static final int port = 3772;
    public static final String addr = "localhost";
    ServerSocket serverSocket;
    Vector<ClientThread> clients;
    String message = "";


    public static void main(String[] args) throws SQLException {
        Server server = new Server();
        server.serverStart();
        server.serverListen();
        //System.out.println(server.checkLogin("zyc", "123"));
    }

    public Server() throws SQLException {
        // 注册数据库JDBC驱动
        DriverManager.registerDriver(new Driver());
    }

    public boolean checkLogin(String id, String pwd) throws SQLException {
        boolean res = true;
        //DriverManager.registerDriver(new Driver());
        Connection connection = DriverManager.getConnection(url, user, password);
        Statement statement = connection.createStatement();
        String select = "select * from userinfo where user_id=\'" + id + "\' and user_password=\'" + pwd + "\';";
        //System.out.println(select);
        ResultSet resultSet = statement.executeQuery(select);
        if (!resultSet.next()) {
            System.out.println("空的！");
            res = false;
        }
        resultSet.close();
        statement.close();
        connection.close();
        return res;
    }

    public void registerUser(String id, String pwd) throws SQLException {
        Connection connection = DriverManager.getConnection(url, user, password);
        Statement statement = connection.createStatement();
        String insert = "insert into userinfo values(\'" + id + "\',\'" + pwd + "\');";
        System.out.println(insert);
        int result = statement.executeUpdate(insert);
        statement.close();
        connection.close();
    }

    /**
     * 服务器启动，建立serverSocket和client表
     */
    private void serverStart() {
        try {
            InetAddress ip = InetAddress.getByName(addr);
            serverSocket = new ServerSocket(port, 0, ip);
            clients = new Vector<ClientThread>();
            System.out.println("服务器正常开启……等待客户端连接中");
        } catch (UnknownHostException e) {
            e.printStackTrace();
            System.out.println("host异常");
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("无法部署socket服务!");
        }
    }

    public void addClient(ClientThread c) {
        clients.add(c);
    }

    public void removeClient(ClientThread c) {
        clients.remove(c);
    }

    /**
     * 关闭服务器的socket
     */
    public void serverClose() {
        try {
            serverSocket.close();
            System.out.println("服务器关闭……");
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("服务器关闭时出现异常");
        }
    }

    /**
     * 监听方法，用于监听所有的客户端连接请求
     */
    public void serverListen() {
        try {
            while (true) {
                Thread.sleep(200);
                Socket socket = serverSocket.accept();
                ClientThread clientThread = new ClientThread(socket, this);
                Thread thread = new Thread(clientThread);
                thread.start();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void addNewMessage(String things) {
        this.message = this.message + things + '\n';
        System.out.println("当前消息记录：\n" + message);
    }

    /**
     * 向所有的客户端发送广播消息
     *
     * @param msg 要发送的消息
     */
    public void sendToAllClient(String msg) {
        Iterator<ClientThread> it = clients.iterator();
        while (it.hasNext()) {
            ClientThread temp = it.next();
            temp.sendInfo(msg);
        }
    }

    public void storeMessageToDB(String line, String user) throws SQLException {
        String msg = line.substring(5);
        int pos1 = msg.indexOf(' ');
        int pos2 = msg.indexOf('@');
        String info = msg.substring(pos1 + 1, pos2);
        String text = msg.substring(pos2 + 1);
        String date = info.substring(0, 10);
        String time = info.substring(11, 19);
        // 连接数据库进行存储
        Connection connection = DriverManager.getConnection(url, Server.user, password);
        Statement statement = connection.createStatement();
        String insert = "insert into msg values(\'" + user + "\',\'" + date + "\',\'"
                + time + "\',\'" + text + "\');";
        System.out.println(insert);
        statement.executeUpdate(insert);
        statement.close();
        connection.close();
    }

    public Vector<String> selectHistoryMessageFromDB() throws SQLException {
        Connection connection = DriverManager.getConnection(url, user, password);
        Statement statement = connection.createStatement();
        String select = "select * from msg;";
        ResultSet resultSet = statement.executeQuery(select);
        Vector<String> history = new Vector<String>();
        while (resultSet.next()) {
            String line1 = resultSet.getString("user_id") + " "
                    + resultSet.getString("send_date") + " "
                    + resultSet.getString("send_time");
            history.add(line1);
            String line2 = resultSet.getString("msg");
            history.add(line2);
        }
        return history;
    }
}