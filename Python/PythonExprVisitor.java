// Generated from PythonExpr.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link PythonExprParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface PythonExprVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link PythonExprParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(PythonExprParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link PythonExprParser#def}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDef(PythonExprParser.DefContext ctx);
	/**
	 * Visit a parse tree produced by {@link PythonExprParser#block}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlock(PythonExprParser.BlockContext ctx);
	/**
	 * Visit a parse tree produced by {@link PythonExprParser#simple_stmts}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSimple_stmts(PythonExprParser.Simple_stmtsContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Assign}
	 * labeled alternative in {@link PythonExprParser#stat}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssign(PythonExprParser.AssignContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Expression}
	 * labeled alternative in {@link PythonExprParser#stat}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression(PythonExprParser.ExpressionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Function}
	 * labeled alternative in {@link PythonExprParser#stat}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction(PythonExprParser.FunctionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code CallFunction}
	 * labeled alternative in {@link PythonExprParser#stat}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCallFunction(PythonExprParser.CallFunctionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Blank}
	 * labeled alternative in {@link PythonExprParser#stat}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlank(PythonExprParser.BlankContext ctx);
	/**
	 * Visit a parse tree produced by the {@code MulDiv}
	 * labeled alternative in {@link PythonExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMulDiv(PythonExprParser.MulDivContext ctx);
	/**
	 * Visit a parse tree produced by the {@code AddSub}
	 * labeled alternative in {@link PythonExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAddSub(PythonExprParser.AddSubContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Parens}
	 * labeled alternative in {@link PythonExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParens(PythonExprParser.ParensContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Id}
	 * labeled alternative in {@link PythonExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitId(PythonExprParser.IdContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Int}
	 * labeled alternative in {@link PythonExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInt(PythonExprParser.IntContext ctx);
	/**
	 * Visit a parse tree produced by {@link PythonExprParser#func}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunc(PythonExprParser.FuncContext ctx);
}