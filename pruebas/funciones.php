<?php
function foo($arg_1, $arg_2, $arg_n)
{
    echo "Example function.\n";
    return $retval;
}

function recursion($a)
{
    if ($a < 20) {
        echo "$a\n";
        recursion($a);
    }
}
?>