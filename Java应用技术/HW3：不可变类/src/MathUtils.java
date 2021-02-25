public class MathUtils {
    public static UnmodifiableVector getUnmodifiableVector(Vector v) {
        double[] nums = new double[v.getLength()];
        for (int i = 0; i < v.getLength(); i++) {
            nums[i] = v.elementAt(i);
        }
        return new UnmodifiableVector(nums);
    }

    public static UnmodifiableMatrix getUnmodifiableMatrix(Matrix m) {
        double[][] nums = new double[m.getRow()][m.getCol()];
        for (int i = 0; i < m.getRow(); i++) {
            for (int j = 0; j < m.getCol(); j++) {
                nums[i][j] = m.elementAt(i, j);
            }
        }
        return new UnmodifiableMatrix(nums);
    }
}
