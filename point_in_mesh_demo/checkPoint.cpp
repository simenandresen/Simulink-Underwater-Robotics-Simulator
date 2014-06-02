#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/common.h>
#include <pcl/io/ply_io.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/point_types.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/io/io.h>
#include <pcl/common/time.h>
#include <sstream>  
#include <string> 
#include <pcl/visualization/pcl_visualizer.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace pcl;
using namespace std;

#define SAME_CLOCKNESS  1
#define DIFF_CLOCKNESS  0

typedef struct fpoint_tag
{
   float x;
   float y;
   float z;
} fpoint;

#define crossProduct(a,b,c) \
	(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
	(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
	(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];

/* a = b - c */
#define vector(a,b,c) \
	(a)[0] = (b)[0] - (c)[0];	\
	(a)[1] = (b)[1] - (c)[1];	\
	(a)[2] = (b)[2] - (c)[2];

#define innerProduct(v,q) \
		((v)[0] * (q)[0] + \
		(v)[1] * (q)[1] + \
		(v)[2] * (q)[2])

// method to check if a ray intersects a triangle
int rayIntersectsTriangle(float *p, float *d,
			float *v0, float *v1, float *v2) {
	float e1[3],e2[3],h[3],s[3],q[3];
	float a,f,u,v,t;
	vector(e1,v1,v0);
	vector(e2,v2,v0);
	crossProduct(h,d,e2);
	a = innerProduct(e1,h);
	if (a > -0.00001 && a < 0.00001)
		return(0);
	f = 1/a;
	vector(s,p,v0);
	u = f * (innerProduct(s,h));
	if (u < 0.0 || u > 1.0){
		return(0);
	}
	crossProduct(q,s,e1);
	v = f * innerProduct(d,q);
	if (v < 0.0 || u + v > 1.0)
		return(0);
	// at this stage we can compute t to find out where
	// the intersection point is on the line
	t = f * innerProduct(e2,q);
	if (t > 0.00001){ // ray intersection
		return(1);
	}else{ // this means that there is a line intersection
		   // but not a ray intersection
		return (0);
		 }
}

int
main (int argc, char** argv){

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
	viewer->setBackgroundColor (0, 0, 0);
	viewer->addCoordinateSystem (1.0, 0);
	viewer->initCameraParameters ();

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PolygonMesh mesh;
	pcl::io::loadPolygonFile("mesh.vtk",mesh);			
	pcl::PointXYZ p1,p2,p3;

	// get cloud from mesh
	pcl::fromPCLPointCloud2 <pcl::PointXYZ>  (mesh.cloud,*cloud);

	// animation 
	std::vector<pcl::Vertices> polygons;
	pcl::Vertices vertice;

	//	viewer->addPolygonMesh<pcl::PointXYZ> (cloud,polygons,"mesh");
	viewer->addPolygonMesh<pcl::PointXYZ>(cloud,polygons, "aMesh");
	float ptInside [] = {1.0, 1.0, 0.0};
	float vect [] = {4.0, 1.0, 1.0};
	float pt1 [3];
	float pt2 [3];
	float pt3 [3];
	int isInside(0);
	double startTime = pcl::getTime();
	for(int i = 0; i< mesh.polygons.size() ; i++){			
		p1 = cloud->points[ mesh.polygons[i].vertices[0]  ] ;
		p2 = cloud->points[ mesh.polygons[i].vertices[1]  ] ;
		p3 = cloud->points[ mesh.polygons[i].vertices[2]  ] ;
		pt1[0] = p1.x;
		pt1[1] = p1.y;
		pt1[2] = p1.z;
		pt2[0] = p2.x;
		pt2[1] = p2.y;
		pt2[2] = p2.z;
		pt3[0] = p3.x;
		pt3[1] = p3.y;
		pt3[2] = p3.z;
		isInside += rayIntersectsTriangle(ptInside,vect , pt1, pt2, pt3);	
	}
	double endTime = pcl::getTime();
	double diffTime = endTime - startTime ;
	p1.x = ptInside[0];
	p1.y = ptInside[1];
	p1.z = ptInside[2];
	int scale = 1;
	p2.x = ptInside[0] + vect[0]; 
	p2.y = ptInside[1] + vect[1]; 
	p2.z = ptInside[2] + vect[2]; 
	viewer->addPolygonMesh(mesh,"amesh");
	viewer->addLine(p1,p2,"line");
	viewer->addSphere(p1,0.1,"sphere");

	cout << "times intersecting " << isInside << endl;
	cout << "time : " << diffTime << endl;
	cout << "Press w to show wireframe" << endl;
	while (!viewer->wasStopped ()){
		viewer->spinOnce (100);
		boost::this_thread::sleep (boost::posix_time::microseconds (100000));
	}

	return (0);
}
