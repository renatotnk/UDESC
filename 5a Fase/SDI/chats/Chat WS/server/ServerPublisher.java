package server;

import javax.xml.ws.Endpoint;

public class ServerPublisher{
	public static void main(String [] args){
		System.out.println("Iniciando o server...");
		Endpoint.publish("http://192.168.100.9:10001/WSChat", new ServerImpl());
		System.out.println("Server iniciado.");
	}
}
