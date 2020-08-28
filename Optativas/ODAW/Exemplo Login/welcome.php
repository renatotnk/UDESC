<?php

session_start();
$link = mysqli_connect("localhost", "root", "", "prova");

$query = "SELECT * FROM produto ORDER BY coda";
$result = mysqli_query($link, $query);

echo "<table border=\"1\">";
echo "<th>Código</th>";
echo "<th>Nome do produto</th>";
echo "<th>Data de Lançamento</th>";

while ($row = mysqli_fetch_row($result)) {
  echo "<tr><td>".$row[0]."</td>";
  echo "<td>".$row[1]."</td>";
  echo "<td>".$row[2]."</td>";
  echo "</tr>";
}
echo "</table><hr>";

if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
    header("location: login.php");

    exit;
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Welcome</title>
</head>
<body>
    <div class="page-header">
        <h1>Olá <?php echo htmlspecialchars($_SESSION["username"]); ?></b></h1>
    </div>


    <p>
        <a href="logout.php" class="btn btn-danger">Entre com outra conta</a>
    </p>
</body>
</html>
