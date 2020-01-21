import cv2
import numpy as np
import pyautogui
import time

time.sleep(5)

myScreenshot = pyautogui.screenshot()

## some conversion operations from pyautogui SS
mySs = np.array(myScreenshot)
mySs = mySs[:,:,::-1].copy()
mySs = cv2.cvtColor(mySs, cv2.COLOR_BGR2GRAY)

average = np.average(mySs)
min_threshold = 0.66*average
max_threshold = 1.33*average

edges = cv2.Canny(mySs, min_threshold, max_threshold)

cv2.imwrite("cannyResult.png", edges)

