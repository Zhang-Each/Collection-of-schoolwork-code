public class UnmodifiableVector {
    private final double[] elements;
    private final int length;

    public UnmodifiableVector(double[] nums) {
        length = nums.length;
        elements = new double[length];
        System.arraycopy(nums, 0, elements, 0, length);
    }

    public UnmodifiableVector(UnmodifiableVector that) {
        length = that.getLength();
        elements = new double[length];
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
    public void showUnmodifiableVector() {
        for (int i = 0; i < length; i++) {
            System.out.print(elementAt(i) + " ");
        }
        System.out.print('\n');
    }

    public UnmodifiableVector addUnmodifiableVector(UnmodifiableVector that) {
        double[] res;
        if (this.length == that.getLength()) {
            res = new double[this.length];
            for (int i = 0; i < this.length; i++) {
                res[i] = this.elementAt(i) + that.elementAt(i);
            }
            return new UnmodifiableVector(res);
        } else {
            System.out.println("向量的维数不同，不能进行加法运算！");
        }
        return null;
    }

    public UnmodifiableVector subUnmodifiableVector(UnmodifiableVector that) {
        double[] res;
        if (this.length == that.getLength()) {
            res = new double[this.length];
            for (int i = 0; i < this.length; i++) {
                res[i] = this.elementAt(i) - that.elementAt(i);
            }
            return new UnmodifiableVector(res);
        } else {
            System.out.println("向量的维数不同，不能进行加法运算！");
        }
        return null;
    }

    public UnmodifiableVector dotProduct(double val) {
        double[] res = new double[this.length];
        for (int i = 0; i < this.length; i++) {
            res[i] = val * this.elementAt(i);
        }
        return new UnmodifiableVector(res);
    }

    public double innerProduct(UnmodifiableVector that) {
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
