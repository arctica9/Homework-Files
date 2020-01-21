import cv2, numpy as np
import os
import matplotlib.pyplot as plt
from moviepy.editor import ImageSequenceClip


def histogram(img):
    height = img.shape[0]
    width = img.shape[1]
    hist = np.zeros((256))
    for i in np.arange(height):
        for j in np.arange(width):
            a = img.item(i,j)
            hist[a] += 1
    return hist


def cum_histogram(hist):
    cum_hist = hist.copy()
    for i in np.arange(1,256):
        cum_hist[i] = cum_hist[i-1] + cum_hist[i]
    return cum_hist


def create_lut(cum_hist, cum_ref_hist):
    LUT = np.zeros((256))
    
    for a in np.arange(256):
        j = 255
        while True:
            LUT[a] = j
            j=j-1
            if j<0 or cum_hist[a]>cum_ref_hist[j]:
                break
    return LUT


jpeg_path, jpeg_dirs, jpeg_files = next(os.walk("C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/walking"))

img = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/walking/00000.jpg')
height, width = img.shape[:2]

red_avg_hist = np.zeros((256))
green_avg_hist = np.zeros((256))
blue_avg_hist = np.zeros((256))

total_img_num = len(jpeg_files)

for i in range(total_img_num):
    print(i)
    img = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/walking/'+jpeg_files[i])
    red = img[:,:,2]
    green = img [:,:,1]
    blue = img[:,:,0]     
    red_avg_hist = red_avg_hist + histogram(red)
    green_avg_hist = green_avg_hist + histogram(green)
    blue_avg_hist = blue_avg_hist + histogram(blue)

red_avg_hist = red_avg_hist / total_img_num
green_avg_hist = green_avg_hist / total_img_num
blue_avg_hist = blue_avg_hist / total_img_num

prob_cum_rah = cum_histogram(red_avg_hist) /(height*width)
prob_cum_gah = cum_histogram(green_avg_hist)/(height*width)
prob_cum_bah = cum_histogram(blue_avg_hist)/(height*width)

target= cv2.imread('C:/Users/DBM/Desktop/vision hw1-part2/Lime-Green-Background.jpg')

target_r = target[:,:,2]
target_g = target [:,:,1]
target_b = target[:,:,0]

target_size = target_r.shape[0]*target_r.shape[1]
 
target_red_hist = histogram(target_r)
target_green_hist = histogram(target_g)
target_blue_hist = histogram(target_b)

prob_cum_target_r = cum_histogram(target_red_hist)/target_size
prob_cum_target_g = cum_histogram(target_green_hist)/target_size
prob_cum_target_b = cum_histogram(target_blue_hist)/target_size

LUT_r = create_lut(prob_cum_rah,prob_cum_target_r)
LUT_g = create_lut(prob_cum_gah,prob_cum_target_g)
LUT_b = create_lut(prob_cum_bah,prob_cum_target_b)

images_list = []

for i in range(total_img_num):
    print(i)
    img = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/walking/'+jpeg_files[i])
    red = img[:,:,2]
    green = img [:,:,1]
    blue = img[:,:,0] 
    new_image = np.zeros((height,width,3),dtype = "uint8")
    for i in np.arange(height):
        for j in np.arange(width):
            r = red.item(i,j)
            g = green.item(i,j)
            b = blue.item(i,j)
            r_new = LUT_r[r]
            g_new = LUT_g[g]
            b_new = LUT_b[b]
            new_image[:,:,2].itemset((i,j),r_new)
            new_image[:,:,1].itemset((i,j),g_new)
            new_image[:,:,0].itemset((i,j),b_new)
    new_image = cv2.cvtColor(new_image, cv2.COLOR_BGR2RGB)
    images_list.append(new_image)
    
clip = ImageSequenceClip(images_list, fps=25)
clip.write_videofile('C:/Users/DBM/Desktop/vision hw1-part2/part2_video1.mp4', codec= 'mpeg4')