package game;

import java.util.Random;

public class matchGame {
    public int maxDigit, number, mode, count;
    public int[] operateNumber;
    public int result = 0;
    public char[] operator;
    public char[] expr; // 作为题目的表达式，先保存正确答案然后再根据一定的算法更改
    public char[] trueExpr; // 作为答案的表达式

    public matchGame(int maxDigit, int maxNum, int gameMode, int match) {
        this.maxDigit = maxDigit;
        this.number = maxNum;
        this.mode = gameMode;
        this.count = match;
        operateNumber = new int[number];
        operator = new char[number];
    }


    /**
     * 生成游戏的基本数据：表达式的内容，包含数字和操作符
     */
    public void generateGame() {
        result = 0;
        int bound = (new Double(Math.pow(10, maxDigit))).intValue();
        for(int i = 0; i < number; i++) {
            Random star = new Random();
            operateNumber[i] = star.nextInt(bound) % bound;

            // 生成运算符
            boolean flag = star.nextBoolean();
            if(flag) {
                operator[i] = '+';
            } else {
                operator[i] = '-';
            }

            // 计算正确的结果，存储在result里面
            if(i == 0) {
                result += operateNumber[i];
            } else {
                if(operator[i - 1] == '+') {
                    result += operateNumber[i];
                } else {
                    result -= operateNumber[i];
                }
            }
        }
        operator[number - 1] = '=';
        // 如果生成的结果不符合条件，就重新生成一次，直到获得了合适的初始表达式
        if(result < 0 || result > Math.pow(10, maxDigit)) {
            generateGame();
        }
    }

    /**
     * 将生成的表达式转化成带空位的标准形式
     * @param num 运算数
     * @param op 运算符
     * @param res 运算的结果
     * @return 返回一个标准形式的表达式，用于后面进一步随机生成题目
     */
    public char[] generateExpr(int[] num, char[] op, int res) {
        StringBuilder temp1 = new StringBuilder();
        StringBuilder temp2 = new StringBuilder();
        this.expr = new char[15];
        for(int i = 0; i < num.length; i++) {
            // 为完整的表达式加上空位
            if(num[i] <= 9)
                temp2.append("**");
            else if(num[i] <= 99)
                temp2.append("*");
            temp1.append(num[i]);
            temp1.append(op[i]);
            temp2.append(num[i]);
            temp2.append(op[i]);
        }
        temp1.append(res);
        // System.out.println(expression);
        //生成有多余位*的表达式
        if(res <= 9)
            temp2.append("**");
        else if(res <= 99)
            temp2.append("*");
        temp2.append(res);
        this.expr = temp2.toString().toCharArray();

        // 将整个表达式转化为一个char[]类型的数组
        return temp1.toString().toCharArray();
    }

    /**
     * 按照输入的要求随机生成一个新的表达式
     */
    public boolean gameShuffle() {
        System.out.println("改变之前的表达式为:");
        System.out.println(this.expr);
        int loop = 0;
        if(mode == 1) {
            // 直到生成合适的表达式之前一直尝试生成合适的表达式
            while(true) {
                loop++;
                if(matchAdd()) {
                    break;
                }
                if(loop >= 10) {
                    return false;
                }
            }
            while(true) {
                loop++;
                if(matchMinus()) {
                    break;
                }
                if(loop >= 10) {
                    return false;
                }
            }
        } else if(mode == 2) {
            while(true) {
                loop++;
                if(matchAdd()) {
                    break;
                }
                if(loop >= 10) {
                    return false;
                }
            }
        } else {
            while(true) {
                loop++;
                if(matchMinus()) {
                    break;
                }
                if(loop >= 10) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * 以下两个方法用于生成增加、减少若干根火柴之后的表达式，其中移动可以通过先添加后减少的方式生成
     * @return true表示成功生成，false表示生成失败，因为采用的是随机算法，因此有一定几率会失败，此时需要重新生成
     */
    public boolean matchAdd() {
        int target = this.count;
        int len = this.expr.length;
        int[] visited = new int[len];
        int loop = 0;
        // 每次随机选取一个下标来增加若干根火柴棒，增加的时候采用贪心的方法
        while(target != 0) {
            Random star = new Random();
            int index = star.nextInt(len);
            if(visited[index] >= 3 || this.expr[index] == '=') {
                continue;
            } else {
                int res = staticData.findMaxChange(this.expr, index, target);
                target -= res;
                visited[index]++;
                loop++;
            }
            // 设置一个循环次数的上限，超过这个上限就表示生成失败，需要重新生成一次
            if(loop >= 10) {
                return false;
            }
        }
        return true;
    }

    public boolean matchMinus() {
        int target = this.count;
        int len = this.expr.length;
        int[] visited = new int[len];
        int loop = 0;
        while(target != 0) {
            Random star = new Random();
            int index = star.nextInt(len);
            if(visited[index] >= 3 || this.expr[index] == '=') {
                continue;
            } else {
                int res = staticData.findMinChange(this.expr, index, target);
                target += res;
                visited[index]++;
                loop++;
            }
            // 设置一个循环次数的上限，超过这个上限就表示生成失败，需要重新生成一次
            if(loop >= 10) {
                return false;
            }
        }
        return true;
    }

    /**
     * 生成一个适当的火柴游戏，生成表达式的过程可能会产生一些不太好的结果导致使用随机算法生成题目的过程中出现死循环
     * 因此在gameShuffle中设置一个退出机制，如果循环了10次还没完成就返回，重新生成作为答案的表达式
     * 这种方式可以避免因为输入的数据比较小导致可以操作的数字比较少而产生的死循环，经实测比较有效
     */
    public void runGame() {
        System.out.println("---------------------游戏开始------------------------");
        boolean ok = false;
        // 成功生成题目的条件还要再考虑：当选择了移动的时候，不能使得题目和答案相同
        do {
            this.generateGame();
            this.trueExpr = this.generateExpr(operateNumber, operator, result);
            ok = this.gameShuffle();
        } while(!ok || checkGame.compare(this.expr, this.trueExpr));
        showGame.showMatchGame(expr);
        checkGame.checkResult(trueExpr, this.mode, this.count);
    }
}
