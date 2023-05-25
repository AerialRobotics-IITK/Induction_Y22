import cv2

# passing input images instead of webcam feed
images=[]
images.append(cv2.imread('example1.png'))
images.append(cv2.imread('example.png'))

# converting to grayscale and gausssian blurring
temp = images[0]
images[0] = cv2.cvtColor(images[0],cv2.COLOR_BGR2GRAY)
images[1] = cv2.cvtColor(images[1],cv2.COLOR_BGR2GRAY)
images[0] = cv2.GaussianBlur(images[0],(5,5),2)
images[1] = cv2.GaussianBlur(images[1],(5,5),2)

# subtracting and thresholding
difference = cv2.subtract(images[1],images[0])
ret,threhsed_img = cv2.threshold(difference,20,255,cv2.THRESH_BINARY)

# opening
element = cv2.getStructuringElement(cv2.MORPH_RECT,(3,3))
erd_img = cv2.erode(threhsed_img,element,iterations=2)
open_img = cv2.dilate(erd_img,element,iterations=2)

# closing after opening
dil_img = cv2.dilate(open_img,element,iterations=2)
close_img = cv2.erode(dil_img,element,iterations=2)

# masking out changes using bitwise operation
mask = close_img
final_bgr = cv2.bitwise_and(temp,temp,mask=mask )
cv2.imshow("ProcessedImage",final_bgr)

# Definition of moments in image processing is borrowed from physics. Assume that each pixel in image has weight that is equal to its intensity. Then the point you defined is centroid (a.k.a. center of mass) of image.
# Assume that I(x,y) is the intensity of pixel (x,y) in image. Then m(i,j) is the sum for all possible x and y of: I(x,y) * (x^i) * (y^j)    
#finding and making circle about centroid
final_gray = cv2.cvtColor(final_bgr,cv2.COLOR_BGR2GRAY)
moments = cv2.moments(final_gray)
x = int((moments['m10'])/(moments['m00']))
y = int((moments['m01'])/(moments['m00']))
center = (x,y)
color = (0,0,255)
cv2.circle(final_bgr,center,5,color,1)
cv2.imshow('Centroid',final_bgr)

cv2.waitKey(0)
cv2.destroyAllWindows()