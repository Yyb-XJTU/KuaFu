;; Auto-generated. Do not edit!


(when (boundp 'V2X_pkg::V2X)
  (if (not (find-package "V2X_PKG"))
    (make-package "V2X_PKG"))
  (shadow 'V2X (find-package "V2X_PKG")))
(unless (find-package "V2X_PKG::V2X")
  (make-package "V2X_PKG::V2X"))

(in-package "ROS")
;;//! \htmlinclude V2X.msg.html


(defclass V2X_pkg::V2X
  :super ros::object
  :slots (_Yellow _Red _Black ))

(defmethod V2X_pkg::V2X
  (:init
   (&key
    ((:Yellow __Yellow) (make-array 0 :initial-element 0 :element-type :integer))
    ((:Red __Red) (make-array 0 :initial-element 0 :element-type :integer))
    ((:Black __Black) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _Yellow __Yellow)
   (setq _Red __Red)
   (setq _Black __Black)
   self)
  (:Yellow
   (&optional __Yellow)
   (if __Yellow (setq _Yellow __Yellow)) _Yellow)
  (:Red
   (&optional __Red)
   (if __Red (setq _Red __Red)) _Red)
  (:Black
   (&optional __Black)
   (if __Black (setq _Black __Black)) _Black)
  (:serialization-length
   ()
   (+
    ;; int32[] _Yellow
    (* 4    (length _Yellow)) 4
    ;; int32[] _Red
    (* 4    (length _Red)) 4
    ;; int32[] _Black
    (* 4    (length _Black)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32[] _Yellow
     (write-long (length _Yellow) s)
     (dotimes (i (length _Yellow))
       (write-long (elt _Yellow i) s)
       )
     ;; int32[] _Red
     (write-long (length _Red) s)
     (dotimes (i (length _Red))
       (write-long (elt _Red i) s)
       )
     ;; int32[] _Black
     (write-long (length _Black) s)
     (dotimes (i (length _Black))
       (write-long (elt _Black i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32[] _Yellow
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Yellow (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _Yellow i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; int32[] _Red
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Red (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _Red i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; int32[] _Black
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Black (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _Black i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get V2X_pkg::V2X :md5sum-) "a7304ed0a871552fc04b10784eeafcb6")
(setf (get V2X_pkg::V2X :datatype-) "V2X_pkg/V2X")
(setf (get V2X_pkg::V2X :definition-)
      "int32[] Yellow
int32[] Red
int32[] Black

")



(provide :V2X_pkg/V2X "a7304ed0a871552fc04b10784eeafcb6")


