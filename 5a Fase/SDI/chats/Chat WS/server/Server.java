package server;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

@WebService
@SOAPBinding(style = Style.RPC)
public interface Server{
	@WebMethod
	int comeca_sessao(String nick);
	@WebMethod
	void finaliza_sessao(int id);
	@WebMethod
	public void multicast(int id, String msg);
	@WebMethod
	public String get_mensagens(int ultimo_id);
}
