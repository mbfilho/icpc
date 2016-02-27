 #include <iostream>
 using namespace std;
 
int main(){
	int bancos[ 21 ];
	int debitos, devedor, credor, din, fortuna, total;
	int cont_bancos, cont_dividas;
	
		freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	
	
	cin >> cont_bancos >> cont_dividas;
	
	while( cont_bancos | cont_dividas ){
		fortuna = 0;
		for( int i = 1; i <= cont_bancos; ++i ){
			cin >> bancos[ i ];
			fortuna += bancos[ i ];
		}
		
		for( int i = 0; i < cont_dividas; ++i ){
			cin >> devedor >> credor >> din;
			
			bancos[ devedor ] -= din;
			bancos[ credor ] += din;
		}
		

		bool pode = true;
		
		total = 0;
		for( int i = 1; i <= cont_bancos; ++i ){
			if( bancos[ i ] < 0 ){
				pode = false;
				break;
			}else
				total += bancos[ i ];
		}
		
		if( pode && total <= fortuna )
			cout << "S" << endl;
		else
			cout << "N" << endl;
		
		cin >> cont_bancos >> cont_dividas;
	}
	
}
