import datetime
import os
from sys import platform

def clearScr():
    if platform == "linux" or platform == "linux2":
        os.system('clear')
    elif platform == "win32":
        os.system('cls')

def print_location(message):
    location = message.guild.name + " at " + message.channel.name
    clearScr()
    print(location)

def print_msgCurrent(message):
    time = datetime.datetime.now()
    info = message.author.name +  " at " + time.strftime("%H:%M")
    print_location(message)
    print(info)
    print(message.content)