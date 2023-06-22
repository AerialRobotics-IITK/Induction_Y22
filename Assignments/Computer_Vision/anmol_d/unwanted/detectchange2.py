import cv2
import os
import numpy as np


cap = cv2.VideoCapture(0)  

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

#if not cap.isOpened():
    #print("Error opening webcam")
    #exit()

#print("Clear Area for a reference background image and press s")

exposure_set = False

# while True:
    
#     exposure_value = cap.get(cv2.CAP_PROP_EXPOSURE)
#     cap.set(cv2.CAP_PROP_EXPOSURE, exposure_value)
#     exposure_set = True
    
#     ret, frame = cap.read()
#     cv2.imshow('Original Frame', frame)
#     if cv2.waitKey(1) & 0xFF == ord('s'):
#         cv2.imwrite('background.jpg', frame)
#         break


# grayim = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
# blurim = cv2.GaussianBlur(grayim, (25,25), sigmaX=34,sigmaY=34)
# w = blurim.shape[0]
# h = blurim.shape[1]

temp = np.full((480, 640), 0, dtype=np.uint8)

while True:
   
    ret, frame = cap.read()

    
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (25,25), sigmaX=34,sigmaY=34)
    
    ret, frame1 = cap.read()

    gray1 = cv2.cvtColor(frame1, cv2.COLOR_BGR2GRAY)
    blur1 = cv2.GaussianBlur(gray1, (25,25), sigmaX=34,sigmaY=34)

   
    #edges = cv2.Canny(blur, 30, 50)
    sub = cv2.absdiff(blur,blur1)
    th,diff = cv2.threshold(sub,5,200,cv2.THRESH_BINARY)
    # diff2 = cv2.erode(diff,(3,3),iterations=0)
    # diff = cv2.dilate(diff2,(3,3),iterations=0)
    # diff2 = cv2.dilate(diff,(3,3),iterations=0)
    # diff = cv2.erode(diff2,(3,3),iterations=0)
    foreground_area = np.sum(diff)/255
    
    if foreground_area<5:
        diff = temp

    masked_frame=cv2.bitwise_and(frame,frame,mask=diff)
    temp = diff   
    
    


    cv2.imshow('Original Frame', frame)
    #cv2.imshow('Canny Edges', edges)
    cv2.imshow('Processed', diff)
    cv2.imshow('masked off', masked_frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()
