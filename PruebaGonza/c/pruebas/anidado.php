<?php
$x = 3;
$y = 8;

if ($x < $y) {
    echo "Si";
    if (3 == 8) {
        if (3 == 8) {
            if (3 != 8) {
                echo "No";
            }
            echo "No";
        }
        echo "No";
    } else {
        echo "Si";
    }
} else {
    if (3 != 8) {
        echo "Corresponde";
    } else {
        echo "No corresponde";
    }
    if (3 == 8) {
        echo "Corresponde";
    } else {
        echo "No Corresponde";
    }
}
?>