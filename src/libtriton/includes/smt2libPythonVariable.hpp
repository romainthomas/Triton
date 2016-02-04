
#ifndef TRITON_PYTHONVARIABLE_H
#define TRITON_PYTHONVARIABLE_H
#include <string>


#include "tritonTypes.hpp"

namespace triton {
  namespace smt2lib {
    class PythonVariable {
      public:
        PythonVariable(void) = default;
        ~PythonVariable(void) = default;

        PythonVariable(const PythonVariable& copy) = default;
        PythonVariable& operator=(const PythonVariable& copy) = default;

        const std::string& name(void) const;
        uint32 id(void) const;
        uint32 size(void) const;
        uint128 value(void) const;

        PythonVariable& setName(const std::string& name);
        PythonVariable& setId(uint32 id);
        PythonVariable& setSize(uint32 size);
        PythonVariable& setValue(uint128 value);



      protected:
        std::string vName;
        uint32 vId;
        uint32 vSize;
        uint128 vValue;
    };
  };
};

#endif
