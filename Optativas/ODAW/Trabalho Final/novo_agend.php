<html>
<head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://code.jquery.com/jquery-3.3.1.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>
  <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:100,100i,300,300i,500,500i">
  <link rel="stylesheet" href="assets/bootstrap/css/bootstrap.min.css">
  <link rel="stylesheet" href="assets/font-awesome/css/font-awesome.min.css">
  <link rel="stylesheet" href="assets/css/animate.css">
  <link rel="stylesheet" href="assets/css/style.css">
  <link rel="stylesheet" href="dashboard.css">
  <link rel="apple-touch-icon-precomposed" sizes="144x144" href="assets/ico/apple-touch-icon-144-precomposed.png">
  <link rel="apple-touch-icon-precomposed" sizes="114x114" href="assets/ico/apple-touch-icon-114-precomposed.png">
  <link rel="apple-touch-icon-precomposed" sizes="72x72" href="assets/ico/apple-touch-icon-72-precomposed.png">
  <link rel="apple-touch-icon-precomposed" href="assets/ico/apple-touch-icon-57-precomposed.png">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
  <script src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.10.6/moment.min.js"></script>
  <script src="http://momentjs.com/downloads/moment-with-locales.min.js"></script>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.37/js/bootstrap-datetimepicker.min.js"></script>
  <link rel="apple-touch-icon" sizes="57x57" href="favicon/apple-icon-57x57.png">
  <link rel="apple-touch-icon" sizes="60x60" href="favicon/apple-icon-60x60.png">
  <link rel="apple-touch-icon" sizes="72x72" href="favicon/apple-icon-72x72.png">
  <link rel="apple-touch-icon" sizes="76x76" href="favicon/apple-icon-76x76.png">
  <link rel="apple-touch-icon" sizes="114x114" href="favicon/apple-icon-114x114.png">
  <link rel="apple-touch-icon" sizes="120x120" href="favicon/apple-icon-120x120.png">
  <link rel="apple-touch-icon" sizes="144x144" href="favicon/apple-icon-144x144.png">
  <link rel="apple-touch-icon" sizes="152x152" href="favicon/apple-icon-152x152.png">
  <link rel="apple-touch-icon" sizes="180x180" href="favicon/apple-icon-180x180.png">
  <link rel="icon" type="image/png" sizes="192x192"  href="favicon/android-icon-192x192.png">
  <link rel="icon" type="image/png" sizes="32x32" href="favicon/favicon-32x32.png">
  <link rel="icon" type="image/png" sizes="96x96" href="favicon/favicon-96x96.png">
  <link rel="icon" type="image/png" sizes="16x16" href="favicon/favicon-16x16.png">
  <link rel="manifest" href="favicon/manifest.json">
  <meta name="msapplication-TileColor" content="#ffffff">
  <meta name="msapplication-TileImage" content="favicon/ms-icon-144x144.png">
  <meta name="theme-color" content="#ffffff">


  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.47/css/bootstrap-datetimepicker-standalone.css">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.47/css/bootstrap-datetimepicker.css">
</head>
<body>
  <?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);

    if(isset($_POST['cpf']) && isset($_POST['data1']) && isset($_POST['data2'])){
      $cpf = $_POST['cpf'];
      $quadra = $_POST['quadra'];
      $data1 = date_create_from_format('d/m/Y H:i', $_POST['data1']);
      $data2 = date_create_from_format('d/m/Y H:i', $_POST['data2']);
      /*echo $data1->format('m-d-y H-i');
      echo $data2->format('m-d-y H-i');*/

      require('conexao.php');
      $con->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
      $stmt = $con->prepare("SELECT id_usuario FROM usuario WHERE cpf = ? LIMIT 1");
      $stmt->bindParam(1, $cpf);
      $stmt->execute();
      $row_count = $stmt->rowCount();
      if ($row_count > 0){
        $data = $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
        $id = $data[0];

        $d1 = $data1->format('Y-m-d H:i:00');
        $d2 = $data2->format('Y-m-d H:i:00');

        $stmt = $con->prepare("SELECT * FROM agendamentos a, evento e WHERE (a.id_quadra = ? AND (a.data_inicio BETWEEN ? AND ? OR a.data_fim BETWEEN ? AND ?)) OR (e.id_quadra = ? AND (e.data_inicio BETWEEN ? AND ? OR e.data_fim BETWEEN ? AND ?))");
        $stmt->bindParam(1, $quadra);
        $stmt->bindParam(2, $d1);
        $stmt->bindParam(3, $d2);
        $stmt->bindParam(4, $d1);
        $stmt->bindParam(5, $d2);
        $stmt->bindParam(6, $quadra);
        $stmt->bindParam(7, $d1);
        $stmt->bindParam(8, $d2);
        $stmt->bindParam(9, $d1);
        $stmt->bindParam(10, $d2);
        $stmt->execute();
        $row_count = $stmt->rowCount();

        if ($row_count > 0){
          echo '<div class="alert alert-danger" role="alert">';
          echo '<strong>Oh não!</strong> Parece que já existe uma reserva neste horário, infelizmente não poderemos completar o seu agendamento. Você será redirecionado para a página de agendamentos em 10 segundos.';
          echo '</div>';
          $kek = $stmt->fetchAll();
          //sleep(5);
          //header("location: login.php");
          header('Refresh: 5; URL=login.php');
        }else{
          echo '<div class="alert alert-success" role="alert">';
          echo '<strong>Sucesso!</strong> Sua reserva foi feita no sistema, agora só falta a sua confirmação pelo sistema ou com um bolsista. Você será redirecionado para a página de agendamentos em 10 segundos.';
          $stmt = $con->prepare("INSERT INTO agendamentos (data_inicio, data_fim, id_usuario, id_quadra, confirmado) VALUES(?, ?, ?, ?, 0)");
          $stmt->bindParam(1, $d1);
          $stmt->bindParam(2, $d2);
          $stmt->bindParam(3, $id);
          $stmt->bindParam(4, $quadra);
          $stmt->execute();
          //sleep(5);
          //header("location: login.php");
          header('Refresh: 5; URL=login.php');
        }



      }else{
        header("location: index.php?erro=1");
        die();
      }


    }else{
      header("location: index.php");
      die();
    }
  ?>
</body>
</html>
