/**
 * @file kdtree.tcc
 * Implementation of kd_tree class.
 */

#include "kdtree.h"
#include<math.h>

template <int Dim>
bool kd_tree<Dim>::smaller_in_dimension(const point<Dim>& first, const point<Dim>& second,int curDim) const
{
	
	if(first[curDim]<second[curDim])
	return true;
	else if(first[curDim]>second[curDim])
	return false;
     else
	return first<second;
}

template <int Dim>
bool kd_tree<Dim>::should_replace(const point<Dim>& target, const point<Dim>& current_best, const point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
	int dis1=0;
	int dis2=0;
	for(int i=0;i<Dim;i++)
	{
		dis1=dis1+pow(target[i]-current_best[i],2);
		dis2=dis2+pow(target[i]-potential[i],2);		
	}
	if(dis1<dis2)
	return false;
	else if(dis1>dis2)
	return true;
	else
	return potential<current_best;
   
}

template <int Dim>
kd_tree<Dim>::kd_tree(const std::vector<point<Dim>>& newpoints)
{
	if(newpoints.size()!=0)
     {
	points=newpoints;
	buildtree(points,0,points.size()-1,0);
	}
     else
	return;


}
template <int Dim>
void kd_tree<Dim>::buildtree(std:: vector<point<Dim>>& newpoints,int begin, int end, int currDim)
{
	
    if(begin!=end)
    {
	quickselect(newpoints, begin, end, currDim);
 
	if(begin!=(begin+end)/2)
	{
      buildtree(newpoints,begin, (begin+end)/2-1,(currDim+1)%Dim);
      buildtree(newpoints,(begin+end)/2+1,end, (currDim+1)%Dim);
	}

	else
	{
	buildtree(newpoints,begin,(begin+end)/2,(currDim+1)%Dim);
	}
    }
	else
	return;

}
template <int Dim>
void  kd_tree<Dim>::quickselect(std::vector<point<Dim>>& newpoints, int first,int second,int currDim)
{
	for(int i=first;i<=second;i++)  
	{	auto min=i;
		auto minp= newpoints[min];
		for(int j=i+1;j<=second;j++)
		{
			if(!smaller_in_dimension(minp,newpoints[j],currDim))
			{
				minp=newpoints[j];
				min=j;   
			}
		}
          std::swap(newpoints[i],newpoints[min]);
	}
}

template <int Dim>
point<Dim> kd_tree<Dim>::find_nearest_neighbor(const point<Dim>& query) const
{
	if(points.size()>=1)
	{
	int r=0;
	return  find(points, query,0,points.size()-1,0,r);  
	}
	else
	return point<Dim>{};
}


template<int Dim>
int kd_tree<Dim>::r(const point<Dim>& point1, const point<Dim>& point2) const 
{
  int radius=0;
  for(int i=0;i<=Dim-1;i++)
	{
	radius=radius+pow(point1[i]-point2[i],2);
	}
  return radius;
}


template<int Dim>
point<Dim> kd_tree<Dim>::find(const std::vector<point<Dim>>& ps, const point<Dim>& query ,int start, int end, int currDim, int& radius) const
{
   if(start==end)
    {
      radius=r(points[start], query);
	 auto temp=points[end];
      return temp; 
    }
  
  point<Dim> tp;
  point<Dim> tp1;
 
	if(!smaller_in_dimension(query, points[(start+end)/2], currDim))  
	{
		tp=find(ps, query, (start+end)/2+1, end, (currDim+1)%Dim,radius);	
	}
	else
	{
		if(start!=(start+end)/2)
		tp=find(ps,query,start,(start+end)/2-1,(currDim+1)%Dim,radius);  
		else
		tp= find(ps, query, start, (start+end)/2, (currDim+1)%Dim,radius); 
	}
	  
	if(should_replace(query, tp, points[(start+end)/2]))
	{
	radius=r(query, tp);
	tp=points[(start+end)/2];
	}
 
     if(radius>=pow(query[currDim]-points[(start+end)/2][currDim],2) )   
    {
      if(smaller_in_dimension(query, points[(start+end)/2], currDim))  
	{
	tp1= find(ps, query, (start+end)/2+1, end, (currDim+1)%Dim,radius);   
	}
      else
	{
		if(start!=(start+end)/2)
		tp1=find(ps,query,start,(start+end)/2-1,(currDim+1)%Dim,radius);
		else
		tp1= find(ps, query, start, (start+end)/2, (currDim+1)%Dim,radius);
	}

    }

   if(should_replace(query, tp, tp1))
     {
       radius=r(query,tp1);
       tp=tp1;
     } 
  return tp;
}



