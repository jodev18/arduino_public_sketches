import numpy as np
import cv2
from matplotlib import pyplot as plt

cap = cv2.VideoCapture('http://192.168.254.104:8080/video')

while 1:
	ret, frame = cap.read()
	#img = cv2.imread('imgtest.jpg',0)

	# Initiate FAST object with default values
	fast = cv2.FastFeatureDetector_create(threshold=10)

	# find and draw the keypoints
	kp = fast.detect(frame,None)
	#img2 = cv2.drawKeypoints(img, kp, None,color=(255,0,0))

	# Print all default params
	#print "nonmaxSuppression: ", fast.getBool('nonmaxSuppression')
	#print "neighborhood: ", fast.getInt('type')
	#print "Total Keypoints with nonmaxSuppression: ", len(kp)

	#cv2.imwrite('fast_true.png',img2)

	# Disable nonmaxSuppression
	fast.setNonmaxSuppression(0)
	kp = fast.detect(frame,None)

	#print "Total Keypoints without nonmaxSuppression: ", len(kp)

	img3 = cv2.drawKeypoints(frame, kp, None,color=(255,0,0))

	cv2.imshow('Plate Number Scanner',img3)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
	#print(path.decode("utf-8"))
	cv2.line(frame,(0,0),(511,511),(255,0,0),5)



#cv2.imwrite('fast_false.png',img3)