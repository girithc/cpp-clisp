(define fun(tree x)
    (cond 
    (nil? tree)(cons x (cons ()()) )
    (> x (car tree)) (cons (car tree) (cons  (car (cdr tree)) (fun (cdr (cdr tree)) x) ) ) 
    (<= x (car tree)) (cons  (fun  (car (cdr tree))  x) tree)    
    )
)

(set a ())
(set b (fun a 2))
(print b)
(print (fun b 4))