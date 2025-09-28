#include <stdio.h>
#include <math.h>

 void funcion3(){
     int i; 
     float x=0,  xk=0,  t=0,  it=0, fx,fxk,xk1,fxk1,er;
     
     printf("Elija el intervalo de la funcion: x^3-3sen(x^2)+1\n");
     
     printf("Ingrese a X0\n");
     scanf("%f", &x);
          printf("Ingrese a X1\n");
     scanf("%f", &xk);
     
     printf("Ingrese el numero de iteraciones que desea:\n");
     scanf("%f", &it);
     
        printf("Ingrese el tamaño del error que desea:\n");
     scanf("%f", &t);
      
     printf("|   Xk-1  ||    Xk    ||   f(Xk-1)  ||   f(Xk)   ||    Xk+1    ||   f(Xk+1)   || Er || Er% | \n");
     
     fx=x*x*x-(3*sin(x*x)+1);
     fxk=xk*xk*xk-(3*sin(xk*xk)+1);
     
     xk1=xk-fx*((xk-x)/fxk-fx);
     fxk1=xk1*xk1*xk1-(3*sin(xk1*xk1)+1);
     
    
     
     float sx=1, sxk=1, sfxk=1, sfx=1, sxk1=1, sfxk1=1, ser=1, n=10;
     int l=0;
     printf("|   %2.2f  ||  %2.2f   || %2.6f || %2.6f || %2.6f || %2.6f ||  Er  ||  Er% |\n", x, xk, fx, fxk, xk1, fxk1);
     
     for(i=1;i<=it;i++){
         
         sx=1, sxk=1, sfxk=1, sfx=1, sxk1=1, sfxk1=1, ser=1, n=2;
        
         
    x=xk;
    xk=xk1;
         
     fx=x*x*x-(3*sin(x*x)+1);
     fxk=xk*xk*xk-(3*sin(xk*xk)+1);
     
     xk1=xk-fx*((xk-x)/fxk-fx);
     fxk1=(pow(xk1,3))-(3*sin(xk1*xk1)+1);
     
     er=(x-xk)/x;
     
     if(er<=t){
         er=0;
     }
     
     n=2;
      l=0;
     while(l!=1){
         
         
         if(x>=100&&x>=pow(10,n)){
             sx=pow(10,n);

         }else{
             l=1;
         }
         n++;
         
     }
          n=2;
      l=0;
              while(l!=1){
                  
         if(xk>=100&&xk>=pow(10,n)){
             sxk=pow(10,n);

         }else{
             l=1;
         }
         n++;
                  
              }
              
            n=2;
             l=0;
             while(l!=1){
         if(fx>=100&&fx>=pow(10,n)){
             sfx=pow(10,n);

         }else{
             l=1;
         }
         n++;
             }
             
              n=2;
            l=0;
         
             while(l!=1){
         if(fxk>=100&&fxk>=pow(10,n)){
             sfxk=pow(10,n);
              
         }else{
             l=1;
         }
         n++;
             }
             
              n=2;
             l=0;
             

             while(l!=1){
         if(xk1>=100&&xk1>=pow(10,n)){
             sxk1=pow(10,n);
             
         }else{
             l=1;
         }
         n++;
             }
             n=2;
            l=0;
                        while(l!=1){
                 
         if(fxk1>=100&&fxk1>=pow(10,n)){
             sfxk1=pow(10,n); 
              
         }else{
             l=1;
         }
         n++;
             }
         
              
    er=(x-xk)/x;
     
     if(x<0||xk<0){
         
         er*(-1);
         
     }

         printf("| %2.2fE-%1.0f || %2.2fE-%1.0f || %2.6f E-%1.0f||%2.6fE-%1.0f||%2.6fE-%1.0f||%2.6fE-%1.0f||%2.2f||%2.2f%|\n", x/sx, pow(sx,1.0/10), xk/sxk, pow(sxk,1.0/10), fx/sfx, pow(sfx,1.0/10),fxk/sfxk, pow(sfxk,1.0/10), xk1/sxk1, pow(sxk1,1.0/10), fxk1/sfxk1, pow(sfxk1,1.0/10), er/ser, er/ser);
         
     }
     if(er==0){
        printf("\nLa raiz del intervalo es: %f\n", xk1);     
         }else{
             printf("\nNo se obtuvo la raiz con este intervalo\n")
         }
     
 }
 
 
 
 void funcion3(){
     int i; 
     float x=0,  xk=0,  t=0,  it=0, fx,fxk,xk1,fxk1,er;
     
     printf("Elija el intervalo de la funcion: x^3-3sen(x^2)+1\n");
     
     printf("Ingrese a X0\n");
     scanf("%f", &x);
          printf("Ingrese a X1\n");
     scanf("%f", &xk);
     
     printf("Ingrese el numero de iteraciones que desea:\n");
     scanf("%f", &it);
     
        printf("Ingrese el tamaño del error que desea:\n");
     scanf("%f", &t);
      
     printf("|   Xk-1  ||    Xk    ||   f(Xk-1)  ||   f(Xk)   ||    Xk+1    ||   f(Xk+1)   || Er || Er% | \n");
     
     fx=x*x*x+(6*(x*x)+(9.4*x)+2.5);
     fxk=xk*xk*xk-(6*(xk*xk)+(9.4*xk)+2.5);
     
     xk1=xk-fx*((xk-x)/fxk-fx);
     fxk1=xk1*xk1*xk1-(6*(xk1*xk1)+(9.4*xk1)+2.5);
     
    
     
     float sx=1, sxk=1, sfxk=1, sfx=1, sxk1=1, sfxk1=1, ser=1, n=10;
     int l=0;
     printf("|   %2.2f  ||  %2.2f   || %2.6f || %2.6f || %2.6f || %2.6f ||  Er  ||  Er% |\n", x, xk, fx, fxk, xk1, fxk1);
     
     for(i=1;i<=it;i++){
         
         sx=1, sxk=1, sfxk=1, sfx=1, sxk1=1, sfxk1=1, ser=1, n=2;
        
         
    x=xk;
    xk=xk1;
         
   fx=x*x*x+(6*(x*x)+(9.4*x)+2.5);
     fxk=xk*xk*xk-(6*(xk*xk)+(9.4*xk)+2.5);
     
     xk1=xk-fx*((xk-x)/fxk-fx);
     fxk1=xk1*xk1*xk1-(6*(xk1*xk1)+(9.4*xk1)+2.5);
     
     er=(x-xk)/x;
     
     if(er<=t){
         er=0;
     }
     
     n=2;
      l=0;
     while(l!=1){
         
         
         if(x>=100&&x>=pow(10,n)){
             sx=pow(10,n);

         }else{
             l=1;
         }
         n++;
         
     }
          n=2;
      l=0;
              while(l!=1){
                  
         if(xk>=100&&xk>=pow(10,n)){
             sxk=pow(10,n);

         }else{
             l=1;
         }
         n++;
                  
              }
              
            n=2;
             l=0;
             while(l!=1){
         if(fx>=100&&fx>=pow(10,n)){
             sfx=pow(10,n);

         }else{
             l=1;
         }
         n++;
             }
             
              n=2;
            l=0;
         
             while(l!=1){
         if(fxk>=100&&fxk>=pow(10,n)){
             sfxk=pow(10,n);
              
         }else{
             l=1;
         }
         n++;
             }
             
              n=2;
             l=0;
             

             while(l!=1){
         if(xk1>=100&&xk1>=pow(10,n)){
             sxk1=pow(10,n);
             
         }else{
             l=1;
         }
         n++;
             }
             n=2;
            l=0;
                        while(l!=1){
                 
         if(fxk1>=100&&fxk1>=pow(10,n)){
             sfxk1=pow(10,n); 
              
         }else{
             l=1;
         }
         n++;
             }
         
              
    er=(x-xk)/x;
     
     if(x<0||xk<0){
         
         er*(-1);
         
     }
         printf("| %2.2fE-%1.0f || %2.2fE-%1.0f || %2.6f E-%1.0f||%2.6fE-%1.0f||%2.6fE-%1.0f||%2.6fE-%1.0f||%2.2f||%2.2f%|\n", x/sx, pow(sx,1.0/10), xk/sxk, pow(sxk,1.0/10), fx/sfx, pow(sfx,1.0/10),fxk/sfxk, pow(sfxk,1.0/10), xk1/sxk1, pow(sxk1,1.0/10), fxk1/sfxk1, pow(sfxk1,1.0/10), er/ser, er/ser);
         
     }
     
     if(er==0){
        printf("\nLa raiz del intervalo es: %f\n", xk1);     
         }else{
             printf("\nNo se obtuvo la raiz con este intervalo\n")
         }
     
 }

int main()
{
    printf("Funcion numero 3: x^3-3sen(x^2)+1");
    funcion3();
    
    printf("Funcion numero 4: x^3-3sen(x^2)+1");
    funcion4();

    return 0;
}

