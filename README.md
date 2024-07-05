# Php to Python Transpiler
## Using Flex and Bison

### Requerimientos

- Sistema operativo LINUX
- GLIBC_2.34 (Chequear con el siguiente comando en una Terminal: *ldd --version*)
- FLEX (Para compilar)
- Bison (Para compilar)
- GCC (Para compilar)

### Instrucciones de Uso
#### Compilar phptopython.l

> flex phptopython.l

#### Compilar phppy.y

> bison -d phppy.y

#### Compilar el lex.yy.c y phppy.tab.c

> gcc -o phptopython lex.yy.c phppy.tab.c -lfl

#### Ejecutar pruebas
> ./phptopython < ./pruebas/\[nombre de la prueba].**php** > ./pruebas/\[nombre de la prueba].**py**

### Utilizar directamente el programa **phptopython** en Linux

1. Descargar el archivo **phptopython**
2. Crear un archivo php o descargar algún archivo de la carpeta de pruebas
3. Abrir terminal en la carpeta donde se ubica el archivo phptopython
4. Modificar los permisos con el siguiente comando:
> chmod +x phptopython
5. Ejecutar

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
