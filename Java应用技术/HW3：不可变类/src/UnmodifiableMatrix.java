public class UnmodifiableMatrix {
    private final double[][] elements;
    private final int row;
    private final int col;

    public UnmodifiableMatrix(double[][] nums) {
        row = nums.length;
        col = nums[0].length;
        elements = new double[row][col];
        for (int i = 0; i < row; i++) {
            System.arraycopy(nums[i], 0, elements[i], 0, col);
        }
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

    public boolean equalSize(UnmodifiableMatrix that) {
        return this.row == that.getRow() && this.col == that.getCol();
    }

    public UnmodifiableMatrix addMatrix(UnmodifiableMatrix that) {
        if (this.equalSize(that)) {
            double[][] res = new double[this.row][this.col];
            for (int i = 0; i < this.row; i++) {
                for (int j = 0; j < this.col; j++) {
                    res[i][j] = this.elementAt(i, j) + that.elementAt(i, j);
                }
            }
            return new UnmodifiableMatrix(res);
        } else {
            System.out.println("矩阵的大小不同，不能进行加法运算");
        }
        return null;
    }

    public UnmodifiableMatrix subMatrix(UnmodifiableMatrix that) {
        if (this.equalSize(that)) {
            double[][] res = new double[this.row][this.col];
            for (int i = 0; i < this.row; i++) {
                for (int j = 0; j < this.col; j++) {
                    res[i][j] = this.elementAt(i, j) - that.elementAt(i, j);
                }
            }
            return new UnmodifiableMatrix(res);
        } else {
            System.out.println("矩阵的大小不同，不能进行减法运算");
        }
        return null;
    }

    public UnmodifiableMatrix mulMatrix(UnmodifiableMatrix that) {
        double[][] res;
        if (canMultiply(that)) {
            res = new double[this.row][that.col];
            for (int i = 0; i < this.row; i++) {
                for (int j = 0; j < this.col; j++) {
                    for (int k = 0; k < that.col; k++) {
                        res[i][k] += this.elementAt(i, j) * that.elementAt(j, k);
                    }
                }
            }

            return new UnmodifiableMatrix(res);
        } else {
            return null;
        }
    }

    public boolean canMultiply(UnmodifiableMatrix that) {
        return this.col == that.getRow();
    }
}
