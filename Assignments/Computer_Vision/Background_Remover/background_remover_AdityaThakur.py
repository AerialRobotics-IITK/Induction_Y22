import cv2
from threading import Thread
from time import sleep
import numpy as np

class Vars():
    frame = None
    proccessingStart = False
    background = None

def bgremover():
    # Create a VideoCapture object
    cap = cv2.VideoCapture(0)  # 0 corresponds to the default camera

    # Check if camera is opened successfully
    if not cap.isOpened():
        print("Unable to open the camera.")
        return

    centroid_radius = 5
    centroid_color = (0, 0, 255) 

    while True:
        # Read frame from the camera
        ret, Vars.frame = cap.read()    # If frame is read correctly, ret will be True
        og_frame = Vars.frame
        frame = Vars.frame
        median = Vars.background

        if ret:
            # Here you are supposed to place the processing code
            if(Vars.proccessingStart):
                frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                frame = cv2.GaussianBlur(frame, (5,5),0)

                dif_frame = cv2.absdiff(median, frame)
                #threshold, diff = cv2.threshold(dif_frame, 100, 255, cv2.THRESH_BINARY)

                diff = cv2.threshold(dif_frame, 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)[1]

                # define the kernel
                kernel_open = np.ones((5, 5), np.uint8)
                kernel_close = np.ones((15, 15), np.uint8)
                
                # opening the image
                opening = cv2.morphologyEx(diff, cv2.MORPH_OPEN,
                                        kernel_open, iterations=1)
                closing = cv2.morphologyEx(opening, cv2.MORPH_CLOSE, 
                                        kernel_close, iterations=1)

                result = cv2.bitwise_and(og_frame, og_frame, mask=closing)
                cv2.imshow('Result', result)

                # Find contours of the objects
                contours, _ = cv2.findContours(closing, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

                # Draw centroid on original frame
                for contour in contours:
                    # Find moments of the contour
                    moments = cv2.moments(contour)

                    # Calculate centroid coordinates
                    if moments["m00"] != 0:
                        centroid_x = int(moments["m10"] / moments["m00"])
                        centroid_y = int(moments["m01"] / moments["m00"])

                        # Draw centroid on the original frame
                        cv2.circle(result, (centroid_x, centroid_y), centroid_radius, centroid_color, -1)
                
                cv2.imshow('Result with Contours', result)

        # Break the loop when 'q' key is pressed
        if cv2.waitKey(1) == ord('q'):
            break

    # Release the VideoCapture object and close the window
    cap.release()
    cv2.destroyAllWindows()

def main():
    Thread(target = lambda:bgremover()).start()
    print("Wait for the video feed to appear, then,")
    print("Move aside to take an image of the background and press ENTER")
    input()
    for i in range(3):
        print(3-i, end = '\r')
        sleep(1)
    print(' ', end='\r')
    cv2.imwrite('background.jpg', Vars.frame)

    Vars.background = cv2.imread('background.jpg')
    Vars.background = cv2.cvtColor(src=Vars.background, code=cv2.COLOR_BGR2GRAY)
    Vars.background = cv2.GaussianBlur(Vars.background, (5,5),0)

    Vars.proccessingStart = True

main()
