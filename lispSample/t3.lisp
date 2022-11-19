(define factorial(a)
    (cond
    (= a 0)(+ 1 0))
    (* a (factorial (- a 1)))
)

(print (factorial 4))
(print (factorial 14))