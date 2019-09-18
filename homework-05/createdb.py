import sqlite3
con = sqlite3.connect("web.db")
cur = con.cursor()
cur.execute("create table users(id varchar(20) primary key,pd varchar(20))")

#cur.execute("create table users(id varchar(10) primary key,pd varchar(10),score double)")
#cur.execute("create table turns(turn long primary key,n long,tot double)")
#cur.execute("create table results(id varchar(10),turn long ,num double,deltscore double, primary key (id,turn),foreign key (id) references users(id),foreign key (turn) references turns(turn))")
