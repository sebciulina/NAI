import cv2
import time
  
  
# define a video capture object
vid = cv2.VideoCapture(0)
  
while(True):
      
    # Capture the video frame
    # by frame
    ret, frame = vid.read()
    start = time.time()
    # Flip the video
    frame = cv2.flip(frame, 1)
    

    img_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blur_img = cv2.GaussianBlur(img_gray, (3,3) ,0)
    ret, img_thresh = cv2.threshold(blur_img, 150, 255, cv2.THRESH_BINARY)
    # detect contours on binary image
    contours, _ = cv2.findContours(img_thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    cv2.drawContours(frame, contours, -1, (0, 255, 0), 2)
    if len(contours)>0:
        # find the biggest countour (c) by the area
        c = max(contours, key = cv2.contourArea)
        end = time.time()
        x,y,w,h = cv2.boundingRect(c)

        # draw the biggest contour (c) in green
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
    cv2.imshow('frame',frame)
    #Exit on ESC
    if cv2.waitKey(1) & 0xFF == 27:
        print("Time: ",end - start)
        break
  
# After the loop release the cap object
vid.release()
# Destroy all the windows
cv2.destroyAllWindows()