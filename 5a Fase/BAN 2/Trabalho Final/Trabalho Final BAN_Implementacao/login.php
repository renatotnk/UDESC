<?php
  ini_set('display_errors', 1);
  ini_set('display_startup_errors', 1);
  error_reporting(E_ALL);

  session_start();

  if(isset($_SESSION['senha']) && isset($_SESSION['cpf'])){
    require('conexao.php');
    $stmt = $con->prepare("SELECT privilegios FROM usuario WHERE cpf = ? AND senha = ? LIMIT 1");
    $stmt->bindParam(1, $_SESSION["cpf"]);
    $stmt->bindParam(2, $_SESSION["senha"]);
    $stmt->execute();
    $row_count = $stmt->rowCount();
    if ($row_count == 0){
      session_unset();
      session_destroy();
      header("location: index.php");
      die();
    }
    $result = $stmt->fetchAll();
    $privilegios = $result[0]['privilegios'];
  }else if(isset($_POST['cpf']) && isset($_POST['senha'])){
    $cpf = $_POST['cpf'];
    $senha = $_POST['senha'];
    $senha = md5($senha);
    require('conexao.php');
    $stmt = $con->prepare("SELECT privilegios FROM usuario WHERE cpf = ? AND senha = ? LIMIT 1");
    $stmt->bindParam(1, $cpf);
    $stmt->bindParam(2, $senha);
    $stmt->execute();
    $row_count = $stmt->rowCount();
    $result = $stmt->fetchAll();
    $privilegios = $result[0]['privilegios'];
    if ($row_count > 0){
      $_SESSION['cpf'] = $cpf;
      $_SESSION['senha'] = $senha;
    }else{
      header("location: index.php?erro=1");
      die();
    }
  }else{
    header("location: index.php");
    die();
  }

?>
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

  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
  <script src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.10.6/moment.min.js"></script>
  <script src="http://momentjs.com/downloads/moment-with-locales.min.js"></script>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.37/js/bootstrap-datetimepicker.min.js"></script>


  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.47/css/bootstrap-datetimepicker-standalone.css">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.47/css/bootstrap-datetimepicker.css">

  <title>Dashboard</title>
