package game;

public class showGame {

    // 用于打印一系列的数字和运算符号
    static String [] num0 = new String[] {
            " * * * ",
            " *   * ",
            " *   * ",
            " *   * ",
            " * * * "
    };
    static String [] num1 = new String[] {
            "     * ",
            "     * ",
            "     * ",
            "     * ",
            "     * "
    };
    static String [] num2 = new String[] {
            " * * * ",
            "     * ",
            " * * * ",
            " *     ",
            " * * * "
    };
    static String [] num3 = new String[] {
            " * * * ",
            "     * ",
            " * * * ",
            "     * ",
            " * * * "
    };
    static String [] num4 = new String[] {
            " *   * ",
            " *   * ",
            " * * * ",
            "     * ",
            "     * "
    };
    static String [] num5 = new String[] {
            " * * * ",
            " *     ",
            " * * * ",
            "     * ",
            " * * * "
    };
    static String [] num6 = new String[] {
            " * * * ",
            " *     ",
            " * * * ",
            " *   * ",
            " * * * "
    };
    static String [] num7 = new String[] {
            " * * * ",
            "     * ",
            "     * ",
            "     * ",
            "     * "
    };

    static String [] num8 = new String[] {
            " * * * ",
            " *   * ",
            " * * * ",
            " *   * ",
            " * * * "
    };

    static String [] num9 = new String[] {
            " * * * ",
            " *   * ",
            " * * * ",
            "     * ",
            " * * * "
    };

    static String [] plus = new String[] {
            "       ",
            "   *   ",
            " * * * ",
            "   *   ",
            "       "
    };

    static String [] minus = new String[] {
            "       ",
            "       ",
            " * * * ",
            "       ",
            "       "
    };

    static String [] equal = new String[] {
            "       ",
            " * * * ",
            "       ",
            " * * * ",
            "       "
    };

    static String[][] list = new String[][] {
            num0, num1, num2, num3, num4, num5, num6, num7, num8, num9, plus, minus, equal
    };

    public static int getIndex(char x) {
        if(x >= '0' && x <= '9') {
            return x - '0';
        } else if(x == '+') {
            return 10;
        } else if(x == '-') {
            return 11;
        } else if(x == '=') {
            return 12;
        }
        else return -1;
    }

    public static void showMatchGame(char[] game) {
        System.out.println("请挑战下面的火柴棒游戏:");
        System.out.println(game);
        for(int i = 0; i < 5; i++) {
            for (char c : game) {
                int index = getIndex(c);
                if(index != -1) {
                    System.out.print(list[getIndex(c)][i]);
                }
            }
            System.out.print('\n');
        }
        System.out.println("\n");
    }
}
