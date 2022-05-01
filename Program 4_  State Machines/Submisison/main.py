#CS330 Assignment 4 State Machines by Julio Rivera and Juan Tarrat

from random import random as rand
from turtle import done

#Initialize State Machine
transitions = [(0.8,0.9), (0.4,0.6), (0.3,0.3), (0.4,0.2),
                (0.3,0.2), (0.3,0.4), (0.8,0.7), (0.8,0.9), (0.8,0.7)]

transitionCount = [0] * len(transitions)
stateCount = [0] * 7

FOLLOW = 1
PULL_OUT = 2
ACCELERATE = 3
PULL_IN_AHEAD = 4
PULL_IN_BEHIND = 5
DECELERATE = 6
DONE = 7

def printList(list):
    res = ""
    for i in range(len(list)):
        res += str(list[i]) + " "
    return res

def followAction(file):
    file.write("state= 1 Follow\n")
    stateCount[FOLLOW - 1] += 1

def pullOutAction(file):
    file.write("state= 2 Pull Out\n")
    stateCount[PULL_OUT - 1] += 1

def accelerateAction(file):
    file.write("state= 3 Accelerate\n")
    stateCount[ACCELERATE - 1] += 1

def pullInAheadAction(file):
    file.write("state= 4 Pull In Ahead\n")
    stateCount[PULL_IN_AHEAD - 1] += 1

def pullInBehindAction(file):
    file.write("state= 5 Pull In Behind\n")
    stateCount[PULL_IN_BEHIND - 1] += 1

def decelerateAction(file):
    file.write("state= 6 Decelerate\n")
    stateCount[DECELERATE - 1] += 1

def doneAction(file):
    file.write("state= 7 Done\n\n")
    stateCount[DONE - 1] += 1

#Assignment
def stateMachinesAssignment(scenario, file, trace = True):
    iterationCount = 0
    for i in range(1, 101):
        if trace :
            file.write("iteration= " + str(i) + "\n")
            iterationCount += 1
        
        state = FOLLOW
        followAction(file)

        while(state != DONE):
            r = rand()
            
            if(state == FOLLOW):
                if(r < transitions[0][scenario - 1]):
                    state = PULL_OUT
                    transitionCount[0] += 1
                    pullOutAction(file)
                else:
                    state = FOLLOW
                    followAction(file)
            
            elif(state == PULL_OUT):
                sum1 = transitions[1][scenario - 1] + transitions[3][scenario - 1]
                if(r < transitions[1][scenario - 1]):
                    state = ACCELERATE
                    transitionCount[1] += 1
                    accelerateAction(file)
                elif(r < sum1):
                    state = PULL_IN_BEHIND
                    transitionCount[3] += 1
                    pullInBehindAction(file)
                else:
                    state = PULL_OUT
                    pullOutAction(file)
            
            elif(state == ACCELERATE):
                sum1 = transitions[2][scenario - 1] + transitions[4][scenario - 1]
                sum2 = sum1 + transitions[5][scenario - 1]
                if(r < transitions[2][scenario - 1]):
                    state = PULL_IN_AHEAD
                    transitionCount[2] += 1
                    pullInAheadAction(file)
                elif(r < sum1):
                    state = PULL_IN_BEHIND
                    transitionCount[4] += 1
                    pullInBehindAction(file)
                elif(r < sum2):
                    state = DECELERATE
                    transitionCount[5] += 1
                    decelerateAction(file)
                else:
                    state = ACCELERATE
                    accelerateAction(file)
            
            elif(state == PULL_IN_AHEAD):
                if(r < transitions[8][scenario - 1]):
                    state = DONE
                    transitionCount[8] += 1
                    doneAction(file)
                else:
                    state = PULL_IN_AHEAD
                    pullInAheadAction(file)
            
            elif(state == PULL_IN_BEHIND):
                if(r < transitions[6][scenario - 1]):
                    state = FOLLOW
                    transitionCount[6] += 1
                    followAction(file)
                else:
                    state = PULL_IN_BEHIND
                    pullInBehindAction(file)
            
            elif(state == DECELERATE):
                if(r < transitions[7][scenario - 1]):
                    state = PULL_IN_BEHIND
                    transitionCount[7] += 1
                    pullInBehindAction(file)
                else:
                    state = DECELERATE
                    decelerateAction(file)
    
    stateFreq = [0] * 7
    transitionFreq = [0] * len(transitions)
    for i in range(len(stateCount)):
        stateFreq[i] = stateCount[i] / sum(stateCount)
        stateFreq[i] = "{:.3f}".format(stateFreq[i])

    for i in range(len(transitionCount)):
        transitionFreq[i] = transitionCount[i] / sum(transitionCount)
        transitionFreq[i] = "{:.3f}".format(transitionFreq[i])

    file.write("\n\n\n\n")

    transitionProbabiliies = list()
    for i in range(len(transitions)):
        transitionProbabiliies.append(transitions[i][scenario - 1])

    #Print stats
    file.write("scenario\t\t\t\t= " + str(scenario) + "\n")
    file.write("trace\t\t\t\t\t= " + str(trace) + "\n")
    file.write("iterations\t\t\t\t= " + str(iterationCount)+ "\n")
    file.write("transition probabilities= " + printList(transitionProbabiliies)+ "\n")
    file.write("state counts\t\t\t= " + printList(stateCount) + "\n")
    file.write("state frequencies\t\t= " + printList(stateFreq) + "\n")
    file.write("transition counts\t\t= " + printList(transitionCount) + "\n")
    file.write("transition frequencies\t= " + printList(transitionFreq) + "\n")


#main function
if __name__ == "__main__":
    file = open("State machines scenario 1.txt", 'w')
    file.write("CS330 Assignment 4 State Machines Juan Tarrat and Julio Rivera\n\n")
    stateMachinesAssignment(1, file)

    file = open("State machines scenario 2.txt", 'w')
    file.write("CS330 Assignment 4 State Machines Juan Tarrat and Julio Rivera\n\n")
    stateMachinesAssignment(2, file)









