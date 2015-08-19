from    triton import *
import  smt2lib

X_ADDR = 0x60204C
Y_ADDR = 0x602050

def csym(instruction):
    return



def cafter(instruction):
    if len(instruction.getOperands()) == 2 and instruction.getOperands()[1].getType() == IDREF.OPERAND.MEM_R and (instruction.getOperands()[1].getMem().getAddress() == X_ADDR or instruction.getOperands()[1].getMem().getAddress() == Y_ADDR):
        reg = instruction.getOperands()[0].getReg()
        convertRegToSymVar(reg.getId(), 64)
    return


def cbefore(instruction):
    if instruction.getAddress() == 0x4008A0:
        zfId    = getRegSymbolicID(IDREF.REG.RAX)
        zfExpr  = getFullExpression(getSymExpr(zfId).getAst())
        print zfExpr
        expr    = smt2lib.smtAssert(smt2lib.bvsgt(zfExpr, smt2lib.bv(0, 64))) # (assert (= zf True))
        models  = getModel(expr)
        print models

    return

def fini():
    print '[+] Analysis done!'


if __name__ == '__main__':

    # Start the symbolic analysis from the 'check' function
    startAnalysisFromSymbol('check')

    addCallback(cafter,         IDREF.CALLBACK.AFTER)
    addCallback(cbefore,        IDREF.CALLBACK.BEFORE)
    addCallback(csym,           IDREF.CALLBACK.BEFORE_SYMPROC)
    addCallback(fini,           IDREF.CALLBACK.FINI)

    # Run the instrumentation - Never returns
    runProgram()


