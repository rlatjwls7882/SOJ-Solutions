import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	static StringTokenizer st;
	public static void main(String[] args) throws Exception {
		int n = Integer.valueOf(br.readLine());
		st = new StringTokenizer(br.readLine());
		int[] a = new int[n];
		for(int i=0;i<n;i++) a[i] = Integer.valueOf(st.nextToken());

		Arrays.sort(a);
		for(int i=0;i<n;i++) bw.write(a[i]+" ");
		bw.close();
	}
}
