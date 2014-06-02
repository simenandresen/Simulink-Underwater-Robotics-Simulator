#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>

#include <iostream>
#include <pcl/common/common.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/point_types.h>
#include <pcl/surface/mls.h>
#include <pcl/surface/poisson.h>
#include <pcl/filters/passthrough.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/surface/vtk_smoothing/vtk_utils.h>

#include <pcl/io/vtk_io.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <math.h>
using namespace pcl;
using namespace std;


int
main (int argc, char** argv){
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

		// Fill in the cloud data
		int samples = 300;
		cloud->width  = samples;
		cloud->height = 1;
		cloud->points.resize (cloud->width * cloud->height);
		double x,y,z, temp;
		for (size_t i = 0; i < cloud->points.size (); ++i)
		{
				x =	rand () % 100 - 50;
				y =	rand () % 100 - 50;
				z =	rand () % 100 - 50;
				temp = (sqrt( x*x + y*y + z*z ));
				cloud->points[i].x = x / temp;
				cloud->points[i].y = y / temp;
				cloud->points[i].z = z / temp;
		}
		pcl::io::savePCDFileBinary("out.pcd",*cloud);
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);

		// Create the filtering object
		pcl::PassThrough<pcl::PointXYZ> pass;
		pass.setInputCloud (cloud);
		pass.setFilterFieldName ("z");
		pass.setFilterLimits (-0.34, 100);
		//pass.setFilterLimitsNegative (true);
		pass.filter (*cloud);

		
		   cout << "begin normal estimation" << endl;
		   NormalEstimationOMP<PointXYZ, Normal> ne;
		   ne.setNumberOfThreads(8);
		   ne.setInputCloud(cloud);
		   ne.setRadiusSearch(0.9);
		   Eigen::Vector4f centroid;
		   compute3DCentroid(*cloud, centroid);
		   ne.setViewPoint(centroid[0], centroid[1], centroid[2]);

		   PointCloud<Normal>::Ptr cloud_normals (new PointCloud<Normal>());
		   ne.compute(*cloud_normals);
		   cout << "normal estimation complete" << endl;
		   cout << "reverse normals' direction" << endl;

		   for(size_t i = 0; i < cloud_normals->size(); ++i){
		   cloud_normals->points[i].normal_x *= -1;
		   cloud_normals->points[i].normal_y *= -1;
		   cloud_normals->points[i].normal_z *= -1;
		   }

		   cout << "combine points and normals" << endl;
		   PointCloud<PointNormal>::Ptr cloud_smoothed_normals(new PointCloud<PointNormal>());
		   concatenateFields(*cloud, *cloud_normals, *cloud_smoothed_normals);

		   cout << "begin poisson reconstruction" << endl;
		   Poisson<PointNormal> poisson;
		   poisson.setDepth(4);
		   poisson.setInputCloud(cloud_smoothed_normals);
		   PolygonMesh mesh;
		   poisson.reconstruct(mesh);


		//io::savePLYFile(argv[2], mesh);
		io::saveVTKFile("mesh.vtk", mesh);
		io::savePCDFileBinary("output.pcd",*cloud_smoothed_normals);





		// Normal estimation*
		pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
		pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
		pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
		tree->setInputCloud (cloud);
		n.setInputCloud (cloud);
		n.setSearchMethod (tree);
		n.setKSearch (10);
		n.compute (*normals);
		//* normals should not contain the point normals + surface curvatures

		// Concatenate the XYZ and normal fields*
		pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
		pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
		//* cloud_with_normals = cloud + normals

		// Create search tree*
		pcl::search::KdTree<pcl::PointNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointNormal>);
		tree2->setInputCloud (cloud_with_normals);

		// Initialize objects
		pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
		pcl::PolygonMesh triangles;

		// Set the maximum distance between connected points (maximum edge length)
		gp3.setSearchRadius (5.55);

		// Set typical values for the parameters
		gp3.setMu (7.5);
		gp3.setMaximumNearestNeighbors (100);
		gp3.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
		gp3.setMinimumAngle(M_PI/18); // 10 degrees
		gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
		gp3.setNormalConsistency(false);

		// Get result
		gp3.setInputCloud (cloud_with_normals);
		gp3.setSearchMethod (tree2);
		gp3.reconstruct (triangles);

		// Additional vertex information
		std::vector<int> parts = gp3.getPartIDs();
		std::vector<int> states = gp3.getPointStates();

		io::saveVTKFile("mesh2.vtk", triangles);

		return (0);
}
