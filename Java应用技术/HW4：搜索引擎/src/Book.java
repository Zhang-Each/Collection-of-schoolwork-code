import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Book {
    private final String title;
    private final String author;
    private final String publisher;
    private final String publishTime;
    private final String bookAbstract;
    private final String contentIntroduction;
    private final String authorIntroduction;
    private final String contents;
    private final String topic;
    public Book(String title, String author, String publisher, String publishTime,
                String bookAbstract, String contentIntroduction,
                String authorIntroduction, String contents, String topic) {
        this.title = title;
        this.author = author;
        this.publisher = publisher;
        this.publishTime = publishTime;
        this.bookAbstract = bookAbstract;
        this.contentIntroduction = contentIntroduction;
        this.authorIntroduction = authorIntroduction;
        this.contents = contents;
        this.topic = topic;
    }

    public void showBookInformation() {
        System.out.println(title);
        System.out.println(author);
        System.out.println(publisher);
        System.out.println(publishTime);
        System.out.println(bookAbstract);
        System.out.println(contentIntroduction);
        System.out.println(authorIntroduction);
        System.out.println(contents);
    }

    /**
     * 将一个书本对象的各种信息按照一定的规则存储在对应的目录下面
     */
    public void writeInfoToFile() {
        String path = "./data/" + topic + "/" + title;
        File bookDictionary = new File(path);
        // 没有的时候创建目录
        if (!bookDictionary.exists()) {
            bookDictionary.mkdir();
        }
        path = path + "/";
        // 基本信息单独写一个文件
        String basic = path + "基本信息.txt";
        File basicInfo = new File(basic);
        try {
            if (!basicInfo.exists()) {
                basicInfo.createNewFile();
            }
            FileWriter fileWriter = new FileWriter(basic);
            fileWriter.write(title + '\n');
            fileWriter.write(author + '\n');
            fileWriter.write(publisher + '\n');
            fileWriter.write(publishTime + '\n');
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        // 摘要单独写一个文件
        String abstractOfBook = path + "摘要.txt";
        File abstractBook = new File(abstractOfBook);
        try {
            if (!abstractBook.exists()) {
                abstractBook.createNewFile();
            }
            FileWriter fileWriter = new FileWriter(abstractBook);
            fileWriter.write(this.bookAbstract);
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        // 作者简介单独写一个文件
        String authorOfBook = path + "作者简介.txt";
        File authorInfo = new File(authorOfBook);
        try {
            if (!authorInfo.exists()) {
                authorInfo.createNewFile();
            }
            FileWriter fileWriter = new FileWriter(authorInfo);
            fileWriter.write(this.authorIntroduction);
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        // 内容简介单独写一个文件
        String simpleIntroduce = path + "内容简介.txt";
        File introduce = new File(simpleIntroduce);
        try {
            if (!introduce.exists()) {
                introduce.createNewFile();
            }
            FileWriter fileWriter = new FileWriter(introduce);
            fileWriter.write(this.contentIntroduction);
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        // 目录单独写一个文件
        String contentOfBook = path + "目录.txt";
        File content = new File(contentOfBook);
        try {
            if (!content.exists()) {
                content.createNewFile();
            }
            FileWriter fileWriter = new FileWriter(content);
            fileWriter.write(this.contents);
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
