public class JavaHW3 {
    public static void main(String[] args) {
        //testVector();
        //testMatrix();
        //testUnmodifiedVector();
        //testUnmodifiedMatrix();
        //testMathUtils();
    }

    public static void testVector() {
        System.out.println("------------------Vector----------------------");
        double[] nums = {1, 2, 3};
        Vector a = new Vector(nums);
        a.showVector();
        Vector b = new Vector(a);
        b.showVector();
        a.dotProduct(2);
        a.showVector();
        double res = a.innerProduct(b);
        System.out.println("a * b = " + res);
        Vector c = new Vector(new double[] {5, 10, 3});
        c.addVector(a);
        c.showVector();
        c.subVector(b);
        c.showVector();
        c.changeVector(1, 100);
        c.showVector();
    }

    public static void testMatrix() {
        System.out.println("------------------Matrix----------------------");
        Matrix a = new Matrix(new double[][] {{1, 2, 3}, {4, 5, 6}});
        Matrix b = new Matrix(a);
        a.showMatrix();
        b.showMatrix();
        a.addMatrix(b);
        a.showMatrix();
        Matrix c = new Matrix(new double[][] {{1,2}, {3, 4}, {5, 6}});
        Matrix d = a.mulMatrix(c);
        d.showMatrix();
        d.changMatrix(1, 1, 100);
    }

    public static void testUnmodifiedMatrix() {
        System.out.println("------------------Unmodified Matrix----------------------");
        UnmodifiableMatrix a = new UnmodifiableMatrix(new double[][] {{1, 2, 3}, {4, 5, 6}});
        UnmodifiableMatrix b = new UnmodifiableMatrix(new double[][] {{1,2}, {3, 4}, {5, 6}});
        UnmodifiableMatrix c = a.addMatrix(a);
        UnmodifiableMatrix d = c.subMatrix(a);
        UnmodifiableMatrix e = a.mulMatrix(b);
        a.showMatrix();
        b.showMatrix();
        c.showMatrix();
        d.showMatrix();
        e.showMatrix();
    }

    public static void testUnmodifiedVector() {
        System.out.println("------------------Unmodified Vector----------------------");
        double[] nums = {1, 2, 3};
        UnmodifiableVector a = new UnmodifiableVector(nums);
        UnmodifiableVector b = a.dotProduct(2);
        UnmodifiableVector c = a.addUnmodifiableVector(b);
        UnmodifiableVector d = a.subUnmodifiableVector(b);
        double res = b.innerProduct(c);
        a.showUnmodifiableVector();
        b.showUnmodifiableVector();
        c.showUnmodifiableVector();
        d.showUnmodifiableVector();
        System.out.println(res);
    }

    public static void testMathUtils() {
        double[] nums = {1, 2, 3};
        Vector a = new Vector(nums);
        UnmodifiableVector unmodified_a = MathUtils.getUnmodifiableVector(a);
        a.showVector();
        unmodified_a.showUnmodifiableVector();

        Matrix b = new Matrix(new double[][] {{1, 2, 3}, {4, 5, 6}});
        UnmodifiableMatrix unmodified_b = MathUtils.getUnmodifiableMatrix(b);
        b.showMatrix();
        unmodified_b.showMatrix();
    }
}
