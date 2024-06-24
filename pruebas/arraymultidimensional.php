<?php
$multiArray = array(
    array(
        "name" => "John",
        "age" => 28,
        "email" => "john@example.com"
    ),
    array(
        "name" => "Jane",
        "age" => 32,
        "email" => "jane@example.com"
    ),
    array(
        "name" => "Mike",
        "age" => 25,
        "email" => "mike@example.com"
    )
);

foreach ($multiArray as $person) {
    echo "Name: " . $person["name"] . "\n";
    echo "Age: " . $person["age"] . "\n";
    echo "Email: " . $person["email"] . "\n";
    echo "\n";
}
?>