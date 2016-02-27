import java.io.*;
import java.util.*;
import java.math.*;


public class Main{
	static BigInteger x1, x2, y1, y2;
	
	public static BigInteger euclides(BigInteger a, BigInteger b){
		x2 = BigInteger.ONE; y2 = BigInteger.ZERO;
		x1 = BigInteger.ZERO; y1 = BigInteger.ONE;
		BigInteger mod, quo;
		
		while(b.compareTo(BigInteger.ZERO) != 0){
			mod = a.remainder(b);
			quo = a.divide(b);
			
			BigInteger tmp = x2.subtract(x1.multiply(quo));
			x2 = x1;
			x1 = tmp;
			
			tmp = y2.subtract(y1.multiply(quo));
			y2 = y1;
			y1 = tmp;
			
			a = b;
			b = mod;
		}
		
		return a;
	}
	
	public static BigInteger chao(BigInteger num, BigInteger den){
		if(num.compareTo(BigInteger.ZERO) >= 0){
			return num.divide(den);
		}else{
			BigInteger sinal = new BigInteger("-1");
			num = num.multiply(sinal).add(den.subtract(BigInteger.ONE));
			return num.divide(den).multiply(sinal);
		}
	}
	
	public static void main(String args[]){
		Scanner sc = new Scanner(System.in);
		BigInteger a, b, c;
		
		while(true){
			a = sc.nextBigInteger();
			b = sc.nextBigInteger();
			c = sc.nextBigInteger();
			if(a.compareTo(BigInteger.ZERO) == 0 && b.compareTo(BigInteger.ZERO) == 0 && c.compareTo(BigInteger.ZERO) == 0) break;
			
			BigInteger gcd = euclides(a,b);
			if(c.remainder(gcd).compareTo(BigInteger.ZERO) != 0) System.out.println("Unquibable!");
			else{
				BigInteger ext = c.divide(gcd);
				x2 = x2.multiply(ext); y2 = y2.multiply(ext);
				
				BigInteger soma = null, x = null, y = null, nx = null, ny = null, nsoma = null;
				BigInteger k;
				
				if(a.compareTo(BigInteger.ZERO) != 0){
					k = chao(y2.multiply(gcd), a);
					nx = x2.add(k.multiply(b).divide(gcd)); ny = y2.subtract(k.multiply(a).divide(gcd)); nsoma = nx.add(ny);
					if(nx.compareTo(BigInteger.ZERO) >= 0 && ny.compareTo(BigInteger.ZERO) >= 0){
						x = nx;
						y = ny;
						soma = nsoma;
					}
				}
				
				if(b.compareTo(BigInteger.ZERO) != 0){
					k = chao(x2.multiply(gcd), b);
					nx = x2.subtract(k.multiply(b).divide(gcd)); ny = y2.add(a.multiply(k).divide(gcd)); nsoma = nx.add(ny);
				
					if(nx.compareTo(BigInteger.ZERO) >= 0 && ny.compareTo(BigInteger.ZERO) >= 0){
						if(soma == null || nsoma.compareTo(soma) <= 0){
							x = nx; y = ny;
						}
					}
				}
				
				if(x == null) System.out.println("Unquibable!");
				else{
					String foom = x.compareTo(BigInteger.ONE) == 0 ? "foom" : "fooms";
					String foob = y.compareTo(BigInteger.ONE) == 0 ? "foob" : "foobs";
					System.out.println(x + " " + foom + " and " + y + " " + foob + " for a twob!");
				}
				
			}
		}
	}
}

