##
# @file textHook.py
# @author ISrbz 
# @brief Send messages via discord webhooks.


from login_info import webhook1, webhook2

from discord_webhook import DiscordWebhook

def sendMessageGeneral(message):
    webhook = DiscordWebhook(url=webhook1, content=message)
    response = webhook.execute()

def sendMessageSpam(message):
    webhook = DiscordWebhook(url=webhook2, content=message)
    response = webhook.execute()

def sendMessage(message, server, channel):
    if server == "Average_elimex_customers":
        if channel == "general": sendMessageGeneral(message)
        elif channel == "spam": sendMessageSpam(message)