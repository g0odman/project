#include <stdio.h>
int main(){
    char a;
    int b,c;
    printf("Please choose an operation(+/-/$):");
    scanf("%s",&a);
    if(!( a== '$' || a == '-' || a == '+')){
        printf("Invalid Operation");
        return 0;}
    printf("Please enter the first operand:");
    scanf("%d",&b);
    printf("%d",b);
    if( b< 48 || b > 57){
        printf("Invalid number");
        return 0;
    }
    printf("Please enter the second operand:");
    scanf("%d",&c);
    if( c< 48 || c > 57){
        printf("Invalid number");
        return 0;
    }
    int ans = 0;
   switch(a){
       case '$'  :
           if( c < b){
               printf("The result is: Not Valid");
               return 0;
           }
        case '-'  :
            printf("The result is: %d", b-c);
            break;
        case '+':
            printf("The result is: %d", b+c);
            break;
   }
    
    return 1;
}
