<?php
  require('conexao.php');

  if(isset($_POST['id'])){
    $stmt = $con->prepare("UPDATE usuario SET privilegios = 0 WHERE id_usuario = ?");
    $stmt->bindParam(1, $_POST['id']);
    $stmt->execute();
    header('location: login.php');
    die();
  }else{
    header('location: login.php');
    die();
  }

?>
