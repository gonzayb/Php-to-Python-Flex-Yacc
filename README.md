# Php-to-Python-Flex-Yacc
Compilar phptopython.l

flex phptopython.l


Compilar phppy.y

bison -d phppy.y

Compilar el lex.yy.c y phppy.tab.c

gcc -o phptopython lex.yy.c phppy.tab.c -lfl


ejecutar pruebas
./phptopython < ./pruebas/[nombre de la prueba].php > 

┌──(kali㉿kali)-[~/…/Compiladores/Php-to-Python-Flex-Yacc]
└─$ flex phppy.l
┌──(kali㉿kali)-[~/…/Compiladores/Php-to-Python-Flex-Yacc/PruebaGonza/c]
└─$ bison -d phppy.y 
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ gcc -o phptopython lex.yy.c phppy.tab.c -lfl

┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/declaraciones.php > ./resultados/declaraciones.py
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/constantes.php > ./resultados/constantes.py      
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/vectores.php > ./resultados/vectores.py
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/arraymultidimensional.php > ./resultados/arraymultidimensional.py
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/comprobaciontipos.php > ./resultados/comprobaciontipos.py    
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/if.php > ./resultados/if.py             
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/while.php > ./resultados/while.py
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/funciones.php > ./resultados/funciones.py
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/anidado.php > ./resultados/anidado.py  
┌──(kali㉿kali)-[~/Documents/Compiladores/Php-to-Python-Flex-Yacc]
└─$ ./phptopython < ./pruebas/ambito.php > ./resultados/ambito.py