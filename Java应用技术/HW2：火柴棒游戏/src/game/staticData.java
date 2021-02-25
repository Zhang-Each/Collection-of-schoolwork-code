package game;

public class staticData {
    public static int[][] difference = {
            {0, -4, 0, 0, 0, 0, 0, -3, 1, 0, 0, 0, 0}, // 0 - 9
            {4, 0, 0, 3, 2, 0, 0, 1, 5, 4, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
            {0, -3, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0},
            {0, -2, 0, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 2, 1 , 0, 0, 0},
            {0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0},
            {3, -1, 0, 2, 0, 0, 0, 0, 4, 3, 0, 0, 0},
            {-1, -5, -2, -2, -3, -2, -1, -4, 0,-1, 0, 0, 0},
            {0, -4, 0, -1, -2, -1, 0, -3, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0}, // +
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // -
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} // =
    };

    public static int findMaxChange(char[] x, int n, int remain) {
        int index = getIndex(x, n);
        // 对于数字的增加火柴棒的操作
        if(index <= 9) {
            int maxi = 0, maxChange = 0;
            for(int i = 0; i < 13; i++) {
                if(difference[index][i] > maxChange && difference[index][i] <= remain) {
                    maxChange = difference[index][i];
                    maxi = i;
                }
            }
            x[n] = (char)('0' + maxi);
            return maxChange;
        }
        // 我们规定加号不会变化，方便生成游戏
        else if(index == 10) {
            return 0;
        } else if (index == 11) {
            x[n] = '+';
            return 1;
        } else {
            //碰到的是空白位置*，此时只要添加就可以
            //采取的策略是尽可能多的消耗remain，即剩余的火柴棒数量，如果剩下超过了7根，就只能变成8然后用掉7根
            if(remain <= 1) {
                return 0;
            } else if(remain == 2) {
                x[n] = '1';
            } else if(remain == 3) {
                x[n] = '7';
            } else if(remain == 4) {
                x[n] = '4';
            } else if(remain == 5) {
                x[n] = '2';
            } else if(remain == 6) {
                x[n] = '6';
            } else {
                x[n] = '8';
                return 7;
            }
            return remain;
        }
    }

    public static int findMinChange(char[] x, int n, int remain) {
        int index = getIndex(x, n);
        // 减号和*不能减少
        if(index >= 11) {
            return 0;
        } else if(index == 10) {
            x[n] = '-';
            return -1;
        } else if(index >= 0) {
            int mini = 0, minChange = 0;
            for(int i = 0; i < 13; i++) {
                if(difference[index][i] < minChange && difference[index][i] + remain >= 0) {
                    minChange = difference[index][i];
                    mini = i;
                }
            }
            if(minChange < 0) {
                x[n] = (char) ('0' + mini);
                return minChange;
            }
            else
                return 0;
        } else {
            return 0;
        }
    }

    public static int getIndex(char[] x, int n) {
        if(x[n] >= '0' && x[n] <= '9') {
            return x[n] - '0';
        } else if(x[n] == '+') {
            return 10;
        } else if(x[n] == '-') {
            return 11;
        } else {
            return 12;
        }
    }

    /**
     * 用来计算一格需要几根火柴棒
     * @param x 表示火柴游戏中的一个单位字符
     * @return x需要的火柴棒数目
     */
    public static int numberOfMatch(char x) {
        if(x == '-') {
            return 1;
        } else if(x == '1' || x == '+' || x == '=') {
            return 2;
        } else if(x == '7') {
            return 3;
        } else if(x == '4') {
            return 4;
        } else if(x == '8') {
            return 7;
        } else if(x == '6') {
            return 6;
        } else
            return 5;
    }

    /**
     * 计算一个表达式需要的火柴棒根数
     * @param expr 火柴游戏的表达式
     * @return 该表达式需要的火柴总数目
     */
    public static int matchOfExpr(char[] expr) {
        int result = 0;
        for (char c : expr) {
            result += numberOfMatch(c);
        }
        return result;
    }
}
