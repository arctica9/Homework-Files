import cv2
import numpy as np
from statistics import mean
import pyautogui
import time

time.sleep(5)

for k in range(3):
    myScreenshot = pyautogui.screenshot()

## converting to gray cv image
    mySs = np.array(myScreenshot)
    mySs = mySs[:,:,::-1].copy()
    mySs_gray = cv2.cvtColor(mySs, cv2.COLOR_BGR2GRAY)
    average = np.average(mySs)
    min_threshold = 0.66*average
    max_threshold = 1.33*average

    canny = cv2.Canny(mySs_gray, min_threshold, max_threshold)
    quality = 0.2

    height, width = canny.shape

    centerX = round(width/2)
    centerY = round(height/2)

    
    dest = cv2.cornerMinEigenVal(canny, 3)
    minEigen, maxEigen, _, _ = cv2.minMaxLoc(dest)


    edgesX = []
    edgesY = []

    for i in range(height):
        for j in range(width):
            if  j> centerX +50 and  centerY-30> i:## with this we eliminate the points detected on creature and points on left and downside
                if dest[i,j] > minEigen + (maxEigen - minEigen)*quality:
                    edgesX.append(j)
                    edgesY.append(i)
                    cv2.circle(mySs, (j,i), 8, (0,255,0), -1)

    cv2.imwrite("ss"+str(k)+".png", mySs) ## saving each screenshot with detected points

    
    print(abs(round(mean(edgesX)) - centerX),abs(round(mean(edgesY)) - centerY))
    if abs(round(mean(edgesX)) - centerX) > abs(round(mean(edgesY)) - centerY): 
        
        pyautogui.keyDown('shift')
        pyautogui.keyDown('d')
        time.sleep(2)
        pyautogui.keyUp('d')
        pyautogui.keyUp('shift')

    else: 
        pyautogui.keyDown('shift')
        pyautogui.keyDown('w')
        time.sleep(4)
        pyautogui.keyUp('w')
        pyautogui.keyUp('shift')

    