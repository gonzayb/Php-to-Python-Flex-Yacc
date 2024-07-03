<?php

$integerVar = 42;
$stringVar = "Hello, world!";
$arrayVar = array(1, 2, 3);
$floatVar = 3.14;
$boolVar = true;

if (is_int($integerVar)) {
    echo "\$integerVar es un entero.\n";
}

if (is_string($stringVar)) {
    echo "\$stringVar es una cadena de texto.\n";
}

if (is_array($arrayVar)) {
    echo "\$arrayVar es un array.\n";
}

if (is_float($floatVar)) {
    echo "\$floatVar es un número de punto flotante.\n";
}

if (is_bool($boolVar)) {
    echo "\$boolVar es un booleano.\n";
}
?>