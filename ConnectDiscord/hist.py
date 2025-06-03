#Deals with the history logs

#######Write#######
#function to create a timestamp string
def timest(x):
    dt = x.created_at.date()
    hr = x.created_at.hour
    min = x.created_at.minute

    if hr == 23:
        hr_str = "01"
    elif hr == 24:
        hr_str = "02"
    elif hr < 8:
        hr_str = "0" + str(hr + 2)
    else:
        hr_str = str(hr + 2)

    if min < 10: 
        min_str = "0" + str(min)
    else: 
        min_str = str(min)

    date = str(dt) + " " + hr_str + ":" + min_str
    return date


#function to create a history file with the last 100 messages in the specified channel
def channelHist(messages):
    if messages is not None and len(messages) > 0:
        guildname = str(messages[0].guild.name).replace(" ", "_")
        channelname = str(messages[0].channel.name).replace(" ", "_")
        filename = str(guildname + "_-_" + channelname + ".txt")
        messages.reverse()
        f = open(filename, "w")
        f.write("#Messages in " + guildname + " at " + channelname + "\n\n")
        for i in messages:
            f.write(i.author.name + " at " + timest(i))
            f.write("\n")
            f.write(i.content)
            f.write("\n")
        f.close()
        print("<" + guildname + " at " + channelname + ": Success getting history>")
    else: print("<" + guildname + " at " + channelname + ": Unable to get history>")

#function to append the history file with every new message
def appendHist(message):
    if message is not None:
        guildname = str(message.guild.name).replace(" ", "_")
        channelname = str(message.channel.name).replace(" ", "_")
        filename = str(guildname + "_-_" + channelname + ".txt")
        f = open(filename, "a")
        f.write(message.author.name + " at " + timest(message))
        f.write("\n")
        f.write(message.content)
        f.write("\n")
        f.close()

#######Read#######
#returns the entire contents of the history file of a channel
def viewFullHist(guildname, channelname):
        filename = str(guildname + "_-_" + channelname + ".txt").replace(" ", "_")
        f = open(filename)
        h = f.readlines()
        f.close()
        return h

#returns the most recent message in a channel
def viewPrev(guildname, channelname):
    m = viewFullHist(guildname, channelname)
    return m[-2], m[-1]

#returns a message, starting with the most recent
def viewHist(guildname, channelname, num):
    i = int(num)*2
    h = viewFullHist(guildname, channelname)
    return h[-i], h[-i+1]