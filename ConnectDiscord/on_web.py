##
# @file on_web.py
# @author ISrbz 
# @brief Deals with flask.

from flask import Flask, render_template, request, redirect
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
@app.route('/<server>/<channel>/history')
def msg_prev(server, channel):
    num = request.args['num']
    info, message = viewHist(server, channel, num)
    return render_template('basic_display_one.html', info=info, content=message)

##show current message in this channel
@app.route('/<server>/<channel>/')
def msg_last(server, channel):
    info, message = viewPrev(server, channel)
    return render_template('basic_display_one.html', info=info, content=message)

##send a message to this channel
@app.route('/<server>/<channel>/', methods=['POST'])
@app.route('/<server>/<channel>/history', methods=['POST'])
def send_msg(server, channel):
    message = request.form['text']
    sendMessage(message, server, channel)
    new_url = '/' + server + '/' + channel
    return redirect(new_url, code=302)

