(define fun(a b)
    (print b)
    (cond
    (> a b)(print (cons (fun (+ 1 a) (* 3 b)) b))
    (<= a b)(cons a b))
)

(fun 2 1)
(print a)
(set a 42)
(print a)