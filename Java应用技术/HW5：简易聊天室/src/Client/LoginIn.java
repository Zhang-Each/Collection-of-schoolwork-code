package Client;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;


public class LoginIn {
    public JFrame loginFrame;
    public JPanel panel;
    public JLabel idLabel, pwdLabel;
    public JTextField idField;
    public JPasswordField passwordField;
    public JButton button;
    public boolean tryLogin = false;
    public String id, password;

    public LoginIn() {
        this.initLoginIn();
        //this.setListeners();
    }

    private void initLoginIn() {
        loginFrame = new JFrame("登陆界面");
        loginFrame.setSize(400, 250);
        loginFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        panel = new JPanel();
        loginFrame.add(panel);
        panel.setLayout(null);
        // 两个标签
        idLabel = new JLabel("账号");
        pwdLabel = new JLabel("密码");
        idLabel.setBounds(80, 20, 80, 35);
        panel.add(idLabel);
        pwdLabel.setBounds(80, 80, 80, 35);
        panel.add(pwdLabel);
        // 两个输入框
        idField = new JTextField(20);
        idField.setBounds(165, 20, 120, 35);
        panel.add(idField);
        passwordField = new JPasswordField(20);
        passwordField.setBounds(165, 80, 120, 35);
        panel.add(passwordField);
        // 登录按钮
        button = new JButton("登录");
        button.setBounds(160, 125, 80, 30);
        panel.add(button);

        loginFrame.setVisible(true);
    }

    private boolean checkLogin(String id, String password) {
        System.out.println(id);
        System.out.println(password);
        this.tryLogin = true;
        return true;
    }

    public void setWindowClose() {
        this.loginFrame.setVisible(false);
    }

    public static void main(String[] args) {
        LoginIn login = new LoginIn();
    }
}
