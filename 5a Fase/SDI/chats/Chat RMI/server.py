import Pyro4
import Pyro4.naming

CLIENT_DB = {
	# username : password
	"client1" : "000",
	"client2" : "000",
	"client3" : "000"
}

# Chat service
class ChatService(object):
	def __init__(self):
		self.nicks = []		# Online users list
		self.users = {}		# Online users object list
		self.groups = {}	# Group list
		self.offline_message = {}

	# Login
	def login(self, username, password, nick, CC_obj):

		# Check login info
		global CLIENT_DB
		if username in CLIENT_DB and password == CLIENT_DB[username]:
			print "Client login!"
			if nick in self.nicks:
				raise ValueError(" * Error: Nick is already used.")

			self.nicks.append(nick)
			self.users[nick] = CC_obj
			if nick in self.offline_message.keys():
				for msg in self.offline_message[nick]:
					CC_obj.show_message(msg)

			self.offline_message[nick] = []

		else:
			raise ValueError(" * Error: Wrong username or password.")
			
	# Logout
	def logout(self, nick):
		self.nicks.remove(nick)
		for key, value in self.groups.iteritems():
			for n in value:
				if n[0] == nick:
					value.remove(n)
		del self.users[nick]

	# New user register
	def register(self, username, password):
		#global CLIENT_DB
		#if username not in CLIENT_DB:
		#	CLIENT_DB[username] = password
		#	print "Client register!"
			
		#else: 
		#	raise ValueError(" * Error: User already exists.")
		return True

	# Join group
	def join_group(self, group, nick, CC_obj):
		if not group or not nick:
			raise ValueError(" * Error: Invalid group or nick.")
		
		if group not in self.groups:
			print "Client '%s' created new a group." % nick
			self.groups[group] = []

		self.groups[group].append((nick, CC_obj))
		message = "%s joined group %s" % (nick, group)
		print message
		self.chat(group, 'System',  message)

	# Quit group
	def quit_group(self, group, nick, CC_obj):
		if not group or not nick:
			raise ValueError(" * Error: Invalid group or nick.")

		self.groups[group].remove((nick, CC_obj))
		message = "%s left group %s" % (nick, group)
		print message
		self.chat(group, 'System',  message)

	# Return online user list
	def list_nicks(self):
		return self.nicks
			
	# Return group list
	def list_groups(self):
		return self.groups.keys()

	# Return group members list
	def group_info(self, group):
		names = []
		if group not in self.groups.keys():
			print "Client looks for none exist group."
			return names
		for u in self.groups[group]:
			names.append(u[0])
		return names

	# Return user's group
	def user_info(self, nick):
		for key, value in self.groups.iteritems():
			for n in value:
				if n[0] == nick:
					return key
	
	# Chat in the group
	def chat(self, group, nick, text):
		for (n, c) in self.groups[group][:]:
			if n != nick:
				c.show_message(" [%s]: " % nick + text)

	# Talk with some individually
	def dialogue(self, nick1, nick2, text):
		# Talk to the person online
		if nick2 in self.users.keys():
			self.users[nick2].show_message(" [%s]: " % nick1 + text)
		# Talk to the person offline
		else:
			self.offline_message[nick2] = []
			self.offline_message[nick2].append(" * Offline message from [%s]: " % nick1 + text + " <<<")


if __name__ == '__main__':
	
	# Daemon server
	with Pyro4.core.Daemon() as daemon:

		# Name server
		with Pyro4.naming.locateNS() as ns:
			CS_obj = ChatService()

			# ROR
			uri = daemon.register(CS_obj)
			print uri
			# Name server register
			print ns.register("Chat.Service", uri)
		print "Server's ready."
		daemon.requestLoop()
