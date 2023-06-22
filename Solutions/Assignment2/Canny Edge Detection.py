import cv2
import numpy as np


def greyscale(image):
    photo = np.array(image)
    rgb_weights = [0.2989, 0.5870, 0.1140]
    greyscaled = np.dot(photo, rgb_weights)
    return greyscaled


def convert_to_grayscale(image):
    # Convert the image to grayscale using the cv2.cvtColor() function.
    grayscale_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    return grayscale_image


# Create a VideoCapture object
cap = cv2.VideoCapture(0)
# Check if the webcam is opened
if not cap.isOpened():
    print("Error opening webcam")
    exit()
# Loop over the frames from the webcam
while True:
    # A)Canny edge detection
    # Capture the frame from the webcam
    ret, frame = cap.read()
    # Do something with the frame
    greyed = convert_to_grayscale(frame)
    blurred = cv2.GaussianBlur(greyed, (3, 3), 1.0)
    canny = cv2.Canny(blurred, 100, 200)

    # Show the frame
    cv2.imshow("Webcam", canny)
    key = cv2.waitKey(1)
    # If the key pressed is `c`, break from the loop
    if key == ord('c'):
        break
cap.release()
cv2.destroyAllWindows()