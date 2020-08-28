package server;

import javax.jws.WebService;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Random;

@WebService(endpointInterface = "server.Server")
public class ServerImpl implements Server{
	public static HashMap<Integer, String> clientes = new HashMap<Integer, String>();
	public static Random rand = new Random();
	public static HashMap<Integer, String> mensagens = new HashMap<Integer, String>();
	public static int ID_MSG = 1;

	ServerImpl(){
	        clientes.put(-1, "Servidor");
	        mensagens.put(0, "Bem-vindo ao servidor.");
	}
	
	public int comeca_sessao(String nick){
		if (nick == "Servidor" || clientes.containsValue(nick)){
			return -99;
		}
		
		int id = rand.nextInt(256);
		while(clientes.containsKey(id)){
			id = rand.nextInt(256);
		}
		clientes.put(id, nick);
		multicast(-1, nick + " acabou de entrar.");
		return id;
	}

	public void finaliza_sessao(int id){
		if(clientes.containsKey(id)){
			multicast(-1, clientes.get(id) + " acabou de sair");
			clientes.remove(id);
		}
	}

	public void multicast(int id, String msg){
		if (clientes.containsKey(id)){
			String nick = clientes.get(id);
			mensagens.put(ID_MSG, nick + ":" + msg);
			ID_MSG++;
		}
	}

	public String get_mensagens(int ultimo_id){
		String retorno = "";
		for(int i : mensagens.keySet()){
			if (i >= ultimo_id){
				retorno = retorno + Integer.toString(i) + "||" + mensagens.get(i) + "\n";			
			}
		}

		return retorno;
	}
}


