import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;

public class Main {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	static StringTokenizer st;
	static String next() throws Exception {
		while(st == null || !st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
		return st.nextToken();
	}
	public static void main(String[] args) throws Exception {
		int n = Integer.valueOf(br.readLine());
		
		long sum=0;
		while(n-->0) sum += Long.valueOf(next());
		bw.write(Long.toString(Math.abs(sum)));
		bw.close();
	}
}
