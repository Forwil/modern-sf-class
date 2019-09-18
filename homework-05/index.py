import web
import string
import time
import thread
import random
from web import form
import data

urls = (
	'/reg','reg',
	'/attend','attend',
	'/','board',
	'/result','result',
	'/resulthtml','resulthtml',
	'/scorehtml','scorehtml',
	'/infohtml','infohtml',
	'/turnhtml','turnhtml',
	'/totalboard','totalboard'
)

render = web.template.render('templates/')
app = web.application(urls, globals())

regform = form.Form(
	form.Textbox("id",
		form.notnull),
	form.Password("pd",
		form.notnull)
)

attendform = form.Form(
	form.Textbox("id",
		form.notnull),
	form.Password("pd",
		form.notnull),
	form.Textbox("num",
		form.regexp('\d+', 'Must be a digit')),	
)


class turnhtml:
	def GET(self):
		return data.nowturn

class infohtml:
	def GET(self):
		if data.gameover==1:
			return "<b>Game is over!</b> the winner is  <b>" + data.winner + "</b>  score is  <b>" + str(data.users[data.winner]) +"</b>"
		else:
			return "LEFT "+ str(data.TURNTIME-(time.time()-data.nowstart)) + "s TO SUBMIT YOUR NUMBER"

class result:
	def GET(self):
		s = ""
		for i in range(len(data.alluped)-1,-1,-1):
			s += str(data.alluped[i]['result']) + '\n'
		return s

class resulthtml:
	def GET(self):
		s = "<table ><tr><td>Round:</td>"
		l = len(data.alluped)
		for i in range(l-1,max(l-12,-1),-1):
			s += "<td>"+str(i)+"</td>"
		s +="</tr><td></td>"
		for i in range(l-1,max(l-12,-1),-1):
			s += "<td>"+str(data.alluped[i]['result'])+"</td>"
		s += "</tr></table>"
		return s

class scorehtml:
	def GET(self):
		b = sorted(data.users.iteritems(),key=lambda a:a[1],reverse = True)
		return render.scorehtml(b,data.alluped)

class totalboard:
	def GET(self):
		return render.totalboard(data.users,data.alluped)

class reg:
	def GET(self):
		form = regform()
		return render.reg(form)		
	def POST(self):
		form = regform()
		if not form.validates():
			return render.reg(form)
		else:
			i = web.input()
			myvar = dict(id = i.id)
			result = list(data.db.select('users',myvar,where = "id = $id"))
			if result==[]:
				data.db.insert('users',id = i.id,pd = i.pd)
				data.users[i.id]=0.0	
				return 0
			else:
				return -1

class attend:
	def GET(self):
		form = attendform()
		return render.attend(form)
	def POST(self):
		form = attendform()
		if not form.validates():
			return render.attend(form)
		else:
			i = web.input()
			i.num = string.atof(i.num)
			result = list(data.db.select('users',where = 'id = "%s"'%(i.id)))
			if result==[]:
				return -1
			if result[0]['pd']!=i.pd:
				return -2
			if 100<i.num or i.num<1:
				return -3
			if data.gameover == 1:
				return -4
			a = data.nowuped.get(i.id)
			t = data.TURNTIME-(time.time()-data.nowstart)
			if a==None and t>=data.DEAD:
				data.nown += 1
				data.nowtot += i.num
				data.nowuped[i.id] = dict(num = i.num,deltscore = 0)
			return "%f,%d,%d"%(0.3*random.random()+(data.TURNTIME-(time.time()-data.nowstart)),data.nowturn,a==None and t>=data.DEAD)

class board:
	def GET(self):
		t = data.TURNTIME-(time.time()-data.nowstart)
		a = render.board(data.DEAD,data.TURNTIME,t>=data.DEAD,data.nowturn,t,data.alluped,data.users,data.TURNTIME)
		return a
def dealwinlost(uped,users,avgn,nowturn):
	minv = 101
	maxv = 0
	winner = 0
	for i in uped:
		delt = abs(uped[i]['num']-avgn)
		if delt>maxv:
			maxv = delt
		if delt<minv:
			minv = delt
			winner = i
	uped[winner]['deltscore'] = 10
	for i in uped:
		if i==winner:
			continue
		delt = abs(uped[i]['num']-avgn)
		if delt==maxv:
			uped[i]['deltscore'] = -1
	a = list(data.db.select('users'))
	for i in a:
		if i['id'] not in uped and i['id']!=winner:
			uped[i['id']] = dict(num = 0.0,deltscore = -5)
	for i in a:
		users[i['id']] += uped[i['id']]['deltscore']
	return winner

def gameinit():
	a = list(data.db.select('users'))
	for i in a:
		data.users[i['id']]=0.0	

def roundinit():
	data.nowuped = {}
	data.nown = 0
	data.nowtot = 0

def round():
	data.nowstart = time.time()
	time.sleep(data.TURNTIME-data.DEAD)
	if (data.nown!=0):
		avgn = data.nowtot/data.nown * 0.618
		data.nowuped['winner'] = dealwinlost(data.nowuped,data.users,avgn,data.nowturn)
		data.nowuped['result'] = avgn
		data.nowuped['turn'] = data.nowturn
		data.alluped.append(data.nowuped)
		data.nowturn += 1
		if data.nowturn >= data.MAXTURN:
			data.gameover = 1
		t =data.TURNTIME-(time.time()-data.nowstart)
		if t>0:
			time.sleep(t)

def game():
	gameinit()
	temp = data.TURNTIME
	data.TURNTIME = 10
	round()
	data.TURNTIME = temp
	while True:
		roundinit()
		round()
		if data.gameover ==1:
			break
	maxscore = -100000
	for i in data.users:
		if data.users[i]>maxscore:
			maxscore = data.users[i]
			data.winner = i
	thread.exit_thread() 

if __name__ == "__main__":
	thread.start_new_thread(game,())
	app.run()
