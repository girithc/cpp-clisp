(define fun (a b)
    (print  (cdr (cons (cons a b) (cons b a)) ))
    (car a)
    (car b)
)

(fun "yes" "no")