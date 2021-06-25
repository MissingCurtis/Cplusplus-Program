import re
import string

# Original code left for testing purposes
def printsomething():
    print("Hello from python!")
# Original code left for testing purposes
def PrintMe(v):
    print("You sent me: " + v)
    return 100;
# Original code left for testing purposes
def SquareValue(v):
    return v * v

def OverallFrequency():#Gets frequency of items
    list1 = []
    inputList = []
    numList = []
    count = 0

    file1 = open("CS210_Project_Three_Input_File.txt","r")#opens file
    
    for i in file1:#Puts external file in list
        j = i.split()#Remove \n
        inputList.append(j)

    file1.close()#Close External file

    # remove duplicates from list 
    for i in inputList:
        if i not in list1:
            list1.append(i)

    for i in list1:#count number of Items
        count = 0
        for n in inputList:
            if n == i:
                count += 1
        numList.append(str(count))
    
    count = 0
    #Prints Item and count
    while count < len(list1):
        item = list1[count]
        num = numList[count]
        num = num.split()
        print ('{} {}'.format(item, num))
        count += 1
    
    # Close
    file1.close()
    

def IndividualFrequency(v):#Get one item count
    item = v
    freq = 0
    list1 = []

    file1 = open("CS210_Project_Three_Input_File.txt","r")#Open external file

    for i in file1:#Reads file to list
        j = i.split()
        list1.append(j)

    for list in list1:#Count number of item
        if item in list:
            freq += 1

    file1.close()#Close file
    #Return freq
    return freq

def Histogram():#Make Dat file
    list1 = []
    inputList = []
    numList = []
    count = 0

    file1 = open("CS210_Project_Three_Input_File.txt","r")#Open external file
    
    for i in file1:#Reads file to list
        j = i.split()
        inputList.append(j)

    file1.close()#Closes external file

    # remove duplicates from list 
    for i in inputList:
        if i not in list1:
            list1.append(i)

    for i in list1:#Counts of Items
        count = 0
        for n in inputList:
            if n == i:
                count += 1
        numList.append(str(count))
    
    count = 0

    while count < len(list1):#Put items and numbers in Dat

        item = list1[count]#Get item
        item = str(item) + '\n'#Put Item on new line

        num = numList[count]#Get Number
        num = num + '\n'#Put Number on new line

        file2 = open("frequency.dat","a")#Create file and or append to it

        file2.writelines(item)#Add item to file
        file2.write(num)#Add number to file

        count += 1
    
    
    file2.close()#close file