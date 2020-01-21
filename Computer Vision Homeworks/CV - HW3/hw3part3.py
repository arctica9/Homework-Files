import cv2 
import numpy as np


def shiThomasi(ss, quality):
    gray_ss = cv2.cvtColor(ss,cv2.COLOR_BGR2GRAY)

    height, width = gray_ss.shape

    ## calculates eigen values, then finds the max. and min. ones
    dest = cv2.cornerMinEigenVal(gray_ss, 3)
    minEigen, maxEigen, _, _ = cv2.minMaxLoc(dest)


    for i in range(height):
        for j in range(width):
            if dest[i,j] > minEigen + (maxEigen - minEigen)*quality:
                cv2.circle(ss, (j,i), 2, (0,255,0),2)

quality = 0.182

ss = cv2.imread('test.png')
shiThomasi(ss, quality)
cv2.imwrite('shiThomasiResult.png', ss)