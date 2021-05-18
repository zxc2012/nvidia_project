#!/usr/bin/env python2.7
import rospy # Python library for ROS
from sensor_msgs.msg import Image # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import numpy as np
import time
import math
import cv2 # OpenCV library


def calibration(cap, board_w, board_h, n_board): #n_board: required num of views
    successes=0
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
    z=0
    board_n = board_w*board_h
    board_sz = (board_w, board_h)
    #capturing required number of views

    while successes<n_board:
        ret, image= cap.read()
        
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        found, corners = cv2.findChessboardCorners(gray, board_sz, None)
        objp=np.zeros((n_board*board_n,3), np.float32)
        objp[:,:2]=np.mgrid[0:board_w, 0:board_h].T.reshape(-1,2)
        obj_pnts=[]
        img_pnts=[]

        #if got a good image, draw chess board
        if found == True:
            #Get Subpixel accuracy on those corners
            cv2.cornerSubPix(gray, corners, board_sz, (-1,-1),criteria)

            print("found frame number {0}".format(z+1))
            cv2.drawChessboardCorners(image, board_sz, corners,found)
            z=z+1

            if len(corners) ==board_n:
                step=successes*board_n
                k=step
                img_pnts.append(corners)
                obj_pnts.append(objp)
            successes=successes+1
            time.sleep(2)
            print("-------------------------------\n")
        #if got a good image, add to matrix
        
        cv2.imshow("Test Frame", image)
        cv2.waitKey(33)
        # cv2.destroyWindow("Test Frame")
    print("Checking is fine, all matrices are created")
    
    # ret, mtx, dist, rvecs, tves = cv2.calibrateCamera(obj_pnts2, img_pnts2, gray.shape[::-1],None, None)
    ret, mtx, dist, rvecs, tves = cv2.calibrateCamera(obj_pnts, img_pnts, gray.shape[::-1], None, None)
    print("Checking Camera Calibration..............OK")
    intrinsic_file=cv2.FileStorage("Intrinsic.xml", cv2.FILE_STORAGE_WRITE)
    intrinsic_file.write("Intrinsic", mtx)
    intrinsic_file.release()
    distort_file=cv2.FileStorage("Distortion.xml", cv2.FILE_STORAGE_WRITE)
    distort_file.write("Distortion", dist)
    distort_file.release()
    return ret, mtx, dist, rvecs, tves

