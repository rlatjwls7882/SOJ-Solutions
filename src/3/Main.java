import java.util.Arrays;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int[] a = new int[n];
		for(int i=0;i<n;i++) a[i] = sc.nextInt();
		
		Arrays.sort(a);
		for(int i=0;i<n;i++) System.out.print(a[i]+" ");
	}
}
