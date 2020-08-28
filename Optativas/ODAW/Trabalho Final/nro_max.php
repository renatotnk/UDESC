<?php
  require('conexao.php');

  if(isset($_POST['range_dias'])){
    $stmt = $con->prepare("UPDATE configuracoes SET dias_maximos = ? WHERE id_conf = 1");
    $stmt->bindParam(1, $_POST['range_dias']);
    $stmt->execute();
    header('location: login.php');
    die();
  }else{
    header('location: login.php');
    die();
  }

?>
