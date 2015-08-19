from    triton import *
import  smt2lib

X_ADDR = 0x600C3C
Y_ADDR = 0x600C40

def csym(instruction):
    return



def cafter(instruction):
    if len(instruction.getOperands()) == 2 and instruction.getOperands()[1].getType() == IDREF.OPERAND.MEM_R and (instruction.getOperands()[1].getMem().getAddress() == X_ADDR or instruction.getOperands()[1].getMem().getAddress() == Y_ADDR):
        reg = instruction.getOperands()[0].getReg()
        convertRegToSymVar(reg.getId(), 64)
    return


def cbefore(instruction):
    if instruction.isBranch():
        zfId    = getRegSymbolicID(IDREF.FLAG.ZF)
        zfExpr  = getFullExpression(getSymExpr(zfId).getAst())
        expr    = smt2lib.smtAssert(smt2lib.equal(zfExpr, smt2lib.bvtrue())) # (assert (= zf True))
        modelsTrue  = getModel(expr)
        expr    = smt2lib.smtAssert(smt2lib.equal(zfExpr, smt2lib.bvfalse())) # (assert (= zf True))
        modelsFalse  = getModel(expr)
        if len(modelsTrue) > 0 or len(modelsFalse) > 0:
            print instruction.getDisassembly()

    return

def fini():
    print '[+] Analysis done!'


if __name__ == '__main__':

    # Start the symbolic analysis from the 'check' function
    startAnalysisFromSymbol('main')

    addCallback(cafter,         IDREF.CALLBACK.AFTER)
    addCallback(cbefore,        IDREF.CALLBACK.BEFORE)
    addCallback(csym,           IDREF.CALLBACK.BEFORE_SYMPROC)
    addCallback(fini,           IDREF.CALLBACK.FINI)

    # Run the instrumentation - Never returns
    runProgram()


