package server;

import java.net.URL;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import java.util.Scanner;
import java.lang.Thread;


public class ClientJava{
	public static void main(String[] args){
		try{
			URL url = new URL("http://192.168.100.9:10001/WSChat?wsdl");
			QName qname = new QName("http://server/", "ServerImplService");

			Service service = Service.create(url, qname);

			Server server = service.getPort(Server.class);
			//System.out.println(server.comeca_sessao("jjjjj"));
			
			Scanner reader = new Scanner(System.in);
			System.out.println("Escolha seu nick: ");			
			String nick = reader.next();
			int meu_id = server.comeca_sessao(nick);
			if (meu_id == -99){
				System.out.println("Nick inválido.");
				System.exit(-1);
			}
			System.out.println(meu_id);
			Thread receber_dados = new Thread(){
                		private volatile boolean ativa = true;
                		public void run(){
                		        int ultima_mensagem = -1;
                		        while (ativa){
                		                String mensagens[] = server.get_mensagens(ultima_mensagem + 1).split("\n");


                		                for(String msg : mensagens){ 
                        		                if (msg != null && !msg.isEmpty()){
                		                                int msg_id = Integer.parseInt(msg.split("\\|\\|")[0]);
                        		                        String msg_corpo = msg.split("\\|\\|")[1];
                                        		        if(msg_id > ultima_mensagem){
                        		                                ultima_mensagem = msg_id;
                                        		        }
                                        		        System.out.println(msg_corpo);
                                       			  }
                                		}
                                		try{
                                		        Thread.sleep(200);
                               		 	}catch (InterruptedException e){
                               		 	        e.printStackTrace();
                               		 	}
                        		}
                		}
			};

  			receber_dados.start();
			
			String msg = "";

			while (true){
				msg = reader.nextLine();
				if (msg.equals("")){
					continue;
				}else if(msg.equals("exit")){
					break;
				}else{
					server.multicast(meu_id, msg);
				}
			}

			server.finaliza_sessao(meu_id);
			System.exit(0);
		}catch (Exception e){
			e.printStackTrace();
		}
	}
}
