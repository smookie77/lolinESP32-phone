#!/bin/python

##
# @file main.py
# @author ISrbz 
# @brief Starts everything else.


import threading
import time

import textBot
import on_web

#I don't think the threading is necessary, but at this point I'm too scared to change it
##use the bot to read incomming messages
threading1 = threading.Thread(target=textBot.recipientFunc)
threading1.daemon = True
threading1.start()

time.sleep(10)

##launch the flask server to view and send messages
thread2 = threading.Thread(target=on_web.websth)
thread2.daemon = True
thread2.start()

#code breaks without this one.
while True:
    message = input("Your message:\n").lower()
