<!DOCTYPE html>
<html lang="pt-br">
<head>
  <meta charset="utf-8">
  <title>Projeto Mãos e Patas</title>
  <meta content="width=device-width, initial-scale=1.0" name="viewport">
  <meta content="ong; causa; animais;" name="keywords">

  <!-- Favicons -->
  <link href="img/logo.png" rel="icon">
  <link href="img/logo.png" rel="apple-touch-icon">

  <!-- Google Fonts -->
  <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,400i,500,600,700,700i|Montserrat:300,400,500,600,700" rel="stylesheet">

  <!-- Bootstrap CSS File -->
  <link href="lib/bootstrap/css/bootstrap.min.css" rel="stylesheet">

  <!-- Libraries CSS Files -->
  <link href="lib/font-awesome/css/font-awesome.min.css" rel="stylesheet">
  <link href="lib/animate/animate.min.css" rel="stylesheet">
  <link href="lib/ionicons/css/ionicons.min.css" rel="stylesheet">
  <link href="lib/owlcarousel/assets/owl.carousel.min.css" rel="stylesheet">
  <link href="lib/lightbox/css/lightbox.min.css" rel="stylesheet">

  <!-- Main Stylesheet File -->
  <link href="css/style.css" rel="stylesheet">
</head>
<body>
  <!-- Header -->
  <header id="header">

    <div class="container">

      <div class="logo float-left">
        <!-- Uncomment below if you prefer to use an image logo -->
        <h1 class="text-light"><a href="#intro" class="scrollto"><span>Mãos e Patas</span></a></h1>
        <!-- <a href="#header" class="scrollto"><img src="img/logo.png" alt="" class="img-fluid"></a> -->
      </div>

      <?php
        error_reporting(E_ALL);
        ini_set('display_errors', TRUE);
        ini_set('display_startup_errors', TRUE);
        session_start();
        if (!isset($_SESSION['token'])){
          if (isset($_POST['email']) && isset($_POST['password'])){
            $email = $_POST['email'];
            $senha = $_POST['password'];
            $conn = new PDO('mysql:host=localhost;dbname=maosepatas', 'LOGIN_SQL', 'SENHA_SQL');
            $stmt = $conn->prepare("SELECT * FROM usuarios WHERE email=:email AND senha=:senha");
            $stmt->bindParam(':email', $email);
            $stmt->bindParam(':senha', $senha);
            $stmt->execute();
            $users = $stmt->fetchAll(PDO::FETCH_ASSOC);
            if (count($users) > 0){
              $user = $users[0];
              $_SESSION['token'] = true;
              $_SESSION['nome'] = $user['nome'];
            }
          }
        }

        if(isset($_GET['sair'])){
          if($_GET['sair'] == '1'){
            unset($_SESSION['token']);
            unset($_SESSION['nome']);
            session_destroy();
          }
        }


      ?>

      <nav class="main-nav float-right d-none d-lg-block">
        <ul>
          <li class="active"><a href="#intro">Home</a></li>
          <li><a href="#about">Sobre Nós</a></li>
          <li><a href="#services">ONGs</a></li>
          <li><a href="#why-us">Como fazer parte</a></li>
          <?php
            if(isset($_SESSION['token'])){
              echo '<li><a href="#"><i class="ion-ios-paw"></i> '.$_SESSION['nome'].'</a></li>';
              echo '<li><a href="?sair=1"><i class="ion-ios-close"></i> Sair</a></li>';
            }else{
              echo '<li data-toggle="modal" data-target="#loginModal"><a href="#"><i class="ion-ios-paw"></i> Login</a></li>';
            }
          ?>
        </ul>
      </nav><!-- .main-nav -->
    </div>
  </header><!-- #header -->

  <!-- Intro Section -->
  <section id="intro" class="clearfix">
    <div class="container d-flex h-100">
      <div class="row justify-content-center align-self-center">
        <div class="col-md-6 intro-info order-md-first order-last">
          <h2>De mãos dadas<br>pela <span>causa!</span></h2>
          <div>
            <a href="#about" class="btn-get-started scrollto">Conheça</a>
          </div>
        </div>

        <div class="col-md-6 intro-img order-md-last order-first">
          <img src="img/logo.svg" alt="" class="img-fluid">
        </div>
      </div>

    </div>
  </section><!-- #intro -->

  <main id="main">

    <!-- Sobre Nós -->
    <section id="about">

      <div class="container">
        <div class="row">

          <div class="col-lg-5 col-md-6">
            <div class="about-img">
              <img src="img/bulldog.jpg" alt="">
            </div>
          </div>

          <div class="col-lg-7 col-md-6">
            <div class="about-content">
              <h2>Sobre Nós</h2>
              <h3>Ajudando você a ajudar quem precisa.</h3>
              <p>O projeto Mãos e Patas é uma plataforma que tem como objetivo principal prover um ambiente de auxílio e divulgação a ONGs de adoção ou que auxiliam na causa animal.</p>
              <p>Nossa plataforma também busca trazer um grau de transparência entre doadores, colaboradores, organizações e patrocinadores.  A plataforma é um canal de comunicação entre pessoas dispostas a ajudar e organizações que apoiam a causa e necessitam de auxílio com mantimentos, verba e pessoal.</p>
              <ul>
                <li><i class="ion-android-checkmark-circle"></i> Auxiliando voluntários na ajuda às ONGs.</li>
                <li><i class="ion-android-checkmark-circle"></i> Auxiliando as ONGs na exposição de suas conquistas e necessidades.</li>
                <li><i class="ion-android-checkmark-circle"></i> Todos juntos pela causa do bem-estar animal.</li>
              </ul>
            </div>
          </div>
        </div>
      </div>

    </section><!-- #about -->


    <!-- ONGs -->
    <section id="services" class="section-bg">
      <div class="container">
        <header class="section-header">
          <h3>ONGs Cadastradas</h3>
          <p>Clique em uma ONG para obter mais informações.</p>
        </header>

        <div class="row">

          <div class="col-md-6 col-lg-4 wow bounceInUp" data-wow-duration="1.4s">
            <div class="box">
              <!--<div class="icon" style="background: #fceef3;"><i class="ion-ios-analytics-outline" style="color: #ff689b;"></i></div>-->
              <div data-toggle="modal" data-target="#modalONG1" style="cursor:pointer">
                <img src="img/ong1.png" style="width:60px; padding-bottom:15px">
                <h4 class="title"><a>SOS Vida Animal</a></h4>
              </div>
              <p class="text-info" style="cursor: pointer" href="#texto1" data-toggle="collapse">Quem somos</p>
              <p class="description panel-collapse collapse text-justify" id="texto1">"SOS Vida Animal é uma organização da sociedade civil, de direito privado, sem fins lucrativos e de caráter associativo, registrada no CNPJ sob nº. 81.762.510/0001-06, com reconhecimento de utilidade pública Municipal pela Lei n. 4.697 de 31/05/1991 e Estadual pela Lei n. 12.580 de 08/06/1999. Atua desde 1989 em Londrina e região."</p>
            </div>
          </div>
          <div class="col-md-6 col-lg-4 wow bounceInUp" data-wow-duration="1.4s">
            <div class="box">
              <div data-toggle="modal" data-target="#modalONG2" style="cursor:pointer">
                <img src="img/ong2.png" style="width:60px; padding-bottom:15px">
                <h4 class="title"><a>Abrigo Animal</a></h4>
              </div>
              <p class="text-info" style="cursor: pointer" href="#texto2" data-toggle="collapse">Quem somos</p>
              <p class="description panel-collapse collapse text-justify" id="texto2">"A Associação ABRIGO ANIMAL, estabelecida em Joinville-SC, com CNPJ Nº 04.603.573/0001-60 é uma Organização Não-Governamental sem fins lucrativos. Foi fundada por voluntários em julho de 2001 com o objetivo de proteger animais domésticos abandonados e maltratados, providenciar atendimento veterinário, castração, vacinação e procurar novos lares para estes animais além de promover a conscientização da população."</p>
            </div>
          </div>

          <div class="col-md-6 col-lg-4 wow bounceInUp" data-wow-delay="0.1s" data-wow-duration="1.4s">
            <div class="box">
              <div data-toggle="modal" data-target="#modalONG3" style="cursor:pointer">
                <img src="img/ong3.png" style="width:60px; padding-bottom:15px">
                <h4 class="title"><a>FRADA</a></h4>
              </div>
              <p class="text-info" style="cursor: pointer" href="#texto3" data-toggle="collapse">Quem somos</p>
              <p class="description panel-collapse collapse text-justify" id="texto3">"A frada é uma associação sem fins lucrativos que age em defesa dos direitos animais, bem como na preservação do meio ambiente."</p>
            </div>
          </div>
          <div class="col-md-6 col-lg-4 wow bounceInUp" data-wow-delay="0.1s" data-wow-duration="1.4s">
            <div class="box">
              <div data-toggle="modal" data-target="#modalONG4" style="cursor:pointer">
                <img src="img/ong4.png" style="width:60px; padding-bottom:15px">
                <h4 class="title"><a>Mia Vida Proteção Animal</a></h4>
              </div>
              <p class="text-info" style="cursor: pointer" href="#texto4" data-toggle="collapse">Quem somos</p>
              <p class="description panel-collapse collapse text-justify" id="texto4">"A Mia Vida foi criada com o objetivo de implemementar o maior número de castrações possível, trabalho que fazemos continuamente desde as pessoas se conheceram em 2007. Somos pessoas que resolveram doar uma parte de seu tempo para os animais. Somos solidários a todos os animais. Fazemos um pouquinho por cada animal que aparece no nosso caminho, seja um cavalo com sede, um cachorro machucado, um coelho abandonado, um gatinho doente ou revirando lixo."</p>
            </div>
          </div>

          <div class="col-md-6 col-lg-4 wow bounceInUp" data-wow-delay="0.2s" data-wow-duration="1.4s">
            <div class="box">
              <div data-toggle="modal" data-target="#modalONG5" style="cursor:pointer">
                <img src="img/ong5.png" style="width:60px; padding-bottom:15px">
                <h4 class="title"><a>APRABLU</a></h4>
              </div>
              <p class="text-info" style="cursor: pointer" href="#texto5" data-toggle="collapse">Quem somos</p>
              <p class="description panel-collapse collapse text-justify" id="texto5">"APRABLU – ASSOCIAÇÃO PROTETORA DE ANIMAIS DE BLUMENAU, inscrita no CNPJ sob nº 03.585.420/0001-75, é uma organização não governamental (ONG), sem fins lucrativos, formada por voluntários que dedicam parte de seu tempo a iniciativas e/ou atividades que visam ao bem-estar e à proteção dos direitos dos animais. Fundada em 1999, tem como objetivo promover o bem-estar e as relações harmoniosas entre humanos e animais. A Aprablu dedica-se a projetos voltados à educação, conscientização para convivência responsável, saudável e harmônica com os animais domésticos e sensibilização das pessoas sobre a posse responsável."</p>
            </div>
          </div>
          <div class="col-md-6 col-lg-4 wow bounceInUp" data-wow-delay="0.2s" data-wow-duration="1.4s">
            <div class="box">
              <div data-toggle="modal" data-target="#modalONG6" style="cursor:pointer">
                <img src="img/ong6.png" style="width:60px; padding-bottom:15px">
                <h4 class="title">Instituto "É o Bicho!"</h4>
              </div>
              <p class="text-info" style="cursor: pointer" href="#texto6" data-toggle="collapse">Quem somos</p>
              <p class="description panel-collapse collapse text-justify" id="texto6">"O Instituto é o Bicho é uma organização sem fins lucrativos, que atua na proteção e defesa do direito a vida de todos os bichos, de nós mesmos e deste planeta que gentilmente nos acolhe."</p>
            </div>
          </div>

        </div>

      </div>


      <!-- Modals -->

      <div class="modal fade" id="modalONG1" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
          <div class="modal-content">
            <div class="modal-header">
              <h5 class="modal-title" id="exampleModalLabel"><b>SOS Vida Animal</b></h5>
              <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                <span aria-hidden="true">&times;</span>
              </button>
            </div>
            <div class="modal-body">
              <p>
                "SOS Vida Animal é uma organização da sociedade civil, de direito privado, sem fins lucrativos e de caráter associativo, registrada no CNPJ sob nº. 81.762.510/0001-06, com reconhecimento de utilidade pública Municipal pela Lei n. 4.697 de 31/05/1991 e Estadual pela Lei n. 12.580 de 08/06/1999. Atua desde 1989 em Londrina e região."
              </p>
              <p>
                <button data-toggle="collapse" type="button" class="btn btn-primary" data-target="#direta1">Doação Direta</button>
                <button type="button" class="btn btn-success">Doe Através da Plataforma</button>
                <div id="direta1" class="collapse">
                  Banco Itaú: Agência 4019 Conta Corrente 07820-5<br>
                  Banco do Brasil: Agência 5047-4 Conta Corrente 7507-8
                </div>
              </p>

            </div>
            <div class="modal-footer">
              <button type="button" class="btn btn-secondary" data-dismiss="modal">Sair</button>
            </div>
          </div>
        </div>
      </div>



      <div class="modal fade" id="modalONG2" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
          <div class="modal-content">
            <div class="modal-header">
              <h5 class="modal-title" id="exampleModalLabel"><b>Abrigo Animal</b></h5>
              <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                <span aria-hidden="true">&times;</span>
              </button>
            </div>
            <div class="modal-body">
              <p>
                "A Associação ABRIGO ANIMAL, estabelecida em Joinville-SC, com CNPJ Nº 04.603.573/0001-60 é uma Organização Não-Governamental sem fins lucrativos. Foi fundada por voluntários em julho de 2001 com o objetivo de proteger animais domésticos abandonados e maltratados, providenciar atendimento veterinário, castração, vacinação e procurar novos lares para estes animais além de promover a conscientização da população."
              </p>
              <p>
                <button data-toggle="collapse" type="button" class="btn btn-primary" data-target="#direta2">Doação Direta</button>
                <button type="button" class="btn btn-success">Doe Através da Plataforma</button>
                <div id="direta2" class="collapse">
                  Banco do Brasil: Agência 5214-0 Conta Corrente 1218398-9<br>
                  Banco Bradesco: Agência 2150-4 Conta Corrente 20445-5
                </div>
              </p>

            </div>
            <div class="modal-footer">
              <button type="button" class="btn btn-secondary" data-dismiss="modal">Sair</button>
            </div>
          </div>
        </div>
      </div>

      <div class="modal fade" id="modalONG3" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
          <div class="modal-content">
            <div class="modal-header">
              <h5 class="modal-title" id="exampleModalLabel"><b>FRADA</b></h5>
              <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                <span aria-hidden="true">&times;</span>
              </button>
            </div>
            <div class="modal-body">
              <p>
                "A frada é uma associação sem fins lucrativos que age em defesa dos direitos animais, bem como na preservação do meio ambiente."
              </p>
              <p>
                <button data-toggle="collapse" type="button" class="btn btn-primary" data-target="#direta3">Doação Direta</button>
                <button type="button" class="btn btn-success">Doe Através da Plataforma</button>
                <div id="direta3" class="collapse">
                  Banco do Brasil: Agência 5214-0 Conta Corrente 1218398-9<br>
                  Banco Bradesco: Agência 2150-4 Conta Corrente 20445-5
                </div>
              </p>

            </div>
            <div class="modal-footer">
              <button type="button" class="btn btn-secondary" data-dismiss="modal">Sair</button>
            </div>
          </div>
        </div>
      </div>



      <div class="modal fade" id="modalONG4" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
          <div class="modal-content">
            <div class="modal-header">
              <h5 class="modal-title" id="exampleModalLabel"><b>Mia Vida Proteção Animal</b></h5>
              <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                <span aria-hidden="true">&times;</span>
              </button>
            </div>
            <div class="modal-body">
              <p>
                "A Mia Vida foi criada com o objetivo de implemementar o maior número de castrações possível, trabalho que fazemos continuamente desde as pessoas se conheceram em 2007. Somos pessoas que resolveram doar uma parte de seu tempo para os animais. Somos solidários a todos os animais. Fazemos um pouquinho por cada animal que aparece no nosso caminho, seja um cavalo com sede, um cachorro machucado, um coelho abandonado, um gatinho doente ou revirando lixo."
              </p>
              <p>
                <button data-toggle="collapse" type="button" class="btn btn-primary" data-target="#direta4">Doação Direta</button>
                <button type="button" class="btn btn-success">Doe Através da Plataforma</button>
                <div id="direta4" class="collapse">
                  Banco Caixa: Agência 1637 Conta Corrente 1969-1
                </div>
              </p>

            </div>
            <div class="modal-footer">
              <button type="button" class="btn btn-secondary" data-dismiss="modal">Sair</button>
            </div>
          </div>
        </div>
      </div>



      <div class="modal fade" id="modalONG5" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
          <div class="modal-content">
            <div class="modal-header">
              <h5 class="modal-title" id="exampleModalLabel"><b>APRABLU</b></h5>
              <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                <span aria-hidden="true">&times;</span>
              </button>
            </div>
            <div class="modal-body">
              <p>
                "APRABLU – ASSOCIAÇÃO PROTETORA DE ANIMAIS DE BLUMENAU, inscrita no CNPJ sob nº 03.585.420/0001-75, é uma organização não governamental (ONG), sem fins lucrativos, formada por voluntários que dedicam parte de seu tempo a iniciativas e/ou atividades que visam ao bem-estar e à proteção dos direitos dos animais. Fundada em 1999, tem como objetivo promover o bem-estar e as relações harmoniosas entre humanos e animais. A Aprablu dedica-se a projetos voltados à educação, conscientização para convivência responsável, saudável e harmônica com os animais domésticos e sensibilização das pessoas sobre a posse responsável."
              </p>
              <p>
                <button data-toggle="collapse" type="button" class="btn btn-primary" data-target="#direta5">Doação Direta</button>
                <button type="button" class="btn btn-success">Doe Através da Plataforma</button>
                <div id="direta5" class="collapse">
                  Banco do Brasil: Agência 2307-8 Conta Corrente 1192068-8<br>
                  Banco Viacred: Agência 0101 Conta Corrente 915772-7
                </div>
              </p>

            </div>
            <div class="modal-footer">
              <button type="button" class="btn btn-secondary" data-dismiss="modal">Sair</button>
            </div>
          </div>
        </div>
      </div>


      <div class="modal fade" id="modalONG6" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
          <div class="modal-content">
            <div class="modal-header">
              <h5 class="modal-title" id="exampleModalLabel"><b>Instituto "É o Bicho!"</b></h5>
              <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                <span aria-hidden="true">&times;</span>
              </button>
            </div>
            <div class="modal-body">
              <p>
                "O Instituto é o Bicho é uma organização sem fins lucrativos, que atua na proteção e defesa do direito a vida de todos os bichos, de nós mesmos e deste planeta que gentilmente nos acolhe."
              </p>
              <p>
                <button data-toggle="collapse" type="button" class="btn btn-primary" data-target="#direta6">Doação Direta</button>
                <button type="button" class="btn btn-success">Doe Através da Plataforma</button>
                <div id="direta6" class="collapse">
                  contato@eobicho.org
                </div>
              </p>

            </div>
            <div class="modal-footer">
              <button type="button" class="btn btn-secondary" data-dismiss="modal">Sair</button>
            </div>
          </div>
        </div>
      </div>

    </section><!-- #services -->

    <!-- Como Fazer Parte -->
    <section id="why-us" class="wow fadeIn">
      <div class="container-fluid">

        <header class="section-header">
          <h3>Como Fazer Parte</h3>
          <p>Guia completo para entrada na plataforma.</p>
        </header>

        <div class="row">

          <div class="col-lg-6">
            <div class="why-us-img">
              <img style="cursor:pointer" src="img/why-us.png" alt="" class="img-fluid">
            </div>
          </div>

          <div class="col-lg-6">
            <div class="why-us-content">
              <p>Este vídeo irá lhe guiar através do processo de criação de conta, ele abordará tanto os passos necessário para a criação de uma conta de usuário comum, quanto para a criação e
                inserção da sua ONG no sistema, caso você seja responsável por uma. O processo é intuitivo e foi simplificado para o seu conforto, quaisquer dúvidas remanescentes podem ser sanadas
                nos enviando uma mensagem através do nosso e-mail <span class="text-primary">suporte@maosepatas.com</span>.</p>

              <div class="features wow bounceInUp clearfix">
                <i class="fa fa-usd" style="color: #85bb65;"></i>
                <h4>A plataforma é gratuíta e sempre será</h4>
                <p>Existem anúncios totalmente opcionais cujo lucro é destinado à ONG escolhida por você.</p>
              </div>

              <div class="features wow bounceInUp clearfix">
                <i class="fa fa-users" style="color: #ffb774;"></i>
                <h4>Juntos somos mais fortes</h4>
                <p>Seu apoio é muito bem-vindo. Você pode ajudar mais do que imagina.</p>
              </div>

              <div class="features wow bounceInUp clearfix">
                <i class="fa fa-download" style="color: #589af1;"></i>
                <h4>Aplicativo do Mãos e Patas</h4>
                <p>Ei, sabia que temos um app? Baixe através do <a href="https://play.google.com/store" target="_blank">link</a> e confira.</p>
              </div>

            </div>

          </div>

        </div>

      </div>
    </section>
  </main>

  <!--==========================
    Footer
  ============================-->
  <footer id="footer" class="section-bg">
    <div class="footer-top">
      <div class="container">

        <div class="row">

          <div class="col-lg-6">

            <div class="row">

                <div class="col-sm-6">
                  <div class="footer-newsletter">
                    <h4>Quer saber das novidades?</h4>
                    <p>Insira seu e-mail abaixo e iremos te avisar sempre que uma novidade sair.</p>
                    <form action="" method="post">
                      <input type="email" name="email"><input type="submit"  value="Inscrever-se">
                    </form>
                  </div>

                </div>

                <div class="col-sm-6">

                  <div class="footer-links">
                    <h4>Entre em contato conosco</h4>
                    <p>
                      <strong>Telefone:</strong> (47) 99717-0337<br>
                      <strong>E-mail:</strong> contato@maosepatas.com<br>
                    </p>
                  </div>

                  <div class="social-links">
                    <a href="#" class="twitter"><i class="fa fa-twitter"></i></a>
                    <a href="#" class="facebook"><i class="fa fa-facebook"></i></a>
                    <a href="#" class="instagram"><i class="fa fa-instagram"></i></a>
                    <a href="#" class="linkedin"><i class="fa fa-linkedin"></i></a>
                  </div>

                </div>

            </div>

          </div>

          <div class="col-lg-6">

            <div class="form">

              <h4>Nos envie uma mensagem</h4>
              <p>Através do formulário abaixo você pode entrar em contato conosco, preencha as informações e entraremos em contato em breve.</p>
              <form action="" method="post" role="form" class="contactForm">
                <div class="form-group">
                  <input type="text" name="name" class="form-control" id="name" placeholder="Nome Completo" data-rule="minlen:4" data-msg="Entre com pelo menos 4 caracteres." />
                  <div class="validation"></div>
                </div>
                <div class="form-group">
                  <input type="email" class="form-control" name="email" id="email" placeholder="E-mail" data-rule="email" data-msg="Entre com um e-mail válido." />
                  <div class="validation"></div>
                </div>
                <div class="form-group">
                  <textarea class="form-control" name="message" rows="5" data-rule="required" data-msg="Escreva uma mensagem para nós" placeholder="Mensagem"></textarea>
                  <div class="validation"></div>
                </div>

                <div id="sendmessage">Your message has been sent. Thank you!</div>
                <div id="errormessage"></div>

                <div class="text-center"><button type="submit" title="Send Message">Enviar</button></div>
              </form>
            </div>

          </div>



        </div>

      </div>
    </div>

    <div class="container">
      <div class="copyright">
        &copy; Copyright <strong>Mãos e Patas</strong>. All Rights Reserved
      </div>
      <div class="credits">
        Designed by Kleiton Pereira
      </div>
    </div>
  </footer><!-- #footer -->

  <a href="#" class="back-to-top"><i class="fa fa-chevron-up"></i></a>
  <div id="preloader"></div>

  <!-- JavaScript Libraries -->
  <script src="lib/jquery/jquery.min.js"></script>
  <script src="lib/jquery/jquery-migrate.min.js"></script>
  <script src="lib/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="lib/easing/easing.min.js"></script>
  <script src="lib/mobile-nav/mobile-nav.js"></script>
  <script src="lib/wow/wow.min.js"></script>
  <script src="lib/waypoints/waypoints.min.js"></script>
  <script src="lib/counterup/counterup.min.js"></script>
  <script src="lib/owlcarousel/owl.carousel.min.js"></script>
  <script src="lib/isotope/isotope.pkgd.min.js"></script>
  <script src="lib/lightbox/js/lightbox.min.js"></script>
  <!-- Contact Form JavaScript File -->
  <script src="contactform/contactform.js"></script>

  <!-- Template Main Javascript File -->
  <script src="js/main.js"></script>

  <!-- Modal -->
  <div class="modal fade" id="loginModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <h5 class="modal-title" id="exampleModalLabel">Login</h5>
          <button type="button" class="close" data-dismiss="modal" aria-label="Close">
            <span aria-hidden="true">&times;</span>
          </button>
        </div>
        <div class="modal-body">
          <form method="post" action="index.php">
            <div class="form-group">
              <label for="email">E-mail</label>
              <input type="email" class="form-control" id="email" name="email" aria-describedby="emailHelp" placeholder="Enter email" required>
            </div>
            <div class="form-group">
              <label for="password">Senha</label>
              <input type="password" class="form-control" id="password" name="password" placeholder="Senha" required>
            </div>
            <button type="submit" class="btn btn-primary">Login</button>
            <button type="button" class="btn btn-secondary" data-dismiss="modal">Fechar</button>
          </form>
        </div>
      </div>
    </div>
  </div>

</body>
</html>
