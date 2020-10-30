//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Declares most of the standard geometric data types used
//	in MiniCAD code. This includes all WorldCoord related types.
//
#include "Prefix/StdAfx.h"
#include "MCCoordTypes.h"

using namespace VectorworksMVR;

const extern double VectorworksMVR::kNearlyEqualEpsilonForWorldCoords = 1e-13;
const extern WorldCoord VectorworksMVR::kMaxLegalWorldCoord = 1.0E100;
const extern WorldCoord VectorworksMVR::kMaxOutOfRangeWorldCoord = DBL_MAX;