 #include <iostream>
 using namespace std;
 
 class Quadrado{
       public:
       int x1, x2, y1, y2;
 };
 
 int main(){
     Quadrado g1, g2;
     Quadrado *guarda1 = &g1, *guarda2 = &g2, *temp;
     int casos;
     int x1, y1, x2, y2;
     int total = 10000, forte, fraca;
     
     cin >> casos;
     
     for( int i = 1; i <= casos; ++i ){
            cin >> guarda1 -> x1 >> guarda1 -> y1 >> guarda1 -> x2 >> guarda1 -> y2;
            cin >> guarda2 -> x1 >> guarda2 -> y1 >> guarda2 -> x2 >> guarda2 -> y2; 
            

            if( guarda1 -> x1 > guarda2 -> x1 ){
                temp = guarda1;
                guarda1 = guarda2;
                guarda2 = temp;
            }
            

            if( guarda2 -> x1 < guarda1 -> x2 ){
                x1 = guarda2 -> x1;
            }else{
               x1 = -1;
            }
               
            if( x1 != -1 ){
                if( guarda1 -> x2 <= guarda2 -> x2 )
                    x2 = guarda1 -> x2;
                else
                    x2 = guarda2 -> x2;
            }          
            
            if( guarda1 -> y1 > guarda2 -> y1 ){
                temp = guarda1;
                guarda1 = guarda2;
                guarda2 = temp;
            }
            
            //guarda1 sempre em cima
            if( guarda2 -> y1 < guarda1 -> y2 )
                y1 = guarda2 -> y1;
            else
                x1 = -1;
            
            if( x1 != -1 ){
                if( guarda2 -> y2 <= guarda1 -> y2 )
                    y2 = guarda2 -> y2;
                else
                    y2 = guarda1 -> y2;       
            }
            
            if( x1 != -1 ){
                forte = ( x2 - x1 ) * ( y2 - y1 );
                fraca = - 2 * forte;
            }else{
                  fraca = 0;
                  forte = 0;
            }
            
            fraca += (guarda1 -> x2 - guarda1 -> x1) * ( guarda1 -> y2 - guarda1 -> y1 );          
            fraca += (guarda2 -> x2 - guarda2 -> x1) * ( guarda2 -> y2 - guarda2 -> y1 ); 
            
            cout << "Night " << i << ": " << forte << " " << fraca << " " 
            << ( total - forte - fraca ) << endl;
                
     }
     
 }
