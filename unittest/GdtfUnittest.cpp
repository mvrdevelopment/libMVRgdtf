//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfUnittest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)

GdtfUnittest::GdtfUnittest(const std::string& currentDir)
{
    fPath = currentDir;
    fPath += std::string("/testGdtf.gdtf");

    std::cout << "Export File to" << fPath << std::endl; 
}

GdtfUnittest::~GdtfUnittest()
{
    
}

bool GdtfUnittest::ExecuteTest()
{
	std::cout << "=                    GdtfUnittest                    =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void GdtfUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
	IGdtfFixturePtr gdtfWrite (IID_IGdtfFixture);

    MvrUUID uuid (225204211, 177198167, 1575790, 96627);
	MvrUUID linkedUuid (2227440, 1542265, 1573622, 2328410);
    if(__checkVCOM(gdtfWrite->OpenForWrite(fPath.c_str(),"FixtureName","Manufacturer", uuid)))
    {
		__checkVCOM(gdtfWrite->SetFixtureTypeDescription("Description"));
		__checkVCOM(gdtfWrite->SetShortName("shortName"));
		__checkVCOM(gdtfWrite->SetFixtureThumbnail("thumbnail"));
		__checkVCOM(gdtfWrite->SetLinkedFixtureGUID(linkedUuid));

		IGdtfActivationGroupPtr gdtfActGroup;
		__checkVCOM(gdtfWrite->CreateActivationGroup("actGroupName", &gdtfActGroup));

		IGdtfFeatureGroupPtr gdtfFeatureGroup;
		if (__checkVCOM(gdtfWrite->CreateFeatureGroup("featureGroupName", "featureGroupPrettyName", &gdtfFeatureGroup)))
		{
			IGdtfFeaturePtr gdtfFeature;
			__checkVCOM(gdtfFeatureGroup->CreateFeature("featureName", &gdtfFeature));
		}
		
		IGdtfAttributePtr gdtfAttribute;
		if (__checkVCOM(gdtfWrite->CreateAttribute("name", "prettyName", &gdtfAttribute)))
		{
			IGdtfActivationGroupPtr gdtfActivattionGroupLink;
			__checkVCOM(gdtfAttribute->SetActivationGroup(gdtfActivattionGroupLink));

			IGdtfFeaturePtr gdtfFeatureLink;
			__checkVCOM(gdtfAttribute->SetFeature(gdtfFeatureLink));

			EGdtfPhysicalUnit unit = EGdtfPhysicalUnit::Angle;
			__checkVCOM(gdtfAttribute->SetPhysicalUnit(unit));

			CieColor cieCol;
			__checkVCOM(gdtfAttribute->SetColor(cieCol));	//TODO maybe

			// Child TODO
		}

		IGdtfWheelPtr wheel1;
		if (__checkVCOM(gdtfWrite->CreateWheel("Wheel 1", &wheel1)))
		{
			IGdtfWheelSlotPtr wheel1Slot;
			if (__checkVCOM(wheel1->CreateWheelSlot("WheelSlot1 Wheel1", &wheel1Slot)))
			{
				CieColor cieCol;
				cieCol.fx  = 0.5;
				cieCol.fy  = 0.4242424242;
				cieCol.f_Y = 1.0;

				__checkVCOM(wheel1Slot->SetColor(cieCol));


				STransformMatrix ma;
				ma.ux = 1;
				ma.uy = 2;
				ma.uz = 3;

				ma.vx = 4;
				ma.vy = 5;
				ma.vz = 6;

				ma.wx = 7;
				ma.wy = 8;
				ma.wz = 9;

				ma.ox = 10;
				ma.oy = 11;
				ma.oz = 12;


				CieColor facetCol;
				facetCol.fx  = 0.4242424242;
				facetCol.fy  = 1.0;
				facetCol.f_Y = 0.5;


				IGdtfWheelSlotPrismFacetPtr gdtfFacet;
				if (__checkVCOM(wheel1Slot->CreatePrismFacet(ma, &gdtfFacet)))
				{
					__checkVCOM(gdtfFacet->SetColor(facetCol));
				}
			}
		}

		

		/*

		//------------------------------------------------------------------------------    
		// Create the Path to the gdtf file
		if (VCOM_SUCCEEDED(gdtfFile->OpenForWrite(pathToGdtf.c_str(), fixtureName.c_str(), manufacturer.c_str(), uuid)))
		{
			// Set other basic data
			//------------------------------------------------------------------------------    
			// Get Attributes
			Local<Object> activationGroups;
			if (GetObjectByName("activationGroups", stateObject, activationGroups))
			{
				Local<Array> activationGroupContainer;
				if (GetArrayByName("items", activationGroups, activationGroupContainer))
				{
					for (size_t i = 0; i < activationGroupContainer->Length(); i++)
					{
						Local<Value>    possibleActGroup = activationGroupContainer->Get(i);
						Local<Object>   actGroup;
						if (CastToObject(possibleActGroup, actGroup))
						{
							// Extract the name out if the
							std::string actGroupName = GetParamString("name", actGroup);

							VectorworksMVR::IGdtfActivationGroupPtr gdtfActGroup;
							VCOM_SUCCEEDED(gdtfFile->CreateActivationGroup(actGroupName.c_str(), &gdtfActGroup));

						}
					}
				}
			}

			Local<Object> featureGroups;
			if (GetObjectByName("featureGroups", stateObject, featureGroups))
			{
				Local<Array> featureGroupsContainer;
				if (GetArrayByName("items", featureGroups, featureGroupsContainer))
				{
					for (size_t i = 0; i < featureGroupsContainer->Length(); i++)
					{
						Local<Value>    possibleFeatureGroup = featureGroupsContainer->Get(i);
						Local<Object>   featureGroup;
						if (CastToObject(possibleFeatureGroup, featureGroup))
						{
							// Extract the name out if the
							std::string featureGroupName = GetParamString("name", featureGroup);
							std::string featureGroupPrettyName = GetParamString("name", featureGroup);

							VectorworksMVR::IGdtfFeatureGroupPtr gdtfFeatureGroup;
							if (VCOM_SUCCEEDED(gdtfFile->CreateFeatureGroup(featureGroupName.c_str(), featureGroupPrettyName.c_str(), &gdtfFeatureGroup)))
							{
								Local<Array> featuresContainer;
								if (GetArrayByName("features", featureGroup, featuresContainer))
								{
									for (size_t j = 0; j < featuresContainer->Length(); j++)
									{
										Local<Value>    possibleFeature = featuresContainer->Get(j);
										Local<Object>   feature;
										if (CastToObject(possibleFeature, feature))
										{
											// Extract the name out if the
											std::string featureName = GetParamString("name", feature);

											VectorworksMVR::IGdtfFeaturePtr gdtfFeature;
											VCOM_SUCCEEDED(gdtfFeatureGroup->CreateFeature(featureName.c_str(), &gdtfFeature));
										}
									}
								}
							}
						}
					}
				}
			}
			struct ResolveMainAttributeObj
			{
				VectorworksMVR::IGdtfAttributePtr   fAttribute;
				std::string                         fUnresolvedMainAttribute;
			};
			std::vector<ResolveMainAttributeObj> mainAttributeToResolve;

			Local<Object> attributeGroups;
			if (GetObjectByName("attributes", stateObject, attributeGroups))
			{
				Local<Array> attrContainer;
				if (GetArrayByName("items", attributeGroups, attrContainer))
				{
					for (size_t i = 0; i < attrContainer->Length(); i++)
					{
						Local<Value>    possibleAttr = attrContainer->Get(i);
						Local<Object>   attr;
						if (CastToObject(possibleAttr, attr))
						{
							// Extract the name out if the
							std::string name = GetParamString("name", attr);
							std::string prettyName = GetParamString("prettyName", attr);

							VectorworksMVR::IGdtfAttributePtr gdtfAttribute;
							if (VCOM_SUCCEEDED(gdtfFile->CreateAttribute(name.c_str(), prettyName.c_str(), &gdtfAttribute)))
							{
								// Set Activation Group
								std::string activationGroupName;
								if (GetParamStringSafe("activationGroup", attr, activationGroupName))
								{
									VectorworksMVR::IGdtfActivationGroupPtr gdtfActivattionGroupLink;
									if (GetGdtfActivationGroupByName(activationGroupName, gdtfFile, gdtfActivattionGroupLink))
									{
										VCOM_SUCCEEDED(gdtfAttribute->SetActivationGroup(gdtfActivattionGroupLink));
									}
								}

								// Set Feature
								std::string featureName = GetParamString("feature", attr);
								VectorworksMVR::IGdtfFeaturePtr gdtfFeatureLink;
								if (GetGdtfFeatureByName(featureName, gdtfFile, gdtfFeatureLink))
								{
									VCOM_SUCCEEDED(gdtfAttribute->SetFeature(gdtfFeatureLink));
								}

								// Set Main Attribute
								std::string mainAttribute;
								if (GetParamStringSafe("mainAttribute", attr, mainAttribute))
								{
									// Prepare to resolve later
									ResolveMainAttributeObj toResolve;
									toResolve.fAttribute = gdtfAttribute;
									toResolve.fUnresolvedMainAttribute = mainAttribute;
									mainAttributeToResolve.push_back(toResolve);
								}

								// Unit
								EGdtfPhysicalUnit unit = Convert_PhysicalUnit(attr);
								VCOM_SUCCEEDED(gdtfAttribute->SetPhysicalUnit(unit));

								// Color
								VectorworksMVR::CieColor cieCol;

								bool b1 = GetParamDoubleSafe("color_fx", attr, cieCol.fx);
								bool b2 = GetParamDoubleSafe("color_fy", attr, cieCol.fy);
								bool b3 = GetParamDoubleSafe("color_f_Y", attr, cieCol.f_Y);
								if (b1 && b2 && b3) { VCOM_SUCCEEDED(gdtfAttribute->SetColor(cieCol)); }


							}

						}
					}
				}
			}
			for (size_t i = 0; i < mainAttributeToResolve.size(); i++)
			{
				std::string                         mainName = mainAttributeToResolve[i].fUnresolvedMainAttribute;
				VectorworksMVR::IGdtfAttributePtr   child = mainAttributeToResolve[i].fAttribute;

				if (child)
				{
					VectorworksMVR::IGdtfAttributePtr mainAttribute;
					GetGdtfAttributeByName(mainName, gdtfFile, mainAttribute);
					VCOM_SUCCEEDED(child->SetMainAttribute(mainAttribute));
				}

			}



			//------------------------------------------------------------------------------    
			// Get Wheels
			Local<Object> wheelsGroup;
			if (GetObjectByName("wheels", stateObject, wheelsGroup))
			{
				Local<Array> wheelsContainer;
				if (GetArrayByName("items", wheelsGroup, wheelsContainer))
				{
					for (size_t i = 0; i < wheelsContainer->Length(); i++)
					{
						Local<Value>    possibleWheel = wheelsContainer->Get(i);
						Local<Object>   wheelObj;
						if (CastToObject(possibleWheel, wheelObj))
						{
							// Extract the name out if the
							std::string wheelName = GetParamString("name", wheelObj);

							VectorworksMVR::IGdtfWheelPtr gdtfWheelObj;
							if (VCOM_SUCCEEDED(gdtfFile->CreateWheel(wheelName.c_str(), &gdtfWheelObj)))
							{
								Local<Array> wheelSlotContainer;
								if (GetArrayByName("wheelSlots", wheelObj, wheelSlotContainer))
								{
									for (size_t j = 0; j < wheelSlotContainer->Length(); j++)
									{
										Local<Value>    possibleWheelSlot = wheelSlotContainer->Get(j);
										Local<Object>   wheelSlotObj;
										if (CastToObject(possibleWheelSlot, wheelSlotObj))
										{
											std::string     wheelSlotName = GetParamString("name", wheelSlotObj);

											VectorworksMVR::IGdtfWheelSlotPtr gdtfWheelSlot;
											if (VCOM_SUCCEEDED(gdtfWheelObj->CreateWheelSlot(wheelSlotName.c_str(), &gdtfWheelSlot)))
											{
												// Set Color
												VectorworksMVR::CieColor cieCol;
												cieCol.fx = GetParamDouble("col_x", wheelSlotObj);
												cieCol.fy = GetParamDouble("col_y", wheelSlotObj);
												cieCol.f_Y = GetParamDouble("col_L", wheelSlotObj);

												VCOM_SUCCEEDED(gdtfWheelSlot->SetColor(cieCol));

												// Set Gobo
												std::string goboName = GetParamString("goboName", wheelSlotObj);
												if (goboName.length() > 0)
												{
													VCOM_SUCCEEDED(gdtfWheelSlot->SetGobo(goboName.c_str()));
													CopyFileIntoGdtf(goboName, sessionFolder, gdtfFile);
												}

												// Add Facets
												Local<Array> prismContainer;
												if (GetArrayByName("prismFacets", wheelSlotObj, prismContainer))
												{
													for (size_t k = 0; k < prismContainer->Length(); k++)
													{
														Local<Value>    possiblePrism = prismContainer->Get(k);
														Local<Object>   prismObj;
														if (CastToObject(possiblePrism, prismObj))
														{
															Local<Object>                       matrix;
															VectorworksMVR::STransformMatrix    ma;
															if (GetObjectByName("matrix", prismObj, matrix))
															{
																ma.ux = GetParamDouble("ux", matrix);
																ma.uy = GetParamDouble("uy", matrix);
																ma.uz = GetParamDouble("uz", matrix);

																ma.vx = GetParamDouble("vx", matrix);
																ma.vy = GetParamDouble("vy", matrix);
																ma.vz = GetParamDouble("vz", matrix);

																ma.wx = GetParamDouble("wx", matrix);
																ma.wy = GetParamDouble("wy", matrix);
																ma.wz = GetParamDouble("wz", matrix);

																ma.ox = GetParamDouble("ox", matrix);
																ma.oy = GetParamDouble("oy", matrix);
																ma.oz = GetParamDouble("oz", matrix);
															}

															Local<Object>               colorObj;
															VectorworksMVR::CieColor    facetCol;
															if (GetObjectByName("color", prismObj, colorObj))
															{
																facetCol.fx = GetParamDouble("fx", colorObj);
																facetCol.fy = GetParamDouble("fy", colorObj);
																facetCol.f_Y = GetParamDouble("f_Y", colorObj);
															}

															VectorworksMVR::IGdtfWheelSlotPrismFacetPtr gdtfFacet;
															if (VCOM_SUCCEEDED(gdtfWheelSlot->CreatePrismFacet(ma, &gdtfFacet)))
															{
																VCOM_SUCCEEDED(gdtfFacet->SetColor(facetCol));


															} // Create GdtfFacet
														}// Cast Prism
													} // Cycle Prism
												} // Get Prism Array
											} // Create GdtfWheel
										} // Cast to Wheel Slot
									} // Cycle Array
								} // wheelSlots
							} // Create GdtfWheel
						} // Cast to Wheel
					} // Cycle Array
				} // items
			}  // wheels


			//------------------------------------------------------------------------------    
			// Get Emitter
			Local<Object> emitterGroup;
			if (GetObjectByName("emitter", stateObject, emitterGroup))
			{
				Local<Array> emitterArray;
				if (GetArrayByName("items", emitterGroup, emitterArray))
				{
					for (size_t i = 0; i < emitterArray->Length(); i++)
					{
						Local<Value>    possibleEmitter = emitterArray->Get(i);
						Local<Object>   emitterObj;
						if (CastToObject(possibleEmitter, emitterObj))
						{
							std::string name = GetParamString("name", emitterObj);

							VectorworksMVR::CieColor color;
							Local<Object> colorObj;
							if (GetObjectByName("color", emitterObj, colorObj))
							{
								color.fx = GetParamDouble("fx", colorObj);
								color.fy = GetParamDouble("fy", colorObj);
								color.f_Y = GetParamDouble("f_Y", colorObj);
							}

							VectorworksMVR::IGdtfPhysicalEmitterPtr gdtfEmitter;
							if (VCOM_SUCCEEDED(gdtfFile->CreateEmitter(name.c_str(), color, &gdtfEmitter)))
							{
								Local<Array> measurementArray;
								if (GetArrayByName("measurements", emitterObj, measurementArray))
								{
									for (size_t j = 0; j < measurementArray->Length(); j++)
									{
										Local<Value> possibleMeasurement = measurementArray->Get(j);
										Local<Object> measurementObject;
										if (CastToObject(possibleMeasurement, measurementObject))
										{
											double wavelength = GetParamDouble("waveLength", measurementObject);
											double energy = GetParamDouble("energy", measurementObject);

											VectorworksMVR::IGdtfMeasurementPointPtr gdtfMeasurement;
											VCOM_SUCCEEDED(gdtfEmitter->CreateMeasurementPoint(wavelength, energy, &gdtfMeasurement));
										}//cast measurement
									}//for measurements
								}//measurements
							}//create emitter
						}//cast to emitter 
					}//items Array
				}//items
			}//emitter

			//------------------------------------------------------------------------------    
			// Add Models

			Local<Object> modelGroups;
			if (GetObjectByName("models", stateObject, modelGroups))
			{
				Local<Array> modelsContainer;
				if (GetArrayByName("items", modelGroups, modelsContainer))
				{
					for (size_t i = 0; i < modelsContainer->Length(); i++)
					{
						Local<Value>    possibleModel = modelsContainer->Get(i);
						Local<Object>   modelObj;
						if (CastToObject(possibleModel, modelObj))
						{
							std::string name = GetParamString("name", modelObj);

							VectorworksMVR::IGdtfModelPtr gdtfModel;
							if (VCOM_SUCCEEDED(gdtfFile->CreateModel(name.c_str(), &gdtfModel)))
							{
								std::string file = GetParamString("file", modelObj);
								if (!file.empty())
								{
									VCOM_SUCCEEDED(gdtfModel->Set3DSGeometryFile(file.c_str()));
									CopyFileIntoGdtf(file, sessionFolder, gdtfFile);
								}

								double height = GetParamDouble("height", modelObj);
								double width = GetParamDouble("width", modelObj);
								double length = GetParamDouble("length", modelObj);
								VCOM_SUCCEEDED(gdtfModel->SetHeight(height));
								VCOM_SUCCEEDED(gdtfModel->SetWidth(width));
								VCOM_SUCCEEDED(gdtfModel->SetLength(length));

								EGdtfModel_PrimitiveType primType = ConvertEGdtfModel_PrimitiveType(GetParamInteger("primitiveType", modelObj));
								VCOM_SUCCEEDED(gdtfModel->SetPrimitiveType(primType));

							}
						}
					}
				}
			}

			//------------------------------------------------------------------------------    
			// Add Geometry

			std::vector<VectorworksMVR::IGdtfGeometryPtr> gdtfGeometryArray;

			Local<Object> geometryGroup;
			if (GetObjectByName("geometries", stateObject, geometryGroup))
			{
				Local<Array> geometryContainer;
				if (GetArrayByName("items", geometryGroup, geometryContainer))
				{
					for (size_t i = 0; i < geometryContainer->Length(); i++)
					{
						Local<Value>    possibleGeo = geometryContainer->Get(i);
						Local<Object>   geoObj;
						if (CastToObject(possibleGeo, geoObj))
						{
							std::string name = GetParamString("name", geoObj);
							EGdtfObjectType objectType = ConvertEGdtfObjectType(GetParamInteger("type", geoObj));

							VectorworksMVR::IGdtfModelPtr model;
							GetGdtfModelByName(GetParamString("model", geoObj), gdtfFile, model);

							// Prepare Transfrom Matrix
							VectorworksMVR::STransformMatrix ma;
							ma.ux = GetParamDouble("ux", geoObj);
							ma.uy = GetParamDouble("uy", geoObj);
							ma.uz = GetParamDouble("uz", geoObj);

							ma.vx = GetParamDouble("vx", geoObj);
							ma.vy = GetParamDouble("vy", geoObj);
							ma.vz = GetParamDouble("vz", geoObj);

							ma.wx = GetParamDouble("wx", geoObj);
							ma.wy = GetParamDouble("wy", geoObj);
							ma.wz = GetParamDouble("wz", geoObj);

							ma.ox = GetParamDouble("ox", geoObj);
							ma.oy = GetParamDouble("oy", geoObj);
							ma.oz = GetParamDouble("oz", geoObj);

							VectorworksMVR::IGdtfGeometryPtr childGeo;
							if (VCOM_SUCCEEDED(gdtfFile->CreateGeometry(objectType, name.c_str(), model, ma, &childGeo)))
							{
								gdtfGeometryArray.push_back(childGeo);
								PrintPropertiesForGeometry(objectType, childGeo, geoObj);

								// Traverse child geometry
								TraverseChildGeometry(geoObj, childGeo, gdtfFile, gdtfGeometryArray);
							}
						}
					}
				}
			}

			//------------------------------------------------------------------------------
			// Get dmxModes

			Local<Object> dmxModesGroup;
			if (GetObjectByName("dmxModes", stateObject, dmxModesGroup))
			{
				Local<Array> dmxModeArray;
				if (GetArrayByName("items", dmxModesGroup, dmxModeArray))
				{

					for (size_t i = 0; i < dmxModeArray->Length(); i++)
					{
						Local<Value> possibleDmxMode = dmxModeArray->Get(i);
						Local<Object> dmxModeObj;
						if (CastToObject(possibleDmxMode, dmxModeObj))
						{
							std::string name = GetParamString("name", dmxModeObj);

							VectorworksMVR::IGdtfDmxModePtr gdtfDmxMode;
							if (VCOM_SUCCEEDED(gdtfFile->CreateDmxMode(name.c_str(), &gdtfDmxMode)))
							{
								std::string name = GetParamString("geometry", dmxModeObj);

								//TODO relation stuff


								VectorworksMVR::IGdtfGeometryPtr geometry;
								if (GetGdtfGeometryByName(name, gdtfGeometryArray, geometry))
								{
									VCOM_SUCCEEDED(gdtfDmxMode->SetGeometry(geometry));
								}


								Local<Array> dmxChannelArray;
								if (GetArrayByName("dmxChannels", dmxModeObj, dmxChannelArray))
								{

									for (size_t j = 0; j < dmxChannelArray->Length(); j++)
									{
										Local<Value> possibleDmxChannel = dmxChannelArray->Get(j);
										Local<Object> dmxChannelObj;
										if (CastToObject(possibleDmxChannel, dmxChannelObj))
										{
											std::string name = GetParamString("name", dmxChannelObj);

											VectorworksMVR::IGdtfDmxChannelPtr gdtfDmxChannel;
											if (VCOM_SUCCEEDED(gdtfDmxMode->CreateDmxChannel(name.c_str(), &gdtfDmxChannel)))
											{
												Sint32 activeResolution = GetParamInteger("activeResolution", dmxChannelObj);
												if (activeResolution > 0)
												{
													Sint32 coarse = GetParamInteger("coarse", dmxChannelObj);
													VCOM_SUCCEEDED(gdtfDmxChannel->SetCoarse(coarse));
												}
												if (activeResolution > 1)
												{
													Sint32 fine = GetParamInteger("fine", dmxChannelObj);
													VCOM_SUCCEEDED(gdtfDmxChannel->SetFine(fine));
												}
												if (activeResolution > 2)
												{
													Sint32 ultra = GetParamInteger("ultra", dmxChannelObj);
													VCOM_SUCCEEDED(gdtfDmxChannel->SetUltra(ultra));
												}
												if (activeResolution > 3)
												{
													Sint32 uber = GetParamInteger("uber", dmxChannelObj);
													VCOM_SUCCEEDED(gdtfDmxChannel->SetUber(uber));
												}

												EGdtfDmxFrequency dmxFrequency = ConvertEGdtfDmxFrequency(GetParamInteger("dmxFrequency", dmxChannelObj));
												VCOM_SUCCEEDED(gdtfDmxChannel->SetDmxFrequency(dmxFrequency));

												Sint32 defaultValue = GetParamInteger("defaultValue", dmxChannelObj);
												VCOM_SUCCEEDED(gdtfDmxChannel->SetDefaultValue(defaultValue));

												if (GetParamBool("hasHighlight", dmxChannelObj))
												{
													Sint32 highlight = GetParamInteger("highlight", dmxChannelObj);
													VCOM_SUCCEEDED(gdtfDmxChannel->SetHighlight(highlight));
												}

												// Dmx Break
												Sint32 dmxbreak = GetParamInteger("breakId", dmxChannelObj);
												VCOM_SUCCEEDED(gdtfDmxChannel->SetDmxBreak(dmxbreak));


												double moveInBlack = GetParamDouble("moveInBlack", dmxChannelObj);
												VCOM_SUCCEEDED(gdtfDmxChannel->SetMoveInBlackFrames(moveInBlack));

												double dmxChangeTimeLimit = GetParamDouble("dmxChangeTimeLimit", dmxChannelObj);
												VCOM_SUCCEEDED(gdtfDmxChannel->SetDmxChangeTimeLimit(dmxChangeTimeLimit));

												std::string name = GetParamString("linkedGeometryName", dmxChannelObj);
												VectorworksMVR::IGdtfGeometryPtr geometry;
												if (GetGdtfGeometryByName(name, gdtfGeometryArray, geometry))
												{
													VCOM_SUCCEEDED(gdtfDmxChannel->SetGeometry(geometry));
												}


												Local<Array> logicalChannels;
												if (GetArrayByName("logicalChannels", dmxChannelObj, logicalChannels))
												{

													for (size_t k = 0; k < logicalChannels->Length(); k++)
													{
														Local<Value> possibleLogicalChannel = logicalChannels->Get(k);
														Local<Object> logicalChannelObj;
														if (CastToObject(possibleLogicalChannel, logicalChannelObj))
														{
															std::string name = GetParamString("name", logicalChannelObj);

															VectorworksMVR::IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
															if (VCOM_SUCCEEDED(gdtfDmxChannel->CreateLogicalChannel(name.c_str(), &gdtfLogicalChannel)))
															{
																std::string logAttribute = GetParamString("attribute", logicalChannelObj);
																VectorworksMVR::IGdtfAttributePtr attribute;
																if (GetGdtfAttributeByName(logAttribute, gdtfFile, attribute))
																{
																	VCOM_SUCCEEDED(gdtfLogicalChannel->SetAttribute(attribute));
																}


																EGdtfDmxMaster master = ConvertEGdtfDmxMaster(GetParamInteger("dmxMaster", logicalChannelObj));
																VCOM_SUCCEEDED(gdtfLogicalChannel->SetDmxMaster(master));

																EGdtfDmxSnap snap = ConvertEGdtfDmxSnap(GetParamInteger("dmxSnap", logicalChannelObj));
																VCOM_SUCCEEDED(gdtfLogicalChannel->SetDmxSnap(snap));

																Local<Array> channelFunctions;
																if (GetArrayByName("channelFunctions", logicalChannelObj, channelFunctions))
																{
																	for (size_t l = 0; l < channelFunctions->Length(); l++)
																	{
																		Local<Value> possibleChannelFunction = channelFunctions->Get(l);
																		Local<Object> channelFunctionObj;
																		if (CastToObject(possibleChannelFunction, channelFunctionObj))
																		{
																			std::string name = GetParamString("name", channelFunctionObj);

																			VectorworksMVR::IGdtfDmxChannelFunctionPtr gdftChannelFunction;
																			if (VCOM_SUCCEEDED(gdtfLogicalChannel->CreateDmxFunction(name.c_str(), &gdftChannelFunction)))
																			{
																				std::string funcAttribute = GetParamString("attribute", channelFunctionObj);
																				VectorworksMVR::IGdtfAttributePtr attribute;
																				if (GetGdtfAttributeByName(logAttribute, gdtfFile, attribute))
																				{
																					VCOM_SUCCEEDED(gdftChannelFunction->SetAttribute(attribute));
																				}

																				std::string orginalAttribute = GetParamString("originalAttribute", channelFunctionObj);
																				VCOM_SUCCEEDED(gdftChannelFunction->SetOriginalAttribute(orginalAttribute.c_str()));

																				Sint32 dmxStartAddress = GetParamInteger("dmxStartAddress", channelFunctionObj);
																				VCOM_SUCCEEDED(gdftChannelFunction->SetStartAddress(dmxStartAddress));

																				double physicalStart = GetParamDouble("physicalStart", channelFunctionObj);
																				VCOM_SUCCEEDED(gdftChannelFunction->SetPhysicalStart(physicalStart));

																				double physicalEnd = GetParamDouble("physicalEnd", channelFunctionObj);
																				VCOM_SUCCEEDED(gdftChannelFunction->SetPhysicalEnd(physicalEnd));

																				double realFade = GetParamDouble("realFade", channelFunctionObj);
																				VCOM_SUCCEEDED(gdftChannelFunction->SetRealFade(realFade));

																				EGDTFDmxInvert dmxInvert = ConvertEGDTFDmxInvert(GetParamInteger("dmxInvert", channelFunctionObj));
																				VCOM_SUCCEEDED(gdftChannelFunction->SetDMXInvert(dmxInvert));

																				EGDTFEncoderInvert encoderInvert = ConvertEGDTFEncoderInvert(GetParamInteger("encoderInvert", channelFunctionObj));
																				VCOM_SUCCEEDED(gdftChannelFunction->SetEncoderInvert(encoderInvert));

																				// Get Channel Set
																				Local<Array> channelSetContainer;
																				if (GetArrayByName("channelSets", channelFunctionObj, channelSetContainer))
																				{
																					for (size_t m = 0; m < channelSetContainer->Length(); m++)
																					{
																						Local<Value> possibleChannelSet = channelSetContainer->Get(m);
																						Local<Object> channelSetObj;
																						if (CastToObject(possibleChannelSet, channelSetObj))
																						{
																							std::string name = GetParamString("name", channelSetObj);
																							Sint32      dmxStart = GetParamInteger("dmxStartAddress", channelSetObj);
																							Sint32      dmxEnd = GetParamInteger("dmxEndAddress", channelSetObj);

																							VectorworksMVR::IGdtfDmxChannelSetPtr gdtfChannelSet;
																							if (VCOM_SUCCEEDED(gdftChannelFunction->CreateDmxChannelSet(name.c_str(), dmxStart, dmxEnd, &gdtfChannelSet)))
																							{
																								if (!GetParamBool("usePhysicalFromParent", channelSetObj))
																								{
																									double physicalEnd = GetParamDouble("physicalEnd", channelSetObj);
																									VCOM_SUCCEEDED(gdtfChannelSet->SetPhysicalEnd(physicalEnd));

																									double physicalStart = GetParamDouble("physicalStart", channelSetObj);
																									VCOM_SUCCEEDED(gdtfChannelSet->SetPhysicalStart(physicalStart));
																								}

																								Sint32 wheelSlotIndex = GetParamInteger("wheelSlotIndex", channelSetObj);
																								VCOM_SUCCEEDED(gdtfChannelSet->SetWheelSlot(wheelSlotIndex));

																							} // Create Channel
																						} // Cast
																					} // Cycle Array
																				} // Get Array
																			} // GdtfDmxFuunction
																		} // Cast
																	}
																}
															}
														}
													}
												}
											}
										}//cast to dmxChannel
									}//dmxChannel Array
								}//dmxChannels
							}//create dmxMode
						}//cast to dmxMode
					}//item Array
				}//items
			}//dmxModes

			//------------------------------------------------------------------------------    
			// Close the stream and dump to disk
			VCOM_SUCCEEDED(gdtfFile->Close());
		}
		*/
        __checkVCOM(gdtfWrite->Close());
    }
}

void GdtfUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
    IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);

    
    if(__checkVCOM(gdtfRead->ReadFromFile(fPath.c_str())))
    {
        // Check Fixture Name
        MvrString fixtureName = gdtfRead->GetName();
        this->checkifEqual("GetName", fixtureName, "FixtureName");
        
    }

	
}