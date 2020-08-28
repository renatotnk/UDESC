<?php
  if (isset($_POST['id_bloco'])){
    require('conexao.php');
    $stmt = $con->prepare("DELETE FROM bloco WHERE id_bloco = ?");
    $stmt->bindParam(1, $_POST['id_bloco']);
    $stmt->execute();
    header("location: login.php");
    die();
  }else{
    header('location: login.php');
    die();
  }
?>
