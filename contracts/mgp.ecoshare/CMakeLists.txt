add_contract(mgp.ecoshare mgp.ecoshare
   ${CMAKE_CURRENT_SOURCE_DIR}/src/ecoshare.cpp
)

target_include_directories(mgp.ecoshare
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(mgp.ecoshare
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/mgp.ecoshare.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/mgp.ecoshare.contracts.md @ONLY )

target_compile_options( mgp.ecoshare PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
