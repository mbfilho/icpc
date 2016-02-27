#include <cstring>
#include <cstdio>
typedef long long ll;

ll pd[21];
/*
import java.util.*;
import java.math.*;



public class Main{
	public static BigInteger expo(BigInteger a, long xp, BigInteger mod){
		BigInteger resp = BigInteger.ONE;
		
		while(xp!=0){
			if( (xp&1) != 0) resp = resp.multiply(a).remainder(mod);
			a = a.multiply(a).remainder(mod);
			xp >>= 1;
		}
		
		return resp;
	}

	public static void main(String args[]){
		BigInteger pot[] = new BigInteger[21], dois = new BigInteger("2");
		pot[0] = BigInteger.ONE;
		for( int i = 1; i < 21; ++i ) pot[i] = pot[i-1].multiply(BigInteger.TEN);
		
		int i = 10;
		while( i != 21 ){
			long it = 315589;
			BigInteger step = expo(dois,1562500, pot[i]);
			int passo = 1562500;
			BigInteger tmp = expo(dois,it,pot[i]);
			while(true){
			
				String s = tmp.toString();
				boolean pode = s.length() == i;
				for( int k = 0; pode && k < s.length(); ++k ){
					if(s.charAt(k) != '1' && s.charAt(k) != '2') pode = false;
				}
			
				if(pode){
					System.out.println( "pd[" + i + "] = " + it + ";" );
					break;
				}
			
				tmp = tmp.multiply(step).remainder(pot[i]);
				it += passo;
			}
			++i;
		}
		
	}
}


*/


int main(){
	pd[1] = 1;
	pd[2] = 9;
	pd[3] = 89;
	pd[4] = 89;
	pd[5] = 589;
	pd[6] = 3089;
	pd[7] = 3089;
	pd[8] = 3089;
	pd[9] = 315589;
	pd[10] = 315589;
	pd[11] = 8128089;
	pd[12] = 164378089;
	pd[13] = 945628089;
	pd[14] = 1922190589LL;
	pd[15] = 11687815589LL;
	pd[16] = 109344065589LL;
	pd[17] = 231414378089LL;
	pd[18] = 1452117503089LL;
	pd[19] = 4503875315589LL;
	pd[20] = 65539031565589LL;
	
	int casos;
	scanf( "%d", &casos );
	for( int ca = 1; ca <= casos; ++ca ){
		int tmp;
		scanf( "%d", &tmp );
		printf( "%d %d %lld\n", ca, tmp, pd[tmp] );
	}
}

