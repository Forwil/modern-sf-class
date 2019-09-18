import web

db = web.database(dbn='sqlite',db='./web.db')

DEFAULTVALUE = 0
TURNTIME = 1.2
DEAD = 0.2
MAXTURN = 100

winner = ""
nowstart = 0
nowturn = 0
nown = 0
nowtot = 0
nowuped = {}
lastuped = {}
alluped = []
users = {}
gameover = 0

