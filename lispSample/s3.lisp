(define fun(tree x)
    (print tree)
    
    (cond 
    (nil? tree)(cons x (cons ()()) )
    (> x (car tree)) (cons (car tree) (cons  (car (cdr tree)) (fun (cdr (cdr tree)) x) ) ) 
    (<= x (car tree)) (cons  (fun  (car (cdr tree))  x) tree)
    //(cons  (fun  (car (cdr tree))  x) (cdr (cdr tree)) ) )        
    )
    (print "tree is not nil")
)


(set a (cons () ()))
(set b (cons 2 a))
(print (fun b 1))

//(print (cons (car tree) (cons  (fun  (car (cdr tree))  x) (cdr (cdr tree)) ) ))