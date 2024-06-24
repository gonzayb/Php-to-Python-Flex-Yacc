
<?php

for ($i = 1; $i <= 10; $i++) {
    echo $i;
}
//Ojo con este
for ($i = 1, $j = 0; $i <= 10; $j += $i, print $i, $i++);
?>