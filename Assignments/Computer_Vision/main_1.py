import cv2
import numpy as np

cap = cv2.VideoCapture(0, cv2.CAP_V4L2)

kernel = np.ones((5, 5), dtype=np.uint8)

if not cap.isOpened():
    print("Unable to open the camera.")
    exit()

ret, background = cap.read()

if not ret:
    print("Unable to read the background frame.")
    exit()

def GrayScale_(image):
    b, g, r = cv2.split(image)
    return cv2.addWeighted(b, 0.114, g, 0.587, 0) + cv2.addWeighted(r, 0.299, 0, 0, 0)

def Gaussian_blur_(image):
    kernel_size = 5
    sigma = 1.67
    center = kernel_size // 2
    x, y = np.meshgrid(np.arange(-center, center+1), np.arange(-center, center+1))
    
    kernel = np.exp(-(x**2 + y**2) / (2 * sigma**2))
    kernel /= np.sum(kernel) 

    image_height, image_width = image.shape[:2]
    
    blurred_image = np.zeros_like(image)
    
    for y in range(center, image_height - center):
        for x in range(center, image_width - center):
            neighborhood = image[y-center:y+center+1, x-center:x+center+1]
            blurred_image[y, x] = np.sum(neighborhood * kernel)

    return blurred_image


background_gray = GrayScale_(background)

def Erosion_(image):
    h, w = image.shape[:2]

    p_h = kernel.shape[0] // 2
    p_w = kernel.shape[1] // 2

    eroded_image = np.zeros_like(image)

    for i in range(p_h, h - p_h):
        for j in range(p_w, w - p_w):
            neighborhood = image[i - p_h : i + p_h + 1, j - p_w : j + p_w + 1]
            eroded_image[i, j] = np.min(neighborhood)

    return eroded_image

def Dilation_(image):
    h, w = image.shape[:2]

    p_h = kernel.shape[0] // 2
    p_w = kernel.shape[1] // 2

    dilated_image = np.zeros_like(image)

    for i in range(p_h, h - p_h):
        for j in range(p_w, w - p_w):
            neighborhood = image[i - p_h : i + p_h + 1, j - p_w : j + p_w + 1]
            dilated_image[i, j] = np.max(neighborhood)

    return dilated_image

Opening_ = lambda image: Dilation_(Erosion_(image))
Closing_ = lambda image: Erosion_(Dilation_(image))

def find_centroid(image) :
    # 1 channel to 3 channel
    img3 = cv2.cvtColor(image, cv2.COLOR_GRAY2BGR)
    gray_blur = Gaussian_blur_(GrayScale_(img3))
    contours, _ = cv2.findContours(gray_blur, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    max_contour = max(contours, key=cv2.contourArea)
    M = cv2.moments(max_contour)
    centroid_x = int(M['m10'] / M['m00'])
    centroid_y = int(M['m01'] / M['m00'])
    cv2.circle(frame, (centroid_x, centroid_y), 6, (0, 0, 255), 2)

while True:
    ret, frame = cap.read()

    if ret:
        gray = GrayScale_(frame)
        gray_blur = Gaussian_blur_(gray)
        edges = cv2.Canny(gray_blur, 40, 100)

        mask = cv2.absdiff(background_gray, gray_blur)
        _, threshold = cv2.threshold(mask, 40, 255, cv2.THRESH_BINARY)

        opening = Opening_(threshold)
        closing = Closing_(opening)

        fin_image = np.zeros_like(frame)
        h, w = frame.shape[:2]
        for i in range(h):
            for j in range(w):
                if (closing[i, j]) :
                    fin_image[i, j] = frame[i, j]

        find_centroid(closing)

        cv2.imshow('Original', frame)
        cv2.imshow('Edges', edges)
        cv2.imshow('Threshold', threshold)
        cv2.imshow('Opening', opening)
        cv2.imshow('Closing', closing)
        cv2.imshow('Final Image', fin_image)

    if cv2.waitKey(1) == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()