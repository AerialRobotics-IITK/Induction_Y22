import cv2
import os
import numpy as np


cap = cv2.VideoCapture(0)  

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

if not cap.isOpened():
    print("Error opening webcam")
    exit()

print("Clear Area for a reference background image and press s")

exposure_set = False

while True:
    
    cap.set(cv2.CAP_PROP_AUTO_EXPOSURE, 1)
    exposure_value = cap.get(cv2.CAP_PROP_EXPOSURE)
    cap.set(cv2.CAP_PROP_EXPOSURE, exposure_value)
    exposure_set = True
    cap.set(cv2.CAP_PROP_AUTO_EXPOSURE, 0)
    
    ret, frame = cap.read()
    cv2.imshow('Original Frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('s'):
        cv2.imwrite('background.jpg', frame)
        break



grayim = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
blurim = cv2.GaussianBlur(grayim, (15,15), sigmaX=70,sigmaY=70)
w = blurim.shape[0]
h = blurim.shape[1]
while True:
   
    ret, frame = cap.read()

    
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (15,15), sigmaX=70,sigmaY=70)
   
    edges = cv2.Canny(blur, 30, 50)
    sub = cv2.absdiff(blur,blurim)
    #diff = cv2.adaptiveThreshold(sub, 205, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 311, 1)
    th,diff = cv2.threshold(sub,15,255,cv2.THRESH_BINARY)
    diff2 = cv2.erode(diff,(3,3),iterations=1)
    diff = cv2.dilate(diff2,(3,3),iterations=1)
    diff2 = cv2.dilate(diff,(3,3),iterations=1)
    diff = cv2.erode(diff2,(3,3),iterations=1)
    masked_frame=cv2.bitwise_and(frame,frame,mask=diff)
               

    cv2.imshow('Original Frame', frame)
    cv2.imshow('Canny Edges', edges)
    cv2.imshow('Processed', diff2)
    cv2.imshow('masked off', masked_frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()
