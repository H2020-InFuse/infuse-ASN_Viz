//
// Copyright (c) 2015-2017, Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.
// Copyright (c) 2015-2017, University of Bremen
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#include <iostream>

#include "MapVisualization.hpp"

//#include <vizkit3d/ColorConversionHelper.hpp>

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>

//#include "ColorGradient.hpp"

using namespace vizkit3d;

// struct GridMapVisualization::Data {
//     // Copy of the value given to updateDataIntern.
//     //
//     // Making a copy is required because of how OSG works
//     virtual ~Data() { }
//     virtual void visualize(osg::Geode& geode) const = 0;
//     virtual maps::grid::CellExtents getCellExtents() const = 0;
//     virtual maps::grid::Vector2d getResolution() const = 0;
//     virtual base::Affine3d getLocalFrame() const = 0;
// };

// template<typename GridT>
// struct DataHold : public GridMapVisualization::Data
// {
//     GridMap<GridT> grid;

//     ColorGradient heatMapGradient;

//     DataHold(const GridMap<GridT> grid) 
//         : grid(grid) 
//     {
//         this->heatMapGradient.createDefaul
//     // Copy of the value given to updateDataIntern.
//     //
//     // Making a copy is required because of how OSG works
//     virtual ~Data() { }
//     virtual void visualize(osg::Geode& geode) const = 0;
//     virtual maps::grid::CellExtents getCellExtents() const = 0;
//     virtutHeatMapGradient();
//     }

//     void visualize(osg::Geode& geode) const
//     {
//         // create height field
//         osg::ref_ptr<osg::HeightField> heightField = createHeighField();

//         while(geode.removeDrawables(0));
//         // add height field to geode
//         osg::ShapeDrawable *drawable = new osg::ShapeDrawable(heightField);
//         geode.addDrawable(drawable);    

//         // set material properties
//         osg::StateSet* state = geode.getOrCreateStateSet();
//         osg::ref_ptr<osg::Material> mat = new osg::Material;
//         mat->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

//         mat->setAmbient( osg::Material::FRONT_AND_BACK,
//                 osg::Vec4( .5f, .5f, .3f, 1.0f ) );
//         mat->setDiffuse( osg::Material::FRONT_AND_BACK,
//                 osg::Vec4( .5f, .5f, .3f, 1.0f ) );
//         //mat->setSpecular( osg::Material::FRONT,
//         //          osg::Vec4( 1.f, 1.f, 1.f, 1.0f ) );

//         state->setAttribute( mat.get() );

//         osg::ref_ptr<osg::Image> image = createTextureImage();   
//         osg::Texture2D* tex = new osg::Texture2D(image);
//         tex->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR_MIPMAP_LINEAR);
//         tex->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);
//         tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
//         tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
//         state->setTextureAttributeAndModes(0, tex);          
//     };
    
//     maps::grid::CellExtents getCellExtents() const
//     {
//         return grid.calculateCellExtents();
//     }

//     maps::grid::Vector2d getResolution() const
//     {
//         return grid.getResolution();
//     }

//     base::Affine3d getLocalFrame() const
//     {
//         return grid.getLocalFrame();
//     }

//     osg::HeightField* createHeighField() const
//     {
//         // create height field
//         osg::HeightField* heightField = new osg::HeightField();
//         heightField->allocate(grid.getNumCells().x(), grid.getNumCells().y());
//         heightField->setXInterval(grid.getResolution().x());
//         heightField->setYInterval(grid.getResolution().y());
//         heightField->setSkirtHeight(0.0f); 

//         double min = grid.getMin(false);
//         double default_value = grid.getDefaultValue();

//         for (unsigned int r = 0; r < heightField->getNumRows(); r++) 
//         {
//             for (unsigned int c = 0; c < heightField->getNumColumns(); c++) 
//             {
//                 GridT cell_value = grid.at(maps::grid::Index(c, r));

//                 if( cell_value !=  default_value)
//                     heightField->setHeight(c, r, cell_value);
//                 else
//                     heightField->setHeight(c, r, min);    // min elevation
//             }
//         }     

