(defvar *test-name* nil)

(defun add(x y)
  (+ x y))

(defun test-add ()
  (and
   (= (add 1 2) 3)
   (= (add 1 3) 4)
   (= (add -1 1) 0)))

(defun test-add-v1 ()
   (format t "~:[FAIL~;pass~] ... ~a~%" (= (add 1 2) 3) '(= (add 1 2) 3))
   (format t "~:[FAIL~;pass~] ... ~a~%" (= (add 1 3) 4) '(= (add 1 3) 4))
  (format t "~:[FAIL~;pass~] ... ~a~%" (= (add -1 1) 0) '(= (add -1 1) 0)))

(defun report-result (result form)
  (format t "~:[FAIL~;pass~] ... ~a  ~a~%" result *test-name* form)
  result)

(defun test-add-v2 ()
  (report-result (= (add 1 2) 3) '(= (add 1 2) 3))
  (report-result (= (add 1 3) 4) '(= (add 1 3) 4))
  (report-result (= (add -1 1) 0) '(= (add -1 1) 0)))

(defmacro check (form)
  `(report-result ,form ',form))

(defun test-add-v3 ()
  (check (= (add 1 2) 3))
  (check (= (add 1 3) 4))
  (check (= (add -1 1) 0)))

(defmacro multi-check (&body forms)
  `(progn
     ,@(loop for f in forms collect `(report-result ,f ',f))))

(defun test-add-v4 ()
  (let ((*test-name* "test-add"))
    (multi-check
      (= (add 1 2) 3)
      (= (add 2 3) 5)
      (= (add 1 -1) 0))))

(defun sub (a b)
  (- a b))

(defun test-sub ()
  (let ((*test-name* "test-sub"))
    (multi-check
      (= (sub 2 1) 1)
      (= (sub 3 2) 1))))

(defmacro combine-results (&body body)
  `(progn
     ,@body))

(defun test-arithmatic ()
  (combine-results
    (test-add-v4)
    (test-sub)))

(defmacro deftest (name parameters &body body)
  `(defun ,name ,parameters
    (let ((*test-name* ',name))
      ,@body)))
