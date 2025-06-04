##
# @file textBot.py
# @author ISrbz 
# @brief Logs in to Discord with a bot account.

import discord

import hist
from login_info import *

def recipientFunc():
    intents = discord.Intents.default()
    intents.message_content = True

    client = discord.Client(intents=intents)

    @client.event
    async def on_ready():
        print(f'We have logged in as {client.user}')

        guild = client.get_guild(server_id) # replace with your server id
        channels = client.get_all_channels()
        channelsToBackup = "general, off-topic, spam" # replace with the names of channels in your server you want to see
        for channel in channels:
            if channel.name in channelsToBackup and isinstance(channel, discord.TextChannel) and channel.permissions_for(guild.me).view_channel:
                messages = [message async for message in channel.history(limit=100)]
                hist.channelHist(messages)
        
        
        

    @client.event
    async def on_message(message):
        hist.appendHist(message)



    client.run(token) # replace with your token