import java.util.HashMap;

public class Request {
    private String kind;
    private String path;
    private String version;
    private String id;
    private String password;

    public Request(String[] line, String[] post) {
        kind = line[0];
        path = line[1];
        version = line[2];
        if (post != null) {
            int pos1 = post[0].indexOf('=');
            if (post[0].substring(0, pos1).equals("login")) {
                id = post[0].substring(pos1 + 1);
            }
            // System.out.println(post[1]);
            int pos2 = post[1].indexOf('=');
            // System.out.println(pos2);
            if (post[1].substring(0, pos2).equals("pass")) {
                password = post[1].substring(pos2 + 1);
                System.out.println(post[1].substring(pos2 + 1));
            }
        }
    }

    public String getRequest() {
        return kind;
    }

    public String getPath() {
        return path;
    }

    public String getId() {
        return id;
    }

    public String getPassword() {
        return password;
    }
}
