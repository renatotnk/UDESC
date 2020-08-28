<?php
  if (isset($_POST['id_quadra'])){
    require('conexao.php');
    $stmt = $con->prepare("DELETE FROM quadra WHERE id_quadra = ?");
    $stmt->bindParam(1, $_POST['id_quadra']);
    $stmt->execute();
    header("location: login.php");
    die();
  }else{
    header('location: login.php');
    die();
  }
?>
