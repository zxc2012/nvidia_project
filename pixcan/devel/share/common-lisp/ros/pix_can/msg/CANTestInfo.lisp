; Auto-generated. Do not edit!


(cl:in-package pix_can-msg)


;//! \htmlinclude CANTestInfo.msg.html

(cl:defclass <CANTestInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (current_wheel
    :reader current_wheel
    :initarg :current_wheel
    :type cl:fixnum
    :initform 0)
   (target_wheel
    :reader target_wheel
    :initarg :target_wheel
    :type cl:fixnum
    :initform 0))
)

(cl:defclass CANTestInfo (<CANTestInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CANTestInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CANTestInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pix_can-msg:<CANTestInfo> is deprecated: use pix_can-msg:CANTestInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CANTestInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pix_can-msg:header-val is deprecated.  Use pix_can-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'current_wheel-val :lambda-list '(m))
(cl:defmethod current_wheel-val ((m <CANTestInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pix_can-msg:current_wheel-val is deprecated.  Use pix_can-msg:current_wheel instead.")
  (current_wheel m))

(cl:ensure-generic-function 'target_wheel-val :lambda-list '(m))
(cl:defmethod target_wheel-val ((m <CANTestInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pix_can-msg:target_wheel-val is deprecated.  Use pix_can-msg:target_wheel instead.")
  (target_wheel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CANTestInfo>) ostream)
  "Serializes a message object of type '<CANTestInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'current_wheel)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'current_wheel)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'target_wheel)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'target_wheel)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CANTestInfo>) istream)
  "Deserializes a message object of type '<CANTestInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'current_wheel)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'current_wheel)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'target_wheel)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'target_wheel)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CANTestInfo>)))
  "Returns string type for a message object of type '<CANTestInfo>"
  "pix_can/CANTestInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CANTestInfo)))
  "Returns string type for a message object of type 'CANTestInfo"
  "pix_can/CANTestInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CANTestInfo>)))
  "Returns md5sum for a message object of type '<CANTestInfo>"
  "f942539659fc3310c68f769b65513a00")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CANTestInfo)))
  "Returns md5sum for a message object of type 'CANTestInfo"
  "f942539659fc3310c68f769b65513a00")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CANTestInfo>)))
  "Returns full string definition for message of type '<CANTestInfo>"
  (cl:format cl:nil "Header header~%uint16 current_wheel~%uint16 target_wheel~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CANTestInfo)))
  "Returns full string definition for message of type 'CANTestInfo"
  (cl:format cl:nil "Header header~%uint16 current_wheel~%uint16 target_wheel~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CANTestInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CANTestInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'CANTestInfo
    (cl:cons ':header (header msg))
    (cl:cons ':current_wheel (current_wheel msg))
    (cl:cons ':target_wheel (target_wheel msg))
))
