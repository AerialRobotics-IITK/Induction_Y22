import cv2
import numpy as np

def centroid(image):
    #grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    #Gaussian blur
    blurred = cv2.GaussianBlur(gray, (7, 7), 0)

    #image moments
    moments = cv2.moments(blurred)

    # Calculate centroid coordinates
    if moments["m00"] != 0:
        cX = int(moments["m10"] / moments["m00"])
        cY = int(moments["m01"] / moments["m00"])
    else:
        cX, cY = 0, 0

    return cX, cY


# Create a VideoCapture object
cap = cv2.VideoCapture(0)  # 0 corresponds to the default camera

# Check if the camera is opened successfully
if not cap.isOpened():
    print("Unable to open the camera.")
    exit()

# Capture the initial frame
ret, initial_frame = cap.read()
if not ret:
    print("Failed to capture initial frame.")
    exit()

# Convert the initial frame to grayscale
initial_gray = cv2.cvtColor(initial_frame, cv2.COLOR_BGR2GRAY)

while True:
    # Read frame from the camera
    ret, frame = cap.read()  # If the frame is read correctly, ret will be True

    if ret: 

        # Convert the frame to grayscale
        gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Apply Gaussian blur to the image
        blurred_frame = cv2.GaussianBlur(gray_frame, (9, 9), 0)

        # Apply Canny edge detection to the blurred frame
        edges = cv2.Canny(blurred_frame, 15, 20)

        # Subtract the initial frame from the current frame
        frame_diff = cv2.absdiff(initial_gray, blurred_frame)

        #thresholding the image
        ret, thresholded = cv2.threshold(frame_diff, 35, 255, cv2.THRESH_BINARY)

        # functions for opening 
        kernel_opening = np.ones((5, 5), np.uint8)
        erosion = cv2.erode(thresholded,kernel_opening,iterations = 1)
        opening=cv2.dilate(erosion,kernel_opening,iterations = 1)
        #opening = cv2.morphologyEx(thresholded, cv2.MORPH_OPEN, kernel_opening) this is the shorter form of hte function that can be used 

        # functions for closing 
        kernel_closing = np.ones((10, 10), np.uint8)
        dialation=cv2.dilate(opening,kernel_closing,iterations =1)
        closing=cv2.erode(dialation,kernel_opening,iterations=1)
        #closing = cv2.morphologyEx(opening, cv2.MORPH_CLOSE, kernel_closing) shorter version instead of two ind fucntions 

        # Create a black background image
        background = np.zeros(frame.shape, dtype=np.uint8)

        # Create a colored foreground by applying bitwise and operation
        colored_foreground = cv2.bitwise_and(frame, frame, mask=closing)
        

        cv2.imshow('Pre-processed Image', thresholded)
        cv2.imshow('Processed Image', colored_foreground)

        cX, cY = centroid(colored_foreground)

        # Draw a red circle on the initial image at the centroid coordinates
        cv2.circle(colored_foreground, (cX, cY), 5, (0, 0, 255), -1)

        # Display the initial image with the centroid circle
        cv2.imshow('Centroid', colored_foreground)



    # Break the loop when 'q' key is pressed
    if cv2.waitKey(1) == ord('q'):
        break

# Release the VideoCapture object and close the window
cap.release()
cv2.destroyAllWindows()
