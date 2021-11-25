(defparameter *my-hash* (make-hash-table))

(defun insert-pair (key value)
  (setf (gethash key *my-hash*) value))

(defun delete-by-key (key)
  (multiple-value-bind (_ find) (gethash key *my-hash*)
		    (if find
			(remhash key *my-hash*))))

(defun primep (number)
  (when (> number 1)
    (loop for fac from 2 to (isqrt number) never
					   (zerop (mod number fac)))))

(defun next-prime (number)
  (loop for n from number when (primep n) return n))

(defmacro do-primes ((var start end) &body body)
  `(do ((,var (next-prime ,start) (next-prime (1+ ,var))))
       ((> ,var ,end))
     ,@body))

(defmacro do-primes-v2 ((var start end) &body body)
  `(do ((ending-value ,end)
	(,var (next-prime ,start) (next-prime (1+ ,var))))
       ((> ,var ending-value))
     ,@body))
