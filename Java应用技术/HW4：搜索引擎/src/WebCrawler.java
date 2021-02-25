import com.gargoylesoftware.htmlunit.BrowserVersion;
import com.gargoylesoftware.htmlunit.NicelyResynchronizingAjaxController;
import com.gargoylesoftware.htmlunit.WebClient;
import com.gargoylesoftware.htmlunit.html.HtmlPage;
import org.apache.commons.logging.LogFactory;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;
import java.io.*;
import java.util.logging.Level;

public class WebCrawler {
    public static void main(String[] args) throws IOException {
        WebCrawler webCrawler = new WebCrawler();
        String[] searchTarget = webCrawler.getSearchTarget();
        for (String topic: searchTarget) {
            String path = "./data/" + topic;
            File directory = new File(path);
            if (!directory.exists()) {
                try {
                    directory.mkdir();
                } catch (Exception exception) {
                    System.out.println(exception);
                }
            }
            String url = webCrawler.generateURL(topic);
            System.out.println("开始爬取新的图书主题：" + topic);
            Document document = webCrawler.getSingleWebsite(url);
            Elements hrefs = document.getElementsByClass("pic");
            // 获得所有的子页面连接之后爬取子页面中的所有信息，并记录在文件中
            for (int i = 0; i < hrefs.size(); i++) {
                String singleHref = hrefs.get(i).attributes().get("href");
                webCrawler.getSingleBookInfo(singleHref, topic);
            }
        }

        //Document document = webCrawler.getSingleWebsite(
                         //"http://search.dangdang.com/?key=java&act=input");
        //Elements hrefs = document.getElementsByClass("pic");

        //for (int i = 0; i < hrefs.size(); i++) {
            //String singleHref = hrefs.get(i).attributes().get("href");
            //webCrawler.getSingleBookInfo(singleHref);
        //}
        //webCrawler.getSingleBookInfo("http://product.dangdang.com/28495225.html", "Java");

    }

    public Document getSingleWebsite(String url) throws IOException {
        LogFactory.getFactory().setAttribute("org.apache.commons.logging.Log","org.apache.commons.logging.impl.NoOpLog");
        java.util.logging.Logger.getLogger("com.gargoylesoftware").setLevel(Level.OFF);
        java.util.logging.Logger.getLogger("org.apache.http.client").setLevel(Level.OFF);

        WebClient webClient = new WebClient(BrowserVersion.CHROME);
        webClient.getOptions().setUseInsecureSSL(true);
        webClient.setAjaxController(new NicelyResynchronizingAjaxController());
        webClient.getOptions().setJavaScriptEnabled(true); //启用JS解释器，默认为true
        webClient.getOptions().setCssEnabled(false); //禁用css支持
        webClient.getOptions().setThrowExceptionOnScriptError(false); //js运行错误时，是否抛出异常
        HtmlPage page = webClient.getPage(url);
        webClient.waitForBackgroundJavaScript(30000);
        return Jsoup.parse(page.asXml());
    }

    public void getSingleBookInfo(String url, String topic) throws IOException {
        Document document = getSingleWebsite(url);
        try {
            Elements elements = document.getElementsByClass("t1");
            //System.out.println(document);
            //System.out.println(elements);
            // 图书的四种种最基本的信息
            String title = document.title().replaceAll("/", "")
                    .replaceAll(" ", "").replaceAll("<", "")
                    .replaceAll(">", "").replace('\\', ' ')
                    .replaceAll(" ", "");
            String author = elements.get(0).child(0).html();
            String publisher = elements.get(1).child(0).html();
            String publishTime = elements.get(2).html().replace("&nbsp;", "");


            Elements dynamicElements = document.getElementsByClass("descrip");

            // System.out.println(dynamicElements);
            if (dynamicElements.size() >= 4) {
                // 分别获得书本的摘要、内容介绍、作者介绍和具体目录
                String bookAbstract = getAbstract(dynamicElements.get(1))
                        .replaceAll("<.+?>", "").trim();
                String contentIntroduction = dynamicElements.get(2).text()
                        .replaceAll("<.+?>", "").trim();
                String authorIntroduction = dynamicElements.get(3).text()
                        .replaceAll("<.+?>", "").trim();
                String contents = dynamicElements.get(4).text()
                        .replaceAll("<.+?>", "\n")
                        .replaceAll("\n\n", "\n");
                // 创建一本书的对象
                Book thisBook = new Book(title, author, publisher,
                        publishTime, bookAbstract, contentIntroduction,
                        authorIntroduction, contents, topic);
                // thisBook.showBookInformation();
                System.out.println("成功爬取了 " + title + " 并开始将信息写入文件!!");
                thisBook.writeInfoToFile();
            }
        } catch (Exception exception) {
            System.out.println("在爬取主题" + topic + "\n网址" + url + "时失败，本页面爬取无效!");
        }
    }

    public String getAbstract(Element element) {
        StringBuilder res = new StringBuilder();
        for (int i = 1; i < element.childrenSize(); i ++) {
            if (!element.child(i).html().isEmpty()) {
                res.append(element.child(i).html().replaceAll("&lt;br", "").
                        replaceAll("/&gt;", "").replaceAll("p&gt;", "").
                        replaceAll("&nbsp;", "").replaceAll("<.+?>", ""));
                res.append('\n');
            }
        }
        return res.toString();
    }

    public String generateURL(String topic) {
        return "http://search.dangdang.com/?key=" + topic + "&act=input";
    }

    public String[] getSearchTarget() {
        // 一些暂定的搜索目标
        String[] searchTarget = {"Java", "Python", "C++", "操作系统", "数据结构", "数据库",
        "计算机组成", "计算机网络", "软件工程", "机器学习"};
        //String[] newTarget = {"操作系统", "数据结构", "数据库",
                //"计算机组成", "计算机网络", "软件工程", "机器学习"};
        return searchTarget;
    }
}
