#use hook to send messages

from discord_webhook import DiscordWebhook

def sendMessage(message):
    webhook = DiscordWebhook(url='url to hook', content=message)
    response = webhook.execute()