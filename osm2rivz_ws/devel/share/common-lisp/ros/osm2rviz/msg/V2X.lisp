; Auto-generated. Do not edit!


(cl:in-package osm2rviz-msg)


;//! \htmlinclude V2X.msg.html

(cl:defclass <V2X> (roslisp-msg-protocol:ros-message)
  ((Yellow
    :reader Yellow
    :initarg :Yellow
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (Red
    :reader Red
    :initarg :Red
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (Black
    :reader Black
    :initarg :Black
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass V2X (<V2X>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <V2X>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'V2X)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name osm2rviz-msg:<V2X> is deprecated: use osm2rviz-msg:V2X instead.")))

(cl:ensure-generic-function 'Yellow-val :lambda-list '(m))
(cl:defmethod Yellow-val ((m <V2X>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader osm2rviz-msg:Yellow-val is deprecated.  Use osm2rviz-msg:Yellow instead.")
  (Yellow m))

(cl:ensure-generic-function 'Red-val :lambda-list '(m))
(cl:defmethod Red-val ((m <V2X>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader osm2rviz-msg:Red-val is deprecated.  Use osm2rviz-msg:Red instead.")
  (Red m))

(cl:ensure-generic-function 'Black-val :lambda-list '(m))
(cl:defmethod Black-val ((m <V2X>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader osm2rviz-msg:Black-val is deprecated.  Use osm2rviz-msg:Black instead.")
  (Black m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <V2X>) ostream)
  "Serializes a message object of type '<V2X>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Yellow))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'Yellow))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Red))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'Red))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Black))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'Black))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <V2X>) istream)
  "Deserializes a message object of type '<V2X>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Yellow) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Yellow)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Red) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Red)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Black) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Black)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<V2X>)))
  "Returns string type for a message object of type '<V2X>"
  "osm2rviz/V2X")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'V2X)))
  "Returns string type for a message object of type 'V2X"
  "osm2rviz/V2X")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<V2X>)))
  "Returns md5sum for a message object of type '<V2X>"
  "a7304ed0a871552fc04b10784eeafcb6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'V2X)))
  "Returns md5sum for a message object of type 'V2X"
  "a7304ed0a871552fc04b10784eeafcb6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<V2X>)))
  "Returns full string definition for message of type '<V2X>"
  (cl:format cl:nil "int32[] Yellow~%int32[] Red~%int32[] Black~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'V2X)))
  "Returns full string definition for message of type 'V2X"
  (cl:format cl:nil "int32[] Yellow~%int32[] Red~%int32[] Black~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <V2X>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Yellow) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Red) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Black) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <V2X>))
  "Converts a ROS message object to a list"
  (cl:list 'V2X
    (cl:cons ':Yellow (Yellow msg))
    (cl:cons ':Red (Red msg))
    (cl:cons ':Black (Black msg))
))
