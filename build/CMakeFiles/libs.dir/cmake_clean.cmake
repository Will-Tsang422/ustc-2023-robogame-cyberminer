file(REMOVE_RECURSE
  "liblibs.a"
  "liblibs.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/libs.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
