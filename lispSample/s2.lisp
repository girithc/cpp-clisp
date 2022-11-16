(define fun (a b)
    //(print  (cdr (cons (cons a b) (cons b a)) ))
    //(number? a)
    //(print "World")
    //(cons a b)
    //(car b)
    //(car a)
    (cond
    (> a b)(print "a is greater than b")
    (< a b)(print "a is less than b"))
    (print a)
)

//(print (fun "yes" "no"))
(set a "A")
(print (list? a))
(cond
(< 1 1)(print 1)
(= 2 2)(set b (cons a a))
)
(print b)
(fun 1 2)




//(print "hello")
//(print (- 4 5))
//(set a "2")
//(print a)
//(set b (cons a a))
//(print b)
//(set c (cons a b))
//(print c)
//(print (cons c a))