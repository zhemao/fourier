(defun list-seek (lst n)
  (if (= n 0) lst
    (list-seek (cdr lst) (- n 1))))

(defun range (start end &optional (s 1))
  (if (= start end) '()
    (cons start (range (+ start s) end))))

(defun fft-rec (tdom n s)
  (if (= n 1)
    (list (car tdom))
    (let ((evens (fft-rec tdom (/ n 2) (* 2 s)))
          (odds (fft-rec (list-seek tdom s) (/ n 2) (* 2 s)))
          (expconst (* -2 pi #C(0 1))))
      (append 
        (map 'list 
             (lambda (i e o) 
               (+ e (* (exp (* expconst (/ i n))) o)))
             (range 0 (/ n 2)) evens odds)
        (map 'list
             (lambda (i e o)
               (- e (* (exp (* expconst (/ i n))) o)))
             (range 0 (/ n 2)) evens odds)))))

(defun fft (tdom n)
  (fft-rec tdom n 1))

(defun ifft (fdom n)
  (let* ((fconj (map 'list #'conjugate fdom))
         (tdom (fft fconj n)))
    (map 'list (lambda (x) (/ x n)) tdom)))
