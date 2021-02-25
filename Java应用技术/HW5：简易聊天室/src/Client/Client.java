package Client;

import org.omg.PortableInterceptor.SYSTEM_EXCEPTION;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.time.LocalDateTime;

public class Client {
    private final LoginIn login;
    private MainPage mainPage;
    // 当前用户的账号和密码
    private String id, password;

    public static final int port = 3772;
    public static final String server = "localhost";
    public Socket socket = null;
    public BufferedReader receive = null;
    public PrintWriter send = null;

    public Thread receiveThread;
    public boolean isRunning = false;
    public int isLogin = 0;

    public String history = "";

    public static void main(String[] args) {
        Client client = new Client();
        client.connectServer();
        client.startListen();
    }

    public Client() {
        login = new LoginIn();
        this.setLoginListener();
        isRunning = true;
    }

    private void setLoginListener() {
        this.login.button.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                id = login.idField.getText();
                password = String.valueOf(login.passwordField.getPassword());
                checkLogin();
            }
        });
    }

    private void setMainPageListener() {
        // 监听send按钮，点击send的时候发送消息
        this.mainPage.send.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                // 点击send的时候
                String message = mainPage.input.getText().replaceAll("\n", "");
                System.out.println(message);
                sendAMessage(message);
                mainPage.input.setText(null);
            }
        });

        // 监听clear按钮，点击clear按钮的时候清除输入框中的内容
        this.mainPage.clear.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                mainPage.input.setText(null);
            }
        });

        this.mainPage.history.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                sendToServer("!history!");
                try {
                    // 等待获取历史记录
                    Thread.sleep(2000);
                } catch (InterruptedException interruptedException) {
                    interruptedException.printStackTrace();
                }
                JOptionPane.showMessageDialog(
                        mainPage.show,
                        "成功获取聊天历史记录！",
                        "通知",
                        JOptionPane.INFORMATION_MESSAGE
                );
                mainPage.show.setText("聊天记录:\n");
                mainPage.show.append(history + "----------------------History---------------------\n");
            }
        });

        this.mainPage.frame.addWindowListener(new WindowListener() {
            @Override
            public void windowOpened(WindowEvent e) {
                isRunning = true;
                System.out.println("登录！");
            }

            @Override
            public void windowClosing(WindowEvent e) {
                isRunning = false;
                System.out.println("退出登录！");
                sendToServer("!logout!");
                try {
                    receive.close();
                    send.close();
                    socket.close();
                    System.out.println("closed!");
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }
                mainPage.frame.dispose();
            }

            @Override
            public void windowClosed(WindowEvent e) {

            }

            @Override
            public void windowIconified(WindowEvent e) {

            }

            @Override
            public void windowDeiconified(WindowEvent e) {

            }

            @Override
            public void windowActivated(WindowEvent e) {

            }

            @Override
            public void windowDeactivated(WindowEvent e) {

            }
        });
    }

    public void sendAMessage(String msg) {
        String info = this.id + " " + LocalDateTime.now().toString();
        // 将消息发送到服务器
        this.sendToServer("!msg!" + info + "@" + msg);
    }


    /**
     * 登陆验证函数，如果登陆成功就关闭登陆界面进入正式的聊天界面
     */
    public void checkLogin() {
        // 登录的时候给服务器发送账号和密码，确认之后再显示登录信息
        this.sendToServer("!login!" + this.id + " " + this.password);
        while (true) {
            // 登陆成功之前处于休眠状态
            System.out.print("");
            if (isLogin != 0) {
                break;
            }
        }

        if (isLogin == 1) {
            JOptionPane.showMessageDialog(
                    login.loginFrame,
                    "登陆成功",
                    "通知",
                    JOptionPane.INFORMATION_MESSAGE
            );
            login.setWindowClose();
            //System.out.println("用户登陆成功");
            // 登录成功之后。先注册用户提交用户的id
            mainPage = new MainPage(id);
            this.setMainPageListener();
            this.registerUser();
        } else if (isLogin == -1) {
            JOptionPane.showMessageDialog(
                    login.loginFrame,
                    "登陆失败，账号或密码错误!",
                    "提示",
                    JOptionPane.ERROR_MESSAGE
            );
            System.out.println("用户登陆失败");
        }
    }

    public void connectServer() {
        try {
            socket = new Socket(server, port);
            receive = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            send = new PrintWriter(socket.getOutputStream(), true);
            //System.out.println(send);
            //System.out.println(receive);

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendToServer(String info) {
        System.out.println("要发送的信息：" + info);
        try {
            send.println(info);
            System.out.println("发送成功");
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }

    public void receiveFromServer() {
        String line;
        try {
            if (!socket.isClosed()) {
                line = receive.readLine();
            } else {
                System.out.println("Socket已经关闭了！");
                return ;
            }
            if (!line.isEmpty()) {
                System.out.println("客户端收到了服务器的消息：" + line);
                // 处理登录请求
                if (line.startsWith("!login!")) {
                    // login的1，2两种状态分别表示登陆成功，账号或者密码错误
                    String res = line.substring(7);
                    if (res.equals("1")) {
                        isLogin = 1;
                        System.out.println("登陆成功！");
                    } else if (res.equals("2")) {
                        isLogin = -1;
                    }
                } else if (line.startsWith("!msg!")) {
                    String msg = line.substring(5);
                    int pos = msg.indexOf('@');
                    String info = msg.substring(0, pos);
                    String text = msg.substring(pos + 1);
                    this.mainPage.show.append(info + '\n');
                    this.mainPage.show.append(text + "\n");
                } else if (line.startsWith("!list!")) {
                    String newUser = line.substring(6);
                    //System.out.println(newUser);
                    System.out.println("添加新用户：" + newUser);
                    this.mainPage.list.append(newUser + '\n');
                } else if (line.startsWith("!history!")) {
                    this.history = this.history + line.substring(9) + '\n';
                }
            }
        } catch (IOException | NullPointerException e) {
            System.out.println("捕捉到IO异常");
        }
    }

    public void registerUser() {
        // 发送用户的信息
        String info = "!register!" + this.id;
        this.sendToServer(info);
    }

    /**
     * 开启socket子线程
     */
    public void startListen() {
        receiveThread = new InfoListener();
        receiveThread.start();
    }

    /**
     * 定义一个socket子线程用于接收信息
     */
    class InfoListener extends Thread {
        @Override
        public void run() {
            System.out.println("客户端监听线程启动！");
            while (isRunning) {
                if (socket.isClosed()) {
                    isRunning = false;
                    break;
                }
                receiveFromServer();
                try {
                    sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } catch (NullPointerException e) {
                    e.printStackTrace();
                }
            }
        }
    }

}
