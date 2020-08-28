<?php
  if(isset($_GET["id"])){
    $id = $_GET["id"];
    require('conexao.php');
    $stmt = $con->prepare("DELETE FROM agendamentos WHERE id_agendamento = ?");
    $stmt->bindParam(1, $id);
    $stmt->execute();
    header("location: login.php");
  }

  die();
?>

<html>
<head>

</head>
<body>

</body>
</html>
