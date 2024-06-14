(defun binomial (n k)
  (cond
    ((= k 0) 1)
    ((= n 0) 0)
    (t (/ (* n (binomial (1- n) (1- k))) k))))

(defun next-row (row)
  (mapcar #'+ (append row '(0)) (append '(0) row)))

(defun generate-pascal (n &optional (rows '((1))))
  (if (zerop n)
      (nreverse rows)
      (generate-pascal (1- n) (cons (next-row (first rows)) rows))))

(defun binomial2 (n k)
  (nth k (nth n (generate-pascal n))))

(defun merge-lists (xs ys)
  (cond
    ((null xs) ys)
    ((null ys) xs)
    ((<= (car xs) (car ys))
     (cons (car xs) (merge-lists (cdr xs) ys)))
    (t (cons (car ys) (merge-lists xs (cdr ys))))))

(defun split-sequence (seq)
  (let* ((half (truncate (/ (length seq) 2)))
         (ys (subseq seq 0 half))
         (zs (subseq seq half)))
    (values ys zs)))

(defun mergesort (xs)
  (if (or (null xs) (null (cdr xs)))
      xs
      (multiple-value-bind (ys zs) (split-sequence xs)
        (merge-lists (mergesort ys) (mergesort zs)))))

(defun de (a b z)
  (labels ((extended-gcd (a b)
             (if (= a 0)
                 (values b 0 1)
                 (multiple-value-bind (g x y)
                     (extended-gcd (mod b a) a)
                   (values g (- y (* (floor b a) x)) x)))))
    (multiple-value-bind (g x y)
        (extended-gcd a b)
      (if (= z g)
          (values x y z)
          (error "No solution")))))

(defun prime-factors (n)
  (labels ((factor (n p)
             (cond
               ((> (* p p) n) (if (> n 1) (list n) nil))
               ((= (mod n p) 0) (cons p (factor (/ n p) p)))
               (t (factor n (1+ p))))))
    (factor n 2)))

(defun number-sequence (start end)
  (if (> start end)
      nil
      (cons start (number-sequence (1+ start) end))))

(defun totient (n)
  (length (remove-if-not (lambda (x) (= (gcd x n) 1)) (number-sequence 1 n))))

(defun totient2 (n)
  (let* ((factors (remove-duplicates (prime-factors n)))
         (result n))
    (dolist (p factors result)
      (setf result (* result (- 1 (/ 1.0 p)))))
    (floor result)))

(defun primes (n)
  (remove-if-not
   (lambda (p)
     (null (remove-if-not (lambda (x) (= (mod p x) 0))
                          (number-sequence 2 (isqrt p)))))
   (number-sequence 2 n)))

(defun main ()
  (format t "~a~%" (binomial 100 10))
  (format t "~a~%" (binomial2 100 10))
  (format t "~a~%" (mergesort '(10 22 18 12091 2 3 4 2 1 3)))
  (format t "~a~%" (multiple-value-list (de 25 20 5)))
  (format t "~a~%" (prime-factors 100))
  (format t "~a~%" (totient 50))
  (format t "~a~%" (totient2 50))
  (format t "~a~%" (primes 50)))

(main)
