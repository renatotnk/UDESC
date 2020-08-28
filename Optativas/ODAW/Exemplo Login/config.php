<?php
$link = mysqli_connect('localhost', 'root', '','prova');

if($link === false){
    die("erro ao se conectar " . mysqli_connect_error());
}
?>
