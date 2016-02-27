import java.math.BigInteger;
import java.util.Scanner;


public class Main {
	BigInteger nove = new BigInteger( "9" );
	BigInteger cem = new BigInteger( "100" );
	BigInteger vinte = new BigInteger( "20" );
	
	String baixar;
	BigInteger resto, c, p, y, x;
	String num;
	
	void setX(){
		x = nove;
		
		while( ( y = vinte.multiply( p ).add(x).multiply(x) ).compareTo(c) > 0 )
			x = x.subtract( BigInteger.ONE );
	}
	
	BigInteger raiz(){
		resto = p = BigInteger.ZERO;
		int prt = 0, tam = num.length();
	
		if( tam % 2 == 1 )
			prt = -1;
		
		
		while( prt <= tam - 2 ){
			if( prt < 0 )
				baixar = num.charAt( prt + 1 ) + "";
			else
				baixar = num.charAt( prt ) + "" + num.charAt( prt + 1 );
			prt += 2;
			
			c = resto.multiply( cem ).add( new BigInteger( baixar ) );
			setX();
			p = p.multiply( BigInteger.TEN ).add( x );
			resto = c.subtract( y );
		}
		return p;	
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner( System.in );
		Main m = new Main();
		int casos = sc.nextInt();
		
		for( int i = 0; i < casos; ++i ){
			m.num = sc.next();
			System.out.println( m.raiz() );
			
			if( i != casos - 1 )
				System.out.println();
		}
	}
}


