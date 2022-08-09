cmake_minimum_required(VERSION 3.5.1)
project(openvdb)

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)
if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-O3)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

option(COMPILE_EXPLICIT_TEMPLATE_INSTANTIATIONS "Use explicit instantiation for all supported classes and methods against a
pre-defined list of OpenVDB trees. This makes the core library larger and slower to compile, but speeds up
the compilation of all dependent code by bypassing the expensive template instantation. If enabled, >40min build time expected." OFF)

set(OPENVDB_DIRECTORY "${CMAKE_SOURCE_DIR}/openvdb/openvdb")
set(OPENVDB_INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/openvdb/
  ${OPENVDB_DIRECTORY}/
  ${OPENVDB_DIRECTORY}/io/
  ${OPENVDB_DIRECTORY}/math/
  ${OPENVDB_DIRECTORY}/points/
  ${OPENVDB_DIRECTORY}/thread/
  ${OPENVDB_DIRECTORY}/tree/
  ${OPENVDB_DIRECTORY}/util/
)
if(${COMPILE_EXPLICIT_TEMPLATE_INSTANTIATIONS})
  list(APPEND OPENVDB_INCLUDE_DIRECTORIES ${OPENVDB_DIRECTORY}/tools/)
endif()
set(OPENVDB_SRC
  # Grid
  ${OPENVDB_DIRECTORY}/Grid.cc
  # IO
  ${OPENVDB_DIRECTORY}/io/Archive.cc
  ${OPENVDB_DIRECTORY}/io/Compression.cc
  ${OPENVDB_DIRECTORY}/io/DelayedLoadMetadata.cc
  ${OPENVDB_DIRECTORY}/io/File.cc
  ${OPENVDB_DIRECTORY}/io/GridDescriptor.cc
  ${OPENVDB_DIRECTORY}/io/Queue.cc
  ${OPENVDB_DIRECTORY}/io/Stream.cc
  ${OPENVDB_DIRECTORY}/io/TempFile.cc
  # Math
  ${OPENVDB_DIRECTORY}/math/Half.cc
  ${OPENVDB_DIRECTORY}/math/Maps.cc
  ${OPENVDB_DIRECTORY}/math/Proximity.cc
  ${OPENVDB_DIRECTORY}/math/QuantizedUnitVec.cc
  ${OPENVDB_DIRECTORY}/math/Transform.cc
  # General
  ${OPENVDB_DIRECTORY}/Metadata.cc
  ${OPENVDB_DIRECTORY}/MetaMap.cc
  ${OPENVDB_DIRECTORY}/openvdb.cc
  ${OPENVDB_DIRECTORY}/Platform.cc
  # Points
  ${OPENVDB_DIRECTORY}/points/AttributeArray.cc
  ${OPENVDB_DIRECTORY}/points/AttributeArrayString.cc
  ${OPENVDB_DIRECTORY}/points/AttributeGroup.cc
  ${OPENVDB_DIRECTORY}/points/AttributeSet.cc
  ${OPENVDB_DIRECTORY}/points/StreamCompression.cc
  ${OPENVDB_DIRECTORY}/points/points.cc
  # Util
  ${OPENVDB_DIRECTORY}/util/Formats.cc
  ${OPENVDB_DIRECTORY}/util/Util.cc
)
if(${COMPILE_EXPLICIT_TEMPLATE_INSTANTIATIONS})
  list(PREPEND OPENVDB_SRC ${OPENVDB_DIRECTORY}/tools/compilation_unit.cc)
endif()
file(GLOB_RECURSE OPENVDB_HEADERS "${OPENVDB_DIRECTORY}/*.h")

# Find catkin macros and libraries
find_package(catkin REQUIRED)

find_package(Blosc REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams)
find_package(TBB REQUIRED COMPONENTS tbb)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)