</head>
<body>
  <nav class="navbar navbar-inverse" role="navigation">
    <div class="container">
      <div class="collapse navbar-collapse" id="top-navbar-1">
        <ul class="nav navbar-nav navbar-right">
          <li>
            <a href="#" id="agenda">
              <i class="fa fa-calendar"></i></i> <span>Agendamentos</span>
            </a>
          </li>
          <?php
            if($privilegios == 2){
          ?>
            <li>
              <a href="#" id="event">
                <i class="fa fa-exclamation"></i> <span>Eventos</span>
              </a>
            </li>
          <?php
            }
          ?>
          <?php
            if($privilegios >= 1){
          ?>
          <li>
            <a href="#" id="adm">
              <i class="fa fa-lock"></i> <span>Área do Administrador</span>
            </a>
          </li>
          <?php
            }
          ?>
          <li>
            <a href="logout.php">
              <i class="fa fa-times"></i> <span>Sair</span>
            </a>
          </li>
        </ul>
      </div>
    </div>
  </nav>

  <div class="agend">
    <div class="container">
      <div class="row">
        <div class="col-sm-12 text wow fadeInLeft">
          <div class="col-sm-8 col-sm-offset-2">
            <h2>Novo Agendamento</h2>
            <hr />
            <form action="novo_agend.php" method="post">
              <div class="form-group">
                <label>CPF</label>
                <input type="input" class="form-control" placeholder="CPF (Somente Números)" name="cpf" value="<?php echo $_SESSION['cpf'];?>" <?php if($privilegios < 1){echo 'readonly';}?>>
              </div>

              <div class="form-group">
                <label>Quadra</label>
                <select class="form-control" name="quadra">
                  <?php
                    $stmt = $con->prepare("SELECT id_quadra, nome_quadra FROM quadra WHERE disponivel = 1");
                    $stmt->execute();
                    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
                      echo '<option value="'.$row['id_quadra'].'">'.$row['nome_quadra'].'</option>';
                    }
                  ?>
                </select>
              </div>

              <div class="form-group">
                <label>Data</label>
              </div>

              <div class="form-group col-sm-6">
                <div class='input-group date' id='datetimepicker1'>
                    <input type='text' class="form-control" name="data1"/>
                    <span class="input-group-addon">
                        <span class="glyphicon glyphicon-calendar"></span>
                    </span>
                </div>
              </div>

              <div class="form-group col-sm-6">
                <div class='input-group date' id='datetimepicker2'>
                  <input type='text' class="form-control" name="data2"/>
                  <span class="input-group-addon">
                    <span class="glyphicon glyphicon-calendar"></span>
                  </span>
                </div>
              </div>
              <div>
                <button type="submit" class="btn btn-primary">Agendar</button>
              </div>
            </form>
          </div>
        </div>
      </div>

      <?php
        if ($privilegios > 1){
      ?>
      <div class="row">
        <h2>Agendamentos</h2>
        <hr />

        <div class="col-sm-10 col-sm-offset-1">
            <div class="table-responsive">
                <table class="table table-condensed table-bordered">
                    <thead>
                        <tr>
                            <th>Data Início</th>
                            <th>Hora Inicio</th>
                            <th>Data Fim</th>
                            <th>Hora Fim</th>
                            <th>Nome</th>
                            <th>Quadra</th>
                            <th>Confirmado</th>
                        </tr>
                    </thead>
                    <tbody>
                      <?php
                        setlocale(LC_ALL, NULL);
                        setlocale(LC_ALL, 'pt_BR');
                        date_default_timezone_set('America/Sao_Paulo');

                        $stmt = $con->prepare("SELECT * FROM (agendamentos JOIN usuario USING (id_usuario)) JOIN quadra USING (id_quadra) WHERE DATE(data_fim) >= CURDATE() ORDER BY data_inicio");
                        $stmt->execute();
                        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
                          $data = date_create_from_format('Y-m-d H:i:s', $row['data_inicio']);
                          $data_fim = date_create_from_format('Y-m-d H:i:s', $row['data_fim']);
                          echo '<tr>';
                          echo '<td class="agenda-date" class="active" rowspan="1">';
                          //echo '<div class="dayofmonth"><b>'.$data->format('d').'</b></div>';
                          echo '<div>'.strftime("%d de %B de %Y", strtotime($data->format('d-m-Y'))).'</div>';
                          echo '</td>';
                          echo '<td class="agenda-time">';
                          echo $data->format('H:i');
                          echo '</td>';
                          echo '<td class="agenda-date" class="active" rowspan="1">';
                          //echo '<div class="dayofmonth"><b>'.$data->format('d').'</b></div>';
                          echo '<div>'.strftime("%d de %B de %Y", strtotime($data_fim->format('d-m-Y'))).'</div>';
                          echo '</td>';
                          echo '<td class="agenda-time">';
                          echo $data_fim->format('H:i');
                          echo '</td>';
                          echo '<td class="agenda-events">';
                          echo '<div class="agenda-event">';
                          echo $row['nome'];
                          echo '</div>';
                          echo '</td>';
                          echo '<td class="agenda-events">';
                          echo '<div class="agenda-event">';
                          echo $row['nome_quadra'];
                          echo '</div>';
                          echo '</td>';
                          if ($row["confirmado"] == 0){
                            echo '<td style="text-align: center"><a title="Confirmar?" href="confirmar.php?id='.$row["id_agendamento"].'"><i class="fa fa-times-circle-o fa-lg" style="color: #F44437"></i></a></i></td>';
                          }else{
                            echo '<td style="text-align: center"><a title="Cancelar?" href="cancelar.php?id='.$row["id_agendamento"].'"><i class="fa fa-check-circle-o fa-lg" style="color: #2DCC70"></i></i></td>';
                          }
                          echo '</tr>';
                        }
                      ?>
                    </tbody>
                </table>
            </div>
        </div>
      </div>
      <?php
        }
      ?>
    </div>
    </div>



  <div class="eventos" style="display:none;">
    <div class="container">
      <div class="row">
        <div class="col-sm-12 text wow fadeInLeft">
          <div class="col-sm-8 col-sm-offset-2">
            <h2>Criar Evento</h2>
            <hr />
            <form action="novo_evento.php" method="post">
              <div class="form-group">
                <label>Nome</label>
                <input type="input" class="form-control" placeholder="Nome" name="nome">
              </div>
              <div class="form-group">
                <select class="form-control" name="quadra">
                  <?php
                    $stmt = $con->prepare("SELECT id_quadra, nome_quadra FROM quadra WHERE disponivel = 1");
                    $stmt->execute();
                    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
                      echo '<option value="'.$row['id_quadra'].'">'.$row['nome_quadra'].'</option>';
                    }
                  ?>
                </select>
              </div>

              <div class="form-group">
                <label>Data</label>
              </div>

              <div class="form-group col-sm-6">
                <div class='input-group date' id='datetimepicker3'>
                    <input type='text' class="form-control" name="data1"/>
                    <span class="input-group-addon">
                        <span class="glyphicon glyphicon-calendar"></span>
                    </span>
                </div>
              </div>

              <div class="form-group col-sm-6">
                <div class='input-group date' id='datetimepicker4'>
                  <input type='text' class="form-control" name="data2"/>
                  <span class="input-group-addon">
                    <span class="glyphicon glyphicon-calendar"></span>
                  </span>
                </div>
              </div>

              <div class="form-group">
                <button type="submit" class="btn btn-primary">Cadastrar</button>
              </div>
            </form>
          </div>

          <div class="col-sm-10 col-sm-offset-1">
              <div class="table-responsive">
                  <table class="table table-condensed table-bordered">
                      <thead>
                          <tr>
                              <th>Data Início</th>
                              <th>Hora Inicio</th>
                              <th>Data Fim</th>
                              <th>Hora Fim</th>
                              <th>Nome</th>
                              <th>Quadra</th>
                          </tr>
                      </thead>
                      <tbody>
                        <?php
                          setlocale(LC_ALL, NULL);
                          setlocale(LC_ALL, 'pt_BR');
                          date_default_timezone_set('America/Sao_Paulo');

                          $stmt = $con->prepare("SELECT * FROM evento JOIN quadra USING (id_quadra) WHERE DATE(data_fim) >= CURDATE() ORDER BY data_inicio");
                          $stmt->execute();
                          while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
                            $data = date_create_from_format('Y-m-d H:i:s', $row['data_inicio']);
                            $data_fim = date_create_from_format('Y-m-d H:i:s', $row['data_fim']);
                            echo '<tr>';
                            echo '<td class="agenda-date" class="active" rowspan="1">';
                            //echo '<div class="dayofmonth"><b>'.$data->format('d').'</b></div>';
                            echo '<div>'.strftime("%d de %B de %Y", strtotime($data->format('d-m-Y'))).'</div>';
                            echo '</td>';
                            echo '<td class="agenda-time">';
                            echo $data->format('H:i');
                            echo '</td>';
                            echo '<td class="agenda-date" class="active" rowspan="1">';
                            //echo '<div class="dayofmonth"><b>'.$data->format('d').'</b></div>';
                            echo '<div>'.strftime("%d de %B de %Y", strtotime($data_fim->format('d-m-Y'))).'</div>';
                            echo '</td>';
                            echo '<td class="agenda-time">';
                            echo $data_fim->format('H:i');
                            echo '</td>';
                            echo '<td class="agenda-events">';
                            echo '<div class="agenda-event">';
                            echo $row['nome'];
                            echo '</div>';
                            echo '</td>';
                            echo '<td class="agenda-events">';
                            echo '<div class="agenda-event">';
                            echo $row['nome_quadra'];
                            echo '</div>';
                            echo '</td>';
                            echo '</tr>';
                          }
                        ?>
                      </tbody>
                  </table>
              </div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <div class="administrador" style="display:none;">
    <div class="container">
      <div class="row">
        <div class="col-sm-12 text wow fadeInLeft">
          <div class="col-sm-8 col-sm-offset-2">
            <h2>Relatorios</h2>
            <hr />
            <div class="form-group">
              <select id="relat" class="form-control">
                <option value="usuario">Relatório de Usuários</option>
                <option value="quadra">Relatório de Quadras</option>
              </select>
            </div>

            <div id="por_usuario" class="table-responsive">
              <table class="table table-condensed table-bordered">
                  <thead>
                      <tr>
                          <th>Nome</th>
                          <th>Agendamentos</th>
                      </tr>
                  </thead>
                  <tbody>
                  <?php
                    $stmt = $con->prepare("SELECT nome, COUNT(id_usuario) FROM agendamentos a JOIN usuario u USING (id_usuario) GROUP BY nome");
                    $stmt->execute();
                    //$result = $stmt->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_NUM);
                    while ($row = $stmt->fetch(PDO::FETCH_GROUP|PDO::FETCH_NUM)){
                      echo '<tr>';
                      echo '<td>'.$row[0].'</td><td>'.$row[1].'</td>';
                      echo '</tr>';
                    }
                  ?>
                </tbody>
              </table>
            </div>

            <div id="por_quadra" style="display: none">
              <table class="table table-condensed table-bordered">
                  <thead>
                      <tr>
                          <th>Nome</th>
                          <th>Agendamentos</th>
                      </tr>
                  </thead>
                  <tbody>
                  <?php
                    $stmt = $con->prepare("SELECT nome_quadra, COUNT(id_quadra) FROM agendamentos a JOIN quadra q USING (id_quadra) GROUP BY nome_quadra");
                    $stmt->execute();
                    //$result = $stmt->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_NUM);
                    while ($row = $stmt->fetch(PDO::FETCH_GROUP|PDO::FETCH_NUM)){
                      echo '<tr>';
                      echo '<td>'.$row[0].'</td><td>'.$row[1].'</td>';
                      echo '</tr>';
                    }
                  ?>
                </tbody>
              </table>
            </div>

          </div>

          <?php
            if($privilegios > 1){
          ?>

          <div class="col-sm-8 col-sm-offset-2">
            <h2>Cadastrar Bolsista</h2>
            <hr />
            <form action="novo_bolsista.php" method="post">
              <div class="form-group">
                <label>CPF</label>
                <input type="input" class="form-control" placeholder="CPF (Somente Números)" name="cpf">
              </div>
              <div class="form-group">
                <button type="submit" class="btn btn-primary">Cadastrar</button>
              </div>
            </form>
          </div>

          <?php
            $stmt = $con->prepare("SELECT dias_maximos FROM configuracoes LIMIT 1");
            $stmt->execute();
            $dias = $stmt->fetchAll();
          ?>

          <div class="col-sm-8 col-sm-offset-2">
            <h2>Remover Bolsista</h2>
            <hr />
            <form action="remove_bolsista.php" method="post">
              <div class="form-group">
                <select class="form-control" name="id">
                  <?php
                    $stmt = $con->prepare("SELECT id_usuario, cpf, nome FROM usuario WHERE privilegios=1");
                    $stmt->execute();
                    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
                      echo '<option value="'.$row['id_usuario'].'">'.$row['cpf']." - ".$row['nome'].'</option>';
                    }
                  ?>
                </select>
              </div>
              <div class="form-group">
                <button type="submit" class="btn btn-primary">Remover</button>
              </div>
            </form>
          </div>

          <div class="col-sm-8 col-sm-offset-2">
            <h2>Número de dias</h2>
            <hr />
            <form action="nro_max.php" method="post">
              <div class="form-group">
                <p>Defina o número mínimo de dias que deve anteceder o agendamento.</p>
                <span id="n_max"><?php echo $dias[0]['dias_maximos']; ?></span>
                <input type="range" value=<?php echo $dias[0]['dias_maximos']; ?> class="slider" min="0" max="30" step="0.1" id="range_dias" name="range_dias">
              </div>
              <div class="form-group">
                <button type="submit" class="btn btn-primary">Definir</button>
              </div>
            </form>
          </div>

          <div class="col-sm-8 col-sm-offset-2">
            <h2>Adicionar Blocos/Quadras</h2>
            <hr />

            <form action="adicionar_quadra_bloco.php" method="post">
              <div class="form-group">
                <select id="quad_ou_bloc" name="quad_ou_bloc" class="form-control">
                  <option value="quadra" selected>Quadra</option>
                  <option value="bloco">Bloco</option>
                </select>
              </div>

              <div class="form-group">
                <label>Nome</label>
                <input type="input" class="form-control" placeholder="Nome" name="nome">
              </div>
              <div class="form-group">
                <label>Bloco</label>
                <select id="id_bloco" name="id_bloco" class="form-control">
                  <?php
                    $stmt = $con->prepare("SELECT id_bloco, nome_bloco FROM bloco");
                    $stmt->execute();
                    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
                      echo '<option value="'.$row['id_bloco'].'">'.$row['nome_bloco'].'</option>';
                    }
                  ?>
                </select>
              </div>
              <div class="form-check">
                <input class="form-check-input" type="checkbox" value="disponivel" id="disp" name="disp">
                <label class="form-check-label" for="disp">
                  Disponível
                </label>
              </div>

              <div class="form-group">
                <button type="submit" class="btn btn-primary">Adicionar</button>
              </div>
            </form>

            <div class="col-sm-8 col-sm-offset-2">
              <h2>Remover Quadra</h2>
              <hr />

              <form action="remover_quadra.php" method="post">
                <div class="form-group">
                  <label>Quadra</label>
                  <select id="id_quadra" name="id_quadra" class="form-control">
                    <?php
                      $stmt = $con->prepare("SELECT id_quadra, nome_quadra FROM quadra");
                      $stmt->execute();
                      while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
                        echo '<option value="'.$row['id_quadra'].'">'.$row['nome_quadra'].'</option>';
                      }
                    ?>
                  </select>
                </div>
                <div class="form-group">
                  <button type="submit" class="btn btn-primary">Remover</button>
                </div>
              </form>
            </div>

            <div class="col-sm-8 col-sm-offset-2">
              <h2>Remover Bloco</h2>
              <hr />

              <form action="remover_bloco.php" method="post">
                <div class="form-group">
                  <label>Bloco</label>
                  <select id="id_bloco" name="id_bloco" class="form-control">
                    <?php
                      $stmt = $con->prepare("SELECT id_bloco, nome_bloco FROM bloco");
                      $stmt->execute();
                      while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
                        echo '<option value="'.$row['id_bloco'].'">'.$row['nome_bloco'].'</option>';
                      }
                    ?>
                  </select>
                </div>
                <div class="form-group">
                  <button type="submit" class="btn btn-primary">Remover</button>
                </div>
              </form>
            </div>
            <?php
              }
            ?>
          </div>


          <script>
            $("#quad_ou_bloc").on('change', function(){
              if ($(this).val() == "quadra"){
                $("#id_bloco").prop('disabled', false);
                $("#disp").prop('disabled', false);
              }else{
                $("#id_bloco").prop('disabled', true);
                $("#disp").prop('disabled', true);
              }
            });
          </script>
        </div>
      </div>
    </div>
  </div>
  <input type="hidden" id="min_data" value="<?php $stmt = $con->prepare("SELECT dias_maximos FROM configuracoes LIMIT 1"); $stmt->execute(); $result = $stmt->fetchAll(); echo $result[0]['dias_maximos']; ?>">
