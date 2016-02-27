import java.util.*;
import java.math.*;

class Main{
	static String pat, text;
	static int tamp, tamt;
	static BigInteger[][] pd = new BigInteger[ 10100 ][ 110 ];
	
	static BigInteger cont( int a, int b ){
		if( pd[ a ][ b ] != null ) return pd[ a ][ b ];
		
		if( b == tamt ) return pd[ a ][ b ] = BigInteger.ONE;
		
		if( a >= tamp ) return pd[ a ][ b ] = BigInteger.ZERO;
		
		BigInteger soma = BigInteger.ZERO;
		if( pat.charAt( a ) == text.charAt( b ) )
			soma = soma.add( cont( a + 1, b + 1 ) );
		
		soma = soma.add( cont( a + 1, b ) );
		
		return pd[ a ][ b ] = soma;		
	}
	
	public static void main( String args[] ) {
		Scanner sc = new Scanner( System.in );
		int casos = sc.nextInt();
		
		for( int p = 0; p < casos; ++p ){
			pat = sc.next();
			text = sc.next();
			tamp = pat.length();
			tamt = text.length();
			for( int i = 0; i <= tamp; ++i ){
				for( int j = 0; j <= tamt; ++j )
					pd[ i ][ j ] = null;
			}
			
			System.out.println( cont( 0, 0  ) );
		}
	}
}

