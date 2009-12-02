import random

infile = raw_input("Source file: ");

adjacency = [[0,0], [0,0]]
charlist  = ["end", "start"]


# pick an index with a maximum value
def maxIndex( n ):
	index = 0
	max = 0
	maxlist = []

	# randomly consider the end of the word and invalid choice 
	# to encourage longer words
	considerEnd = random.randint(0,2)

	# looks a bit complicated but the assumption is there exists
	# a high chance for ties occuring
	for entry in adjacency[n]:
		if considerEnd == 1 or index != 0:
			if entry > max:
					maxlist = [index]
					max = entry
			elif entry == max:
				maxlist.append(index)
		index+=1

	index = random.choice(maxlist)

	return index

# check if the word has vowels in it 
def containsVowels( w ):
	if w.find("a") != -1 or w.find("e") != -1 or w.find("i") != -1 or w.find("o") != -1 or w.find("u") != -1:
		return True
	
	return False


try:
	f = open(infile, "r")
	prev = None
	next = None

	# iterate through the file building the matrix
	for line in f:
		line = line.strip()
		line = line.lower()
		for c in line:
			if c in charlist:
				if prev is None: 
					# first letter in word
					prev = charlist.index(c)
					adjacency[1][prev] += 1
				else:
					# next letter in word
					next = charlist.index(c)
					adjacency[prev][next] += 1 
					prev = next
			else:
				# first time seeing letter
				charlist.append(c)
				sublist = list()
				
				for i in charlist:
					sublist.append(0)
				adjacency.append(sublist)

				count = 0;
				for i in adjacency:
					if count != charlist.index(c):
						i.append(0)
					count += 1

				if prev is None:
					# first letter in word
					prev = charlist.index(c)
					adjacency[1][prev] = 1
				else:
					adjacency[prev][charlist.index(c)] = 1
					prev = charlist.index(c)
			
		if len(adjacency[0])-1 >= charlist.index(c):
			adjacency[charlist.index(c)][0] += 1
		else:
			i = len(adjacency[0])
			for j in (i-1, charlist.index(c)):
				adjacency[0].append(0)
			adjacency[charlist.index(c)][0] += 1

		prev = None

	f.close()

	startLocs = []
	vowelLocs = []
	
	i = 0
	for entry in adjacency[1]:
		if entry != 0:
			startLocs.append(i)
		i+=1
	
	# grab the locations of the vowels
	if "a" in charlist:
		vowelLocs.append(charlist.index("a"))

	if "e" in charlist:
		vowelLocs.append(charlist.index("e"))

	if "i" in charlist:
		vowelLocs.append(charlist.index("i"))
	
	if "o" in charlist:
		vowelLocs.append(charlist.index("o"))
	
	if "u" in charlist:
		vowelLocs.append(charlist.index("u"))
	
	# pick a random starting position
	startPoint = random.choice(startLocs)
	curLoc = startPoint

	word = charlist[startPoint]
	nextChar = word
	
	while nextChar != "end":
		prev = curLoc
		curLoc = maxIndex(curLoc)
		nextChar = charlist[curLoc]

		if nextChar != "end":
			word += nextChar
		else:
			# every word should contain atleast one vowel
			if not containsVowels(word):
				prev = curLoc
				curLoc = random.choice(vowelLocs)
				nextChar = charlist[curLoc]
				word += nextChar

	print word

except IOError: 
	print "Cannot open ", infile

