from posixpath import split
import serial
import time
import http.client
import json
import sqlite3

connection=sqlite3.connect('info.db')
cursor=connection.cursor()

conn = http.client.HTTPSConnection("portal.metrotel.com.bd")

headersList = {
 "Accept": "*/*",
 "User-Agent": "Thunder Client (https://www.thunderclient.com)",
 "Content-Type": "application/json"
}



##################################################################
foodName=["PARATHA","OMELETE","DAL","TEA","SINGARA","SAMUCHA"]
price=[5,20,10,10,5,5]
#################################################################



ser = serial.Serial(
    port='COM6',\
    baudrate=9600)

print("connected to: " + ser.portstr)

person=[]

def sendMSG(msg,contact):
    #use your personal API system
    #not uploaded because of security
    return

def printToBT(string):
    ser.reset_input_buffer()
    print("SENDING :", string)
    ser.reset_output_buffer()
    ser.write(string.encode()+b'\n')#for now
    ser.flush()
    time.sleep(1)

def readFromBT():
    print("RECEIVING: ")
    s=str(ser.readline())
    s=s[2:][:-5]
    print(s)
    while(not s.startswith("C")): #sometimes getting \xff as garbage, so it is removed
        s=s[1:]

    print("RECEIVED MSG: ",s)
    return s

def checkUUID(uuid):
    cursor.execute("SELECT EXISTS(SELECT * from Info where uuid="+uuid+")")
    if(cursor.fetchone()[0]==1):
        return 1
    else:
        return 0

def getPerson(uuid):
    res=cursor.execute('''SELECT * FROM INFO where uuid='''+uuid)
    person=res.fetchone()
    return person[1:] #discard uuid 

def updatePrice(name,balance):
    cursor.execute('update info set balance='+str(balance)+' where Name="'+name+'"')
    connection.commit()

# code system
# $$ means invalid
# CPS ---> COMMAND PASSWORD
# CID ---> COMMAND TO CHECK UUID
# CMS ---> SEND MSG

while True:
    s=readFromBT()
    command=s.split('-')[0]
    if(command=="CID"):
        uuid=s.split('-')[1]
        if(checkUUID(uuid)):
            person=getPerson(uuid)
            print("SENDING NAME TO BT: ",person[0])
            printToBT("R-OK-"+person[0])
        else:
            printToBT("R-NOT")
    elif(command=="CPS"):
        password=s.split('-')[1]
        print(password)
        print(person[1])
        if(password==person[1]):
            printToBT("R-PASSOK-"+str(person[2]))
        else:
            printToBT("R-PASSWRONG")
    elif(command=="CMS"):
        totalPrice=0
        msg=""
        for order in s.split('-')[1:] :
            foodID,quantity=order.split(',')
            msg=msg+foodName[int(foodID)]+" "+quantity+'\n'
            totalPrice+=price[int(foodID)]*int(quantity)
        msg+="TOTAL: "+str(totalPrice)
        flag=1
        while(flag<10):
            try:
                sendMSG(msg,person[3])
                print("ok")
                printToBT("R-OK")
                print("ok")
                print(person[2])
                print(totalPrice)
                print(type(totalPrice))
                print(type(person[2]))
                print(person[2])
                # person[2]=person[2]-totalPrice
                print("ok")
                updatePrice(person[0],person[2]-totalPrice)
                print("ok")
                break
            except:
                flag=flag+1
                pass 
        if(flag>=10):
            printToBT("R-NOT")


