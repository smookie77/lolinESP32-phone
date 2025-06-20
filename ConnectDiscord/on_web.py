##
# @file on_web.py
# @author ISrbz 
# @brief Deals with flask.

from flask import Flask, render_template, request, redirect, jsonify
from hist import viewHist, viewPrev
from textHook import sendMessage

import os

app = Flask(__name__)

##run a development flask server
def websth():
    os.system("flask --app ./ConnectDiscord/on_web.py run")

#for testing purposes
if __name__ == "__main__":
    websth()


##show a previous message
#@app.route('/<server>/<channel>/history')
def msg_prev(server, channel):
    num = request.args['num']
    info, message = viewHist(server, channel, num)
    data = {'info': info, 'message': message}
    return jsonify(data)
##show current message in this channel
#@app.route('/<server>/<channel>/')
def msg_last(server, channel):
    info, message = viewPrev(server, channel)
    data = {'info': info, 'message': message}
    return jsonify(data)
    #return render_template('basic_display_one.html', info=info, content=message)

##send a message to this channel
@app.route('/<server>/<channel>/')
def send_msg(server, channel):
    message = request.args.get('text')
    if message is None:
        return msg_last(server, channel)
    else:
        sendMessage(message, server, channel)
        new_url = '/' + server + '/' + channel
        return redirect(new_url, code=302)
    
@app.route('/<server>/<channel>/history')
def send_msg_hist(server, channel):
    message = request.args.get('text')
    if message is None:
        return msg_prev(server, channel)
    else:
        sendMessage(message, server, channel)
        new_url = '/' + server + '/' + channel
        return redirect(new_url, code=302)

