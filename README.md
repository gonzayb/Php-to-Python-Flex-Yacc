# Php to Python Transpiler
## Using Flex and Bison

### Instrucciones de Uso
#### Compilar phptopython.l

> flex phptopython.l

#### Compilar phppy.y

> bison -d phppy.y

#### Compilar el lex.yy.c y phppy.tab.c

> gcc -o phptopython lex.yy.c phppy.tab.c -lfl


#### Ejecutar pruebas
> ./phptopython < ./pruebas/\[nombre de la prueba].**php** > ./pruebas/\[nombre de la prueba].**py**

### Ejemplos:
  
> └─$ ./phptopython < ./pruebas/declaraciones.php > ./resultados/declaraciones.py
>
>  └─$ ./phptopython < ./pruebas/constantes.php > ./resultados/constantes.py
>  
>  └─$ ./phptopython < ./pruebas/vectores.php > ./resultados/vectores.py
>  
>  └─$ ./phptopython < ./pruebas/arraymultidimensional.php > ./resultados/arraymultidimensional.py
>  
>  └─$ ./phptopython < ./pruebas/comprobaciontipos.php > ./resultados/comprobaciontipos.py
>  
>  └─$ ./phptopython < ./pruebas/if.php > ./resultados/if.py
>  
>  └─$ ./phptopython < ./pruebas/while.php > ./resultados/while.py
>  
>  └─$ ./phptopython < ./pruebas/funciones.php > ./resultados/funciones.py
>  
>  └─$ ./phptopython < ./pruebas/anidado.php > ./resultados/anidado.py
>  
>  └─$ ./phptopython < ./pruebas/ambito.php > ./resultados/ambito.py
