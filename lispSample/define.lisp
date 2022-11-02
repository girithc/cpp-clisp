(define merge (a b) ( cond 
   (nil? a) b
   (nil? b) a
   (lte? (car a) (car b))
       (cons (car a) (merge (cdr a) b))
    't (cons (car b) (merge (cdr b) a))
))