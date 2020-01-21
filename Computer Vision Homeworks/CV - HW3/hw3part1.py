import cv2
import numpy as np
import pyautogui
import time

def sobelOperator(img):
    container = np.copy(img)
    size = container.shape
    for i in range(1, size[0] - 1):
        for j in range(1, size[1] - 1):
            gx = (img[i - 1][j - 1] + 2*img[i][j - 1] + img[i + 1][j - 1]) - (img[i - 1][j + 1] + 2*img[i][j + 1] + img[i + 1][j + 1])
            gy = (img[i - 1][j - 1] + 2*img[i - 1][j] + img[i - 1][j + 1]) - (img[i + 1][j - 1] + 2*img[i + 1][j] + img[i + 1][j + 1])
            container[i][j] = min(255, np.sqrt(gx**2 + gy**2))
    return container

time.sleep(5)

myScreenshot = pyautogui.screenshot()
myScreenshot.save("test.png")

#converting to opencv image
mySs = np.array(myScreenshot)
mySs = mySs[:,:,::-1].copy()

mySs = cv2.cvtColor(mySs, cv2.COLOR_BGR2GRAY)

sobel_mySs = sobelOperator(mySs)

sobel_mySs = cv2.cvtColor(sobel_mySs,cv2.COLOR_GRAY2BGR)

cv2.imwrite("sobelResult.png",sobel_mySs)