import numpy as np
import cv2

cap = cv2.VideoCapture('http://192.168.254.104:8080/video')

fgbg = cv2.createBackgroundSubtractorMOG2()
kernel = np.ones((5,5),np.uint8)

while(1):
    ret, frame = cap.read()

    imgray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    fgmask = fgbg.apply(frame)

    opening = cv2.morphologyEx(fgmask,cv2.MORPH_OPEN,kernel)
    closing = cv2.morphologyEx(opening,cv2.MORPH_CLOSE,kernel)

    ret,thresh = cv2.threshold(closing,127,255,0)
    im2,contours,hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)

    if len(contours) > 0:
        cnt = contours[0]

        x,y,w,h = cv2.boundingRect(cnt)
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)

        rect = cv2.minAreaRect(cnt)
        box = cv2.boxPoints(rect)
        box = np.int0(box)
        cv2.drawContours(frame,contours,0,(0,0,255),3)

    cv2.imshow('frame',closing)
    #cv2.imshow('frame',frame)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()