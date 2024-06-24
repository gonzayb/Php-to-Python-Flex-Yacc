# Php-to-Python-Flex-Yacc
Compilar phptopython.l

flex phptopython.l


Compilar phptopython.y

bison -d phptopython.y

Compilar el lex.yy.c y phptopython.tab.c

gcc -o phptopython lex.yy.c phptopython.tab.c -lfl


ejecutar pruebas
./phptopython < ./pruebas/[nombre de la prueba].php