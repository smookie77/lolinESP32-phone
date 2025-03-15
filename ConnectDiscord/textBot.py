#Create bot to recieve messages

import discord

import hist
import on_screen

import login_info

def recipientFunc():
    intents = discord.Intents.default()
    intents.message_content = True

    client = discord.Client(intents=intents)

    @client.event
    async def on_ready():
        print(f'We have logged in as {client.user}')
        channel = client.get_channel(login_info.channel_id) #replace with your channel id
        messages = [message async for message in channel.history(limit=100)]
        hist.channelHist(messages)
        

    @client.event
    async def on_message(message):
        on_screen.print_msgCurrent(message)



    client.run(login_info.token) #replace with your token