def publish_message():
 
  # Node is publishing to the video_frames topic using 
  # the message type Image
  pub = rospy.Publisher('video_frames', Image, queue_size=10)
     
  # Tells rospy the name of the node.
  # Anonymous = True makes sure the node has a unique name. Random
  # numbers are added to the end of the name.
  rospy.init_node('video_pub_py', anonymous=True)
     
  # Go through the loop 10 times per second
  rate = rospy.Rate(10) # 10hz
  
  board_w=8 # number of horizontal corners
  board_h=6 # number of vertical corners
  n_board=1
  # Create a VideoCapture object
  # The argument '0' gets the default webcam.
  cap = cv2.VideoCapture(0)

  ret, mtx, dist, rvecs, tves=calibration(cap, board_w, board_h, n_board)
  
  calib_mode=rospy.get_param('calib', 1)
  if calib_mode:
      found= False
      while found==False:
          ret, frame = cap.read()
          gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
          h, w = frame.shape[:2] #height, width
          newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h),1,(w,h))
              
          #termination criteria
          criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
          
          #undistort
          mapx, mapy=cv2.initUndistortRectifyMap(mtx, dist, None, newcameramtx, (w,h),5)
          
          #rectify image
          # dst= cv2.remap(image, mapx, mapy, cv2.INTER_LINEAR)

          #Get the chessboard on the plane
          found, corners = cv2.findChessboardCorners(gray, (board_w, board_h), None)
          cv2.namedWindow("Chessboard")
          cv2.imshow("Chessboard",frame)
          cv2.waitKey(33)


      print(corners)
      print("All mapping completed")
      #Get Subpixel accuracy on those corners
      cv2.cornerSubPix(gray, corners, (board_w, board_h), (-1,-1),criteria )

      #Get the image and object points
      #We will choose chessboard object points as (radius,center)
      #(0,0),(board_w-1,0), (0,board_h-1), (board_w-1,board_h-1)
      objPts=np.zeros((4,2), dtype=np.float32)
      imgPts=np.zeros((4,2), dtype=np.float32)

      pi=math.pi
      theta= math.atan2((corners[0][0][1]-corners[(board_h-1)*board_w+board_w-1][0][1]),-(corners[0][0][0]-corners[(board_h-1)*board_w+board_w-1][0][0]))
      print(-(corners[0][0][0]-corners[(board_h-1)*board_w+board_w-1][0][0]))
      print(corners[0][0][1]-corners[(board_h-1)*board_w+board_w-1][0][1])
      print(theta/math.pi)

      if theta>=0.5*pi: 
          print(1) 
          imgPts[0]=corners[(board_h-1)*board_w+board_w-1][0]
          imgPts[1]=corners[(board_h-1)*board_w][0]
          imgPts[2]=corners[board_w-1][0]
          imgPts[3]=corners[0][0]
      elif theta<-0.5*pi:
          print(2)   
          imgPts[0]=corners[(board_h-1)*board_w][0]   
          imgPts[1]=corners[0][0]
          imgPts[2]=corners[(board_h-1)*board_w+board_w-1][0] 
          imgPts[3]=corners[board_w-1][0]
      elif theta>-pi*0.5 and theta<0:
          print(3)
          imgPts[0]=corners[0][0]
          imgPts[1]=corners[board_w-1][0]
          imgPts[2]=corners[(board_h-1)*board_w][0]
          imgPts[3]=corners[(board_h-1)*board_w+board_w-1][0]
      else:
          print(4)
          imgPts[0]=corners[board_w-1][0]
          imgPts[1]=corners[(board_h-1)*board_w+board_w-1][0]  
          imgPts[2]=corners[0][0]
          imgPts[3]=corners[(board_h-1)*board_w][0]                                                                                                                                                                                                                                                                                                                                                                                                     

      imgPts_int=imgPts.astype(int)

      objPts[0]=[imgPts[2][0],700]
      objPts[1]=[(board_w-1)*100+imgPts[2][0], 700]
      objPts[2]=[imgPts[2][0],(board_h-1)*100+700]
      objPts[3]=[(board_w-1)*100+imgPts[2][0],700+ (board_h-1)*100]

      #Draw the points in order : B,G,R,Y
      cv2.circle(frame, tuple(imgPts_int[0]), 9, (0,0,255)) #img, center, radius, color, thickness=1, lineType=8, shift=0
      cv2.circle(frame, tuple(imgPts_int[1]), 9, (0,255,0))
      cv2.circle(frame, tuple(imgPts_int[2]), 9, (255,0,0))
      cv2.circle(frame, tuple(imgPts_int[3]), 9, (255,255,0))

      #Draw the found chessboard
      cv2.drawChessboardCorners(frame,(board_w, board_h), corners, found)
      cv2.imshow("Chessboard", frame)

      #Find the Homography
      H=cv2.getPerspectiveTransform(imgPts,objPts)

      cv_file=cv2.FileStorage("H.xml", cv2.FILE_STORAGE_WRITE)
      cv_file.write("H", H)
      cv_file.release()

      #Let the user adjust the z height of the view
      # Z=10
      # key =0.5
      bird_image=frame.copy()
  
  else:
      cv_file = cv2.FileStorage("H.xml", cv2.FILE_STORAGE_READ)

      # get H
      H = cv_file.getNode("H")
  # Used to convert between ROS and OpenCV images
  br = CvBridge()
 
  # While ROS is still running.
  while not rospy.is_shutdown():
     
      # Capture frame-by-frame
      # This method returns True/False as well
      # as the video frame.
      ret, frame = cap.read()
      bird_video=cv2.warpPerspective(frame, H, (1000,1000))
      if ret == True:
        # Print debugging information to the terminal
        rospy.loginfo('publishing video frame')
             
        # Publish the image.
        # The 'cv2_to_imgmsg' method converts an OpenCV
        # image to a ROS image message
        pub.publish(br.cv2_to_imgmsg(bird_video,"bgr8"))
             
      # Sleep just enough to maintain the desired rate
      rate.sleep()
  cap.release()
  cv2.destroyAllWindows()
         
if __name__ == '__main__':
  try:
    publish_message()
  except rospy.ROSInterruptException:
    pass