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

blue= cv2.imread('C:/Users/DBM/Desktop/vision-hw1part3/blue.jpg')
orange= cv2.imread('C:/Users/DBM/Desktop/vision-hw1part3/pink.jpg')

jpeg_path, jpeg_dirs, jpeg_files = next(os.walk("C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/blackswan"))

total_img_num = len(jpeg_files)

hist_duck_r = np.zeros((256))
hist_duck_g = np.zeros((256))
hist_duck_b = np.zeros((256))

hist_img_of_back_r = np.zeros((256))
hist_img_of_back_g = np.zeros((256))
hist_img_of_back_b = np.zeros((256))

for i in range(total_img_num):
    #duck processes starts here
    img = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/blackswan/'+jpeg_files[i])
    seg = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/Annotations/blackswan/'+ jpeg_files[i].split('.')[0]+'.png',cv2.IMREAD_GRAYSCALE )
    height, width = img.shape[:2]
    seg = (seg==38)
    anti_seg = np.logical_xor(seg, True)
    
    img_of_duck_r = img[:,:,2]*seg
    img_of_duck_g = img[:,:,1]*seg
    img_of_duck_b = img[:,:,0]*seg
    
    duck_height = img_of_duck_r.shape[0]
    duck_width = img_of_duck_r.shape[1]
    
    hist_duck_r = hist_duck_r + histogram(img_of_duck_r)
    hist_duck_g = hist_duck_g + histogram(img_of_duck_g)
    hist_duck_b = hist_duck_b + histogram(img_of_duck_b)
    
   
    
    #background processes starts here

    img_of_back_r = img[:,:,2]*anti_seg
    img_of_back_g = img[:,:,1]*anti_seg
    img_of_back_b = img[:,:,0]*anti_seg
    
    back_height= img_of_back_r.shape[0]
    back_width = img_of_back_r.shape[1]
    
    hist_img_of_back_r = hist_img_of_back_r + histogram(img_of_back_r)
    hist_img_of_back_g = hist_img_of_back_g + histogram(img_of_back_g)
    hist_img_of_back_b = hist_img_of_back_b + histogram(img_of_back_b)

hist_duck_r = hist_duck_r/total_img_num
hist_duck_g = hist_duck_g/total_img_num
hist_duck_b = hist_duck_b/total_img_num
    
hist_img_of_back_r = hist_img_of_back_r/total_img_num
hist_img_of_back_g = hist_img_of_back_g/total_img_num
hist_img_of_back_b = hist_img_of_back_b/total_img_num

cum_hist_duck_r = cum_histogram(hist_duck_r)
cum_hist_duck_g = cum_histogram(hist_duck_g)
cum_hist_duck_b = cum_histogram(hist_duck_b)
    
prob_chd_r = cum_hist_duck_r/ (duck_height*duck_width)
prob_chd_g = cum_hist_duck_g/ (duck_height*duck_width)
prob_chd_b = cum_hist_duck_b/ (duck_height*duck_width)

cum_hiob_r = cum_histogram(hist_img_of_back_r)
cum_hiob_g = cum_histogram(hist_img_of_back_g)
cum_hiob_b = cum_histogram(hist_img_of_back_b)
    
prob_chiob_r = cum_hiob_r / (back_height*back_width)
prob_chiob_g = cum_hiob_g / (back_height*back_width)
prob_chiob_b = cum_hiob_b / (back_height*back_width)

##blue image processes for duck's his togram matching starts here

blue_r = blue[:,:,2]
blue_g = blue[:,:,1]
blue_b = blue[:,:,0]

hist_blue_r = histogram(blue_r)
hist_blue_g = histogram(blue_g)
hist_blue_b = histogram(blue_b)

cum_hist_blue_r = cum_histogram(hist_blue_r)
cum_hist_blue_g = cum_histogram(hist_blue_g)
cum_hist_blue_b = cum_histogram(hist_blue_b)

prob_chb_r = cum_hist_blue_r /(blue_r.shape[0]*blue_r.shape[1])
prob_chb_g = cum_hist_blue_g /(blue_g.shape[0]*blue_g.shape[1])
prob_chb_b = cum_hist_blue_b /(blue_b.shape[0]*blue_b.shape[1])


