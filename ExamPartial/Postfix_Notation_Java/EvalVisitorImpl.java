import java.util.HashMap;
import java.util.Map;

/* added the Impl at the end of the class to avoid it being .gitignored sorry */
public class EvalVisitorImpl extends LabeledExprBaseVisitor<Integer> {
	Map<String, Integer> memory = new HashMap<String, Integer>();

	/* ID '=' expr NEWLINE */
	@Override
	public Integer visitAssign(LabeledExprParser.AssignContext ctx) {
		String id = ctx.ID().getText();
		int value = visit(ctx.expr());
		System.out.println("id: " + id);
		System.out.println("value: " + value);
		memory.put(id, value);
		return value;
		
	}

	/* expr NEWLINE */
	@Override
	public Integer visitPrintExpr(LabeledExprParser.PrintExprContext ctx) {
		Integer value = visit(ctx.expr());
		System.out.println(value);
		return 0;
	}

	/* INT */
	@Override
	public Integer visitInt(LabeledExprParser.IntContext ctx) {
		return Integer.valueOf(ctx.INT().getText());
	}

	/* ID */
	@Override
	public Integer visitId(LabeledExprParser.IdContext ctx) {
		String id = ctx.ID().getText();
		if (memory.containsKey(id)) 
			return memory.get(id);
		//retornar error no existe la variable
		return 0;
	}

	/* expr expr op = ('*' | '/') */
	@Override
	public Integer visitMulDiv(LabeledExprParser.MulDivContext ctx) {
		int left = visit(ctx.expr(0));
		int right = visit(ctx.expr(1));
		if (ctx.op.getType() == LabeledExprParser.MUL) {
			return left * right;
		} else {
			return left / right;
		}
	}

	/* expr expr op = ('+' | '-') */
	@Override
	public Integer visitAddSub(LabeledExprParser.AddSubContext ctx) {
		int left = visit(ctx.expr(0));
		int right = visit(ctx.expr(1));
		if (ctx.op.getType() == LabeledExprParser.ADD) {
			return left + right;
		} else {
			return left - right;
		}
	}

	/* expr expr op = ('%' | '^') expr */
	@Override
	public Integer visitModPow(LabeledExprParser.ModPowContext ctx) {
		int left = visit(ctx.expr(0));
		int right = visit(ctx.expr(1));
		if (ctx.op.getType() == LabeledExprParser.MOD) {
			return left % right;
		} else {
			return (int) Math.pow(left, right);
		}
	}

	/* '(' expr ')' */
	@Override
	public Integer visitParens(LabeledExprParser.ParensContext ctx) {
		return visit(ctx.expr());
	}
}