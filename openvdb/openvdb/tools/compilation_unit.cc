
// This file exists for the purpose of explicitly instantiating templates within the OpenVDB Tools package.
// This source file acts as a 'compilation unit' for all the tool templates.
// For each tool header that includes templates, we need to declare a symbol to enable explicit instantiation.

#define OPENVDB_INSTANTIATE_ACTIVATE
#include "openvdb/tools/Activate.h"

#define OPENVDB_INSTANTIATE_CHANGEBACKGROUND
#include "openvdb/tools/ChangeBackground.h"

#define OPENVDB_INSTANTIATE_CLIP
#include "openvdb/tools/Clip.h"

#define OPENVDB_INSTANTIATE_COMPOSITE
#include "openvdb/tools/Composite.h"

#define OPENVDB_INSTANTIATE_DIAGNOSTIC
#include "openvdb/tools/Diagnostics.h"

#define OPENVDB_INSTANTIATE_FASTSWEEPING
#include "openvdb/tools/FastSweeping.h"

#define OPENVDB_INSTANTIATE_FILTER
#include "openvdb/tools/Filter.h"

#define OPENVDB_INSTANTIATE_FINDACTIVEVALUES
#include "openvdb/tools/FindActiveValues.h"

#define OPENVDB_INSTANTIATE_GRIDOPERATORS
#include "openvdb/tools/GridOperators.h"

#define OPENVDB_INSTANTIATE_GRIDTRANSFORMER
#include "openvdb/tools/GridTransformer.h"

#define OPENVDB_INSTANTIATE_LEVELSETADVECT
#include "openvdb/tools/LevelSetAdvect.h"

#define OPENVDB_INSTANTIATE_LEVELSETFILTER
#include "openvdb/tools/LevelSetFilter.h"

#define OPENVDB_INSTANTIATE_LEVELSETFRACTURE
#include "openvdb/tools/LevelSetFracture.h"

#define OPENVDB_INSTANTIATE_LEVELSETMEASURE
#include "openvdb/tools/LevelSetMeasure.h"

#define OPENVDB_INSTANTIATE_LEVELSETMORPH
#include "openvdb/tools/LevelSetMorph.h"

#define OPENVDB_INSTANTIATE_LEVELSETPLATONIC
#include "openvdb/tools/LevelSetPlatonic.h"

#define OPENVDB_INSTANTIATE_LEVELSETREBUILD
#include "openvdb/tools/LevelSetRebuild.h"

#define OPENVDB_INSTANTIATE_LEVELSETSPHERE
#include "openvdb/tools/LevelSetSphere.h"

#define OPENVDB_INSTANTIATE_LEVELSETTRACKER
#include "openvdb/tools/LevelSetTracker.h"

#define OPENVDB_INSTANTIATE_LEVELSETUTIL
#include "openvdb/tools/LevelSetUtil.h"

#define OPENVDB_INSTANTIATE_MASK
#include "openvdb/tools/Mask.h"

#define OPENVDB_INSTANTIATE_MERGE
#include "openvdb/tools/Merge.h"

#define OPENVDB_INSTANTIATE_MESHTOVOLUME
#include "openvdb/tools/MeshToVolume.h"

#define OPENVDB_INSTANTIATE_MORPHOLOGY
#include "openvdb/tools/Morphology.h"

#define OPENVDB_INSTANTIATE_MULTIRESGRID
#include "openvdb/tools/MultiResGrid.h"

#define OPENVDB_INSTANTIATE_POISSONSOLVER
#include "openvdb/tools/PoissonSolver.h"

#define OPENVDB_INSTANTIATE_POTENTIALFLOW
#include "openvdb/tools/PotentialFlow.h"

#define OPENVDB_INSTANTIATE_PRUNE
#include "openvdb/tools/Prune.h"

#define OPENVDB_INSTANTIATE_RAYTRACER
#include "openvdb/tools/RayTracer.h"

#define OPENVDB_INSTANTIATE_SIGNEDFLOODFILL
#include "openvdb/tools/SignedFloodFill.h"

#define OPENVDB_INSTANTIATE_TOPOLOGYLEVELSET
#include "openvdb/tools/TopologyToLevelSet.h"

#define OPENVDB_INSTANTIATE_VALUETRANSFORMER
#include "openvdb/tools/ValueTransformer.h"

#define OPENVDB_INSTANTIATE_VECTORTRANSFORMER
#include "openvdb/tools/VectorTransformer.h"

#define OPENVDB_INSTANTIATE_VOLUMEADVECT
#include "openvdb/tools/VolumeAdvect.h"

#define OPENVDB_INSTANTIATE_VOLUMETOMESH
#include "openvdb/tools/VolumeToMesh.h"

#define OPENVDB_INSTANTIATE_VOLUMETOSPHERES
#include "openvdb/tools/VolumeToSpheres.h"
