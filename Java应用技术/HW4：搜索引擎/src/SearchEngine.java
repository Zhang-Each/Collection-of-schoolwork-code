import java.io.*;
import java.util.LinkedList;
import java.util.Scanner;

import org.apache.lucene.analysis.Analyzer;

import org.apache.lucene.document.*;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;
import org.wltea.analyzer.lucene.IKAnalyzer;

public class SearchEngine {
    public static void main(String[] args) {
        SearchEngine w = new SearchEngine();
        String filePath = "./index";//创建索引的存储目录
        System.out.println("正在创建索引中，请稍等........");
        w.createIndex(filePath);//创建索引
        System.out.println("索引建立完成.");
        w.search(filePath);//搜索
    }

    public void createIndex(String filePath) {
        File f = new File(filePath);
        IndexWriter iwr=null;
        try {
            Directory dir = FSDirectory.open(f);
            Analyzer analyzer = new IKAnalyzer();
            IndexWriterConfig conf=new IndexWriterConfig(Version.LUCENE_4_10_0,analyzer);
            iwr = new IndexWriter(dir,conf); //建立IndexWriter。固定套路
            // 清空之间建立的所有索引
            try {
                iwr.deleteAll();
            } catch (Exception e) {
                e.printStackTrace();
            }
            // 遍历得到所有的文档，然后进行索引的创建
            LinkedList<Document> docs = getAllDocuments();
            for (Document doc: docs) {
                iwr.addDocument(doc);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            iwr.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public LinkedList<Document> getAllDocuments () {
        LinkedList<Document> result = new LinkedList<Document>();
        int id = 0;
        try {
            // 进入爬虫所得数据的根目录
            File root = new File("./data");
            try {
                // 获取每种书的目录并进行遍历
                File[] dictionary = root.listFiles();
                for (File topic: dictionary) {
                    // 获取每种书下面的所有单本书籍
                    File[] books = topic.listFiles();

                    // 遍历一本书所在的目录下面的所有信息
                    for (File book: books) {
                        // 创建一本书的索引Document
                        Document doc = new Document();
                        // 先写入一个编号
                        Field no = new IntField("No.", id, Field.Store.YES);
                        id += 1;
                        doc.add(no);
                        File[] information = book.listFiles();
                        // 获取书的每一项信息，并写入这个doc中
                        for (File info: information) {
                            int temp;
                            StringBuilder thingsInFile = new StringBuilder();
                            try {
                                Reader reader = new InputStreamReader(new FileInputStream(info));
                                while ((temp = reader.read()) != -1) {
                                    thingsInFile.append((char) temp);
                                }
                            } catch (Exception exception) {
                                exception.printStackTrace();
                            }
                            String thing = thingsInFile.toString().trim()
                                    .replace('/', ' ').replaceAll("\n\n", "\n");
                            // 将爬到书本信息作为document中的一项写入
                            Field bookInfo = new TextField(info.getName().replace(".txt", ""),
                                    thing, Field.Store.YES);
                            doc.add(bookInfo);
                        }
                        result.add(doc);
                    }
                }
            } catch (NullPointerException exception) {
                exception.printStackTrace();
            }

        } catch (Exception exception) {
            exception.printStackTrace();
        }
        return result;
    }

    /** 废弃的样例代码
    public Document getDocument() {
        //doc中内容由field构成，在检索过程中，Lucene会按照指定的Field依次搜索每个document的该项field是否符合要求。
        Document doc=new Document();
        Field f1=new TextField("name","XXX",Field.Store.YES);
        Field f2=new TextField("pic","梵高是一名画家",Field.Store.YES);
        Field f3=new TextField("grade","钱学森的学习成绩十分优秀",Field.Store.YES);
        Field f4=new TextField("address","浙江大学玉泉校区",Field.Store.YES);
        Field f5=new StringField("id","大学生",Field.Store.YES);
        doc.add(f1);
        doc.add(f2);
        doc.add(f3);
        doc.add(f4);
        doc.add(f5);

        return doc;

    }
     */

    public void search (String filePath) {
        File f = new File(filePath);
        Scanner input = new Scanner(System.in);
        try {
            while (true) {
                IndexSearcher searcher = new IndexSearcher(DirectoryReader.open(FSDirectory.open(f)));
                System.out.println("输入要查找的关键字，输入quit结束搜索引擎的运行！");
                String userInput, userChoice, needMore;
                //userInput = input.nextLine().trim().isEmpty();
                while ((userInput = input.nextLine().trim()).isEmpty());
                if (userInput.equals("quit")) {
                    break;
                } else {
                    Analyzer analyzer = new IKAnalyzer();
                    System.out.println("输入信息的检索范围：1.基本信息，2.目录，3.内容简介，4.摘要，5.作者简介");
                    String choice = input.nextLine();
                    if (choice.equals("1")) {
                        userChoice = "基本信息";
                    } else if (choice.equals("2")) {
                        userChoice = "目录";
                    } else if (choice.equals("3")) {
                        userChoice = "内容简介";
                    } else if (choice.equals("4")) {
                        userChoice = "摘要";
                    } else {
                        userChoice = "作者简介";
                    }
                    System.out.println("是否显示详细信息？Y/N");
                    needMore = input.next();
                    int resNum = 5;
                    QueryParser parser = new QueryParser(userChoice, analyzer);
                    Query query = parser.parse(userInput);
                    TopDocs hits = searcher.search(query,resNum);
                    //前面几行代码也是固定套路，使用时直接改field和关键词即可
                    System.out.println("查询结果：\n");
                    for (ScoreDoc res: hits.scoreDocs) {
                        Document d = searcher.doc(res.doc);
                        System.out.println("-------------------书籍基本信息---------------------");
                        System.out.println(d.get("基本信息"));
                        if (needMore.equals("Y") || needMore.equals("y")) {
                            System.out.println(d.get("目录"));
                            System.out.println(d.get("内容简介"));
                            System.out.println(d.get("摘要"));
                            System.out.println(d.get("作者简介"));
                        } else {
                            System.out.println("目录，内容摘要，作者简介等可以选择查看详细信息进行查看！");
                        }
                        System.out.println("---------------------------------------------------");
                    }
                }

            }

        } catch (IOException | ParseException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

}
