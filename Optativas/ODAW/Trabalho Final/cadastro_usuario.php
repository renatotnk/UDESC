<?php
   if (isset($_POST["nome"])){
    require('conexao.php');
    
    $stmt = $con->prepare("INSERT INTO `usuario` (`nome`, `privilegios`, `cpf`, `senha`, `email`) VALUES(?, 0, ?, md5(?), ?)");
    $stmt->bindParam(1, $_POST['nome']);
    $stmt->bindParam(2, $_POST['cpf']);
    $stmt->bindParam(3, $_POST['senha']);
    $stmt->bindParam(4, $_POST['email']);

    $stmt->execute();

    header("location: login.php");
    die();
   }

?>

<html>
<head>
<!-- ********* IMPORTS ********* -->
<link rel="stylesheet" href="bootstrap/css/bootstrap.min.css">
<script src="bootstrap/js/bootstrap.min.js"></script>
<link rel="stylesheet" href="login.css">
<script src="https://code.jquery.com/jquery-3.3.1.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>
<!-- ********* FIM IMPORTS ********* -->
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
<title>Login</title>
</head>
<body id="LoginForm">
  <div class="container">
    <div class="login-form">
      <div class="main-div">
        <div class="panel">
          <h1>UDESC</h1>
          <h2>Cadastro de Usuários</h2>
          <p>Por favor, digite seus dados para efetuar o cadastro na plataforma:</p>
        </div>
        <form id="Login" method="post" action="cadastro_usuario.php">
          <div class="form-group">
            <input name="nome" type="text" class="form-control" id="nome" placeholder="Nome de Usuário" required>
          </div>
          <div class="form-group">
            <input name="cpf" type="text" class="form-control" id="cpf" placeholder="CPF" required>
          </div>
          <div class="form-group">
            <input name="senha" type="password" class="form-control" id="senha" placeholder="Senha" required>
          </div>
          <div class="form-group">
            <input name="email" type="text" class="form-control" id="email" placeholder="Email" required>
          </div>
          <button type="submit" class="btn btn-primary">Cadastrar</button>
          <div>
            <a href="index.php">
              <button type = "button" style = "margin-top: 2px; background: #e24c4c none repeat scroll 0 0 !important;border-color: #e24c4c !important;color: #ffffff;font-size: 14px;width: 100%;height: 50px;line-height: 50px;padding: 0;" class="btn btn-cadastro">Voltar</button>
            </a>
          </div>
        </form>
        <?php
          if(isset($_GET['erro'])){
            echo '<div class="alert alert-danger" role="alert">Erro! CPF ou Senha inválidos!</div>';
          }
        ?>
      </div>
    </div>
  </div>
</body>
</html>