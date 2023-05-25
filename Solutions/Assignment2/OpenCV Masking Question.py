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


def dilate(array):
    dilated_array = np.copy(array)  # Create a copy of the input array to store the eroded result

    for row in range(1, array.shape[0] - 1):
        for col in range(1, array.shape[1] - 1):
            if array[row, col] == 1:
                # Set the surrounding elements to 0
                dilated_array[row - 1: row + 2, col - 1: col + 2] = 1

    return dilated_array


def erode(array):
    eroded_array = np.copy(array)  # Create a copy of the input array to store the eroded result

    for row in range(1, array.shape[0] - 1):
        for col in range(1, array.shape[1] - 1):
            if array[row, col] == 0:
                # Set the surrounding elements to 0
                eroded_array[row - 1: row + 2, col - 1: col + 2] = 0

    return eroded_array

# Create a VideoCapture object
cap = cv2.VideoCapture(0)
# Check if the webcam is opened
if not cap.isOpened():
    print("Error opening webcam")
    exit()
# Get the first frame
ret, frame = cap.read()

# Save the first frame
cv2.imwrite("first_frame.jpg", frame)

# Close the video
cap.release()

# Load the first frame
first_frame = cv2.imread("first_frame.jpg")
# Do something with the frame
greyfirst = convert_to_grayscale(first_frame)
blurredfirst = cv2.GaussianBlur(greyfirst, (3, 3), 1.0)
thresholdedfirst=cv2.threshold(blurredfirst,127,255,cv2.THRESH_BINARY)[1]
#converting to array to operate upon
thresholdedfirst_array = np.array(thresholdedfirst)
closed_after_opened_first=erode(dilate(dilate(erode(thresholdedfirst_array))))
#highlight the pixels =1 in first image
boolmask = (closed_after_opened_first[:, :] == 255)
processed_mask=np.array(first_frame)
processed_mask[np.invert(boolmask)]=0

# Show the frame
cv2.imshow("first frame",first_frame)
cv2.imshow("processed mask",processed_mask)

cap = cv2.VideoCapture(0)
# Check if the webcam is opened
if not cap.isOpened():
    print("Error opening webcam")
    exit()
while True:
    # A)Canny edge detection
    # Capture the frame from the webcam
    ret, frame = cap.read()
    Final=frame-processed_mask
    cv2.imshow("Webcam",frame)
    cv2.imshow("final", Final)
    key = cv2.waitKey(1)
    # If the key pressed is `c`, break from the loop
    if key == ord('c'):
        break

#Centroid detection
centroid_image=thresholdedfirst_array
centroid_image[np.invert(boolmask)]=0
M=cv2.moments(centroid_image)
centroid_x = int(M['m10'] / M['m00'])
centroid_y = int(M['m01'] / M['m00'])
centroid = (centroid_x, centroid_y)
cv2.circle(first_frame,centroid, 5, (0,0,255), -1)
cv2.imshow("Image with Circle", first_frame)
cv2.waitKey(6000)
cv2.destroyAllWindows()
