
#-----------------------------------------------------------------------------
set(MODULE_NAME CarreraSlice)
string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

#-----------------------------------------------------------------------------
add_subdirectory(Logic)

#-----------------------------------------------------------------------------
#Set up the Editor module

set(MODULE_PYTHON_SCRIPTS
 #__init__
  KUtil
  CarreraSliceEffect
  )

set(MODULE_PYTHON_RESOURCES
  CarreraSliceEffect.png
  )

#-----------------------------------------------------------------------------
slicerMacroBuildScriptedModule(
  NAME      ${MODULE_NAME}
  SCRIPTS   ${MODULE_PYTHON_SCRIPTS}
  RESOURCES ${MODULE_PYTHON_RESOURCES}
  VERBOSE
  )

