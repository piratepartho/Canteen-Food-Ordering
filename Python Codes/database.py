import sqlite3

connection=sqlite3.connect('info.db')

cursor=connection.cursor()

# cursor.execute('''CREATE TABLE IF NOT EXISTS Info
# (UUID TEXT,Name TEXT,Pin TEXT,Balance INT,Contact TEXT, primary key(UUID) )''')

# cursor.execute('''DROP TABLE info''')

# cursor.execute('''INSERT INTO Info VALUES("1151114346","EVAN","1436",150,"#phone number")''')



uuid="24323917524"
res=cursor.execute('''SELECT * FROM INFO where uuid='''+uuid)



print(res.fetchall())
# person=res.fetchone()
# print(type(person[3]))
# name,pin,balance,contact=res.fetchone()
# print(type(name),type(pin),type(balance),type(contact))



# uuid="24323917524"
# cursor.execute("SELECT EXISTS(SELECT * from Info where uuid="+uuid+")")
# print(cursor.fetchall())

# balance=700
# name="DHRUBO"
# # cursor.execute('update info set balance='+str(balance)+' where Name="'+name+'"')
# cursor.execute('update info set balance='+str(balance)+' where Name="'+name+'"')

def checkUUID(uuid):
    cursor.execute("SELECT EXISTS(SELECT * from Info where uuid="+uuid+")")
    if(cursor.fetchone()[0]==1):
        return 1
    else:
        return 0

def getPerson(uuid):
    res=cursor.execute('''SELECT * FROM INFO where uuid='''+uuid)
    person=res.fetchone()
    return person[1:]

# print(getPerson("24323917524"))

connection.commit()

cursor.close()