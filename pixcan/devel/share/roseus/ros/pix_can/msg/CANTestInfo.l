;; Auto-generated. Do not edit!


(when (boundp 'pix_can::CANTestInfo)
  (if (not (find-package "PIX_CAN"))
    (make-package "PIX_CAN"))
  (shadow 'CANTestInfo (find-package "PIX_CAN")))
(unless (find-package "PIX_CAN::CANTESTINFO")
  (make-package "PIX_CAN::CANTESTINFO"))

(in-package "ROS")
;;//! \htmlinclude CANTestInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass pix_can::CANTestInfo
  :super ros::object
  :slots (_header _current_wheel _target_wheel ))

(defmethod pix_can::CANTestInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:current_wheel __current_wheel) 0)
    ((:target_wheel __target_wheel) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _current_wheel (round __current_wheel))
   (setq _target_wheel (round __target_wheel))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:current_wheel
   (&optional __current_wheel)
   (if __current_wheel (setq _current_wheel __current_wheel)) _current_wheel)
  (:target_wheel
   (&optional __target_wheel)
   (if __target_wheel (setq _target_wheel __target_wheel)) _target_wheel)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint16 _current_wheel
    2
    ;; uint16 _target_wheel
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint16 _current_wheel
       (write-word _current_wheel s)
     ;; uint16 _target_wheel
       (write-word _target_wheel s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint16 _current_wheel
     (setq _current_wheel (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _target_wheel
     (setq _target_wheel (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get pix_can::CANTestInfo :md5sum-) "f942539659fc3310c68f769b65513a00")
(setf (get pix_can::CANTestInfo :datatype-) "pix_can/CANTestInfo")
(setf (get pix_can::CANTestInfo :definition-)
      "Header header
uint16 current_wheel
uint16 target_wheel

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :pix_can/CANTestInfo "f942539659fc3310c68f769b65513a00")


