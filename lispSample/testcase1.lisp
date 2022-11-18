(set a ())
(set b 2)
(set c "two")
(set d (cons b c))
(cond
(nil? a)(print "a is nil"))
(cond
(number? b)(print "b is a number"))
(cond
(symbol? c)(print "c is a symbol"))
(cond
(list? d)(print "d is a list"))

