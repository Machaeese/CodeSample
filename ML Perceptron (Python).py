import numpy as np

def getData(data):
    return data[:,0:819]

def getLabel(data):
    return data[:,819]


def get12(data, label):
    data12 = []
    label12 = []
    for x in range(len(data)):
        if label[x] == 1:
            data12.append(data[x])
            label12.append(-1)
        if label[x] == 2:
            data12.append(data[x])
            label12.append(1)
    return data12, label12

######### Regular Perceptron ############
def regularPerceptron(data, label, wm):
    for t in range(len(data)):
        if label[t]*(np.dot(wm, data[t])) <= 0:
            wm = wm + data[t]*label[t]
    return wm


def errorTestingRegular(trainData, trainLabel, testData, testLabel, n):
    error = 0
    wm = [0] * 819
    for x in range(n):
        wm = regularPerceptron(trainData, trainLabel, wm)
    for i in range(len(testData)):
        signed = np.sign(np.dot(testData[i], wm))
        if signed == 0:
            signed = -1
        if not signed == testLabel[i]:
            error += 1
    return error/len(testData)




############# Voted Perceptron ############
def votedPerceptron(data, label, wm, cm, ws, cms):
    for t in range(len(data)):
        if label[t] * (np.dot(wm, data[t])) <= 0:
            ws.append(wm)
            cms.append(cm)
            wm = wm + data[t] * label[t]
            cm = 1
        else:
            cm += 1
    return ws, cms, wm, cm


def errorTestingVoted(trainData, trainLabel, testData, testLabel, n):
    error = 0
    wm = [0] * 819
    cm = 1
    ws = []
    cms = []
    for x in range(n):
        ws, cms, wm, cm = votedPerceptron(trainData, trainLabel, wm, cm, ws, cms)
    for i in range(len(testData)):
        sum = 0
        for j in range(len(ws)):
            if np.dot(ws[j], testData[i]) == 0:
                sum += 0
            else:
                sum += np.sign(np.dot(ws[j], testData[i])) * cms[j]
        signed = np.sign(sum)
        if signed == 0:
            signed = -1
        if not signed == testLabel[i]:
            error += 1
    return error/len(testData)



######### Average Perceptron ############
def averagePerceptron(data, label, wm, cm, average):
    sum = average
    for t in range(len(data)):
        if label[t] * (np.dot(wm, data[t])) <= 0:
            mult = []
            result = []
            for i in range(819):
                mult.append(wm[i] * cm)
                result.append(mult[i] + sum[i])
            sum = result
            wm = wm + data[t] * label[t]
            cm = 1
        else:
            cm += 1
    return sum, wm, cm


def errorTestingAverage(trainData, trainLabel, testData, testLabel, n):
    error = 0
    wm = [0] * 819
    cm = 1
    average = [0] * 819
    for x in range(n):
        average, wm, cm = averagePerceptron(trainData, trainLabel, wm, cm, average)
    for i in range(len(testData)):
        if np.dot(average, testData[i]) == 0:
            result = 0
        else:
            result = np.sign(np.dot(average, testData[i]))
        signed = np.sign(result)
        if signed == 0:
            signed = -1
        if not signed == testLabel[i]:
            error += 1
    return error/len(testData)


def getILabel(label, i):
    labelI = []
    for x in range(len(label)):
        if label[x] == i:
            labelI.append(1)
        else:
            labelI.append(-1)
    return labelI

def getNumOfLabels(data, label):
    numOfLabels = [0] * 6
    label1s = []
    label2s = []
    label3s = []
    label4s = []
    label5s = []
    label6s = []
    for x in range(len(label)):
        if label[x] == 1:
            label1s.append(data[x])
            numOfLabels[0] += 1
        if label[x] == 2:
            label2s.append(data[x])
            numOfLabels[1] += 1
        if label[x] == 3:
            label3s.append(data[x])
            numOfLabels[2] += 1
        if label[x] == 4:
            label4s.append(data[x])
            numOfLabels[3] += 1
        if label[x] == 5:
            label5s.append(data[x])
            numOfLabels[4] += 1
        if label[x] == 6:
            label6s.append(data[x])
            numOfLabels[5] += 1
    return numOfLabels, label1s, label2s, label3s, label4s, label5s, label6s


def prediction(cl, data):
    matrix = np.zeros((7, 6))
    for i in range(6):
        for x in range(len(data[i])):
            l = []
            for j in range(6):
                signed = np.sign(np.dot(data[i][x], cl[j]))
                if signed == 0:
                    signed = -1
                l.append(signed)
            if l.count(1) == 1:
                for k in range(6):
                    if l[k] == 1:
                        matrix[k][i] += 1
            else:
                matrix[6][i] += 1
    return matrix


def getConfusion(matrix, Nj):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            matrix[i][j] /= Nj[j]
    return matrix