</body>
<script>
  $('#range_dias').on('input', function() {
    $('#n_max').html(Math.round($(this).val()));
  });
</script>

<script>
  $('#relat').on('change', function(){
    if($(this).val() == "usuario"){
      $("#por_quadra").fadeOut();
      $("#por_usuario").delay(400).fadeIn();
    }else{
      $("#por_usuario").fadeOut();
      $("#por_quadra").delay(400).fadeIn();
    }
  });
</script>

<script>
  $('#agenda').on('click', function(){
    $(".eventos").fadeOut();
    $(".administrador").fadeOut().delay(200);
    $(".agend").delay(500).fadeIn();
  });

  $('#event').on('click', function(){
    $(".administrador").fadeOut();
    $(".agend").fadeOut().delay(200);
    $(".eventos").delay(500).fadeIn();
  });

  $('#adm').on('click', function(){
    $(".eventos").fadeOut();
    $(".agend").fadeOut();
    $(".administrador").delay(500).fadeIn();
  });
</script>

<script type="text/javascript">
$(document).ready(function() {
  $(function() {
    $('#datetimepicker1').datetimepicker({locale: 'pt-br', minDate: moment().add(parseInt($('#min_data').val(), 10), 'd').toDate()});
    $('#datetimepicker2').datetimepicker({
      locale: 'pt-br',
      minDate: moment().add(parseInt($('#min_data').val(), 10), 'd').toDate(),
      useCurrent: false
    });
    $("#datetimepicker1").on("dp.change", function(e) {
      $('#datetimepicker2').data("DateTimePicker").minDate(e.date);
    });
    $("#datetimepicker2").on("dp.change", function(e) {
      $('#datetimepicker1').data("DateTimePicker").maxDate(e.date);
    });

    $('#datetimepicker3').datetimepicker({locale: 'pt-br', minDate: moment()});
    $('#datetimepicker4').datetimepicker({
      locale: 'pt-br',
      minDate: moment(),
      useCurrent: false
    });
    $("#datetimepicker3").on("dp.change", function(e) {
      $('#datetimepicker4').data("DateTimePicker").minDate(e.date);
    });
    $("#datetimepicker4").on("dp.change", function(e) {
      $('#datetimepicker3').data("DateTimePicker").maxDate(e.date);
    });
  });
});
</script>

</html>
