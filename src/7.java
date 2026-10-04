import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        double[] x = new double[3];
        for(int i=0;i<3;i++) x[i] = sc.nextDouble();
        Arrays.sort(x);
        double a=x[0], b=x[1], c=x[2];
        if(a*a+b*b<=c*c) {
            System.out.printf("%.7f", a*b/2);
        } else {
            double s = (a+b+c)/2;
            System.out.printf("%.7f", Math.sqrt(s*(s-a)*(s-b)*(s-c)));
        }
    }
}