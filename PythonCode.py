import re
import string
import os.path
from os import path

#function that pulls from text file to get data
def Count(): 
	text = open("CS210_Project_Three_Input_File.txt", "r") 
	dictionary = dict()#creates dictionary to store data
	for line in text:#for loop to search data from file
		line = line.strip()#cleans unecessary spaces from file
		word = line.lower()#changes to lowercase for easier matching
		if word in dictionary:#adds to dictionary based on words in file
			dictionary[word] = dictionary[word] + 1
		else:
			dictionary[word] = 1
	for key in list(dictionary.keys()):#displays data from dictionary into capital letters 
		print(key.capitalize(), ":", dictionary[key])#displays the number of times item is found
	text.close()#closes the file
#function that counts instances of specific item based on user input
def CountInstances(searchItem):#gathers input from callIntFunc
    searchItem = searchItem.lower()#switches input to lowercase to match file
    text = open("CS210_Project_Three_Input_File.txt", "r")
    wordCount = 0#creates word count to store number of times item is found
    for line in text:
        line = line.strip()
        word = line.lower()
        if word == searchItem:#matches file data with input to display wordCount while incrementing
            wordCount += 1
    return wordCount
    text.close()
#function to gather data from frequency file to display histogram
def FindData():
	text = open("CS210_Project_Three_Input_File.txt", "r")
	frequency = open("frequency.dat", "w")#opens file as write to add data to
	dictionary = dict()
	for line in text:
		line = line.strip()
		word = line.lower()
		if word in dictionary:#similar functionality as Count function 
			dictionary[word] = dictionary[word] + 1
		else:
			dictionary[word] = 1
	for key in list(dictionary.keys()):#displays data capitalized with a word count
		frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")
		
	text.close()#closes both files
	frequency.close()
			