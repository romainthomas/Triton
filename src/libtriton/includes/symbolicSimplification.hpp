//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifndef TRITON_SYMBOLICSIMPLIFICATION_H
#define TRITON_SYMBOLICSIMPLIFICATION_H

#include <list>

#include "ast.hpp"
#include "tritonTypes.hpp"

#ifdef TRITON_PYTHON_BINDINGS
  #ifdef __unix__
    #include <python2.7/Python.h>
  #elif _WIN32
    #include <Python.h>
  #endif
#endif



//! \module The Triton namespace
namespace triton {
/*!
 *  \addtogroup triton
 *  @{
 */

  //! \module The Engines namespace
  namespace engines {
  /*!
   *  \ingroup triton
   *  \addtogroup engines
   *  @{
   */

    //! \module The Symbolic Execution namespace
    namespace symbolic {
    /*!
     *  \ingroup engines
     *  \addtogroup symbolic
     *  @{
     */

      typedef triton::ast::AbstractNode* (*sfp)(triton::ast::AbstractNode*);

      //! \class SymbolicSimplification
      /*! \brief The symbolic simplification class */
      class SymbolicSimplification {

        protected:
          //! Flag to define if we can use z3 to simplify expressions. Default: false.
          bool z3Enabled;

          //! List of simplification callbacks. These callbacks will be called before assigning a symbolic expression to a register or part of memory.
          std::list<triton::engines::symbolic::sfp> simplificationCallbacks;

        public:
          //! Constructor.
          SymbolicSimplification();

          //! Destructor.
          ~SymbolicSimplification();

          //! Returns true if Triton can use the simplification passes of z3.
          bool isZ3SimplificationEnabled(void);

          //! Enabled, Triton will use the simplification passes of z3 before to call its recorded simplification passes.
          void enableZ3Simplification(bool flag);

          //! Records a simplification callback.
          void recordSimplificationCallback(triton::engines::symbolic::sfp cb);

          //! Removes a simplification callback.
          void removeSimplificationCallback(triton::engines::symbolic::sfp cb);

          //! Processes all recorded simplifications. Returns the simplified node.
          triton::ast::AbstractNode* processSimplification(triton::ast::AbstractNode* node, bool z3=false);
      };

    /*! @} End of symbolic namespace */
    };
  /*! @} End of engines namespace */
  };
/*! @} End of triton namespace */
};

#endif /* TRITON_SYMBOLICSIMPLIFICATION_H */