##creating lookup table of blue duck

duck_LUT_r = create_lut(prob_chd_r,prob_chb_r)
duck_LUT_g = create_lut(prob_chd_g,prob_chb_g)
duck_LUT_b = create_lut(prob_chd_b,prob_chb_b)



#pink image processes for background's histogram matching starts here (first made orange, then changed it as pink)

orange_r = orange[:,:,2]
orange_g = orange[:,:,1]
orange_b = orange[:,:,0]

hist_orange_r = histogram(orange_r)
hist_orange_g = histogram(orange_g)
hist_orange_b = histogram(orange_b)

cum_hist_orange_r = cum_histogram(hist_orange_r)
cum_hist_orange_g = cum_histogram(hist_orange_g)
cum_hist_orange_b = cum_histogram(hist_orange_b)

prob_cho_r = cum_hist_orange_r / (orange_r.shape[0]*orange_r.shape[1])
prob_cho_g = cum_hist_orange_g / (orange_g.shape[0]*orange_g.shape[1])
prob_cho_b = cum_hist_orange_b / (orange_b.shape[0]*orange_b.shape[1])

#creating lookup table of pink background

backg_LUT_r = create_lut(prob_chiob_r, prob_cho_r)
backg_LUT_g = create_lut(prob_chiob_g, prob_cho_g)
backg_LUT_b = create_lut(prob_chiob_b, prob_cho_b)

images_list = []

for i in range(total_img_num):
    print(i)
    img = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/JPEGImages/blackswan/'+jpeg_files[i])
    seg = cv2.imread('C:/Users/DBM/Desktop/DAVIS-JPEGImages/Annotations/blackswan/'+ jpeg_files[i].split('.')[0]+'.png',cv2.IMREAD_GRAYSCALE )
    height, width = img.shape[:2]
    seg = (seg==38)
    anti_seg = np.logical_xor(seg, True)

    duck_red = img[:,:,2]
    duck_green = img [:,:,1]
    duck_blue = img[:,:,0]
    back_red = img[:,:,2]
    back_green = img[:,:,1]
    back_blue = img[:,:,0]
    
    new_duck = np.zeros((height,width,3),dtype = "uint8")
    new_back = np.zeros((height,width,3),dtype = "uint8")

    for i in np.arange(height):
        for j in np.arange(width):
            
            d_r = duck_red.item(i,j)
            d_g = duck_green.item(i,j)
            d_b = duck_blue.item(i,j)
            
            b_r = back_red.item(i,j)
            b_g = back_green.item(i,j)
            b_b = back_blue.item(i,j)
            
            dr_new = duck_LUT_r[d_r]
            dg_new = duck_LUT_g[d_g]
            db_new = duck_LUT_b[d_b]
            
            br_new = backg_LUT_r[b_r]
            bg_new = backg_LUT_g[b_g]
            bb_new = backg_LUT_b[b_b]
            
            new_duck[:,:,2].itemset((i,j),dr_new)
            new_duck[:,:,1].itemset((i,j),dg_new)
            new_duck[:,:,0].itemset((i,j),db_new)
            
            new_back[:,:,2].itemset((i,j),br_new)
            new_back[:,:,1].itemset((i,j),bg_new)
            new_back[:,:,0].itemset((i,j),bb_new)
    
    new_duck[:,:,2]= new_duck[:,:,2]*seg
    new_duck[:,:,1]= new_duck[:,:,1]*seg
    new_duck[:,:,0]= new_duck[:,:,0]*seg
    
    new_back[:,:,2]= new_back[:,:,2]*anti_seg
    new_back[:,:,1]= new_back[:,:,1]*anti_seg
    new_back[:,:,0]= new_back[:,:,0]*anti_seg
        
    image = new_duck + new_back
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    images_list.append(image)

clip = ImageSequenceClip(images_list, fps=25)
clip.write_videofile('C:/Users/DBM/Desktop/vision-hw1part3/part3_video1.mp4', codec= 'mpeg4')
