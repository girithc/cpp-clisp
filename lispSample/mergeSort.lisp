;;;; mergeSort
;;;;;;(mergeSort ( 9 8 7 6 3 1896 321 19763 134 986 976 1976 97 7))
;;idea mergeSort ((9)(8)(7)(6)(3)(1896)(321)(19763)(134)(986v)(976)(1976)(97)(7))
(define mergeSort(list) ( cond 
	(nil? list) list
	(nil? (cdr list)) list
	(atom? car a) ;initialcall--build a list of list and sort that
		(mergeSort ( cons (cons (car list) ()) (mergeSort( cdr list))))
	(nil? (cdr list)) (car list) ; done reached a single list,it is sorted 
	;we have at least two sub-list
	(mergeSort 
		(	cons 
				(merge(car list) (car (cdr list))) 
				(mergeSort (cdr (cdr list))) 
		)
	)
))
;merge two list
(define merge (a b) ( cond 
   (nil? a) b
   (nil? b) a
   (lte? (car a) (car b))
       (cons (car a) (merge (cdr a) b))
    't (cons (car b) (merge (cdr b) a))
))

(define sum (a b)
	(print a)
)