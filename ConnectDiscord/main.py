import threading

import textBot
import textHook


#use the bot to read incomming messages & make it run regardless of user input
threading1 = threading.Thread(target=textBot.recipientFunc)
threading1.daemon = True
threading1.start()

#use the webhook to send messages
while True:
    message = input("Your message:\n").lower()
    textHook.sendMessage(message)