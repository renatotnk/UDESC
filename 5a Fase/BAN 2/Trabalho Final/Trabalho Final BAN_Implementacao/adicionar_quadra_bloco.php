<?php
  if(isset($_POST['quad_ou_bloc']) && isset($_POST['nome'])){
    require('conexao.php');
    if($_POST['disp'] == "disponivel"){
      $disponivel = 1;
    }else{
      $disponivel = 0;
    }
    if($_POST['quad_ou_bloc'] == "quadra"){
      $stmt = $con->prepare("INSERT INTO quadra (disponivel, nome_quadra, id_bloco) VALUES (?, ?, ?)");
      $stmt->bindParam(1, $disponivel);
      $stmt->bindParam(2, $_POST['nome']);
      $stmt->bindParam(3, $_POST['id_bloco']);
    }else{
      $stmt = $con->prepare("INSERT INTO bloco (nome_bloco) VALUES (?)");
      $stmt->bindParam(1, $_POST['nome']);
    }

    $stmt->execute();

    header("location: login.php");
    die();
  }else{
    header("location: login.php");
    die();
  }
?>
