import cv2, numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import os
from moviepy.editor import ImageSequenceClip

jpeg_path, jpeg_dirs, jpeg_files = next(os.walk("C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/night-race"))

images_list = []

for i in range(len(jpeg_files)):
    img = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/night-race/'+jpeg_files[i])
    seg = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/Annotations/night-race/'+ jpeg_files[i].split('.')[0]+'.png',cv2.IMREAD_GRAYSCALE )
   
    height, width = img.shape[:2]
    seg = (seg == 38)
    image_of_the_guy = np.zeros((height,width,3), np.uint8)#create template
    image_without_the_guy = np.zeros((height,width,3), np.uint8)#create template


    image_of_the_guy[:,:,1] = seg*img[:,:,1]#only red color channel is needed
    
    image_without_the_guy[:,:,0] = np.logical_xor(seg, True)*img[:,:,0]
    image_without_the_guy[:,:,1] = np.logical_xor(seg, True)*img[:,:,1]
    image_without_the_guy[:,:,2] = np.logical_xor(seg, True)*img[:,:,2]
 
    
    image = image_of_the_guy + image_without_the_guy
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    #os.chdir(r'C:\Users\DBM\Desktop\results')    
    #cv2.imwrite(jpeg_files[i].split('.')[0]+'.png', image)
    images_list.append(image)

clip = ImageSequenceClip(images_list, fps=25)
clip.write_videofile('part1_video3.mp4', codec= 'mpeg4')