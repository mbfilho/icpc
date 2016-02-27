 #include <iostream>
 using std::cin;
 using std::cout;
 
 #include <cstdlib>
 
 int main(){
	int m, n, qtd;
	bool trocou;
	
	cin >> m >> n;
	
	while( m != 0 || n != 0 ){
		if( m < n ){
			int temp = n;
			n = m;
			m = temp;
			trocou = true;
		}else
			trocou = false;
		
		if( n == 0 )
			qtd = 0;
		else if( n == 1 )
			qtd = m;
		else if( n == 2 ){
			qtd = 4 * ( m / 4 );
			
			switch( m % 4 ){
				case 0:
					break;
				case 1:
					qtd += 2;
					break;
				case 2:
				case 3:
					qtd += 4;
					break;
			}
		}else{
			qtd = (m * n) / 2;
			if( (m * n) % 2 != 0 )
				++qtd;
		}
		
		if( trocou == false )
			cout << qtd << " knights may be placed on a " << m << " row "
				<< n << " column board." << std::endl;
		else
			cout << qtd << " knights may be placed on a " << n << " row "
				<< m << " column board." << std::endl;
		cin >> m >> n;		
	}
 }
