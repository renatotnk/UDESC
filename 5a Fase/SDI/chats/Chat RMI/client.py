import Pyro4
from threading import Thread

# Chat client
class ChatClient(object):
	def __init__(self):
		# Chat service initialize
		self.ChatService = Pyro4.Proxy("PYRO:Chat.Service@192.168.100.4:10001")
		self.abort = 0
		self.USERNAME = None
		self.PASSWORD = None
		
	# Call back method
	#@Pyro4.oneway
	def show_message(self, text):
		print text

	def start(self):
		# New user or exist user?
		print " * System: Hi, welcom!\nAre you new user? (Yes / No): "

		choice = raw_input()

		if choice == "yes":
			print " * System: Welcome, new user! Please register before chat!"
			self.USERNAME = raw_input(" * User name: ")
			self.PASSWORD = raw_input(" * Password: ")

			self.ChatService.register(self.USERNAME, self.PASSWORD)	
		
		elif choice == "no":
			self.USERNAME = raw_input(" * User name: ")
			self.PASSWORD = raw_input(" * Password: ")

		else:
			raise ValueError("Wrong option.")

		# Nick name other one can see
		self.nick = raw_input(" * Input your dick: ")

		# Login
		self.ChatService.login(self.USERNAME, self.PASSWORD, self.nick, self)

		# Show people chatting on the server
		nicks = self.ChatService.list_nicks()
		if nicks:
			print " * The following people are on the server:"
			i = 1
			for n in nicks:
				print "%d. %s" % (i, n)
				i += 1

		# See existed group or create a new one 
		groups = sorted(self.ChatService.list_groups())

		see_group = raw_input(" * Wanna see groups online now? (Yes/No)")

		if see_group == "yes":
			if groups:
				print "* The following groups already exist:"
				i = 1
				for g in groups:
					print "%d. %s" % (i, g)
					i += 1
	
				self.group = raw_input(" * Choose one group or create a new one: ")
			else:
				self.group = raw_input(" * No group, please create a new one: ")

			# Join in the group
			self.ChatService.join_group(self.group, self.nick, self)
		else:
			pass

			
		
		print " * System: Start chatting!\n * Note: Use '#help' command for more instructions.\n"

		try:
			try:
				while not self.abort:
					# Chat input
					line = raw_input('> ').strip()
					if line == '#quit':
						self.ChatService.logout(self.nick)
						break

					# Show help instruction
					elif line == '#help':
						print " *** HELP ***\n * '#quit': quit chat.\n * '#list nicks': list current users.\n * '#list groups': list current groups.\n * '#group': show members with group name. \n * '#user': show user's group with user name. \n * '#join group' : join with group name or create a new one. \n * '#quit group': quit your current group. \n * '#dialogue': talk with some user you choose."

					# Show users now on server
					elif line == '#list nicks':
						nicks = self.ChatService.list_nicks()
						if nicks:
							print "* The following people are on the server:"
							i = 1
							for n in nicks:
								print "%d. %s" % (i, n)

					# Show groups now on the server
					elif line == '#list groups':
						print "* The following groups already exist:"
						i = 1
						for g in sorted(self.ChatService.list_groups()):
							print "%d. %s" % (i, g)
							i += 1

					# Show group's members
					elif line[0:6] == '#group':
						group_name = line[7:]

						if self.ChatService.group_info(group_name):
							print " * Here are members in group '%s':" % group_name
							i = 1
							
							for n in self.ChatService.group_info(group_name):
								print "%d. %s" % (i, n)
								i += 1
						else:
							print " * The group you're looking for dosen't exist. Please ues #join command to create a new one."

					# Show user's group
					elif line[0:5] == '#user':
						user_name = line[6:]
						user_group = self.ChatService.user_info(user_name)
						print " * The user '%s' is in group '%s'." % (user_name, user_group)

					# Join to the group given or create it if it doesn't exist
					elif line[0:11] == "#join group":
						self.group = line[12:]
						self.ChatService.join_group(self.group, self.nick, self)

					# Quit from chat group
					elif line == "#quit group":
						if self.group:
							self.ChatService.quit_group(self.group, self.nick, self)
						else:
							print " * You haven't logined any group!"

					# Chat with someone individually
					elif line[0:9] == "#dialogue":
						line = line[10:]
						dialogue_user = line.split()[0]
						text = line.split(None, 1)[1]
						self.ChatService.dialogue(self.nick, dialogue_user, text)

					else:
						self.ChatService.chat(self.group, self.nick, line)

			except EOFError:
				pass
		finally:
			# Quit from system
			self.abort = 1
			self._pyroDaemon.shutdown()

# Daemon thread deal with call back from server
class DaemonThread(Thread):
	def __init__(self, CC_obj):
		Thread.__init__(self)
		self.CC_obj = CC_obj
		self.setDaemon(True)

	def run(self):
		with Pyro4.core.Daemon() as daemon:
			daemon.register(self.CC_obj)
			daemon.requestLoop(lambda: not self.CC_obj.abort)


if __name__ == '__main__':
	
	CC_obj = ChatClient()
	daemonthread = DaemonThread(CC_obj)
	daemonthread.start()
	CC_obj.start()
