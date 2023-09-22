
(cl:in-package :asdf)

(defsystem "osm2rviz-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Guide_line" :depends-on ("_package_Guide_line"))
    (:file "_package_Guide_line" :depends-on ("_package"))
    (:file "V2X" :depends-on ("_package_V2X"))
    (:file "_package_V2X" :depends-on ("_package"))
  ))