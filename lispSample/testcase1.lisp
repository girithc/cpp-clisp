(set a ())

(cond
(nil? a)(print "a is nil")
(number? a)(print "a is a number")
(symbol? a)(print "a is a symbol")
(list? a)(print "a is a list"))

(set a 2)

(cond
(nil? a)(print "a is nil")
(number? a)(print "a is a number")
(symbol? a)(print "a is a symbol")
(list? a)(print "a is a list"))

(set a "two")

(cond
(nil? a)(print "a is nil")
(number? a)(print "a is a number")
(symbol? a)(print "a is a symbol")
(list? a)(print "a is a list"))


(set a (cons () "two"))

(cond
(nil? a)(print "a is nil")
(number? a)(print "a is a number")
(symbol? a)(print "a is a symbol")
(list? a)(print "a is a list"))

