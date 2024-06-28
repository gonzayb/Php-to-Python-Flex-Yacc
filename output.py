integerVar = 42
stringVar = "Hello, world!"
arrayVar = [1, 2, 3]
floatVar = 3.14
boolVar = True
if isinstance(integerVar, object):
    print(integerVar, "\\$integerVar es un entero.")
if isinstance(stringVar, object):
    print(stringVar, "\\$stringVar es una cadena de texto.")
if isinstance(arrayVar, object):
    print(arrayVar, "\\$arrayVar es un array.")
if isinstance(floatVar, object):
    print(floatVar, "\\$floatVar es un número de punto flotante.")
if isinstance(boolVar, object):
    print(boolVar, "\\$boolVar es un booleano.")
