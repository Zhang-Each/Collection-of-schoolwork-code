public class Matrix {
    private double[][] elements;
    private int row;
    private int col;

    /**
     * 构造函数
     * @param nums 用于初始化的二维数组
     */
    public Matrix(double[][] nums) {
        row = nums.length;
        col = nums[0].length;
        elements = new double[row][col];
        for (int i = 0; i < row; i++) {
            System.arraycopy(nums[i], 0, elements[i], 0, col);
        }
    }

    public Matrix(Matrix that) {
        row = that.getRow();
        col = that.getCol();
        elements = new double[row][col];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                this.elements[i][j] = that.elementAt(i, j);
            }
        }
    }

    public Matrix() {
        row = col = 0;
    }

    public void showMatrix() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                System.out.print(this.elements[i][j] + " ");
            }
            System.out.print('\n');
        }
    }

    public int getRow() { return row; }
    public int getCol() { return col; }

    public double elementAt(int i, int j) {
        try {
            return elements[i][j];
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("矩阵下表溢出，请重试！");
        }
        return elements[i][j];
    }

    public void changMatrix(int i, int j, double val) {
        try {
            elements[i][j] = val;
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("矩阵下表溢出，请重试！");
        }
    }

    public boolean equalSize(Matrix that) {
        return this.row == that.getRow() && this.col == that.getCol();
    }

    public void addMatrix(Matrix that) {
        if (this.equalSize(that)) {
            for (int i = 0; i < this.row; i++) {
                for (int j = 0; j < this.col; j++) {
                    this.elements[i][j] += that.elementAt(i, j);
                }
            }
        } else {
            System.out.println("矩阵的大小不同，不能进行加法运算");
        }
    }

    public void subMatrix(Matrix that) {
        if (this.equalSize(that)) {
            for (int i = 0; i < this.row; i++) {
                for (int j = 0; j < this.col; j++) {
                    this.elements[i][j] -= that.elementAt(i, j);
                }
            }
        } else {
            System.out.println("矩阵的大小不同，不能进行减法运算");
        }
    }

    /**
     * 矩阵的乘法运算，需要返回一个矩阵
     * @param that 另一个矩阵
     * @return 作为乘法运算结果的矩阵
     */
    public Matrix mulMatrix(Matrix that) {
        if (canMultiply(that)) {
            double[][] res = new double[this.row][that.col];
            for (int i = 0; i < this.row; i++) {
                for (int j = 0; j < this.col; j++) {
                    for (int k = 0; k < that.col; k++) {
                        res[i][k] += this.elements[i][j] * that.elementAt(j, k);
                    }
                }
            }
            return new Matrix(res);
        } else {
            return new Matrix();
        }
    }

    public boolean canMultiply(Matrix that) {
        return this.col == that.getRow();
    }
}