if __name__ == '__main__':
    #get data and label from training data
    trainInput = np.loadtxt("pa3train.txt") ##3000
    trainData = getData(trainInput)
    trainLabel = getLabel(trainInput)
    #get data and label from test data
    testInput = np.loadtxt("pa3test.txt")   ##1000
    testData = getData(testInput)
    testLabel = getLabel(testInput)
    #get data from dictionary ##819
    file = open('pa3dictionary.txt', 'r')
    dictionary = file.readlines()

################################Question 1######################################
    '''
    dtrain, ltrain = get12(trainData, trainLabel)
    dtest, ltest = get12(testData, testLabel)

    
    print("Training Error of Perceptron")
    print(errorTestingRegular(dtrain, ltrain, dtrain, ltrain, 1))
    print(errorTestingRegular(dtrain, ltrain, dtrain, ltrain, 2))
    print(errorTestingRegular(dtrain, ltrain, dtrain, ltrain, 3))
    print(errorTestingRegular(dtrain, ltrain, dtrain, ltrain, 4))
    
    print("Training Error of Voted Perceptron")
    print(errorTestingVoted(dtrain, ltrain, dtrain, ltrain, 1))
    print(errorTestingVoted(dtrain, ltrain, dtrain, ltrain, 2))
    print(errorTestingVoted(dtrain, ltrain, dtrain, ltrain, 3))
    print(errorTestingVoted(dtrain, ltrain, dtrain, ltrain, 4))
    
    print("Training Error of Average Perceptron")
    print(errorTestingAverage(dtrain, ltrain, dtrain, ltrain, 1))
    print(errorTestingAverage(dtrain, ltrain, dtrain, ltrain, 2))
    print(errorTestingAverage(dtrain, ltrain, dtrain, ltrain, 3))
    print(errorTestingAverage(dtrain, ltrain, dtrain, ltrain, 4))
    
    print("Testing Error of Perceptron")
    print(errorTestingRegular(dtrain, ltrain, dtest, ltest, 1))
    print(errorTestingRegular(dtrain, ltrain, dtest, ltest, 2))
    print(errorTestingRegular(dtrain, ltrain, dtest, ltest, 3))
    print(errorTestingRegular(dtrain, ltrain, dtest, ltest, 4))
    
    print("Testing Error of Voted Perceptron")
    print(errorTestingVoted(dtrain, ltrain, dtest, ltest, 1))
    print(errorTestingVoted(dtrain, ltrain, dtest, ltest, 2))
    print(errorTestingVoted(dtrain, ltrain, dtest, ltest, 3))
    print(errorTestingVoted(dtrain, ltrain, dtest, ltest, 4))
    
    print("Testing Error of Average Perceptron")
    print(errorTestingAverage(dtrain, ltrain, dtest, ltest, 1))
    print(errorTestingAverage(dtrain, ltrain, dtest, ltest, 2))
    print(errorTestingAverage(dtrain, ltrain, dtest, ltest, 3))
    print(errorTestingAverage(dtrain, ltrain, dtest, ltest, 4))
    

################################Question 2######################################

    
    dtrain, ltrain = get12(trainData, trainLabel)
    wm = [0] * 819
    cm = 1
    average = [0] * 819
    average, wm, cm = averagePerceptron(dtrain, ltrain, wm, cm, average)
    average, wm, cm = averagePerceptron(dtrain, ltrain, wm, cm, average)
    average, wm, cm = averagePerceptron(dtrain, ltrain, wm, cm, average)
    sorted = np.argsort(average)
    print(sorted[0], sorted[1], sorted[2])
    print(dictionary[sorted[0]], dictionary[sorted[1]], dictionary[sorted[2]])
    print(sorted[-1], sorted[-2], sorted[-3])
    print(dictionary[sorted[-1]], dictionary[sorted[-2]], dictionary[sorted[-3]])
    

################################Question 3######################################
    
    wm = [0] * 819
    c1 = regularPerceptron(trainData, getILabel(trainLabel, 1), wm)
    c2 = regularPerceptron(trainData, getILabel(trainLabel, 2), wm)
    c3 = regularPerceptron(trainData, getILabel(trainLabel, 3), wm)
    c4 = regularPerceptron(trainData, getILabel(trainLabel, 4), wm)
    c5 = regularPerceptron(trainData, getILabel(trainLabel, 5), wm)
    c6 = regularPerceptron(trainData, getILabel(trainLabel, 6), wm)
    cl = [c1, c2, c3, c4, c5, c6]

    Nj, dataW1, dataW2, dataW3, dataW4, dataW5, dataW6 = getNumOfLabels(testData,testLabel)
    data = [dataW1, dataW2, dataW3, dataW4, dataW5, dataW6]
    matrix = prediction(cl, data)
    print(matrix)
    print(getConfusion(matrix, Nj))
    '''






