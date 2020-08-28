#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from TCP import *

cliente = TCP()

conexao = cliente.conectar('localhost', 45000)
cliente.enviar_dados(conexao, ('In TCP, the congestion window is one of the factors that determines the number of bytes that can be outstanding at any time. The congestion window is maintained by the sender. Note that this is not to be confused with the sliding window size which is maintained by the receiver. The congestion window is a means of stopping a link between the sender and the receiver from becoming overloaded with too much traffic. It is calculated by estimating how much congestion there is on the link.When a connection is set up, the congestion window, a value maintained independently at each host, is set to a small multiple of the MSS allowed on that connection. Further variance in the congestion window is dictated by an AIMD approach. This means that if all segments are received and the acknowledgments reach the sender on time, some constant is added to the window size.') * 10)
cliente.fechar_conexao(conexao)
