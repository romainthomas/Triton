#include "../init.hpp"

#include <api.hpp>
#include <bitsVector.hpp>
#include <cpuSize.hpp>
#include <immediateOperand.hpp>
#include <memoryOperand.hpp>
#include <registerOperand.hpp>

#ifdef __unix__
  #include <python2.7/Python.h>
#elif _WIN32
  #include <Python.h>
#endif

void init_Triton_Callbacks(py::module& m) {

  m.def("assignSymbolicExpressionToMemory",
      [] (triton::engines::symbolic::SymbolicExpression* se, triton::arch::MemoryOperand& mem)
      {
        triton::api.assignSymbolicExpressionToMemory(se, mem);
      }, py::arg("se"), py::arg("mem"));


  m.def("assignSymbolicExpressionToRegister",
      [] (triton::engines::symbolic::SymbolicExpression* se, triton::arch::RegisterOperand& reg)
      {
        triton::api.assignSymbolicExpressionToRegister(se, reg);
      }, py::arg("se"), py::arg("reg"));


  m.def("buildSemantics",
      [] (triton::arch::Instruction& inst)
      {
        triton::api.buildSemantics(inst);
      }, py::arg("instruction"));


  m.def("buildSymbolicImmediate",
      [] (triton::arch::ImmediateOperand& imm)
      {
        return triton::api.buildSymbolicImmediateOperand(imm);
      }, py::arg("imm"));


  m.def("buildSymbolicMemory",
      [] (triton::arch::MemoryOperand& mem)
      {
        return triton::api.buildSymbolicMemoryOperand(mem);
      }, py::arg("mem"));


  m.def("buildSymbolicRegister",
      [] (triton::arch::RegisterOperand& reg)
      {
        return triton::api.buildSymbolicRegisterOperand(reg);
      }, py::arg("reg"));


  m.def("clearPathConstraints",
      [] (void)
      {
        triton::api.clearPathConstraints();
      });

  m.def("concretizeAllMemory",
      [] (void)
      {
        triton::api.concretizeAllMemory();
      });


  m.def("concretizeMemory",
      [] (triton::__uint addr)
      {
        triton::api.concretizeMemory(addr);
      }, py::arg("addr"));


  m.def("concretizeMemory",
      [] (triton::arch::MemoryOperand& mem)
      {
        triton::api.concretizeMemory(mem);
      }, py::arg("mem"));


  m.def("concretizeRegister",
      [] (triton::arch::RegisterOperand& reg)
      {
        triton::api.concretizeRegister(reg);
      }, py::arg("reg"));


  m.def("convertExpressionToSymbolicVariable",
      [] (triton::__uint exprId, triton::uint32 symVarSize, std::string symVarComment)
      {
        return triton::api.convertExpressionToSymbolicVariable(exprId, symVarSize, symVarComment);
      }, py::arg("exprId"), py::arg("symVarSize"), py::arg("symVarComment"));


  m.def("convertMemoryToSymbolicVariable",
      [] (triton::arch::MemoryOperand mem, std::string symVarComment)
      {
        return triton::api.convertMemoryToSymbolicVariable(mem, symVarComment);
      }, py::arg("mem"), py::arg("symVarComment"));


  m.def("convertRegisterToSymbolicVariable",
      [] (triton::arch::RegisterOperand reg, std::string symVarComment)
      {
        return triton::api.convertRegisterToSymbolicVariable(reg, symVarComment);
      }, py::arg("reg"), py::arg("symVarComment"));


  m.def("cpuInvalidRegister",
      [] (void)
      {
        return triton::api.cpuInvalidRegister();
      });


  m.def("cpuNumberOfRegisters",
      [] (void)
      {
        return triton::api.cpuNumberOfRegisters();
      });


  m.def("cpuRegisterBitSize",
      [] (void)
      {
        return triton::api.cpuRegisterBitSize();
      });


  m.def("cpuRegisterSize",
      [] (void)
      {
        return triton::api.cpuRegisterSize();
      });


  m.def("createSymbolicFlagExpression",
      [] (triton::arch::Instruction& inst, triton::ast::AbstractNode* node, triton::arch::RegisterOperand& flag, std::string comment)
      {
        return triton::api.createSymbolicFlagExpression(inst, node, flag, comment);
      }, py::arg("inst"), py::arg("node"), py::arg("flag"), py::arg("comment"));


  m.def("createSymbolicMemoryExpression",
      [] (triton::arch::Instruction& inst, triton::ast::AbstractNode* node, triton::arch::MemoryOperand& mem, std::string comment)
      {
        return triton::api.createSymbolicMemoryExpression(inst, node, mem, comment);
      }, py::arg("inst"), py::arg("node"), py::arg("mem"), py::arg("comment"));


  m.def("createSymbolicRegisterExpression",
      [] (triton::arch::Instruction& inst, triton::ast::AbstractNode* node, triton::arch::RegisterOperand& reg, std::string comment)
      {
        return triton::api.createSymbolicRegisterExpression(inst, node, reg, comment);
      }, py::arg("inst"), py::arg("node"), py::arg("reg"), py::arg("comment"));


  m.def("createSymbolicVolatileExpression",
      [] (triton::arch::Instruction& inst, triton::ast::AbstractNode* node, std::string comment)
      {
        return triton::api.createSymbolicVolatileExpression(inst, node, comment);
      }, py::arg("inst"), py::arg("node"), py::arg("comment"));


  //TODO: Remove and place in Instruction Class
  m.def("disassembly",
      [] (triton::arch::Instruction& inst)
      {
        return triton::api.disassembly(inst);
      }, py::arg("inst"));


  m.def("enableSymbolicEmulation",
      [] (bool flag)
      {
        triton::api.enableSymbolicEmulation(flag);
      }, py::arg("flag"));


  m.def("enableSymbolicEngine",
      [] (bool flag)
      {
        triton::api.enableSymbolicEngine(flag);
      }, py::arg("flag"));


  m.def("enableSymbolicOptimization",
      [] (enum triton::engines::symbolic::optimization_e opti, bool flag)
      {
        triton::api.enableSymbolicOptimization(static_cast<enum triton::engines::symbolic::optimization_e>(opti), flag);
      }, py::arg("opti"), py::arg("flag"));


  m.def("enableSymbolicZ3Simplification",
      [] (bool flag)
      {
        triton::api.enableSymbolicZ3Simplification(flag);
      }, py::arg("flag"));


  m.def("enableTaintEngine",
      [] (bool flag)
      {
        triton::api.enableTaintEngine(flag);
      }, py::arg("flag"));


  m.def("evaluateAstViaZ3",
      [] (triton::ast::AbstractNode *node)
      {
        return triton::api.evaluateAstViaZ3(node);
      }, py::arg("node"));


  m.def("getAllRegisters",
      [] (void)
      {
        throw std::runtime_error("TODO");
        return 0;
      });


  m.def("getArchitecture",
      [] (void)
      {
        return triton::api.getArchitecture();
      });


  m.def("getAstFromId",
      [] (triton::__uint symExprId)
      {
        return triton::api.getAstFromId(symExprId);
      }, py::arg("id"));


  m.def("getAstRepresentationMode",
      [] (void)
      {
        return triton::api.getAstRepresentationMode();
      });


  m.def("getAstDictionariesStats",
      [] (void)
      {
        throw std::runtime_error("TODO");
      });


  m.def("getFullAst",
      [] (triton::ast::AbstractNode* node)
      {
        return triton::api.getFullAst(node);
      }, py::arg("node"));


  m.def("getFullAstFromId",
      [] (triton::__uint symExprId)
      {
        return triton::api.getFullAstFromId(symExprId);
      }, py::arg("id"));


  m.def("getMemoryAreaValue",
      [] (void)
      {
        throw std::runtime_error("TODO");
      });


  m.def("getMemoryValue",
      [] (triton::arch::MemoryOperand& mem)
      {
        return triton::api.getMemoryValue(mem);
      }, py::arg("mem"));


  m.def("getMemoryValue",
      [] (triton::__uint addr)
      {
        return triton::api.getMemoryValue(addr);
      }, py::arg("addr"));


  m.def("getModel",
      [] (void)
      {
        throw std::runtime_error("TODO");
      });


  m.def("getModels",
      [] (void)
      {
        throw std::runtime_error("TODO");
      });


  m.def("getParentRegisters",
      [] (void)
      {
        throw std::runtime_error("TODO");
      });


  m.def("getPathConstraints",
      [] (void)
      {
        throw std::runtime_error("TODO");
      });


  m.def("getPathConstraintsAst",
      [] (void)
      {
        return triton::api.getPathConstraintsAst();
      });


  m.def("getRegisterValue",
      [] (triton::arch::RegisterOperand& reg)
      {
        return triton::api.getRegisterValue(reg);
      }, py::arg("reg"));


  m.def("getSymbolicExpressionFromId",
      [] (triton::__uint symExprId)
      {
        return triton::api.getSymbolicExpressionFromId(symExprId);
      }, py::arg("reg"));


  m.def("getSymbolicExpressions",
      [] (void)
      {
        return triton::api.getSymbolicExpressions();
      });


  m.def("getSymbolicMemory",
      [] (void)
      {
        return triton::api.getSymbolicMemory();
      });


  m.def("getSymbolicMemoryId",
      [] (triton::__uint addr)
      {
        return triton::api.getSymbolicMemoryId(addr);
      }, py::arg("addr"));


  m.def("getSymbolicMemoryValue",
      [] (triton::arch::MemoryOperand& mem)
      {
        return triton::api.getSymbolicMemoryValue(mem);
      }, py::arg("mem"));


  m.def("getSymbolicMemoryValue",
      [] (triton::__uint address)
      {
        return triton::api.getSymbolicMemoryValue(address);
      }, py::arg("addr"));


  m.def("getSymbolicRegisters",
      [] (void)
      {
        return triton::api.getSymbolicRegisters();
      });


  m.def("getSymbolicRegisterId",
      [] (triton::arch::RegisterOperand& reg)
      {
        return triton::api.getSymbolicRegisterId(reg);
      }, py::arg("reg"));


  m.def("getSymbolicRegisterValue",
      [] (triton::arch::RegisterOperand& reg)
      {
        return triton::api.getSymbolicRegisterValue(reg);
      }, py::arg("reg"));
















  m.def("setArchitecture", [] (triton::uint32 arch)
      {
        triton::api.setArchitecture(arch);
      },
      py::arg("arch"));
}
