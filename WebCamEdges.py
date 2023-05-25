import cv2
import time

#capturing live video feed and applying edge detection
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Unable to capture footage")

while cv2.waitKey(10)==-1:
    ret,frame = cap.read()
    if ret:
        frame = cv2.Canny(frame,10,200)
        cv2.imshow("Webcam",frame)

    else:
        print("video not read")

