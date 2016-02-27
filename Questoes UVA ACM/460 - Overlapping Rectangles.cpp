#include <iostream>
using std::cin;
using std::cout;

class Quadrado{
	public:
		int x1, y1, x2, y2;
};

int main(){
	Quadrado q1, q2;
	int casos;
	int x1, y1, x2, y2;
	
	cin >> casos;
	
	while( casos-- ){
		cin >> q1.x1 >> q1.y1;
		cin >> q1.x2 >> q1.y2;
		cin >> q2.x1 >> q2.y1;
		cin >> q2.x2 >> q2.y2;
		
		//q1 está mais à esquerda
		if( q1.x1 <= q2.x1 ){
		
			// intercepta no x
			if( q2.x1 < q1.x2 )
				x1 = q2.x1;
			else{
				cout << "No Overlap\n";
				if( casos )
					cout << "\n";
				continue;				
			}
			
			//se intercepta no x, determina x2
			if( q2.x2 <= q1.x2 )
				x2 = q2.x2;
			else
				x2 = q1.x2;
		
		//q2 está mais à esquerda
		}else{
			//intercepta no x
			if( q1.x1 < q2.x2 )
				x1 = q1.x1;
			else{
				cout << "No Overlap\n";
				if( casos )
					cout << "\n";
				continue;	
			}
			
			//se intercepta no x, determina x2
			if( q1.x2 <= q2.x2 )
				x2 = q1.x2;
			else
				x2 = q2.x2;
		}
		
		
		if( q2.y1 >= q1.y1 ){
			//se intercepta no y
			if( q2.y1 < q1.y2 )
				y1 = q2.y1;
			else{
				cout << "No Overlap\n";
				if( casos )
					cout << "\n";
				continue;	
			}
			
			//se intercepta no y, determina y2
			if( q2.y2 < q1.y2 )
				y2 = q2.y2;
			else
				y2 = q1.y2;
			
		}else{
			if( q1.y1 < q2.y2 )
				y1 = q1.y1;
			else{
				cout << "No Overlap\n";
				if( casos )
					cout << "\n";
				continue;	
			}
			
			//se intercepta no y, determina y2
			if( q1.y2 < q2.y2 )
				y2 = q1.y2;
			else
				y2 = q2.y2;
		}
		
		cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
		if( casos )
			cout << "\n";
		
	}
	
}
