#!/usr/bin/python3
# vim: ts=4:sw=4: et :

##############################
## Author  : @PrakashGautam ##
## Written : Dec 15,2015    ##
## Updated : Dec 15, 2015   ##
##############################


# This is my First dive into python. For  the sake of learnig  python  I
# just converted my already existing C++ code  into python. This  surely
# not the best way to do this as it surely isn't pythonic. But this  has
# helped me dive into python as I learned clearly there is nothing  like 
# pass by value in python.




import bisect
import copy

class HoffEncode:
    def __init__(self,ProbList):
        self.ProbList= ProbList
        self.Done = self.IterateCode(self.ProbList)
    
    
    def IterateCode(self,Codes):
        """        
        This is a recursive implementation of Huffman Algorithm. We reiterate
        the process up until  an array  with  just  two probabilities is left.
        When we are  left  with just two, we (arbitrarily) assign the symbols
        '0'  and  '1'  to the  last tow of them. When there are more than two
        add  the last two, and push it up(?) the order in rank and remove the
        last two,  and  find code for  that new array. When the code for that
        reduced array is  found, we  find the code  for the added probability
        from highest,  (Huffman algorithm  gives least  variance with the sum
        pushed  highest up the order),  attach  it to the individual ones and
        """
        Rem = len(Codes)
        RetVec = Codes
        LastTwoSum = Codes[0]['p'] + Codes[1]['p']
        '''Assign symbols '0' and '1' to the last two'''
        RetVec[0]['c'] = '1'
        RetVec[1]['c'] = '0'
        '''If only tow are left, check if the sum gives probability 1, and leave'''
        if Rem == 2:
            return RetVec
        else:
            TrimmedCode = self.TrimCodes(Codes)
            RedCodes = self.IterateCode(TrimmedCode)
            RedSize = len(RedCodes)
            FoundRed = [False for Element in RedCodes]
            FoundOrg = [False for Element in Codes]
            FoundSum = False
            '''
            For the last two elements in the unreduced array, attach the code
            of the sum of them in the reduced array. Search from the sum from
            the top because it will give the least variance codes for symbols
            '''
            for j,RedElem in reversed(list(enumerate(RedCodes))):
                if LastTwoSum == RedElem['p'] and (not FoundSum) and (not FoundRed[j]) :
                    RetVec[0]['c'] = RedCodes[j]['c'] + RetVec[0]['c']
                    RetVec[1]['c'] = RedCodes[j]['c'] + RetVec[1]['c']
                    FoundRed[j] = True
                    FoundSum = True
                    break
            '''
            Once code for the sum of them is found, find code for the rest of
            them and copy codes to them. Then return
            '''
            for i in range(2,Rem):
                for j in range(RedSize):
                    if(RetVec[i]['p'] == RedCodes[j]['p'] and (not FoundRed[j] and not FoundOrg[i])):
                        RetVec[i]['c'] = RedCodes[j]['c']
                        FoundRed[j] = True
                        FoundOrg[i] = True
                        break
            
        return RetVec
        
    
    def TrimCodes(self,Codes):
        '''
        Our job in this function is to add the least (last) two probabilities
        insert the sum in the array in order (lexicographic here)  and remove
        the last two elements whose sum we calculated;
        '''
        LocCodes = copy.deepcopy(Codes)
        
        '''First find the sum of last two as the least two reside on index 0 and 1'''
        LastTwoSum = LocCodes[0]['p'] + LocCodes[1]['p']
      
        LocCodes.append({'p':LastTwoSum,'c':''})
        LocCodes = LocCodes[2:]
        LocCodes.sort(key = lambda x:x['p'])
        return LocCodes
    #end TrimCodes
        
    def Display(self):
        for Item in self.Done:
            print(Item)
    #end Display
    
#end class HoffCode

if __name__ == '__main__':

    ProbList = [
        {'p':625,'c':""},
        {'p':625,'c':""},
        {'p':625,'c':""},
        {'p':625,'c':""},
        {'p':1250,'c':''},
        {'p':1250,'c':''},
        {'p':2500,'c':""},
        {'p':2500,'c':""}
    ]
    Coder = HoffEncode(ProbList)
    Coder.Display()

