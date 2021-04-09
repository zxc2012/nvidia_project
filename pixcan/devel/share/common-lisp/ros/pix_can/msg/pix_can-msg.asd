
(cl:in-package :asdf)

(defsystem "pix_can-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "CANTestInfo" :depends-on ("_package_CANTestInfo"))
    (:file "_package_CANTestInfo" :depends-on ("_package"))
  ))