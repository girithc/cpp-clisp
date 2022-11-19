#include "scanner.cpp"

void testCase1()
{
    /*
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

    */
   ofstream testFile;
    testFile.open("test/tempTestCase1.txt");


    string code = "(set a ())";
    code.append("\n");
    code.append("(cond");
    code.append("\n");
    //code2.append("  eat() {");
    code.append("(nil? a)(print \"a is nil\")");
    code.append("\n");
    //code2.append("    return \"eating Waffles\";");
    code.append("(number? a)(print \"a is a number\")");
    code.append("\n");
    code.append("(symbol? a)(print \"a is a symbol\")");
    code.append("\n");
    code.append("(list? a)(print \"a is a list\"))");
    code.append("\n");
    code.append("(set a 2)");
    code.append("\n");
    //code2.append("sayHi(\"Girith\", \"Choudhary\", \"m\");");
    code.append("(cond");
    code.append("\n");
    code.append("(nil? a)(print \"a is nil\")");
    code.append("\n");
    code.append("(number? a)(print \"a is a number\")");
    code.append("\n");
    code.append("(symbol? a)(print \"a is a symbol\")");
    code.append("\n");
    code.append("(list? a)(print \"a is a list\"))");
    code.append("\n");

    code.append("(set a \"two\")");
    code.append("\n");
    code.append("(cond");
    code.append("\n");
    //code2.append("  eat() {");
    code.append("(nil? a)(print \"a is nil\")");
    code.append("\n");
    //code2.append("    return \"eating Waffles\";");
    code.append("(number? a)(print \"a is a number\")");
    code.append("\n");
    code.append("(symbol? a)(print \"a is a symbol\")");
    code.append("\n");
    code.append("(list? a)(print \"a is a list\"))");
    code.append("\n");
    code.append("(set a (cons () \"two\"))");
    code.append("\n");
    //code2.append("sayHi(\"Girith\", \"Choudhary\", \"m\");");
    code.append("(cond");
    code.append("\n");
    code.append("(nil? a)(print \"a is nil\")");
    code.append("\n");
    code.append("(number? a)(print \"a is a number\")");
    code.append("\n");
    code.append("(symbol? a)(print \"a is a symbol\")");
    code.append("\n");
    code.append("(list? a)(print \"a is a list\"))");
    code.append("\n");

    
    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());
    //cout << code << endl << endl;
    string lisp = "lisp>";
    cout << "testCase1()" << endl;

    LispScanner lispScanner(code);
    list<Token> testTokens = lispScanner.scanTokens();

    lispParser lispParser(testTokens);
    list<Stmt*> stmts = lispParser.parse();

    lispInterpreter* interpreter = new lispInterpreter(stmts);
    interpreter->interpret();

    testFile.close();

    cout.rdbuf(oldCout);
    ifstream rdFile;
    ofstream wrFile;

    string line;
    rdFile.open("test/tempTestCase1.txt");
    wrFile.open("test/testCase1.txt");


    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    //cout << "Hello World" << line << endl;
        
    getline(rdFile, line);
    assert(line.substr(lisp.length()) == "[ (a is nil) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (a is nil) ]" << endl;

    getline(rdFile, line);
    assert(line.substr(lisp.length()) == "[ (a is a number) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (a is a number) ]" << endl;

    getline(rdFile, line);
    //cout << line << endl;
    assert(line.substr(lisp.length()) == "[ (a is a symbol) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (a is a symbol) ]" << endl;

    getline(rdFile, line);
    assert(line.substr(lisp.length()) == "[ (a is a list) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (a is a list) ]" << endl;

    wrFile << endl << endl;
    rdFile.close();
    remove("test/tempTestCase1.txt");

}


void testCase2()
{
        /*
        (set a 2)
        (set b 4)
        (set c (cons a b))
        (set d (cons c 6))
        (print d)
        (print (car d))
        (print (cdr d))
        (print (cdr (cdr d)))
        */
    
   ofstream testFile;
    testFile.open("test/tempTestCase2.txt");


    string code = "(set a 2)";
    code.append("\n");
    code.append("(set b 4)");
    code.append("\n");
    code.append("(set c (cons a b))");
    code.append("\n");
    code.append("(set d (cons c 6))");
    code.append("\n");
    code.append("(print d)");
    code.append("\n");
    code.append("(print (car d))");
    code.append("\n");
    code.append("(print (cdr d))");
    code.append("\n");
    code.append("(print (cdr (cdr d)))");
    code.append("\n");
    


    
    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());
    //cout << code << endl << endl;
    string lisp = "lisp>";
    cout << "testCase2()" << endl;

    LispScanner lispScanner(code);
    list<Token> testTokens = lispScanner.scanTokens();

    lispParser lispParser(testTokens);
    list<Stmt*> stmts = lispParser.parse();

    lispInterpreter* interpreter = new lispInterpreter(stmts);
    interpreter->interpret();

    testFile.close();

    cout.rdbuf(oldCout);
    ifstream rdFile;
    ofstream wrFile;

    string line;
    rdFile.open("test/tempTestCase2.txt");
    wrFile.open("test/testCase2.txt");


    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    //cout << "Hello World" << line << endl;
        
    getline(rdFile, line);
    //cout << "Hello World1" << line << endl;
    
    assert(line.substr(lisp.length()) == "[( (2)  (4) ) (6) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[( (2)  (4) ) (6) ]" << endl;
    
    //cout << "Hello World" << line << endl;

    getline(rdFile, line);
    assert(line.substr(lisp.length()) == "[ (2)  (4) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (2)  (4) ]" << endl;

    getline(rdFile, line);
    //cout << line << endl;
    assert(line.substr(lisp.length()) == "[ (6) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (6) ]" << endl;

    getline(rdFile, line);
    assert(line.substr(lisp.length()) == "[]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[]" << endl;

    wrFile << endl << endl;
    rdFile.close();
    remove("test/tempTestCase2.txt");


}

void testCase3()
{
    /*
    (define factorial(a)
    (cond
    (= a 0)(+ 1 0))
    (* a (factorial (- a 1)))
)

(print (factorial 4))
(print (factorial 14))
    */
    ofstream testFile;
    testFile.open("test/tempTestCase3.txt");


    string code = "(define factorial(a)";
    code.append("\n");
    code.append("(cond");
    code.append("\n");
    code.append("(= a 0)(+ 1 0))");
    code.append("\n");
    code.append("(* a (factorial (- a 1)))");
    code.append("\n");
    code.append(")");
    code.append("\n");
    code.append("(print (factorial 4))");
    code.append("\n");
    code.append("(print (factorial 14))");
    code.append("\n");

    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());
    //cout << code << endl << endl;
    string lisp = "lisp>";
    cout << "testCase3()" << endl;

    LispScanner lispScanner(code);
    list<Token> testTokens = lispScanner.scanTokens();

    lispParser lispParser(testTokens);
    list<Stmt*> stmts = lispParser.parse();

    lispInterpreter* interpreter = new lispInterpreter(stmts);
    interpreter->interpret();

    testFile.close();

    cout.rdbuf(oldCout);
    ifstream rdFile;
    ofstream wrFile;

    string line;
    rdFile.open("test/tempTestCase3.txt");
    wrFile.open("test/testCase3.txt");


    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    //cout << "Hello World" << line << endl;
        
    getline(rdFile, line);
    //cout << "Hello World1" << line << endl;
    
    assert(line.substr(lisp.length()) == "[ (24.000000) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (24.000000) ]" << endl;
    
    //cout << "Hello World" << line << endl;

    getline(rdFile, line);
    assert(line.substr(lisp.length()) == "[ (87178291200.000000) ]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (87178291200.000000) ]" << endl;

    wrFile << endl << endl;
    rdFile.close();
    remove("test/tempTestCase3.txt");
}

void testCase4()
{
    /*
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
        */
    ofstream testFile;
    testFile.open("test/tempTestCase4.txt");


    string code = "(define binTree(tree x)";
    code.append("\n");
    code.append("(cond ");
    code.append("\n");
    code.append("(nil? tree)(cons x (cons ()()) )");
    code.append("\n");
    code.append("(> x (car tree)) (cons (car tree) (cons  (car (cdr tree)) (binTree (cdr (cdr tree)) x) ) ) ");
    code.append("\n");
    code.append("(<= x (car tree)) (cons  (binTree  (car (cdr tree))  x) tree)    ");
    code.append("\n");
    code.append("))");
    code.append("\n");
    code.append("(set a ())");
    code.append("\n");
    code.append("(set b (binTree a 2))");
    code.append("\n");
    code.append("(print b)");
    code.append("\n");
    code.append("(print (binTree b 4))");
    code.append("\n");

    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());
    //cout << code << endl << endl;
    string lisp = "lisp>";
    cout << "testCase4()" << endl;

    LispScanner lispScanner(code);
    list<Token> testTokens = lispScanner.scanTokens();

    lispParser lispParser(testTokens);
    list<Stmt*> stmts = lispParser.parse();

    lispInterpreter* interpreter = new lispInterpreter(stmts);
    interpreter->interpret();

    testFile.close();

    cout.rdbuf(oldCout);
    ifstream rdFile;
    ofstream wrFile;

    string line;
    rdFile.open("test/tempTestCase4.txt");
    wrFile.open("test/testCase4.txt");


    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    //cout << "Hello World" << line << endl;
        
    getline(rdFile, line);
    //cout << "Hello World1" << line << endl;
    
    assert(line.substr(lisp.length()) == "[ (2) ((())(()))]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (2) ((())(()))]" << endl;
    
    //cout << "Hello World" << line << endl;

    getline(rdFile, line);
    assert(line.substr(lisp.length()) == "[ (2) ((())( (4) ((())(()))))]");
    wrFile << "Test passed: (" << line.substr(lisp.length()) << ") = " << "[ (2) ((())( (4) ((())(()))))]" << endl;

    wrFile << endl << endl;
    rdFile.close();
    remove("test/tempTestCase4.txt");
}


void testLispInterpreter()
{
    testCase1();
    testCase2();
    testCase3();
    testCase4();
}