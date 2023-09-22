;; Auto-generated. Do not edit!


(when (boundp 'osm2rviz::Guide_line)
  (if (not (find-package "OSM2RVIZ"))
    (make-package "OSM2RVIZ"))
  (shadow 'Guide_line (find-package "OSM2RVIZ")))
(unless (find-package "OSM2RVIZ::GUIDE_LINE")
  (make-package "OSM2RVIZ::GUIDE_LINE"))

(in-package "ROS")
;;//! \htmlinclude Guide_line.msg.html


(defclass osm2rviz::Guide_line
  :super ros::object
  :slots (_x _y _heading ))

(defmethod osm2rviz::Guide_line
  (:init
   (&key
    ((:x __x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:y __y) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:heading __heading) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _x __x)
   (setq _y __y)
   (setq _heading __heading)
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:heading
   (&optional __heading)
   (if __heading (setq _heading __heading)) _heading)
  (:serialization-length
   ()
   (+
    ;; float32[] _x
    (* 4    (length _x)) 4
    ;; float32[] _y
    (* 4    (length _y)) 4
    ;; float32[] _heading
    (* 4    (length _heading)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[] _x
     (write-long (length _x) s)
     (dotimes (i (length _x))
       (sys::poke (elt _x i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _y
     (write-long (length _y) s)
     (dotimes (i (length _y))
       (sys::poke (elt _y i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _heading
     (write-long (length _heading) s)
     (dotimes (i (length _heading))
       (sys::poke (elt _heading i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[] _x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _y
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _y (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _y i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _heading
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _heading (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _heading i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get osm2rviz::Guide_line :md5sum-) "497c36b4f8b08b430204bff5826ad4da")
(setf (get osm2rviz::Guide_line :datatype-) "osm2rviz/Guide_line")
(setf (get osm2rviz::Guide_line :definition-)
      "float32[] x
float32[] y
float32[] heading
")



(provide :osm2rviz/Guide_line "497c36b4f8b08b430204bff5826ad4da")


