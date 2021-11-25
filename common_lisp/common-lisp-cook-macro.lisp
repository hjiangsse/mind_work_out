(defmacro setq2 (v1 v2 e)
  (let ((e1 (my-pow2 e)))
    (list 'progn
	  (list 'setq v1 e1)
	  (list 'setq v2 e1))))

(defmacro setq2-new (v1 v2 e)
  `(let ((e1 (my-pow2 ,e)))
     (progn
       (setq ,v1 e1)
       (setq ,v2 e1))))

(defun my-pow2 (x)
  (* x x))

(defmacro setq-reverse (v1 v2 direction)
  (case direction
    (:normal (list 'setq v1 v2))
    (:backward (list 'setq v2 v1))
    (t `(error "Unknow direction: ~a" direction))))


(defmacro gen-list (&body body)
  `(',@body))
