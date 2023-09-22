
(cl:in-package :asdf)

(defsystem "V2X_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "V2X" :depends-on ("_package_V2X"))
    (:file "_package_V2X" :depends-on ("_package"))
  ))