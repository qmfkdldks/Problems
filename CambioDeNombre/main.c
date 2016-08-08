#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1001 /* longitud m¢¥axima de una cadena */
#define MAXCHANGES 101 /* m¢¥aximo n¢¥umero de cambios de nombre */
typedef char string[MAXLEN];
string mergers[MAXCHANGES][2]; /* nombres de empresas antes/despu¢¥es*/
int nmergers; /* cantidad de cambios de nombre */
read_changes()
{
    nmergers = 4;
    int i; /* contador */
    scanf("%d\n",&nmergers);
    for (i=0; i<nmergers; i++) {
        read_quoted_string(&(mergers[i][0]));
        read_quoted_string(&(mergers[i][1]));
    }
}
read_quoted_string(char *s)
{
//    int i=0; /* contador */
//    char c; /* ultimo ¢¥ car¢¥acter */
//    while ((c=getchar()) != "\"") ;
//    while ((c=getchar()) != "\"") {
//    s[i] = c;
//    i = i+1;
//    }
//    s[i] = "\0";


}

int main()
{
    printf("Hello world!\n");
    char c = getchar();
    printf(c);
    return 0;
}