//         return heightField;  
//     }    

//     osg::Image* createTextureImage() const
//     {
//         osg::Image* image = new osg::Image(); 

//         //convert double to uint16 
//         int size = grid.getNumCells().x() * grid.getNumCells().y() * 4;
//         unsigned char* image_raw_data = new unsigned char[size];
//         unsigned char* pos = image_raw_data;

//         GridT min = grid.getMin(false);
//         GridT max = grid.getMax(false);

//         //scaling between SCALING_MIN_VALUE and SCALING_MAX_VALUE meters 
//         double scaling = std::abs(max - min);

//         if(scaling == 0)
//             scaling = 1.0;

//         // fill image with color
//         for (unsigned int y = 0; y < grid.getNumCells().y(); ++y)
//         {
//             for (unsigned int x = 0; x < grid.getNumCells().x(); ++x)
//             {
//                 /** Get the cell value **/
//                 GridT cell_value = grid.at(maps::grid::Index(x, y));

//                 double normalize_value = (double)(cell_value - min)/scaling;
//                 osg::Vec4f col(1.0,1.0,0.6,1.0);
//                 this->heatMapGradient.getColorAtValue(normalize_value, col.r(),col.g(),col.b());

//                 *pos++ = (unsigned char)(col.r() * 255.0);
//                 *pos++ = (unsigned char)(col.g() * 255.0);
//                 *pos++ = (unsigned char)(col.b() * 255.0);
//                 *pos++ = (unsigned char)(col.a() * 255.0);
//             }
//         }

//         image->setImage(
//                 grid.getNumCells().x(),
//                 grid.getNumCells().y(),
//                 1, // datadepth per channel
//                 GL_RGBA, 
//                 GL_RGBA, 
//                 GL_UNSIGNED_BYTE, // GLenum type, (GL_UNSIGNED_BYTE, 0x1401)
//                 (unsigned char*)(image_raw_data), // unsigned char* data
//                 osg::Image::USE_NEW_DELETE, // USE_NEW_DELETE, //osg::Image::NO_DELETE,// AllocationMode mode (shallow copy)
//                 1);      

//         return image;
//     }    
// };

MapVisualization::MapVisualization():heightFieldCreated(false)
{}

MapVisualization::~MapVisualization()
{
}

osg::ref_ptr<osg::Node> MapVisualization::createMainNode()
{
    osg::ref_ptr<osg::Group> mainNode = new osg::Group;
    geode = new osg::Geode();
    mainNode->addChild(geode.get());

    return mainNode;
}

void MapVisualization::updateMainNode ( osg::Node* node )
{
    if (!heightFieldCreated){
        heightField= new osg::HeightField();
        heightFieldCreated = true;
        // map
        // heightField->allocate(grid.getNumCells().x(), grid.getNumCells().y());
        // heightField->setXInterval(grid.getResolution().x());
        // heightField->setYInterval(grid.getResolution().y());
        // heightField->setSkirtHeight(0.0f); 

        // double min = grid.getMin(false);
        // double default_value = grid.getDefaultValue();
    }

         for (unsigned int r = 0; r < heightField->getNumRows(); r++) 
        {
            for (unsigned int c = 0; c < heightField->getNumColumns(); c++) 
            {
                //GridT cell_value = grid.at(maps::grid::Index(c, r));
                
                // if( cell_value !=  default_value)
                //     heightField->setHeight(c, r, cell_value);
                // else
                //     heightField->setHeight(c, r, min);    // min elevation
            }
        }   

    //if(!p) return;

    // Draw map.
    //p->visualize(*geode);

    // Draw map extents.
    // visualizeMapExtents(p->getCellExtents(), p->getResolution());

    // Set local frame.
    // setLocalFrame(p->getLocalFrame());
}

void MapVisualization::updateDataIntern(asn1SccMap const& value)
{
    // p.reset(new DataHold<double>( value ));
    map = value;
}

//Macro that makes this plugin loadable in ruby, this is optional.
//VizkitQtPlugin(ElevationMapVisualization)
