#!/usr/bin/bash 

setup(){ 
    local venvpath="$HOME/Compilers/env"

    # Verifica si el directorio del entorno virtual existe

    export MYDEPENDENCIES=$HOME/.m2/repository/org/antlr/antlr4/
    export LLVMDEPENDENCIES=$HOME/llvm/llvm-project/build

    export CLASSPATH=.:$MYDEPENDENCIES/4.13.1/antlr4-4.13.1-complete.jar:$CLASSPATH
    alias antlr4="java org.antlr.v4.Tool"
    alias grun='java org.antlr.v4.gui.TestRig'

    #source "${venvpath}/bin/activate"
    #export CLASSPATH=.:~/.m2/repository/org/antlr/antlr4/4.13.1/antlr4-4.13.1-complete.jar:$CLASSPATH
    export ANTLR4I=/usr/local/include/antlr4-runtime
    export ANTLR4L=/usr/local/lib/antlr4-runtime

    export LLVM17I=$LLVMDEPENDENCIES/include
	export LLVM17L=$LLVMDEPENDENCIES/lib
}


setup