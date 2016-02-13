
#ifndef TRITON_PYTHONVARIABLE_H
#define TRITON_PYTHONVARIABLE_H
#include <string>


#include "tritonTypes.hpp"

namespace triton {
  namespace smt2lib {
    class PythonVariable {
      public:
        PythonVariable(void);
        ~PythonVariable(void) = default;

        PythonVariable(const PythonVariable& copy)            = default;
        PythonVariable& operator=(const PythonVariable& copy) = default;

        std::string        name(void) const;
        uint32             id(void) const;
        uint32             size(void) const;
        uint128            value(void) const;
        bool               isValue(void) const;
        const std::string& expression(void) const;


        PythonVariable& setIsValue(bool flag);
        PythonVariable& setName(const std::string& name);
        PythonVariable& setId(uint32 id);
        PythonVariable& setSize(uint32 size);
        PythonVariable& setValue(uint128 value);
        PythonVariable& setExpression(const std::string& expression);



      protected:
        std::string vName;
        uint32      vId;
        uint32      vSize;
        uint128     vValue;
        bool        vIsValue;
        std::string vExpression;
    };
  };
};

#endif