# Catkin package macro
catkin_package(
  INCLUDE_DIRS
    ${OPENVDB_INCLUDE_DIRECTORIES}
    ${Blosc_INCLUDE_DIRS}  
    ${Boost_INCLUDE_DIRS}
    ${TBB_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
  LIBRARIES
    ${PROJECT_NAME}_openvdb
  DEPENDS
    Boost
)

########################
## Library definition ##
########################
add_library(${PROJECT_NAME}_openvdb
  ${OPENVDB_SRC}
  ${OPENVDB_HEADERS}
)
target_include_directories(${PROJECT_NAME}_openvdb PUBLIC
  ${OPENVDB_INCLUDE_DIRECTORIES}
)
target_include_directories(${PROJECT_NAME}_openvdb SYSTEM PUBLIC
  ${Blosc_INCLUDE_DIRS}  
  ${Boost_INCLUDE_DIRS}
  ${TBB_INCLUDE_DIRS}
  ${ZLIB_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}_openvdb
  Blosc::blosc
  Boost::iostreams
  TBB::tbb
  Threads::Threads
  ZLIB::ZLIB
)
if(${COMPILE_EXPLICIT_TEMPLATE_INSTANTIATIONS}) 
  target_compile_definitions(${PROJECT_NAME}_openvdb PRIVATE -DOPENVDB_USE_EXPLICIT_INSTANTIATION=1)
endif()

#############
## Install ##
#############
install(
  TARGETS
    ${PROJECT_NAME}_openvdb
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(
  DIRECTORY
    ${OPENVDB_DIRECTORY}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

##############
##   Test   ##
##############
if(CATKIN_ENABLE_TESTING)
  set(OPENVDB_TESTS_SRC
    ${OPENVDB_DIRECTORY}/unittest/TestBBox.cc
    ${OPENVDB_DIRECTORY}/unittest/TestCoord.cc
    ${OPENVDB_DIRECTORY}/unittest/TestIndexFilter.cc
    ${OPENVDB_DIRECTORY}/unittest/TestIndexIterator.cc
    ${OPENVDB_DIRECTORY}/unittest/TestInit.cc
    ${OPENVDB_DIRECTORY}/unittest/TestInt32Metadata.cc
    ${OPENVDB_DIRECTORY}/unittest/TestInt64Metadata.cc
    ${OPENVDB_DIRECTORY}/unittest/TestLinearInterp.cc
    ${OPENVDB_DIRECTORY}/unittest/TestMaps.cc
    ${OPENVDB_DIRECTORY}/unittest/TestMath.cc
    ${OPENVDB_DIRECTORY}/unittest/TestName.cc
    ${OPENVDB_DIRECTORY}/unittest/TestNodeMask.cc
    ${OPENVDB_DIRECTORY}/unittest/TestQuadraticInterp.cc
    ${OPENVDB_DIRECTORY}/unittest/TestQuantizedUnitVec.cc
    ${OPENVDB_DIRECTORY}/unittest/TestQuat.cc
    ${OPENVDB_DIRECTORY}/unittest/TestStats.cc
    ${OPENVDB_DIRECTORY}/unittest/TestTransform.cc
    ${OPENVDB_DIRECTORY}/unittest/TestTypes.cc
    ${OPENVDB_DIRECTORY}/unittest/TestUtil.cc
    ${OPENVDB_DIRECTORY}/unittest/TestVec2Metadata.cc
    ${OPENVDB_DIRECTORY}/unittest/TestVec3Metadata.cc
  )
  if(${COMPILE_EXPLICIT_TEMPLATE_INSTANTIATIONS})
    list(APPEND OPENVDB_TESTS_SRC
      ${OPENVDB_DIRECTORY}/unittest/TestActivate.cc
      ${OPENVDB_DIRECTORY}/unittest/TestAttributeArray.cc
      ${OPENVDB_DIRECTORY}/unittest/TestAttributeArrayString.cc
      ${OPENVDB_DIRECTORY}/unittest/TestAttributeGroup.cc
      ${OPENVDB_DIRECTORY}/unittest/TestAttributeSet.cc
      ${OPENVDB_DIRECTORY}/unittest/TestClip.cc
      ${OPENVDB_DIRECTORY}/unittest/TestConjGradient.cc
      ${OPENVDB_DIRECTORY}/unittest/TestCount.cc
      ${OPENVDB_DIRECTORY}/unittest/TestCpt.cc
      ${OPENVDB_DIRECTORY}/unittest/TestCurl.cc
      ${OPENVDB_DIRECTORY}/unittest/TestDelayedLoadMetadata.cc
      ${OPENVDB_DIRECTORY}/unittest/TestDense.cc
      ${OPENVDB_DIRECTORY}/unittest/TestDenseSparseTools.cc
      ${OPENVDB_DIRECTORY}/unittest/TestDiagnostics.cc
      ${OPENVDB_DIRECTORY}/unittest/TestDivergence.cc
      ${OPENVDB_DIRECTORY}/unittest/TestDoubleMetadata.cc
      ${OPENVDB_DIRECTORY}/unittest/TestExceptions.cc
      ${OPENVDB_DIRECTORY}/unittest/TestFastSweeping.cc
      ${OPENVDB_DIRECTORY}/unittest/TestFile.cc
      ${OPENVDB_DIRECTORY}/unittest/TestFilter.cc
      ${OPENVDB_DIRECTORY}/unittest/TestFindActiveValues.cc
      ${OPENVDB_DIRECTORY}/unittest/TestFloatMetadata.cc
      ${OPENVDB_DIRECTORY}/unittest/TestGradient.cc
      ${OPENVDB_DIRECTORY}/unittest/TestGrid.cc
      ${OPENVDB_DIRECTORY}/unittest/TestGridBbox.cc
      ${OPENVDB_DIRECTORY}/unittest/TestGridDescriptor.cc
      ${OPENVDB_DIRECTORY}/unittest/TestGridIO.cc
      ${OPENVDB_DIRECTORY}/unittest/TestGridTransformer.cc
      ${OPENVDB_DIRECTORY}/unittest/TestInternalOrigin.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLaplacian.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLeaf.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLeafBool.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLeafIO.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLeafManager.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLeafMask.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLeafOrigin.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLevelSetRayIntersector.cc
      ${OPENVDB_DIRECTORY}/unittest/TestLevelSetUtil.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMat4Metadata.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMeanCurvature.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMerge.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMeshToVolume.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMetadata.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMetadataIO.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMetaMap.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMorphology.cc
      ${OPENVDB_DIRECTORY}/unittest/TestMultiResGrid.cc
      ${OPENVDB_DIRECTORY}/unittest/TestNodeIterator.cc
      ${OPENVDB_DIRECTORY}/unittest/TestNodeManager.cc
      ${OPENVDB_DIRECTORY}/unittest/TestNodeVisitor.cc
      ${OPENVDB_DIRECTORY}/unittest/TestParticleAtlas.cc
      ${OPENVDB_DIRECTORY}/unittest/TestParticlesToLevelSet.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointAdvect.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointAttribute.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointConversion.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointCount.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointDataLeaf.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointDelete.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointGroup.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointIndexGrid.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointInstantiate.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointMask.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointMove.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointPartitioner.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointRasterizeFrustum.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointRasterizeSDF.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointRasterizeTrilinear.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointSample.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointScatter.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointStatistics.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPointsToMask.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPoissonSolver.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPotentialFlow.cc
      ${OPENVDB_DIRECTORY}/unittest/TestPrePostAPI.cc
      ${OPENVDB_DIRECTORY}/unittest/TestRay.cc
      ${OPENVDB_DIRECTORY}/unittest/TestStream.cc
      ${OPENVDB_DIRECTORY}/unittest/TestStreamCompression.cc
      ${OPENVDB_DIRECTORY}/unittest/TestStringMetadata.cc
      ${OPENVDB_DIRECTORY}/unittest/TestTools.cc
      ${OPENVDB_DIRECTORY}/unittest/TestTopologyToLevelSet.cc
      ${OPENVDB_DIRECTORY}/unittest/TestTree.cc
      ${OPENVDB_DIRECTORY}/unittest/TestTreeCombine.cc
      ${OPENVDB_DIRECTORY}/unittest/TestTreeGetSetValues.cc
      ${OPENVDB_DIRECTORY}/unittest/TestTreeIterators.cc
      ${OPENVDB_DIRECTORY}/unittest/TestTreeVisitor.cc
      ${OPENVDB_DIRECTORY}/unittest/TestValueAccessor.cc
      ${OPENVDB_DIRECTORY}/unittest/TestVolumeRayIntersector.cc
      ${OPENVDB_DIRECTORY}/unittest/TestVolumeToMesh.cc
      ${OPENVDB_DIRECTORY}/unittest/TestVolumeToSpheres.cc
    )
  endif()

  catkin_add_gtest(test_${PROJECT_NAME}_openvdb
    ${OPENVDB_TESTS_SRC}
    ${OPENVDB_DIRECTORY}/unittest/main.cc
  )
  add_dependencies(test_${PROJECT_NAME}_openvdb
    ${PROJECT_NAME}_openvdb
  )
  target_include_directories(test_${PROJECT_NAME}_openvdb PRIVATE
    ${${PROJECT_NAME}_openvdb_INCLUDE_DIRECTORIES}
    ${OPENVDB_INCLUDE_DIRECTORIES}
    ${Boost_INCLUDE_DIRS}
    ${TBB_INCLUDE_DIRS}
  )
  target_link_libraries(test_${PROJECT_NAME}_openvdb
    ${PROJECT_NAME}_openvdb
    Blosc::blosc
    Boost::iostreams
    TBB::tbb
    Threads::Threads
  )

  ###################
  ## Code_coverage ##
  ###################
  find_package(cmake_code_coverage QUIET)
  if(cmake_code_coverage_FOUND)
    add_gtest_coverage(
      TEST_BUILD_TARGETS
        test_${PROJECT_NAME}_openvdb
    )
  endif()
endif()

#################
## Clang_tools ##
#################
find_package(cmake_clang_tools QUIET)
if(cmake_clang_tools_FOUND)
  add_default_clang_tooling(
    DISABLE_CLANG_FORMAT
  )
endif(cmake_clang_tools_FOUND)