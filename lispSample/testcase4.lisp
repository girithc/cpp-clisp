(define fun(tree x)
    (cond 
    (nil? tree)(cons x (cons ()()) )
    (> x (car tree)) (cons (car tree) (cons  (car (cdr tree)) (fun (cdr (cdr tree)) x) ) ) 
    (<= x (car tree)) (cons  (fun  (car (cdr tree))  x) tree)    
    )
)

(set a (cons () ()))
(set b (cons 2 a))
(print (fun b 4))
