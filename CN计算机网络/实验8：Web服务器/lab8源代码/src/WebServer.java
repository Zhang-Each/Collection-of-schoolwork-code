import java.io.*;
import java.net.Socket;
import java.util.Arrays;

public class WebServer extends Thread {

    private InputStream input;
    private OutputStream output;
    private String path;
    private static final int BUFFER_SIZE = 4096;
    private static final String account = "3180103772";
    private static final String password = "3772";
    private Request request;

    public WebServer(Socket socket, String path) throws IOException {
        this.input = socket.getInputStream();
        this.output = socket.getOutputStream();
        this.path = path;
    }

    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName() + " start!");
        try {
            this.request = HTTPParser();
            if (request.getRequest().equals("GET")) {
                System.out.println("A GET Request!!!");
                // 处理get请求
                responseGetRequest();
            } else if (request.getRequest().equals("POST")) {
                System.out.println("A POST Request!!!");
                // 处理post请求
                responsePostRequest();
            } else {
                System.out.println("Unknown Request!!");
                // 本简易web服务器不提供其他的HTTP请求的服务
            }
            System.out.println(Thread.currentThread().getName() + " End!");
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            stop();
        }
    }

    public Request HTTPParser() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));
        String line = reader.readLine();
        String[] parseLine = line.split(" ");
        if (parseLine[0].equals("GET")) {
            return new Request(parseLine, null);
        } else if (parseLine[0].equals("POST")) {
            int len = 0;
            while ((line = reader.readLine()) != null) {
                // 到了请求头的末尾
                if (line.equals("")) {
                    break;
                } else if (line.contains("Content-Length")) {
                    // 解析长度
                    int pos = line.indexOf("Content-Length") + 16;
                    len = Integer.parseInt(line.substring(pos));
                }
            }
            if (len >= 1) {
                char[] buffer = new char[len];
                int flag = reader.read(buffer, 0, len);
                System.out.println(buffer);

                String[] info = new String(buffer).split("&");
                return new Request(parseLine, info);
            }
        }
        return null;
    }

    public void responseGetRequest() throws IOException {
        // HTML文件的地址
        String filePath = path + request.getPath();
        System.out.println(filePath);
        File file = new File(filePath);
        if (!filePath.equals("/") && file.exists()) {
            InputStream fileInput = new FileInputStream(file);
            byte[] buffer = new byte[BUFFER_SIZE];
            int len;
            // 在output中写入HTTP的response请求头部
            output.write("HTTP/1.1 200 OK\r\n".getBytes());
            // 在output中写入HTTP的content-type
            String postfix = getPostFixName(request.getPath());
            if (postfix.equals("jpg")) {
                output.write("Content-Type:image/jpg\r\n".getBytes());
            } else if (postfix.equals("html") || postfix.equals("htm")) {
                output.write("Content-Type:text/html;charset=UTF-8\r\n".getBytes());
            } else {
                // 传输的是纯文本时候的情况
                output.write("Content-Type:text/plain;charset=UTF-8\r\n".getBytes());
            }
            output.write("\r\n".getBytes());
            // 写入文件中的数据
            while ((len = fileInput.read(buffer)) != -1) {
                output.write(buffer, 0, len);
            }
        } else {
            String tip = "<h1>404 NOT FOUND---FROM ZYC SERVER</h1>";
            String error = "HTTP/1.1 404 NOT FOUND\r\n" + "Content-Type:text/html;charset=UTF-8\n" +
                    "Content-Length:" + tip.length() +"\r\n" + "\r\n" + tip;
            output.write(error.getBytes());
        }
        output.flush();
        output.close();
    }

    public String getPostFixName(String file) {
        int pos = file.indexOf('.');
        return file.substring(pos + 1);
    }

    public void responsePostRequest() throws IOException {
        System.out.println(request.getId());
        System.out.println(request.getPassword());
        System.out.println(request.getPath());
        if (request.getPath().equals("/html/dopost") && !request.getId().isEmpty()
                && !request.getPassword().isEmpty()) {
            String message;
            if (request.getId().equals(account) && request.getPassword().equals(password)) {
                message = "<h1>Login Success!</h1>";
            } else {
                message = "<h1>Login Fail!</h1>";
            }
            String result = "HTTP/1.1 200 OK\r\n" + "Content-Type:text/html;charset=UTF-8\n" + "Content-Length:"
                    + message.length() + "\r\n" + "\r\n" + message;
            output.write(result.getBytes());
        } else {
            String tip = "<h1>404 NOT FOUND---FROM ZYC SERVER</h1>";
            String error = "HTTP/1.1 404 NOT FOUND\r\n" + "Content-Type:text/html;charset=UTF-8\n" +
                    "Content-Length:" + tip.length() +"\r\n" + "\r\n" + tip;
            output.write(error.getBytes());
        }
        output.flush();
        output.close();
    }
}
