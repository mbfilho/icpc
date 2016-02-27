		
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef int Coordenadas[2];
const int X = 0;
const int Y = 1;

int main(){
	// lembrar de tirar quando for submeter
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	
	Coordenadas rainha;
	Coordenadas destino;
	bool alcance;
	
	while( true ){
		alcance = false;
		scanf( "%d%d%d%d", &rainha[ X ], &rainha[ Y ], &destino[ X ], &destino[ Y ] );
        
        if( rainha[ X ] == 0 && rainha[ Y ] == 0 && destino[ X ] == 0 && destino[ Y ] == 0 )
            break;
            
		if( destino[ X ] == rainha[ X ] && destino[ Y ] == rainha[ Y ] )
			printf( "%d\n", 0 );
		else{
			alcance = alcance || ( destino[ X ] == rainha[ X ] );
			alcance = alcance || ( destino[ Y ] == rainha[ Y ] );
			int temp1 = destino[ X ] - rainha[ X ];
			temp1 = temp1 > 0? temp1: -temp1;
            int temp2 = destino[ Y ] - rainha[ Y ];
            temp2 = temp2>0? temp2: -temp2;
            
            alcance = alcance || (temp1 == temp2);   
            
			if( alcance )
				printf( "%d\n", 1 );
			else
				printf( "%d\n", 2 );
		}
	}


	return 0;
}
