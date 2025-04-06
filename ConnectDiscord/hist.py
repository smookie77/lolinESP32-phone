#function to create a timestamp string
#function to create a history file with the last 100 messages in the specified channel

def timest(x):
    dt = x.created_at.date()
    hr = x.created_at.hour
    min = x.created_at.minute

    if hr == 23:
        hr_str = "01"
    elif hr == 24:
        hr_str = "02"
    elif hr < 10:
        hr_str = "0" + str(hr + 2)
    else:
        hr_str = str(hr + 2)

    if min < 10: 
        min_str = "0" + str(min)
    else: 
        min_str = str(min)

    date = str(dt) + " " + hr_str + ":" + min_str
    return date


def channelHist(messages):
    if messages is not None and len(messages) > 0:
        guildname = str(messages[0].guild.name).replace(" ", "_")
        channelname = str(messages[0].channel.name).replace(" ", "_")
        filename = str(guildname + "_-_" + channelname + ".txt")
        messages.reverse()
        f = open(filename, "w")
        f.write("#Messages in " + guildname + " at " + channelname + "\n\n")
        for i in messages:
            #f.write(i.author.name + " in " + i.guild.name + " at " + i.channel.name + " at " + timest(i))
            f.write(i.author.name + " at " + timest(i))
            f.write("\n")
            f.write(i.content)
            f.write("\n")
        f.close()
        print("<Succes getting history!>")

    else: print("< Something went wrong :( >")

def appendHist(message):
    if message is not None:
        f = open("hist.txt", "a")
        f.write(message.author.name + " in " + message.guild.name + " at " + message.channel.name + " at " + timest(message))
        f.write("\n")
        f.write(message.content)
        f.write("\n")
        f.close()
