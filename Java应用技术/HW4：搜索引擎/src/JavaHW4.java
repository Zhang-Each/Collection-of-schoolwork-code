import java.io.IOException;

public class JavaHW4 {
    public static void main(String[] args) throws IOException {
        SearchEngine w = new SearchEngine();
        String filePath = "./index";//创建索引的存储目录
        System.out.println("正在创建索引中，请稍等........");
        w.createIndex(filePath);//创建索引
        System.out.println("索引建立完成.");
        w.search(filePath);//搜索
    }
}

