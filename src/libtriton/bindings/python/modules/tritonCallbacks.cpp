#include "../init.hpp"

#include <api.hpp>
#include <bitsVector.hpp>
#include <cpuSize.hpp>
#include <immediateOperand.hpp>
#include <memoryOperand.hpp>
#include <registerOperand.hpp>
#include <ast.hpp>

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



  m.def("getSymbolicVariableFromId",
      [] (triton::__uint symVarId)
      {
        return triton::api.getSymbolicVariableFromId(symVarId);
      }, py::arg("symVarId"));


  m.def("getSymbolicVariableFromName",
      [] (std::string& symVarName)
      {
        return triton::api.getSymbolicVariableFromName(symVarName);
      }, py::arg("symVarName"));


  m.def("getSymbolicVariables",
      [] (void)
      {
        return triton::api.getSymbolicVariables();
      });


  m.def("getTaintedSymbolicExpressions",
      [] (void)
      {
        return triton::api.getTaintedSymbolicExpressions();
      });


  m.def("isMemoryTainted",
      [] (triton::__uint addr)
      {
        return triton::api.isMemoryTainted(addr);
      }, py::arg("addr"));


  m.def("isArchitectureValid",
      [] (void)
      {
        return triton::api.isArchitectureValid();
      });


  m.def("isMemoryTainted",
      [] (triton::arch::MemoryOperand& mem)
      {
        return triton::api.isMemoryTainted(mem);
      }, py::arg("mem"));


  m.def("isRegisterTainted",
      [] (triton::arch::RegisterOperand& reg)
      {
        return triton::api.isRegisterTainted(reg);
      }, py::arg("reg"));



  m.def("isSymbolicEngineEnabled",
      [] (void)
      {
        return triton::api.isSymbolicEngineEnabled();
      });


  m.def("isSymbolicOptimizationEnabled",
      [] (enum triton::engines::symbolic::optimization_e opti)
      {
        return triton::api.isSymbolicOptimizationEnabled(static_cast<enum triton::engines::symbolic::optimization_e>(opti));
      }, py::arg("opti"));


  m.def("isTaintEngineEnabled",
      [] (void)
      {
        return triton::api.isTaintEngineEnabled();
      });


  m.def("isTaintEngineEnabled",
      [] (void)
      {
        return triton::api.isTaintEngineEnabled();
      });


  m.def("processing",
      [] (triton::arch::Instruction& inst)
      {
        return triton::api.processing(inst);
      }, py::arg("inst"));


  //m.def("recordSimplificationCallback",
  //    [] (triton::engines::symbolic::sfp cb)
  //    {
  //      triton::api.recordSimplificationCallback(cb);
  //    }, py::arg("cb"));


  ////TODO: Python argument


  //m.def("removeSimplificationCallback",
  //    [] (triton::engines::symbolic::sfp cb)
  //    {
  //      triton::api.removeSimplificationCallback(cb);
  //    }, py::arg("cb"));


  m.def("resetEngines",
      [] (void)
      {
        triton::api.resetEngines();
      });


  m.def("setArchitecture",
      [] (triton::uint32 arch)
      {
        triton::api.setArchitecture(arch);
      },
      py::arg("arch"));


  m.def("setLastMemoryValue",
      [] (triton::__uint addr, triton::uint8 value)
      {
        triton::api.setLastMemoryValue(addr, value);
      },
      py::arg("addr"), py::arg("value"));


  m.def("setLastMemoryValue",
      [] (triton::arch::MemoryOperand& mem)
      {
        triton::api.setLastMemoryValue(mem);
      },
      py::arg("mem"));


  m.def("setLastRegisterValue",
      [] (triton::arch::RegisterOperand& reg)
      {
        triton::api.setLastRegisterValue(reg);
      },
      py::arg("reg"));


  m.def("setTaintMemory",
      [] (triton::arch::MemoryOperand& mem, bool flag)
      {
        return triton::api.setTaintMemory(mem, flag);
      },
      py::arg("mem"), py::arg("flag"));


  m.def("setTaintRegister",
      [] (triton::arch::RegisterOperand& reg, bool flag)
      {
        return triton::api.setTaintRegister(reg, flag);
      },
      py::arg("reg"), py::arg("flag"));


  m.def("simplify",
      [] (triton::ast::AbstractNode* node)
      {
        return triton::api.processSimplification(node);
      },
      py::arg("node"));


  m.def("taintMemory",
      [] (triton::__uint addr)
      {
        return triton::api.taintMemory(addr);
      },
      py::arg("addr"));


  m.def("taintAssignmentMemoryImmediate",
      [] (triton::arch::MemoryOperand& memDst)
      {
        return triton::api.taintAssignmentMemoryImmediate(memDst);
      },
      py::arg("memDst"));


  m.def("taintAssignmentMemoryMemory",
      [] (triton::arch::MemoryOperand& memDst, triton::arch::MemoryOperand& memSrc)
      {
        return triton::api.taintAssignmentMemoryMemory(memDst, memSrc);
      },
      py::arg("memDst"), py::arg("memSrc"));


  m.def("taintAssignmentMemoryRegister",
      [] (triton::arch::MemoryOperand& memDst, triton::arch::RegisterOperand& regSrc)
      {
        return triton::api.taintAssignmentMemoryRegister(memDst, regSrc);
      },
      py::arg("memDst"), py::arg("regSrc"));


  m.def("taintAssignmentRegisterImmediate",
      [] (triton::arch::RegisterOperand& regDst)
      {
        return triton::api.taintAssignmentRegisterImmediate(regDst);
      },
      py::arg("regDst"));


  m.def("taintAssignmentRegisterMemory",
      [] (triton::arch::RegisterOperand& regDst, triton::arch::MemoryOperand& memSrc)
      {
        return triton::api.taintAssignmentRegisterMemory(regDst, memSrc);
      },
      py::arg("regDst"), py::arg("memSrc"));


  m.def("taintAssignmentRegisterRegister",
      [] (triton::arch::RegisterOperand& regDst, triton::arch::RegisterOperand& regSrc)
      {
        return triton::api.taintAssignmentRegisterRegister(regDst, regSrc);
      },
      py::arg("regDst"), py::arg("regSrc"));


  m.def("taintMemory",
      [] (triton::arch::MemoryOperand& mem)
      {
        return triton::api.taintMemory(mem);
      },
      py::arg("mem"));


  m.def("taintRegister",
      [] (triton::arch::RegisterOperand& reg)
      {
        return triton::api.taintRegister(reg);
      },
      py::arg("reg"));



  m.def("taintUnionMemoryImmediate",
      [] (triton::arch::MemoryOperand& memDst)
      {
        return triton::api.taintUnionMemoryImmediate(memDst);
      },
      py::arg("memDst"));


  m.def("taintUnionMemoryMemory",
      [] (triton::arch::MemoryOperand& memDst, triton::arch::MemoryOperand& memSrc)
      {
        return triton::api.taintUnionMemoryMemory(memDst, memSrc);
      },
      py::arg("memDst"), py::arg("memSrc"));


  m.def("taintUnionMemoryRegister",
      [] (triton::arch::MemoryOperand& memDst, triton::arch::RegisterOperand& regSrc)
      {
        return triton::api.taintUnionMemoryRegister(memDst, regSrc);
      },
      py::arg("memDst"), py::arg("regSrc"));


  m.def("taintUnionRegisterImmediate",
      [] (triton::arch::RegisterOperand& regDst)
      {
        return triton::api.taintUnionRegisterImmediate(regDst);
      },
      py::arg("regDst"));



  m.def("taintUnionRegisterMemory",
      [] (triton::arch::RegisterOperand& regDst, triton::arch::MemoryOperand& memSrc)
      {
        return triton::api.taintUnionRegisterMemory(regDst, memSrc);
      },
      py::arg("regDst"), py::arg("memSrc"));


  m.def("taintUnionRegisterRegister",
      [] (triton::arch::RegisterOperand& regDst, triton::arch::RegisterOperand& regSrc)
      {
        return triton::api.taintUnionRegisterRegister(regDst, regSrc);
      },
      py::arg("regDst"), py::arg("regSrc"));


  m.def("untaintMemory",
      [] (triton::__uint addr)
      {
        return triton::api.untaintMemory(addr);
      },
      py::arg("addr"));


  m.def("untaintMemory",
      [] (triton::arch::MemoryOperand& mem)
      {
        return triton::api.untaintMemory(mem);
      },
      py::arg("mem"));


  m.def("untaintRegister",
      [] (triton::arch::RegisterOperand& reg)
      {
        return triton::api.untaintRegister(reg);
      },
      py::arg("reg"));











}
