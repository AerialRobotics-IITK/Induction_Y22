import cv2
import numpy as np

# Function for opening operation
def opening(img, kernel_size):
    kernel = np.ones((kernel_size, kernel_size), np.uint8)
    opening = cv2.morphologyEx(img, cv2.MORPH_OPEN, kernel)
    return opening

# Function for closing operation
def closing(img, kernel_size):
    kernel = np.ones((kernel_size, kernel_size), np.uint8)
    closing = cv2.morphologyEx(img, cv2.MORPH_CLOSE, kernel)
    return closing

# Create a VideoCapture object
cap = cv2.VideoCapture(0)  # 0 corresponds to the default camera

# Check if the camera is opened successfully
if not cap.isOpened():
    print("Unable to open the camera.")
    exit()

# Read the first frame to use as the background
ret, background = cap.read()
if not ret:
    print("Unable to read the frame.")
    exit()

# Convert the background frame to grayscale
background_gray = cv2.cvtColor(background, cv2.COLOR_BGR2GRAY)

while True:
    # Read frame from the camera
    ret, frame = cap.read()  # If the frame is read correctly, ret will be True

    if ret:
        # Convert frame to grayscale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Apply Gaussian blur to reduce noise
        blurred = cv2.GaussianBlur(gray, (5, 5), 0)

        # Compute the absolute difference between the background and current frame
        diff = cv2.absdiff(background_gray, blurred)

        # Threshold the difference image
        _, thresh = cv2.threshold(diff, 30, 255, cv2.THRESH_BINARY)

        # Perform opening and closing operations on the thresholded image
        opened = opening(thresh, 3)
        closed = closing(opened, 3)

        # Create a mask with the difference image
        mask = cv2.bitwise_and(frame, frame, mask=closed)

        # Convert the mask to black and white
        mask_bw = cv2.cvtColor(mask, cv2.COLOR_BGR2GRAY)

        # Invert the mask
        mask_inv = cv2.bitwise_not(mask_bw)

        # Create a colored foreground image
        foreground = cv2.bitwise_and(frame, frame, mask=mask_inv)

        # Find contours in the masked image
        contours, _ = cv2.findContours(closed, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Initialize centroid coordinates
        centroid_x = None
        centroid_y = None

        if len(contours) > 0:
            # Find the largest contour (assuming it corresponds to the object of interest)
            largest_contour = max(contours, key=cv2.contourArea)

            # Calculate the centroid of the largest contour
            M = cv2.moments(largest_contour)
            if M["m00"] != 0:
                centroid_x = int(M["m10"] / M["m00"])
                centroid_y = int(M["m01"] / M["m00"])

        # Display the pre-processed images and processed images
        cv2.imshow('Original Frame', frame)
        cv2.imshow('Difference Image', diff)
        cv2.imshow('Thresholded Image', thresh)
        cv2.imshow('Mask', mask)
        cv2.imshow('Foreground', foreground)

        # Draw the centroid on the frame if it exists
        if centroid_x is not None and centroid_y is not None:
            cv2.circle(frame, (centroid_x, centroid_y), 5, (0, 0, 255), -1)
            cv2.putText(frame, 'Centroid', (centroid_x - 20, centroid_y - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

        # Display the frame with centroid
        cv2.imshow('Frame with Centroid', frame)

    # Break the loop when 'q' key is pressed
    if cv2.waitKey(1) == ord('q'):
        break

# Release the VideoCapture object and close the windows
cap.release()
cv2.destroyAllWindows()
