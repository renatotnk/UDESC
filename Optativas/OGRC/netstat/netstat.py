from easysnmp import Session
import argparse

ap = argparse.ArgumentParser()
ap.add_argument("-i", "--ip", required = False, help="Flag para especificar o IP")
ap.add_argument("-p", "--protocol", required = False, help="Flag para especificar o protocolo")
args = vars(ap.parse_args())
#print (args["ip"], args["protocol"])

host = args["ip"] if args["ip"] else '192.168.0.10' 
# Criando sessao SNMP para nossas consultas com IP padrao ou passado como argumento
session = Session(hostname= host, community='public', version=2)

# Realizando consultas
udp_items = session.walk('udp')
tcp_items = session.walk('tcpConnEntry')

# Formatacao
templ = "%-5s %-30s %-30s %-13s"
print(templ % (
    "Proto", "Local address", "Remote address", "Status"))

# Imprimindo informacoes
# Caso usuario tenha passado alguma flag de protocolo, ira imprimir apenas informacoes de tal protocolo
if args["protocol"] == None or args["protocol"] == "tcp":
    for item in tcp_items:
        if item.value == '5':
            print(templ % ( 'TCP' , ".".join(item.oid_index.split(".")[0:4]) + ":" + item.oid_index.split(".")[4], ".".join(item.oid_index.split(".")[5:9]) + ":" + item.oid_index.split(".")[9], "ESTABLISHED"))

if args["protocol"] == None or args["protocol"] == "udp":
    for item in udp_items:
        if item.snmp_type == 'IPADDR':
            print(templ % ( 'UDP' , ".".join(item.oid_index.split(".")[0:4]) + ":" + item.oid_index.split(".")[4], "", ""))
