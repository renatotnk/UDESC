<?php
  if(isset($_POST['nome']) && isset($_POST['quadra']) && isset($_POST['data1']) && isset($_POST['data2'])){
    $nome = $_POST['nome'];
    $quadra = $_POST['quadra'];
    $data1 = date_create_from_format('d/m/Y H:i', $_POST['data1']);
    $data2 = date_create_from_format('d/m/Y H:i', $_POST['data2']);
    $d1 = $data1->format('Y-m-d H:i:00');
    $d2 = $data2->format('Y-m-d H:i:00');
    require('conexao.php');
    $stmt = $con->prepare("SELECT id_agendamento FROM agendamentos WHERE id_quadra = ? AND (data_inicio BETWEEN ? AND ? OR data_fim BETWEEN ? AND ?)");
    $stmt->bindParam(1, $quadra);
    $stmt->bindParam(2, $d1);
    $stmt->bindParam(3, $d2);
    $stmt->bindParam(4, $d1);
    $stmt->bindParam(5, $d2);
    $stmt->execute();
    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
      $rmstmt = $con->prepare("DELETE FROM agendamentos WHERE id_agendamento = ?");
      $rmstmt->bindParam(1, $row['id_agendamento']);
      $rmstmt->execute();
    }

    $stmt = $con->prepare("INSERT INTO evento (nome, data_inicio, data_fim, id_quadra) VALUES(?, ?, ?, ?)");
    $stmt->bindParam(1, $nome);
    $stmt->bindParam(2, $d1);
    $stmt->bindParam(3, $d2);
    $stmt->bindParam(4, $quadra);
    $stmt->execute();

    header("location: login.php");
    die();
  }else{
    header("location: login.php");
    die();
  }
?>
