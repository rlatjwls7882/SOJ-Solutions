import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;

public class Main {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	static StringTokenizer st;
	public static void main(String[] args) throws Exception {
		int n = Integer.valueOf(br.readLine());
		int[] cnt = new int[100_001];
		st = new StringTokenizer(br.readLine());
		while(n-->0) {
			int a = Integer.valueOf(st.nextToken());
			cnt[a]++;
		}

		for(int i=1;i<=100_000;i++) {
			while(cnt[i]-->0) {
				bw.write(i+" ");
			}
		}
		bw.close();
	}
}
