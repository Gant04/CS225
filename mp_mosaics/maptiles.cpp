/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include <unordered_map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
		vector<Point<3>> point_colors;
		for(const TileImage tile: theTiles){
				point_colors.push_back(convertToXYZ(tile.getAverageColor()));
		}

		std::map<Point<3>,TileImage*> Point2TileImage;

		for(size_t i=0;i<theTiles.size();i++){
			Point2TileImage[point_colors[i]]= & theTiles[i];
		}

		KDTree<3> color_tree(point_colors);

		MosaicCanvas* new_mosaic=  new MosaicCanvas(theSource.getRows(),theSource.getColumns());

		for(int i=0;i<theSource.getRows();i++){
			for(int j=0;j<theSource.getColumns();j++){
				LUVAPixel region_color=theSource.getRegionColor(i,j);
				Point<3> average_color=convertToXYZ(region_color);
				TileImage * new_tile=Point2TileImage[color_tree.findNearestNeighbor(average_color)];
				new_mosaic->setTile(i,j,new_tile);
			}
		}
		


    return new_mosaic;
}

