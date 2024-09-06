#
# This file is used to executed given unit test commands locally, handling
# additional arguments like 'exhaustive' and setting the DCMDICTPATH
# environment variable appropriately.
#

set(ENV{DCMDICTPATH} "C:/Users/sahnn/Downloads/dcmtk-3.6.8/dcmtk-3.6.8/dcmdata/data/dicom.dic;C:/Users/sahnn/Downloads/dcmtk-3.6.8/dcmtk-3.6.8/dcmdata/data/private.dic")
set(ENV{DCMICONVPATH} "C:/Users/sahnn/Downloads/dcmtk-3.6.8/dcmtk-3.6.8/oficonv/data")

execute_process(COMMAND
    "${DCMTK_CTEST_TESTCASE_COMMAND}" $ENV{DCMTK_CTEST_EXTRA_ARGUMENTS} "${DCMTK_CTEST_TEST_NAME}"
    RESULT_VARIABLE RESULT
)

# We cannot forward the result value to CMake, so print it instead and let CMake
# return with code '1' or whatever it deems appropriate to notify about an error.
if(RESULT)
    message(FATAL_ERROR "Test command returned: ${RESULT}")
endif()
