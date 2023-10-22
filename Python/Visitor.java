import java.util.HashMap;
import java.util.Map;

public class Visitor extends PythonExprBaseVisitor<Integer> {
    Map<String, Integer> memory = new HashMap<String, Integer>();

    /* ID '=' expr NEWLINE */
    @Override
    public Integer visitAssign(PythonExprParser.AssignContext ctx) {
        String id = ctx.ID().getText();
        int value = visit(ctx.expr());
        System.out.println("id: " + id);
        System.out.println("value: " + value);
        memory.put(id, value);
        return value;
    }

    /* expr ('*'|'/') expr */
    @Override
    public Integer visitMulDiv(PythonExprParser.MulDivContext ctx) {
      int left = visit(ctx.expr(0));
      int right = visit(ctx.expr(1));
      if(ctx.op.getType() == PythonExprParser.MUL){
        return left * right;
      }
      else{
        return left / right;
      }
    }

    /* expr ('+'|'-') expr */
    @Override
    public Integer visitAddSub(PythonExprParser.AddSubContext ctx) {
      int left = visit(ctx.expr(0));
      int right = visit(ctx.expr(1));
      System.out.println("left: " + left + " right: " + right);
      if(ctx.op.getType() == PythonExprParser.ADD){
        return left + right;
      }
      else{
        return left - right;
      }
    }

    /* INT */
    @Override
    public Integer visitInt(PythonExprParser.IntContext ctx) {
      return Integer.valueOf(ctx.INT().getText());
    }

    /* ID */
    @Override
    public Integer visitId(PythonExprParser.IdContext ctx) {
      String id = ctx.ID().getText();
      if (memory.containsKey(id))
        return memory.get(id);
      // retornar error no existe la variable
      return 0;
    }

    /* '(' expr ')' */
    @Override
    public Integer visitParens(PythonExprParser.ParensContext ctx) {
      return visit(ctx.expr());
    }
}
