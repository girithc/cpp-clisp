(define fun(a b) 
    (cond 
    (> a b)(print a)
    (<= a b)(fun (+ 2 a) b))
)

(fun 2 40)