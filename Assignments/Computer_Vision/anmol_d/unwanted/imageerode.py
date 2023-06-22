import cv2
import os

image = cv2.imread('./image.png')

frame = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#frame = cv2.GaussianBlur(gray, (25,25), sigmaX=34,sigmaY=34)
  
dup= frame
w = frame.shape[0]
h = frame.shape[1]


erode =cv2.erode(frame,(3,3),iterations=0)
open = cv2.dilate(erode,(3,3),iterations=0)
open2 = cv2.dilate(open,(3,3),iterations=0)
erode2 =cv2.erode(open2,(3,3),iterations=0)
while True:
    cv2.imshow('original',image)
    cv2.imshow('cv processed',erode2)
    cv2.imshow('eroded', erode)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break






cv2.destroyAllWindows()
