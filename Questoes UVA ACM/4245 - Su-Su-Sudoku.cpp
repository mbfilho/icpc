#include <iostream>
using namespace std;

int matriz[ 10 ][ 10 ];
bool preenchido;
bool pos[ 5 ][ 10 ];

class No{
	public:
		int i, j;
} falta[ 5 ];

void analisar(  ){
int x = 0, y = 0;
	for( int i=0; i<5; ++i ){
			x = falta[ i ].i;
			y = falta[ i ].j;
			
			for( int k = 1; k <= 9; ++k ){
				pos[ i ][ matriz[ x ][ k ] ] = false;
				pos[ i ][ matriz[ k ][ y ] ] = false;
			}
			
			int x1 = 3 * ( ( x - 1 ) / 3 ) + 1;
			int y1 = 3 * ( ( y - 1 ) / 3 ) + 1;
			for( int h = x1; h< x1 + 3; h++){
				for( int j=y1; j<y1+3; j++ ){
					pos[ i ][ matriz[ h ][ j ] ] = false;
				}
			}
		}

			
}


int main(){

	int vezes;
	char temp;
	int cont;
		
	cin >> vezes;
	int x, y;
	
	while( vezes-- ){
		cont = 0;
		preenchido = false;
		
		for( int j = 1; j <= 9; ++j ){
			for( int i = 1; i <= 9; ++i ){
				cin >> temp;
				temp -= '0';
				matriz[ i ][ j ] = temp;
				if( temp == 0 ){
					falta[ cont ].i = i;
					falta[ cont ].j = j;
					++cont;
				}
			}
			
			while( cin.peek() == '\n' )
				cin.ignore();
		}
		
		for( int i = 0; i < 5; ++i ){
			for( int j = 1; j <= 9; ++j )
				pos[ i ][ j ] = true;
		}
		
		bool ent = true;
		
		while( ent ){
			
			int cout = 0;
			ent = false;
			for( int j=0; j<5; j++ ){
				analisar();
				cout = 0;
				for( int i=1; i<=9; i++ ){
					if( pos[ j ][ i ] == true )
						cout++;
				}
				if( cout == 1 ){
					ent = true;
					for( int i=1; i<=9; i++ ){
						if( pos[ j ][ i ] == true ){
							matriz[ falta[ j ].i ][ falta[ j ].j ] = i;
							
						}
					}
				}				
			}				
		}
		
		ent = false;
		for( int j=1; j<=9; j++ ){
			for( int i=1; i<=9; i++ ){
				if( matriz[ i ][ j ] == 0 ){
					ent = true;
					break;
				}
			}
		}
		for( int j=0; j<5; j++ ){
			for( int i=1; i<=9; i++ ){
				if( pos[ j ][ i ] == true ){
					ent = true;
					break;
				}
			}
		}
		
		bool a[ 10 ], b[ 10 ], c[ 10 ];
		for( int o = 0; o < 10; ++o )
			a[ o ] = b[ o ] = c[ o ] = false;
			
		for( int i =1; i<=9; i++ ){
			for( int j=1; j<=9; j++ ){
			x = i;
			y = j;
								
			int s1 = 0;
			int s2 = 0;
			int s3 = 0;
			for( int k = 1; k <= 9; ++k ){
				s1 += matriz[ k ][ y ];
				s2 += matriz[ x ][ k ];
			}
			
			int x1 = 3 * ( ( x - 1 ) / 3 ) + 1;
			int y1 = 3 * ( ( y - 1 ) / 3 ) + 1;
			for( int h = x1; h< x1 + 3; h++){
				for( int j=y1; j<y1+3; j++ ){
					s3 += matriz[ h ][ j ];
				}
			}
			
			if( s1!=45 || s2!=45 || s3 !=45 ){
				ent = true;
				break;
			}
			}
		}
		
		if( ent == false ){
			for( int i = 1; i <= 9; ++i ){
				for( int j = 1; j <= 9; ++j )
					cout << matriz[ j ][ i ];
				cout << endl;
			}
			cout << endl;
		}else
			cout << "Could not complete this grid." << endl << endl;
	}
	
	
}


