#include <iostream>
using std::cin;

#include <cstdio>

const int x = 0, y = 1;

int main(){
	double pontos[ 3 ][ 2 ];
	double temp[ 2 ];
	int ex1, meio, ex2;
	double x4, y4;
	
//	freopen( "in.txt", "r", stdin );
//	freopen( "out.txt", "w", stdout );
	
	while(cin >> pontos[ 0 ][ x ] >> pontos[ 0 ][ y ]){
		//Carrega o primeiro vértice
		;
		
		//Carrega o segundo vértice
		cin >> pontos[ 1 ][ x ] >> pontos[ 1 ][ y ];
		
		//Carrega o terceiro vértice
		cin >> temp[ x ] >> temp [ y ]; 
		
		if( temp[ x ] == pontos[ 0 ][ x ] && temp[ y ] == pontos[ 0 ][ y ] ){
			meio = 0;
			ex1 = 1;
			ex2 = 2; 
			
			//Carrega o quarto vértice
			cin >> pontos[ 2 ][ x ] >> pontos[ 2 ][ y ];
		}else if( temp[ x ] == pontos[ 1 ][ x ] && pontos[ 1 ][ y ] == temp[ y ] ){
			meio = 1;
			ex1 = 0;
			ex2 = 2;
			
			//Carrega o quarto vértice
			cin >> pontos[ 2 ][ x ] >> pontos[ 2 ][ y ];
		}else{
			pontos[ 2 ][ x ] = temp[ x ];
			pontos[ 2 ][ y ] = temp[ y ];
			
			//Carrega o quarto vértice
			cin >> temp[ x ] >> temp [ y ]; 
			if( temp[ x ] == pontos[ 0 ][ x ] && temp[ y ] == pontos[ 0 ][ y ] ){
				meio = 0;
				ex1 = 1;
				ex2 = 2;
			}else{
				meio = 1;
				ex1 = 0;
				ex2 = 2;
			}		
		}
		
	//	printf( "Ponto1: X: %lf Y: %lf\n", pontos[ 0 ][ x ], pontos[ 0 ][ y ] );
	//	printf( "Ponto2: X: %lf Y: %lf\n", pontos[ 1 ][ x ], pontos[ 1 ][ y ] ); 
	//	printf( "Ponto3: X: %lf Y: %lf\n", pontos[ 2 ][ x ], pontos[ 2 ][ y ] ); 	
	
		x4 = pontos[ ex2 ][ x ] - pontos[ meio ][ x ] + pontos[ ex1 ][ x ];
		y4 = pontos[ ex2 ][ y ] - pontos[ meio ][ y ] + pontos[ ex1 ][ y ];
		
		printf( "%.3lf %.3lf\n", x4, y4 );
	}
	
	fclose( stdout );
}
