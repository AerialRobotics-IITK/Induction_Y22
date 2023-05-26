
import matplotlib
matplotlib.use('TkAgg')  # Set the backend before importing pyplot

import matplotlib.pyplot as plt
import cv2 as cv
import numpy as np
import time
import keyboard

def grayscale(image):
    
    gray=np.dot(image[..., :3], [0.2989, 0.587, 0.114])
    
    return gray(np.uint8)

def create_gaussian_kernel( ker, sigma):
    oneD=np.linspace(-(ker//2), ker//2, ker)
    oneD=np.exp(-0.5 * (oneD/sigma)** 2)
    oneD/= np.sum(oneD)
    
    kernel=np.outer(oneD,oneD)
    return kernel


def gaussian(image, ker=3, sigma=1.0):
    kernel=create_gaussian_kernel( ker, sigma)
    c=ker//2
    paddedImg=np.pad(image, ((c,c), (c,c), (0,0) ), mode='edge')
    
    blurredImg= np.zeroes_like(image, dtype=np.float32)
    
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            for k in range(image.shape[2]):
                patch = paddedImg[i:i+ker, j:j+ker, k]
                blurredImg[i, j, k] = np.sum(patch * kernel)
                
    blurredImg= blurredImg.astype(np.uint8)
    
    return blurredImg
    
    
    

def canny_edge(frame):
    
    imgGray=cv.cvtColor( frame, cv.COLOR_BGR2GRAY)
    
    imgBlur=cv.GaussianBlur(imgGray, (7,7), 0)
    
    imgCanny=cv.Canny(imgBlur, 30, 100)
    
    return imgCanny

def opening(image, kernel):
    
    _, binary=cv.threshold(image, 127, 255, cv.THRESH_BINARY)
    ker= np.ones(kernel, np.uint8)
    opened=cv.morphologyEx(binary, cv.MORPH_OPEN, ker)
    return opened

def closing(image, kernel):
    
    _, binary = cv.threshold(image, 127, 255, cv.THRESH_BINARY)
    ker = np.ones(kernel, np.uint8)
    closed = cv.morphologyEx(binary, cv.MORPH_CLOSE, ker)
    return closed

def Centroid_detection(image):
    
   
    blur=cv.GaussianBlur(image, (5,5), 0)
    
    _, threshold=cv.threshold(blur, 127, 255, 0)
    
    # Find contours in the binary image
    contours, _ = cv.findContours(threshold, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
    

    
    for contour in contours:
        M = cv.moments(contour)
        if M["m00"] != 0:
            cX = int(M["m10"] / M["m00"])
            cY = int(M["m01"] / M["m00"])
            cv.circle(image, (cX, cY), 5, (255, 255, 255), -1)
            
            
def fix_image_channels(frame):

    
    if len(frame.shape) == 3:
        num_channels = frame.shape[2]
    else:
        num_channels = 1

    if num_channels == 1:
        frame = cv.cvtColor(frame, cv.COLOR_GRAY2RGB)

    return frame

cap = cv.VideoCapture(0) 


if not cap.isOpened():
    print("Unable to open the camera.")
    
# Warm up the camera by reading frames for a short period
warmup_duration = 2  
start_time = time.time()
while time.time() - start_time < warmup_duration:
    ret, frame = cap.read()
    if not ret:
        print("Failed to read frame during warm-up.")
        exit()
    

ret, fra= cap.read()

if (ret==False):
    print("Frame capturing failed")
    exit()
    
first_frame = fix_image_channels(fra)

gray_first_frame= cv.cvtColor( first_frame, cv.COLOR_BGR2GRAY)

gauss_first_frame=cv.GaussianBlur(gray_first_frame, (5,5), 0)

_, thresh_first_frame=cv.threshold(gray_first_frame, 0, 255, cv.THRESH_BINARY)

time.sleep(1)

while True:
    
    ret, frame = cap.read()   

    if (ret==True):
        
        frame = fix_image_channels(frame)

        
        grayFrame=cv.cvtColor( frame, cv.COLOR_BGR2GRAY)
        
        gaussFrame=cv.GaussianBlur( grayFrame, (5,5), 0)
        
        
        #absolute difference of current frame and median frame
        dframe=cv.absdiff(gauss_first_frame,gaussFrame)
        
        cv.imshow('Camera', dframe)
        
        _,thresh= cv.threshold(dframe, 127 , 255, cv.THRESH_BINARY)
        cv.imshow('Camera', dframe)
        
        open=opening(thresh, (5,5))
        close=closing(thresh, (5,5))
        
        foreground_pixels= np.count_nonzero(thresh_first_frame==255)

        removed=first_frame.copy()
        removed[thresh_first_frame==0]=0
        
        color=cv.bitwise_and( frame, frame, mask=close)
        
        Centroid_detection(close)
        
        

        plt.figure(figsize=(10, 6))
        plt.subplot(2, 2, 1), plt.imshow(cv.cvtColor(frame, cv.COLOR_BGR2RGB)), plt.title('Original Frame')
        plt.subplot(2, 2, 2), plt.imshow(close, cmap='gray'), plt.title('Preprocessed')
        plt.subplot(2, 2, 3), plt.imshow(cv.cvtColor(color, cv.COLOR_BGR2RGB)), plt.title('Processed')
        
        plt.show()
        
        

    # Break the loop when 'q' key is pressed
    if keyboard.is_pressed('q'):
        break

cap.release()
cv.destroyAllWindows()

plt.close('all')


    

    
    
    
    
    

