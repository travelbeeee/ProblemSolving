def isVowel(c):
    if(c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u') :
        return True
    return False

def backtracking(startInd, len):
    global L
    global C
    global cipher
    if(len == L):
        vowel = 0
        consonant = 0
        for c in cipher:
            if isVowel(c): vowel = vowel + 1
            else : consonant = consonant + 1
        if(not(1 <= vowel and 2 <= consonant)):
            return
        print(''.join(cipher))
        return

    for i in range(startInd, C):
        cipher.append(alp[i])
        backtracking(i + 1, len + 1)
        cipher.pop()
    return

numInput = input()
numInput = numInput.split()

alp = input()
alp = alp.split()
alp.sort()

L = int(numInput[0])
C = int(numInput[1])

cipher = []

backtracking(0, 0)
