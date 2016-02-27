import java.util.*;
import java.math.*;

public class Main{
	public static BigInteger pd[][] = new BigInteger[2][1001];
	public static BigInteger nn;
	public static BigInteger expo[] = new BigInteger[1001];
	
	
	public static BigInteger pega(int i, int k){
		if(pd[k%2][i] == null) System.out.println(">>> " + i+ ":" + k);
		return pd[k%2][i].multiply(expo[k-i]);
	}
	
	public static BigInteger gcd(BigInteger a, BigInteger b){
		if(b.compareTo(BigInteger.ZERO) == 0) return a;
		return gcd(b, a.remainder(b));
	}
	
	public static void main(String args[]){
		pd[0][0] = BigInteger.ONE;
						
		int n, m, k;
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		m = sc.nextInt();
		k = sc.nextInt();
		
		for(int i = 1; i <= k; ++i){
			pd[i%2][0] = pd[i%2][i] = BigInteger.ONE;
			for(int j = 1; j < i; ++j){
				pd[i%2][j] = pd[(i+1)%2][j].add(pd[(i+1)%2][j-1]);
			}
		}

		expo[0] = BigInteger.ONE;
		BigInteger tmp = new BigInteger((n-1) + "");
		for(int i = 1; i <= k; ++i)
			expo[i] = expo[i-1].multiply(tmp);
		
		BigInteger soma = BigInteger.ZERO;
		
		for(int i = 0; i <= k; i += 2){
			//	System.out.println(i);
			//System.out.println(i + ":" + pega(i,k));
			soma = soma.add(pega(i,k));
		}
		//System.out.println("M " + soma);
		soma = soma.multiply(new BigInteger("" + m));
		BigInteger soma2 = BigInteger.ZERO;
		for(int i = 1; i <= k; i += 2){
			soma2 = soma2.add(pega(i,k));
		}
		soma2 = soma2.multiply(new BigInteger("" + (n-m)));
		soma = soma.add(soma2);
		
		BigInteger den = BigInteger.ONE;
		nn = new BigInteger("" + n);
		for(int i = 1; i <= k; ++i)
			den = den.multiply(nn);
		BigInteger mdc = gcd(den, soma);
		soma = soma.divide(mdc);
		den = den.divide(mdc);
		System.out.println(soma +"/" + den);
		
	}
	
}
