import java.util.Scanner;
import game.matchGame;

public class JavaHW2 {

    public static void main(String[] args) {
        int maxDigit, maxNum, gameMode, matchNum;
        // 直到输入合法的数据之前持续读入一系列数据
        do {
            System.out.println("请输入数字的最大位数(1,2,3):");
            Scanner input = new Scanner(System.in);
            maxDigit = input.nextInt();
            System.out.println("请输入提示数(2，3)");
            maxNum = input.nextInt();
            System.out.println("请输入游戏类型和可操作的火柴根数:\n1.移动\n2.删除\n3.添加");
            gameMode = input.nextInt();
            matchNum = input.nextInt();
        } while (!isLegalGame(maxDigit, maxNum, gameMode, matchNum));
        matchGame game = new matchGame(maxDigit, maxNum, gameMode, matchNum);
        game.runGame();
        System.out.println("恭喜您，游戏结束，欢迎下次再来！");
    }

    /**
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String temp = input.nextLine();
        boolean ok = checkGame.isExprRight(temp.toCharArray());
        System.out.println(ok);
    }
     */

    /**
     * 检测游戏的初始化数据是否合法
     * @param digit 应该是1，2，3中的一个数
     * @param num 应该是2或者3
     * @param mode 应该是1，2，3中的一个数，代表游戏类型
     * @param match 火柴棒根数，原则上不超过3根
     * @return true表示游戏的初始化数据合法，可以开始游戏，false表示数据有误需要再次输入
     */
    public static boolean isLegalGame(int digit, int num, int mode, int match) {
        if(!(digit == 1 || digit == 2 || digit == 3)) {
            System.out.println("数字位数输入错误!");
            return false;
        } else if(!(num == 2 || num == 3)) {
            System.out.println("提示数输入错误!");
            return false;
        } else if(!(mode == 1 || mode == 2 || mode == 3)) {
            System.out.println("游戏模式输入错误!");
            return false;
        } else if(match <= 0 || match >=4) {
            System.out.println("火柴棒数量输入不合理!");
            return false;
        }
        return true;
    }
}
