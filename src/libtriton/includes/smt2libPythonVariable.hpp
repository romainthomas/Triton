
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

        const std::string& getName(void) const;
        uint32 getId(void) const;
        uint32 getSize(void) const;

        PythonVariable& setName(const std::string& name);
        PythonVariable& setId(uint32 id);
        PythonVariable& setSize(uint32 size);


      protected:
        std::string name;

        uint32 id;
        uint32 size;
    };
  };
};

#endif
