/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"
#include <stdexcept>
mosaic_canvas map_tiles(const source_image& source, const std::vector<tile_image>& tiles)
{
		if(source.rows()==0||source.columns()==0||tiles.size()==0)
      	throw std::runtime_error{"invalid!"};
     
		mosaic_canvas  img = mosaic_canvas(source.rows(), source.columns());
		std::map<point<3>, tile_image> tilemap;
		std::vector<point<3>> tp;
	
	
		for(auto it=tiles.begin();it!=tiles.end();it++)
          {
		epng::rgba_pixel curr = it->average_color();
		point<3>tpp (curr.red, curr.green, curr.blue);
		tp.push_back(tpp);
		tilemap[tpp]=*it;
		}
	

	kd_tree<3>t{tp};

		for(int i=0;i<source.rows();i++)
		{
			for(int j=0;j<source.columns();j++)
			{
				epng:: rgba_pixel region=source.region_color(i,j);
				point<3> query (region.red, region.green, region.blue);
				point<3> resultcolor= t.find_nearest_neighbor(query);
				tile_image tile= tilemap[resultcolor];
				img.set_tile(i,j,tile); 
			}
		}
  
 	 return img;  
}
