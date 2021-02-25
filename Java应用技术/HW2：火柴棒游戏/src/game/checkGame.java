package game;
import java.util.Scanner;

public class checkGame {
    public static void checkResult(char[] origin, int mode, int match) {
        // System.out.println(origin);
        while(true) {
            if(gameLoop(origin, mode, match))
                break;
        }
    }

    public static boolean gameLoop(char[] origin, int mode, int match) {
        System.out.println("请输入你的答案:");
        Scanner input = new Scanner(System.in);
        String inputResult = input.nextLine();
        if(inputResult.isEmpty()) {
            System.out.println("正确答案是: ");
            showTrueAnswer(origin);
            return true;
        }
        char[] inputExpression = new char[origin.length];
        int j = 0;
        for(int i = 0; i < inputResult.length(); i++) {
            if(j >= origin.length) {
                System.out.println("答案错误！请重试！");
                return false;
            }
            if(inputResult.charAt(i) == ' ') {
                continue;
            } else if(inputResult.charAt(i) >= '0' && inputResult.charAt(i) <= '9') {
                inputExpression[j++] = inputResult.charAt(i);
            }
            else if(inputResult.charAt(i) == '+' || inputResult.charAt(i) == '-' || inputResult.charAt(i) == '=') {
                inputExpression[j++] = inputResult.charAt(i);
            }
            else {
                System.out.println("答案错误！请重试！");
                return false;
            }
        }
        System.out.println(inputExpression);
        int resultNum = staticData.matchOfExpr(inputExpression);
        if(mode == 2) {
            resultNum -= match;
        } else if(mode == 3) {
            resultNum += match;
        }
        if(compare(origin, inputExpression) ||
                (resultNum == staticData.matchOfExpr(origin) && isExprRight(inputExpression))) {
            System.out.println("答案正确！恭喜您完成了游戏！");
            return true;
        } else {
            System.out.println("答案错误！请重试！");
            return false;
        }
    }

    public static boolean compare(char[] origin, char[] now) {
        for(int i = 0; i < origin.length; i++) {
            if(origin[i] != now[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * 检测表达式中的结果是否正确
     * @param expr 待检测的表达式
     * @return 正确返回true，否则false
     */
        public static boolean isExprRight(char[] expr) {
        int[] num =  new int[4]; //算上结果最多也就四个数字
        char[] op = new char[3]; //算上等号最多也就三个运算符
        int i = 0, j = 0, temp = 0;
        for(char k : expr) {
            if(k == '+' || k == '-' || k == '=') {
                op[j++] = k;
                num[i++] = temp;
                temp = 0;
            } else if(k >= '0'&& k <= '9') {
                temp = temp * 10 + (k - '0');
            }
        }
        num[i++] = temp;
        //System.out.println(i);
        //System.out.println(j);
        if(i != j + 1) {
            // 不合法的表达式
            return false;
        }
        int res = num[0];
        for(int k = 0; k < op.length; k++) {
            if(op[k] == '+') {
                res += num[k + 1];
            } else if(op[k] == '-') {
                res -= num[k + 1];
            } else if(op[k] == '=') {
                return res == num[k + 1];
            }
        }
        return false;
    }

    public static void showTrueAnswer(char[] res) {
        for(char i : res) {
            if(i != '*') {
                System.out.print(i);
            }
        }
        System.out.print("\n");
    }
}
