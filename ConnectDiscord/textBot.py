#Create bot to recieve messages

import discord

def recieveMessage():
    intents = discord.Intents.default()
    intents.message_content = True

    client = discord.Client(intents=intents)

    @client.event
    async def on_ready():
        print(f'We have logged in as {client.user}')

    @client.event
    async def on_message(message):
        print(message.author.name)
        print(message.content)

    client.run('token')
