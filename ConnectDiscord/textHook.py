#use hook to send messages

from discord_webhook import DiscordWebhook

import login_info

def sendMessage(message):
    webhook = DiscordWebhook(url=login_info.webhook, content=message) #replace with your webhook url
    response = webhook.execute()