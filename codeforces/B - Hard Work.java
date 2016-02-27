import java.util.*;

class Main{
	
	public static void main( String args[] ){
		Scanner sc = new Scanner( System.in );
		String a[] = new String[ 3 ], conc[] = new String[ 6 ];
		
		a[ 0 ] = sc.next().replace( "_", "" ).replace( ";", "" ).replace( "-", "" ).toLowerCase();
		a[ 1 ] = sc.next().replace( "_", "" ).replace( ";", "" ).replace( "-", "" ).toLowerCase();
		a[ 2 ] = sc.next().replace( "_", "" ).replace( ";", "" ).replace( "-", "" ).toLowerCase();
		
		conc[ 0 ] = a[ 0 ] + a[ 1 ] + a[ 2 ];
		conc[ 1 ] = a[ 0 ] + a[ 2 ] + a[ 1 ];
		conc[ 2 ] = a[ 1 ] + a[ 0 ] + a[ 2 ];
		conc[ 3 ] = a[ 1 ] + a[ 2 ] + a[ 0 ];
		conc[ 4 ] = a[ 2 ] + a[ 0 ] + a[ 1 ];
		conc[ 5 ] = a[ 2 ] + a[ 1 ] + a[ 0 ];
		
		int qtd = sc.nextInt();
		
		for( int i = 0; i < qtd; ++i ){
			String r = sc.next().replace( "_", "" ).replace( ";", "" ).replace( "-", "" ).toLowerCase();
			
			boolean sim = false;
			for( int j = 0; j < 6; ++j ){
				if( r.equals( conc[ j ] ) ){
					sim = true;
					break;
				}
			}
			
			if( sim )
				System.out.println( "ACC" );
			else
				System.out.println( "WA" );
		}
	} 
}