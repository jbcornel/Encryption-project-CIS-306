def GCD(x, y): 
  
    if x > y: 
        small = y 
    else: 
        small = x 
    for i in range(1, small+1): 
        if((x % i == 0) and (y % i == 0)): 
            gcd = i 
              
    return gcd 


class encryptionObject:
    def __init__(self):
        
        self.p = int(input("Hello, please enter in your first random prime number(P): "))
        p = self.p
        self.q = int(input("Hello, please enter in your second random prime number(Q): "))
        q = self.q
        self.n = p*q
        self.phiN = (p-1)*(q-1)
        phiN = (p-1)*(q-1)
        i = 2
        while GCD(i, phiN) != 1:
            i = i + 1
        self.e = i
        e = i
        if e >= phiN:
            print("Error: ")
        k = 1
        while ((k*phiN)+1) % e != 0:
            k +=1
        self.d = ((k*phiN)+1) / e
        
        d = int(((k*phiN)+1) / e)

    def encrypt(self, message, keyE, keyN):
      #  print(str(self.e) + " ")
        list1 = []

        for i in message:
            insertCharacter = ord(i)
            list1.append(pow(insertCharacter, int(keyE), int(keyN)))
        return list1

    def decrypt(self, list1):
        returnString = ""
        for character in list1:
            inputValue = int(character)
            value = pow(inputValue, int(self.d), int(self.n))
            returnString += chr(value)
        
        
        return returnString

    def getAll(self):
        print("P: ", end=" ")
        print(self.p)
        print("Q: ", end=" ")
        print(self.q)
        print("N: ", end=" ")
        print(self.n)
        print("phiN: ", end=" ")
        print(self.phiN)
        print("D: ", end=" ")
        print(self.d)
        print("E: ", end=" ")
        print(self.e)

if __name__ == "__main__":
    atlas = encryptionObject()
    keepLoop = True
    while keepLoop == True:
       print(" ")
       print(" ")
       print("*****WELCOME TO THE ENCRYPTION MODULE*****")
       print("1. ENCRYPT A MESSAGE")
       print("2. DECRYPT A MESSAGE")
       print("3. VIEW VALUES")
       print("4. CHANGE PRIVATE KEY")
       inputVal = input("ENTER: ")
       if inputVal == '1':
             #encrypt a message to send to someone
             print("Values of your encryption key: ")
             atlas.getAll()
             keyE = input("Please enter in public key value for E: ")
             keyN = input("Please enter in public key value for N: ")
             message = input("enter in your message: ")
             encryptedList = atlas.encrypt(message, keyE, keyN)
             print("ENCRYPTED MESSAGE: ", end ="")
             for character in encryptedList:
                 print(character, end=" ")
             print(" ")
       if inputVal == '2':
             #decrypt a message
             encryptedString = input("enter in your list of numbers to decrypt as a space seperated list: ")
             encryptedList = encryptedString.split (" ")
             print("Decrypted message: ", end="")
             print(atlas.decrypt(encryptedList))
       if inputVal == '3':
           atlas.getAll()
           # get all values for object
       if inputVal == '4':
           atlas = encryptionObject()
           # change p & q and change class calculations
       continueLoop = input("Would you like to continue decrypting or encrypting?(Y/N): ")
      
       if continueLoop == "n" or continueLoop == "N":
           keepLoop = False
       elif continueLoop == "y" or continueLoop =="Y":
           keepLoop = True
           



    