import java.math.BigDecimal;
import java.util.Scanner;


class Main {

	public static void main( String args[] ){
		Scanner sc = new Scanner( System.in );
		BigDecimal soma, temp;
		int casos = sc.nextInt();
		String aux;
		
		for( int i = 0; i < casos; ++i ){
			soma = new BigDecimal( 0 );
			
			while( true ){
				aux = sc.next();
				if( aux.equals( "0" ) )
					break;
				
				temp = new BigDecimal( aux );
				soma = soma.add( temp );
			}
			
			if( soma.compareTo( BigDecimal.ZERO ) == 0 )
				System.out.println( "0" );
			else{
				String resul = soma.toPlainString();
				int j;
				for( j = 0; j < resul.length(); ++j ){
					if( resul.charAt( j ) == '.' )
						break;
				}
				
				if( j == resul.length() )
					System.out.println( resul );
				else{
					int cont = -1, ponto = j;
					for( j = j + 1; j < resul.length(); ++j ){
						if( resul.charAt( j ) != '0' )
							cont = j;
					}
					
					if( cont == -1 ){
						for( j = 0; j < ponto; ++j )
							System.out.print( resul.charAt( j ) );
						
						System.out.println();
					}else{
						for( j = 0 ; j <= cont; ++j )
							System.out.print( resul.charAt( j ) );
						System.out.println();
					}
				}
			}
		}
	}
}
