public class Vector {
    private double[] elements;
    private int length;

    /**
     * 构造函数：用double数组进行构造
     * @param nums 初始化的数组
     */
    public Vector(double[] nums) {
        length = nums.length;
        elements = new double[length];
        System.arraycopy(nums, 0, elements, 0, length);
    }

    /**
     * 拷贝构造函数
     * @param m 用来拷贝的向量
     */
    public Vector(Vector m) {
        length = m.getLength();
        elements = new double[length];
        for (int i = 0; i < length; i++) {
            elements[i] = m.elementAt(i);
        }
    }

    public int getLength() {
        return length;
    }

    public double elementAt(int k) {
        try {
            return elements[k];
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("下标溢出，请重试！");
        }
        return elements[k];
    }

    /**
     * 打印整个vector
     */
    public void showVector() {
        for (int i = 0; i < length; i++) {
            System.out.print(elementAt(i) + " ");
        }
        System.out.print('\n');
    }

    /**
     * 改变vector中第K位的值，并且有一场检查
     * @param k 需要改变的下标
     * @param val 改变后的值
     */
    public void changeVector(int k, double val) {
        try {
            elements[k] = val;
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("下标溢出，请重试！");
        }
    }

    public void addVector(Vector that) {
        if (this.length == that.getLength()) {
            for (int i = 0; i < this.length; i++) {
                elements[i] += that.elementAt(i);
            }
        } else {
            System.out.println("向量的维数不同，不能进行加法运算！");
        }
    }

    // 以下定义了向量的若干种基本运算，包含加减法，内积和数量积
    public void subVector(Vector that) {
        if (this.length == that.getLength()) {
            for (int i = 0; i < this.length; i++) {
                elements[i] -= that.elementAt(i);
            }
        } else {
            System.out.println("向量的维数不同，不能进行减法运算！");
        }
    }

    public void dotProduct(double dot) {
        for (int i = 0; i < this.length; i++) {
            elements[i] *= dot;
        }
    }

    public double innerProduct(Vector that) {
        double res = 0;
        if (this.length == that.getLength()) {
            for (int i = 0; i < this.length; i++) {
                res += this.elementAt(i) * that.elementAt(i);
            }
        } else {
            System.out.println("向量的维数不同，不能进行数量积运算");
        }
        return res;
    }
}
