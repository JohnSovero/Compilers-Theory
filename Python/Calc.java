import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

import java.io.FileInputStream;
import java.io.InputStream;

public class Calc {
    public static void main(String[] args) throws Exception {
        String inputFile = null;
        if (args.length > 0)
            inputFile = args[0];
        InputStream is = System.in;
        if (inputFile != null)
            is = new FileInputStream(inputFile);
        CharStream input = CharStreams.fromStream(is);

        PythonExprLexer lexer = new PythonExprLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        PythonExprParser parser = new PythonExprParser(tokens);
        ParseTree tree = parser.program();
        System.out.println(tree.toStringTree(parser));
        Visitor visitor = new Visitor();
        visitor.visit(tree);
    }
}