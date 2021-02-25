package Client;

import javax.swing.*;
import java.awt.*;

public class MainPage {
    public JFrame frame;
    public JPanel panel;
    public JTextArea show, list;
    public JEditorPane input;
    public JButton send, clear, history;
    public JLabel label;

    public MainPage(String user) {
        frame = new JFrame("聊在浙大 ChattingInZJU");
        frame.setSize(1200, 840);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        panel = new JPanel();
        panel.setLayout(null);
        frame.add(panel);
        // 聊天室的标题
        String title = "欢迎使用聊在浙大! " + user;
        label = new JLabel(title);
        label.setFont(new Font("微软雅黑", Font.BOLD, 20));
        label.setBounds(20, 10, 1000, 30);
        panel.add(label);
        // 聊天记录框的设定
        show = new JTextArea();
        show.setEditable(false);
        show.setBounds(20, 50, 840, 560);
        show.setBackground(Color.WHITE);
        show.setFont(new Font("宋体", Font.BOLD, 20));
        show.setText("聊天记录：\n");
        panel.add(show);
        // 允许窗口滚动条
        JScrollPane scrollPane = new JScrollPane(show);
        scrollPane.setBounds(20, 50, 840, 560);
        panel.add(scrollPane);
        // 输入框的设定
        input = new JEditorPane();
        input.setBounds(20, 630, 840, 150);
        input.setBackground(Color.WHITE);
        panel.add(input);
        // 用户列表的设定
        list = new JTextArea();
        list.setEditable(false);
        list.setBounds(900, 50, 270, 560);
        list.setBackground(Color.GRAY);
        list.setFont(new Font("楷体", Font.BOLD, 20));
        list.setText("聊天室用户列表：\n");
        panel.add(list);

        // 按钮的设定
        send = new JButton("发送消息");
        send.setBounds(900, 630, 270, 35);
        panel.add(send);

        clear = new JButton("清除");
        clear.setBounds(900, 675, 270, 35);
        panel.add(clear);

        history = new JButton("查看历史记录");
        history.setBounds(900, 720, 270, 35);
        panel.add(history);

        frame.setVisible(true);
    }
}
