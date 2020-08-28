<?php
  require('conexao.php');

  if(isset($_POST['cpf'])){
    $stmt = $con->prepare("UPDATE usuario SET privilegios = 1 WHERE cpf = ?");
    $stmt->bindParam(1, $_POST['cpf']);
    $stmt->execute();
    header('location: login.php');
    die();
  }else{
    header('location: login.php');
    die();
  }

?>
